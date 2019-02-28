
#ifndef LIFE_CELL_H
#define LIFE_CELL_H

typedef struct _cell {
    int x;
    int y;
    int isAlive;
    int neighboursNum;
} cell;

cell *createCell(int x, int y);

void destroyCell(cell *c);


#endif
