#ifndef __STRUCTURE_H_
#define __STRUCTURE_H_

typedef struct sFlag sFlag;
struct sFlag{
    int BEQ ; //ope1 = ope2
    int BNE ; //ope1 !=ope2
    int BLE ; //ope1 ≤ ope2
    int BGE ; //ope1 ≥ ope2
    int BL  ; //ope1 < ope2
    int BG  ; //ope1 > ope2
};


typedef struct sCore sCore;
struct sCore{
    unsigned long rArray[15];
    sFlag flags;
    int pc;
};

/* 
   BCC  Zeros  opcode     ope2      IV
0x|0000|000|0|0000|0000|0000|0000|00000000
             IV     ope1     dest
*/
typedef struct sInstruction sInstruction;
struct sInstruction{
    int bcc;        // 4 bits
    int zeros;      // 3 bits
    int ivFlag;     // 1 bits
    int opcode;     // 4 bits
    int ope1;       // 4 bits
    int ope2;       // 4 bits
    int dest;       // 4 bits
    int iv;         // 8 bits
};

#endif