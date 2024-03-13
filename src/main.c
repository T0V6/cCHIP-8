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

   if (argc != 2 || !argv[1]) {
        fprintf(stderr, "[MAIN] Error parsing arguments\n");
        printf("Usage:\t%s <ROM>\n", argv[0]);

        return -1;
   }
    
    srand(time(NULL));

    const float delay = 2.0f;
    const char* rom     = argv[1]; //argv[0] is program's name 

    Chip cc8;
    chip_init(&cc8, rom, 640, 480);
    
    
    clock_t time_start = clock(); // get start time
    uint8_t quit = 1;

    while (quit) {
        quit = keys_input(cc8.keys);

        clock_t time_current = clock();
        float diff = ((float)(time_current - time_start) / CLOCKS_PER_SEC) * 1000.0f;

        if (diff > delay) {
            time_start = time_current;

            chip_run(&cc8);
        }
    }

    return 0;
}