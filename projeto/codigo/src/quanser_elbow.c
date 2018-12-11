/**
 * @file quanser_elbow.c
 * @author Francisco Knebel, Luciano Zancan, Rodrigo Dal Ri
 * @date 30 Nov 2018
 * @brief File containing example of doxygen usage for quick reference.
 */

#include <quanser_elbow.h>

int main(int argc, char const *argv[]) {
  int elbow_id = 0;

  if (argc < 2)
  {
  }
    fprintf(stderr, "Usage: ./quanser_elbow <elbow_id (1 or 2)> ");
    exit(1);

  sscanf(argv[1], "%d", &elbow_id);

  if(elbow_id != 1 && elbow_id != 2) {
    fprintf(stderr, "Invalid elbow id value. Valid ids: 1, 2 ");
    exit(2);
  }

  int status = 0;
  char buffer[1];

  while(1) {
    if (elbow_id == 1) {
      pgets(buffer, 1, "/sys/class/gpio/gpio13/value");
    }  else {
      pgets(buffer, 1, "/sys/class/gpio/gpio14/value");
    }

    sscanf(buffer, "%d", &status);  
    if (status == 1) {
      printf("Done!\n");
      return 0;
    } else {
      printf("Running...\n");
    }
  }
}
