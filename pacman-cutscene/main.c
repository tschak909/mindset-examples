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

#define COMMON_Y 100  // The same Y position for both Blinky and Pac-Man

unsigned short palette[16]={
  0x0000, // Bkg
  0xE03F, // Pacman
  0xC007, // Blinky Bkg
  0xF1FF, // Ghost eyeball
  0x10C0, // Ghost Iris
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

// Global VBI Variables
unsigned short frame_cnt; // Frame counter.
unsigned char frame_done;

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
  
  _asm("popad; leave; retf");
}

/**
 * Blinky Chases Pac-Man
 */
void blinky_chase_pacman(void)
{
  unsigned short bp[40]; // The blitter params
  short pacman_x=48;
  short blinky_x=0;
  short pacman_lx=pacman_x;
  short blinky_lx=blinky_x;
  unsigned short pacman_frame_cnt;
  unsigned short blinky_frame_cnt;
  union REGPACK regs;
    
  while (pacman_x<416)
    {
      frame_done=false;

      pacman_lx=pacman_x;
      blinky_lx=blinky_x;
      
      // Scoot pacman and blinky every other frame
      // Also adjust pac-man's frame every other frame
      if ((frame_cnt&1)==0)
	{
	  // Mouth pac-man
	  if (pacman_frame_cnt>3)
	    pacman_frame_cnt=0;
	  else
	    pacman_frame_cnt++;

	  // Scoot pac-man and Blinky
	  pacman_x+=2;
	  blinky_x+=2;
	}

      // Adjust blinky animation frame every 4 frames
      if ((frame_cnt&3)==0)
	{
	  blinky_frame_cnt=((blinky_frame_cnt==0) ? 1 : 0);
	}

      // Make Blinky creep up a bit more...
      if ((frame_cnt&7)==0)
	{
	  blinky_x++;
	}
      
      // The blitter copy parameter blocks follow.
      // Pac-man's background (black)
      bp[0]=FP_OFF(blank);                             // pointer to image
      bp[1]=FP_SEG(blank);                             // ""   ""
      bp[2]=8;                                         // stride size (# of bytes per row, must be even)
      bp[3]=0;                                         // X source position 
      bp[4]=0;                                         // Y source position
      bp[5]=pacman_lx;                                  // X dest position
      bp[6]=COMMON_Y;                                  // Y dest position
      bp[7]=16;                                        // copy width
      bp[8]=16;                                        // copy height
      bp[9]=0xFFFF;                                    // write mask

      // Pac-man
      bp[10]=FP_OFF(pacman_frames[pacman_frame_cnt]);  // Pointer to image
      bp[11]=FP_SEG(pacman_frames[pacman_frame_cnt]);  // ""    ""
      bp[12]=8;                                        // stride size
      bp[13]=0;                                        // X source position
      bp[14]=0;                                        // Y source position
      bp[15]=pacman_x;                                 // X dest position
      bp[16]=COMMON_Y;                                 // Y dest position
      bp[17]=16;                                       // copy width
      bp[18]=16;                                       // copy height
      bp[19]=0xffff;                                   // write mask

      // Blinky's background (black)
      bp[20]=FP_OFF(blank);                            // pointer to image
      bp[21]=FP_SEG(blank);                            // ""   ""
      bp[22]=8;                                        // stride size (# of bytes per row, must be even)
      bp[23]=0;                                        // X source position 
      bp[24]=0;                                        // Y source position
      bp[25]=blinky_lx;                                 // X dest position
      bp[26]=COMMON_Y;                                 // Y dest position
      bp[27]=16;                                       // copy width
      bp[28]=16;                                       // copy height
      bp[29]=0xFFFF;                                   // write mask

      // Blinky
      bp[30]=FP_OFF(blinky_frames[blinky_frame_cnt]);  // Pointer to image
      bp[31]=FP_SEG(blinky_frames[blinky_frame_cnt]);  // ""    ""
      bp[32]=8;                                        // stride size
      bp[33]=0;                                        // X source position
      bp[34]=0;                                        // Y source position
      bp[35]=blinky_x;                                 // X dest position
      bp[36]=COMMON_Y;                                 // Y dest position
      bp[37]=16;                                       // copy width
      bp[38]=16;                                       // copy height
      bp[39]=0xffff;                                   // write mask

      // Set up the BLT COPY
      regs.h.ah=0x08;       // BLT copy
      regs.h.al=1;          // BLT id
      regs.w.cx=4;          // # of blits to do
      regs.w.dx=0;          // Top/bottom, left/right normal blit
      regs.w.si=0;          // X origin
      regs.w.di=0;          // Y origin
      regs.w.es=FP_SEG(bp); // pointer to blitter params
      regs.w.bx=FP_OFF(bp); // ""      "" 
      intr(0xEF,&regs);

      // We're done, wait for VBI to finish.
      wait_frame();
    }
}

/**
 * Pac-man chases Blinky
 */
void pacman_chase_blinky(void)
{
  unsigned short bp[40]; // The blitter params
  short pacman_x=416;
  short blinky_x=352;
  short pacman_lx=pacman_x;
  short blinky_lx=blinky_x;
  unsigned short pacman_frame_cnt;
  unsigned short blinky_frame_cnt;
  union REGPACK regs;
    
  while (blinky_x>-64)
    {
      frame_done=false;

      pacman_lx=pacman_x;
      blinky_lx=blinky_x;
      
      // Scoot pacman and blinky every other frame
      // Also adjust pac-man's frame every other frame
      if ((frame_cnt&1)==0)
	{
	  // Mouth pac-man
	  if (pacman_frame_cnt>3)
	    pacman_frame_cnt=0;
	  else
	    pacman_frame_cnt++;

	  // Scoot pac-man and Blinky
	  pacman_x-=2;
	  blinky_x-=2;
	}

      // Adjust blinky animation frame every 4 frames
      if ((frame_cnt&3)==0)
	{
	  blinky_frame_cnt=((blinky_frame_cnt==0) ? 1 : 0);
	}

      // Make pac-man creep up a bit more...
      if ((frame_cnt&7)==0)
	{
	  pacman_x--;
	}
      
      // The blitter copy parameter blocks follow.
      // Pac-man's background (black)
      bp[0]=FP_OFF(bigblank);                             // pointer to image
      bp[1]=FP_SEG(bigblank);                             // ""   ""
      bp[2]=16;                                         // stride size (# of bytes per row, must be even)
      bp[3]=0;                                         // X source position 
      bp[4]=0;                                         // Y source position
      bp[5]=pacman_lx;                                  // X dest position
      bp[6]=COMMON_Y-16;                                  // Y dest position
      bp[7]=32;                                        // copy width
      bp[8]=32;                                        // copy height
      bp[9]=0xFFFF;                                    // write mask

      // Pac-man
      bp[10]=FP_OFF(bigpacman_frames[pacman_frame_cnt]);  // Pointer to image
      bp[11]=FP_SEG(bigpacman_frames[pacman_frame_cnt]);  // ""    ""
      bp[12]=16;                                        // stride size
      bp[13]=0;                                        // X source position
      bp[14]=0;                                        // Y source position
      bp[15]=pacman_x;                                 // X dest position
      bp[16]=COMMON_Y-16;                                 // Y dest position
      bp[17]=32;                                       // copy width
      bp[18]=32;                                       // copy height
      bp[19]=0xffff;                                   // write mask

      // Blinky's background (black)
      bp[20]=FP_OFF(blank);                            // pointer to image
      bp[21]=FP_SEG(blank);                            // ""   ""
      bp[22]=8;                                        // stride size (# of bytes per row, must be even)
      bp[23]=0;                                        // X source position 
      bp[24]=0;                                        // Y source position
      bp[25]=blinky_lx;                                 // X dest position
      bp[26]=COMMON_Y;                                 // Y dest position
      bp[27]=16;                                       // copy width
      bp[28]=16;                                       // copy height
      bp[29]=0xFFFF;                                   // write mask

      // Blinky
      bp[30]=FP_OFF(blinkyblue_frames[blinky_frame_cnt]);  // Pointer to image
      bp[31]=FP_SEG(blinkyblue_frames[blinky_frame_cnt]);  // ""    ""
      bp[32]=8;                                        // stride size
      bp[33]=0;                                        // X source position
      bp[34]=0;                                        // Y source position
      bp[35]=blinky_x;                                 // X dest position
      bp[36]=COMMON_Y;                                 // Y dest position
      bp[37]=16;                                       // copy width
      bp[38]=16;                                       // copy height
      bp[39]=0xffff;                                   // write mask

      // Set up the BLT COPY
      regs.h.ah=0x08;       // BLT copy
      regs.h.al=1;          // BLT id
      regs.w.cx=4;          // # of blits to do
      regs.w.dx=0;          // Top/bottom, left/right normal blit
      regs.w.si=0;          // X origin
      regs.w.di=0;          // Y origin
      regs.w.es=FP_SEG(bp); // pointer to blitter params
      regs.w.bx=FP_OFF(bp); // ""      "" 
      intr(0xEF,&regs);

      // We're done, wait for VBI to finish.
      wait_frame();
    }
}

/**
 * Main entrypoint
 */
int main(int argc, char* argv[])
{
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  mindset_gfx_set_display_int_address(&vblank_handler);

  while (!kbhit())
    {
      blinky_chase_pacman();
      pacman_chase_blinky();
    }
  
  mindset_gfx_set_display_int_address(0); // must disable.
  return 0;
}
