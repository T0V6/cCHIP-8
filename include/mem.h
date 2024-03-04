#ifndef MEM_H
#define MEM_H

#include "globals.h"


/* Memory layout (4kB)

    +-----------------+ 0xFFF (4095) End of RAM
    |                 |
    |                 |
    |                 |
    |                 |
    |                 |
    |  [0x200, 0xFFF] |
    |  Program / Data |
    |      Space      |
    |                 |
    |                 |
    |                 |
    +~ ~ ~ ~ ~ ~ ~ ~ ~+ 0x600 (1536) Start of ETI 660 programs
    |                 |
    |                 |
    |                 |
    +-----------------+ 0x200 (512) Start of most programs
    |  [0x000, 0x1FF] |
    |  Reserved for   |
    |   interpreter   |
    +-----------------+ 0x000 (0) Start of RAM


    -> [0x050, 0x0A0] (81B)  will be used for fonts
*/


/* Initialises chip's memory (starting at 0x200) with ROM contents  */
int8_t load_rom(Chip*, const char*);
/* Loads font set into reserved memory */
void load_fonts(Chip*, uint8_t*);
/* Set function pointer tables with their respective instructions */
void set_instructions(void);

#endif  // MEM_H