/*
    Even though one can modify the emulator to increase, let's say, the number of usable keys, 
        one must also remember that almost every address is expected by ROMs. 
            Therefore, changes must be done cautiously and in accordance with the expected files.
*/

#include <time.h>
#include "chip.h"


int main(void)
{
    srand(time(NULL)); // seed random
    

    return 0;
}