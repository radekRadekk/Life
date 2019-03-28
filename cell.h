
#ifndef LIFE_CELL_H
#define LIFE_CELL_H

typedef struct _cell {
    unsigned short int x;
    unsigned short int y;
    unsigned short int isAlive;
    unsigned short int neighboursNum;
} cell;

cell *createCell(unsigned short int x, unsigned short int y);

void destroyCell(cell *c);


#endif
