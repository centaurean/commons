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

#include "CpuInfo.h"

void CpuInfo::requestCpuid(unsigned int instruction, uint32_t* data) {
#ifdef _WIN32
    __cpuid((int*)data, (int)instruction);
#else
    asm volatile
        ("cpuid" : "=a" (data[0]), "=b" (data[1]), "=c" (data[2]), "=d" (data[3]) : "a" (instruction), "c" (0));
#endif
}

bool CpuInfo::bitTest(uint32_t bitField, unsigned int shift) {
    return (bitField & ((int)1 << shift)) != 0;
}

CpuInfo::CpuInfo() {
    data = new uint32_t[4];

    requestCpuid(0x0, data);
    vendor_id.append(std::string((const char *)&data[1], 4));
    vendor_id.append(std::string((const char *)&data[3], 4));
    vendor_id.append(std::string((const char *)&data[2], 4));

    requestCpuid(0x1, data);
    uint32_t ids = data[0];
    if (ids >= 1) {
        mmx   = bitTest(data[3], 23);
        sse   = bitTest(data[3], 25);
        sse2  = bitTest(data[3], 26);
        sse3  = bitTest(data[2],  0);
        ssse3 = bitTest(data[2],  9);
        sse41 = bitTest(data[2], 19);
        sse42 = bitTest(data[2], 20);
        avx   = bitTest(data[2], 28);
        fma3  = bitTest(data[2], 12);
        aesni = bitTest(data[2], 25);
    }

    requestCpuid(0x80000000, data);
    uint32_t extendedIds = data[0];
    if (extendedIds >= 0x80000001) {
        requestCpuid(0x80000001, data);
        x64   = bitTest(data[3], 29);
        sse4a = bitTest(data[2],  6);
        fma4  = bitTest(data[2], 16);
        xop   = bitTest(data[2], 11);
    }
}

CpuInfo::~CpuInfo() {
    delete[] data;
}

std::string CpuInfo::getVendorId() {
    return vendor_id;
}

bool CpuInfo::getX64() {
    return x64;
}

bool CpuInfo::getMmx() {
    return mmx;
}

bool CpuInfo::getSse() {
    return sse;
}

bool CpuInfo::getSse2() {
    return sse2;
}

bool CpuInfo::getSse3() {
    return sse3;
}

bool CpuInfo::getSsse3() {
    return ssse3;
}

bool CpuInfo::getSse41() {
    return sse41;
}

bool CpuInfo::getSse42() {
    return sse42;
}

bool CpuInfo::getSse4a() {
    return sse4a;
}

bool CpuInfo::getAvx() {
    return avx;
}

bool CpuInfo::getXop() {
    return xop;
}

bool CpuInfo::getFma3() {
    return fma3;
}

bool CpuInfo::getFma4() {
    return fma4;
}

bool CpuInfo::getAesNI() {
    return aesni;
}

/*int main(int argc, char *argv[]) {
    CpuInfo* cpuInfo = new CpuInfo();

    std::cout << "CPU vendor id = " << cpuInfo->getVendorId() << std::endl;
    std::string features = cpuInfo->getMmx() ? "mmx " : "";
    features += cpuInfo->getSse() ? "sse " : "";
    features += cpuInfo->getSse2() ? "sse2 " : "";
    features += cpuInfo->getSse3() ? "sse3 " : "";
    features += cpuInfo->getSsse3() ? "ssse3 " : "";
    features += cpuInfo->getSse41() ? "sse41 " : "";
    features += cpuInfo->getSse42() ? "sse42 " : "";
    features += cpuInfo->getAvx() ? "avx " : "";
    features += cpuInfo->getFma3() ? "fma3 " : "";
    features += cpuInfo->getX64() ? "x64 " : "";
    features += cpuInfo->getSse4a() ? "sse4a " : "";
    features += cpuInfo->getFma4() ? "fma4 " : "";
    features += cpuInfo->getXop() ? "xop " : "";
    features += cpuInfo->getAesNI() ? "aesni " : "";
    std::cout << "CPU features = " << features << std::endl;

    delete cpuInfo;
}*/

