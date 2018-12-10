/**
 * @file modules/pwm.c
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 30 Nov 2018
 * @brief File containing example of doxygen usage for quick reference.
 */

#include <pwm.h>
char str[100];

/**
 * @brief Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
int pwm_enable() { return pputs("/sys/class/pwm/pwmchip0/pwm1/enable", "1"); }

/**
 * @brief Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
int pwm_disable() { return pputs("/sys/class/pwm/pwmchip0/pwm1/enable", "0"); }

/**
 * @brief Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
int pwm_set_period(int period) {
  sprintf(str, "%d", (int)period);
  return pputs("/sys/class/pwm/pwmchip0/device/pwm_period", str);
}

/**
 * @brief Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
int pwm_set_duty_cycle(int duty_cycle) {
  sprintf(str, "%d", duty_cycle);
  return pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", str);
}
