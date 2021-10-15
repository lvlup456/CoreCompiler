#ifndef __USEFUL_H_
#define __USEFUL_H_

#include "struct.h"


void printSCore(sCore* core);
void printSInstruction(sInstruction* instruction);

int getBits(int32_t n, int bitswanted);
int getFromBitTOBit(int32_t n, int firstBit, int lastBit );

#endif