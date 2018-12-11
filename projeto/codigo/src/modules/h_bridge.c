/**
 * @file modules/h_bridge.c
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 30 Nov 2018
 * @brief Module containing H-bridge function helpers and manipulators.
 */

#include <h_bridge.h>

/**
 * @brief Disable the H-bridge, on GPIO38.
 */
int h_bridge_disable() {
  return pputs("/sys/class/gpio/gpio38/value", "0");
}

/**
 * @brief Enable the H-bridge, on GPIO38.
 */
int h_bridge_enable()
{
  return pputs("/sys/class/gpio/gpio38/value", "1");
}