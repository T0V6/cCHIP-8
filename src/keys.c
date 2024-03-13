#include "keys.h"


uint8_t keys_input(uint8_t* keys_array)
{
    uint8_t status = 1;

    SDL_Event e;

    // horrendous
    while (SDL_PollEvent(&e)) {
        switch (e.type)
        {
        case SDL_QUIT:
            status = 0;
            break;

        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                status = 0;
                break;
            
            case SDLK_x:
                keys_array[0] = 1;
                break;
            
            case SDLK_1:
                keys_array[1] = 1;
                break;

            case SDLK_2:
                keys_array[2] = 1;    
                break;

			case SDLK_3:
                keys_array[3] = 1;
                break;

			case SDLK_q:
                keys_array[4] = 1;
                break;

			case SDLK_w:
                keys_array[5] = 1;
                break;

			case SDLK_e:
                keys_array[6] = 1;
                break;

			case SDLK_a:
                keys_array[7] = 1;
                break;

			case SDLK_s:
                keys_array[8] = 1;
                break;

			case SDLK_d:
                keys_array[9] = 1;
                break;

			case SDLK_z:
                keys_array[10] = 1;
                break;

			case SDLK_c:
                keys_array[11] = 1;
                break;

			case SDLK_4:
                keys_array[12] = 1;
                break;

			case SDLK_r:
                keys_array[13] = 1;
                break;

			case SDLK_f:
                keys_array[14] = 1;
                break;

			case SDLK_v:
                keys_array[15] = 1;
                break;

            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (e.key.keysym.sym)
			{
			case SDLK_x:
                keys_array[0] = 0;
                break;

			case SDLK_1:
                keys_array[1] = 0;
                break;

			case SDLK_2:
                keys_array[2] = 0;
                break;

			case SDLK_3:
                keys_array[3] = 0;
                break;

			case SDLK_q:
                keys_array[4] = 0;
                break;

			case SDLK_w:
                keys_array[5] = 0;
                break;

			case SDLK_e:
                keys_array[6] = 0;
                break;

			case SDLK_a:
                keys_array[7] = 0;
                break;

			case SDLK_s:
                keys_array[8] = 0;
                break;

			case SDLK_d:
                keys_array[9] = 0;
                break;

			case SDLK_z:
                keys_array[10] = 0;
                break;

			case SDLK_c:
                keys_array[11] = 0;
                break;

			case SDLK_4:
                keys_array[12] = 0;
                break;

			case SDLK_r:
                keys_array[13] = 0;
                break;

			case SDLK_f:
                keys_array[14] = 0;
                break;

			case SDLK_v:
                keys_array[15] = 0;
                break;
			}
			break;

        default:
            break;
        }
    }

    return status;
}