#include <stdio.h>
#include <stdlib.h>
#include "myMalloc.h"

int main() {

    float* float_data = myMalloc(sizeof(float)); // size of *data = 4, size of data(address) = 8
    printf("After allocation of float type of size %lu bytes + header 16 bytes\n",sizeof(float));
    printFreeList();

    double* double_data = myMalloc(sizeof(double));
    printf("After allocation of double type of size %lu bytes + header 16 bytes\n",sizeof(double));
    printFreeList();

    char* char_data = myMalloc(sizeof(char));
    printf("After allocation of char type of size %lu bytes + header 16 bytes\n",sizeof(char));
    printFreeList();

    int* int_data = myMalloc(sizeof(int));
    printf("After allocation of int type of size %lu bytes + header 16 bytes\n",sizeof(int));
    printFreeList();
    
    myFree(int_data);
    printf("After deallocation of int type of size %lu bytes + header 16 bytes\n",sizeof(int));
    printFreeList();

    int* int_data1 = myMalloc(sizeof(int));
    printf("After allocation of int type of size %lu bytes + header 16 bytes\n",sizeof(int));
    printFreeList();

    myFree(char_data);
    printf("After deallocation of char type of size %lu bytes + header 16 bytes\n",sizeof(char));
    printFreeList();

    myFree(float_data);
    printf("After deallocation of char type of size %lu bytes + header 16 bytes\n",sizeof(float));
    printFreeList();
    
    int* int_data2 = myMalloc(sizeof(int));
    printf("After allocation of int type of size %lu bytes + header 16 bytes\n",sizeof(int));
    printFreeList();

    char* char_data1 = myMalloc(sizeof(char));
    printf("After allocation of char type of size %lu bytes + header 16 bytes\n",sizeof(char));
    printFreeList();

    char* char_data2 = myMalloc(sizeof(char));
    printf("After allocation of char type of size %lu bytes + header 16 bytes\n",sizeof(char));
    printFreeList();

    unMap();

    return 0;
}