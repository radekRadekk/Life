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
    config *conf = createConfig(argc,argv);
    playGame(conf);
    destroyConfig(conf);
//
//    field *field = readField("/home/radek/Pulpit/work/fileName");
//    printField(field);

    return 0;
}
