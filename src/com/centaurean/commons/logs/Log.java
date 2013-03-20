package com.centaurean.commons.logs;

import java.io.PrintStream;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

/*
 * Copyright (c) 2013, Centaurean software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Centaurean software nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Centaurean software BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * jetFlow
 *
 * 20/03/13 02:09
 * @author gpnuma
 */
public class Log {
    private static final DateFormat dateFormat = new SimpleDateFormat("[yyyy-MM-dd HH:mm:ss:SSS] ");

    private static String dateTime() {
        return dateFormat.format(new Date());
    }

    private static void header(PrintStream out, LogLevel level, Class classId) {
        out.print(dateTime());
        out.print(level.getText());
        out.print("[");
        out.print(classId.getCanonicalName());
        out.print("] ");
    }

    public static void message(Class classId, boolean debug, PrintStream out, LogLevel level, String message) {
        if (level == LogLevel.DEBUG && !debug)
            return;
        header(out, level, classId);
        out.println(message);
    }

    public static void message(Class classId, boolean debug, LogLevel level, String message) {
        message(classId, debug, System.out, level, message);
    }

    public static void message(Class classId, boolean debug, String message) {
        message(classId, debug, System.out, LogLevel.DEBUG, message);
    }

    public static void startMessage(Class classId, boolean debug, PrintStream out, LogLevel level, String message) {
        if (level == LogLevel.DEBUG && !debug)
            return;
        header(out, level, classId);
        out.print(message);
        out.println("...");
    }

    public static void startMessage(Class classId, boolean debug, String message) {
        startMessage(classId, debug, System.out, LogLevel.DEBUG, message);
    }

    public static void endMessage(Class classId, boolean debug, PrintStream out, LogLevel level, LogStatus status, String message) {
        if (level == LogLevel.DEBUG && !debug)
            return;
        header(out, level, classId);
        out.print(status.getText());
        out.println(message);
    }

    public static void endMessage(Class classId, boolean debug, LogStatus status, String message) {
        endMessage(classId, debug, System.out, LogLevel.DEBUG, status, message);
    }
}
