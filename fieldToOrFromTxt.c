#include <stdio.h>
#include "fieldToOrFromTxt.h"

void saveField(field *f, char *filePath) {
    FILE *file = fopen(filePath, "w");
    for (int y = 0; y < f->sizeY; y++) {
        for (int x = 0; x < f->sizeX; x++) {
            fprintf(file, "%d", getCell(f, x, y)->isAlive);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

//test
field *readField(char *filePath) {
    int sizeX = 0;
    int sizeY = 0;
    FILE *file = fopen(filePath, "r");

    if (file != NULL) {
        while (getc(file) != '\n')
            sizeX++;
        fclose(file);
    }

    file = fopen(filePath, "r");
    int signsNum = 0;

    if (file != NULL) {
        while (getc(file) != EOF)
            signsNum++;
        fclose(file);
    }

    if (sizeX == 0 || signsNum == 0) {
        return createField(1, 1);
    }

    sizeY = signsNum / sizeX;
    field *f = createField(sizeX, sizeY);
    file = fopen(filePath, "r");

    char sign = getc(file);

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            if (sign == '1')
                getCell(f, x, y)->isAlive = 1;
            sign = getc(file);
        }
    }

    fclose(file);

    return f;
}