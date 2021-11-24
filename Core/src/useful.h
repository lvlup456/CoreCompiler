#ifndef __USEFUL_H_
#define __USEFUL_H_

#include "struct.h"


void printSCore(sCore* core);
void printSInstruction(sInstruction* instruction);

int32_t getBits32(int32_t n, int bitswanted);
int64_t getBits64(int64_t n, int bitswanted);
int32_t getFromBitTOBit32(int32_t n, int firstBit, int lastBit );
int64_t getFromBitTOBit64(int64_t n, int firstBit, int lastBit );
int64_t int128ToInt64(__int128_t n);
int64_t uint128ToInt64(__uint128_t n);
int getBits128(__int128_t n, __uint128_t bitswanted);
void print128(__uint128_t res);
int VERBOSE;


#endif