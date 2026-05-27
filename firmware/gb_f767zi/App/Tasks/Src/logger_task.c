#include "logger_task.h"

#include "Log/log_service.h"

void logger_task(void *argument)
{
  (void)argument;

  for (;;)
  {
    log_service_process();
  }
}
