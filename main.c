#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "includes/board.h"
#include "includes/game.h"
#include "includes/cell.h"
#include "includes/generation.h"
#include "includes/gui.h"

int main(int argc, char *argv[])
{

    // Check si le nombre d'arguments est correct (le nombre de lignes et de colonnes)
    if (argc != 3)
    {
        printf("Usage: ./game_of_life rows cols\n");
        return 1;
    }
    // Initialisation des lignes et des colonnes
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // Initialisation du jeu
    Game *game = malloc(sizeof(Game));

    // Initialisation de la GUI
    GUI *gui = malloc(sizeof(GUI));
    init_sdl();
    init_gui_components(gui, rows, cols);

    // Jouer la musique de fond
    Mix_PlayMusic(gui->BackgroundMusic, -1);

    // Création de la table de jeu
    Board *board = malloc(sizeof(Board));
    init_board(rows, cols, board);

    // Création de la première génération
    Generation *first_gen = malloc(sizeof(Generation));
    first_gen->board = board;
    first_gen->prev = NULL;
    first_gen->next = NULL;

    // Application de la première génération au jeu
    game->current_generation = first_gen;
    int generation_counter = 1;

    // Chargement de la table de jeu depuis le fichier
    load_board(board);
    display_board(game->current_generation->board, gui->renderer, gui->font, generation_counter, gui->image_texture);

    // Si on appuie sur la flèche droite, on passe à la génération suivante
    // Si on appuie sur la flèche gauche, on passe à la génération précédente
    // Si on appuie sur la touche Echap, on quitte le jeu
    int quit = 0;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    next_generation(game);
                    generation_counter++;
                    Mix_PlayChannel(-1, gui->NextGenerationSound, 0);
                    display_board(game->current_generation->board, gui->renderer, gui->font, generation_counter, gui->image_texture);
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    prev_generation(game);
                    if (generation_counter > 1)
                    {
                        generation_counter--;
                        Mix_PlayChannel(-1, gui->PreviousGenerationSound, 0);
                        display_board(game->current_generation->board, gui->renderer, gui->font, generation_counter, gui->image_texture);
                    }
                }
                if (event.key.keysym.sym == SDLK_UP)
                {
                    save_board_to_file(game->current_generation->board);
                }
            }
        }
        SDL_Delay(10);
    }

    // Cloture de la fenêtre et de tout ce qui est lié à SDL pour éviter les fuites de mémoire
    destroy_gui_components(gui);
}
