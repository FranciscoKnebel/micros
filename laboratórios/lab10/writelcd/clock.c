/*
  writelcd.c: Write a string in a I2C LCD with RGB backlight
  
  Copyright (c) 2016 Walter Fetter Lages <w.fetter@ieee.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include <i2cutil.h>
#include <jhdlcd.h>

static void i2c_error(const char *msg)
{
    perror(msg);
    exit(-errno);
}

int main(int argc,char *argv[])
{
        int fd;
        int i;
        int n;
        
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
        i2c_write_reg(fd,BL_LEDOUT,BL_RED_GRPPWM | BL_GREEN_GRPPWM | 
                BL_BLUE_GRPPWM);
        i2c_write_reg(fd,BL_MODE2,BL_DMBLNK);
        
	setBackground(0,255,0);

        if(ioctl(fd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

	i2c_write_reg(fd,LCD_C0,LCD_DDRAMADDRSET | 0x40);
	int l2_n = strlen(argv[1]);
	for(i=0;i < l2n_n;i++) i2c_write_reg(fd,LCD_RS,argv[1][i]);

                
	/* Write string */
        //n=strlen(argv[1]);
	//for(i=0;i < n;i++) i2c_write_reg(fd,LCD_RS,argv[1][i]);
	
	
        close(fd);

	return 0;
}

void setBackground(int r, int g, int b) {
    i2c_write_reg(fd,BL_RED,r);
    i2c_write_reg(fd,BL_GREEN,g);
    i2c_write_reg(fd,BL_BLUE,b);
}
