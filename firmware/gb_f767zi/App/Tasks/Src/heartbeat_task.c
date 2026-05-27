#include "heartbeat_task.h"

#include "board_led.h"
#include "cmsis_os.h"

void heartbeat_task(void *argument)
{
  (void)argument;

  for (;;)
  {
    // HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    board_led_toggle(BOARD_LED_RED);
    osDelay(500U);
  }
}
