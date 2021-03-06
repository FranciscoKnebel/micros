/*
  fading.c: Dimmers a LED on Galileo Gen2 IO3 using PWM.
  
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

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <galileo2io.h>

int main(int argc,char * argv[])
{
        int fd;
        int i;
        char str[80];

        pputs("/sys/class/pwm/pwmchip0/device/pwm_period","10000000");
        
        if((fd=open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",O_WRONLY)) < 0)
        {
                perror("Opening duty_cycle:");
                return -1;
        }
        write(fd,"0\n",2);
        
        pputs("/sys/class/pwm/pwmchip0/pwm1/enable","1");

	int iterations = 20;
	int jump = 500000;
        for(i=0;i < jump * iterations;i+=jump)
        {
                lseek(fd,0,SEEK_SET);
                snprintf(str,sizeof str,"%d\n",i);
                write(fd,str,strlen(str));

                printf("%d\n",i);
                sleep(1);
        }
        
        close(fd);

        pputs("/sys/class/pwm/pwmchip0/pwm1/enable","0");        
       
        return 0;
}
