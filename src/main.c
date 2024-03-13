/*
    Even though one can modify the emulator to increase, let's say, the number of usable keys, 
        one must also remember that almost every address is expected by ROMs. 
            Therefore, changes must be done cautiously and in accordance with the expected files.
*/

/* TODO:
    * Sound 
*/

#include <time.h>
#include "chip.h"


int main(int argc, char** argv)
{
    /* 
    Random notes:
        char* arg1 = "hello";   // pointer to the first character in the string
        char* arg2 = "world";   //    "                 "                   "
        char* matrix[] = { arg1, arg2 }; // array of strings (pointers to the first char in the string)
        char** argv = matrix;   // pointer to the array of strings


        argv[0]     == *(argv + 0)                          == *(&matrix + 0)
        argv[0][0]  == *(argv[0])   == *(*(argv + 0) + 0)   == *(*(&matrix + 0) + 0)
    */

   if (argc != 3 || !argv[1]) {
        fprintf(stderr, "[MAIN] Error parsing arguments\n");
        printf("Usage:\t%s <ROM> <Delay>\n", argv[0]);

        return -1;
   }
    
    srand(time(NULL));

    const char* rom         = argv[1]; //argv[0] = program's name 
    const uint32_t delay    = strtoul(argv[2], NULL, 0);

    Chip cc8;
    chip_init(&cc8, rom, 640, 480);
    
    uint8_t quit = 1;

    while(quit) {
        quit = keys_input(cc8.keys);
        SDL_Delay(delay);

        chip_run(&cc8);
    }

    return 0;
}