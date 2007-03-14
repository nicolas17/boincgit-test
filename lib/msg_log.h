// Berkeley Open Infrastructure for Network Computing
// http://boinc.berkeley.edu
// Copyright (C) 2005 University of California
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation;
// either version 2.1 of the License, or (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// To view the GNU Lesser General Public License visit
// http://www.gnu.org/copyleft/lesser.html
// or write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef _BOINC_MSG_LOG_H_
#define _BOINC_MSG_LOG_H_

#include <cstdio>
#include <cstdarg>

#ifdef _USING_FCGI_
#include "fcgi_stdio.h"
#endif

// the __attribute((format...)) tags are GCC extensions that let the compiler
// do like-checking on printf-like arguments
//
#if !defined(__GNUC__) && !defined(__attribute__)
#define __attribute__(x) /*nothing*/
#endif

#ifdef _USING_FCGI_
#define __attribute__(x) /*nothing*/
#endif

class MSG_LOG {
    int debug_level;
    int indent_level;
    char spaces[80];
    FILE* output;
public:
    int pid;

    MSG_LOG(FILE* output);
    virtual ~MSG_LOG(){}
    void enter_level(int = 1);
    void leave_level() { enter_level(-1); }
    MSG_LOG& operator++() { enter_level(); return *this; }
    MSG_LOG& operator--() { leave_level(); return *this; }

    void printf(int kind, const char* format, ...) __attribute__ ((format (printf, 3, 4)));
    void printf_multiline(int kind, const char* str, const char* prefix_format, ...) __attribute__ ((format (printf, 4, 5)));
    void printf_file(int kind, const char* filename, const char* prefix_format, ...) __attribute__ ((format (printf, 4, 5)));
    void vprintf(int kind, const char* format, va_list va);
    void vprintf_multiline(int kind, const char* str, const char* prefix_format, va_list va);
    void vprintf_file(int kind, const char* filename, const char* prefix_format, va_list va);

protected:

    virtual const char* v_format_kind(int kind) const = 0;
    virtual bool v_message_wanted(int kind) const = 0;
};

// automatically ++/--MSG_LOG on scope entry / exit.
// See lib/msg_log.C for commentary
//
#if _MSC_VER >= 1300
#pragma warning(disable: 4512) // assignment operator could not be generated
#endif

class SCOPE_MSG_LOG {
    MSG_LOG& messages;
    int kind;
public:
    SCOPE_MSG_LOG(MSG_LOG& messages_, int kind_) : messages(messages_), kind(kind_)
    { ++messages; }
    ~SCOPE_MSG_LOG() { --messages; }
    SCOPE_MSG_LOG& operator++() { ++messages; return *this; }
    SCOPE_MSG_LOG& operator--() { --messages; return *this; }

    void printf(const char* format, ...) __attribute__ ((format (printf, 2, 3)));
    void printf_multiline(const char* str, const char* prefix_format, ...) __attribute__ ((format (printf, 3, 4)));
    void printf_file(const char* filename, const char* prefix_format, ...) __attribute__ ((format (printf, 3, 4)));
};

#if _MSC_VER >= 1300
#pragma warning(default: 4512) // assignment operator could not be generated
#endif

#endif
