#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

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

/* SDL context initialiser */
int8_t gfx_initialise(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** texture, uint16_t width, uint16_t height);

/* Delete SDL context */
void gfx_destroy(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture);


#endif // GRAPHICS_H