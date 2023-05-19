#ifndef GENERATION_H
#define GENERATION_H

#include "board.h"

typedef struct Generation
{
    Board *board;
    struct Generation *prev;
    struct Generation *next;
} Generation;

#endif