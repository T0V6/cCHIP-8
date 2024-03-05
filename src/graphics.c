#include "graphics.h"
#include "globals.h"


int8_t gfx_initialise(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** texture, uint16_t width, uint16_t height)
{
    /*
        Double pointer is necessary when initializing memory dynamically from a pointer

        T   window;
        T*  wind = &window;
        T** win = &wind;

        |------------|-------------------------------------------------------|
        |  Variable  |                      Value                            |        
        |------------|-------------------------------------------------------|
        |  win       |  &wind (address; address of pointer wind)             |
        |------------|-------------------------------------------------------|
        |  *win      |  wind (value; address of window)                      |                   
        |------------|-------------------------------------------------------|
        |  **win     |  *wind (value; value stored at the address of window) |               
        |------------|-------------------------------------------------------|
    */

    SDL_Init(SDL_INIT_EVERYTHING);

    *window = SDL_CreateWindow("CHIP-8 - C17", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED,
    width, 
    height, 
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!(*window)) {
        fprintf(stderr, "[GFX] Error creating window\n"); 

        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (!(*renderer)) {
        fprintf(stderr, "[GFX] Error creating renderer\n");

        return -1;
    }

    *texture = SDL_CreateTexture(*renderer, 
    SDL_PIXELFORMAT_RGBA8888, 
    SDL_TEXTUREACCESS_TARGET, 
    CC8_GFX_BUFF_WIDTH, 
    CC8_GFX_BUFF_HEIGHT);

    if (!(*texture)) {
        fprintf(stderr, "[GFX] Error creating texture\n");

        return -1;
    }

    printf("[GFX] SDL subsystems initialised\n");

    return 0;
}

void gfx_destroy(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    printf("[GFX] SDL subsystems destroyed\n");

    return;
}

