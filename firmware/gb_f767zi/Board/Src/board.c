#include "board.h"

#include "board_gpio.h"

void board_init(void)
{
    board_gpio_init();
}
