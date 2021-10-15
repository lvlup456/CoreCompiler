#include "fetch.h"
#include "useful.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getBits(int32_t n, int bitswanted){
  return 0 != (n & (1 << bitswanted));;
}

int getFromBitTOBit(int32_t n, int firstBit, int lastBit ){
    int res = 0;
    int j = 0 ;
    for (int i = firstBit; i <= lastBit; i++){
        res += getBits(n, i) * pow(2,j);
        j++;
    }
    return res;
}



sInstruction fetch(sCore* core, int32_t** instructionArray){
    sInstruction instruction;
    
    int32_t instructionRaw = *instructionArray[core->pc];

    instruction.bcc    = getFromBitTOBit(instructionRaw, 28, 31);
    instruction.zeros  = getFromBitTOBit(instructionRaw, 25, 27);
    instruction.ivFlag = getFromBitTOBit(instructionRaw, 24, 24);
    instruction.opcode = getFromBitTOBit(instructionRaw, 20, 23);
    instruction.ope1   = getFromBitTOBit(instructionRaw, 16, 19);
    instruction.ope2   = getFromBitTOBit(instructionRaw, 12, 15);
    instruction.dest   = getFromBitTOBit(instructionRaw, 8, 11);
    instruction.iv     = getFromBitTOBit(instructionRaw, 0, 7);

    printSInstruction(&instruction);
    return instruction;
}
