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
} input_button_state_t;

static input_button_state_t buttonState[sizeof(buttonMap) / sizeof(buttonMap[0])];

static void input_task_debounce_button(const input_button_hw_t *hw, input_button_state_t *state, bool raw_pressed)
{
  uint32_t now = HAL_GetTick();

  if (raw_pressed != state->last_raw_pressed)
  {
    state->last_raw_pressed = raw_pressed;
    state->last_change_tick = now;
  }

  if ((now - state->last_change_tick) >= APP_INPUT_DEBOUNCE_MS)
  {
    if (raw_pressed != state->stable_pressed)
    {
      state->stable_pressed = raw_pressed;

      if (state->stable_pressed)
      {
        (void)input_service_post_event(hw->key, INPUT_ACTION_SHORT);
      }
    }
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
      // input_service_post_event(buttonMap[i].key, INPUT_ACTION_SHORT);

      input_task_debounce_button(&buttonMap[i], &buttonState[i], raw_pressed);
    }

    osDelay(APP_INPUT_SCAN_PERIOD_MS);
  }
}
