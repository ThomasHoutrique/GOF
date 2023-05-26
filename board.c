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

void load_board(Board *board)
{
    FILE *file = fopen("board.txt", "r");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    int rows = 0, cols = 0;
    char ch;

    // Récupération de la taille du fichier
    while (!feof(file))
    {
        ch = fgetc(file);
        if (ch == '\n')
        {
            rows++;
        }
        else if (ch == ' ' && rows == 0)
        {
            cols++;
        }
    }
    cols++; // Ajout du dernier espace

    // Vérification de la taille du fichier
    if (rows != board->rows || cols != board->cols)
    {
        printf("Erreur: la taille du fichier ne correspond pas à la taille du tableau\n");
        printf("Taille du fichier: %d x %d\n", rows, cols);
        printf("Taille du tableau: %d x %d\n", board->rows, board->cols);
        exit(1);
    }

    rewind(file);

    // Affectation des valeurs
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!fscanf(file, "%d", &board->cells[i][j].alive))
            {
                break;
            }
        }
    }

    fclose(file);
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