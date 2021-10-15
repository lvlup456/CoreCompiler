#ifndef __STRUCTURE_H_
#define __STRUCTURE_H_
#include <stdlib.h>

typedef struct sFlag sFlag;
struct sFlag{
    int CF  ; // Carry Flag (Drapeau de retenue)
    int PF  ; // Parity Flag (Drapeau de parité)
    int AF  ; // Adjust Flag (Drapeau d'ajustement)
    int ZF  ; // Zero Flag (Drapeau zéro)
    int OF  ; // Overflow Flag (Drapeau de débordement)
    int SF  ; // Sign Flag (Drapeau de signe)
};


typedef struct sCore sCore;
struct sCore{
    int64_t rArray[15];
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