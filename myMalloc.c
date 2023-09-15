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
    /**
    * @addr[.length] : null, then kernel chooses the (page-aligned) address at which to create the mapping
    * size = 8192 Allocates 8192KB
    * PROT_READ | PROT_WRITE : Read and write access
    * MAP_PRIVATE | MAP_ANONYMOUS : private map not associated with files
    * -1 not mapped to any files
    * 0 - offset
    */
    memory = mmap(NULL, totalSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (memory == MAP_FAILED) {
        printf("The memory allocation failed \n");
        return NULL;
    }

    int size_in_bytes = 1024*totalSize;
    printf("Memory start address %p of size %d\n", memory,size_in_bytes); 
    //initialize memory along with header information
    head = memory;
    head->size = size_in_bytes-sizeof(struct freeList);
    head->next = NULL;
    printf("After allocating freeList node, available size: %d\n",head->size);
    return memory;
}
/**
 * Allocates space for the given size
 * size - (bytes)
*/

void* myMalloc(unsigned int size) {
    //Initiate memory if not initialized yet
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
                //if size exactly matches the free node size, change the header information & make the previous node to node-.next
                if (availableSize == size) {
                    if (node != prev) {
                        prev->next = node->next;
                    }
                    //Move head if head is the only free space
                    if (node == head) {
                        head = node->next;
                    }
                    node->next = NULL;
                    return (char*)node+sizeof(struct freeList); 
                }
                /**
                 * Size greater than the requested size, then allocate space at node starting address 
                 * and move the freespace node right after the allocated memory
                 * return the node+sizeof(freeList) as address
                */
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
/**
 * Deallocate the space for the given address
 * hptr - pointer to the header of address given
 * 
*/

void myFree(void* address) {
    struct freeList *hptr = (struct freeList*)address - sizeof(struct freeList);
    int size = hptr->size;
    //free space is just infront of the other node, combine it
    if (hptr+sizeof(struct freeList)+size == head) {
        hptr->size = hptr->size+head->size+sizeof(struct freeList);
        hptr->next = head->next;
        head = hptr;
        return;
    }
    //change next pointer to point to head and make the adress block as head
    else {
        hptr->next = head;
        head = hptr;
    }
}
/**
 * Method to print the freeList space
 * prints from head to null
 */
void printFreeList() {
    struct freeList *node = head;
    printf("Free List:\n");
    while(node != NULL) {
        printf("%d(bytes), start Address %p\n",node->size,node+sizeof(struct freeList));
        node = node->next;
    }
}

void unMap(){
    munmap(memory,totalSize);
}