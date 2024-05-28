//
// Created by os on 5/26/23.
//

#include "../h/syscall_c.hpp"
#include "../h/RiscV.hpp"

//0x01
void* mem_alloc(size_t size){
    size_t size_blocks = (size + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;
    RiscV::write_a1((uint64) size_blocks);
    RiscV::write_a0(0x01);

    RiscV::ecall();

    return (void*) RiscV::return_value();
}

//0x02
int mem_free(void* address){
    RiscV::write_a1((uint64) address);
    RiscV::write_a0(0x02);

    RiscV::ecall();

    return (int)RiscV::return_value();
}

//0x03
void userMode(){
    RiscV::write_a0(0x03);

    RiscV::ecall();
}

//0x04
void systemMode(){
    RiscV::write_a0(0x04);

    RiscV::ecall();
}

//0x11
int thread_create(thread_t* handle, void(*start_routine)(void*), void* arg){
    RiscV::write_a3((uint64) arg);
    RiscV::write_a2((uint64) start_routine);
    RiscV::write_a1((uint64) handle);
    RiscV::write_a0(0x11);

    RiscV::ecall();

    return (int)RiscV::return_value();
}

//0x12
int thread_exit(){
    RiscV::write_a0(0x12);

    RiscV::ecall();

    return (int)RiscV::return_value();
}

//0x13
void thread_dispatch(){
    RiscV::write_a0(0x13);

    RiscV::ecall();
}

//0x14
void thread_join(thread_t handle){
    RiscV::write_a1((uint64) handle);
    RiscV::write_a0(0x14);

    RiscV::ecall();
}

//0x21
int sem_open(sem_t* handle, unsigned init){
    RiscV::write_a2(init);
    RiscV::write_a1((uint64) handle);
    RiscV::write_a0(0x21);

    RiscV::ecall();

    return (int)RiscV::return_value();
}

//0x22
int sem_close(sem_t handle){
    RiscV::write_a1((uint64) handle);
    RiscV::write_a0(0x22);

    RiscV::ecall();

    return (int)RiscV::return_value();
}

//0x23
int sem_wait(sem_t handle){
    RiscV::write_a1((uint64) handle);
    RiscV::write_a0(0x23);

    RiscV::ecall();

    return (int)RiscV::return_value();
}

//0x24
int sem_signal(sem_t handle){
    RiscV::write_a1((uint64) handle);
    RiscV::write_a0(0x24);

    RiscV::ecall();

    return (int)RiscV::return_value();
}

//0x41
char getc(){
    RiscV::write_a0(0x41);

    RiscV::ecall();

    return (char)RiscV::return_value();
}

//0x42
void putc(char c){
    RiscV::write_a1((uint64) c);
    RiscV::write_a0(0x42);

    RiscV::ecall();
}