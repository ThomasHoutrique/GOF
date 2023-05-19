#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "includes/game.h"
#include "includes/board.h"
#include "includes/gui.h"

void init_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Impossible d'initialiser SDL: %s", SDL_GetError());
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("Impossible d'initialiser SDL TTF: %s", SDL_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("Erreur lors de l'initialisation du son : %s", Mix_GetError());
    }
}

void init_gui_components(GUI *gui, int rows, int cols)
{
    init_sdl();

    gui->window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cols * 20, rows * 20 + 50, SDL_WINDOW_SHOWN);
    if (!gui->window)
    {
        SDL_Log("Erreur lors de la creation de la fenetre : %s", SDL_GetError());
    }

    gui->renderer = SDL_CreateRenderer(gui->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(gui->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (!gui->renderer)
    {
        SDL_Log("Erreur lors de la creation du renderer : %s", SDL_GetError());
    }

    gui->font = TTF_OpenFont("./assets/fonts/inter.ttf", 24);
    if (!gui->font)
    {
        SDL_Log("Erreur lors du chargement de la police : %s", SDL_GetError());
    }

    gui->BackgroundMusic = Mix_LoadMUS("./assets/sounds/background.wav");
    if (!gui->BackgroundMusic)
    {
        SDL_Log("Erreur lors du chargement de la musique de fond : %s", Mix_GetError());
    }

    gui->NextGenerationSound = Mix_LoadWAV("./assets/sounds/next.wav");
    if (!gui->NextGenerationSound)
    {
        SDL_Log("Erreur lors du chargement du son pour la generation suivante : %s", Mix_GetError());
    }

    gui->PreviousGenerationSound = Mix_LoadWAV("./assets/sounds/previous.wav");
    if (!gui->PreviousGenerationSound)
    {
        SDL_Log("Erreur lors du chargement du son pour la generation precedente : %s", Mix_GetError());
    }

    gui->image_surface = IMG_Load("./assets/images/controller.png");
    if (!gui->image_surface)
    {
        SDL_Log("Erreur lors du chargement de l'image du controller : %s", SDL_GetError());
    }
    gui->image_texture = SDL_CreateTextureFromSurface(gui->renderer, gui->image_surface);
    if (!gui->image_texture)
    {
        SDL_Log("Erreur lors de la creation de la texture de l'image du controller : %s", SDL_GetError());
    }
}

void render_text(SDL_Renderer *renderer, const char *text, int x, int y, TTF_Font *font, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void display_board(Board *board, SDL_Renderer *renderer, TTF_Font *font, int generation, SDL_Texture *image_texture)
{
    SDL_SetRenderDrawColor(renderer, 131, 56, 236, 255);
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            SDL_Rect rect = {j * 20, i * 20, 20, 20};
            if (board->cells[i][j].alive)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 130, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 131, 56, 236, 255);
            }
            else
            {
                SDL_RenderFillRect(renderer, &rect);
            }
            SDL_SetRenderDrawColor(renderer, 82, 14, 177, 255);
            SDL_RenderDrawRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 131, 56, 236, 255);
        }
    }

    char gen_text[64];
    sprintf(gen_text, "Generation: %d", generation);
    SDL_Color white = {255, 255, 255, 255};
    // Add dark purple box to the bottom of the screen to display the generation number
    SDL_Rect rect = {0, board->rows * 20, board->cols * 20, 50};
    SDL_SetRenderDrawColor(renderer, 82, 14, 177, 255);
    SDL_RenderFillRect(renderer, &rect);
    // Render the text at the bottom of the screen 50 pixels from the left
    render_text(renderer, "Utilisez les fleches pour naviguer", 60, board->rows * 20 + 20, font, white);
    SDL_Rect image_rect = {0, board->rows * 20, 50, 50};
    SDL_RenderCopy(renderer, image_texture, NULL, &image_rect);
    render_text(renderer, gen_text, 500, board->rows * 20 + 20, font, white);
    SDL_RenderPresent(renderer);
}

void destroy_gui_components(GUI *gui)
{
    SDL_DestroyRenderer(gui->renderer);
    SDL_DestroyWindow(gui->window);
    TTF_CloseFont(gui->font);
    Mix_FreeMusic(gui->BackgroundMusic);
    Mix_FreeChunk(gui->NextGenerationSound);
    Mix_FreeChunk(gui->PreviousGenerationSound);
    SDL_FreeSurface(gui->image_surface);
    SDL_DestroyTexture(gui->image_texture);
    TTF_Quit();
    SDL_Quit();
}