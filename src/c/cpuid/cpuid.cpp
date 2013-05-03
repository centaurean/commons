#include "cpuid.h"

void Cpuid::load(unsigned instruction) {
#ifdef _WIN32
    __cpuid((int *)regs, (int)instruction);

#else
  asm volatile
    ("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
     : "a" (instruction), "c" (0));
  // ECX is set to zero for CPUID function 4
#endif
}

const uint32_t Cpuid::&EAX() const {
    return regs[0];
}

const uint32_t Cpuid::&EBX() const {
    return regs[1];
}

const uint32_t Cpuid::&ECX() const {
    return regs[2];
}

const uint32_t Cpuid::&EDX() const {
    return regs[3];
}