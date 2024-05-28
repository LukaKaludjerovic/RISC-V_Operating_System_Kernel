//
// Created by os on 5/26/23.
//

#include "../h/RiscV.hpp"
#include "../lib/console.h"
#include "../h/MemoryAllocator.hpp"
#include "../h/CCB.hpp"
#include "../h/Semafor.hpp"

void RiscV::popSppSpie() {
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}

void RiscV::handleSupervisorTrap() {
    uint64 scause = RiscV::read_scause();

    switch(scause){
        //ecall
        case 0x09: case 0x08: {
            uint64 sepc = RiscV::read_sepc() + 4;
            uint64 sstatus = RiscV::read_sstatus();
            long code = RiscV::read_a0();

            switch(code){
                //mem_alloc
                case 0x01:{
                    uint64 size_blocks = RiscV::read_a1();
                    void* volatile ret = MemoryAllocator::get_instance()->mem_alloc(size_blocks);
                    RiscV::stack_a0((long) ret);
                    break;
                }

                //mem_free
                case 0x02:{
                    uint64 address = RiscV::read_a1();
                    int ret = MemoryAllocator::get_instance()->mem_free((void*) address);
                    RiscV::stack_a0(ret);
                    break;
                }

                //userMode
                case 0x03:{
                    RiscV::write_sstatus(sstatus);
                    RiscV::write_sepc(sepc);
                    mask_clear_sip(RiscV::SIP_SSIP);
                    RiscV::mask_clear_sstatus(RiscV::SSTATUS_SPP);
                    return;
                }

                //systemMode
                case 0x04:{
                    RiscV::write_sstatus(sstatus);
                    RiscV::write_sepc(sepc);
                    mask_set_sip(RiscV::SIP_SSIP);
                    RiscV::mask_clear_sstatus(RiscV::SSTATUS_SPP);
                    return;
                }

                //thread_create
                case 0x11:{
                    uint64 handle = RiscV::read_a1();
                    uint64 start_routine = RiscV::read_a2();
                    uint64 arg = RiscV::read_a3();
                    CCB::createCCB((CCB**) handle, (CCB::Body) start_routine, (void*) arg);
                    (CCB**)handle != nullptr ? RiscV::stack_a0(0) : RiscV::stack_a0(-1);
                    break;
                }

                //thread_exit
                case 0x12:{
                    if(!CCB::running){
                        RiscV::stack_a0(-1);
                        break;
                    }
                    CCB::running->setFinished(true);
                    CCB::dispatch();
                    RiscV::stack_a0(0);
                    break;
                }

                //thread_dispatch
                case 0x13:{
                    CCB::dispatch();
                    break;
                }

                //thread_join
                case 0x14:{
                    uint64 handle = RiscV::read_a1();
                    while(!((CCB*) handle)->isFinished())
                        CCB::dispatch();
                    break;
                }

                //sem_open
                case 0x21:{
                    uint64 handle = RiscV::read_a1();
                    uint64 value = RiscV::read_a2();
                    Semafor::createSemafor((Semafor**) handle, value);
                    (Semafor**) handle != nullptr ? RiscV::stack_a0(0) : RiscV::stack_a0(-1);
                    break;
                }

                //sem_close
                case 0x22:{
                    uint64 handle = RiscV::read_a1();
                    int ret = ((Semafor*) handle)->close();
                    RiscV::stack_a0(ret);
                    break;
                }

                //sem_wait
                case 0x23:{
                    uint64 handle = RiscV::read_a1();
                    int ret = ((Semafor*) handle)->wait();
                    RiscV::stack_a0(ret);
                    break;
                }

                //sem_signal
                case 0x24:{
                    uint64 handle = RiscV::read_a1();
                    int ret = ((Semafor*) handle)->signal();
                    RiscV::stack_a0(ret);
                    break;
                }

                //0x41
                case 0x41:{
                    char c = __getc();
                    RiscV::stack_a0(c);
                    break;
                }

                //0x42
                case 0x42:{
                    uint64 c = RiscV::read_a1();
                    __putc((char) c);
                    break;
                }

                default: break;
            }

            RiscV::write_sstatus(sstatus);
            RiscV::write_sepc(sepc);
            break;
        }
        //greska
        case 0x07: case 0x05: case 0x02:{
            break;
        }
        //spoljasnji hardverski prekid
        case 0x01UL << 63 | 0x09UL:{
            console_handler();
            break;
        }
        //softverski prekid iz najprivilegovanijeg rezima rada
        case 0x01UL << 63 | 0x01UL:{
            RiscV::mask_clear_sip(SIP_SSIP);
            break;
        }
        default: break;
    }
}
