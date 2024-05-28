//
// Created by os on 6/23/23.
//

//kod u ovom fajlu je preuzet sa vezbi

#include "../h/syscall_c.hpp"

void* operator new (size_t size){
    return mem_alloc(size);
}

void operator delete (void* address){
    mem_free(address);
}

void* operator new[] (size_t size){
    return mem_alloc(size);
}

void operator delete[] (void* address){
    mem_free(address);
}