#include <stdio.h>
#include "execute.h"
#include <math.h>

int64_t selectVal2(sCore* core, sInstruction instruction){
    if (instruction.ivFlag){
        //TODO: test neg
        return instruction.iv;
    }else{
        return core->rArray[instruction.ope1];
    }   
}


//TODO: add flags and exceptions
void add(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    
    core->rArray[instruction.dest] = val1 + val2;
}

//TODO: add flags and exceptions
void orr(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 || val2;
}

//TODO: add flags and exceptions
void and(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 && val2;
}

//TODO: add flags and exceptions
void xor(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 ^ val2;
}

//TODO: add flags and exceptions
void adc(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 + val2 + core->flags.CF;
}

//TODO: add flags and exceptions
void cmp(sCore* core, sInstruction instruction){
    int val1,val2, tmp;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    tmp = val1 - val2;
    if (tmp<0){
        core->flags.SF = 1;
    }else if (tmp > 0){
        core->flags.SF = 0;
    }else if (tmp == 0){
        core->flags.ZF = 1;
    }
}

//TODO: add flags and exceptions
void sub(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 - val2;

    if (core->rArray[instruction.dest] < 0){
        core->flags.SF = 1;
    }else if (core->rArray[instruction.dest] > 0){
        core->flags.SF = 0;
    }else if (core->rArray[instruction.dest] == 0){
        core->flags.ZF = 1;
    }
}

//TODO: add flags and exceptions
void sbc(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 - val2 + core->flags.CF - 1;
}

//TODO: add flags and exceptions
void mov(sCore* core, sInstruction instruction){
    int val2;
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val2;
}

void lsh(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 << val2;
}

void rsh(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 >> val2;
}


void execute(sCore* core, sInstruction instruction){
    printf("j'execute des trucs\n");
    switch (instruction.opcode){
        case 0x0:
            and(core,instruction);
            break;
        case 0x1:
            orr(core,instruction);
            break;
        case 0x2:
            xor(core,instruction);
            break;
        case 0x3:
            add(core,instruction);
            break;
        case 0x4:
            adc(core,instruction);
            break;
        case 0x5:
            cmp(core,instruction);
            break;
        case 0x6:
            sub(core,instruction);
            break;
        case 0x7:
            sbc(core,instruction);
            break;
        case 0x8:
            mov(core,instruction);
            break;
        case 0x9:
            lsh(core,instruction);
            break;
        case 0xA:
            rsh(core,instruction);
            break;
        default:
            printf("wrong upcode\n");
            exit(EXIT_FAILURE);
            break;
    }
}