// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#font


#ifndef FONTS_H
#define FONTS_H

#include <stdint.h>
#include "memory.h"

/*
    Most ROMs expect 16 characters to write to the screen. Characters are sorta like sprites.
    Each sprite is composed of 5 bytes (8b * 5)

    Example:
        Letter 'C' is :
            11110000            -->         ****     
            10000000            -->         *
            10000000            -->         * 
            10000000            -->         *
            11110000            -->         ****

    Each bit represents a pixel and follows the same logic as video:
            0 = off
            1 = on
    Each sprite has a total of 40 pixels
*/


uint8_t fontset[CC8_SIZE_FONT] = 
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

#endif // FONTS_H