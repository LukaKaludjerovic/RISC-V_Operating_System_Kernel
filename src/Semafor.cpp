//
// Created by os on 6/24/23.
//

#include "../h/Semafor.hpp"

Semafor* Semafor::createSemafor(Semafor **handle, int value) {
    *handle = new Semafor(value);
    return *handle;
}

int Semafor::close() {
    CCB* thread = blockedQueue.removeFirst();
    while(thread){
        thread->setBlocked(false);
        thread->setClosed(true);
        Scheduler::put(thread);
        thread = blockedQueue.removeFirst();
    }
    return 0;
}

int Semafor::wait() {
    if(--value < 0) {
        if (CCB::running->isClosed())
            return -1;
        CCB::running->setBlocked(true);
        blockedQueue.addLast(CCB::running);
        CCB::dispatch();
    }
    return 0;
}

int Semafor::signal() {
    if(++value <= 0) {
        CCB* thread = blockedQueue.removeFirst();
        thread->setBlocked(false);
        Scheduler::put(thread);
    }
    return 0;
}