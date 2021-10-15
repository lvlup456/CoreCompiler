#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "useful.h"
#include "init.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"

int main(){

    sCore core;
    int32_t toBeExecRaw;
    sInstruction toBeExec;

    initSCore(&core);
    initSCoreWithValues("./files/load1.txt", &core);
    printSCore(&core);

    int32_t* instructionsArray = initInstructionArray("./files/loadInstructions.txt");
    int instructionsArraySize = 0;
    while (instructionsArray[instructionsArraySize] != '\0' ){
        instructionsArraySize++;
    }
    
    while (core.pc < instructionsArraySize){
        toBeExecRaw = fetch(&core, instructionsArray);
        toBeExec = decode(toBeExecRaw);
        execute(toBeExec);
    }

    return 0;
}
