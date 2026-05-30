#include "input_debug_task.h"

#include "cmsis_os.h"
#include "Input/input_service.h"
#include "Log/log_service.h"

void input_debug_task(void *argument)
{
  input_event_t event;

  (void)argument;

  for (;;)
  {
    if (input_service_get_event(&event, osWaitForever) == osOK)
    {
      LOG_INFO("input", "key=%s action=%s tick=%lu", input_service_key_text(event.key),
               input_service_action_text(event.action), event.timestamp);
    }
  }
}
