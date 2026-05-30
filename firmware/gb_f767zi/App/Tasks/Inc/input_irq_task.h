#ifndef INPUT_IRQ_TASK_H
#define INPUT_IRQ_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

void input_irq_task(void *argument);
void input_irq_task_notify_user_button_from_isr(void);

#ifdef __cplusplus
}
#endif

#endif /* INPUT_IRQ_TASK_H */
