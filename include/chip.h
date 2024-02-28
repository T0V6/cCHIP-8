// https://en.wikipedia.org/wiki/CHIP-8
// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

#ifndef CHIP_H
#define CHIP_H

#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "memory.h"


/* Random int generator */
static int generate_random(int, int);

/* Initialises chip */
void chip_init(Chip*, const char*);



/* CLS (clear screen) */
// * Clear video
void op_00e0(Chip* obj);

/* RET (return) */
// * Puts the stack pointer instruction into program counter
void op_00ee(Chip* obj);

/* JP (jump) */
// * Sets program counter to <nnn>
// * Doesn't return to previous address
void op_1nnn(Chip* obj);

/* CALL (call subroutine) 
    * Puts current program counter into the stack so returning is possible
    * Increments stack pointer
*/
void op_2nnn(Chip* obj);

/* SE (skip equal)
    * Compares register Vx to nn 
    * If they are equal, skips to the next instruction (+= 2 since an instruction is 2 bytes long)
*/
void op_3xnn(Chip* obj);

/* SNE (skip not equal) 
    * Compares register Vx to nn
    * If they are NOT equal, skips to the next instruction (+= 2 since an instruction is 2 bytes long)
*/
void op_4xnn(Chip* obj);

/* SE (skip equal, registers variant) 
    * Compares registers Vx and Vy
    * If they are equal, it skips to the next instruction (+= 2 since an instruction is 2 bytes long)
*/
void op_5xy0(Chip* obj);

/* LD (load register)
    * Sets Vx register to nn
*/
void op_6xnn(Chip* obj);

/* ADD (add to register)
    * Adds nn to register Vx
*/
void op_7xnn(Chip* obj);



/* */

#endif // CHIP_H