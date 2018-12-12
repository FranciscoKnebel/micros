// Quanser Shield
// Copyright (C) 2018 Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/**
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @file quanser_elbow.c
 * @date 11 Dez 2018
 * @brief Detect end of trajectory of elbow 1 or 2.
 */

#include <quanser_elbow.h>

int main(int argc, char const *argv[]) {
  int elbow1 = 0;
  int elbow2 = 0;
  int shoulder1 = 0;
  int shoulder2 = 0;
  char buffer[1];

  while (1) {
    // gpio13 = elbow 1
    pgets(buffer, 1, "/sys/class/gpio/gpio13/value");
    sscanf(buffer, "%d", &elbow1);

    // gpio14 = elbow 2
    pgets(buffer, 1, "/sys/class/gpio/gpio14/value");
    sscanf(buffer, "%d", &elbow2);

    // gpio9 = shoulder 1
    pgets(buffer, 1, "/sys/class/gpio/gpio9/value");
    sscanf(buffer, "%d", &shoulder1);

    // gpio1 = shoulder 2
    pgets(buffer, 1, "/sys/class/gpio/gpio1/value");
    sscanf(buffer, "%d", &shoulder2);

    printf("e1: %d - e2: %d - s1: %d - s2: %d\n", elbow1, elbow2, shoulder1,
           shoulder2);
  }
}
