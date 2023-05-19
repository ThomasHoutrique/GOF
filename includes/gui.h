#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "board.h"

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *image_surface;
    SDL_Texture *image_texture;
    TTF_Font *font;

    // Create 3 music channels
    Mix_Music *BackgroundMusic;
    Mix_Chunk *NextGenerationSound;
    Mix_Chunk *PreviousGenerationSound;
} GUI;

void render_text(SDL_Renderer *renderer, const char *text, int x, int y, TTF_Font *font, SDL_Color color);
void display_board(Board *board, SDL_Renderer *renderer, TTF_Font *font, int generation, SDL_Texture *image_texture);
void init_sdl();
void init_gui_components(GUI *gui, int rows, int cols);
void destroy_gui_components(GUI *gui);
#endif