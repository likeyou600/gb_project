#include "busy_task.h"

#include <stdint.h>

#include "cmsis_os.h"
#include "Log/log_service.h"

void busy_task(void *argument)
{
  uint32_t counter = 0U;

  (void)argument;

  for (;;)
  {
    for (volatile uint32_t i = 0U; i < 5000000UL; i++)
    {
    }

    LOG_INFO("busy", "busy loop done counter=%lu", counter++);

    osDelay(10U);
  }
}
