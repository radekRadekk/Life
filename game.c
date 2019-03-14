#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "game.h"
#include "field.h"
#include "saving.h"

void changeCellState(cell *c, gameRules *gRules) {
    if ((c->isAlive == 1) && (contains(gRules->liveToLiveNums, c->neighboursNum) == 0))
        c->isAlive = 0;
    else if ((c->isAlive == 0) && (contains(gRules->deadToLiveNums, c->neighboursNum) == 1))
        c->isAlive = 1;
}

void doGeneration(field *f, gameRules *gRules) {
    countNeighbours(f, gRules->countingNeighboursMethod);
    for (int x = 0; x < f->sizeX; x++)
        for (int y = 0; y < f->sizeY; y++)
            changeCellState(getCell(f, x, y), gRules);
}

// to refractor
void playGame(field *f, config *c) {
    int iterNum = 0;
    int pictureNumber = 1;
    while (isAnyAlive(f) == 1 && iterNum < c->iterationsNum) {
        doGeneration(f, c->gRules);
        if (iterNum % c->savingFreq == 0) {
            createSave(f, "picture", pictureNumber);
            pictureNumber++;
        }
        iterNum++;
    }
}

