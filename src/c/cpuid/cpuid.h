#ifndef CPUID_H
#define CPUID_H

#ifdef _WIN32
#include <limits.h>
typedef unsigned __int32  uint32_t;

#else
#include <stdint.h>
#endif

class Cpuid {
  uint32_t regs[4];

public:
  void load(unsigned);
  const uint32_t &EAX() const;
  const uint32_t &EBX() const;
  const uint32_t &ECX() const;
  const uint32_t &EDX() const;
};

#endif