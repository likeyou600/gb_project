#include "board_led.h"

#include "main.h"

static GPIO_TypeDef *board_led_port(board_led_t led)
{
    switch (led) {
    case BOARD_LED_GREEN:
        return LD1_GPIO_Port;
    case BOARD_LED_BLUE:
        return LD2_GPIO_Port;
    case BOARD_LED_RED:
        return LD3_GPIO_Port;
    default:
        return LD1_GPIO_Port;
    }
}

static uint16_t board_led_pin(board_led_t led)
{
    switch (led) {
    case BOARD_LED_GREEN:
        return LD1_Pin;
    case BOARD_LED_BLUE:
        return LD2_Pin;
    case BOARD_LED_RED:
        return LD3_Pin;
    default:
        return LD1_Pin;
    }
}

void board_led_on(board_led_t led)
{
    HAL_GPIO_WritePin(board_led_port(led), board_led_pin(led), GPIO_PIN_SET);
}

void board_led_off(board_led_t led)
{
    HAL_GPIO_WritePin(board_led_port(led), board_led_pin(led), GPIO_PIN_RESET);
}

void board_led_toggle(board_led_t led)
{
    HAL_GPIO_TogglePin(board_led_port(led), board_led_pin(led));
}
