#include "includes/game.h"
#include "includes/board.h"
#include "includes/generation.h"

void next_generation(Game *game)
{
    Board *current_board = game->current_generation->board;
    Board *new_board = malloc(sizeof(Board));
    init_board(current_board->rows, current_board->cols, new_board);

    // Define the mask for the neighbours
    int mask[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < new_board->rows; i++)
    {
        for (int j = 0; j < new_board->cols; j++)
        {
            int alive = current_board->cells[i][j].alive;
            int neighbors = 0;

            // Use the mask to check for neighbours
            for (int m = 0; m < 8; m++)
            {
                int k = i + mask[m][0];
                int l = j + mask[m][1];

                if (k < 0 || k >= current_board->rows || l < 0 || l >= current_board->cols)
                {
                    continue;
                }
                if (current_board->cells[k][l].alive)
                {
                    neighbors++;
                }
            }

            if (alive && (neighbors < 2 || neighbors > 3))
            {
                new_board->cells[i][j].next = 0;
            }
            else if (!alive && neighbors == 3)
            {
                new_board->cells[i][j].next = 1;
            }
            else
            {
                new_board->cells[i][j].next = alive;
            }
        }
    }

    for (int i = 0; i < new_board->rows; i++)
    {
        for (int j = 0; j < new_board->cols; j++)
        {
            new_board->cells[i][j].alive = new_board->cells[i][j].next;
        }
    }

    Generation *new_gen = malloc(sizeof(Generation));
    new_gen->board = new_board;
    new_gen->prev = game->current_generation;
    new_gen->next = NULL;

    game->current_generation->next = new_gen;
    game->current_generation = new_gen;
}

void prev_generation(Game *game)
{
    if (game->current_generation->prev != NULL)
    {
        game->current_generation = game->current_generation->prev;
    }
}