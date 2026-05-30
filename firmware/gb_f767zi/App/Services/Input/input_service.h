#ifndef INPUT_SERVICE_H
#define INPUT_SERVICE_H

#include <stdint.h>
#include <stdbool.h>
#include "board_input.h"

#include "cmsis_os.h"

#ifdef __cplusplus
extern "C"
{
#endif

  typedef enum
  {
    INPUT_KEY_TEST = 0,
    INPUT_KEY_UP,
    INPUT_KEY_DOWN,
    INPUT_KEY_LEFT,
    INPUT_KEY_RIGHT,
    INPUT_KEY_OK,
  } input_key_t;

  typedef struct
  {
    input_key_t key;
    board_input_t board_input;
  } input_button_hw_t;

  static const input_button_hw_t buttonMap[] = {
    { INPUT_KEY_UP, BOARD_INPUT_EXT_UP },       { INPUT_KEY_DOWN, BOARD_INPUT_EXT_DOWN },
    { INPUT_KEY_LEFT, BOARD_INPUT_EXT_LEFT },   { INPUT_KEY_RIGHT, BOARD_INPUT_EXT_RIGHT },
    { INPUT_KEY_OK, BOARD_INPUT_EXT_OK },
  };

  typedef enum
  {
    INPUT_ACTION_PRESS = 0,
    INPUT_ACTION_RELEASE,
    INPUT_ACTION_SHORT,
    INPUT_ACTION_LONG
  } input_action_t;

  typedef struct
  {
    input_key_t key;
    input_action_t action;
    uint32_t timestamp;
  } input_event_t;

  void input_service_init(void);
  osStatus_t input_service_post_event(input_key_t key, input_action_t action);
  osStatus_t input_service_get_event(input_event_t *event, uint32_t timeout);

  const char *input_service_key_text(input_key_t key);
  const char *input_service_action_text(input_action_t action);

#ifdef __cplusplus
}
#endif

#endif /* INPUT_SERVICE_H */
