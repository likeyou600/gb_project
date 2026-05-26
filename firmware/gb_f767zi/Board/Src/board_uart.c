#include "board_uart.h"

#include <string.h>

#include "usart.h"

void board_uart_write_debug(const char *message)
{
    if (message == NULL) {
        return;
    }

    board_uart_write_debug_bytes((const uint8_t *)message, strlen(message));
}

void board_uart_write_debug_bytes(const uint8_t *data, size_t length)
{
    if ((data == NULL) || (length == 0U)) {
        return;
    }

    HAL_UART_Transmit(&huart3, (uint8_t *)data, (uint16_t)length, HAL_MAX_DELAY);
}
