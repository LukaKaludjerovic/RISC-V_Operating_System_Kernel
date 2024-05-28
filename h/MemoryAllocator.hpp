//
// Created by os on 5/19/23.
//

#ifndef PROJECT_BASE_MEMORYALLOCATOR_HPP
#define PROJECT_BASE_MEMORYALLOCATOR_HPP

#include "../lib/hw.h"

class MemoryAllocator {
public:
    static MemoryAllocator* get_instance();
    void* mem_alloc(size_t size);
    int mem_free(void* address);

private:
    struct FreeMem{
        size_t size;
        FreeMem* next;
    };
    FreeMem* head;
    void try_to_join(FreeMem* node);
};

#endif //PROJECT_BASE_MEMORYALLOCATOR_HPP
