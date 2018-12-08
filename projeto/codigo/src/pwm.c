#include <pwm.h>

int pwm_enable(){
	return pputs("/sys/class/pwm/pwmchip0/pwm1/enable","1");
}

int pwm_disable(){
	return pputs("/sys/class/pwm/pwmchip0/pwm1/enable","0");
}

int pwm_set_period(int period){
	return pputs("/sys/class/pwm/pwmchip0/device/pwm_period", period_str);
}

int pwm_set_duty_cycle(int duty_cycle){
	return pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", duty_cycle_str);
}
