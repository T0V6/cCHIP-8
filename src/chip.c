#include <stdio.h>
#include <memory.h>
#include "chip.h"
#include "fonts.h"
#include "opcodes.h"
#include "graphics.h"

//////////////////////////////////////////
////            Functions             ////
//////////////////////////////////////////

void chip_init(Chip* obj, const char* romfile)
{
    obj->reg_pc = CC8_ADDR_PROG_START;

    if (ram_load_rom(obj, romfile) != 0)    { fprintf(stderr, "[CHIP] Error reading ROM\n"); }

    ram_load_fonts(obj, fontset);

    ram_load_instructions();

    return;
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