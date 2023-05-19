#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "generation.h"
typedef struct
{
    Generation *current_generation;
} Game;

void next_generation(Game *game);
void prev_generation(Game *game);

#endif