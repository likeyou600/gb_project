#include "Input/input_service.h"

#include "app_config.h"
#include "Log/log_service.h"
#include "main.h"

static osMessageQueueId_t inputEventQueueHandle;

void input_service_init(void)
{
#if APP_INPUT_ENABLE
  inputEventQueueHandle = osMessageQueueNew(APP_INPUT_EVENT_QUEUE_DEPTH, sizeof(input_event_t), NULL);
  LOG_INFO("RTOS-input_service", "input_service_init called");
#endif
}

osStatus_t input_service_post_event(input_key_t key, input_action_t action)
{
#if APP_INPUT_ENABLE
  input_event_t event = {
    .key = key,
    .action = action,
    .timestamp = HAL_GetTick(),
  };

  if (inputEventQueueHandle == NULL)
  {
    return osErrorResource;
  }

  return osMessageQueuePut(inputEventQueueHandle, &event, 0U, 0U);
#else
  (void)key;
  (void)action;
  return osErrorResource;
#endif
}

osStatus_t input_service_get_event(input_event_t *event, uint32_t timeout)
{
#if APP_INPUT_ENABLE
  if ((inputEventQueueHandle == NULL) || (event == NULL))
  {
    return osErrorParameter;
  }

  return osMessageQueueGet(inputEventQueueHandle, event, NULL, timeout);
#else
  (void)event;
  (void)timeout;
  return osErrorResource;
#endif
}

const char *input_service_key_text(input_key_t key)
{
  switch (key)
  {
  case INPUT_KEY_TEST:
    return "TEST";
  case INPUT_KEY_UP:
    return "UP";
  case INPUT_KEY_DOWN:
    return "DOWN";
  case INPUT_KEY_LEFT:
    return "LEFT";
  case INPUT_KEY_RIGHT:
    return "RIGHT";
  case INPUT_KEY_OK:
    return "OK";
  default:
    return "UNKNOWN";
  }
}

const char *input_service_action_text(input_action_t action)
{
  switch (action)
  {
  case INPUT_ACTION_PRESS:
    return "PRESS";
  case INPUT_ACTION_RELEASE:
    return "RELEASE";
  case INPUT_ACTION_SHORT:
    return "SHORT";
  case INPUT_ACTION_LONG:
    return "LONG";
  default:
    return "UNKNOWN";
  }
}
