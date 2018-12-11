/**
 * @file quanser_elbow.c
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 30 Nov 2018
 * @brief File containing example of doxygen usage for quick reference.
 */

#include <quanser_elbow.h>

int main(int argc, char const *argv[]) {
  int duty_cycle = 0;

  if (argc < 2)
  {
    fprintf(stderr, "Usage: ./quanser_pwm <duty_cycle> ");
    exit(1);
  }

  sscanf(argv[1], "%d", &duty_cycle);

  while(1) {
    usleep(TIME_STEP);

    pwm_set_period(PWM_PERIOD);
    pwm_enable();
    pwm_set_duty_cycle(duty_cycle);
    usleep(TIME_STEP);
    pwm_disable();
  }

  return 0;
}