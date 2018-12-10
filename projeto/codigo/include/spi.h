/**
 * @file spi.h
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 30 Nov 2018
 * @brief File containing example of doxygen usage for quick reference.
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

void pabort(const char *s);
int spi_init();
int spi_end();
void transfer(int fd, uint8_t *tx, uint8_t *rx);
void spi_transfer(uint8_t *tx, uint8_t *rx);
void spi_stat();

#endif
