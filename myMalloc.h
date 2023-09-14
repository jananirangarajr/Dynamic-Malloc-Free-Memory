#ifndef MY_MALLOC_H
#define MY_MALLOC_H
#include <stdlib.h>

void printFreeList();
void* myMalloc(unsigned int size);
void myFree(void* address);

#endif