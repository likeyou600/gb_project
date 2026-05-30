#include "board_input.h"

#include "main.h"

bool board_input_is_pressed(board_input_t input)
{
  switch (input)
  {
  case BOARD_INPUT_INT_USER:
    return HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET;
  case BOARD_INPUT_EXT_UP:
    return HAL_GPIO_ReadPin(EXT_UP_Btn_GPIO_Port, EXT_UP_Btn_Pin) == GPIO_PIN_RESET;
  case BOARD_INPUT_EXT_DOWN:
    return HAL_GPIO_ReadPin(EXT_DOWN_Btn_GPIO_Port, EXT_DOWN_Btn_Pin) == GPIO_PIN_RESET;
  case BOARD_INPUT_EXT_LEFT:
    return HAL_GPIO_ReadPin(EXT_LEFT_Btn_GPIO_Port, EXT_LEFT_Btn_Pin) == GPIO_PIN_RESET;
  case BOARD_INPUT_EXT_RIGHT:
    return HAL_GPIO_ReadPin(EXT_RIGHT_Btn_GPIO_Port, EXT_RIGHT_Btn_Pin) == GPIO_PIN_RESET;
  case BOARD_INPUT_EXT_OK:
    return HAL_GPIO_ReadPin(EXT_OK_Btn_GPIO_Port, EXT_OK_Btn_Pin) == GPIO_PIN_RESET;
  default:
    return false;
  }
}
