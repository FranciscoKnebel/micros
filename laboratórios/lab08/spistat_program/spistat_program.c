/*
  spistat.c: Shows the status of the SPI controller.
  
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
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

int main(int argc,char *argv[])
{
	int fd;
	uint8_t mode=3, bpw=8;
	uint8_t lsb;
	uint32_t rate = 500000;
	
	unsigned char send[2], receive[2];
	send[0] = 'a';
	send[1] = 'b';
	struct spi_ioc_transfer transfer = {
	  .tx_buf = (unsigned long) send,
	  .rx_buf = (unsigned long) receive,
	  .len = 2,
	};
	
	if(argc != 2)
	{
		printf("Usage: spistat device\n");
		return -1;
	}
	if((fd=open(argv[1],O_RDWR))==-1)
	{
		perror("Can't open device");
		return -1;
	}
	
	ioctl(fd,SPI_IOC_WR_MODE,&mode);
	ioctl(fd,SPI_IOC_RD_MODE,&mode);
	
	ioctl(fd,SPI_IOC_WR_LSB_FIRST,&lsb);
	ioctl(fd,SPI_IOC_RD_LSB_FIRST,&lsb);
	
	ioctl(fd,SPI_IOC_WR_BITS_PER_WORD,&bpw);
	ioctl(fd,SPI_IOC_RD_BITS_PER_WORD,&bpw);
	
	ioctl(fd,SPI_IOC_WR_MAX_SPEED_HZ,&rate);
	ioctl(fd,SPI_IOC_RD_MAX_SPEED_HZ,&rate);
	
	
	printf("spi mode: 0x%x\n", mode);
	printf("bits per word: %d\n", bpw);
	printf("max speed: %d Hz (%d KHz)\n", rate, rate/1000);
	
	if (ioctl(fd, SPI_IOC_MESSAGE(1), &transfer)<0){
	  perror("Failed to send SPI message");
	  return -1;
	}
	printf("send value: %c %c\n",send[0], send[1]);
	printf("return value: %c %c\n",receive[0], receive[1]);
	
	close(fd);
	return 0;
}
