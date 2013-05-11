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
 * 12/05/13 00:05
 * @author gpnuma
 */

#include "BitWriter.h"

BitWriter::BitWriter(std::ofstream* outFileStream) {
    this->outFileStream = outFileStream;
	buffer = new byte[BUFFER_SIZE];
	resetState();
	resetBuffer();
	bitsWritten = 0;
}

BitWriter::~BitWriter() {
	delete[] buffer;
}

void BitWriter::write(bool bit) {
	currentByte |= bit << (7 - state);
	state ++;
	switch(state) {
	case 8:
		addToBuffer(currentByte);
		resetState();
		break;
	}
	bitsWritten ++;
}

void BitWriter::write(unsigned short value) {
	currentByte |= value >> (8 + state);
	addToBuffer(currentByte);

	currentByte = (value >> state) & 0xFFFFFFFF;
	addToBuffer(currentByte);

	currentByte = (value << (8 - state)) & 0xFFFFFFFF;
	bitsWritten += 16;
}

void BitWriter::write(unsigned int value) {
	currentByte |= value >> (24 + state);
	addToBuffer(currentByte);

	currentByte = (value >> (16 + state)) & 0xFFFFFFFF;
	addToBuffer(currentByte);

	currentByte = (value >> (8 + state)) & 0xFFFFFFFF;
	addToBuffer(currentByte);

	currentByte = (value >> state) & 0xFFFFFFFF;
	addToBuffer(currentByte);

	currentByte = (value << (8 - state)) & 0xFFFFFFFF;
	bitsWritten += 32;
}

void BitWriter::resetState() {
	currentByte = 0;
	state = 0;
}

void BitWriter::resetBuffer() {
	position = 0;
}

byte* BitWriter::flush() {
	outFileStream->write((char*)buffer, position);
	resetBuffer();
	return &currentByte;
}

void BitWriter::addToBuffer(byte aByte) {
	buffer[position] = aByte;
	position ++;
	switch(position) {
	case BUFFER_SIZE:
		flush();
		break;
	}
}

unsigned long BitWriter::getBitsWritten() {
	return bitsWritten;
}

