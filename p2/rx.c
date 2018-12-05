/*
  rx.c: Francisco Knebel e Luciano Zancan
  
  Espera interrupção na IO2 o sinal de CLK.
  Envia para a I03 um sinal de ACK.
  Após receber, lê pela IO4 uma string como sinal de data.
  Demonstra o valor dessa string no display LCD.  
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <galileo2io.h>
#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include <i2cutil.h>
#include <jhdlcd.h>

void writeLCD(char* str) {
  int fd;
  int i;
  int n;

  if ((fd = open("/dev/i2c-0", O_WRONLY)) < 0)
    i2c_error("Opening /dev/i2c-0");
  usleep(30000); /* Wait for 30 ms after power on */

  /* LCD initialization */
  if (ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0)
    i2c_error("ioctl on /dev/i2c-0");

  i2c_write_reg(fd, LCD_C0, LCD_FUNCTIONSET | LCD_2LINE);
  usleep(40); /* Wait for more than 39 us */

  i2c_write_reg(fd, LCD_C0, LCD_DISPLAYSWITCH | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
  usleep(40); /* Wait for more then 39 us */

  i2c_write_reg(fd, LCD_C0, LCD_SCREENCLEAR);
  usleep(1600); /* Wait for more then 1.53 ms */

  i2c_write_reg(fd, LCD_C0, LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);

  /* Backlight initialization */
  if (ioctl(fd, I2C_SLAVE, BL_ADDR) < 0)
    i2c_error("ioctl on /dev/i2c-0");
  i2c_write_reg(fd, BL_MODE1, 0);
  i2c_write_reg(fd, BL_LEDOUT, BL_RED_GRPPWM | BL_GREEN_GRPPWM | BL_BLUE_GRPPWM);
  i2c_write_reg(fd, BL_MODE2, BL_DMBLNK);

  i2c_write_reg(fd, BL_RED, 255);
  i2c_write_reg(fd, BL_GREEN, 0);
  i2c_write_reg(fd, BL_BLUE, 0);

  /* Write string */
  n = strlen(str);

  if (ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0)
    i2c_error("ioctl on /dev/i2c-0");
  for (i = 0; i < n; i++)
    i2c_write_reg(fd, LCD_RS, str[i]);

  close(fd);
}

void readData(int fd, char str[]) {
  char c;
  char str[10];
  int i = 0;
  
  printf("Reading data...\n");
  lseek(fd,0,SEEK_SET);
  while(c != '\0') {
   read(fd,&c,1); 
   str[i++] = c;
  }
  printf("Data read.\n");
}

void writeACK(int fd) {
  printf("Writing ACK %c.\n", state);
  lseek(fd,0,SEEK_SET);
  write(fd,&state,sizeof state);
  sleep(1);
  printf("ACK sent.\n");
}

unsigned char awaitCLK(struct pollfd pfd) {
  printf("awaiting CLK...\n");
  unsigned char c;
  pputs("/sys/class/gpio/gpio13/edge","both");
  poll(&pfd,1,-1);
  
  lseek(pfd.fd,0,SEEK_SET);
  read(pfd.fd,&c,1);
  
  pputs("/sys/class/gpio/gpio13/edge","none");
  read(pfd.fd,&c,1);
  printf("CLK received.\n");
  sleep(1);
  return c;
}

int main (int argc, char* argv[]) {
  char* str;
  char c;
  
  ACK_fd=open("/sys/class/gpio/gpio14/value",O_WRONLY);
  data_fd=open("/sys/class/gpio/gpio6/value",O_RDONLY);
  
  // lê clock no IO2, por interrupção - gpio13
  struct pollfd CLK_pfd;
  
  if((CLK_pfd.fd=open("/sys/class/gpio/gpio13/value",O_RDONLY)) < 0)
  {
    perror("Opening gpio13:");
    return -1;
  }
  
  // Clear old values
  read(CLK_pfd.fd,&c,1);
  CLK_pfd.events=POLLPRI;

  for(;;)
  {
    awaitCLK(CLK_pfd);
    
    // escreve ack no IO3 - gpio14
    writeACK(ACK_fd);
    
    // lê data no IO4 - gpio6
    readData(data_fd, str);
    
    // escreve data no LCD
    writeLCD(str);
  }
  
  return 0;  
}
