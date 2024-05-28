//
// Created by os on 5/19/23.
//

#include "../h/MemoryAllocator.hpp"

//kod ove funkcije je preuzet sa kolokvijuma -> 1. zadatak, 3. kolokvijum, jun 2022.
MemoryAllocator* MemoryAllocator::get_instance() {
    static MemoryAllocator instance;
    return &instance;
}

void* MemoryAllocator::mem_alloc(size_t size) {
    if(head == nullptr){
        FreeMem* header = (FreeMem*)HEAP_START_ADDR;
        header->size = ((char*)HEAP_END_ADDR - (char*)HEAP_START_ADDR - sizeof(FreeMem)) / MEM_BLOCK_SIZE;
        header->next = nullptr;
        head = header;
    }
    void* returnAddress = nullptr;
    FreeMem* current = head;
    FreeMem* previous = nullptr;
    while(current && current->size < size) {
        previous = current;
        current = current->next;
    }
    if(current == nullptr)
        return nullptr;
    if(current->size == size){
        returnAddress = (char*)current + sizeof(FreeMem);
        if(previous != nullptr)
            previous->next = current->next;
        else
            head = current->next;
    }
    else{
        returnAddress = (char*)current + sizeof(FreeMem);
        FreeMem* newBlock = (FreeMem*)((char*)current + sizeof(FreeMem) + size*MEM_BLOCK_SIZE);
        newBlock->size = (current->size - size - sizeof(FreeMem)) / MEM_BLOCK_SIZE;
        newBlock->next = current->next;
        if(previous != nullptr)
            previous->next = newBlock;
        else
            head = newBlock;
        current->size = size;
    }
    return returnAddress;
}

//kod ove funkcije je preuzet sa kolokvijuma -> 2. zadatak, 2. kolokvijum, septembar 2015.
void MemoryAllocator::try_to_join(MemoryAllocator::FreeMem *node) {
    if(node->next && (char*)node + sizeof(FreeMem) + node->size*MEM_BLOCK_SIZE == (char*)node->next){
        node->size += node->next->size;
        node->next = node->next->next;
    }
}

int MemoryAllocator::mem_free(void *address) {
    if(address == nullptr)
        return -1;
    if((char*)address < (char*)HEAP_START_ADDR || (char*)address >= (char*)HEAP_END_ADDR)
        return -2;
    FreeMem* current = (FreeMem*)((char*)address - sizeof(FreeMem));
    FreeMem* previous = head;
    if(head == nullptr)
        previous = nullptr;
    else{
        while(previous->next != nullptr && (char*)address > (char*)previous->next)
            previous = previous->next;
    }
    if(previous != nullptr) {
        current->next = previous->next;
        previous->next = current;
        try_to_join(previous);
        try_to_join(current);
    }
    else {
        current->next = head;
        head = current;
        try_to_join(current);
    }
    return 0;
}