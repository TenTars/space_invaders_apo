#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "serialize_lock.h"
#include "font_types.h"
#include "perip_handle.h"
#include "model.h"


unsigned short *fb;
bool quit;

uint16_t make_color(uint8_t red, uint8_t green, uint8_t blue){
  unsigned char mask = 0x001f;
  uint16_t num = 0;
  red = red & mask;
  green = green & 0x003f;
  blue = blue & mask;
  num += red;
  num = num << 5;
  num += green;
  num = num << 6;
  num += blue;
  return num;
}
 
void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}
 
void draw_char(int x, int y, font_descriptor_t* fdes, char ch) {
}
 
int char_width(font_descriptor_t* fdes, int ch) {
  int width = 0;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    ch -= fdes->firstchar;
    if (!fdes->width) {
      width = fdes->maxwidth;
    } else {
      width = fdes->width[ch];
    }
  }
  return width;
}
 
int main(int argc, char *argv[]){
  unsigned char *mem_base;
  unsigned char *parlcd_mem_base;
  int ptr;
  fb  = (unsigned short *)malloc(320*480*sizeof(unsigned short));
 
  /*
   * Setup memory mapping which provides access to the peripheral
   * registers region of RGB LEDs, knobs and line of yellow LEDs.
   */
  mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
 
  /* If mapping fails exit with error code */
  if (mem_base == NULL)
    exit(1);
 
 
  struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};

  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
 
  if (parlcd_mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);

  

    printf("Start of game loop\n");
  int count = 0;
  char game_state = 0;
  while (!quit){
    set_RGB_LED_LEFT(mem_base, count,count,1-count/2);
    set_RGB_LED_RIGHT(mem_base, 1-count, count, count);
    bool r = is_RED_KNOB_pressed(mem_base);
    bool g = is_GREEN_KNOB_pressed(mem_base);
    bool b = is_BLUE_KNOB_pressed(mem_base);
    printf("red: %d, green: %d, blue: %d\n", r,g,b);
    if(r){game_state = 0;}
    if(g){game_state = 1;}
    if(b){game_state = 2;}
    
    int j = val_of_BLUE_KNOB(mem_base);

    count++;
    for (int k = 0; k < 480*320; k++)
    {
      if(game_state == 0) fb[k] = k/10;
      if(game_state == 1) fb[k] =k/5;
      if(game_state == 2) fb[k] =(j-j/2);
       
    }
    

    for (int i = 0; i < 480*320; i++)
    {
      parlcd_write_data(parlcd_mem_base, fb[i]);
    }
    

    //update();
    //draw();
    //printf("LOOP\n");
    clock_nanosleep(CLOCK_MONOTONIC,0,&loop_delay, NULL);
    
  }
 
  printf("Game loop ended\n");
}