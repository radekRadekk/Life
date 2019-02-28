#include <stdlib.h>
#include "cell.h"

cell *createCell(int x, int y) {
    cell *newCell = malloc(sizeof(cell *));
    newCell->x = x;
    newCell->y = y;
    newCell->isAlive = 0;
    return newCell;
}

void destroyCell(cell *c) {
    free(c);
}
