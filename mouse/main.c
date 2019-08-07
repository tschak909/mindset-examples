/**
 * mouse demo
 *
 * Show and move a cursor using mouse
 *
 * Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 */

#include <conio.h>
#include <i86.h>
#include <libmindset_gfx.h>
#include "cursor.h"

unsigned short x,y,lx,ly;
short dx,dy;

unsigned short palette[16]={
  0x91C0, // Black
  0xF1FF, // Dark Blue
  0x0000, // Dark Green
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

void cursor_plot(unsigned short lx, unsigned short ly, unsigned short x, unsigned short y)
{
  union REGPACK regs;
  
  unsigned short bp[20];

  bp[0]=FP_OFF(cursor_0);
  bp[1]=FP_SEG(cursor_0);
  bp[2]=6;
  bp[3]=0;
  bp[4]=0;
  bp[5]=lx;
  bp[6]=ly;
  bp[7]=12;
  bp[8]=19;
  bp[9]=0xFFFF;
  bp[10]=FP_OFF(cursor);
  bp[11]=FP_SEG(cursor);
  bp[12]=6;
  bp[13]=0;
  bp[14]=0;
  bp[15]=x;
  bp[16]=y;
  bp[17]=12;
  bp[18]=19;
  bp[19]=0xFFFF;

  // Plot BG and cursor
  regs.h.ah=0x08;
  regs.h.al=0;
  regs.w.cx=2;
  regs.w.dx=0;
  regs.w.si=0;
  regs.w.di=0;
  regs.w.es=FP_SEG(bp);
  regs.w.bx=FP_OFF(bp);
  intr(0xEF,&regs);
}
  
int main(int argc, char* argv[])
{
  union REGS r;
  
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  mindset_gfx_set_transfer_mode(0,0); // COPY

  x=y=lx=ly=0;
  
  cursor_plot(0,0,0,0);
  
  while (!kbhit())
    {
      // Read mouse
      r.h.ah=0x1F;
      int86(0xEE,&r,&r);

      dx=r.w.bx;
      dy=r.w.cx;

      if ((dx != 0) && (dy != 0))
	{
	  x += dx;
	  y += dy;

	  if ((x != lx) || (y != ly))
	    {
	      cursor_plot(lx,ly,x,y);
	      lx=x;
	      ly=y;
	    }
	}

    }
  
  return 0;
}
