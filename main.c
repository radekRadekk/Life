#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "field.h"
#include "game.h"
#include "test.h"
#include "imgCreation.h"

int main(int argc, char **argv) {

    config *conf = createConfig(argc, argv);
    playGame(conf);
    destroyConfig(conf);

    return 0;
}
