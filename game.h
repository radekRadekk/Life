
#ifndef LIFE_GAME_H
#define LIFE_GAME_H

#include "field.h"
#include "configuration.h"

void changeCellState(cell *, gameRules *);

void doGeneration(field *, gameRules *);

void playGame(field *, config *);

#endif //LIFE_GAME_H

