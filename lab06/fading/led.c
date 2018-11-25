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

        pputs("/sys/class/pwm/pwmchip0/device/pwm_period","1000000");
        
        if((fd=open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",O_WRONLY)) < 0)
        {
                perror("Opening duty_cycle:");
                return -1;
        }
        write(fd,"0\n",2);
        
        pputs("/sys/class/pwm/pwmchip0/pwm1/enable","1");

	int iterations = 4	;
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
