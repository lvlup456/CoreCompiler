#include "useful.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long rArray[15];
sFlag flags;
int pc;

/**
 * @brief print all the flags
 * 
 * @param flag 
 */
void printSFlags(sFlag* flag){
    printf("les flags: \n");
    printf("CF  = %X\n",flag->CF);
    printf("ZF  = %X\n",flag->ZF);
    printf("SF  = %X\n",flag->SF);
}

/**
 * @brief print the core values
 * 
 * @param core 
 */
void printSCore(sCore* core){
    printf("The core Values:\n");
    printf("pc = %X\n", core->pc);

    for (int i = 0; i < 15; i++){
        printf("r%i = %llX\n",i ,core->rArray[i]);
    }
    printSFlags(&core->flags);   
}

/**
 * @brief print an instruction
 * 
 * @param instruction 
 */
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

/**
 * @brief Get the bitwanted in n
 * 
 * @param n 
 * @param bitswanted 
 * @return int32_t 
 */
int32_t getBits32(int32_t n, int bitswanted){
  return 0 != (n & (1 << bitswanted));;
}

/**
 * @brief Get the bitwanted in n
 * 
 * @param n 
 * @param bitswanted 
 * @return int64_t 
 */
int64_t getBits64(int64_t n, int bitswanted){
  return 0 != (n & (1 << bitswanted));;
}


int32_t getFromBitTOBit32(int32_t n, int firstBit, int lastBit ){
    int32_t res = 0;
    int j = 0 ;
    for (int i = firstBit; i <= lastBit; i++){
        res += getBits32(n, i) * pow(2,j);
        j++;
    }
    return res;
}

int64_t getFromBitTOBit64(int64_t n, int firstBit, int lastBit ){
    int64_t res = 0;
    int j = 0 ;
    for (int i = firstBit; i <= lastBit; i++){
        res += getBits64(n, i) * pow(2,j);
        j++;
    }
    return res;
}

int getBits128(__int128_t n, __uint128_t bitswanted){
    __uint128_t mask = (((__uint128_t)1 ) << bitswanted);
    return 0 != (n & mask);
}

int64_t int128ToInt64(__int128_t n){
    int64_t val = 0;
    for (int i = 62; i >= 0; i--){
        val += (int64_t) (getBits128(n, i) * (int64_t)powl(2,i));
    }
    return val * pow(-1, getBits128(n, 128));
}



int64_t uint128ToInt64(__uint128_t n){
    int64_t val = 0;
    for (int i = 63; i >= 0; i--){
        val += (int64_t) (getBits128(n, i) * (int64_t)powl(2,i));
    }
    return val;
}

void print128(__uint128_t res){
    for (int i = 128; i >= 0; i--){
        printf("%d", getBits128(res, i));
    }
    printf("\n");
}