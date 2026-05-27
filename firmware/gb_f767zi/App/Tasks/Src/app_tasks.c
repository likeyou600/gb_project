#include "app_tasks.h"

#include "app_config.h"
#include "busy_task.h"
#include "cmsis_os.h"
#include "debug_task.h"
#include "heartbeat_task.h"
#include "logger_task.h"
#include "Log/log_service.h"
#include "monitor_task.h"

/* Task handle definitions ------------------------------------------------- */
#if APP_BUSY_TASK_TEST_ENABLE
static osThreadId_t busyTaskHandle;
static const osThreadAttr_t busyTask_attributes = {
  .name = "busy",
  .stack_size = 512 * 4,
  .priority = (osPriority_t)osPriorityNormal,
};
#endif

#if APP_LOG_ENABLE
static osThreadId_t loggerTaskHandle;
static const osThreadAttr_t loggerTask_attributes = {
  .name = "logger",
  .stack_size = 512 * 4,
  .priority = (osPriority_t)osPriorityNormal,
};
#endif

static osThreadId_t debugTaskHandle;
static const osThreadAttr_t debugTask_attributes = {
  .name = "debug",
  .stack_size = 512 * 4,
  .priority = (osPriority_t)osPriorityLow,
};

static osThreadId_t heartbeatTaskHandle;
static const osThreadAttr_t heartbeatTask_attributes = {
  .name = "heartbeat",
  .stack_size = 256 * 4,
  .priority = (osPriority_t)osPriorityLow,
};

#if APP_MONITOR_TASK_ENABLE
static osThreadId_t monitorTaskHandle;
static const osThreadAttr_t monitorTask_attributes = {
  .name = "monitor",
  .stack_size = 512 * 4,
  .priority = (osPriority_t)osPriorityLow,
};
#endif

/* Task initialization function ------------------------------------------------- */
void app_tasks_init(void)
{
#if APP_BUSY_TASK_TEST_ENABLE
  busyTaskHandle = osThreadNew(busy_task, NULL, &busyTask_attributes);
#endif

#if APP_MONITOR_TASK_ENABLE
  monitorTaskHandle = osThreadNew(monitor_task, NULL, &monitorTask_attributes);
#endif

#if APP_LOG_ENABLE
  loggerTaskHandle = osThreadNew(logger_task, NULL, &loggerTask_attributes);
#endif

  debugTaskHandle = osThreadNew(debug_task, NULL, &debugTask_attributes);
  heartbeatTaskHandle = osThreadNew(heartbeat_task, NULL, &heartbeatTask_attributes);
}


/* Get Task Handle Function ------------------------------------------------- */
osThreadId_t app_tasks_get_busy_handle(void)
{
#if APP_BUSY_TASK_TEST_ENABLE
  return busyTaskHandle;
#else
  return NULL;
#endif
}

osThreadId_t app_tasks_get_monitor_handle(void)
{
#if APP_MONITOR_TASK_ENABLE
  return monitorTaskHandle;
#else
  return NULL;
#endif
}

osThreadId_t app_tasks_get_logger_handle(void)
{
#if APP_LOG_ENABLE
  return loggerTaskHandle;
#else
  return NULL;
#endif
}

osThreadId_t app_tasks_get_debug_handle(void)
{
  return debugTaskHandle;
}

osThreadId_t app_tasks_get_heartbeat_handle(void)
{
  return heartbeatTaskHandle;
}

