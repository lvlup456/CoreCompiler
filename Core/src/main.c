#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "useful.h"
#include "init.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include <string.h>



int main(int argc, char **argv){

    sCore core;
    int32_t toBeExecRaw;
    sInstruction toBeExec;
    char code[100],state[100];

    if (argc == 3){
        strcpy(code,argv[1]);
        strcpy(state,argv[2]);
        VERBOSE = 0;
    }else if (argc == 4){
        strcpy(code,argv[1]);
        strcpy(state,argv[2]);
        VERBOSE = 1;
    }else{  
        printf("usage: <CODE> <State> (Verbose)");
        exit(EXIT_SUCCESS);
    }
    
    initSCore(&core);
    initSCoreWithValues(state, &core);

    if (VERBOSE){
        printSCore(&core);  
    }

    int32_t* instructionsArray = initInstructionArray(code);
    int instructionsArraySize = 0;
    while (instructionsArray[instructionsArraySize] != '\0' ){
        instructionsArraySize++;
    }
    while (core.pc < instructionsArraySize){
        toBeExecRaw = fetch(&core, instructionsArray);
        if (toBeExecRaw != -1){
            toBeExec = decode(toBeExecRaw);
            execute(&core, toBeExec);
        }
        if (VERBOSE){
            printSCore(&core);
            printf("\n\n\n");
        }
    }
    printf("fin: \n");
    printSCore(&core);


    return 0;
}
