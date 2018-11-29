/**
 * Arquivo do papai zanc
 * 
 * Servo na pw1
 * 
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <math.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2cutil.h>
#include <jhdlcd.h>
#include <galileo2io.h>

#include "main.h"

int main() {
  // servo -90 até 90
  // LCD: 
    // primeira linha posição graus e radianos
    // segunda linha referencia do push button
      // Push button: armazenar referência
        // < 10%: backlight amarelo
        // > 10%: backlight vermelho
        // dentro do intervalo: backlight verde

  char buffer[BUFFER_SIZE];

  int potentiometer_scale;
  int potentiometer_fd = potentiometer_init(&potentiometer_scale);

  int button_fd = button_init();
  char button_value;
  int button_pressed;

  int lcd_fd = LCD_init();

  float reference = -1;
  float referenceUpper = -1;
  float referenceLower = -1;

  float value;
  float value_deg;
  float value_rad;
  float voltage;
  for(;;) {
    value = potentiometer_read();
    voltage = value * potentiometer_scale;

    value_deg = voltage / VOLTAGE_PER_DEGREE;
    value_rad = value_deg * M_PI / 180.0;

    servo_write(value, value_deg);

    button_pressed = button_read(button_fd, &button_value);
    if(button_pressed) {
      reference = value;
      referenceUpper = reference + reference / 10;
      referenceLower = reference - reference / 10;
    }

    snprintf(buffer, BUFFER_SIZE, "G:%f R:%f", value_deg, value_rad);
    LCD_write(buffer, 1);

    if(reference >= 0) {
      // printar referencia na segunda linha
      snprintf(buffer, BUFFER_SIZE, "%f", reference);
      LCD_write(buffer, 2);

      if(reference >= 0) {
        // Alterar cor do backlight
        if (value > referenceUpper)
        {
          LCD_setBacklight(lcd_fd, 255, 0, 0);
        }
        else if (value < referenceLower)
        {
          LCD_setBacklight(lcd_fd, 255, 255, 0);
        }
        else
        {
          // Verde
          LCD_setBacklight(lcd_fd, 0, 0, 255);
        }
      }
    }
  }

  // exitAll();
}

int potentiometer_init(int* scale) {
  int fd;
  char buffer[BUFFER_SIZE];
  if ((fd = open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw", O_RDONLY)) < 0)
  {
    perror("Opening in_voltage0raw:");
    return -1;
  }

  pgets(buffer, BUFFER_SIZE, "/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
  (*scale) = atof(buffer)/1000.0;

  return fd;
}

float potentiometer_read(int fd) {
  char buffer[BUFFER_SIZE];
  
  lseek(fd, 0, SEEK_SET);
  read(fd, buffer, BUFFER_SIZE);
  int raw = atoi(buffer);

  return raw;
}

int servo_write(float value, float angle) {
  int fd;
  int i;
  char str[BUFFER_SIZE];

  int duty_cycle = angle / M_PI_2 * 850000 + 1500000;

  pputs("/sys/class/pwm/pwmchip0/device/pwm_period", "20000000");
  snprintf(str, sizeof str, "%d\n", duty_cycle);
  pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", str);

  if ((fd = open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", O_WRONLY)) < 0) {
    perror("Opening duty_cycle:");
    return -1;
  }
  write(fd, "0\n", 2);

  pputs("/sys/class/pwm/pwmchip0/pwm1/enable", "1");
  lseek(fd, 0, SEEK_SET);
  snprintf(str, sizeof str, "%d\n", value);
  write(fd, str, strlen(str));
  printf("SERVO: %d\n", value);
  close(fd);
  pputs("/sys/class/pwm/pwmchip0/pwm1/enable", "0");

  return 0;
}

int button_init() {
  int fd;
  unsigned char c;

  if ((fd = open("/sys/class/gpio/gpio6/value", O_RDONLY)) < 0) {
    perror("Opening gpio6:");
  }

  /* Clear old values */
  read(fd, &c, 1);
  pputs("/sys/class/gpio/gpio6/edge", "rising");

  return fd;
}

int button_read(int fd, char* c) {
  // lseek(fd, 0, SEEK_SET);
  // read(fd, &c, 1);
  strcpy(c, "1");

  return atoi(c);
}

int LCD_init() {
  int fd;
  if ((fd = open("/dev/i2c-0", O_WRONLY)) < 0)
    perror("Opening /dev/i2c-0");
  
  usleep(30000); /* Wait for 30 ms after power on */

  /* LCD initialization */
  if (ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0)
    perror("ioctl on /dev/i2c-0");

  i2c_write_reg(fd, LCD_C0, LCD_FUNCTIONSET | LCD_2LINE);
  usleep(40); /* Wait for more than 39 us */

  i2c_write_reg(fd, LCD_C0, LCD_DISPLAYSWITCH | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
  usleep(40); /* Wait for more then 39 us */

  i2c_write_reg(fd, LCD_C0, LCD_SCREENCLEAR);
  usleep(1600); /* Wait for more then 1.53 ms */

  i2c_write_reg(fd, LCD_C0, LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);

  /* Backlight initialization */
  LCD_setBacklight(fd, 0, 0, 255);
}

void LCD_setBacklight(int fd, int r, int g, int b)
{
  if (ioctl(fd, I2C_SLAVE, BL_ADDR) < 0)
    perror("ioctl on /dev/i2c-0");

  i2c_write_reg(fd, BL_MODE1, 0);
  i2c_write_reg(fd, BL_LEDOUT, BL_RED_GRPPWM | BL_GREEN_GRPPWM | BL_BLUE_GRPPWM);
  i2c_write_reg(fd, BL_MODE2, BL_DMBLNK);

  i2c_write_reg(fd, BL_RED, r);
  i2c_write_reg(fd, BL_GREEN, g);
  i2c_write_reg(fd, BL_BLUE, b);
}

void LCD_write(char* message, int line) {
  if (line == 1) {
    printf("LINHA 1: %s\n", message);
  } else if (line == 2) {
    printf("LINHA 2: %s\n", message);
  }
}

void exitAll(int button_fd) {
  pputs("/sys/class/gpio/gpio6/edge", "none");
  close(button_fd);
}