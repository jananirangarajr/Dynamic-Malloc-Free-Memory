#include <stdio.h>
#include <stdlib.h>
#include "myMalloc.h"

int main() {

    float* float_data = myMalloc(sizeof(float)); // size of *data = 4, size of data(address) = 8
    *float_data = 3.2f;
    printf("After allocation of float type of size %lu bytes + header 16 bytes\n",sizeof(float));
    printFreeList();

    double* double_data = myMalloc(sizeof(double));
    *double_data = 4.8;
    printf("After allocation of double type of size %lu bytes + header 16 bytes\n",sizeof(double));
    printFreeList();

    char* char_data = myMalloc(sizeof(char));
    *char_data = 'A';
    printf("After allocation of char type of size %lu bytes + header 16 bytes\n",sizeof(char));
    printFreeList();

    int* int_data = myMalloc(sizeof(int));
    *int_data = 8;
    printf("After allocation of int type of size %lu bytes + header 16 bytes\n",sizeof(int));
    printFreeList();

    printf("Allocated Space Values and Addresses\n");
    printf("float Address :%p and float value: %f\n",float_data,*float_data);
    printf("double Address :%p and double value: %lf\n",double_data,*double_data);
    printf("char Address :%p and char value: %c\n",char_data,*char_data);
    printf("int Address :%p and int value: %d\n",int_data,*int_data);
    
    myFree(int_data);
    printf("After deallocation of int type of size %lu bytes + header 16 bytes\n",sizeof(int));
    printFreeList();

    int* int_data1 = myMalloc(sizeof(int));
    *int_data1 = 2;
    printf("After allocation of int type of size %lu bytes + header 16 bytes\n",sizeof(int));
    printFreeList();

    printf("int Address :%p and int value: %d\n",int_data1,*int_data1);

    myFree(char_data);
    printf("After deallocation of char type of size %lu bytes + header 16 bytes\n",sizeof(char));
    printFreeList();

    myFree(float_data);
    printf("After deallocation of float type of size %lu bytes + header 16 bytes\n",sizeof(float));
    printFreeList();
    
    int* int_data2 = myMalloc(sizeof(int));
    *int_data2 = 8;
    printf("After allocation of int type of size %lu bytes + header 16 bytes\n",sizeof(int));
    printFreeList();
    printf("int Address :%p and int value: %d\n",int_data2,*int_data2);

    char* char_data1 = myMalloc(sizeof(char));
    *char_data1 = 'C';
    printf("After allocation of char type of size %lu bytes + header 16 bytes\n",sizeof(char));
    printFreeList();
    printf("char Address :%p and char value: %c\n",char_data1,*char_data1);

    char* char_data2 = myMalloc(sizeof(char));
    *char_data2 = 'B';
    printf("After allocation of char type of size %lu bytes + header 16 bytes\n",sizeof(char));
    printFreeList();
    printf("char Address :%p and char value: %c\n",char_data2,*char_data2);

    unMap();
    return 0;
}