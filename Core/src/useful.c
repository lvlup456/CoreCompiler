#include "useful.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long rArray[15];
sFlag flags;
int pc;

void printSFlags(sFlag* flag){
    printf("les flags: \n");
    printf("BEQ = %X\n",flag->BEQ);
    printf("BNE = %X\n",flag->BNE);
    printf("BLE = %X\n",flag->BLE);
    printf("BGE = %X\n",flag->BGE);
    printf("BL  = %X\n",flag->BL);
    printf("BG  = %X\n",flag->BG);
}

void printSCore(sCore* core){
    printf("The core Values:\n");
    printf("pc = %X\n", core->pc);

    for (int i = 0; i < 15; i++){
        printf("r%i = %lX\n",i ,core->rArray[i]);
    }
    printSFlags(&core->flags);   
}



void printSInstruction(sInstruction* instruction){
    printf("instruction: \n");
    printf("%d--",instruction->bcc);
    printf("%d--",instruction->zeros);
    printf("%d--",instruction->ivFlag);
    printf("%d--",instruction->opcode);
    printf("%d--",instruction->ope1);
    printf("%d--",instruction->ope2);
    printf("%d--",instruction->dest);
    printf("%d\n",instruction->iv);    
}
