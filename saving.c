#include "saving.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void createSave(field *f, char *base, int num) {
    char *dataFileName = generateFileName(base, ".txt", num);
    char *pngFileName = generateFileName(base, ".png", num);
    char *gnuplotScriptFileName = generateFileName(base, ".gpi", num);
    char *bashScriptFileName = generateFileName(base, ".sh", num);

    saveField(f, dataFileName);
    generateGnuplotScript(bashScriptFileName, dataFileName, pngFileName);
    generateBashScript(bashScriptFileName, gnuplotScriptFileName);

    char *command = malloc(strlen(bashScriptFileName) + 3);
    int commandIter = 0;
    command[commandIter++] = '.';
    command[commandIter++] = '/';
    for (int i = 0; i < strlen(bashScriptFileName); i++)
        command[commandIter++] = bashScriptFileName[i];
    command[commandIter] = '\0';

    system(command);
    system("rm *.sh");
    system("rm *.txt");
    system("rm *.gpi");

    free(dataFileName);
    free(pngFileName);
    free(gnuplotScriptFileName);
    free(bashScriptFileName);
    free(command);
}

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

char *generateFileName(char *base, char *extension, int num) {
    int numCopy = num;
    int digitsNum = 0;

    while (numCopy != 0) {
        digitsNum++;
        numCopy /= 10;
    }

    char *numString = malloc(digitsNum + 1);
    sprintf(numString, "%d", num);

    int fileNameLength = strlen(base) + strlen(extension) + strlen(numString);

    char *fileName = malloc(fileNameLength + 1);
    int fileNameIter = 0;

    for (int i = 0; i < strlen(base); i++)
        fileName[fileNameIter++] = base[i];
    for (int i = 0; i < strlen(numString); i++)
        fileName[fileNameIter++] = numString[i];
    for (int i = 0; i < strlen(extension); i++)
        fileName[fileNameIter++] = extension[i];
    fileName[fileNameIter] = '\0';

    free(numString);

    return fileName;
}

void *generateGnuplotScript(char *scriptFileName, char *dateFileName, char *pngFileName) {
    FILE *file = fopen(scriptFileName, "w");
    fprintf(file, "%s\n", "set term pngcairo size 1920,1080 enhanced square");
    fprintf(file, "%s\n", "unset border");
    fprintf(file, "%s\n", "set palette gray");
    fprintf(file, "%s\n", "set xtics nomirror");
    fprintf(file, "%s\n", "set ytics nomirror");
    fprintf(file, "%s\n", "unset xtics");
    fprintf(file, "%s\n", "unset ytics");
    fprintf(file, "%s\n", "unset colorbox");
    fprintf(file, "%s\n", "unset key");
    fprintf(file, "%s\n", "unset tics");
    fprintf(file, "%s\n", "set border");
    fprintf(file, "%s\'%s\'\n", "set output ", pngFileName);
    fprintf(file, "%s\'%s\'%s\n", "plot ", dateFileName, " matrix with image");
    fprintf(file, "%s\n", "set term x11");

    fclose(file);
}

void *generateBashScript(char *scriptFileName, char *gnuplotScriptName) {
    FILE *file = fopen(scriptFileName, "w");
    fprintf(file, "#!/bin/bash\n");
    fprintf(file, "%s%s\n", "$ ./gnuplot ", gnuplotScriptName);
    fclose(file);
}