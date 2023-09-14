#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

void* memory;
struct freeList *head = NULL;
int totalSize = 8192;

struct freeList {
    int size;
    struct freeList *next;
};  //freeList size 16

void* initializeMemory() 
{
    // @addr[.length] : null, then kernel chooses the (page-aligned) address at which to create the mapping
    // size = 8192 Allocates 8192KB
    // PROT_READ | PROT_WRITE : Read and write access
    // MAP_PRIVATE | MAP_ANONYMOUS : private map not associated with files
    // -1 not mapped to any files
    // 0 - offset
    int size_in_bytes = 1024*totalSize;
    memory = mmap(NULL, totalSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (memory == MAP_FAILED) {
        printf("The memory allocation failed \n");
        return NULL;
    }
    printf("Memory start address %p of size %d\n", memory,size_in_bytes); 
    head = memory;
    head->size = size_in_bytes-sizeof(struct freeList);
    head->next = NULL;
    printf("After allocating freeList node, available size: %d address %p\n",head->size,head);
    return memory;
}

void* myMalloc(unsigned int size) {

    if (memory == NULL) {
        initializeMemory();
    }
    if (head != NULL) {
        struct freeList *node = head;
        struct freeList *prev = head;
        int isAllocated = 0;
        while(node != NULL) {
            int availableSize = node->size;
            if(availableSize >= size) {
                isAllocated = 1;
                if (availableSize == size) {
                    if (node != prev) {
                        prev->next = node->next;
                    }
                    // handle this case if 
                    if (node == head) {
                        head = node->next;
                    }
                    node->next = NULL;
                    return (char*)node+sizeof(struct freeList); 
                }
                if(availableSize > size+sizeof(struct freeList)) {
                    struct freeList *freeListNode = node+sizeof(struct freeList)+size;
                    freeListNode->size = availableSize - (size+sizeof(struct freeList));
                    freeListNode->next = node->next;
                    node->size = size;
                    node->next = NULL;
                    if (head == node) {
                        head = freeListNode;
                    }
                    else {
                        prev->next = freeListNode;
                    }
                    return node+sizeof(struct freeList);
                }
            }
            prev = node;
            node = node->next;
        }
        if(isAllocated == 0){
            printf("There is no enough free space left to allocate space");
        }
    }
   return NULL;
}

void myFree(void* address) {
    struct freeList *hptr = (struct freeList*)address - sizeof(struct freeList);
    int size = hptr->size;
    //if the freed space is just infront of the head, combine it
    if (hptr+sizeof(struct freeList)+size == head) {
        hptr->size = hptr->size+head->size+sizeof(struct freeList);
        hptr->next = head->next;
        head = hptr;
        return;
    }
    else {
        hptr->next = head;
        head = hptr;
    }
}

void printFreeList() {
    struct freeList *node = head;
    printf("Free List:\n");
    while(node != NULL) {
        printf("%d(bytes) \n",node->size);
        node = node->next;
    }
}

// int main() {

//     float* float_data = myMalloc(sizeof(float)); // size of *data = 4, size of data(address) = 8
//     printf("After allocation of float type of size %lu bytes + header %lu bytes\n",sizeof(float),sizeof(struct freeList));
//     printFreeList();

//     double* double_data = myMalloc(sizeof(double));
//     printf("After allocation of double type of size %lu bytes + header %lu bytes\n",sizeof(double),sizeof(struct freeList));
//     printFreeList();

//     char* char_data = myMalloc(sizeof(char));
//     printf("After allocation of char type of size %lu bytes + header %lu bytes\n",sizeof(char),sizeof(struct freeList));
//     printFreeList();

//     int* int_data = myMalloc(sizeof(int));
//     printf("After allocation of int type of size %lu bytes + header %lu bytes\n",sizeof(int),sizeof(struct freeList));
//     printFreeList();
    
//     myFree(int_data);
//     printf("After deallocation of int type of size %lu bytes",sizeof(int));
//     printFreeList();

//     int* int_data1 = myMalloc(sizeof(int));
//     printf("After allocation of int type of size %lu bytes + header %lu bytes\n",sizeof(int),sizeof(struct freeList));
//     printFreeList();

//     myFree(char_data);
//     printf("After deallocation of char type of size %lu bytes + header %lu bytes\n",sizeof(char),sizeof(struct freeList));
//     printFreeList();

//     myFree(float_data);
//     printf("After deallocation of char type of size %lu bytes + header %lu bytes\n",sizeof(float),sizeof(struct freeList));
//     printFreeList();
    
//     // int* int_data2 = myMalloc(sizeof(int));
//     // printf("After allocation of int type of size %lu bytes + header %lu bytes\n",sizeof(int),sizeof(struct freeList));
//     // printFreeList();

//     char* char_data1 = myMalloc(sizeof(char));
//     printf("After allocation of char type of size %lu bytes + header %lu bytes\n",sizeof(char),sizeof(struct freeList));
//     printFreeList();

//     char* char_data2 = myMalloc(sizeof(char));
//     printf("After allocation of char type of size %lu bytes + header %lu bytes\n",sizeof(char),sizeof(struct freeList));
//     printFreeList();

//     // return 0;

// }