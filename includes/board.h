#ifndef BOARD_H
#define BOARD_H
#include "cell.h"

typedef struct
{
    Cell **cells;
    int rows;
    int cols;
} Board;

void init_board(int rows, int cols, Board *board);
void randomize_board(Board *board);
void save_board_to_file();
#endif