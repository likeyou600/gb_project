#include "debug_task.h"

#include <stdio.h>

#include "app_log.h"
#include "cmsis_os.h"
#include "main.h"

void debug_task(void *argument)
{
  (void)argument;
  uint32_t counter = 0U;
  char message[80];


  for (;;)
  {
    // printf("[%08lu][rtos ][INFO] debug_task alive counter=%lu\r\n",
    //        HAL_GetTick(),
    //        counter++);
    (void)snprintf(message, sizeof(message), "[%08lu][rtos ][INFO] debug_task alive counter=%lu\r\n", HAL_GetTick(),
                   counter++);
    app_log_write(message);

    osDelay(1000U);
  }
}
