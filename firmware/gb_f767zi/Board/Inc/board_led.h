#ifndef BOARD_LED_H
#define BOARD_LED_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef enum
  {
    BOARD_LED_GREEN = 0,
    BOARD_LED_BLUE,
    BOARD_LED_RED
  } board_led_t;

  void board_led_on(board_led_t led);
  void board_led_off(board_led_t led);
  void board_led_toggle(board_led_t led);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_LED_H */
