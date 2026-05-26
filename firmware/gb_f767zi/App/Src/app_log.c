#include "app_log.h"

#include "app_config.h"
#include "board_uart.h"

void app_log_write(const char *message)
{
#if APP_LOG_ENABLE
  board_uart_write_debug(message);
#else
  (void)message;
#endif
}
