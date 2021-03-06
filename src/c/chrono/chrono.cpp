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
 * 03/05/13 20:53
 * @author gpnuma
 */

#include "chrono.h"

Chrono::Chrono() {
}

Chrono::~Chrono() {
}

void Chrono::start() {
	startTime = clock();
	isRunning = true;
}

void Chrono::stop() {
	if (isRunning) {
		elapsedTime = clock();
		elapsedTime = elapsedTime - startTime;
		isRunning = false;
	}
}

unsigned int Chrono::getElapsedMillis() {
	if (isRunning) {
		elapsedTime = clock();
		elapsedTime = elapsedTime - startTime;
	} 
	return (unsigned int)((1000 * elapsedTime) / CLOCKS_PER_SEC);
}

/*int main(int argc, char *argv[]) {
    Chrono* chrono = new Chrono();

	chrono->start();
	for(unsigned int i = 0; i < 1024 * 1024 * 512; i ++);
	chrono->stop();

    std::cout << "Time = " << chrono->getElapsedMillis() << "ms" << std::endl;

    delete chrono;
}*/
