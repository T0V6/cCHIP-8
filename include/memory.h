#ifndef MEMORY_H
#define MEMORY_H

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


/* Program's starting address */
#define CC8_ADDR_PROG_START (0x200U)
/* Fonts starting address */
#define CC8_ADDR_FONT_START (0x050U)



/* Amount of registers */
#define CC8_SIZE_REGISTERS  (16U)
/* Memory's size */
#define CC8_SIZE_RAM        (4096U)
/* Stack levels */
#define CC8_SIZE_STACK      (16U)
/* Amount of usable keys */
#define CC8_SIZE_KEYS       (16U)
/* Total bytes for fonts (5B * 16)*/
#define CC8_SIZE_FONT       (80U)

/* Initialises chip's memory (starting at 0x200) with ROM contents  */
int8_t load_rom(Chip*, const char*);
/* Loads font set into reserved memory */
int8_t load_fonts(Chip*, uint8_t*);

#endif