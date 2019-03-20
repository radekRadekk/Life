#include "imgCreation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void createImage(field *f, char *base, int num) {
    char *dataFileName = generateFileName(base, ".txt", num);
    char *pngFileName = generateFileName(base, ".png", num);
    char *gnuplotScriptFileName = generateFileName(base, ".gpi", num);

    saveField(f, dataFileName);
    generateGnuplotScript(gnuplotScriptFileName, dataFileName, pngFileName);

    char *commandExe = createCommand("gnuplot ", gnuplotScriptFileName);
    char *commandChmod = createCommand("chmod -x ", gnuplotScriptFileName);

    system(commandChmod);
    system(commandExe);
    system("rm *.txt");
    system("rm *.gpi");

    free(dataFileName);
    free(pngFileName);
    free(gnuplotScriptFileName);
    free(commandChmod);
    free(commandExe);
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

void generateGnuplotScript(char *scriptFileName, char *dateFileName, char *pngFileName) {
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

char *createCommand(char *base, char *fileName) {
    char *command = malloc(strlen(fileName) + strlen(base) + 1);
    int commandIter = 0;
    for (int i = 0; i < strlen(base); i++)
        command[commandIter++] = base[i];
    for (int i = 0; i < strlen(fileName); i++)
        command[commandIter++] = fileName[i];
    command[commandIter] = '\0';

    return command;
}