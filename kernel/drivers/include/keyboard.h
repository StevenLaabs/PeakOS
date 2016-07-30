#ifndef _KEYBOARD_DRIVER_H
#define _KEYBOARD_DRIVER_H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_CMD_PORT 0x64

void keyboard_handler();

#endif
