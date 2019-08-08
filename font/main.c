/**
 * Font demo 
 * 
 * Draws a PAC-MAN(tm) Maze using BLT STRING
 *
 * Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 *
 * 
 */

#include <conio.h>
#include <i86.h>
#include <libmindset_gfx.h>

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

unsigned char color_table[16]=
  {
    0x00,
    0x11,
    0x22,
    0x33,
    0x44,
    0x55,
    0x66,
    0x77,
    0x88,
    0x99,
    0xAA,
    0xBB,
    0xCC,
    0xDD,
    0xEE,
    0xFF
  };

unsigned char fontdata[2048]=
  {
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,   
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F,
    0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88
  };

const char* text="0123456789";

int main(int argc, char* argv[])
{
  union REGPACK regs;
  unsigned short fontpointer[7];
  unsigned short textpointer[5];
  
  mindset_gfx_set_mode(2); // 320x200x4
  mindset_gfx_set_palette(0,16,0,&palette);

  fontpointer[0]=0x0000; // fixed font, no excess interspacing
  fontpointer[1]=0x0008; // 8px wide
  fontpointer[2]=0x0008; // 8px high
  fontpointer[3]=0x0100; // stride is 256 ytes long.
  fontpointer[4]=FP_OFF(fontdata);
  fontpointer[5]=FP_SEG(fontdata);
  fontpointer[6]=0x7F00; // First and last 
  
  // Set font pointer.
  regs.h.ah=0x1f;
  regs.w.es=FP_SEG(fontpointer);
  regs.w.bx=FP_OFF(fontpointer);
  intr(0xEF,&regs);

  // Set up text parameter block.
  textpointer[0]=0x0040; // X
  textpointer[1]=0x0040; // Y
  textpointer[2]=10;     // Len
  textpointer[3]=FP_OFF(text);
  textpointer[4]=FP_SEG(text);

  // Set up text string call
  regs.h.ah=0x21;       // BLT STRING
  regs.h.al=1;          // BLT ID 1
  regs.h.ch=1;          // # of text pointer structs
  regs.h.cl=0;          // # of text chars to ignore at beginning of string (none)
  regs.h.dh=0;          // draw left to right
  regs.h.dl=0xFF;       // color
  regs.w.si=0;          // X origin
  regs.w.di=0;          // Y origin
  regs.w.es=FP_SEG(textpointer); // Text pointer (seg)
  regs.w.bx=FP_OFF(textpointer); // Text pointer (off)
  
  while (!kbhit())
    {
      textpointer[0]=rand()&0xFF;
      textpointer[1]=rand()&0x7F;
      regs.h.dl=color_table[rand()&0x0F];
      intr(0xEF,&regs);
    }
  
  return 0;
}
