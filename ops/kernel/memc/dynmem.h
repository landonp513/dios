#ifndef __DYNMEM_H
#define __DYNMEM_H

#include <stddef.h>

void initialize_memory();
void* malloc(size_t size);
void free(void* ptr);

#endif