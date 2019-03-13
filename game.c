#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "game.h"
#include "field.h"

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

//do unit test
void changeCellSatate(cell *c, gameRules *gRules) {
    if (c->isAlive == 1 && contains(gRules->liveToLiveNums, c->neighboursNum) == 0)
        c->isAlive = 0;
    else if (c->isAlive == 0 && contains(gRules->deadToLiveNums, c->neighboursNum) == 1)
        c->isAlive = 1;
}

//do unit test
void doGeneration(field *f, gameRules *gRules) {
    countNeighbours(f, gRules->countingNeighboursMethod);
    for (int x = 0; x < f->sizeX; x++)
        for (int y = 0; y < f->sizeY; y++)
            changeCellSatate(getCell(f, x, y), gRules);
}

