#include <stdio.h>
#include "execute.h"
#include <math.h>
#include "useful.h"

int64_t selectVal2(sCore* core, sInstruction instruction){
    if (instruction.ivFlag){
        return instruction.iv;
    }else{
        return core->rArray[instruction.ope2];
    }   
}

//it works
void add(sCore* core, sInstruction instruction){
    uint64_t val1,val2 = 0;
    __uint128_t res = 0;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    res = (__uint128_t) val1 + (__uint128_t) val2;
    core->rArray[instruction.dest] = (uint64_t) res;
    if (res <= (__uint128_t) UINT64_MAX){
        core->flags.CF = 0;
    }else{
        core->flags.CF = 1;
    }
    core->flags.ZF = res == 0;
    core->flags.SF = res<0;
    core->rArray[instruction.dest] = res;
}

void orr(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 || val2;

    core->flags.CF = 0;
    core->flags.ZF = core->rArray[instruction.dest] == 0;
    core->flags.SF = core->rArray[instruction.dest] < 0;
}

void and(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 && val2;
    core->flags.CF = 0;
    core->flags.ZF = core->rArray[instruction.dest] == 0;
    core->flags.SF = core->rArray[instruction.dest] < 0;
}

void xor(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val1 ^ val2;
    core->flags.CF = 0;
    core->flags.ZF = core->rArray[instruction.dest] == 0;
    core->flags.SF = core->rArray[instruction.dest] < 0;
}

//it Works
void adc(sCore* core, sInstruction instruction){
    uint64_t val1,val2 = 0;
    __uint128_t res = 0;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    res = (__uint128_t) val1 + (__uint128_t) val2 + (__uint128_t) core->flags.CF;
    core->rArray[instruction.dest] = (uint64_t) res;
    if (res <= (__uint128_t) UINT64_MAX){
        core->flags.CF = 0;
    }else{
        core->flags.CF = 1;
    }
    core->flags.ZF = res == 0;
    core->flags.SF = res<0;
    core->rArray[instruction.dest] = res;
}

void cmp(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    __int128_t tmp = (__int128_t) val1 - (__int128_t) val2;
    if (tmp < INT64_MIN && tmp > INT64_MAX){
        core->flags.CF = 1;
    }else{
        core->flags.CF = 0;
    }
    core->flags.SF = tmp < 0;
    core->flags.ZF = tmp == 0;
}

void sub(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    __int128_t res = (__int128_t)val1 - (__int128_t)val2;
    if (res > INT64_MIN && res < INT64_MAX){
        core->flags.CF = 0;
    }else{
        core->flags.CF = 1;
    }
    core->rArray[instruction.dest] = (int64_t) res;
    core->flags.SF = core->rArray[instruction.dest] < 0;
    core->flags.ZF = core->rArray[instruction.dest] == 0;
}

void sbc(sCore* core, sInstruction instruction){
    int64_t val1,val2;
    val1 = core->rArray[instruction.ope1];
    val2 = selectVal2(core,instruction);
    __int128_t res = (__int128_t)val1 - (__int128_t)val2 + (__int128_t) (core->flags.CF - 1);
    if (res > INT64_MIN && res < INT64_MAX){
        core->flags.CF = 0;
    }else{
        core->flags.CF = 1;
    }
    core->rArray[instruction.dest] = (int64_t) res;
    core->flags.SF = core->rArray[instruction.dest] < 0;
    core->flags.ZF = core->rArray[instruction.dest] == 0;
}

void mov(sCore* core, sInstruction instruction){
    int val2;
    val2 = selectVal2(core,instruction);
    core->rArray[instruction.dest] = val2;
}

//it works
void lsh(sCore* core, sInstruction instruction){
    __int128_t val1,val2, res = 0;
    val1 =  core->rArray[instruction.ope1];
    val2 =  selectVal2(core,instruction);
    res = val1 << val2;
    int overflow = 0;
    for (int i = 0; i < val2; i++){
        if (getBits128(val1, 63-i)){
            overflow = 1;
        }
    }
    core->flags.CF = overflow;
    core->rArray[instruction.dest] = (int64_t) res;
    core->flags.SF = core->rArray[instruction.dest] < 0;
    core->flags.ZF = core->rArray[instruction.dest] == 0;
}

void rsh(sCore* core, sInstruction instruction){
    __int128_t val1,val2, res = 0;
    val1 =  core->rArray[instruction.ope1];
    val2 =  selectVal2(core,instruction);
    res = val1 >> val2;
    int overflow = 0;
    for (int i = 0; i < val2; i++){
        if (getBits128(val1, i)){
            overflow = 1;
        }
    }
    core->flags.CF = overflow;
    core->rArray[instruction.dest] = (int64_t) res;
    core->flags.SF = core->rArray[instruction.dest] < 0;
    core->flags.ZF = core->rArray[instruction.dest] == 0;
}

void printInstruction(int code){
    switch (code){
        case 0x0:
            printf("and:\n");
            break;
        case 0x1:
            printf("orr:\n");
            break;
        case 0x2:
            printf("xor:\n");
            break;
        case 0x3:
            printf("add:\n");
            break;
        case 0x4:
            printf("adc:\n");
            break;
        case 0x5:
            printf("cmp:\n");
            break;
        case 0x6:
            printf("sub:\n");
            break;
        case 0x7:
            printf("sbc:\n");
            break;
        case 0x8:
            printf("movv:\n");
            break;
        case 0x9:
            printf("lsh:\n");
            break;
        case 0xA:
            printf("rsh:\n");
            break; 
        default:
            break;
    }
}

void execute(sCore* core, sInstruction instruction){
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
    if (VERBOSE){
        printInstruction(instruction.opcode);
    }
}