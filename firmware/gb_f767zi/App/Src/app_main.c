#include "app_main.h"

#include "app_tasks.h"
#include "Input/input_service.h"
#include "Log/log_service.h"

void app_main_init(void)
{
// Initialize application modules
// Message queue init
#if APP_LOG_ENABLE
  log_service_init();
#endif
#if APP_INPUT_ENABLE
  input_service_init();
#endif

  // Initialize application tasks
  app_tasks_init();
}

void app_main_run(void)
{
  LOG_INFO("RTOS-app_main", "app_main_run called");
  // Application main loop can be implemented here if needed
}
