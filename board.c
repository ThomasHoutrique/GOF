#include "includes/board.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void init_board(int rows, int cols, Board *board)
{
    board->rows = rows;
    board->cols = cols;
    board->cells = calloc(rows, sizeof(Cell *));
    for (int i = 0; i < rows; i++)
    {
        board->cells[i] = calloc(cols, sizeof(Cell));
    }
}

void randomize_board(Board *board)
{
    srand(time(NULL));
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            int alive = rand() % 5 == 0;
            board->cells[i][j].alive = alive;
        }
    }
}

void save_board_to_file(Board *board)
{
    FILE *file = fopen("board.txt", "w");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            fprintf(file, "%d", board->cells[i][j].alive);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}