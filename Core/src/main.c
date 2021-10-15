#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "useful.h"
#include "init.h"
#include "fetch.h"


int main(){

    sCore core;

    initSCore(&core);
    initSCoreWithValues("./files/load1.txt", &core);
    printSCore(&core);

    int32_t* instructionsArray = initInstructionArray("./files/loadInstructions.txt");

    sInstruction toBeExec = fetch(&core, &instructionsArray);

    return 0;
}
