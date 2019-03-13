#include <stdlib.h>
#include <string.h>
#include "field.h"
#include "cell.h"

field *createField(int sizeX, int sizeY) {
    field *newField = malloc(sizeof(*newField));
    newField->sizeX = sizeX;
    newField->sizeY = sizeY;
    newField->gameField = malloc(sizeX * sizeY * sizeof(cell *));
    for (int y = 0; y < sizeY; y++)
        for (int x = 0; x < sizeX; x++)
            newField->gameField[sizeX * y + x] = createCell(x, y);

    return newField;
}

cell *getCell(field *field1, int x, int y) {
    return field1->gameField[y * field1->sizeX + x];
}

void destroyField(field *field1) {
    for (int y = 0; y < field1->sizeY; y++)
        for (int x = 0; x < field1->sizeX; x++)
            destroyCell(field1->gameField[field1->sizeX * y + x]);
    free(field1->gameField);
    free(field1);
}

int areGoodCoords(int x, int y, field *f) {
    if (x < 0 || y < 0)
        return 0;
    if (x >= f->sizeX || y >= f->sizeY)
        return 0;
    return 1;
}

void countNeighboursMoore(cell *c, field *f) {
    int cellX = c->x;
    int cellY = c->y;
    int neighboursNum = 0;

    for (int testX = cellX - 1; testX <= cellX + 1; testX++) {
        for (int testY = cellY - 1; testY <= cellY + 1; testY++) {
            if (testX != cellX || testY != cellY)
                if (areGoodCoords(testX, testY, f) == 1)
                    if (getCell(f, testX, testY)->isAlive == 1) {
                        neighboursNum++;
                    }
        }
    }
    c->neighboursNum = neighboursNum;
}

void countNeighboursNeumann(cell *c, field *f) {
    int cellX = c->x;
    int cellY = c->y;
    int neighboursNum = 0;

    if (areGoodCoords(cellX, cellY - 1, f) == 1 && getCell(f, cellX, cellY - 1)->isAlive == 1)
        neighboursNum++;
    if (areGoodCoords(cellX + 1, cellY, f) == 1 && getCell(f, cellX + 1, cellY)->isAlive == 1)
        neighboursNum++;
    if (areGoodCoords(cellX, cellY + 1, f) == 1 && getCell(f, cellX, cellY + 1)->isAlive == 1)
        neighboursNum++;
    if (areGoodCoords(cellX - 1, cellY, f) == 1 && getCell(f, cellX - 1, cellY)->isAlive == 1)
        neighboursNum++;

    c->neighboursNum = neighboursNum;
}

//MOORE method is default
void countNeighbours(field *f, char *method) {
    if (strcmp(method, "NEUMANN") == 0)
        for (int x = 0; x < f->sizeX; x++)
            for (int y = 0; y < f->sizeY; y++)
                countNeighboursNeumann(getCell(f, x, y), f);
    else {
        for (int x = 0; x < f->sizeX; x++)
            for (int y = 0; y < f->sizeY; y++)
                countNeighboursMoore(getCell(f, x, y), f);
    }
}

//  1 - true;   0 - false
int isAnyAlive(field *f) {
    int isAnyAlive = 0;
    for (int x = 0; x < f->sizeX; x++) {
        for (int y = 0; y < f->sizeY; y++) {
            if (getCell(f, x, y)->isAlive == 1) {
                isAnyAlive = 1;
                break;
            }
        }
    }
    return isAnyAlive;
}






