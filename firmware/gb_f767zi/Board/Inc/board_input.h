#ifndef BOARD_INPUT_H
#define BOARD_INPUT_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef enum
  {
    BOARD_INPUT_INT_USER = 0,
    BOARD_INPUT_EXT_UP,
    BOARD_INPUT_EXT_DOWN,
    BOARD_INPUT_EXT_LEFT,
    BOARD_INPUT_EXT_RIGHT,
    BOARD_INPUT_EXT_OK
  } board_input_t;

  bool board_input_is_pressed(board_input_t input);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_INPUT_H */
