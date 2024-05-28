//
// Created by os on 5/26/23.
//

//odredjene funkcionalnosti ove klase su preuzete sa vezbi

#ifndef PROJECT_BASE_RISCV_HPP
#define PROJECT_BASE_RISCV_HPP

#include "../lib/hw.h"

class RiscV {
public:
    static void popSppSpie();

    static void pushRegisters();
    static void popRegisters();

    static uint64 read_scause();
    static void write_scause(uint64 scause);

    static uint64 read_sepc();
    static void write_sepc(uint64 sepc);

    static uint64 read_stvec();
    static void write_stvec(uint64 stvec);

    static uint64 read_stval();
    static void write_stval(uint64 stval);

    enum BitMaskSip{
        SIP_SSIP = 1 << 1,
        SIP_STIP = 1 << 5,
        SIP_SEIP = 1 << 9
    };
    static void mask_set_sip(uint64 mask);
    static void mask_clear_sip(uint64 mask);
    static uint64 read_sip();
    static void write_sip(uint64 sip);

    enum BitMaskSstatus{
        SSTATUS_SIE = 1 << 1,
        SSTATUS_SPIE = 1 << 5,
        SSTATUS_SPP = 1 << 8
    };
    static void mask_set_sstatus(uint64 mask);
    static void mask_clear_sstatus(uint64 mask);
    static uint64 read_sstatus();
    static void write_sstatus(uint64 sstatus);

    static long read_a0();
    static void write_a0(long a0);
    static void stack_a0(long a0);
    static long return_value();

    static uint64 read_a1();
    static void write_a1(uint64 a1);

    static uint64 read_a2();
    static void write_a2(uint64 a2);

    static uint64 read_a3();
    static void write_a3(uint64 a3);

    static uint64 read_a4();
    static void write_a4(uint64 a4);

    static uint64 read_a5();
    static void write_a5(uint64 a5);

    static uint64 read_a6();
    static void write_a6(uint64 a6);

    static uint64 read_a7();
    static void write_a7(uint64 a7);

    static void supervisorTrap();

    static void ecall();

private:
    static void handleSupervisorTrap();

};


inline uint64 RiscV::read_scause() {
    uint64 volatile scause;
    __asm__ volatile ("csrr %[scause], scause" : [scause] "=r"(scause));
    return scause;
}
inline void RiscV::write_scause(uint64 scause) {
    __asm__ volatile ("crrw scause, %[scause]" : : [scause] "r"(scause));
}


inline uint64 RiscV::read_sepc() {
    uint64 volatile sepc;
    __asm__ volatile ("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
    return sepc;
}
inline void RiscV::write_sepc(uint64 sepc) {
    __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
}


inline uint64 RiscV::read_stvec() {
    uint64 volatile stvec;
    __asm__ volatile ("csrr %[stvec], stvec" : [stvec] "=r"(stvec));
    return stvec;
}
inline void RiscV::write_stvec(uint64 stvec) {
    __asm__ volatile ("csrw stvec, %[stvec]" : : [stvec] "r"(stvec));
}


inline uint64 RiscV::read_stval() {
    uint64 volatile stval;
    __asm__ volatile ("csrr %[stval], stval" : [stval] "=r"(stval));
    return stval;
}
inline void RiscV::write_stval(uint64 stval) {
    __asm__ volatile ("csrw stval, %[stval]" : : [stval] "r"(stval));
}


inline void RiscV::mask_set_sip(uint64 mask) {
    __asm__ volatile ("csrs sip, %[mask]" : : [mask] "r"(mask));
}
inline void RiscV::mask_clear_sip(uint64 mask) {
    __asm__ volatile ("csrc sip, %[mask]" : : [mask] "r"(mask));
}
inline uint64 RiscV::read_sip() {
    uint64 volatile sip;
    __asm__ volatile ("csrr %[sip], sip" : [sip] "=r"(sip));
    return sip;
}
inline void RiscV::write_sip(uint64 sip) {
    __asm__ volatile ("csrw sip, %[sip]" : : [sip] "r"(sip));
}


inline void RiscV::mask_set_sstatus(uint64 mask) {
    __asm__ volatile ("csrs sstatus, %[mask]" : : [mask] "r"(mask));
}
inline void RiscV::mask_clear_sstatus(uint64 mask) {
    __asm__ volatile ("csrc sstatus, %[mask]" : : [mask] "r"(mask));
}
inline uint64 RiscV::read_sstatus() {
    uint64 volatile sstatus;
    __asm__ volatile ("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));
    return sstatus;
}
inline void RiscV::write_sstatus(uint64 sstatus) {
    __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
}


inline long RiscV::read_a0() {
    long volatile a0;
    __asm__ volatile ("ld %[a0], 10*8(fp)" : [a0] "=r"(a0));
    return a0;
}
inline void RiscV::write_a0(long a0) {
    __asm__ volatile ("mv a0, %[a0]" : : [a0] "r"(a0));
}
inline void RiscV::stack_a0(long a0) {
    __asm__ volatile ("sd %[a0], 10*8(fp)" : : [a0] "r"(a0));
}
inline long RiscV::return_value() {
    long volatile return_value;
    __asm__ volatile ("mv %[ret], a0" : [ret] "=r"(return_value));
    return return_value;
}


inline uint64 RiscV::read_a1() {
    uint64 volatile a1;
    __asm__ volatile ("ld %[a1], 11*8(fp)" : [a1] "=r"(a1));
    return a1;
}
inline void RiscV::write_a1(uint64 a1) {
    __asm__ volatile ("mv a1, %[a1]" : : [a1] "r"(a1));
}


inline uint64 RiscV::read_a2() {
    uint64 volatile a2;
    __asm__ volatile ("ld %[a2], 12*8(fp)" : [a2] "=r"(a2));
    return a2;
}
inline void RiscV::write_a2(uint64 a2) {
    __asm__ volatile ("mv a2, %[a2]" : : [a2] "r"(a2));
}


inline uint64 RiscV::read_a3() {
    uint64 volatile a3;
    __asm__ volatile ("ld %[a3], 13*8(fp)" : [a3] "=r"(a3));
    return a3;
}
inline void RiscV::write_a3(uint64 a3) {
    __asm__ volatile ("mv a3, %[a3]" : : [a3] "r"(a3));
}


inline uint64 RiscV::read_a4() {
    uint64 volatile a4;
    __asm__ volatile ("ld %[a4], 14*8(fp)" : [a4] "=r"(a4));
    return a4;
}
inline void RiscV::write_a4(uint64 a4) {
    __asm__ volatile ("mv a4, %[a4]" : : [a4] "r"(a4));
}


inline uint64 RiscV::read_a5() {
    uint64 volatile a5;
    __asm__ volatile ("ld %[a5], 15*8(fp)" : [a5] "=r"(a5));
    return a5;
}
inline void RiscV::write_a5(uint64 a5) {
    __asm__ volatile ("mv a5, %[a5]" : : [a5] "r"(a5));
}


inline uint64 RiscV::read_a6() {
    uint64 volatile a6;
    __asm__ volatile ("ld %[a6], 16*8(fp)" : [a6] "=r"(a6));
    return a6;
}
inline void RiscV::write_a6(uint64 a6) {
    __asm__ volatile ("mv a6, %[a6]" : : [a6] "r"(a6));
}


inline uint64 RiscV::read_a7() {
    uint64 volatile a7;
    __asm__ volatile ("ld %[a7], 17*8(fp)" : [a7] "=r"(a7));
    return a7;
}
inline void RiscV::write_a7(uint64 a7) {
    __asm__ volatile ("mv a7, %[a7]" : : [a7] "r"(a7));
}


inline void RiscV::ecall() {
    __asm__ volatile ("ecall");
}

#endif //PROJECT_BASE_RISCV_HPP
