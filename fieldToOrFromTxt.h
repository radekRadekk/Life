#ifndef LIFE_FIELDTOORFROMTXT_H
#define LIFE_FIELDTOORFROMTXT_H

#include "field.h"

void saveField(field *f, char *filePath);

field *readField(char *filePath);

#endif //LIFE_FIELDTOORFROMTXT_H
