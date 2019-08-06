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

const char* text="0123456789";

const unsigned char fontdata[]=
  {

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F, // 0x21 !
    0x00,0x3E,0x63,0x07,0x1E,0x3C,0x70,0x7F, // 0x22 "
    0x00,0x3F,0x06,0x0C,0x1E,0x03,0x63,0x3E, // 0x23 #
    0x00,0x0E,0x1E,0x36,0x66,0x7F,0x06,0x06, // 0x24 $
    0x00,0x7E,0x60,0x7E,0x03,0x03,0x63,0x3E, // 0x25 %
    0x00,0x1E,0x30,0x60,0x7E,0x63,0x63,0x3E, // 0x26 &
    0x00,0x7F,0x63,0x06,0x0C,0x18,0x18,0x18, // 0x27 '
    0x00,0x3C,0x62,0x72,0x3C,0x4F,0x43,0x3E, // 0x28 (
    0x00,0x3E,0x63,0x63,0x3F,0x03,0x06,0x3C, // 0x29 )
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

  };

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
  fontpointer[6]=0xFF00; // First and last 
  
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
      regs.h.dl=rand()&0xFF;
      intr(0xEF,&regs);
    }
  
  return 0;
}
