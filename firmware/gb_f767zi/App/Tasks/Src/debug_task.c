#include "debug_task.h"

#include "cmsis_os.h"
#include "Log/log_service.h"

void debug_task(void *argument)
{
  (void)argument;
  uint32_t counter = 0U;

  for (;;)
  {
    LOG_INFO("RTOS-debug_task", "debug_task alive counter=%lu", counter++);
    osDelay(1000U);
  }
}
