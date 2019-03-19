
#ifndef LIFE_GAME_H
#define LIFE_GAME_H

#include "field.h"
#include "configuration.h"

void setRandomCellsAlive(field *f, int num);

void changeCellState(cell *, gameRules *);

void doGeneration(field *, gameRules *);

void playGame(config *);

#endif //LIFE_GAME_H

