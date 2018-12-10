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

int main(int argc, char* argv[]);

#endif
