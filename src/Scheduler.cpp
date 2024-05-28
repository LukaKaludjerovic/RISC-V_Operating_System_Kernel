//
// Created by os on 6/23/23.
//

#include "../h/Scheduler.hpp"

List<CCB> Scheduler::readyQueue;

CCB* Scheduler::get() {
    return readyQueue.removeFirst();
}

void Scheduler::put(CCB* thread){
    readyQueue.addLast(thread);
}