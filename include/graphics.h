#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>


/* SDL context initialiser */
int8_t gfx_initialise(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** texture, uint16_t width, uint16_t height);

/* Delete SDL context */
void gfx_destroy(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture);

/* Render to screen */
void render(uint32_t* buffer, SDL_Renderer* renderer, SDL_Texture* texture);

#endif // GRAPHICS_H