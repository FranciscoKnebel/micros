/**
 * @file modules/decoder.c
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 11 Dez 2018
 * @brief Module for decoder functions and helpers.
 */

#include <decoder.h>

/**
 * @brief Initializes the decoder.
 */
void decoder_init() {
  char wr_data[2] = {WRITE_MDR0, QUADRX1};
  char rd_data[2];
  spi_transfer((uint8_t *)wr_data, (uint8_t *)rd_data);
}

/**
 * @brief Read decoder counter.
 */
int decoder_read_counter() {
  char wr_data[1] = {READ_CNTR};
  int rd_data;
  spi_transfer((uint8_t *)wr_data, (uint8_t *)&rd_data);

  return rd_data;
}

/**
 * @brief Clear the decoder counter.
 */
void decoder_clear_counter() {
  char wr_data[1] = {CLR_CNTR};
  char rd_data[1];
  spi_transfer((uint8_t *)wr_data, (uint8_t *)rd_data);
}
