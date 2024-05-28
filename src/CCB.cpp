//
// Created by os on 6/23/23.
//

#include "../h/CCB.hpp"
#include "../h/RiscV.hpp"
#include "../h/syscall_c.hpp"

CCB* CCB::running = nullptr;

int CCB::threads = 0;

CCB* CCB::createCCB(CCB** handle, Body body, void* bodyArg) {
    *handle =  new CCB(body, bodyArg);
    if(body != nullptr)
        Scheduler::put(*handle);
    return *handle;
}

void CCB::yield() {
    RiscV::pushRegisters();
    CCB::dispatch();
    RiscV::popRegisters();
}

void CCB::dispatch(){
    CCB* old = running;
    if(!old->isFinished() && !old->isBlocked()){
        Scheduler::put(old);
    }
    running = Scheduler::get();

    CCB::contextSwitch(&old->context, &running->context);
}

void CCB::threadWrapper() {
    RiscV::popSppSpie();
    running->body(running->bodyArg);
    running->setFinished(true);
    threads--;
    thread_dispatch();
}