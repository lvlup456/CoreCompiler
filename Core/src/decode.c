#include "decode.h"
#include "useful.h"



sInstruction decode(int32_t instructionRaw){
    sInstruction instruction;

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
