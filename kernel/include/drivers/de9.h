#include <stdint.h>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

void de9_init(uint16_t com);
void de9_set_baud(uint16_t com, uint16_t divisor);
void de9_config_line(uint16_t com);
void de9_config_buffer(uint16_t com);
void de9_config_modem(uint16_t com);

char read_serial(uint16_t com);
void write_serial(uint16_t com, char c);
