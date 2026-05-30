#include "input_irq_task.h"

#include <stdbool.h>
#include <stdint.h>

#include "app_config.h"
#include "board_input.h"
#include "cmsis_os.h"
#include "Input/input_service.h"
#include "Log/log_service.h"

#define INPUT_THREAD_FLAG_USER_BTN_IRQ (1UL << 0)

static osThreadId_t inputIrqTaskHandle;
static osTimerId_t userButtonDebounceTimerHandle;
static bool userButtonStablePressed;

// timer expired
// 代表 debounce 等待時間到了，
// 不是 timer 自己判斷按鍵穩定，
// 而是準備重新讀一次 GPIO。
static void input_irq_task_user_button_timer_cb(void *argument)
{
  bool pressed;

  (void)argument;

  pressed = board_input_is_pressed(BOARD_INPUT_INT_USER);

  if (pressed != userButtonStablePressed)
  {
    userButtonStablePressed = pressed;

    if (userButtonStablePressed)
    {
      (void)input_service_post_event(INPUT_KEY_TEST, INPUT_ACTION_PRESS);
    }
    else
    {
      (void)input_service_post_event(INPUT_KEY_TEST, INPUT_ACTION_RELEASE);
    }
  }
}

void input_irq_task_notify_user_button_from_isr(void)
{
  if (inputIrqTaskHandle != NULL)
  {
    (void)osThreadFlagsSet(inputIrqTaskHandle, INPUT_THREAD_FLAG_USER_BTN_IRQ);
  }
}

void input_irq_task(void *argument)
{
  (void)argument;

  inputIrqTaskHandle = osThreadGetId();
  userButtonDebounceTimerHandle = osTimerNew(input_irq_task_user_button_timer_cb, osTimerOnce, NULL, NULL);
  LOG_INFO("input_irq", "user button debounce timer created");

  for (;;)
  {
    uint32_t flags = osThreadFlagsWait(INPUT_THREAD_FLAG_USER_BTN_IRQ, osFlagsWaitAny, osWaitForever);

    if ((flags & INPUT_THREAD_FLAG_USER_BTN_IRQ) != 0U)
    {
      if (userButtonDebounceTimerHandle != NULL)
      {
        (void)osTimerStart(userButtonDebounceTimerHandle, APP_INPUT_EXTI_DEBOUNCE_MS);
      }
    }
  }
}
