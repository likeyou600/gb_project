#include "app_tasks.h"

#include "app_config.h"
#include "busy_task.h"
#include "cmsis_os.h"
#include "debug_task.h"
#include "heartbeat_task.h"
#include "input_debug_task.h"
#include "input_irq_task.h"
#include "input_task.h"
#include "logger_task.h"
#include "Log/log_service.h"
#include "monitor_task.h"

static void app_tasks_log_create_result(const char *name, osThreadId_t handle)
{
  if (handle == NULL)
  {
    LOG_ERROR("tasks", "%s create failed", name);
  }
  else
  {
    LOG_INFO("tasks", "%s created", name);
  }
}

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

#if APP_INPUT_ENABLE
static osThreadId_t inputTaskHandle;
static const osThreadAttr_t inputTask_attributes = {
  .name = "input",
  .stack_size = 512 * 4,
  .priority = (osPriority_t)osPriorityNormal,
};
#endif

#if APP_INPUT_ENABLE && APP_INPUT_IRQ_TASK_ENABLE
static osThreadId_t inputIrqTaskHandle;
static const osThreadAttr_t inputIrqTask_attributes = {
  .name = "inputIrq",
  .stack_size = 512 * 4,
  .priority = (osPriority_t)osPriorityNormal,
};
#endif

#if APP_INPUT_ENABLE && APP_INPUT_DEBUG_TASK_ENABLE
static osThreadId_t inputDebugTaskHandle;
static const osThreadAttr_t inputDebugTask_attributes = {
  .name = "inputDebug",
  .stack_size = 512 * 4,
  .priority = (osPriority_t)osPriorityLow,
};
#endif

/* Task initialization function ------------------------------------------------- */
void app_tasks_init(void)
{
/* 測試相關 function ------------------------------------------------- */
#if APP_BUSY_TASK_TEST_ENABLE
  busyTaskHandle = osThreadNew(busy_task, NULL, &busyTask_attributes);
  app_tasks_log_create_result("busy", busyTaskHandle);
#endif

/* 監控相關 function ------------------------------------------------- */
#if APP_MONITOR_TASK_ENABLE
  monitorTaskHandle = osThreadNew(monitor_task, NULL, &monitorTask_attributes);
  app_tasks_log_create_result("monitor", monitorTaskHandle);
#endif

#if APP_LOG_ENABLE
  loggerTaskHandle = osThreadNew(logger_task, NULL, &loggerTask_attributes);
  app_tasks_log_create_result("logger", loggerTaskHandle);
#endif
/* 調試相關 function ------------------------------------------------- */
  debugTaskHandle = osThreadNew(debug_task, NULL, &debugTask_attributes);
  app_tasks_log_create_result("debug", debugTaskHandle);

  heartbeatTaskHandle = osThreadNew(heartbeat_task, NULL, &heartbeatTask_attributes);
  app_tasks_log_create_result("heartbeat", heartbeatTaskHandle);

/* 輸入相關 function ------------------------------------------------- */
#if APP_INPUT_ENABLE
  inputTaskHandle = osThreadNew(input_task, NULL, &inputTask_attributes);
  app_tasks_log_create_result("input", inputTaskHandle);
#endif
#if APP_INPUT_ENABLE && APP_INPUT_IRQ_TASK_ENABLE
  inputIrqTaskHandle = osThreadNew(input_irq_task, NULL, &inputIrqTask_attributes);
  app_tasks_log_create_result("input_irq", inputIrqTaskHandle);
#endif
#if APP_INPUT_ENABLE && APP_INPUT_DEBUG_TASK_ENABLE
  inputDebugTaskHandle = osThreadNew(input_debug_task, NULL, &inputDebugTask_attributes);
  app_tasks_log_create_result("input_debug", inputDebugTaskHandle);
  // [00000019][ERROR][tasks] input_debug create failed
#endif
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

osThreadId_t app_tasks_get_input_handle(void)
{
#if APP_INPUT_ENABLE
  return inputTaskHandle;
#else
  return NULL;
#endif
}

osThreadId_t app_tasks_get_input_irq_handle(void)
{
#if APP_INPUT_ENABLE && APP_INPUT_IRQ_TASK_ENABLE
  return inputIrqTaskHandle;
#else
  return NULL;
#endif
}

osThreadId_t app_tasks_get_input_debug_handle(void)
{
#if APP_INPUT_ENABLE && APP_INPUT_DEBUG_TASK_ENABLE
  return inputDebugTaskHandle;
#else
  return NULL;
#endif
}
