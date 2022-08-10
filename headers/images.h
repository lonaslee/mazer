#ifndef IMAGES_H
#define IMAGES_H

#include <SDL.h>
#include <SDL_image.h>

#include "definitions.h"
#include "maze.h"

/**
 * @brief Sets the pre-declared variable texture pointer to a texture struct.
 *
 * @param renderer the renderer to use
 * @param texture the texture pointer
 * @param fp the file path of the texture to load
 */
#define TEXTURE_FROM_FILE(renderer, texture, fp)                                                                     \
    do {                                                                                                             \
        SDL_Surface *surface = IMG_Load(fp);                                                                         \
        if (surface == NULL) EXIT_ERR("Failed to load image from file: %s\n%s\n", fp, SDL_GetError());               \
        texture = SDL_CreateTextureFromSurface(renderer, surface);                                                   \
        SDL_FreeSurface(surface);                                                                                    \
        if (texture == NULL) PRINT_ERR("Failed to create texture from loaded surface: %s\n%s\n", fp, SDL_GetError()) \
    } while (0);

#define DRAW_TEXTURE(renderer, texture, xpos, ypos)              \
    do {                                                         \
        SDL_Rect rect = {.x = xpos, .y = ypos};                  \
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h); \
        SDL_RenderCopy(renderer, texture, NULL, &rect);          \
    } while (0);

#define DRAW_TEXTURE_WH(renderer, texture, xpos, ypos, width, height)    \
    do {                                                                 \
        SDL_Rect rect = {.x = xpos, .y = ypos, .w = width, .h = height}; \
        SDL_RenderCopy(renderer, texture, NULL, &rect);                  \
    } while (0);

SDL_Texture *load_texture(char *fp);
SDL_Surface *draw_surface(void);
void draw_grid(SDL_Renderer *renderer, Grid *grid);

#endif /* IMAGES_H */