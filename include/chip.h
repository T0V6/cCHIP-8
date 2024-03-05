// https://en.wikipedia.org/wiki/CHIP-8
// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

#ifndef CHIP_H
#define CHIP_H

#include <stdlib.h>
#include "mem.h"


/* Initialises chip */
void chip_init(Chip*, const char*);

/* Executes a cycle */
void chip_run(Chip*);

#endif // CHIP_H