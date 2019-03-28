#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "configuration.h"
#include "list.h"


// 1 - true, 0 - false
int isGoodPattern(char *rulesPattern) {
    char *iter = rulesPattern;
    int wasSlash = 0;
    int isGood = 1;
    int i = 0;

    while (iter[i] != '\0') {
        if (isdigit(iter[i]) == 0 && iter[i] != '/') {
            isGood = 0;
            break;
        }
        if (iter[i] == '/' && wasSlash == 1) {
            isGood = 0;
            break;
        }
        if (iter[i] == '/' && wasSlash == 0)
            wasSlash = 1;
        i++;
    }
    if (iter[i - 1] == '/')
        isGood = 0;
    if (iter[0] == '/')
        isGood = 0;
    if (i > 1 && wasSlash == 0)
        isGood = 0;

    return isGood;
}

void definePatternNums(char *pattern, list *previous, list *next) {
    int i = 0;
    while (pattern[i] != '/') {
        add(previous, pattern[i++] - '0');
    }
    i++;
    while (pattern[i] != '\0')
        add(next, pattern[i++] - '0');
}

gameRules *createDefaultGameRules() {
    gameRules *newGameRules = malloc(sizeof(*newGameRules));
    newGameRules->countingNeighboursMethod = "MOORE";
    newGameRules->liveToLiveNums = createList(10);
    newGameRules->deadToLiveNums = createList(10);
    definePatternNums("23/3", newGameRules->liveToLiveNums, newGameRules->deadToLiveNums);
    return newGameRules;
}

void destroyGameRules(gameRules *gRules) {
    destroyList(gRules->liveToLiveNums);
    destroyList(gRules->deadToLiveNums);
    free(gRules);
}

config *createDefaultConfig() {
    config *newConfig = malloc(sizeof(*newConfig));
    newConfig->sizeX = 100;
    newConfig->sizeY = 100;
    newConfig->aliveCellsNum = 3333;
    newConfig->iterationsNum = 100;
    newConfig->savingFreq = 0.1;
    newConfig->mode = 2;
    newConfig->gRules = createDefaultGameRules();
    return newConfig;
}

config *createConfig(int argc, char **argv) {
    config *newConfig = createDefaultConfig();
    int tmpAliveCellsNum = -1;
    char *tmpGameRulesPattern = NULL;
    int tmpMode = -1;

    for (int i = 1; i < argc - 1; i++) {
        if ((strcmp(argv[i], "-x") == 0) && (atoi(argv[i + 1]) > 0)) {
            newConfig->sizeX = atoi(argv[i + 1]);
        } else if ((strcmp(argv[i], "-y") == 0) && (atoi(argv[i + 1]) > 0)) {
            newConfig->sizeY = atoi(argv[i + 1]);
        } else if ((strcmp(argv[i], "-a") == 0) && (atoi(argv[i + 1]) > 0)) {
            tmpAliveCellsNum = atoi(argv[i + 1]);
        } else if ((strcmp(argv[i], "-i") == 0) && (atoi(argv[i + 1]) > 0)) {
            newConfig->iterationsNum = atoi(argv[i + 1]);
        } else if ((strcmp(argv[i], "-f") == 0) && (atof(argv[i + 1]) > 0) && (atof(argv[i + 1]) <= 1)) {
            newConfig->savingFreq = atof(argv[i + 1]);
        } else if (strcmp(argv[i], "-r") == 0) {
            tmpGameRulesPattern = argv[i + 1];
        } else if ((strcmp(argv[i], "-me") == 0) &&
                   ((strcmp(argv[i], "NEUMANN") == 0) || (strcmp(argv[i], "MOORE") == 0))) {
            free(newConfig->gRules->countingNeighboursMethod);
            newConfig->gRules->countingNeighboursMethod = argv[i + 1];
        } else if ((strcmp(argv[i], "-mo") == 0) && (atoi(argv[i + 1]) > 0)) {
            tmpMode = atoi(argv[i + 1]);
        }
    }

    if ((tmpAliveCellsNum <= newConfig->sizeX * newConfig->sizeY) && tmpAliveCellsNum != -1 &&
        tmpAliveCellsNum <= (newConfig->sizeX * newConfig->sizeY)) {
        newConfig->aliveCellsNum = tmpAliveCellsNum;
    } else {
        newConfig->aliveCellsNum = (int) (newConfig->sizeX * newConfig->sizeY * 0.33);
    }
    if (tmpMode == 1 || tmpMode == 2) {
        newConfig->mode = tmpMode;
    }
    if (tmpGameRulesPattern != NULL) {
        if (isGoodPattern(tmpGameRulesPattern) == 1) {
            destroyList(newConfig->gRules->liveToLiveNums);
            destroyList(newConfig->gRules->deadToLiveNums);
            newConfig->gRules->liveToLiveNums = createList(10);
            newConfig->gRules->deadToLiveNums = createList(10);
            definePatternNums(tmpGameRulesPattern, newConfig->gRules->liveToLiveNums,
                              newConfig->gRules->deadToLiveNums);
        }
    }

    return newConfig;
}

void destroyConfig(config *c) {
    destroyGameRules(c->gRules);
    free(c);
}