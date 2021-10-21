#include "fetch.h"
#include "useful.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "init.h"


int pcEquation(int pc, int instruction27, int instruction26to0){
    return pc + pow(-1,instruction27) * instruction26to0;
}
/**
   - CF Carry Flag (Drapeau de retenue) : 
   - PF Parity Flag (Drapeau de parité) : 
   - AF Adjust Flag (Drapeau d'ajustement) : 
   - ZF Zero Flag (Drapeau zéro) : 
   - SF Sign Flag (Drapeau de signe) : 
   - OF Overflow Flag (Drapeau de débordement) : 
**/

void setPcAccordingToFlag(sCore* core, int32_t instruction,int boolean){
    if(boolean){
        core->pc += pcEquation(core->pc, getFromBitTOBit(instruction, 27, 27),getFromBitTOBit(instruction, 0, 27));
    }else{
        core->pc++;
    }
}

void computeNewPc(sCore* core, int bcc, int32_t instruction){
    int boolean;
    switch (bcc){
    case 0x8: // Unconditional branch B
        core->pc += pcEquation(core->pc, getFromBitTOBit(instruction, 27, 27),getFromBitTOBit(instruction, 0, 27));
        break;
    case 0x9: // Branch if equal BEQ
        boolean = core->flags.ZF;
        setPcAccordingToFlag(core, instruction, boolean);
        break;
    case 0xa: // Branch if not equal BNE
        boolean = core->flags.ZF == 0;
        setPcAccordingToFlag(core, instruction, boolean);
        break;
    case 0xb: // Branch if lower or equal BLE a-b < 0 -> a<b 
        boolean = (core->flags.ZF == 1) || (core->flags.SF == 1) ;
        setPcAccordingToFlag(core, instruction, boolean);
        break;
    case 0xc: // Branch if greater or equal BGE
        boolean = (core->flags.ZF == 1) || (core->flags.SF == 0) ;
        setPcAccordingToFlag(core, instruction, boolean);
        break;
    case 0xd: // Branch if lower BL
        boolean = (core->flags.SF == 1) ;
        setPcAccordingToFlag(core, instruction, boolean);
        break;
    case 0xe: // Branch if greater BG
        boolean = (core->flags.SF == 0) ;
        setPcAccordingToFlag(core, instruction, boolean);
        break;
    default:
        core->pc++;
        break;
    }
} 



int32_t fetch(sCore* core, int32_t* instructionArray){

    int32_t instructionRaw = instructionArray[core->pc];
    computeNewPc(core, getFromBitTOBit(instructionRaw, 28, 31),instructionRaw);

    return instructionRaw;
}
