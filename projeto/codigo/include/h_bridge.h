/**
 * @file h_bridge.h
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 30 Nov 2018
 * @brief Header for the H-bridge module, containing H-bridge function helpers and manipulators.
 */

#ifndef H_BRIDGE_H_
#define H_BRIDGE_H_

#include <stdio.h>
#include <galileo2io.h>

/**
 * @brief Disable the H-bridge, on GPIO38.
 */
int h_bridge_disable();

/**
 * @brief Enable the H-bridge, on GPIO38.
 */
int h_bridge_enable();

#endif
