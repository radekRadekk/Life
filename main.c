#include <stdio.h>
#include "cell.h"
#include "field.h"
#include "game.h"

//w mainie są robocze testy
//test
int main() {
    printf("Hello, World!\n");
    cell *testCell = createCell(0, 0);
    printf("%d\n", testCell->isAlive);
    testCell->isAlive = 1;
    printf("%d\n", testCell->isAlive);
    destroyCell(testCell);

    field *testField = createField(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d\t", getCell(testField, j, i)->isAlive);
        printf("\n");
    }

    getCell(testField, 0, 0)->isAlive = 1;
    getCell(testField, 1, 1)->isAlive = 1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d\t", getCell(testField, j, i)->isAlive);
        printf("\n");
    }


    destroyField(testField);

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

    field *testField2 = createField(3, 3);
    getCell(testField2, 1, 0)->isAlive = 1;
    getCell(testField2, 1, 1)->isAlive = 1;
    getCell(testField2, 0, 1)->isAlive = 1;

    countNeighboursMoore(getCell(testField2, 1, 1), testField2);
    int moore = getCell(testField2, 1, 1)->neighboursNum;
    countNeighboursNeumann(getCell(testField2, 1, 1), testField2);
    int neumann = getCell(testField2, 1, 1)->neighboursNum;
    printf("%d\t%d\n", moore, neumann);

    destroyField(testField2);

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

    list *testList = createList(0);
    add(testList, 1);
    add(testList, 2);
    add(testList, 3);

    list *iter = testList;
    while (iter->next != NULL) {
        printf("%d\n", iter->value);
        iter = iter->next;
    }
    printf("%d\n", iter->value);
    printf("%d\n", contains(testList, 0));
    destroyList(testList);

    //printf("%d\n", isGoodPattern("12a/123"));

    printf("Pattern!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    gameRules *testRules = createGameRules("123/456", "MOORE");

    list *iterLiveToLive = testRules->liveToLiveNums;
    while (iterLiveToLive->next != NULL) {
        printf("%d\n", iterLiveToLive->value);
        iterLiveToLive = iterLiveToLive->next;
    }
    printf("%d\n", iterLiveToLive->value);

    list *iterDeadToLive = testRules->deadToLiveNums;
    while (iterDeadToLive->next != NULL) {
        printf("%d\n", iterDeadToLive->value);
        iterDeadToLive = iterDeadToLive->next;
    }
    printf("%d\n", iterDeadToLive->value);

    destroyGameRules(testRules);


    return 0;
}
