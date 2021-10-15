#include "init.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


void initSFlag(sFlag* flag){
    flag->BEQ = 0;
    flag->BNE = 0;
    flag->BLE = 0;
    flag->BGE = 0;
    flag->BL  = 0;
    flag->BG  = 0;
}

void initSCore(sCore* core){
    core->pc = 0;
    for (int i = 0; i < 15; i++){
        core->rArray[i] = 0;
    }
    initSFlag(&core->flags);
}

FILE* lireFichier(char* path){
    FILE* fichier = NULL;
    fichier = fopen(path, "r+");
    if (fichier == NULL){
        printf("Impossible d'ouvrir le fichier : %s\n",path);
        exit(EXIT_SUCCESS);
    }
    return fichier;
}

//TODO: test wrong file 
void initSCoreWithValues(char* path, sCore* core){
    FILE* fp = lireFichier(path);
    char* pointerLine = NULL;
    char * endPtr;
    size_t len = 0;
    int registerNumber;
    int registerValue;
    ssize_t read;

    while ((read = getline(&pointerLine, &len, fp)) != -1){
        while (*pointerLine != '\n' && *pointerLine != '\0' && *pointerLine != EOF ){
            if (*pointerLine != 'R' || *pointerLine != 'r'){
                pointerLine++;
                registerNumber = strtol( pointerLine, &endPtr, 10 ); 
                if (endPtr == pointerLine){
                    printf("Wrong register number in init file  : %s\n",path);
                    exit(EXIT_SUCCESS);              
                }
                if (registerNumber < 0 || registerNumber > 15 ){
                    printf("Wrong register name in init file  : %s\n",path);
                    exit(EXIT_SUCCESS);
                } 
                while (*pointerLine != '\n' && *pointerLine != '\0' && *pointerLine != '0'){
                    pointerLine ++;
                }
                registerValue = strtol( pointerLine, &endPtr, 16 ); 
                if (endPtr == pointerLine){
                    printf("Wrong register value in init file  : %s\n",path);
                    exit(EXIT_SUCCESS);              
                }else{
                    core->rArray[registerNumber + 1] = registerValue;
                    pointerLine = endPtr;
                    registerNumber = -1;
                }
            }
            pointerLine++;
        }

    }
    fclose(fp);
}

int countLine(char* path){
    FILE* fp = lireFichier(path);
    char* pointerLine = NULL;
    size_t len = 0;
    ssize_t read;
    int lineNumber = 0;
    while ((read = getline(&pointerLine, &len, fp)) != -1){
        lineNumber ++;
    }
    return lineNumber;
}




int32_t* initInstructionArray(char* path){
    FILE* fp = lireFichier(path);
    int32_t* instructArray = malloc(countLine(path) * sizeof(int32_t));
    
    char * endPtr;
    char* pointerLine = NULL;
    size_t len = 0;
    ssize_t read;
    int lenLine;
    int i = 0;

    while ((read = getline(&pointerLine, &len, fp)) != -1){
        lenLine = strlen(pointerLine);
        if ( lenLine != 9 && lenLine != 8){
            printf("Wrong instruction length\n");
            exit(EXIT_SUCCESS);    
        }
        printf("%s\n", pointerLine);
        instructArray[i] = strtol( pointerLine, &endPtr, 16 );
        if (endPtr == pointerLine){
            printf("Wrong instrcution format\n");
            exit(EXIT_SUCCESS); 
        }
        i++;
    }
    return instructArray;
}