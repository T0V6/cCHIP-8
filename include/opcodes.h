#ifndef OPCODES_H
#define OPCODES_H

#include "globals.h"


/* CLS (clear screen)
    * Clear video
*/
void op_00e0(Chip*);

/* RET (return)
    * Puts the stack pointer instruction into program counter
*/
void op_00ee(Chip*);

/* JP (jump) 
    * Sets program counter to <nnn>
    * Doesn't return to previous address
*/
void op_1nnn(Chip*);

/* CALL (call subroutine) 
    * Puts current program counter into the stack so returning is possible
    * Increments stack pointer
*/
void op_2nnn(Chip*);

/* SE (skip equal)
    * Compares register Vx to nn 
    * If they are equal, skips to the next instruction (+= 2 since an instruction is 2 bytes long)
*/
void op_3xnn(Chip*);

/* SNE (skip not equal) 
    * Compares register Vx to nn
    * If they are NOT equal, skips to the next instruction (+= 2 since an instruction is 2 bytes long)
*/
void op_4xnn(Chip*);

/* SE (skip equal, registers variant) 
    * Compares registers Vx and Vy
    * If they are equal, it skips to the next instruction (+= 2 since an instruction is 2 bytes long)
*/
void op_5xy0(Chip*);

/* LD (load register)
    * Sets Vx register to nn
*/
void op_6xnn(Chip*);

/* ADD (add to register)
    * Adds nn to register Vx
*/
void op_7xnn(Chip*);


/* LD (load register) 
    * Sets Vx register with the contents of Vy register
*/
void op_8xy0(Chip*);

/* OR (bitwise | operation)
    * Sets Vx register to Vx OR Vy
*/
void op_8xy1(Chip*);

/* AND (bitwise & operation) 
    * Sets Vx register to Vx AND Vy
*/
void op_8xy2(Chip*);

/* XOR (bitwise ^ operation) 
    * Sets Vx register to Vx XOR Vy
*/
void op_8xy3(Chip*);

/* ADD (add registers with carry)
    * Adds Vx and Vy and stores into Vx
    * If result is greater than 255 (1B), VF is set to 1 and only the lowest 8 bits are kept
*/
void op_8xy4(Chip*);

/* SUB (subtract registers)
    * Subtracts Vx and Vy and stores into Vx
    * If Vx is greater than Vy, VF is set to 1
*/
void op_8xy5(Chip*);

/* SHR (shift right)
    * Shifts 1 bit right Vx register
    * Least significant bit is stored in VF register
    * If LSB is 1, VF is set to 1
    * Since binary increments by a factor of 2 from right to left, shifting 1 bit to the right is equivalent to dividing by 2
*/
void op_8xy6(Chip*);

/* SUBN (subtract registers negative)
    * Subtracts Vy and Vx and stores into Vx
    * If Vy is greater than Vx, VF is set to 1
*/
void op_8xy7(Chip*);

/* SHL (shift left)
    * Shifts 1 bit left Vx register
    * MSB is stored in VF register
    * Since binary increments by a factor of 2 from right to left, shifting 1 bit to the left is equivalent to multiplying by 2
*/
void op_8xye(Chip*);


/* SNE (skip next instruction if not equal)
    * Compares Vx and Vy, if they are not equal, the next instruction is skipped
    * Program counter is incremented before calling the instruction, so it is already incremented by 2 (has the opcode stored)
    * Current opcode would be the function comparing Vx and Vy
        If they are not equal, the next instruction (+2, the one Program Counter has stored) is skipped (+2 again) 
*/
void op_9xy0(Chip*);


/* LD (load register)
    * Sets the index register with the contents of nnn
*/
void op_annn(Chip*);

/* JP (jump)
    * Jumps to location nnn + V0
*/
void op_bnnn(Chip*);

/* RND (random and)
    * Sets Vx register to random and performs AND operation with the result
*/
void op_cxnn(Chip*);

/* DRW (draw)
    * Draws n-byte height pixels with a width of 1-byte pixels (since uint8_t). Row size = n, Columns = 1B
    * Draws at coordinates (Vx, Vy) 
    * Starts reading from memory at address stored in Index variable (Index is not modified)
    * Vf is set to 1 if XOR operation returns 0 (from set to unset; collision). Otherwise, is set to 0
*/
void op_dxyn(Chip*);

/* SKP (skip instruction if key is pressed)
    * Skips next instruction if Vx is a pressed key
    * See op_9xy0 function comments for an explanation of why program counter is incremented by 2
*/
void op_ex9e(Chip*);

/* SKNP (skip instruction if key is not pressed)
    * Skips next instruction if Vx is NOT a pressed key
    * See op_9xy0 function comments for an explanation of why program counter is incremented by 2
*/
void op_exa1(Chip*);

/* LD (load register)
    * Sets Vx with the delay timer
*/
void op_fx07(Chip*);

/* LD (load register)
    * Waits for key input and stores it in Vx
    * To 'wait' we decrement the Program Counter by 2. This will lead to a loop
        since PC will be incremented by 2 again on next cycle
*/
void op_fx0a(Chip*);

/* LD (load register)
    * Sets delay timer with Vx contents
*/
void op_fx15(Chip*);

/* LD (load register)
    * Sets sound timer with Vx contents
*/
void op_fx18(Chip*);

/* ADD (Add register)
    * Sets Index register as Vx + Index
*/
void op_fx1e(Chip*);

/*  LD (load register)
    * Sets Index register to the location of the sprite for digit Vx
    * Fonts start at 0x50 and each font is 5B long, so we can multiply by 5 the digit to get the sprite location
*/
void op_fx29(Chip*);

/* LD (load register)
    * Stores BCD representation of Vx register contents in RAM at Index, Index + 1 and Index + 2
    * The hundreds are placed at Index, tens at Index + 1 and ones at Index + 2
    * Modulo 10 is used to isolate the ones-place (since it will wrap around 10)
    * Then division by 10 is performed to discard the ones-place. Value now will have decimals, but since
       the type is int, it will be truncated
    * Repeat

    * Example:
        256 % 10    = 6         256 / 10    = 25.6
        25  % 10    = 5         25 / 10     = 2.5
        2   % 10    = 2             --------
*/
void op_fx33(Chip*);

/* LD (load register)
    * Stores registers V from [0, x] in memory starting at Index
*/
void op_fx55(Chip*);

/* LD (load register)
    * Reads (stores into registers) registers V from [0, x] in memory starting at Index
*/
void op_fx65(Chip*);




/* Main funtion pointers array; calls the instruction or derives into other tables */
extern void (*cc8_instruction[0xF + 1])(Chip* obj);
/* Table of function pointers for 0-starting instructions */
extern void (*cc8_table_0[0xE + 1])(Chip* obj);
/* Table of function pointers for 8-starting instructions */
extern void (*cc8_table_8[0xE + 1])(Chip* obj);
/* Table of function pointers for E-starting instructions */
extern void (*cc8_table_e[0xE + 1])(Chip* obj);
/* Table of function pointers for F-starting instructions */
extern void (*cc8_table_f[0x65 + 1])(Chip* obj);


/* Decoder for 0-starting instructions */
void opcodes_0(Chip* obj);
/* Decoder for 8-starting instructions */
void opcodes_8(Chip* obj);
/* Decoder for E-starting instructions */
void opcodes_e(Chip* obj);
/* Decoder for F-starting instructions */
void opcodes_f(Chip* obj);

#endif // OPCODES_H