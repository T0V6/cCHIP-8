#include <stdio.h>
#include "chip.h"
#include "fonts.h"


//////////////////////////////////////////
////            Functions             ////
//////////////////////////////////////////

void chip_init(Chip* obj, const char* romfile)
{
    obj->reg_pc = CC8_ADDR_PROG_START;

    if (load_rom(obj, romfile) != 0)    { fprintf(stderr, "[CHIP] Error reading ROM\n"); }

    if (load_fonts(obj, fontset) != 0)  {fprintf(stderr, "[CHIP] Error loading fonts\n"); }

    return;
}
