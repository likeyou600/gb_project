#include "input_task.h"

#include "app_config.h"
#include "board_input.h"
#include "cmsis_os.h"
#include "Input/input_service.h"
#include "main.h"


typedef struct
{
  bool stable_pressed;
  bool last_raw_pressed;
  uint32_t last_change_tick;
  uint32_t press_start_tick;
} input_button_state_t;

static input_button_state_t buttonState[sizeof(buttonMap) / sizeof(buttonMap[0])];

static bool input_task_update_debounce(input_button_state_t *state, bool raw_pressed, uint32_t now)
{
  // 如果這次讀到的 GPIO 狀態跟上次不一樣，代表按鍵可能正在變化，所以先記錄下這個變化的時間點。
  // 按鍵剛按下時，GPIO 可能會因為彈跳變成這樣：
  // false → true → false → true → true
  // 所以程式前面這段會一直更新 last_change_tick。
  if (raw_pressed != state->last_raw_pressed)
  {
    state->last_raw_pressed = raw_pressed;
    state->last_change_tick = now;
  }

  // GPIO 狀態至少維持 APP_INPUT_DEBOUNCE_MS 沒再亂跳，才相信它是真的按下或放開。
  if ((now - state->last_change_tick) >= APP_INPUT_DEBOUNCE_MS)
  {
    // 如果是按下按鍵：raw_pressed = true、stable_pressed = false
    // 如果是放開按鍵：raw_pressed = false、stable_pressed = true
    if (raw_pressed != state->stable_pressed)
    {
      state->stable_pressed = raw_pressed;
      return true;
    }
  }

  return false;
}

static void input_task_handle_button_event(const input_button_hw_t *hw, input_button_state_t *state, uint32_t now)
{
  // 如果是穩定按下，就記錄按下的時間點，並送出 PRESS event。
  if (state->stable_pressed)
  {
    state->press_start_tick = now;

    (void)input_service_post_event(hw->key, INPUT_ACTION_PRESS);
    return;
  }

  // 如果是穩定放開，就送出 RELEASE event，
  // 再根據按下的時間長短來決定是 SHORT 還是 LONG。
  uint32_t press_duration = now - state->press_start_tick;
  input_action_t action = INPUT_ACTION_SHORT;

  (void)input_service_post_event(hw->key, INPUT_ACTION_RELEASE);

  // 按下時間 < 300 ms  -> short press ; >= 300 ms -> long press
  if (press_duration >= APP_INPUT_LONG_PRESS_MS)
  {
    action = INPUT_ACTION_LONG;
  }

  (void)input_service_post_event(hw->key, action);
}

static void input_task_process_button(const input_button_hw_t *hw, input_button_state_t *state, bool raw_pressed)
{
  uint32_t now = HAL_GetTick();

  if (input_task_update_debounce(state, raw_pressed, now))
  {
    input_task_handle_button_event(hw, state, now);
  }
}

void input_task(void *argument)
{
  (void)argument;

  for (;;)
  {
    for (size_t i = 0U; i < (sizeof(buttonMap) / sizeof(buttonMap[0])); i++)
    {
      bool raw_pressed = board_input_is_pressed(buttonMap[i].board_input);
      // if (raw_pressed)
      // {
      //   input_service_post_event(buttonMap[i].key, INPUT_ACTION_PRESS);
      // }

      input_task_process_button(&buttonMap[i], &buttonState[i], raw_pressed);
    }

    osDelay(APP_INPUT_SCAN_PERIOD_MS);
  }
}
