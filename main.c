#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cell.h"
#include "field.h"
#include "game.h"
#include "test.h"
#include "imgCreation.h"

int main(int argc, char **argv) {

    srand(time(NULL));
    config *conf = createConfig(argc, argv);
    printf("%d %d\n", conf->sizeX, conf->sizeY);
    printf("%d %d\n", conf->iterationsNum, conf->aliveCellsNum);
    printf("%d %d\n", conf->mode, conf->savingFreq);
    printf("%s\n", conf->gRules->countingNeighboursMethod);
    list *tmp = conf->gRules->liveToLiveNums;
    while (tmp->next != NULL) {
        printf("%d\n", tmp->value);
        tmp = tmp->next;
    }
    printf("%d\n", tmp->value);
    destroyConfig(conf);

    return 0;
}
