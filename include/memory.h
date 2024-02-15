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


#define CC8_ADDR_PROG_START (0x200U)


#define CC8_SIZE_REGISTERS  (16U)
#define CC8_SIZE_RAM        (4096U)
#define CC8_SIZE_STACK      (16U)
#define CC8_SIZE_KEYS       (16U)


#endif