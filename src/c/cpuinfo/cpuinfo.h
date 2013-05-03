/*
 * Copyright (c) 2013, Centaurean
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Centaurean nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Centaurean BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Commons
 *
 * 03/05/13 12:02
 * @author gpnuma
 */

#ifndef CPU_INFO_H
#define CPU_INFO_H

#include <iostream>
using namespace std;

#ifdef _WIN32
#include <limits.h>
typedef unsigned __int32  uint32_t;
#else
#include <stdint.h>
#endif

class CpuInfo {
private:
    uint32_t* data;
    string vendor_id;
    bool x64, mmx, sse, sse2, sse3, ssse3, sse41, sse42, sse4a, avx, xop, fma3, fma4, aesni;

    static void requestCpuid(unsigned int, uint32_t*);
    static bool bitTest(uint32_t, unsigned int);
public:
    CpuInfo();
    ~CpuInfo();

    string getVendorId();
    bool getX64();
    bool getMmx();
    bool getSse();
    bool getSse2();
    bool getSse3();
    bool getSsse3();
    bool getSse41();
    bool getSse42();
    bool getSse4a();
    bool getAvx();
    bool getXop();
    bool getFma3();
    bool getFma4();
    bool getAesNI();
};

#endif