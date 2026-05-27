#ifndef BOARD_GPIO_H
#define BOARD_GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

  void board_gpio_init(void);
  void board_debug_pin_set(void);
  void board_debug_pin_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_GPIO_H */
