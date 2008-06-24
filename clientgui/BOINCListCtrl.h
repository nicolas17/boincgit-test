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
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef _BOINCLISTCTRL_H_
#define _BOINCLISTCTRL_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "BOINCListCtrl.cpp"
#endif

#ifdef __WXMSW__
#define USE_NATIVE_LISTCONTROL 1
#else
#define USE_NATIVE_LISTCONTROL 0
#endif

#if USE_NATIVE_LISTCONTROL
#define LISTCTRL_BASE wxListCtrl
#include "wx/listctrl.h"
#else
#define LISTCTRL_BASE wxGenericListCtrl
#include "wx/generic/listctrl.h"
#endif

class CBOINCBaseView;
class CDrawBarGraphEvent;

class CBOINCListCtrl : public LISTCTRL_BASE {
    DECLARE_DYNAMIC_CLASS(CBOINCListCtrl)

public:
    CBOINCListCtrl();
    CBOINCListCtrl(CBOINCBaseView* pView, wxWindowID iListWindowID, int iListWindowFlags);

    ~CBOINCListCtrl();

    virtual bool            OnSaveState(wxConfigBase* pConfig);
    virtual bool            OnRestoreState(wxConfigBase* pConfig);

private:
    virtual void            OnClick(wxCommandEvent& event);

    virtual wxString        OnGetItemText(long item, long column) const;
    virtual int             OnGetItemImage(long item) const;
    virtual wxListItemAttr* OnGetItemAttr(long item) const;

    bool                    m_bIsSingleSelection;

    CBOINCBaseView*         m_pParentView;

#if USE_NATIVE_LISTCONTROL
public:
   void PostDrawBarGraphEvent();
private:
    void OnDrawBarGraph(CDrawBarGraphEvent& event);
    void DrawBarGraphs(void);
    
    bool m_bBarGraphEventPending;
#else
 public:
    void DrawBarGraphs(void);
//    wxScrolledWindow* GetMainWin(void) { return (wxScrolledWindow*) ((wxGenericListCtrl*)this)->m_mainWin; }
//    wxCoord GetHeaderHeight(void) { return ((wxGenericListCtrl*)this)->m_headerHeight; }
    wxScrolledWindow* GetMainWin(void) { return (wxScrolledWindow*) m_mainWin; }
    wxCoord GetHeaderHeight(void) { return m_headerHeight; }
    long GetFocusedItem() { return GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_FOCUSED); }
    long GetFirstSelected() { return GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED); }
#endif
};

class CDrawBarGraphEvent : public wxEvent
{
public:
    CDrawBarGraphEvent(wxEventType evtType, CBOINCListCtrl* myCtrl)
        : wxEvent(-1, evtType)
        {
            SetEventObject(myCtrl);
        }

    virtual wxEvent *Clone() const { return new CDrawBarGraphEvent(*this); }
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_DRAW_BARGRAPH, 10000 )
END_DECLARE_EVENT_TYPES()

#define EVT_DRAW_BARGRAPH(fn)            DECLARE_EVENT_TABLE_ENTRY(wxEVT_DRAW_BARGRAPH, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),


// Define a custom event handler
class MyEvtHandler : public wxEvtHandler
{
public:
    MyEvtHandler(CBOINCListCtrl *theListControl) { m_listCtrl = theListControl; }
    void OnPaint(wxPaintEvent & event);

private:
    CBOINCListCtrl *m_listCtrl;

    DECLARE_EVENT_TABLE()
};

#endif

