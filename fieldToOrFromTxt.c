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

field *readField(char *filePath){

}