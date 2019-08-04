/**
 * BLT Copy example
 *
 * Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 */

#include <conio.h>
#include <i86.h>
#include <libmindset_gfx.h>
#include "pacman.h"

unsigned short __far* pp;

unsigned short palette[16]={
  0xF1FF, // Black
  0x10C0, // Dark Blue
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

unsigned short blt_params[10];

int main(int argc, char* argv[])
{
  union REGS regs;
  struct SREGS sregs;
  
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);

  segread(&sregs);
  
  pp=&pacman[0];
  
  blt_params[0]=FP_OFF(&pacman[0]);          // Source offset
  blt_params[1]=FP_SEG(&pacman[0]);          // Source seg
  blt_params[2]=16;                // 16 bytes?
  blt_params[3]=0;                 // X source offset
  blt_params[4]=0;                 // Y source offset
  blt_params[5]=128;                 // X dest   offset
  blt_params[6]=128;                 // Y dest   offset
  blt_params[7]=16;                // X width in pixels
  blt_params[7]=16;                // Y width in pixels
  blt_params[7]=0xFFFF;            // Source mask (everything)

  regs.h.ah=0x08;
  regs.h.al=0; // BLT ID 0
  regs.w.cx=1; // One blit op to do
  regs.w.dx=0; // top/bottom, left/right, normal blit
  regs.w.si=0; // X origin
  regs.w.di=0; // Y origin
  sregs.es=FP_SEG(&blt_params);
  regs.w.bx=FP_OFF(&blt_params);

  int86x(0xEF,&regs,&regs,&sregs);
  
  while (!kbhit())
    {
      
    }

  return 0;
}
