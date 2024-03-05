#include <stdio.h>
#include <memory.h>
#include "chip.h"
#include "fonts.h"
#include "opcodes.h"
#include "graphics.h"


int8_t chip_init(Chip* obj, const char* romfile, uint16_t width, uint16_t height)
{
    if (!obj) {
        fprintf(stderr, "[CHIP] Error: struct Chip pointer was NULL\n");

        return -1;
    }

    // Initialise members
    for (size_t i = 0; i < CC8_SIZE_REGISTERS; ++i)     { obj->regs[i] = 0; }    
    for (size_t i = 0; i < CC8_SIZE_RAM; ++i)           { obj->mem[i] = 0; }   
    for (size_t i = 0; i < CC8_SIZE_STACK; ++i)         { obj->stack[i] = 0; }   
    for (size_t i = 0; i < CC8_SIZE_KEYS; ++i)          { obj->keys[i] = 0; }       
    for (size_t i = 0; i < CC8_GFX_BUFF_SIZE; ++i)      { obj->gfx.graphics_buffer[i] = 0; }   

    obj->reg_index      = 0;
    obj->reg_pc         = CC8_ADDR_PROG_START;
    obj->ptr_stack      = 0;
    obj->delay_timer    = 0;
    obj->sound_timer    = 0;
    obj->opcode         = 0;

    gfx_initialise(&(obj->gfx.window), &(obj->gfx.renderer), &(obj->gfx.texture), width, height);

    ram_load_fonts(obj, cc8_fontset);

    ram_load_instructions();


    // load rom
    if (ram_load_rom(obj, romfile) != 0) { 
        fprintf(stderr, "[CHIP] Error reading ROM\n"); 

        return -1;
    }
    
    return 0;
}

void chip_run(Chip* obj)
{ 
    // opcode is 2B long
    // gets first byte, then merge the second one
    obj->opcode = (obj->mem[obj->reg_pc] << 8U) | obj->mem[obj->reg_pc + 1]; 

    obj->reg_pc += 2;

    // get the first value so instruction array can redirect to the opcode
    // shifted 12 since we need only the first hex (4 bits)
    cc8_instruction[(obj->opcode & 0xF000U) >> 12U](obj);

    if (obj->delay_timer > 0)   { obj->delay_timer -= 1; }
    if (obj->sound_timer > 0)   { obj->sound_timer -= 1; }

    return;
}