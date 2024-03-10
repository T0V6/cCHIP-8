#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#include "opcodes.h"


int8_t ram_load_rom(Chip* obj, const char* file)
{
    FILE* f = fopen(file, "rb");


    if (f) {
        printf("[MEMORY] opened file %s\n", file);

        if (fseek(f, 0, SEEK_END) != 0) {
            fclose(f);
            fprintf(stderr, "[MEMORY] Error seeking ROM's file end\n");

            return -1;
        }

        long size = ftell(f);   // get file size

        char* buffer = (size >= 0) ? (char*)malloc((size_t)size) : NULL; // allocate buffer
        if (buffer) {
            rewind(f); // go to the beginning of the file
            
            size_t bytes_read = fread(buffer, 1, (size_t)size, f);
            if (bytes_read != (size_t)size) {
                fclose(f);
                fprintf(stderr, "[MEMORY] Error filling buffer from ROM\n");

                return -1;
            }
            
            printf("[MEMORY] ROM buffer filled sucessfully\n");
            printf("[MEMORY] Loading ROM into RAM...\n");

            for (long i = 0; i < size; ++i)  { 
                uint16_t address = CC8_ADDR_PROG_START + i;
                printf("[MEMORY] %x\n", address);

                obj->mem[address] = buffer[i]; 
            }

            printf("[MEMORY] ROM loaded successfully\n");

            free(buffer);
        }
        else {
            fclose(f);
            fprintf(stderr, "[MEMORY] Error allocating memory for ROM buffer\n");

            return -1;
        }
    }
    else { 
        fprintf(stderr, "[MEMORY] Error opening ROM file\n");

        return -1; 
    }


    fclose(f);

    return 0;
}

void ram_load_fonts(Chip* obj, const uint8_t* fonts) 
{
    printf("[MEMORY] Loading Fonts into RAM...\n");

    for (uint8_t i = 0; i < CC8_SIZE_FONT; ++i) { 
        uint8_t address = CC8_ADDR_FONT_START + i;
        printf("[MEMORY] %x\n", address);

        obj->mem[address] = fonts[i];
    }

    printf("[MEMORY] Fonts loaded successfully\n");

    return;
}

void ram_load_instructions(void)
{
    cc8_instruction[0x0] = &opcodes_0;
    cc8_instruction[0x1] = &op_1nnn;
    cc8_instruction[0x2] = &op_2nnn;
    cc8_instruction[0x3] = &op_3xnn;
    cc8_instruction[0x4] = &op_4xnn;
    cc8_instruction[0x5] = &op_5xy0;
    cc8_instruction[0x6] = &op_6xnn;
    cc8_instruction[0x7] = &op_7xnn;
    cc8_instruction[0x8] = &opcodes_8;
    cc8_instruction[0x9] = &op_9xy0;
    cc8_instruction[0xA] = &op_annn;
    cc8_instruction[0xB] = &op_bnnn;
    cc8_instruction[0xC] = &op_cxnn;
    cc8_instruction[0xD] = &op_dxyn;
    cc8_instruction[0xE] = &opcodes_e;
    cc8_instruction[0xF] = &opcodes_f;


    cc8_table_0[0x0] = &op_00e0;
    cc8_table_0[0xE] = &op_00ee;

    cc8_table_8[0x0] = &op_8xy0; 
    cc8_table_8[0x1] = &op_8xy1; 
    cc8_table_8[0x2] = &op_8xy2; 
    cc8_table_8[0x3] = &op_8xy3; 
    cc8_table_8[0x4] = &op_8xy4; 
    cc8_table_8[0x5] = &op_8xy5; 
    cc8_table_8[0x6] = &op_8xy6; 
    cc8_table_8[0x7] = &op_8xy7; 
    cc8_table_8[0xE] = &op_8xye; 

    cc8_table_e[0xA] = &op_exa1;
    cc8_table_e[0x9] = &op_ex9e;

    cc8_table_f[0x07] = &op_fx07;
    cc8_table_f[0x0A] = &op_fx0a;
    cc8_table_f[0x15] = &op_fx15;
    cc8_table_f[0x18] = &op_fx18;
    cc8_table_f[0x1E] = &op_fx1e;
    cc8_table_f[0x29] = &op_fx29;
    cc8_table_f[0x33] = &op_fx33;
    cc8_table_f[0x55] = &op_fx55;
    cc8_table_f[0x65] = &op_fx65;

    return;
}