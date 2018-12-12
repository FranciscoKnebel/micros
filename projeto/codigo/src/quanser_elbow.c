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
 * @brief Detect end of trajectory of elbow 1 and 2 or shoulder 1 and 2
 */

#include <quanser_elbow.h>

int main(int argc, char const *argv[]) {
  int elbow1 = 0;
  int elbow2 = 0;
  int shoulder1 = 0;
  int shoulder2 = 0;

  while (1) {
    // gpio13 = elbow 1
    elbow1 = detect_endoftrajectory_elbow(1);
    
    // gpio14 = elbow 2
    elbow2 = detect_endoftrajectory_elbow(2);
    
    // gpio9 = shoulder 1
    shoulder1 = detect_endoftrajectory_shoulder(1);
    
    // gpio1 = shoulder 2
    shoulder2 = detect_endoftrajectory_shoulder(2);
  
    printf("e1: %d - e2: %d - s1: %d - s2: %d\n", elbow1, elbow2, shoulder1,
           shoulder2);
  }
}
