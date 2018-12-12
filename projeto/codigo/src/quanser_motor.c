/**
 * @file quanser_motor.c
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 11 Dez 2018
 * @brief Receive voltage, calculate the duty cicle and set the movement of the
 * elbow.
 */

#include <quanser_motor.h>

int main(int argc, char const *argv[]) {
  int voltage = 0;
  int duty_cycle = 0;

  if (argc < 2) {
    fprintf(stderr, "Usage: ./quanser_motor <voltage> ");
    exit(1);
  }

  sscanf(argv[1], "%d", &voltage);

  if (voltage > MAX_VOLTAGE || voltage < MIN_VOLTAGE) {
    fprintf(stderr,
            "Invalid voltage input value. Max value '%d' - Min value '%d'",
            MAX_VOLTAGE, MIN_VOLTAGE);
    exit(2);
  }

  h_bridge_disable();

  pwm_set_period(PWM_PERIOD);
  pwm_enable();
  duty_cycle = voltage * DUTY_SLOPE + DUTY_LIMIT;
  pwm_set_duty_cycle(duty_cycle);

  h_bridge_enable();
  usleep(TIME_STEP);

  h_bridge_disable();
  pwm_disable();

  return 0;
}
