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

#ifndef _PROJECTSCOMPONENT_H_
#define _PROJECTSCOMPONENT_H_


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "sg_ProjectsComponent.cpp"
#endif

class SkinClass;
class StatImageLoader;
class CSimplePanel;
class ImageLoader;
class CTransparentStaticLine;

class CProjectsComponent : public wxPanel {
    DECLARE_DYNAMIC_CLASS( CProjectsComponent )

public:
	
	int clientRunMode;
	int clientNetworkMode;
	char defaultIcnPath[256];
	// projects vector
	std::vector<StatImageLoader*> m_statProjects; // vector of all project icons created for GUI
	wxImage *g_statIcn;
	//static content
	wxStaticText *stMyProj;
	CTransparentStaticLine *lnMyProjTop;
	CTransparentStaticLine *lnMyProjBtm;
	// default icon
	// spacer
	ImageLoader *i_spacer1;
	ImageLoader *i_spacer2;
	ImageLoader *i_spacer3;

	wxBitmapButton *btnArwLeft;
	wxBitmapButton *btnArwRight;
	wxBitmapButton *btnAddProj;
	wxBitmapButton *btnSynchronize;
	wxBitmapButton *btnHelp;
	wxBitmapButton *btnMessages;
	wxBitmapButton *btnAlertMessages;
	wxBitmapButton *btnPause;
	wxBitmapButton *btnResume;
	wxBitmapButton *btnPreferences;
	wxBitmapButton *btnAdvancedView;
    wxWindow       *w_sp1;
    wxWindow       *w_sp2;
    wxWindow       *w_sp3;
	
    CProjectsComponent();
    CProjectsComponent(CSimplePanel* parent,wxPoint coord);
    ~CProjectsComponent();

    void CreateComponent();
	void UpdateInterface();
	void ReskinInterface();
    void OnBtnClick(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event); 
	void UpdateProjectArray();

    void OnHelp(wxCommandEvent& event);
    void OnPreferences(wxCommandEvent& event);
    void OnMessages(wxCommandEvent& event);
    void OnSuspend(wxCommandEvent& event);
    void OnResume(wxCommandEvent& event);
    void OnAttachToProject(wxCommandEvent& event);
    void OnSynchronize(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()

protected:
	void OnEraseBackground(wxEraseEvent& event);

private:
	wxTimer* checkForMessagesTimer;
	int m_maxNumOfIcons;
	int m_leftIndex;
	bool receivedErrorMessage;
	bool alertMessageDisplayed;
	size_t lastMessageId;
	void OnMessageCheck(wxTimerEvent& WXUNUSED(event));
   	void MessagesViewed();
	void UpdateDisplayedProjects();
};

#endif

