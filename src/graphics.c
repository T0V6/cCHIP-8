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

    /*
        To simulate a screen, a single texture is used
        The texture will be updated turning pixels black (0 <uint32_t>) or white (1 <uint32_t>)
    */

    *texture = SDL_CreateTexture(*renderer, 
    SDL_PIXELFORMAT_RGBA8888, 
    SDL_TEXTUREACCESS_STREAMING,    // TARGET also works, but STREAMING is preferred for updating as byte-array  
    CC8_GFX_BUFF_WIDTH, 
    CC8_GFX_BUFF_HEIGHT);

    if (!(*texture)) {
        fprintf(stderr, "[GFX] Error creating texture\n");

        return -1;
    }
    
    // Set drawing colour to black
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
    SDL_RenderClear(*renderer);
    SDL_RenderPresent(*renderer);

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

void gfx_render(uint32_t* buffer, SDL_Renderer* renderer, SDL_Texture* texture) 
{
    // update texture from buffer values
    SDL_UpdateTexture(texture, NULL, buffer, CC8_GFX_BUFF_WIDTH * sizeof(uint32_t));

    // Clear screen
    SDL_RenderClear(renderer);

    // Copy updated texture to the rendering target; default target is the window surface
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // move to front-buffer
    SDL_RenderPresent(renderer);

    return;
}