#ifndef PWM_H_
#define PWM_H_

#include <stdio.h>
#include <galileo2io.h>

int pwm_enable();
int pwm_disable();
int pwm_set_period(int period);
int pwm_set_duty_cycle(int duty_cycle);

#endif
