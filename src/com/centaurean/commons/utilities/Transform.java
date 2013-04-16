package com.centaurean.commons.utilities;

import java.util.Collection;

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
 * jetFlow
 *
 * 25/03/13 16:31
 * @author gpnuma
 */
public class Transform {
    public static int[] toArray(Collection<Integer> integersList) {
        int count = 0;
        int[] result = new int[integersList.size()];
        for(Integer integerElement : integersList)
            result[count ++] = integerElement;
        return result;
    }

    public static long[] toArray(Collection<Long> longList) {
        int count = 0;
        long[] result = new long[longList.size()];
        for(Long longElement : longList)
            result[count ++] = longElement;
        return result;
    }

    public static String toHexArray(long[] longList) {
        int count = longList.length;
        StringBuilder stringBuilder = new StringBuilder("[");
        for(long longElement : longList) {
            stringBuilder.append("0x").append(Long.toHexString(longElement));
            if(--count > 0)
                stringBuilder.append(", ");
        }
        return stringBuilder.append("]").toString();
    }
}
