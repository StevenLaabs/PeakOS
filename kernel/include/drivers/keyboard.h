#ifndef _KEYBOARD_DRIVER_H
#define _KEYBOARD_DRIVER_H

/*
 * Initializes the keyboard driver by unmasking the keyboard IRQ
 */
void keyboard_init();

/*
 * Runs the keyboard handler when an interrupt has been found.
 * Processes the scancode and sets the key press state and gets the
 * corresponding ascii value from the key map which is printed to the
 * terminal
 */
void keyboard_handler();

#endif
