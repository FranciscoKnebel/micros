#define BUFFER_SIZE 80
#define VOLTAGE_PER_DEGREE 0.0277

float potentiometer_read();
int servo_write(float value, float angle);
int button_init();
int button_read(int fd, char *c);
int LCD_init();
void LCD_write(char *message, int line);
void LCD_setBacklight(int fd, int r, int g, int b);
void exitAll(int button_fd);