#include "init.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void initSFlag(sFlag* flag){
    flag->CF = 0;
    flag->ZF = 0;
    flag->SF  = 0;
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

/**
 * @brief initialise the register with the <STATE> file value
 * 
 * @param path 
 * @param core 
 */
void initSCoreWithValues(char* path, sCore* core){
    FILE* fp = lireFichier(path);
    char* pointerLine = NULL;
    char * endPtr;
    size_t len = 0;
    int registerNumber;
    int64_t registerValue;
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
                pointerLine++;
                while (*pointerLine != '\n' && *pointerLine != '\0' && *pointerLine != '0'){
                    pointerLine ++;
                }
                registerValue = strtoull( pointerLine, &endPtr, 16 ); 
                if (endPtr == pointerLine){
                    printf("Wrong register value in init file  : %s\n",path);
                    exit(EXIT_SUCCESS);              
                }else{
                    core->rArray[registerNumber] = registerValue;
                    registerValue = 0;  
                    pointerLine = endPtr;
                    registerNumber = -1;
                }
            }
            pointerLine++;
        }
    }
    fclose(fp);
}


/**
 * @brief initialise the instruction array with the <CODE> file values
 * 
 * @param path 
 * @return int32_t* 
 */
int32_t* initInstructionArray(char* path){
    FILE* fp = lireFichier(path);
    fseek(fp, 0, SEEK_END); 
    int size = ftell(fp)/4; 
    fseek(fp, 0, SEEK_SET); 
    int32_t* instructArray = malloc((size) * sizeof(int32_t));    
    char pointerLine[2];
    int i = 0;

    for (int j = 0; j < (size*4); j+= 4){
        instructArray[i] = 0;
        for (int k = 0; k <= 3; k++){
            fgets(pointerLine, 2, (FILE*)fp);
            instructArray[i] += ((unsigned char) pointerLine[0]) * (int)powl(16,(3-k)*2);
        }
        i++;
    }
    fclose(fp);
    return instructArray;
}