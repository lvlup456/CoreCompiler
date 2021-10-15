#ifndef __INIT_H_
#define __INIT_H_

#include "struct.h"
#include <stdlib.h>


void initSCore(sCore* core);
void initSFlag(sFlag* flag);
void initSCoreWithValues(char* path, sCore* core);
int32_t* initInstructionArray(char* path);

#endif