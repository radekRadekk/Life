
#ifndef LIFE_FIELD_H
#define LIFE_FIELD_H

#include "cell.h"



typedef struct _field {
    int sizeX;
    int sizeY;
    cell **gameField;
} field;

field *createField(int sizeX, int sizeY);

cell *getCell(field *, int x, int y);

void destroyField(field *);

int areGoodCoords(int x, int y, field *);

void countNeighboursMoore(cell *, field *);

void countNeighboursNeumann(cell *, field *);

void countNeighbours(field *, char *);


#endif //LIFE_FIELD_H

