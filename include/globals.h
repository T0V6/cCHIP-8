#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

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
/* Total bytes for fonts (5B * 16) */
#define CC8_SIZE_FONT       (80U)



/* Graphics buffer width (columns) */
#define CC8_GFX_BUFF_WIDTH  (64U) 
/* Graphics buffer height (rows) */
#define CC8_GFX_BUFF_HEIGHT (32U)
/* Display buffer size (for linear array managment) */
#define CC8_GFX_BUFF_SIZE   (CC8_GFX_BUFF_WIDTH * CC8_GFX_BUFF_HEIGHT)



/* CHIP-8 Structure */
typedef struct chip {

    // Registers are labeled as V<hex_value>. VF is reserved for operations' returns
    // Each register holds values within [0x00, 0xFF] (1B)
    // CPU storage
    uint8_t regs[CC8_SIZE_REGISTERS];

    // Memory address space is [0x000, 0xFFF] (4kB)
    // RAM
    uint8_t mem[CC8_SIZE_RAM];

    // Index register
    // Stores memory addresses for use in operations
    uint16_t reg_index;  

    // Program counter register
    // Stores the address of the next instruction to execute (starting at 0x200)
    uint16_t reg_pc; 

    // Stack containing the functions' order of execution
    // Pushes the <reg_pc> value when the CALL instruction was executed
    // RET instruction pops the address from the stack and puts it into the <reg_pc> to continue the execution on next cycle
    uint16_t stack[CC8_SIZE_STACK];

    // Stack pointer
    // Keeps track of where of the stack levels we are in
    // bits required depends on the max value of <CC8_SIZE_STACK>
    // When pushing a value to the stack, first put <reg_pc> into the stack and then increase the pointer
    // When popping a value from the stack, first decrease the pointer and then put the address into <reg_pc>
    uint8_t ptr_stack;

    // For timing
    // Loaded value will be decremented by a rate of 60Hz (or at the rate the clock cycle is set to) if it != 0
    uint8_t delay_timer;

    // Sound timing
    // Loaded value will be decremented by a rate of 60Hz (or at the rate the clock cycle is set to) if it != 0
    // Buzzer will sound as long as the value is > 0, when it equals 0, it deactivates
    uint8_t sound_timer;

    // Input keys that match hex values from 0 to F (4b)
    // Keys status can be pressed or not
    uint8_t keys[CC8_SIZE_KEYS];

    // Buffer used for storing the graphics to display
    // Each pixel can be either on or off --> monochrome
    // Since the variable is 32b long:
    //      * 0x0x00000000  = off
    //      * 0xFFFFFFFF    = on
    // XOR operation is performed between the sprite pixel and the display pixe; pixels will turn on only when their statuses differ
    uint32_t graphics_buffer[CC8_GFX_BUFF_SIZE];

    // Operation code
    // A CPU instruction, its size is 2B
    //      As a result, when fetching an instruction, we must fetch a byte from <memory[reg_pc]> and another from <memory[reg_pc + 1]>
    //          However, since <memory> is 1B, we need to left shift the first byte by 8 positions:
    //                                 * 10101011 << 8U =  1010101100000000
    //          Then, we need to combine them into a single value. Operation would look like this:
    //                  * opcode = (memory[reg_pc] << 8U) | memory[reg_pc + 1]
    uint16_t opcode;
    
} Chip;

#endif // GLOBALS_H