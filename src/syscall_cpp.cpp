//
// Created by os on 6/24/23.
//

#include "../h/syscall_cpp.hpp"
#include "../h/Scheduler.hpp"
#include "../h/CCB.hpp"
#include "../h/Semafor.hpp"

Thread::Thread(void (*body)(void *), void *arg){
    myHandle = new CCB(body, arg);
    this->body = body;
    this->arg = arg;
}

Thread::~Thread() {
    delete myHandle;
}

int Thread::start() {
    Scheduler::put(myHandle);
    return 0;
}

void Thread::join() {
    thread_join(myHandle);
}

void Thread::dispatch() {
    thread_dispatch();
}

Thread::Thread() {
    myHandle = new CCB(thread_wrapper, this);
    this->body = thread_wrapper;
    this->arg = this;
}

void Thread::thread_wrapper(void *arg) {
    ((Thread*) arg)->run();
}



Semaphore::Semaphore(unsigned int init) {
    this->myHandle = nullptr;
    sem_open(&myHandle, init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    return sem_wait(myHandle);
}

int Semaphore::signal() {
    return sem_signal(myHandle);
}



char Console::getc() {
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
}