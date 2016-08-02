#include <drivers/keyboard.h>
#include <kernel/io.h>
#include <kernel/terminal.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_CMD_PORT 0x64

static unsigned char keymap[128] = {
  0, /* no character at start */
  27,
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
  '\n', 0, /* left control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
  '`', 0, '\\', /* left shift */
  'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
  0, /* right shift */
  '*', 0, /* left alt */
  ' ', 0, /* caps lock */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* f1-f10 */
  0, /* num lock */
  0, /* scroll lock */
  0,	/* Home key */
  0,	/* Up Arrow */
  0,	/* Page Up */
'-',
  0,	/* Left Arrow */
  0,
  0,	/* Right Arrow */
'+',
  0,	/* 79 - End key*/
  0,	/* Down Arrow */
  0,	/* Page Down */
  0,	/* Insert Key */
  0,	/* Delete Key */
  0,   0,   0,
  0,	/* F11 Key */
  0,	/* F12 Key */
  0,	/* Rest are undefined */
};

static uint8_t read_scancode()
{
  return inb(KEYBOARD_DATA_PORT);
}

void keyboard_handler()
{
  uint8_t scancode = read_scancode();

  if(scancode & 0x80) {
    // key released
  } else {
    terminal_putchar(keymap[scancode]);
  }
}
