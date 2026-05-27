#include "busy_task.h"

#include <stdint.h>

#include "board_gpio.h"
#include "cmsis_os.h"
#include "Log/log_service.h"
#include "main.h"

void busy_task(void *argument)
{
  uint32_t counter = 0U;

  (void)argument;

  for (;;)
  {
    board_debug_pin_set();
    for (volatile uint32_t i = 0U; i < 5000000UL; i++)
    {
    }
    board_debug_pin_reset();

    osDelay(200U);

    // LOG_INFO("busy", "busy loop done counter=%lu", counter++);

    // osDelay(10U);
  }
}
