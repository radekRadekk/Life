#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include "game.h"
#include "field.h"
#include "imgCreation.h"
#include "fieldToOrFromTxt.h"


//test
void setRandomCellsAlive(field *f, int num) {
    int coordsX[num];
    int coordsY[num];
    int drawnNum = 0;

    while (drawnNum < num) {
        int tmpX = rand() % f->sizeX;
        int tmpY = rand() % f->sizeY;

        int isUnique = 1;
        for (int i = 0; i < drawnNum; i++) {
            if (coordsX[i] == tmpX && coordsY[i] == tmpY) {
                isUnique = 0;
                break;
            }
        }

        if (isUnique == 1) {
            coordsX[drawnNum] = tmpX;
            coordsY[drawnNum] = tmpY;
            drawnNum++;
        }
    }

    for (int i = 0; i < num; i++) {
        getCell(f, coordsX[i], coordsY[i])->isAlive = 1;
    }
}

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
void playGame(config *c) {
    int iterNum = 0;
    field *f;
    if (c->mode == 1) {
        f = readField("/home/radek/Pulpit/work/fileName");                                  // write save file's name
    }
    if (c->mode == 2 || isAnyAlive(f) == 0) {
        f = createField(c->sizeX, c->sizeY);
        setRandomCellsAlive(f, c->aliveCellsNum);
    }

    while (isAnyAlive(f) == 1 && iterNum < c->iterationsNum) {
        doGeneration(f, c->gRules);
        if (iterNum % ((int) pow(c->savingFreq, -1)) == 0) {
            createImage(f, "picture", iterNum);
        }
        iterNum++;
    }

    saveField(f, "fileName");                                       //write save file's name
    destroyField(f);
}