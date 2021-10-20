#include "useful.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long rArray[15];
sFlag flags;
int pc;

void printSFlags(sFlag* flag){
    printf("les flags: \n");
    printf("CF  = %X\n",flag->CF);
    printf("ZF  = %X\n",flag->ZF);
    printf("OF  = %X\n",flag->OF);
    printf("SF  = %X\n",flag->SF);

}

void printSCore(sCore* core){
    printf("The core Values:\n");
    printf("pc = %X\n", core->pc);

    for (int i = 0; i < 15; i++){
        printf("r%i = %llX\n",i ,core->rArray[i]);
    }
    printSFlags(&core->flags);   
}

void printSInstruction(sInstruction* instruction){
    printf("instruction: \n");
    printf("%x--",instruction->bcc);
    printf("%x--",instruction->zeros);
    printf("%x--",instruction->ivFlag);
    printf("%x--",instruction->opcode);
    printf("%x--",instruction->ope1);
    printf("%x--",instruction->ope2);
    printf("%x--",instruction->dest);
    printf("%x\n",instruction->iv);    
}


int32_t getBits(int32_t n, int bitswanted){
  return 0 != (n & (1 << bitswanted));;
}

int32_t getFromBitTOBit(int32_t n, int firstBit, int lastBit ){
    int32_t res = 0;
    int j = 0 ;
    for (int i = firstBit; i <= lastBit; i++){
        res += getBits(n, i) * pow(2,j);
        j++;
    }
    return res;
}