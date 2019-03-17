#ifndef LIFE_SAVING_H
#define LIFE_SAVING_H

#include "field.h"

void createImage(field *f, char *base, int num);

void saveField(field *f, char *filePath);

char *generateFileName(char *base, char *extension, int num);

void *generateGnuplotScript(char *scriptFileName, char *dateFileName, char *pngFileName);

char *createCommand(char *base, char *fileName);

#endif //LIFE_SAVING_H
