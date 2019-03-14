#ifndef LIFE_SAVING_H
#define LIFE_SAVING_H

#include "field.h"

void saveField(field *f, char *filePath);

char *generateFileName(char *base, int num);

#endif //LIFE_SAVING_H
