#include "Log/log_service.h"

#include <stdio.h>
#include <string.h>

#include "app_config.h"
#include "board_uart.h"
#include "cmsis_os.h"
#include "main.h"

/* Log message definitions ------------------------------------------------- */
typedef struct
{
  uint32_t timestamp;
  log_service_level_t level;
  char module[APP_LOG_MODULE_NAME_MAX_LEN];
  char message[APP_LOG_MESSAGE_MAX_LEN];
} log_service_message_t;

static osMessageQueueId_t logQueueHandle;

void log_service_init(void)
{
  logQueueHandle = osMessageQueueNew(APP_LOG_QUEUE_DEPTH, sizeof(log_service_message_t), NULL);
  LOG_INFO("RTOS-log_service", "log_service_init called");
}

/* Log function definitions ------------------------------------------------- */
static const char *log_service_level_text(log_service_level_t level)
{
  switch (level)
  {
  case APP_LOG_LEVEL_INFO:
    return "INFO";
  case APP_LOG_LEVEL_WARN:
    return "WARN";
  case APP_LOG_LEVEL_ERROR:
    return "ERROR";
  default:
    return "UNK";
  }
}

void log_service_submit(log_service_level_t level, const char *module, const char *format, ...)
{
  va_list args;

  va_start(args, format);
  log_service_vsubmit(level, module, format, args);
  va_end(args);
}

void log_service_vsubmit(log_service_level_t level, const char *module, const char *format, va_list args)
{
#if APP_LOG_ENABLE

  log_service_message_t logMessage = { 0 };

  if ((logQueueHandle == NULL) || (format == NULL))
  {
    return;
  }

  logMessage.timestamp = HAL_GetTick();
  logMessage.level = level;

  module = module ? module : "app";

  (void)snprintf(logMessage.module, sizeof(logMessage.module), "%s", module);
  (void)vsnprintf(logMessage.message, sizeof(logMessage.message), format, args);

  (void)osMessageQueuePut(logQueueHandle, &logMessage, 0U, 0U);

#else
  (void)level;
  (void)module;
  (void)format;
  (void)args;
#endif
}

/* Log processing function to be called in the logger task------------------- */
void log_service_process(void)
{
  log_service_message_t logMessage;
  char line[APP_LOG_MESSAGE_MAX_LEN + 40];

  if (osMessageQueueGet(logQueueHandle, &logMessage, NULL, osWaitForever) == osOK)
  {
    (void)snprintf(line, sizeof(line), "[%08lu][%-5s][%s] %s\r\n", logMessage.timestamp,
                   log_service_level_text(logMessage.level), logMessage.module, logMessage.message);
    board_uart_write_debug(line);
  }
}
