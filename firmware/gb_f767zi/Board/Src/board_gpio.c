#include "board_gpio.h"

#include "main.h"

void board_gpio_init(void)
{
}

void board_debug_pin_set(void)
{
  //GPIOF, GPIO_PIN_12, PF_12
  HAL_GPIO_WritePin(DEBUG_GPIO_Port, DEBUG_Pin, GPIO_PIN_SET);
}

void board_debug_pin_reset(void)
{
  HAL_GPIO_WritePin(DEBUG_GPIO_Port, DEBUG_Pin, GPIO_PIN_RESET);
}
