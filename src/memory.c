#include <stdlib.h>
#include <stdio.h>
#include "memory.h"


//////////////////////////////////////////
////            Functions             ////
//////////////////////////////////////////
static int8_t helper_is_null(void* ptr, const char* name)
{
    if (ptr == NULL) {
        fprintf(stderr, "[MEMORY] Error: %s pointer was NULL\n", name);

        return -1;
    }
    else { return 0; }
}


int8_t load_rom(Chip* obj, const char* file)
{
    if (helper_is_null(obj, "Chip") != 0)   { return -1; }

    FILE* f = fopen(file, "rb");


    if (f != NULL) {
        printf("[MEMORY] opened file %s\n", file);

        if (fseek(f, 0, SEEK_END) != 0) {
            fclose(f);
            fprintf(stderr, "[MEMORY] Error seeking ROM's file end\n");

            return -1;
        }

        long size = ftell(f);   // get file size

        char* buffer = (size >= 0) ? (char*)malloc((size_t)size) : NULL; // allocate buffer
        if (buffer != NULL) {
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


int8_t load_fonts(Chip* obj, uint8_t* fonts) 
{
    if (helper_is_null(obj, "Chip") != 0) { return -1; }

    printf("[MEMORY] Loading Fonts into RAM...\n");

    for (uint8_t i = 0; i < CC8_SIZE_FONT; ++i) { 
        uint8_t address = CC8_ADDR_FONT_START + i;
        printf("[MEMORY] %x\n", address);

        obj->mem[address] = fonts[i];
    }

    printf("[MEMORY] Fonts loaded successfully\n");


    return 0;
}