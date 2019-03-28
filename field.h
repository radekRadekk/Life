#ifndef LIFE_FIELD_H
#define LIFE_FIELD_H

#include "cell.h"

typedef struct _field {
    unsigned short int sizeX;
    unsigned short int sizeY;
    cell **gameField;
} field;

field *createField(unsigned short int sizeX, unsigned short int sizeY);

cell *getCell(field *, int x, int y);

void destroyField(field *);

int areGoodCoords(int x, int y, field *);

void countNeighboursMoore(cell *, field *);

void countNeighboursNeumann(cell *, field *);

void countNeighbours(field *, char *);

int isAnyAlive(field *);

void printField(field *f);

#endif //LIFE_FIELD_H

