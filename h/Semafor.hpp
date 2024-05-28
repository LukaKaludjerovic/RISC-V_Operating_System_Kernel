//
// Created by os on 6/24/23.
//

#ifndef PROJECT_BASE_SEMAFOR_HPP
#define PROJECT_BASE_SEMAFOR_HPP

#include "../h/List.hpp"
#include "../h/CCB.hpp"

class Semafor {
public:
    static Semafor* createSemafor(Semafor** handle, int value);
    int close();
    int wait();
    int signal();

private:
    explicit Semafor(int value): value(value), blockedQueue(List<CCB>()) {}

    friend class RiscV;

    int value;
    List<CCB> blockedQueue;
};


#endif //PROJECT_BASE_SEMAFOR_HPP
