//
// Created by os on 6/23/23.
//

//kod u ovom fajlu, kao i u odgovarajucem .cpp fajlu, je preuzet sa vezbi

#ifndef PROJECT_BASE_SCHEDULER_HPP
#define PROJECT_BASE_SCHEDULER_HPP

#include "../h/List.hpp"

class CCB;

class Scheduler {
public:
    static CCB* get();
    static void put(CCB* thread);

private:
    static List<CCB> readyQueue;
};


#endif //PROJECT_BASE_SCHEDULER_HPP
