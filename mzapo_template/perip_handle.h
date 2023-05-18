#ifndef PERIP_HANDLE
#define PERIP_HANDLE

#include <stdbool.h>
#include <stdint.h>

#include "mzapo_phys.h"
#include "mzapo_regs.h"

void set_LED_LINE(unsigned char* mem_base, int value);

void set_RGB_LED_LEFT(unsigned char* mem_base, char red, char green, char blue);

void set_RGB_LED_RIGHT(unsigned char* mem_base, char red, char green, char blue);

bool is_RED_KNOB_pressed(unsigned char* mem_base);

bool is_GREEN_KNOB_pressed(unsigned char* mem_base);

bool is_BLUE_KNOB_pressed(unsigned char* mem_base);

char val_of_RED_KNOB(unsigned char* mem_base);

char val_of_GREEN_KNOB(unsigned char* mem_base);

char val_of_BLUE_KNOB(unsigned char* mem_base);

#endif