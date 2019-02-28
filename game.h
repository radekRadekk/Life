
#ifndef LIFE_GAME_H
#define LIFE_GAME_H

#include "field.h"

typedef struct _list {
    int value;
    struct _list *next;
} list;

list *createList(int num);

void destroyList(list *);

void add(list *, int num);

int contains(list *l, int num);

typedef struct _gameRules {
    char *countingNeighboursMethod;         //możesz zmienić nazwę, bo ciut długa
    list *liveToLiveNums;
    list *deadToLiveNums;
} gameRules;

int isGoodPattern(char *);

gameRules *createGameRules(char *, char *);

void destroyGameRules(gameRules *);

void changeCellSatate(cell *, gameRules *);

void doGeneration(field *, gameRules *);

void playGame(field *);

#endif //LIFE_GAME_H

