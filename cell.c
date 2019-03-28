#include <stdlib.h>
#include "cell.h"

cell *createCell(unsigned short int x, unsigned short int y) {
    cell *newCell = malloc(sizeof(*newCell));
    newCell->x = x;
    newCell->y = y;
    newCell->isAlive = 0;
    return newCell;
}

void destroyCell(cell *c) {
    free(c);
}
