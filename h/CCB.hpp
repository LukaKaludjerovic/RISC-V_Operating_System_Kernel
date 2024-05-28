//
// Created by os on 6/23/23.
//

//kod u ovom fajlu, kao i u odgovarajucem .cpp fajlu, je delimicno preuzet sa vezbi

#ifndef PROJECT_BASE_CCB_HPP
#define PROJECT_BASE_CCB_HPP

#include "../h/Scheduler.hpp"
#include "../lib/hw.h"

class CCB {
public:
    ~CCB() {delete[] stack;}

    bool isFinished() const {return finished;}
    void setFinished(bool finished) {this->finished = finished;}
    bool isBlocked() const {return blocked;}
    void setBlocked(bool blocked) {this->blocked = blocked;}
    bool isClosed() const {return closed;}
    void setClosed(bool closed) {this->closed = closed;}

    using Body = void (*)(void*);

    static CCB* createCCB(CCB** handle, Body body, void* bodyArg);

    static void yield();

    static CCB* running;

    static int threads;

private:
    explicit CCB(Body body, void* bodyArg = nullptr):
            body(body),
            bodyArg(bodyArg),
            stack(body != nullptr ? new uint64[DEFAULT_STACK_SIZE] : nullptr),
            context({body != nullptr ? (uint64) &threadWrapper : 0,
                     stack != nullptr ? (uint64) &stack[DEFAULT_STACK_SIZE] : 0
                    }),
            finished(false),
            blocked(false),
            closed(false)
    {
        threads++;
    }

    struct Context{
        uint64 ra;
        uint64 sp;
    };

    friend class RiscV;
    friend class Thread;
    friend class Semafor;

    Body body;
    void* bodyArg;
    uint64* stack;
    Context context;
    bool finished;
    bool blocked;
    bool closed;

    static void contextSwitch(Context* oldContext, Context* runningContext);

    static void dispatch();

    static void threadWrapper();
};


#endif //PROJECT_BASE_CCB_HPP
