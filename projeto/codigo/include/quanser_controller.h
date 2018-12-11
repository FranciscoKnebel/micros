/**
 * @file quanser_controller.h
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 30 Nov 2018
 * @brief File containing example of doxygen usage for quick reference.
 */

#ifndef QUANSER_CONTROLLER_H
#define QUANSER_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <decoder.h>
#include <spi.h>
#include <pwm.h>

#define TIME_STEP 10000
#define PWM_PERIOD 1500000

#define MAX_VOLTAGE 27
#define MIN_VOLTAGE (-27)

#define DUTY_SLOPE PWM_PERIOD / (MAX_VOLTAGE - MIN_VOLTAGE)
#define DUTY_LIMIT DUTY_SLOPE *MAX_VOLTAGE

int main(int argc, char* argv[]);

#endif
