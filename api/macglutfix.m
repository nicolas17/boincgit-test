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

//
//  macglutfix.m
//

#include <Cocoa/Cocoa.h>

#include "boinc_api.h"

void MacGLUTFix(bool isScreenSaver);
void BringAppToFront(void);

// The standard ScreenSaverView class actually sets the window 
// level to 2002, not the 1000 defined by NSScreenSaverWindowLevel 
// and kCGScreenSaverWindowLevel
#define RealSaverLevel 2002

// Delay when switching to screensaver mode to reduce annoying flashes
#define SAVERDELAY 30

void MacGLUTFix(bool isScreenSaver) {
    static NSMenu * emptyMenu;
    NSOpenGLContext * myContext = nil;
    NSView *myView = nil;
    NSWindow* myWindow = nil;
    int newWindowLevel;
    static int stabilizationDelay = 0;

    if (! boinc_is_standalone()) {
        if (emptyMenu == nil) {
            emptyMenu = [ NSMenu alloc ];
            [ NSApp setMainMenu:emptyMenu ];
        }
    }

    // In screensaver mode, set our window's level just above 
    // our BOINC screensaver's window level so it can appear 
    // over it.  This doesn't interfere with the screensaver 
    // password dialog because the dialog appears only after 
    // our screensaver is closed.
    myContext = [ NSOpenGLContext currentContext ];
    if (myContext)
        myView = [ myContext view ];
    if (myView)
        myWindow = [ myView window ];
    if (myWindow == nil)
        return;
        
    newWindowLevel = isScreenSaver ? RealSaverLevel+20 : NSNormalWindowLevel;
    if ([ myWindow level ] == newWindowLevel)
    {
        stabilizationDelay = 0;
        return;
    }
    
    if (++stabilizationDelay < SAVERDELAY)
        return;
        
    [ myWindow setLevel:newWindowLevel ];
}

void BringAppToFront() {
    [ NSApp activateIgnoringOtherApps:YES ];
}
