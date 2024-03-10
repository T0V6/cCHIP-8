/*
    Even though one can modify the emulator to increase, let's say, the number of usable keys, 
        one must also remember that almost every address is expected by ROMs. 
            Therefore, changes must be done cautiously and in accordance with the expected files.
*/

/* TODO:
    * Sound 
    * Error: null pointer dereference after initial screens on ROMs
*/
/*  
    FIxed errors:
    Stupid bug was because opcode was 009E. Since the AND mask was 00FF, it tried to access the array at 9E (158) position,
        But array had a maximum posiiton of E+1.
        Since there are only 2 instructions starting with E:
            ExA1
            Ex9E
        And neither of the last 2 bytes repeat, we can choose to use A/9 or 1/E
        The array will be smaller if we choose the first bytes, since maximum will be A+1 (11) vs E+1 (16)
        Then the mask will be 00F0
*/


#include <time.h>
#include "chip.h"


int main(int argc, char** argv)
{
    (void)argc; // ignore this

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

    const float delay = 10.0f;
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