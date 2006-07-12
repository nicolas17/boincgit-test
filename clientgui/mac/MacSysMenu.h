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

#ifndef _MACSYSMENU_H_
#define _MACSYSMENU_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "MacSysMenu.cpp"
#endif

#include <Carbon/Carbon.h>

#include "BOINCTaskBar.h"

class CMacSystemMenu : public CTaskBarIcon
{
public:
    CMacSystemMenu(wxString title, wxIcon* icon, wxIcon* iconDisconnected, wxIcon* iconSnooze);
    ~CMacSystemMenu();

    bool SetIcon(const wxIcon& icon, const wxString& tooltip = wxEmptyString);

    void LoadPrivateFrameworkBundle( CFStringRef framework, CFBundleRef *bundlePtr );
    //	Function pointer prototypes to the Mach-O Cocoa wrappers
    typedef void	(*SetUpSystemMenuProc)(MenuRef menuToCopy, PicHandle theIcon);
    typedef void	(*SetSystemMenuIconProc)(PicHandle theIcon);

    SetUpSystemMenuProc         SetUpSystemMenu;
    SetSystemMenuIconProc       SetSystemMenuIcon;
    
    bool                        IsOpeningAboutDlg() { return m_OpeningAboutDlg; }
    void                        SetOpeningAboutDlg(bool b) { m_OpeningAboutDlg = b; }
private:
    
    bool                        m_OpeningAboutDlg;

};


#endif

