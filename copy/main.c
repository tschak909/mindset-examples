/**
 * BLT Copy example
 *
 * Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 */

#include <conio.h>
#include <i86.h>
#include <stdlib.h>
#include <string.h>
#include <libmindset_gfx.h>
#include "pacman.h"

unsigned short palette[16]={
  0x0000, // Black
  0x4003, // Yellow
  0xF1FF, // Dark Green
  0x91C0, // Dark Cyan
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

unsigned short* blt_params; // blitter params

int main(int argc, char* argv[])
{
  union REGPACK regs;
  int i;

  blt_params=malloc(2560);
  
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  
  regs.h.ah=0x08;
  regs.h.al=1; // BLT ID 0
  regs.w.cx=128; // One blit ops to do
  regs.w.dx=0; // top/bottom, left/right, normal blit
  regs.w.si=0; // X origin
  regs.w.di=0; // Y origin
  regs.w.es=FP_SEG(blt_params);
  regs.w.bx=FP_OFF(blt_params);

  intr(0xEF,&regs);
  
  while (!kbhit())
    {
      for (i=0;i<128;i++)
	{
	  blt_params[i*10+0]=FP_OFF(pacman);          // Source offset
	  blt_params[i*10+1]=FP_SEG(pacman);          // Source seg
	  blt_params[i*10+2]=8;                // 16 bytes?
	  blt_params[i*10+3]=0;                 // X source offset
	  blt_params[i*10+4]=0;                 // Y source offset
	  blt_params[i*10+5]=rand()&0xFF;                 // X dest   offset
	  blt_params[i*10+6]=rand()&0x7F;                 // Y dest   offset
	  blt_params[i*10+7]=16;                // X width in pixels
	  blt_params[i*10+8]=16;                // Y width in pixels
	  blt_params[i*10+9]=0xFFFF;            // Source mask (everything)
	}
      intr(0xEF,&regs);
    }

  free(blt_params);
  
  return 0;
}
