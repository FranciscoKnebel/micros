/**
 * @file modules/decoder.c
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 30 Nov 2018
 * @brief File containing example of doxygen usage for quick reference.
 */

#include <decoder.h>

/**
 * @brief Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
void decoder_init() {
  char wr_data[2] = {WRITE_MDR0, QUADRX1};
  char rd_data[2];
  spi_transfer((uint8_t *)wr_data, (uint8_t *)rd_data);
}

/**
 * @brief Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
int decoder_read_counter() {
  char wr_data[1] = {READ_CNTR};
  int rd_data;
  spi_transfer((uint8_t *)wr_data, (uint8_t *)&rd_data);

  return rd_data;
}

/**
 * @brief Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
void decoder_clear_counter() {
  char wr_data[1] = {CLR_CNTR};
  char rd_data[1];
  spi_transfer((uint8_t *)wr_data, (uint8_t *)rd_data);
}
