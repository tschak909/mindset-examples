/**
 * Polyline example
 *
 * Draws a bunch of lines with fill
 */

#include <libmindset_gfx.h>
#include <stdlib.h>

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

PolyLineParams pl[128];

int main(int argc, char* argv[])
{
  unsigned char c; // Color.
  unsigned char i; // index.
  
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);

  for (;;)
    {

      c=rand()&0xFF;
      
      for (i=0;i<128;i++)
	{
	  pl[i].x=rand()&0xff;
	  pl[i].y=rand()&0xff>>1;
	}

      mindset_gfx_blt_polyline(0,128,c,1,0,0,&pl);
      
    }
}
