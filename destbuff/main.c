/**
 * Get Dest buff
 */

#include <libmindset_gfx.h>
#include <stdio.h>

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

int main(int argc, char* argv[])
{
  unsigned short width, height;
  unsigned short __far* buffer;
  
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);

  mindset_get_destination_buffer(&width,&height,buffer);

  printf("Width: %d\n",width);
  printf("Height: %d\n",height);

  return 0;
}
