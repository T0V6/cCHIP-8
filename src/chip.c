#include <stdio.h>
#include "chip.h"
#include "fonts.h"


//////////////////////////////////////////
////            Functions             ////
//////////////////////////////////////////

static int generate_random(int min, int max)   { return ((rand() % (max - min + 1)) + min); }


void chip_init(Chip* obj, const char* romfile)
{
    obj->reg_pc = CC8_ADDR_PROG_START;

    if (load_rom(obj, romfile) != 0)    { fprintf(stderr, "[CHIP] Error reading ROM\n"); }

    if (load_fonts(obj, fontset) != 0)  {fprintf(stderr, "[CHIP] Error loading fonts\n"); }

    return;
}




//////////////////////////////////////////
////            Instructions          ////
//////////////////////////////////////////

void op_00e0(Chip* obj) 
{
    memset(obj->graphics_buffer, 0, sizeof(obj->graphics_buffer));

    return;
}

void op_00ee(Chip* obj) 
{
    obj->ptr_stack--;
    obj->reg_pc = obj->stack[obj->ptr_stack];

    return;
}

void op_1nnn(Chip* obj)
{
    uint16_t address = obj->opcode & 0x0FFFU; // 0x0FFF == 4095. We only care about nnn values of the instruction

    obj->reg_pc = address;

    return;
}

void op_2nnn(Chip* obj)
{
    uint16_t address = obj->opcode & 0x0FFFU; // 0x0FFF == 4095. We only care about nnn values of the instruction

    obj->stack[obj->ptr_stack] = obj->reg_pc;
    obj->ptr_stack++;
    obj->reg_pc = address;

    return;
}

void op_3xnn(Chip* obj)
{
    // 3 x n n
    // | | | |
    // 0 F 0 0
    // We only care about Vx, which is lower half of the first 8 bits (lower 4 bits)
    // Operation Codes are 2 bytes long ==> 1st byte 3x, 2nd byte nn
    // Therefore:
    // 3333 xxxx nnnn nnnn
    // We need to get x, so an AND operation will reveal only the required bytes (0x0F00 == 0000 1111 0000 0000)
    // Then we need to shift the result so it aligns with the lower 4 bits (since there are only 16 registers)
    /*
        Example:

        0011 0100 0101 0110   (0x3456 opcode)
        0000 1111 0000 0000   (0x0F00u mask)
        -------------------
        0000 0100 0000 0000   (Result)

        Shift:
        0000 0000 0000 0100   (Right shift, normalised to lower 4 bits)
    */
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;

    // Doesn't need shifting since it's the whole second byte
    uint8_t nn = (obj->opcode & 0x00FFU);

    if (obj->regs[vx] == nn)    { obj->reg_pc += 2; }

    return;
}

void op_4xnn(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t nn = (obj->opcode & 0x00FFU);

    if (obj->regs[vx] != nn)    { obj->reg_pc += 2; }

    return;
}

void op_5xy0(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy = (obj->opcode & 0x00F0U) >> 4U;

    if (obj->regs[vx] == obj->regs[vy])     { obj->reg_pc += 2; }

    return;
}

void op_6xnn(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t nn = obj->opcode & 0x00FFU;

    obj->regs[vx] = nn;

    return;
}

void op_7xnn(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t nn = obj->opcode & 0x00FFU;

    obj->regs[vx] += nn;

    return;
}


