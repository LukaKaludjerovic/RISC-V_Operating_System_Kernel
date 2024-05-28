//
// Created by os on 6/24/23.
//

//kod u ovom fajlu je u preuzet iz postavke projekta

#ifndef PROJECT_BASE_SYSCALL_CPP_HPP
#define PROJECT_BASE_SYSCALL_CPP_HPP

#include "../h/syscall_c.hpp"

class Thread{
public:
    Thread(void (*body)(void*), void* arg);
    virtual ~Thread();

    int start();

    void join();

    static void dispatch();

protected:
    Thread();
    virtual void run(){};

private:
    static void thread_wrapper(void* arg);

    thread_t myHandle;
    void (*body)(void*);
    void* arg;
};



class Semaphore{
public:
    explicit Semaphore(unsigned init = 1);
    virtual ~Semaphore();

    int wait();
    int signal();

private:
    sem_t myHandle;
};



class Console{
public:
    static char getc();
    static void putc(char c);
};

#endif //PROJECT_BASE_SYSCALL_CPP_HPP
