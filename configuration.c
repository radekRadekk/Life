#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "configuration.h"

list *createList(int num) {
    list *newList = malloc(sizeof(*newList));
    newList->value = num;
    newList->next = NULL;
    return newList;
}

void destroyList(list *l) {
    while (l != NULL) {
        list *current = l;
        l = l->next;
        free(current);
    }
    free(l);
}

void add(list *l, int num) {
    if (l == NULL) {
        l = createList(num);
    } else {
        list *current = l;
        while (current->next != NULL)
            current = current->next;
        current->next = createList(num);
    }
}

// 1 - true, 0 - false
int contains(list *l, int num) {
    list *iter = l;
    while (iter->next != NULL) {
        if (iter->value == num)
            return 1;
        iter = iter->next;
    }
    if (iter->value == num)
        return 1;
    return 0;
}

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
    return isGood;
}

gameRules *createGameRules(char *rulesPattern, char *countingNeighboursMethod) {
    char *DEFAULT_PATTERN = "23/3";
    int i = 0;
    gameRules *gRules = malloc(sizeof(*gRules));
    gRules->liveToLiveNums = createList(-1);                                //dodaję minus jedynki, bo mi się krzaczyło
    gRules->deadToLiveNums = createList(-1);                                //coś z listą, a tak działa
    gRules->countingNeighboursMethod = countingNeighboursMethod;            //no i nie można mieć -1 sąsiada, więc nic
    //nie zaburzy
    char *pattern = rulesPattern;                                           //!!Potem usuń koomentarz!!
    if (isGoodPattern(pattern) == 0)
        pattern = DEFAULT_PATTERN;

    while (pattern[i] != '/') {
        char *substring = malloc(2);
        substring[0] = pattern[i];
        substring[1] = '\0';
        add(gRules->liveToLiveNums, atoi(substring));
        i++;
        free(substring);
    }
    i++;
    while (pattern[i] != '\0') {
        char *substring = malloc(2);
        substring[0] = pattern[i];
        substring[1] = '\0';
        add(gRules->deadToLiveNums, atoi(substring));
        i++;
        free(substring);
    }

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
    char *tmpGameRulesPattern = "000";
    char *tmpMethod = "000";

    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-x") && atoi(argv[i + 1]) > 0) {
            newConfig->sizeX = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-y") && atoi(argv[i + 1]) > 0) {
            newConfig->sizeY = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-a") && atoi(argv[i + 1]) > 0) {
            tmpAliveCellsNum = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-i") && atoi(argv[i + 1]) > 0) {
            newConfig->iterationsNum = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-f") && atoi(argv[i + 1]) > 0) {
            tmpSavingFreq = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-ff") && atoi(argv[i + 1]) > 0) {
            tmpSavingFreqNoLimit = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-r")) {
            tmpGameRulesPattern = argv[i + 1];
        } else if (strcmp(argv[i], "-me")) {
            tmpMethod = argv[i + 1];
        } else if (strcmp(argv[i], "-mo") && atoi(argv[i + 1]) > 0) {
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