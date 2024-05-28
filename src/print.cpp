//
// Created by os on 5/24/23.
//

#include "../h/print.hpp"
#include "../lib/console.h"
#include "../h/syscall_c.hpp"

/*void printString(char const *string){
    while(*string != '\0'){
        putc(*string);
        string++;
    }
}

void printInteger(uint64 integer){
    static char digits[] = "0123456789";
    char buf[16];
    int i = 0;
    do{
        buf[i++] = digits[integer % 10];
    }while((integer /= 10) != 0);
    while(--i >= 0)
        putc(buf[i]);
}*/