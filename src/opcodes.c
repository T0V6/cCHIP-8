#include <stdlib.h>
#include <memory.h>
#include "opcodes.h"


//////////////////////////////////////////
////            Instructions          ////
//////////////////////////////////////////

void op_00e0(Chip* obj) 
{
    memset(obj->gfx.graphics_buffer, 0x00000000U, sizeof(obj->gfx.graphics_buffer));

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
    uint8_t nn = obj->opcode & 0x00FFU;

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


void op_8xy0(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy = (obj->opcode & 0x00F0U) >> 4U;

    obj->regs[vx] = obj->regs[vy]; // *((*obj).regs + vy); lol

    return;
}

void op_8xy1(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy = (obj->opcode & 0x00F0U) >> 4U;

    obj->regs[vx] |= obj->regs[vy];

    return;
}

void op_8xy2(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy = (obj->opcode & 0x00F0U) >> 4U;

    obj->regs[vx] &= obj->regs[vy];

    return;
}

void op_8xy3(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy = (obj->opcode & 0x00F0U) >> 4U;

    obj->regs[vx] ^= obj->regs[vy];

    return;
}

void op_8xy4(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy = (obj->opcode & 0x00F0U) >> 4U;
    
    uint16_t result = obj->regs[vx] + obj->regs[vy];

    obj->regs[CC8_SIZE_REGISTERS - 1] = (result > 255U) ? 1 : 0;

    obj->regs[vx] = result & 0x00FFU;

    return;
}

void op_8xy5(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy = (obj->opcode & 0x00F0U) >> 4U;

    obj->regs[CC8_SIZE_REGISTERS - 1] = (obj->regs[vx] > obj->regs[vy]) ? 1 : 0;

    obj->regs[vx] -= obj->regs[vy];

    return;
}

void op_8xy6(Chip* obj)
{
    uint8_t vx  = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t lsb = obj->regs[vx] & 0x1U; // 0x1 == 0001

    obj->regs[CC8_SIZE_REGISTERS - 1] = lsb;

    obj->regs[vx] >>= 1;

    return;
}

void op_8xy7(Chip* obj)
{
    uint8_t vx  = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy  = (obj->opcode & 0x00F0U) >> 4U;

    uint16_t sub = obj->regs[vy] - obj->regs[vx];

    obj->regs[CC8_SIZE_REGISTERS - 1] = (sub > 0) ? 1 : 0;

    obj->regs[vx] = sub;

    return;
}

void op_8xye(Chip* obj)
{
    uint8_t vx  = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t msb = (obj->regs[vx] & 0x80U) >> 7U; // 1000 0000 --> 0000 0001

    obj->regs[CC8_SIZE_REGISTERS - 1] = msb;

    obj->regs[vx] <<= 1;

    return;
}


void op_9xy0(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy = (obj->opcode & 0x00F0U) >> 4U;

    if (obj->regs[vx] != obj->regs[vy])     { obj->reg_pc += 2; }

    return;
}


void op_annn(Chip* obj)
{
    uint16_t nnn = obj->opcode & 0x0FFFU;

    obj->reg_index = nnn;

    return;
}

void op_bnnn(Chip* obj)
{
    uint16_t nnn = obj->opcode & 0x0FFFU;

    obj->reg_pc = obj->regs[0] + nnn;

    return;
}

void op_cxnn(Chip* obj)
{
    uint8_t vx  = (obj->opcode & 0x0F00U) >> 8U;
    uint16_t nn = obj->opcode & 0x00FFU;

    obj->regs[vx] = (rand() % 256) & nn;

    return;
}

void op_dxyn(Chip* obj)
{
    uint8_t vx  = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t vy  = (obj->opcode & 0x00F0U) >> 4U;
    uint8_t n   = obj->opcode & 0x000FU;

    // wrap around display size
    uint8_t pos_x = (obj->regs[vx]) % CC8_GFX_BUFF_WIDTH;   // initial x position
    uint8_t pos_y = (obj->regs[vy]) % CC8_GFX_BUFF_HEIGHT; // initial y position

    obj->regs[CC8_SIZE_REGISTERS - 1] = 0; // reset 0xF status


    for (uint8_t y = 0; y < n; ++y) {
        // get the binary value for the y-sprite row
        // index should be set to sprite's initial address. y variable will iterate over it's 
        uint8_t sprite_row = obj->mem[obj->reg_index + y];

        for (uint8_t x = 0; x < 8U; ++x) {
            /* 
                * if x column (pixel) of the y row IS 0, we don't need to do anything since there's nothing to draw
                * 0x80 as we need to locate the bit column in the row byte
                * Example:
                    x = 2

                    0x80 = 1000 0000 >> x       ==>     0010 0000 = 0x20
                    We need to find out if bit n°6 (column 2) is 1 or 0

                    1010 0000       (y-sprite byte)
                                &
                    0010 0000       (byte to check column x status)
                    --------------
                    0010 0000       (result; bit n°6 is set)
            */
            if (sprite_row & (0x80U >> x)) {
                // Calculates memory position
                // Sprite starts at pos_x/y, adds x/y for current bit in the display at (x,y)
                //      Equivalent to (row * ARR_WIDTH + column)
                // Wrap so it doesn't go out of bounds
                uint16_t address_pixel = ((pos_y + y) * CC8_GFX_BUFF_WIDTH + (pos_x + x)) % CC8_GFX_BUFF_SIZE;
                uint32_t* display_pixel = &(obj->gfx.graphics_buffer[address_pixel]);

                // We know that 1 bit is set to 1 (see if condition above)
                // Therefore, if the current bit in the display at (x,y) position is also set to 1, it will be flipped (XOR)
                // If that happens, we must set Vf to 1 as pixels collide
                if ((*display_pixel) == UINT32_MAX)   { obj->regs[CC8_SIZE_REGISTERS -1] = 1; }

                obj->gfx.graphics_buffer[address_pixel] ^= UINT32_MAX; // draw
            }
        }
    }

    return;
}

void op_ex9e(Chip* obj)
{
    uint8_t vx  = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t key = obj->regs[vx];

    if (obj->keys[key])   { obj->reg_pc += 2; }

    return;
}

void op_exa1(Chip* obj)
{
    uint8_t vx  = (obj->opcode & 0x0F00U) >> 8U;
    uint8_t key = obj->regs[vx];

    if (!obj->keys[key])   { obj->reg_pc += 2; }

    return;
}


void op_fx07(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;

    obj->regs[vx] = obj->delay_timer;

    return;
}

void op_fx0a(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    
    uint8_t resume = 0;

    for (uint8_t i = 0; i < CC8_SIZE_KEYS; ++i) {
        if (obj->keys[i]) {
            obj->regs[vx] = i;
            resume = 1;

            break;
        }
    }

    if (!resume)    { obj->reg_pc -= 2; } // execute again

    return;
}

void op_fx15(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;

    obj->delay_timer = obj->regs[vx];

    return;
}

void op_fx18(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;

    obj->sound_timer = obj->regs[vx];

    return;
}

void op_fx1e(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;

    obj->reg_index += obj->regs[vx];

    return;
}

void op_fx29(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;

    obj->reg_index = CC8_ADDR_FONT_START + (5 * obj->regs[vx]);

    return;
}

void op_fx33(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;
    
    uint8_t value = obj->regs[vx];

    obj->mem[obj->reg_index + 2] = value % 10; // ones
    value /= 10;

    obj->mem[obj->reg_index + 1] = value % 10; // tens
    value /= 10;

    obj->mem[obj->reg_index] = value % 10;  // hundreds 

    return;
}

void op_fx55(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;

    for (uint8_t i = 0; i < vx; ++i ) {
        obj->mem[obj->reg_index + i] = obj->regs[i];
    }

    return;
}

void op_fx65(Chip* obj)
{
    uint8_t vx = (obj->opcode & 0x0F00U) >> 8U;

    for (uint8_t i = 0; i < vx; ++i) {
        obj->regs[i] = obj->mem[obj->reg_index + i];
    }

    return;
}




//////////////////////////////////////////
////      Decoding Instructions       ////
//////////////////////////////////////////

void (*cc8_instruction[0xF + 1])(Chip* obj) = { NULL };
void (*cc8_table_0[0xE + 1])(Chip* obj)     = { NULL };
void (*cc8_table_8[0xE + 1])(Chip* obj)     = { NULL };
void (*cc8_table_e[0xA + 1])(Chip* obj)     = { NULL };
void (*cc8_table_f[0x65 + 1])(Chip* obj)    = { NULL };

void opcodes_0(Chip* obj)
{
    cc8_table_0[obj->opcode & 0x000FU](obj);

    return;
}

void opcodes_8(Chip* obj)
{
    cc8_table_8[obj->opcode & 0x000FU](obj);

    return;
}

void opcodes_e(Chip* obj)
{
    cc8_table_e[(obj->opcode & 0x00F0U) >> 4U](obj);

    return;
}

void opcodes_f(Chip* obj)
{
    cc8_table_f[obj->opcode & 0x00FFU](obj);

    return;
}