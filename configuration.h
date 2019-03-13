#ifndef LIFE_CONFIGURATION_H
#define LIFE_CONFIGURATION_H

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

typedef struct _config {
//    -x    field size X
//    -y    field size Y
//    -a    start number of alive cells
//    -i    number of maximum games's iterations
//    -f    frequency of saving the field with limit to be less than sqrt(iterations number)
//    -ff   frequency of saving the field without limits
//    -r    game rules (pattern ddd/ddd)
//    -me   counting neighbourhood method
//    -mo   mode of game:   1 - load last field; 2 - start
    int sizeX;
    int sizeY;
    int aliveCellsNum;
    int iterationsNum;
    int savingFreq;
    gameRules *gRules;
    int mode;
} config;

config *createConfig(int argc, char **argv);

void destroyConfig(config *c);

#endif //LIFE_CONFIGURATION_H
