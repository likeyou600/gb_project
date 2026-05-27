#ifndef LOG_SERVICE_H
#define LOG_SERVICE_H

#include <stdarg.h>
#include <stdint.h>

#include "app_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

  typedef enum
  {
    APP_LOG_LEVEL_INFO = 0,
    APP_LOG_LEVEL_WARN,
    APP_LOG_LEVEL_ERROR
  } log_service_level_t;

  void log_service_init(void);
  void log_service_process(void);

  void log_service_submit(log_service_level_t level, const char *module, const char *format, ...);
  void log_service_vsubmit(log_service_level_t level, const char *module, const char *format, va_list args);

#define LOG_INFO(module, format, ...) log_service_submit(APP_LOG_LEVEL_INFO, module, format, ##__VA_ARGS__)
#define LOG_WARN(module, format, ...) log_service_submit(APP_LOG_LEVEL_WARN, module, format, ##__VA_ARGS__)
#define LOG_ERROR(module, format, ...) log_service_submit(APP_LOG_LEVEL_ERROR, module, format, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* LOG_SERVICE_H */
