// https://en.wikipedia.org/wiki/CHIP-8
// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

#ifndef CHIP_H
#define CHIP_H

#include "cchip8.h"
#include "memory.h"


/* Initialises chip */
void chip_init(Chip*, const char*);

#endif // CHIP_H