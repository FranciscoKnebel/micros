/*
  tx.c: Francisco Knebel e Luciano Zancan
  
  Envia para a IO7 um sinal de CLK.
  Espera interrupção na IO6 o sinal de ACK.
  Após receber, envia para o IO5 uma string argv[1], como sinal de data.
*/
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <galileo2io.h>

void writeData(int fd, char* str, int str_size) {
  printf("Writing data \"%s\".\n", str);
  lseek(fd,0,SEEK_SET);
  write(fd,str,str_size);
  write(fd,'\0',1);
  printf("Data sent.\n");
}

unsigned char awaitACK(struct pollfd pfd) {
  printf("Awaiting ACK...\n");
  unsigned char c;
  pputs("/sys/class/gpio/gpio1/edge","both");
  poll(&pfd,1,-1);
  
  lseek(pfd.fd,0,SEEK_SET);
  read(pfd.fd,&c,1);
  
  pputs("/sys/class/gpio/gpio1/edge","none");
  read(pfd.fd,&c,1);
  printf("ACK received.\n");  
  return c;
}

void writeCLK(int fd, char state) {
  printf("Writing CLK %c.\n", state);
  lseek(fd,0,SEEK_SET);
  write(fd,&state,sizeof state);
  sleep(1);
  printf("CLK sent.\n");
}

int main (int argc, char* argv[]) {
  char* str;
  char c;
  
  if(argc != 2) {
    printf("\tUsage:\t%s <string>\n",argv[0]);
    return -1;
  }
  
  str = argv[1];
  int str_size = strlen(str);
  
  char CLK_state = '0';
  int CLK_fd, data_fd;	
  struct pollfd ACK_pfd;
  
  CLK_fd=open("/sys/class/gpio/gpio38/value",O_WRONLY);
  data_fd=open("/sys/class/gpio/gpio0/value",O_WRONLY);

  if((ACK_pfd.fd=open("/sys/class/gpio/gpio1/value",O_RDONLY)) < 0)
  {
    perror("Opening gpio1:");
    return -1;
  }
  
  // Clear old values
  read(ACK_pfd.fd,&c,1);
  ACK_pfd.events=POLLPRI;
  
  for(;;)
  {	
    // escreve CLK no IO7 - gpio38
    writeCLK(CLK_fd, CLK_state);
    CLK_state ^= '0'^'1';
        
    // recebe ACK do IO6, por interrupção - gpio1
    awaitACK(ACK_pfd);
    
    // escreve data no IO5 - gpio0
    writeData(data_fd, str, str_size);
  }
}