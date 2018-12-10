#include <quanser_controller.h>

int main(int argc, char* argv[]){
    float angular_position = 0;
	float reference_angular_position = 0;
	float count_angle_constant = 1e-3;
	float kp = 0, ki = 0, kd = 0;
    float error = 0;
    int duty_cycle = 0;
    float integral_error = 0, derivative_error = 0, last_error = 0;
	int last_count = 0;

    if(argc < 5){
		fprintf(stderr, "Usage: ./quanser_controller <reference_angular_position> <p_gain> <i_gain> <d_gain> [<count_angle_constant>]");
		exit(1);
	}
    sscanf(argv[1], "%f", &reference_angular_position);
    sscanf(argv[2], "%f", &kp);
    sscanf(argv[3], "%f", &ki);
    sscanf(argv[4], "%f", &kd);

	if(argc > 5){
		sscanf(argv[5], "%f", &count_angle_constant);
	}

	spi_init();
	decoder_init();
	last_count = decoder_read_counter();

	while(1) {
		usleep(TIME_STEP);

		int current_count = decoder_read_counter();
		int delta_count = current_count - last_count;

		angular_position = angular_position + (count_angle_constant * delta_count);

		error = reference_angular_position - angular_position;
		integral_error = integral_error + error * TIME_STEP;
		derivative_error = (error - last_error)/TIME_STEP;

		double relative_speed = kp * error + ki * integral_error + kd * derivative_error;

		pwm_set_period(PWM_PERIOD);
		pwm_enable();
		duty_cycle = (relative_speed + 1) * PWM_PERIOD / 2;
		pwm_set_duty_cycle(duty_cycle);
		pwm_disable();
		printf("New relative speed: %f (%f)\n", relative_speed, angular_position);

		last_count = current_count;
		last_error = error;
	}

	spi_end();
}
