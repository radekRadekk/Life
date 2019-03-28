#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cell.h"
#include "field.h"
#include "game.h"
#include "test.h"
#include "imgCreation.h"
#include "fieldToOrFromTxt.h"

int main(int argc, char **argv) {

    srand(time(NULL));
    config *conf = createConfig(argc, argv);
    printf("%d %d %d %d %d %s\n", conf->sizeX, conf->sizeY, conf->aliveCellsNum, conf->iterationsNum, conf->mode,conf->gRules->countingNeighboursMethod);
    playGame(conf);
    destroyConfig(conf);
    return 0;
}
