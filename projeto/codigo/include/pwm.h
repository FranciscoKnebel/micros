/**
 * @file pwm.h
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 30 Nov 2018
 * @brief File containing example of doxygen usage for quick reference.
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdio.h>
#include <galileo2io.h>

int pwm_enable();
int pwm_disable();
int pwm_set_period(int period);
int pwm_set_duty_cycle(int pwm_set_duty_cycle);

#endif
