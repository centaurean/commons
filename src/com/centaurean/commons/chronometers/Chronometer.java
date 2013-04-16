package com.centaurean.commons.chronometers;

import java.util.concurrent.locks.ReentrantLock;

import static com.centaurean.commons.chronometers.Precision.*;

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
 * 20/03/13 08:49
 * @author gpnuma
 */
public class Chronometer {
    private static int nextId = 0;
    private static final ReentrantLock lock = new ReentrantLock();

    private int id;
    private long start;
    private long stop;
    private boolean started;
    private boolean stopped;

    public static Chronometer newInstance() {
        return new Chronometer();
    }

    public Chronometer() {
        id = nextId();
        reset();
    }

    private static int nextId() {
        int newId;
        lock.lock();
        newId = nextId++;
        lock.unlock();
        return newId;
    }

    public Chronometer reset() {
        started = false;
        stopped = false;
        return this;
    }

    public Chronometer start() {
        if (started)
            throw new ChronometerAlreadyStartedException();
        started = true;
        start = System.nanoTime();
        return this;
    }

    public Chronometer stop() {
        if (!started)
            throw new ChronometerNotStartedException();
        if (stopped)
            throw new ChronometerAlreadyStoppedException();
        stopped = true;
        stop = System.nanoTime();
        return this;
    }

    public boolean started() {
        return started;
    }

    public boolean stopped() {
        return stopped;
    }

    public long lap() {
        if (!started)
            throw new ChronometerNotStartedException();
        return System.nanoTime() - start;
    }

    public long elapsed() {
        if (!started)
            throw new ChronometerNotStartedException();
        if (!stopped)
            throw new ChronometerNotStoppedException();
        return stop - start;
    }

    private long extract(StringBuilder stringBuilder, long time, long part, String label) {
        if (time > part) {
            long quantity = time / part;
            stringBuilder.append(quantity).append(label).append(" ");
            time -= quantity * part;
        }
        return time;
    }

    public String toString(Precision precision) {
        if (!started)
            return "";
        if (!stopped)
            return "Running";
        StringBuilder result = new StringBuilder();
        long elapsed = elapsed();
        if (precision.getValue() <= HOUR.getValue())
            elapsed = extract(result, elapsed, HOUR.getValue(), HOUR.getLabel());
        if (precision.getValue() <= MINUTE.getValue())
            elapsed = extract(result, elapsed, MINUTE.getValue(), MINUTE.getLabel());
        if (precision.getValue() <= SECOND.getValue())
            elapsed = extract(result, elapsed, SECOND.getValue(), SECOND.getLabel());
        if (precision.getValue() <= MILLISECOND.getValue())
            elapsed = extract(result, elapsed, MILLISECOND.getValue(), MILLISECOND.getLabel());
        if (precision.getValue() <= MICROSECOND.getValue())
            elapsed = extract(result, elapsed, MICROSECOND.getValue(), MICROSECOND.getLabel());
        if (precision.getValue() <= NANOSECOND.getValue())
            extract(result, elapsed, NANOSECOND.getValue(), NANOSECOND.getLabel());
        return result.toString().trim();
    }

    @Override
    public boolean equals(Object object) {
        if (object == null)
            return false;
        if (object == this)
            return true;
        if (!(object instanceof Chronometer))
            return false;
        Chronometer chronometer = (Chronometer) object;
        return (hashCode() == chronometer.hashCode());
    }

    @Override
    public int hashCode() {
        return id;
    }

    @Override
    public String toString() {
        return toString(Precision.NANOSECOND);
    }
}
