#include "../h/RiscV.hpp"
#include "../test/printing.hpp"
#include "../h/syscall_c.hpp"
#include "../h/CCB.hpp"
#include "../h/workers.hpp"
#include "../h/userMain.hpp"
#include "../h/Semafor.hpp"

int main(){
    RiscV::write_stvec((uint64) &RiscV::supervisorTrap);

    int* niz1 = (int*) mem_alloc(50);
    for(int i = 0; i < 50; i++) niz1[i] = i + 1;
    int* niz2 = (int*) mem_alloc(50);
    for(int i = 0; i < 50; i++) niz2[i] = 50 - i;
    int* niz3 = (int*) mem_alloc(50);
    for(int i = 0; i < 50; i++) niz3[i] = niz1[i] + niz2[i];
    mem_free(niz1);
    mem_free(niz2);
    mem_free(niz3);

    userMode();

    CCB* thread;
    thread_create(&thread, nullptr, nullptr);
    CCB::running = thread;

    userMain();

    while(CCB::threads > 1){
        thread_dispatch();
    }
    delete thread;

    return 0;
}