/**
 * Font demo 
 * 
 * Draws a PAC-MAN(tm) Maze using BLT STRING
 *
 * Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 *
 * 
 */

#include <i86.h>
#include <libmindset_gfx.h>

typedef struct _fontdata {
  unsigned char type;
  unsigned char excess;
  unsigned short nominal_width;
  unsigned short nominal_height;
  unsigned short byte_width;
  unsigned short __far *addr;
  unsigned char first;
  unsigned char last;
} FontData;

FontData fd;

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

typedef struct _textparams {
  unsigned short x;
  unsigned short y;
  unsigned short len;
  unsigned short off;
  unsigned short seg;
} TextParams;

TextParams tp;

char* text=" !@#$%&'()";

unsigned short fontbitmap[]=
  {
   0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // 0x20 SPACE
   0x0000,0x0C00,0x1C00,0x0C00,0x0C00,0x0C00,0x0C00,0x3F00, // 0x21 !
   0x0000,0x3E00,0x6300,0x0700,0x1E00,0x3C00,0x7000,0x7F00, // 0x22 "
   0x0000,0x3F00,0x0600,0x0C00,0x1E00,0x0300,0x6300,0x3E00, // 0x23 #
   0x0000,0x0E00,0x1E00,0x3600,0x6600,0x7F00,0x0600,0x0600, // 0x24 $
   0x0000,0x7E00,0x6000,0x7E00,0x0300,0x0300,0x6300,0x3E00, // 0x25 %
   0x0000,0x1E00,0x3000,0x6000,0x7E00,0x6300,0x6300,0x3E00, // 0x26 &
   0x0000,0x7F00,0x6300,0x0600,0x0C00,0x1800,0x1800,0x1800, // 0x27 '
   0x0000,0x3C00,0x6200,0x7200,0x3C00,0x4F00,0x4300,0x3E00, // 0x28 (
   0x0000,0x3E00,0x6300,0x6300,0x3F00,0x0300,0x0600,0x3C00, // 0x29 )
  };

int main(int argc, char* argv[])
{
  mindset_gfx_set_mode(2); // 320x200x4
  mindset_gfx_set_palette(0,16,0,&palette);

  fd.type=0; // Fixed font.
  fd.excess=0; // no excess space.
  fd.nominal_width=8; // nominal width in pixels
  fd.nominal_height=8; // nominal height in pixels
  fd.byte_width=2;   // bitmap for each line takes up 1 word.
  fd.addr=MK_FP(FP_SEG(&fontbitmap),FP_OFF(&fontbitmap));
  fd.first=0x20;
  fd.last=0x29;

  mindset_gfx_set_font_pointer((unsigned char __far *)&fd);

  tp.x=0;
  tp.y=0;
  tp.len=9;
  tp.off=FP_OFF(&text);
  tp.seg=FP_SEG(&text);
  
  mindset_gfx_blt_string(0,1,0,0,12,0,0,(unsigned short *)&tp);

  for (;;) { }
  
}
