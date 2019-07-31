/**
 * BLT COPY WORD example
 *
 * Draws a bunch of filled boxes
 */

#include <libmindset_gfx.h>
#include <stdlib.h>
#include <conio.h>

#define true 1
#define false !true

// see the comments on mindset_gfx_set_palette() for
// information on how the palette words are defined.

unsigned short palette[16]={
  0x0000, // Black
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

CopyWordParams cw[128];

int main(int argc, char* argv[])
{
  unsigned char i; // index.
  unsigned char quit=false;
  
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);

  while (quit==false)
    {      
      for (i=0;i<128;i++)
	{
	  cw[i].pattern=rand();
	  cw[i].x=rand()&0xff;
	  cw[i].y=rand()&0xff>>1;
	  cw[i].width=rand()&0xff;
	  cw[i].height=rand()&0xff>>1;
	}

      mindset_gfx_blt_copy_word(0,128,0,0,&cw);
      if (kbhit())
	quit=true;
    }
  
  return 0;
}
