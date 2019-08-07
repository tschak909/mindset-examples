/**
 * pac-man cut-scene animation
 *
 * Uses blt copy and vbi interrupt handler.
 *
 * Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 *
 */

#include <i86.h>
#include <libmindset_gfx.h>
#include <conio.h>
#include "bobs.h"

#define true 1
#define false !true

unsigned short palette[16]={
  0x0000, // Bkg
  0xE03F, // Pacman
  0x2018, // Dark Green
  0x30D8, // Dark Cyan
  0x4003, // Dark Red
  0x5063, // Dark Magenta
  0x601B, // Dark Yellow (brown?)
  0x70DB, // Dark Grey
  0x8049, // Light Black
  0x91C0, // Light Blue
  0xA038, // Light Green
  0xB1F8, // Light Cyan
  0xC007, // Light Red
  0xD1C7, // Light Magenta
  0xE03F, // Light Yellow
  0xF1FF  // White
};

unsigned short frame_cnt; // Frame counter.
unsigned short pacman_frame_cnt;
unsigned char frame_done;
unsigned short pacman_x;

/**
 * Wait for frame to complete
 */
void wait_frame(void)
{
  while (frame_done==false) {}
}

void vblank_handler(void)
{
  _asm("pushad");

  frame_cnt++;
  frame_done=true;

  if ((frame_cnt&1)==0)
    {
      if (pacman_x<320)
	pacman_x++;
      else
	pacman_x=0;
      if (pacman_frame_cnt!=4)
	pacman_frame_cnt++;
      else
	pacman_frame_cnt=0;
    }
  
  _asm("popad; leave; retf");
}

/** 
 * Primary runloop
 */
void loop(void)
{
  union REGPACK regs;
  unsigned short bp[20];

  frame_done=false;

  bp[0]=FP_OFF(blank);
  bp[1]=FP_SEG(blank);
  bp[2]=8;
  bp[3]=0;
  bp[4]=0;
  bp[5]=pacman_x;
  bp[6]=100;
  bp[7]=16;
  bp[8]=16;
  bp[9]=0xFFFF;
  bp[10]=FP_OFF(pacman_frames[pacman_frame_cnt]);
  bp[11]=FP_SEG(pacman_frames[pacman_frame_cnt]);
  bp[12]=8;
  bp[13]=0;
  bp[14]=0;
  bp[15]=pacman_x;
  bp[16]=100;
  bp[17]=16;
  bp[18]=16;
  bp[19]=0xFFFF;
  
  regs.h.ah=0x08;
  regs.h.al=1;
  regs.w.cx=2;
  regs.w.dx=0;
  regs.w.si=0;
  regs.w.di=0;
  regs.w.es=FP_SEG(bp);
  regs.w.bx=FP_OFF(bp);

  intr(0xEF,&regs);
  
  wait_frame();
}

int main(int argc, char* argv[])
{
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  mindset_gfx_set_display_int_address(&vblank_handler);

  while (!kbhit())
    {
      loop();
    }
  
  mindset_gfx_set_display_int_address(0); // must disable.
  return 0;
}
