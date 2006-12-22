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


#ifndef _DLG_MESSAGES_H_ 
#define _DLG_MESSAGES_H_ 

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "sg_DlgMessages.cpp"
#endif


/*!
 * Includes
 */

////@begin includes
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class CSGUIListCtrl;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DLGMESSAGES 10000
#define SYMBOL_CDLGMESSAGES_STYLE wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER
#define SYMBOL_CDLGMESSAGES_TITLE wxT("")
#define SYMBOL_CDLGMESSAGES_IDNAME ID_DLGMESSAGES
#define SYMBOL_CDLGMESSAGES_SIZE wxDefaultSize
#define SYMBOL_CDLGMESSAGES_POSITION wxDefaultPosition
#define ID_COPYSELECTED 10001
#define ID_COPYAll 10002
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif


/*!
 * CPanelPreferences class declaration
 */

class CPanelMessages : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( CPanelMessages )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CPanelMessages( );
    CPanelMessages( wxWindow* parent );

    /// Destructors
    ~CPanelMessages( );

    /// Creation
    bool Create();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CPanelMessages event handler declarations
    /// wxEVT_ERASE_BACKGROUND event handler for ID_DLGMESSAGES
    void OnEraseBackground( wxEraseEvent& event );

    /// wxEVT_TIMER event handler for ID_REFRESHMESSAGESTIMER
    void OnRefresh( wxTimerEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOK( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_COPYAll
    void OnMessagesCopyAll( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_COPYSELECTED
    void OnMessagesCopySelected( wxCommandEvent& event );

////@end CPanelMessages event handler declarations

////@begin CPanelMessages member function declarations
////@end CPanelMessages member function declarations

    virtual wxString        OnListGetItemText( long item, long column ) const;
	virtual wxListItemAttr* OnListGetItemAttr( long item ) const;

    bool                    OnSaveState(wxConfigBase* pConfig);
    bool                    OnRestoreState(wxConfigBase* pConfig);

private:
	wxInt32                 m_iPreviousDocCount;

    CSGUIListCtrl*          m_pList;
    wxListItemAttr*         m_pMessageInfoAttr;
    wxListItemAttr*         m_pMessageErrorAttr;

    bool                    m_bProcessingRefreshEvent;
    bool                    m_bForceUpdateSelection;

	wxTimer*                m_pRefreshMessagesTimer;

    bool                    EnsureLastItemVisible();
	wxInt32                 FormatProjectName( wxInt32 item, wxString& strBuffer ) const;
    wxInt32                 FormatPriority( wxInt32 item, wxString& strBuffer ) const;
    wxInt32                 FormatTime( wxInt32 item, wxString& strBuffer ) const;
    wxInt32                 FormatMessage( wxInt32 item, wxString& strBuffer ) const;

#ifdef wxUSE_CLIPBOARD
    bool                    m_bClipboardOpen;
    wxString                m_strClipboardData;
    bool                    OpenClipboard();
    wxInt32                 CopyToClipboard( wxInt32 item );
    bool                    CloseClipboard();
#endif

    wxInt32                 GetDocCount();
};


class CDlgMessages : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CDlgMessages )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CDlgMessages( );
    CDlgMessages( wxWindow* parent, wxWindowID id = SYMBOL_CDLGMESSAGES_IDNAME, const wxString& caption = SYMBOL_CDLGMESSAGES_TITLE, const wxPoint& pos = SYMBOL_CDLGMESSAGES_POSITION, const wxSize& size = SYMBOL_CDLGMESSAGES_SIZE, long style = SYMBOL_CDLGMESSAGES_STYLE );

    ~CDlgMessages();
    
    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CDLGMESSAGES_IDNAME, const wxString& caption = SYMBOL_CDLGMESSAGES_TITLE, const wxPoint& pos = SYMBOL_CDLGMESSAGES_POSITION, const wxSize& size = SYMBOL_CDLGMESSAGES_SIZE, long style = SYMBOL_CDLGMESSAGES_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

    /// wxEVT_SHOW event handler for ID_DLGMESSAGES
    void OnShow( wxShowEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOK( wxCommandEvent& event );

private:

    bool SaveState();
    void SaveWindowDimensions();
    bool RestoreState();
    void RestoreWindowDimensions();

////@begin CDlgMessages member variables
    CPanelMessages* m_pBackgroundPanel;
////@end CDlgMessages member variables
};


#endif  // end CDlgMessages
