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

gameRules *createGameRules(char *rulesPattern, char *countingNeighboursMethod) {
    char *DEFAULT_PATTERN = "23/3";
    gameRules *gRules = malloc(sizeof(*gRules));
    gRules->liveToLiveNums = createList(-1);
    gRules->deadToLiveNums = createList(-1);
    gRules->countingNeighboursMethod = countingNeighboursMethod;
    char *pattern = rulesPattern;
    if (isGoodPattern(pattern) == 0)
        pattern = DEFAULT_PATTERN;

    definePatternNums(pattern, gRules->liveToLiveNums, gRules->deadToLiveNums);

    return gRules;
}

void destroyGameRules(gameRules *gRules) {
    destroyList(gRules->liveToLiveNums);
    destroyList(gRules->deadToLiveNums);
    free(gRules);
}

config *createConfig(int argc, char **argv) {
    config *newConfig = malloc(sizeof(*newConfig));
    newConfig->sizeX = 100;
    newConfig->sizeY = 100;
    newConfig->aliveCellsNum = 100;
    newConfig->iterationsNum = 100;
    newConfig->savingFreq = /*sqrt(*/newConfig->iterationsNum/*)*/;
    newConfig->mode = 2;
    int tmpAliveCellsNum = 100;
    int tmpSavingFreq = 10;
    int tmpSavingFreqNoLimit = -1;
    int tmpMode = 2;
    char *tmpGameRulesPattern = "xxx";
    char *tmpMethod = "MOORE";

    for (int i = 1; i < argc - 1; i++) {
        if ((strcmp(argv[i], "-x") == 0) && (atoi(argv[i + 1]) > 0)) {
            newConfig->sizeX = atoi(argv[i + 1]);
        } else if ((strcmp(argv[i], "-y") == 0) && (atoi(argv[i + 1]) > 0)) {
            newConfig->sizeY = atoi(argv[i + 1]);
        } else if ((strcmp(argv[i], "-a") == 0) && (atoi(argv[i + 1]) > 0)) {
            tmpAliveCellsNum = atoi(argv[i + 1]);
        } else if ((strcmp(argv[i], "-i") == 0) && (atoi(argv[i + 1]) > 0)) {
            newConfig->iterationsNum = atoi(argv[i + 1]);
        } else if ((strcmp(argv[i], "-f") == 0) && (atoi(argv[i + 1]) > 0)) {
            tmpSavingFreq = atoi(argv[i + 1]);
        } else if ((strcmp(argv[i], "-ff") == 0) && (atoi(argv[i + 1]) > 0)) {
            tmpSavingFreqNoLimit = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-r") == 0) {
            tmpGameRulesPattern = argv[i + 1];
        } else if ((strcmp(argv[i], "-me") == 0)&&(strcmp(argv[i],"NEUMANN")==0)) {
            tmpMethod = argv[i + 1];
        } else if ((strcmp(argv[i], "-mo") == 0) && (atoi(argv[i + 1]) > 0)) {
            tmpMode = atoi(argv[i + 1]);
        }
    }

    if (tmpAliveCellsNum <= 0.5 * newConfig->sizeX * newConfig->sizeY) {
        newConfig->aliveCellsNum = tmpAliveCellsNum;
    }
    if (tmpSavingFreq <= /*(int) sqrt(*/newConfig->iterationsNum)/*)*/ {
        newConfig->savingFreq = tmpSavingFreq;
    }
    if (tmpMode == 1 || tmpMode == 2) {
        newConfig->mode = tmpMode;
    }                                                                                                       //jak coś będzię nie tak z częstotliwośćią to tu szukać
    if (tmpSavingFreqNoLimit < newConfig->iterationsNum && tmpSavingFreqNoLimit != -1) {
        newConfig->savingFreq = tmpSavingFreqNoLimit;
    }
    newConfig->gRules = createGameRules(tmpGameRulesPattern, tmpMethod);

    return newConfig;
}

void destroyConfig(config *c) {
    destroyGameRules(c->gRules);
    free(c);
}