#include "dynmem.h"
#include <stdint.h>

typedef struct MemoryBlock {
    size_t size;
    int free;
    struct MemoryBlock* next;
} MemoryBlock;

#define HEAP_SIZE 64 * 1024
static uint8_t heap[HEAP_SIZE];
static MemoryBlock* free_list = (MemoryBlock*)heap;

void initialize_memory() {
    free_list->size = HEAP_SIZE - sizeof(MemoryBlock);
    free_list->free = 1;
    free_list->next = NULL;
}

void* malloc(size_t size) {
    MemoryBlock* current = free_list;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            current->free = 0;
            return (void*)(current + 1);
        }
        current = current->next;
    }
    return NULL;
}

void free(void* ptr) {
    if (ptr == NULL) return;
    MemoryBlock* block = (MemoryBlock*)ptr - 1;
    block->free = 1;
}