#ifndef BOARD_UART_H
#define BOARD_UART_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

  void board_uart_write_debug(const char *message);
  void board_uart_write_debug_bytes(const uint8_t *data, size_t length);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_UART_H */
