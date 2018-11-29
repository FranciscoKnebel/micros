
/* Luciano Zancan e Vinícius Fratin */

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <galileo2io.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include <i2cutil.h>
#include <jhdlcd.h>

static void i2c_error(const char *msg)
{
    perror(msg);
    exit(-errno);
}

int main(int argc,char * argv[])
{
	double voltage_per_degree = 0.0277;
	
	int fd;
        char data_str[80];
        double scale;
        int raw;

        if((fd=open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw",O_RDONLY)) < 0)
        {
                perror("Opening in_voltage0raw:");
                return -1;
        }
        
        pgets(data_str,sizeof data_str,"/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
        scale=atof(data_str)/1000.0;
        
	int fd_lcd;
	int n;
	
	if((fd_lcd=open("/dev/i2c-0",O_WRONLY)) < 0) i2c_error("Opening /dev/i2c-0");
        usleep(30000);	/* Wait for 30 ms after power on */
        
        /* LCD initialization */
        if(ioctl(fd_lcd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

        i2c_write_reg(fd_lcd,LCD_C0,LCD_FUNCTIONSET | LCD_2LINE);
        usleep(40);  /* Wait for more than 39 us */

        i2c_write_reg(fd_lcd,LCD_C0,LCD_DISPLAYSWITCH | LCD_DISPLAYON | 
                LCD_CURSOROFF | LCD_BLINKOFF);
        usleep(40);	/* Wait for more then 39 us */

        
        
        i2c_write_reg(fd_lcd,LCD_C0,LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);

        /* Backlight initialization */
        if(ioctl(fd_lcd,I2C_SLAVE,BL_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
        i2c_write_reg(fd_lcd,BL_MODE1,0);
        i2c_write_reg(fd_lcd,BL_LEDOUT,BL_RED_GRPPWM | BL_GREEN_GRPPWM | 
                BL_BLUE_GRPPWM);
        i2c_write_reg(fd_lcd,BL_MODE2,BL_DMBLNK);
        
        i2c_write_reg(fd_lcd,BL_RED,255);
        i2c_write_reg(fd_lcd,BL_GREEN,0);
        i2c_write_reg(fd_lcd,BL_BLUE,0);
	
        for(;;)
        {
		double voltage_array[100];
		double std_dev = 0;
		
		double acc_voltage = 0;
		int i;
		for(i = 0; i < 100; i++)
		{
		  lseek(fd,0,SEEK_SET);
		  read(fd,data_str,sizeof data_str);
		  raw=atoi(data_str);
		  
		  double voltage = raw*scale;
		  acc_voltage += voltage;
		  voltage_array[i] = voltage;
		}
		
		double mean_voltage = acc_voltage/100;
		
		for(i = 0; i < 100; i++)
		{
		    std_dev += pow((voltage_array[i] - mean_voltage), 2);
		}
		
		std_dev /= 100;
		std_dev = sqrt(std_dev);
		
		double degrees = mean_voltage/voltage_per_degree - 90;
		
		int duty_cycle;
		char str[100];
		
		double angle=degrees * M_PI/180.0;
		
		duty_cycle=angle/M_PI_2*850000+1500000;
			
		pputs("/sys/class/pwm/pwmchip0/device/pwm_period","20000000");
		
		snprintf(str,sizeof str,"%d\n",duty_cycle);
		pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",str);
		pputs("/sys/class/pwm/pwmchip0/pwm1/enable","1");2
		
		i2c_write_reg(fd_lcd,LCD_C0,LCD_SCREENCLEAR);
		usleep(1600);	/* Wait for more then 1.53 ms */
	
		char lcd_str[256];
		sprintf(lcd_str, "m=%.2lf d=%.2lf", mean_voltage, std_dev);
		n=strlen(lcd_str);
		
		i2c_write_reg(fd_lcd, LCD_C0, LCD_DDRAMADDRSET | 0);
		if(ioctl(fd_lcd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
		for(i=0;i < n;i++) i2c_write_reg(fd_lcd,LCD_RS,lcd_str[i]);
		
		char angle_str[256];
		sprintf(angle_str, "g=%.2lf r=%.2lf", degrees, angle);
		n=strlen(angle_str);

		i2c_write_reg(fd_lcd, LCD_C0, LCD_DDRAMADDRSET | 0x40);
		if(ioctl(fd_lcd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
		for(i=0;i < n;i++) i2c_write_reg(fd_lcd,LCD_RS,angle_str[i]);
        }
        
        close(fd);
	close(fd_lcd);

        return 0;
}
