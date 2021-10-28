#include "decode.h"
#include "useful.h"



sInstruction decode(int32_t instructionRaw){
    sInstruction instruction;

    instruction.bcc    = getFromBitTOBit32(instructionRaw, 28, 31);
    instruction.zeros  = getFromBitTOBit32(instructionRaw, 25, 27);
    instruction.ivFlag = getFromBitTOBit32(instructionRaw, 24, 24);
    instruction.opcode = getFromBitTOBit32(instructionRaw, 20, 23);
    instruction.ope1   = getFromBitTOBit32(instructionRaw, 16, 19);
    instruction.ope2   = getFromBitTOBit32(instructionRaw, 12, 15);
    instruction.dest   = getFromBitTOBit32(instructionRaw, 8, 11);
    instruction.iv     = getFromBitTOBit32(instructionRaw, 0, 7);    

    printSInstruction(&instruction);

    return instruction;
}
