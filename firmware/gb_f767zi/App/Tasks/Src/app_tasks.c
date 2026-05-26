#include "app_tasks.h"

#include "cmsis_os.h"
#include "debug_task.h"
#include "heartbeat_task.h"

static osThreadId_t heartbeatTaskHandle;
static const osThreadAttr_t heartbeatTask_attributes = {
  .name = "heartbeat",
  .stack_size = 256 * 4,
  .priority = (osPriority_t)osPriorityLow,
};

static osThreadId_t debugTaskHandle;
static const osThreadAttr_t debugTask_attributes = {
  .name = "debug",
  .stack_size = 512 * 4,
  .priority = (osPriority_t)osPriorityLow,
};

void app_tasks_init(void)
{
  heartbeatTaskHandle = osThreadNew(heartbeat_task, NULL, &heartbeatTask_attributes);
  debugTaskHandle = osThreadNew(debug_task, NULL, &debugTask_attributes);
}
