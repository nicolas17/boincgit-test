// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

#if defined(_WIN32) && !defined(__CYGWIN32__)

#if defined(_WIN64) && defined(_M_X64)
#define HOSTTYPE    "windows_x86_64"
#define HOSTTYPEALT "windows_intelx86"
#else
#define HOSTTYPE "windows_intelx86"
#endif

#include "version.h"         // version numbers from autoconf
#endif

#if !defined(_WIN32) || defined(__CYGWIN32__)
// Please don't create a header of headers for UNIX systems.
// This is partially causes the mess with looking for symbols named "*open64"
// Not to mention the assumption that every source file wants these 
// headers is wrong.
// #include "config.h"
// #include <iostream>
// #include <vector>
// #include <string>
// #include <cstring>
#endif
