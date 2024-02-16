#include "chip.h"


//////////////////////////////////////////
////            Functions             ////
//////////////////////////////////////////

void chip_init(Chip* obj, const char* romfile)
{
    obj->reg_pc = CC8_ADDR_PROG_START;

    load_rom(obj, romfile);

    return;
}




