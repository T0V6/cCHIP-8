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



/* LD (load register) 
    * Sets Vx register with the contents of Vy register
*/
void op_8xy0(Chip* obj);

/* OR (bitwise | operation)
    * Sets Vx register to Vx OR Vy
*/
void op_8xy1(Chip* obj);

/* AND (bitwise & operation) 
    * Sets Vx register to Vx AND Vy
*/
void op_8xy2(Chip* obj);

/* XOR (bitwise ^ operation) 
    * Sets Vx register to Vx XOR Vy
*/
void op_8xy3(Chip* obj);

/* ADD (add registers with carry)
    * Adds Vx and Vy and stores into Vx
    * If result is greater than 255 (1B), VF is set to 1 and only the lowest 8 bits are kept
*/
void op_8xy4(Chip* obj);

/* SUB (subtract registers)
    * Subtracts Vx and Vy and stores into Vx
    * If Vx is greater than Vy, VF is set to 1
*/
void op_8xy5(Chip* obj);

/* SHR (shift right)
    * Shifts 1 bit right Vx register
    * Least significant bit is stored in VF register
    * If LSB is 1, VF is set to 1
*/
void op_8xy6(Chip* obj);

/* SUBN (subtract registers negative)
    * Subtracts Vy and Vx and stores into Vx
    * If Vy is greater than Vx, VF is set to 1
*/
void op_8xy7(Chip* obj);

/* SHL (shift left)
    * Shifts 1 bit left Vx register
    * MSB is stored in VF register
*/
void op_8xye(Chip* obj);

#endif // CHIP_H