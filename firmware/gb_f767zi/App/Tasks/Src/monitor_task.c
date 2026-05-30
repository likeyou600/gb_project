#include "monitor_task.h"

#include "app_config.h"
#include "app_tasks.h"
#include "cmsis_os.h"
#include "Log/log_service.h"

static void monitor_task_log_stack(const char *name, osThreadId_t handle)
{
  if (handle == NULL)
  {
    return;
  }

  LOG_INFO("RTOS-monitor_task", "%s stack_space=%lu", name, osThreadGetStackSpace(handle));
}

void monitor_task(void *argument)
{
  (void)argument;

  for (;;)
  {
    monitor_task_log_stack("logger", app_tasks_get_logger_handle());
    monitor_task_log_stack("debug", app_tasks_get_debug_handle());
    monitor_task_log_stack("heartbeat", app_tasks_get_heartbeat_handle());
    monitor_task_log_stack("input", app_tasks_get_input_handle());
    monitor_task_log_stack("input_irq", app_tasks_get_input_irq_handle());
    monitor_task_log_stack("input_debug", app_tasks_get_input_debug_handle());
    monitor_task_log_stack("busy", app_tasks_get_busy_handle());
    monitor_task_log_stack("monitor", app_tasks_get_monitor_handle());

    osDelay(APP_MONITOR_TASK_PERIOD_MS);
  }
}
