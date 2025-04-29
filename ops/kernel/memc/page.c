#include "page.h"
#include <stdint.h>

#define PAGE_DIR_SIZE 1024
#define PAGE_TABLE_SIZE 1024
#define PAGE_SIZE 4096

uint32_t page_directory[PAGE_DIR_SIZE] __attribute__((aligned(PAGE_SIZE)));
uint32_t first_page_table[PAGE_TABLE_SIZE] __attribute__((aligned(PAGE_SIZE)));

void page_init() {
    // Clear page directory
    for (int i = 0; i < PAGE_DIR_SIZE; i++) {
        page_directory[i] = 0x00000002;
    }

    // Identity map the first 4MB of memory using page table
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        first_page_table[i] = (i * PAGE_SIZE) | 3;
    }

    // Point the first entry of the page directory to the first page table
    page_directory[0] = ((uint32_t)first_page_table) | 3;

    // Load page directory
    asm volatile ("mov %0, %%cr3":: "r"(&page_directory));

    // Enable paging
    uint32_t cr0;
    asm volatile ("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile ("mov %0, %%cr0":: "r"(cr0));
}