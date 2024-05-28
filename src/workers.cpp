//
// Created by os on 6/23/23.
//

#include "../lib/hw.h"
#include "../h/CCB.hpp"
#include "../test/printing.hpp"
#include "../h/syscall_c.hpp"

static uint64 fibonacci(uint64 n){
    if(n == 0 || n == 1)
        return n;
    if(n % 4 == 0)
        thread_dispatch();
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void workerBodyX(void* arg){
    uint8 i = 0;
    for(; i < 3; i++){
        printString("A: i=");
        printInt(i);
        printString("\n");
    }

    printString("A: dispatch\n");
    __asm__ ("li t1, 7");
    thread_dispatch();

    uint64 t1 = 0;
    __asm__ ("mv %[t1], t1" : [t1] "=r"(t1));

    printString("A: t1=");
    printInt(i);
    printString("\n");

    uint64 result = fibonacci(20);
    printString("A: fibonaci=");
    printInt(result);
    printString("\n");

    for(; i < 6; i++){
        printString("A: i=");
        printInt(i);
        printString("\n");
    }

    thread_dispatch();
}

void workerBodyY(void* arg){
    uint8 i = 10;
    for(; i < 13; i++){
        printString("B: i=");
        printInt(i);
        printString("\n");
    }

    printString("B: dispatch\n");
    __asm__ ("li t1, 5");
    thread_dispatch();

    uint64 result = fibonacci(23);
    printString("A: fibonaci=");
    printInt(result);
    printString("\n");

    for(; i < 16; i++){
        printString("B: i=");
        printInt(i);
        printString("\n");
    }
    thread_dispatch();
}