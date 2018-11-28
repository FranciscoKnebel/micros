#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "../include/i2cutil.h"
#include "../include/jhdlcd.h"
#include "../include/galileo2io.h"

#define ROTARY_MIN 0
#define ROTARY_MAX 5

#define MAX_STR 80

#define BL_YELLOW 0x05

int servo(int rotary_volts);
int init_lcd();
int lcd(int fd, char *message, int message_len, int line, int color);
int debug = 0;

int main(){

	int rotary_fd, lcd_fd, button_fd;
	char rotary_data_str[MAX_STR], button_data_str[MAX_STR];
	char message_lcd[MAX_STR];
	double rotary_scale, button_scale;
	int rotary_raw, button_raw, button_read;
	int angle_rad, angle_deg;
	int lcd_color;
	char angle_rad_str[5], angle_deg_str[5];

	if((rotary_fd=open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw",O_RDONLY)) < 0)
	{
		perror("Opening in_voltage0raw:");
		return -1;
	}
	if((button_fd=open("/sys/bus/iio/devices/iio:device0/in_voltage1_raw",O_RDONLY)) < 0)
	{
		perror("Opening in_voltage1raw:");
		return -1;
	}
        
	pgets(rotary_data_str, sizeof rotary_data_str, "/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
	pgets(button_data_str, sizeof button_data_str, "/sys/bus/iio/devices/iio:device0/in_voltage1_scale");
	
	scale = atof(data_str)/1000.0;
	
	lcd_fd = init_lcd();
        
	for(;;)
	{
		lseek(rotary_fd, 0, SEEK_SET);
		read(rotary_fd, rotary_data_str, sizeof rotary_data_str);
		rotary_raw = atoi(rotary_data_str);
		angle_rad = servo(rotary_raw*rotary_scale);
		angle_deg = 180 * angle_rad / M_PI;
		sprintf(angle_rad_str, "%d", angle_rad);
		if(debug) printf("angle_rad_str: %s\n", angle_rad_str);
		sprintf(angle_deg_str, "%d", angle_deg);
		if(debug) printf("angle_deg_str: %s\n", angle_deg_str);
		strcpy(message_lcd, "RAD:");
		strcat(message_lcd, angle_rad_str);
		strcat(message_lcd, " DEG:");
		strcat(message_lcd, angle_deg_str);
		if(debug) printf("message_lcd: %s\n", message_lcd);
		if(angle_rad > -9 && angle_rad < 9) lcd_color = BL_YELLOW;
		else if((angle_rad >= 9 && angle_rad < 11) || (angle_rad > -11 && angle_rad <= -9)) lcd_color = BL_GREEN;
		else lcd_color = BL_RED;
		lcd(lcd_fd, message_lcd, strlen(message_lcd), 1, lcd_color);
		
		lseek(button_fd, 0, SEEK_SET);
		read(button_fd, button_data_str, sizeof button_data_str);
		button_raw = atoi(button_data_str);
		if(button_raw * button_scale < 1)
	        lcd(lcd_fd, message_lcd, strlen(message_lcd), 2);		
	}
        
	close(rotary_fd);
    close(lcd_fd);
    
	return 0;

}
int servo(int rotary_volts){
	int duty_cycle;
	double angle_rad, angle_deg;
	char str[100];
        
	angle_deg = 36*rotary_volts-90;
	angle_rad = angle_deg*M_PI/180.0;

	duty_cycle=angle_rad/M_PI_2*850000+1500000;
                
	pputs("/sys/class/pwm/pwmchip0/device/pwm_period","20000000");
        
	snprintf(str,sizeof str,"%d\n",duty_cycle);
	pputs("/sys/class/pwm/pwmchip0/pwm3/duty_cycle",str);
	pputs("/sys/class/pwm/pwmchip0/pwm3/enable","1");

	return angle_deg;

}
int init_lcd(){

    int fd;
    int i;
    int n;
    char message[MAX_STR] = "Initializing...";

    if((fd=open("/dev/i2c-0",O_WRONLY)) < 0) i2c_error("Opening /dev/i2c-0");
    usleep(30000);	/* Wait for 30 ms after power on */
        
    /* LCD initialization */
    if(ioctl(fd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

    i2c_write_reg(fd,LCD_C0,LCD_FUNCTIONSET | LCD_2LINE);
    usleep(40);  /* Wait for more than 39 us */

    i2c_write_reg(fd,LCD_C0,LCD_DISPLAYSWITCH | LCD_DISPLAYON | 
        LCD_CURSOROFF | LCD_BLINKOFF);
    usleep(40);	/* Wait for more then 39 us */

    i2c_write_reg(fd,LCD_C0,LCD_SCREENCLEAR);
    usleep(1600);	/* Wait for more then 1.53 ms */
        
    i2c_write_reg(fd,LCD_C0,LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);

    /* Backlight initialization */
    if(ioctl(fd,I2C_SLAVE,BL_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
    i2c_write_reg(fd,BL_MODE1,0);
    i2c_write_reg(fd,BL_LEDOUT,BL_RED_GRPPWM | BL_GREEN_GRPPWM | BL_BLUE_GRPPWM);
    i2c_write_reg(fd,BL_MODE2,BL_DMBLNK);
        
    i2c_write_reg(fd,BL_RED,0);
    i2c_write_reg(fd,BL_GREEN,255);
    i2c_write_reg(fd,BL_BLUE,0);

    /* Write string */
    n=strlen(message);

    if(ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
    for(i=0; i < n;i++) {
        i2c_write_reg(fd,LCD_RS,message[i]);
        if(i > 11) usleep(1000000);
    }


	return fd;
}
int lcd(int fd, char *message, int message_len, int line, int color){

    if(ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
    
    if(line == 1){    
        i2c_write_reg(fd,LCD_C0,LCD_DDRAMADDRSET | 0);
        for(i=0; i < message_len; i++) i2c_write_reg(fd, LCD_RS, message[i]);
    }
    else{
        i2c_write_reg(fd,LCD_C0,LCD_DDRAMADDRSET | 0x40);
        for(i=0; i < message_len; i++) i2c_write_reg(fd, LCD_RS, message[i]);
    }

    if(color == BL_RED){
        i2c_write_reg(fd,BL_RED,255);
        i2c_write_reg(fd,BL_GREEN,0;
        i2c_write_reg(fd,BL_BLUE,0));
    }
    else if(color == BL_GREEN){
        i2c_write_reg(fd,BL_RED,0);
        i2c_write_reg(fd,BL_GREEN,255);
        i2c_write_reg(fd,BL_BLUE,0);
    }
    else{
        i2c_write_reg(fd,BL_RED,255);
        i2c_write_reg(fd,BL_GREEN,255);
        i2c_write_reg(fd,BL_BLUE,0);
    }
	return 0;
}
