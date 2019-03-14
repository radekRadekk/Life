#include <stdio.h>
#include "cell.h"
#include "field.h"
#include "game.h"
#include "test.h"

int main(int argc, char **argv) {
    // test();
//    field *testFieldConfig = createField(3, 3);
//    getCell(testFieldConfig, 1, 0)->isAlive = 1;
//    getCell(testFieldConfig, 1, 1)->isAlive = 1;
//    getCell(testFieldConfig, 1, 2)->isAlive = 1;
//    countNeighbours(testFieldConfig, "MOORE");
//    printf("sasiedzi\n");
//    for (int y = 0; y < testFieldConfig->sizeX; y++) {
//        for (int x = 0; x < testFieldConfig->sizeY; x++) {
//            printf("%d", getCell(testFieldConfig, x, y)->neighboursNum);
//        }
//        printf("\n");
//    }
//    printf("\n================================================================\n");
//
//
//    config *testConfig = createConfig(argc, argv);
//    testConfig->iterationsNum = 10;
//    printf("test config contains live to live\n");
//    printf("%d\n", contains(testConfig->gRules->liveToLiveNums, 2));
//    printf("%d\n", contains(testConfig->gRules->liveToLiveNums, 3));
//    printf("test config contains dead to live\n");
//    printf("%d\n", contains(testConfig->gRules->deadToLiveNums, 3));
//    playGame(testFieldConfig, testConfig);
//    destroyConfig(testConfig);
//    destroyField(testFieldConfig);

    printf("%d\n", isGoodPattern("111121/2"));
    return 0;
}
