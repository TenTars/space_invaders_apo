#include <stdbool.h>
#include <stdint.h>

#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "perip_handle.h"


void set_LED_LINE(unsigned char* mem_base ,int value){
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o) = value;
}

void set_RGB_LED_LEFT(unsigned char* mem_base, char red, char green, char blue){

    uint32_t value = (red<<16)|(green<<8)|(blue);
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = value;

}

void set_RGB_LED_RIGHT(unsigned char* mem_base, char red, char green, char blue){

    uint32_t value = (red<<16)|(green<<8)|(blue);
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = value;
}

bool is_RED_KNOB_pressed(unsigned char* mem_base ){

    int val = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    val = (val&0x4000000);
    return ((val == 0) ? false : true);
}

bool is_GREEN_KNOB_pressed(unsigned char* mem_base ){
    int val = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    val = (val&0x2000000);
    return ((val == 0) ? false : true);
}

bool is_BLUE_KNOB_pressed(unsigned char* mem_base ){
        int val = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    val = (val&0x1000000);
    return ((val == 0) ? false : true);
}

char val_of_RED_KNOB(unsigned char* mem_base ){
    int val = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    val = val>>16;
    val = (val & 0xff);
    return (char) val;
}

char val_of_GREEN_KNOB(unsigned char* mem_base ){
    int val = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    val = val>>8;
    val = (val & 0xff);
    return (char) val;
}

char val_of_BLUE_KNOB(unsigned char* mem_base ){
    int val = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    val = (val & 0xff);
    return (char) val;
}

