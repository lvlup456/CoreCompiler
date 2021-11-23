#ifndef __STRUCTURE_H_
#define __STRUCTURE_H_
#include <stdlib.h>

typedef struct sFlag sFlag;
struct sFlag{
    int CF  ; // Carry Flag (Drapeau de retenue)
    int ZF  ; // Zero Flag (Drapeau zéro)
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
    unsigned int bcc;        // 4 bits
    unsigned int zeros;      // 3 bits
    unsigned int ivFlag;     // 1 bits
    unsigned int opcode;     // 4 bits
    unsigned int ope1;       // 4 bits
    unsigned int ope2;       // 4 bits
    unsigned int dest;       // 4 bits
    unsigned int iv;         // 8 bits
};

#endif