#include <drivers/keyboard.h>
#include <kernel/terminal.h>
#include <hal.h>

#define KEYBOARD_IRQ 1

// Keyboard ports for reading and writing data
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_CMD_PORT 0x64

// Scancodes for left and right shift keys
#define LEFT_SHIFT_CODE 0x2A
#define RIGHT_SHIFT_CODE 0x36

// Corresponding ascii codes for when the shift key is unpressed
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

// Corresponding ascii codes for when the shift key is held down
static unsigned char keymap_shift[128] = {
  0, /* no character at start */
  27,
  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
  '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
  '\n', 0, /* left control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"',
  '~', 0, '\\', /* left shift */
  'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
  0, /* right shift */
  '*', 0, /* left alt */
  ' ', 0, /* caps lock */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* f1-f10 */
  0, /* num lock */
  0, /* scroll lock */
  0,	/* Home key */
  0,	/* Up Arrow */
  0,	/* Page Up */
'_',
  0,	/* Left Arrow */
  0,
  0,	/* Right Arrow */
'=',
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

// Pressed state of each key (0: unpressed 1: pressed)
static unsigned char keyactive[128] = { 0 };

// Returns the scancode sent to the keyboard date port and returns its value
static uint8_t read_scancode()
{
  return inb(KEYBOARD_DATA_PORT);
}

void keyboard_init()
{
	irq_install(KEYBOARD_IRQ, keyboard_handler);
}

void keyboard_handler()
{
  uint8_t scancode = read_scancode();

  if(scancode & 0x80) {
    // key released
	keyactive[scancode & 0x7F] = 0;
  } else {
	keyactive[scancode] = 1;
	if(!keymap[scancode]) {
  		interrupt_complete(KEYBOARD_IRQ);
		return;
	}
	
	if(keyactive[LEFT_SHIFT_CODE] || keyactive[RIGHT_SHIFT_CODE])
		terminal_putchar(keymap_shift[scancode]);
	else
    	terminal_putchar(keymap[scancode]);
  }

  interrupt_complete(KEYBOARD_IRQ);
}
