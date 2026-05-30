#ifndef APP_TASKS_H
#define APP_TASKS_H

#include "cmsis_os.h"

#ifdef __cplusplus
extern "C"
{
#endif

  void app_tasks_init(void);
  osThreadId_t app_tasks_get_busy_handle(void);
  osThreadId_t app_tasks_get_logger_handle(void);
  osThreadId_t app_tasks_get_debug_handle(void);
  osThreadId_t app_tasks_get_heartbeat_handle(void);
  osThreadId_t app_tasks_get_input_handle(void);
  osThreadId_t app_tasks_get_input_irq_handle(void);
  osThreadId_t app_tasks_get_input_debug_handle(void);
  osThreadId_t app_tasks_get_monitor_handle(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_TASKS_H */
