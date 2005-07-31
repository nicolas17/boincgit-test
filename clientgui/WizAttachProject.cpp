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
#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "WizAttachProject.h"
#endif

#include "stdwx.h"
#include "BOINCGUIApp.h"

////@begin includes
////@end includes

#include "WizAttachProject.h"

////@begin XPM images
#include "res/attachprojectwizard.xpm"
#include "res/wizquestion.xpm"
#include "res/wizsuccess.xpm"
#include "res/wizfailure.xpm"
////@end XPM images


/*!
 * CWizAttachProject global helper macros
 */
#define PAGE_TRANSITION_NEXT(id) \
    ((CWizAttachProject*)GetParent())->PushPageTransition((wxWizardPage*)this, id)

#define PAGE_TRANSITION_BACK \
    ((CWizAttachProject*)GetParent())->PopPageTransition()

#define CHECK_DEBUG_FLAG \
    ((CWizAttachProject*)GetParent())->IsDiagFlagsSet(id)

/*!
 * CWizAttachProject type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CWizAttachProject, wxWizard )

/*!
 * CWizAttachProject event table definition
 */

BEGIN_EVENT_TABLE( CWizAttachProject, wxWizard )

////@begin CWizAttachProject event table entries
    EVT_WIZARD_CANCEL( ID_ATTACHPROJECTWIZARD, CWizAttachProject::OnWizardCancel )

////@end CWizAttachProject event table entries

END_EVENT_TABLE()

/*!
 * CWizAttachProject constructors
 */

CWizAttachProject::CWizAttachProject( )
{
}

CWizAttachProject::CWizAttachProject( wxWindow* parent, wxWindowID id, const wxPoint& pos )
{
    Create(parent, id, pos);
}

/*!
 * CWizAttachProject creator
 */

bool CWizAttachProject::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos )
{
////@begin CWizAttachProject member initialisation
    m_WelcomePage = NULL;
    m_ProjectInfoPage = NULL;
    m_ProjectPropertiesPage = NULL;
    m_AccountKeyPage = NULL;
    m_AccountInfoPage = NULL;
    m_AccountCreationPage = NULL;
    m_CompletionPage = NULL;
    m_ErrProjectUnavailablePage = NULL;
    m_ErrNoInternetConnectionPage = NULL;
    m_ErrAccountAlreadyExistsPage = NULL;
    m_ErrAccountCreationDisabledPage = NULL;
    m_ErrProxyInfoPage = NULL;
    m_ErrProxyHTTPPage = NULL;
    m_ErrProxySOCKSPage = NULL;
    m_ErrProxyCompletionPage = NULL;
////@end CWizAttachProject member initialisation

    m_ulDiagFlags = 0;

////@begin CWizAttachProject creation
    wxBitmap wizardBitmap(GetBitmapResource(wxT("res/attachprojectwizard.xpm")));
    wxWizard::Create( parent, id, _("Attach to Project Wizard"), wizardBitmap, pos );

    CreateControls();
////@end CWizAttachProject creation
    return TRUE;
}

/*!
 * Control creation for CWizAttachProject
 */

void CWizAttachProject::CreateControls()
{    
    wxLogTrace(wxT("Function Start/End"), wxT("CWizAttachProject::CreateControls - Function Begin"));

////@begin CWizAttachProject content construction
    wxWizard* itemWizard1 = this;

    m_WelcomePage = new CWelcomePage;
    m_WelcomePage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_WelcomePage);
    m_ProjectInfoPage = new CProjectInfoPage;
    m_ProjectInfoPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ProjectInfoPage);
    m_ProjectPropertiesPage = new CProjectPropertiesPage;
    m_ProjectPropertiesPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ProjectPropertiesPage);
    m_AccountKeyPage = new CAccountKeyPage;
    m_AccountKeyPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_AccountKeyPage);
    m_AccountInfoPage = new CAccountInfoPage;
    m_AccountInfoPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_AccountInfoPage);
    m_AccountCreationPage = new CAccountCreationPage;
    m_AccountCreationPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_AccountCreationPage);
    m_CompletionPage = new CCompletionPage;
    m_CompletionPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_CompletionPage);
    m_ErrProjectUnavailablePage = new CErrProjectUnavailablePage;
    m_ErrProjectUnavailablePage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrProjectUnavailablePage);
    m_ErrNoInternetConnectionPage = new CErrNoInternetConnectionPage;
    m_ErrNoInternetConnectionPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrNoInternetConnectionPage);
    m_ErrAccountAlreadyExistsPage = new CErrAccountAlreadyExistsPage;
    m_ErrAccountAlreadyExistsPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrAccountAlreadyExistsPage);
    m_ErrAccountCreationDisabledPage = new CErrAccountCreationDisabledPage;
    m_ErrAccountCreationDisabledPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrAccountCreationDisabledPage);
    m_ErrProxyInfoPage = new CErrProxyInfoPage;
    m_ErrProxyInfoPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrProxyInfoPage);
    m_ErrProxyHTTPPage = new CErrProxyHTTPPage;
    m_ErrProxyHTTPPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrProxyHTTPPage);
    m_ErrProxySOCKSPage = new CErrProxySOCKSPage;
    m_ErrProxySOCKSPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrProxySOCKSPage);
    m_ErrProxyCompletionPage = new CErrProxyComplationPage;
    m_ErrProxyCompletionPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrProxyCompletionPage);
    wxWizardPageSimple* lastPage = NULL;
////@end CWizAttachProject content construction

    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls - Begin Page Map"));
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_WelcomePage = id: '%d', location: '%p'"), ID_WELCOMEPAGE, m_WelcomePage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ProjectInfoPage = id: '%d', location: '%p'"), ID_PROJECTINFOPAGE, m_ProjectInfoPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ProjectPropertiesPage = id: '%d', location: '%p'"), ID_PROJECTPROPERTIESPAGE, m_AccountKeyPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_AccountKeyPage = id: '%d', location: '%p'"), ID_ACCOUNTKEYPAGE, m_AccountKeyPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_AccountInfoPage = id: '%d', location: '%p'"), ID_ACCOUNTINFOPAGE, m_AccountInfoPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_AccountCreationPage = id: '%d', location: '%p'"), ID_ACCOUNTCREATIONPAGE, m_AccountCreationPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_CompletionPage = id: '%d', location: '%p'"), ID_COMPLETIONPAGE, m_CompletionPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ErrProjectUnavailablePage = id: '%d', location: '%p'"), ID_ERRPROJECTUNAVAILABLEPAGE, m_ErrProjectUnavailablePage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ErrNoInternetConnectionPage = id: '%d', location: '%p'"), ID_ERRNOINTERNETCONNECTIONPAGE, m_ErrNoInternetConnectionPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ErrAccountAlreadyExistsPage = id: '%d', location: '%p'"), ID_ERRACCOUNTALREADYEXISTSPAGE, m_ErrAccountAlreadyExistsPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ErrAccountCreationDisabledPage = id: '%d', location: '%p'"), ID_ERRACCOUNTCREATIONDISABLEDPAGE, m_ErrAccountCreationDisabledPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ErrProxyInfoPage = id: '%d', location: '%p'"), ID_ERRPROXYINFOPAGE, m_ErrProxyInfoPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ErrProxyHTTPPage = id: '%d', location: '%p'"), ID_ERRPROXYHTTPPAGE, m_ErrProxyHTTPPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ErrProxySOCKSPage = id: '%d', location: '%p'"), ID_ERRPROXYSOCKSPAGE, m_ErrProxySOCKSPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ErrProxyCompletionPage = id: '%d', location: '%p'"), ID_ERRPROXYCOMPLETIONPAGE, m_ErrProxyCompletionPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls - End Page Map"));

    wxLogTrace(wxT("Function Start/End"), wxT("CWizAttachProject::CreateControls - Function End"));
}

/*!
 * Runs the wizard.
 */

bool CWizAttachProject::Run()
{
    if (m_WelcomePage) return RunWizard(m_WelcomePage);
    return FALSE;
}

/*!
 * Should we show tooltips?
 */

bool CWizAttachProject::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CWizAttachProject::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CWizAttachProject bitmap retrieval
    if (name == wxT("res/attachprojectwizard.xpm"))
    {
        wxBitmap bitmap(attachprojectwizard_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end CWizAttachProject bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CWizAttachProject::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CWizAttachProject icon retrieval
    return wxNullIcon;
////@end CWizAttachProject icon retrieval
}

/*!
 * Determine if the wizard page has a next page
 */

bool CWizAttachProject::HasNextPage( wxWizardPage* page )
{
    if (page == m_CompletionPage)
        return false;
    return true;
}

/*!
 * Determine if the wizard page has a previous page
 */

bool CWizAttachProject::HasPrevPage( wxWizardPage* page )
{
    if (page == m_WelcomePage)
        return false;
    return true;
}

/*!
 * Set the diagnostics flags.
 */

void CWizAttachProject::SetDiagFlags( unsigned long ulFlags )
{
    m_ulDiagFlags = ulFlags;
}

/*!
 * Check the desired bitmask against our existing bitmask.
 */

bool CWizAttachProject::IsDiagFlagsSet( unsigned long ulFlags )
{
    if (ulFlags & m_ulDiagFlags) {
        return true;
    }
    return false;
}

/*!
 * Remove the page transition to the stack.
 */

wxWizardPage* CWizAttachProject::PopPageTransition() 
{
    if (GetCurrentPage()) {
        if (m_PageTransition.size() > 0) {
            wxWizardPage* pPage = m_PageTransition.top();
            m_PageTransition.pop();
            wxASSERT(pPage);
            return pPage;
        }
    }
    return NULL;
}

/*!
 * Add the page transition to the stack.
 */
wxWizardPage* CWizAttachProject::PushPageTransition( wxWizardPage* pCurrentPage, unsigned long ulPageID )
{
    if (GetCurrentPage()) {
        wxWizardPage* pPage = NULL;

        if (ID_WELCOMEPAGE == ulPageID)
            pPage = m_WelcomePage;

        if (ID_PROJECTINFOPAGE == ulPageID)
            pPage = m_ProjectInfoPage;

        if (ID_PROJECTPROPERTIESPAGE == ulPageID)
            pPage = m_ProjectPropertiesPage;

        if (ID_ACCOUNTINFOPAGE == ulPageID)
            pPage = m_AccountInfoPage;

        if (ID_ACCOUNTKEYPAGE == ulPageID)
            pPage = m_AccountKeyPage;

        if (ID_ACCOUNTCREATIONPAGE == ulPageID)
            pPage = m_AccountCreationPage;

        if (ID_COMPLETIONPAGE == ulPageID)
            pPage = m_CompletionPage;

        if (ID_ERRPROJECTUNAVAILABLEPAGE == ulPageID)
            pPage = m_ErrProjectUnavailablePage;

        if (ID_ERRNOINTERNETCONNECTIONPAGE == ulPageID)
            pPage = m_ErrNoInternetConnectionPage;

        if (ID_ERRACCOUNTALREADYEXISTSPAGE == ulPageID)
            pPage = m_ErrAccountAlreadyExistsPage;

        if (ID_ERRACCOUNTCREATIONDISABLEDPAGE == ulPageID)
            pPage = m_ErrAccountCreationDisabledPage;

        if (ID_ERRPROXYINFOPAGE == ulPageID)
            pPage = m_ErrProxyInfoPage;

        if (ID_ERRPROXYHTTPPAGE == ulPageID)
            pPage = m_ErrProxyHTTPPage;

        if (ID_ERRPROXYSOCKSPAGE == ulPageID)
            pPage = m_ErrProxySOCKSPage;

        if (ID_ERRPROXYCOMPLETIONPAGE == ulPageID)
            pPage = m_ErrProxyCompletionPage;

        if (pPage) {
            if ((pCurrentPage == m_WelcomePage) && (m_PageTransition.size() == 0)) {
                m_PageTransition.push(NULL);
            }
            if (m_PageTransition.top() != pCurrentPage) {
                m_PageTransition.push(pCurrentPage);
            }
            return pPage;
        }
    }
    return NULL;
}

void CWizAttachProject::OnWizardCancel( wxWizardEvent& event )
{
    if ( wxMessageBox( _("Do you really want to cancel?"), _("Question"),
         wxICON_QUESTION | wxYES_NO, this ) != wxYES
       )
    {
        // not confirmed
        event.Veto();
    }
}


/*!
 * CWelcomePage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CWelcomePage, wxWizardPage )

/*!
 * CWelcomePage event table definition
 */

BEGIN_EVENT_TABLE( CWelcomePage, wxWizardPage )

////@begin CWelcomePage event table entries
    EVT_WIZARD_PAGE_CHANGING( -1, CWelcomePage::OnPageChanging )

////@end CWelcomePage event table entries

END_EVENT_TABLE()

/*!
 * CWelcomePage constructors
 */

CWelcomePage::CWelcomePage( )
{
}

CWelcomePage::CWelcomePage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * WizardPage creator
 */

bool CWelcomePage::Create( wxWizard* parent )
{
////@begin CWelcomePage member initialisation
    m_ErrProjectPropertiesCtrl = NULL;
    m_ErrProjectCommCtrl = NULL;
    m_ErrProjectPropertiesURLCtrl = NULL;
    m_ErrAccountCreationDisabledCtrl = NULL;
    m_ErrAccountAlreadyExistsCtrl = NULL;
    m_ErrGoogleCommCtrl = NULL;
    m_ErrYahooCommCtrl = NULL;
    m_ErrNetDetectionCtrl = NULL;
////@end CWelcomePage member initialisation

////@begin CWelcomePage creation
    wxBitmap wizardBitmap(GetBitmapResource(wxT("res/attachprojectwizard.xpm")));
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CWelcomePage creation
    return TRUE;
}

/*!
 * Control creation for WizardPage
 */

void CWelcomePage::CreateControls()
{    
////@begin CWelcomePage content construction
    CWelcomePage* itemWizardPage2 = this;

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage2->SetSizer(itemBoxSizer3);

    wxStaticText* itemStaticText4 = new wxStaticText;
    itemStaticText4->Create( itemWizardPage2, wxID_STATIC, _("Welcome to the Attach to Project\nWizard"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText4->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText;
    itemStaticText5->Create( itemWizardPage2, wxID_STATIC, _("This wizard will guide you through the process of attaching to a project."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText5, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer3->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText;
    itemStaticText7->Create( itemWizardPage2, wxID_STATIC, _("This wizard will require access to the Internet in order to attach to\na project using an existing account or creating a new one."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText7, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer8Static = new wxStaticBox(itemWizardPage2, wxID_ANY, _("Debug Flags"));
    wxStaticBoxSizer* itemStaticBoxSizer8 = new wxStaticBoxSizer(itemStaticBoxSizer8Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer8, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer9 = new wxFlexGridSizer(-1, 2, 0, 0);
    itemFlexGridSizer9->AddGrowableCol(0);
    itemFlexGridSizer9->AddGrowableCol(1);
    itemStaticBoxSizer8->Add(itemFlexGridSizer9, 0, wxGROW|wxALL, 5);

    m_ErrProjectPropertiesCtrl = new wxCheckBox;
    m_ErrProjectPropertiesCtrl->Create( itemWizardPage2, ID_ERRPROJECTPROPERTIES, _("Project Properties Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrProjectPropertiesCtrl->SetValue(FALSE);
    itemFlexGridSizer9->Add(m_ErrProjectPropertiesCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrProjectCommCtrl = new wxCheckBox;
    m_ErrProjectCommCtrl->Create( itemWizardPage2, ID_ERRPROJECTCOMM, _("Project Comm Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrProjectCommCtrl->SetValue(FALSE);
    itemFlexGridSizer9->Add(m_ErrProjectCommCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrProjectPropertiesURLCtrl = new wxCheckBox;
    m_ErrProjectPropertiesURLCtrl->Create( itemWizardPage2, ID_ERRPROJECTPROPERTIESURL, _("Project Properties URL Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrProjectPropertiesURLCtrl->SetValue(FALSE);
    itemFlexGridSizer9->Add(m_ErrProjectPropertiesURLCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrAccountCreationDisabledCtrl = new wxCheckBox;
    m_ErrAccountCreationDisabledCtrl->Create( itemWizardPage2, ID_ERRACCOUNTCREATIONDISABLED, _("Account Creation Disabled"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrAccountCreationDisabledCtrl->SetValue(FALSE);
    itemFlexGridSizer9->Add(m_ErrAccountCreationDisabledCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrAccountAlreadyExistsCtrl = new wxCheckBox;
    m_ErrAccountAlreadyExistsCtrl->Create( itemWizardPage2, ID_ERRACCOUNTALREADYEXISTS, _("Account Already Exists"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrAccountAlreadyExistsCtrl->SetValue(FALSE);
    itemFlexGridSizer9->Add(m_ErrAccountAlreadyExistsCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrGoogleCommCtrl = new wxCheckBox;
    m_ErrGoogleCommCtrl->Create( itemWizardPage2, ID_ERRGOOGLECOMM, _("Google Comm Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrGoogleCommCtrl->SetValue(FALSE);
    itemFlexGridSizer9->Add(m_ErrGoogleCommCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrYahooCommCtrl = new wxCheckBox;
    m_ErrYahooCommCtrl->Create( itemWizardPage2, ID_ERRYAHOOCOMM, _("Yahoo Comm Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrYahooCommCtrl->SetValue(FALSE);
    itemFlexGridSizer9->Add(m_ErrYahooCommCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrNetDetectionCtrl = new wxCheckBox;
    m_ErrNetDetectionCtrl->Create( itemWizardPage2, ID_ERRNETDETECTION, _("Net Detection Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrNetDetectionCtrl->SetValue(FALSE);
    itemFlexGridSizer9->Add(m_ErrNetDetectionCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    wxStaticText* itemStaticText18 = new wxStaticText;
    itemStaticText18->Create( itemWizardPage2, wxID_STATIC, _("To continue, click Next."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText18, 0, wxALIGN_LEFT|wxALL, 5);

////@end CWelcomePage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CWelcomePage::GetPrev() const
{
    return NULL;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CWelcomePage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_PROJECTINFOPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CWelcomePage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CWelcomePage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CWelcomePage bitmap retrieval
    if (name == wxT("res/attachprojectwizard.xpm"))
    {
        wxBitmap bitmap(attachprojectwizard_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end CWelcomePage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CWelcomePage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CWelcomePage icon retrieval
    return wxNullIcon;
////@end CWelcomePage icon retrieval
}


/*!
 * wxEVT_WIZARD_PAGE_CHANGING event handler for ID_WELCOMEPAGE
 */

void CWelcomePage::OnPageChanging( wxWizardEvent& event )
{
    if (event.GetDirection() == false) return;

    unsigned long ulFlags = 0;

    if (m_ErrProjectPropertiesCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRPROJECTPROPERTIES;

    if (m_ErrProjectPropertiesURLCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRPROJECTPROPERTIESURL;

    if (m_ErrProjectCommCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRPROJECTCOMM;

    if (m_ErrGoogleCommCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRGOOGLECOMM;

    if (m_ErrYahooCommCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRYAHOOCOMM;

    if (m_ErrAccountAlreadyExistsCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRACCOUNTALREADYEXISTS;

    if (m_ErrAccountCreationDisabledCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRACCOUNTCREATIONDISABLED;

    if (m_ErrNetDetectionCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRNETDETECTION;

    ((CWizAttachProject*)GetParent())->SetDiagFlags( ulFlags );
}


/*!
 * CProjectInfoPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CProjectInfoPage, wxWizardPage )

/*!
 * CProjectInfoPage event table definition
 */

BEGIN_EVENT_TABLE( CProjectInfoPage, wxWizardPage )

////@begin CProjectInfoPage event table entries
////@end CProjectInfoPage event table entries

END_EVENT_TABLE()

/*!
 * CProjectInfoPage constructors
 */

CProjectInfoPage::CProjectInfoPage( )
{
}

CProjectInfoPage::CProjectInfoPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * WizardPage creator
 */

bool CProjectInfoPage::Create( wxWizard* parent )
{
////@begin CProjectInfoPage member initialisation
    m_ProjectUrlStaticCtrl = NULL;
    m_ProjectUrlCtrl = NULL;
////@end CProjectInfoPage member initialisation

////@begin CProjectInfoPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CProjectInfoPage creation
    return TRUE;
}

/*!
 * Control creation for WizardPage
 */

void CProjectInfoPage::CreateControls()
{    
////@begin CProjectInfoPage content construction
    CProjectInfoPage* itemWizardPage19 = this;

    wxBoxSizer* itemBoxSizer20 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage19->SetSizer(itemBoxSizer20);

    wxStaticText* itemStaticText21 = new wxStaticText;
    itemStaticText21->Create( itemWizardPage19, wxID_STATIC, _("Project Information"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText21->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer20->Add(itemStaticText21, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText22 = new wxStaticText;
    itemStaticText22->Create( itemWizardPage19, wxID_STATIC, _("Which project do you wish to attach to?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer20->Add(itemStaticText22, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer20->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText24 = new wxStaticText;
    itemStaticText24->Create( itemWizardPage19, wxID_STATIC, _("The project URL is generally the project's homepage.  It is in the form of\na web address and can be found in your browsers address bar."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer20->Add(itemStaticText24, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer25 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer25->AddGrowableCol(1);
    itemBoxSizer20->Add(itemFlexGridSizer25, 0, wxALIGN_LEFT|wxALL, 5);

    m_ProjectUrlStaticCtrl = new wxStaticText;
    m_ProjectUrlStaticCtrl->Create( itemWizardPage19, ID_PROJECTURLSTATICCTRL, _("Project URL:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer25->Add(m_ProjectUrlStaticCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProjectUrlCtrl = new wxTextCtrl;
    m_ProjectUrlCtrl->Create( itemWizardPage19, ID_PROJECTURLCTRL, _T(""), wxDefaultPosition, wxSize(250, -1), 0 );
    itemFlexGridSizer25->Add(m_ProjectUrlCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer20->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText29 = new wxStaticText;
    itemStaticText29->Create( itemWizardPage19, wxID_STATIC, _("For more information, and to see a list of some BOINC-based projects,\ngo to:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer20->Add(itemStaticText29, 0, wxALIGN_LEFT|wxALL, 5);

    wxHyperLink* itemHyperLink30 = new wxHyperLink;
    itemHyperLink30->Create( itemWizardPage19, ID_PROJECRINFOBOINCLINK, wxT("http://boinc.berkeley.edu/"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
    itemBoxSizer20->Add(itemHyperLink30, 0, wxALIGN_LEFT|wxALL, 5);

    // Set validators
    m_ProjectUrlCtrl->SetValidator( wxTextValidator(wxFILTER_NONE, & m_strProjectURL) );
////@end CProjectInfoPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CProjectInfoPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CProjectInfoPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_PROJECTPROPERTIESPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CProjectInfoPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CProjectInfoPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CProjectInfoPage bitmap retrieval
    return wxNullBitmap;
////@end CProjectInfoPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CProjectInfoPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CProjectInfoPage icon retrieval
    return wxNullIcon;
////@end CProjectInfoPage icon retrieval
}


/*!
 * CProjectPropertiesPage custom event definition
 */
DEFINE_EVENT_TYPE(wxEVT_PROJECTPROPERTIES_STATECHANGE)


/*!
 * CProjectPropertiesPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CProjectPropertiesPage, wxWizardPage )

/*!
 * CProjectPropertiesPage event table definition
 */

BEGIN_EVENT_TABLE( CProjectPropertiesPage, wxWizardPage )

    EVT_PROJECTPROPERTIES_STATECHANGE( CProjectPropertiesPage::OnStateChange )

////@begin CProjectPropertiesPage event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, CProjectPropertiesPage::OnPageChanged )

////@end CProjectPropertiesPage event table entries

END_EVENT_TABLE()

/*!
 * CProjectPropertiesPage constructors
 */

CProjectPropertiesPage::CProjectPropertiesPage( )
{
}

CProjectPropertiesPage::CProjectPropertiesPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * WizardPage creator
 */

bool CProjectPropertiesPage::Create( wxWizard* parent )
{
////@begin CProjectPropertiesPage member initialisation
    m_RetrProjectPropertiesImageCtrl = NULL;
    m_RetrProjectPropertiesCtrl = NULL;
    m_CommYahooImageCtrl = NULL;
    m_CommYahooCtrl = NULL;
    m_CommGoogleImageCtrl = NULL;
    m_CommGoogleCtrl = NULL;
    m_DetermineConnectionStatusImageCtrl = NULL;
    m_DetermineConnectionStatusCtrl = NULL;
    m_FinalProjectPropertiesStatusCtrl = NULL;
////@end CProjectPropertiesPage member initialisation
    m_bProjectPropertiesSucceeded = false;
    m_bProjectPropertiesURLFailure = false;
    m_bProjectAccountCreationDisabled = false;
    m_bCommunicateYahooSucceeded = false;
    m_bCommunicateGoogleSucceeded = false;
    m_bDeterminingConnectionStatusSucceeded = false;
    m_iCurrentState = PROJPROP_INIT;

////@begin CProjectPropertiesPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CProjectPropertiesPage creation
    return TRUE;
}

/*!
 * Control creation for WizardPage
 */

void CProjectPropertiesPage::CreateControls()
{    
////@begin CProjectPropertiesPage content construction
    CProjectPropertiesPage* itemWizardPage31 = this;

    wxBoxSizer* itemBoxSizer32 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage31->SetSizer(itemBoxSizer32);

    wxStaticText* itemStaticText33 = new wxStaticText;
    itemStaticText33->Create( itemWizardPage31, wxID_STATIC, _("Project Properties"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText33->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer32->Add(itemStaticText33, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText34 = new wxStaticText;
    itemStaticText34->Create( itemWizardPage31, wxID_STATIC, _("This wizard is now attempting to retrieve the projectís account\ncreation policies."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer32->Add(itemStaticText34, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer32->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText36 = new wxStaticText;
    itemStaticText36->Create( itemWizardPage31, wxID_STATIC, _("If this wizard cannot reach the project server, it'll attempt to contact a\ncouple known good websites in an effort to help diagnose the problem."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer32->Add(itemStaticText36, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer37 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer32->Add(itemFlexGridSizer37, 0, wxALIGN_LEFT|wxALL, 5);

    wxBitmap m_RetrProjectPropertiesImageCtrlBitmap(itemWizardPage31->GetBitmapResource(wxT("res/wizquestion.xpm")));
    m_RetrProjectPropertiesImageCtrl = new wxStaticBitmap;
    m_RetrProjectPropertiesImageCtrl->Create( itemWizardPage31, ID_RETRPROJECTPROPERTIESIMAGECTRL, m_RetrProjectPropertiesImageCtrlBitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemFlexGridSizer37->Add(m_RetrProjectPropertiesImageCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_RetrProjectPropertiesCtrl = new wxStaticText;
    m_RetrProjectPropertiesCtrl->Create( itemWizardPage31, ID_RETRPROJECTPROPERTIESCTRL, _("Retrieving project account creation policy"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer37->Add(m_RetrProjectPropertiesCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmap m_CommYahooImageCtrlBitmap(itemWizardPage31->GetBitmapResource(wxT("res/wizsuccess.xpm")));
    m_CommYahooImageCtrl = new wxStaticBitmap;
    m_CommYahooImageCtrl->Create( itemWizardPage31, ID_COMMYAHOOIMAGECTRL, m_CommYahooImageCtrlBitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemFlexGridSizer37->Add(m_CommYahooImageCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_CommYahooCtrl = new wxStaticText;
    m_CommYahooCtrl->Create( itemWizardPage31, ID_COMMYAHOOCTRL, _("Communicating with Yahoo"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer37->Add(m_CommYahooCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmap m_CommGoogleImageCtrlBitmap(itemWizardPage31->GetBitmapResource(wxT("res/wizfailure.xpm")));
    m_CommGoogleImageCtrl = new wxStaticBitmap;
    m_CommGoogleImageCtrl->Create( itemWizardPage31, ID_COMMGOOGLEIMAGECTRL, m_CommGoogleImageCtrlBitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemFlexGridSizer37->Add(m_CommGoogleImageCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_CommGoogleCtrl = new wxStaticText;
    m_CommGoogleCtrl->Create( itemWizardPage31, ID_COMMGOOGLECTRL, _("Communicating with Google"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer37->Add(m_CommGoogleCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmap m_DetermineConnectionStatusImageCtrlBitmap(itemWizardPage31->GetBitmapResource(wxT("res/wizquestion.xpm")));
    m_DetermineConnectionStatusImageCtrl = new wxStaticBitmap;
    m_DetermineConnectionStatusImageCtrl->Create( itemWizardPage31, ID_DETERMINECONNECTIONSTATUSIMAGECTRL, m_DetermineConnectionStatusImageCtrlBitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemFlexGridSizer37->Add(m_DetermineConnectionStatusImageCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DetermineConnectionStatusCtrl = new wxStaticText;
    m_DetermineConnectionStatusCtrl->Create( itemWizardPage31, ID_DETERMINECONNECTIONSTATUSCTRL, _("Determining connection status"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer37->Add(m_DetermineConnectionStatusCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_FinalProjectPropertiesStatusCtrl = new wxStaticText;
    m_FinalProjectPropertiesStatusCtrl->Create( itemWizardPage31, ID_FINALPROJECTPROPERTIESTATUSCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer32->Add(m_FinalProjectPropertiesStatusCtrl, 0, wxALIGN_LEFT|wxALL, 5);

////@end CProjectPropertiesPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CProjectPropertiesPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CProjectPropertiesPage::GetNext() const
{
    if (GetProjectPropertiesSucceeded() && GetProjectPropertiesURLFailure()) {
        // Legacy Authentication Scheme
        return PAGE_TRANSITION_NEXT(ID_ACCOUNTKEYPAGE);
    } else if (GetProjectPropertiesSucceeded() && GetProjectAccountCreationDisabled()) {
        // Account Creation Disabled
        return PAGE_TRANSITION_NEXT(ID_ERRACCOUNTCREATIONDISABLEDPAGE);
    } else if (GetProjectPropertiesSucceeded()) {
        // We were successful in retrieving the project properties
        return PAGE_TRANSITION_NEXT(ID_ACCOUNTINFOPAGE);
    } else if ((!GetCommunicateYahooSucceeded() && !GetCommunicateGoogleSucceeded()) && GetDeterminingConnectionStatusSucceeded()) {
        // Possible proxy problem
        return PAGE_TRANSITION_NEXT(ID_ERRPROXYINFOPAGE);
    } else if ((!GetCommunicateYahooSucceeded() && !GetCommunicateGoogleSucceeded()) && !GetDeterminingConnectionStatusSucceeded()) {
        // No Internet Connection
        return PAGE_TRANSITION_NEXT(ID_ERRNOINTERNETCONNECTIONPAGE);
    } else {
        // The project much be down for maintenance
        return PAGE_TRANSITION_NEXT(ID_ERRPROJECTUNAVAILABLEPAGE);
    }
    return NULL;
}

/*!
 * Should we show tooltips?
 */

bool CProjectPropertiesPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CProjectPropertiesPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    if (name == wxT("res/wizquestion.xpm"))
    {
        wxBitmap bitmap(wizquestion_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizsuccess.xpm"))
    {
        wxBitmap bitmap(wizsuccess_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizfailure.xpm"))
    {
        wxBitmap bitmap(wizfailure_xpm);
        return bitmap;
    }
    return wxNullBitmap;
}

/*!
 * Get icon resources
 */

wxIcon CProjectPropertiesPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CProjectPropertiesPage icon retrieval
    return wxNullIcon;
////@end CProjectPropertiesPage icon retrieval
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_PROJECTPROPERTIESPAGE
 */

void CProjectPropertiesPage::OnPageChanged( wxWizardEvent& event )
{
    if (event.GetDirection() == false) return;

    SetProjectPropertiesSucceeded(false);
    SetProjectPropertiesURLFailure(false);
    SetProjectAccountCreationDisabled(false);
    SetCommunicateYahooSucceeded(false);
    SetCommunicateGoogleSucceeded(false);
    SetDeterminingConnectionStatusSucceeded(false);
    SetNextState(PROJPROP_INIT);

    CProjectPropertiesPageEvent TransitionEvent(wxEVT_PROJECTPROPERTIES_STATECHANGE, this);
    AddPendingEvent(TransitionEvent);
}

/*!
 * wxEVT_PROJECTPROPERTIES_STATECHANGE event handler for ID_PROJECTPROPERTIESPAGE
 */

void CProjectPropertiesPage::OnStateChange( CProjectPropertiesPageEvent& event )
{
    bool bPostNewEvent = true;

    wxFont fontOriginal = m_FinalProjectPropertiesStatusCtrl->GetFont();
    wxFont fontBold = m_FinalProjectPropertiesStatusCtrl->GetFont();
    fontBold.SetWeight(wxBOLD);

    switch(GetCurrentState()) {
        case PROJPROP_INIT:
            // Set initial bitmaps to question marks since we don't yet know how
            //   things will turn out.
            m_RetrProjectPropertiesImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizquestion.xpm")));
            m_CommYahooImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizquestion.xpm")));
            m_CommGoogleImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizquestion.xpm")));
            m_DetermineConnectionStatusImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizquestion.xpm")));

            // Hide the additional diagnostics stuff until we really need it.
            m_CommYahooImageCtrl->Hide();
            m_CommYahooCtrl->Hide();
            m_CommGoogleImageCtrl->Hide();
            m_CommGoogleCtrl->Hide();
            m_DetermineConnectionStatusImageCtrl->Hide();
            m_DetermineConnectionStatusCtrl->Hide();

            // Clear out any text that might exist in the final status field
            m_FinalProjectPropertiesStatusCtrl->SetLabel(wxT(""));

            SetNextState(PROJPROP_RETRPROJECTPROPERTIES_BEGIN);
            break;
        case PROJPROP_RETRPROJECTPROPERTIES_BEGIN:
            // Highlight the current activity by making it bold
            m_RetrProjectPropertiesCtrl->SetFont(fontBold);

            SetNextState(PROJPROP_RETRPROJECTPROPERTIES_EXECUTE);
            break;
        case PROJPROP_RETRPROJECTPROPERTIES_EXECUTE:
            // Attempt to retrieve the projectís account creation policies
            wxSleep(2);

            // Replace with the function call that really does the work.
            if (!((CWizAttachProject*)GetParent())->IsDiagFlagsSet(WIZDEBUG_ERRPROJECTPROPERTIES)) {
                m_RetrProjectPropertiesImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizsuccess.xpm")));
                SetProjectPropertiesSucceeded(true);

                if (((CWizAttachProject*)GetParent())->IsDiagFlagsSet(WIZDEBUG_ERRPROJECTPROPERTIESURL)) {
                    SetProjectPropertiesURLFailure(true);
                } else {
                    SetProjectPropertiesURLFailure(false);
                }

                if (((CWizAttachProject*)GetParent())->IsDiagFlagsSet(WIZDEBUG_ERRACCOUNTCREATIONDISABLED)) {
                    SetProjectAccountCreationDisabled(true);
                } else {
                    SetProjectAccountCreationDisabled(false);
                }

                // Say something useful to go with this condition
                m_FinalProjectPropertiesStatusCtrl->SetLabel(_("To continue, click Next."));

                SetNextState(PROJPROP_END);
            } else {
                m_RetrProjectPropertiesImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizfailure.xpm")));

                // Show the additional diagnostics stuff.
                m_CommYahooImageCtrl->Show();
                m_CommYahooCtrl->Show();
                m_CommGoogleImageCtrl->Show();
                m_CommGoogleCtrl->Show();
                m_DetermineConnectionStatusImageCtrl->Show();
                m_DetermineConnectionStatusCtrl->Show();

                SetProjectPropertiesSucceeded(false);
                SetNextState(PROJPROP_COMMUNICATEYAHOO_BEGIN);
            }
            m_RetrProjectPropertiesCtrl->SetFont(fontOriginal);
            break;
        case PROJPROP_COMMUNICATEYAHOO_BEGIN:
            // Highlight the current activity by making it bold
            m_CommYahooCtrl->SetFont(fontBold);
            SetNextState(PROJPROP_COMMUNICATEYAHOO_EXECUTE);
            break;
        case PROJPROP_COMMUNICATEYAHOO_EXECUTE:
            // Attempt to successfully download the Yahoo homepage
            wxSleep(2);

            // Replace with the function call that really does the work.
            if (!((CWizAttachProject*)GetParent())->IsDiagFlagsSet(WIZDEBUG_ERRYAHOOCOMM)) {
                m_CommYahooImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizsuccess.xpm")));
                SetCommunicateYahooSucceeded(true);
            } else {
                m_CommYahooImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizfailure.xpm")));
                SetCommunicateYahooSucceeded(false);
            }
            SetNextState(PROJPROP_COMMUNICATEGOOGLE_BEGIN);
            m_CommYahooCtrl->SetFont(fontOriginal);
            break;
        case PROJPROP_COMMUNICATEGOOGLE_BEGIN:
            // Highlight the current activity by making it bold
            m_CommGoogleCtrl->SetFont(fontBold);
            SetNextState(PROJPROP_COMMUNICATEGOOGLE_EXECUTE);
            break;
        case PROJPROP_COMMUNICATEGOOGLE_EXECUTE:
            // Attempt to successfully download the Google homepage
            wxSleep(2);

            // Replace with the function call that really does the work.
            if (!((CWizAttachProject*)GetParent())->IsDiagFlagsSet(WIZDEBUG_ERRGOOGLECOMM)) {
                m_CommGoogleImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizsuccess.xpm")));
                SetCommunicateGoogleSucceeded(true);
            } else {
                m_CommGoogleImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizfailure.xpm")));
                SetCommunicateGoogleSucceeded(false);
            }
            m_CommGoogleCtrl->SetFont(fontOriginal);
            SetNextState(PROJPROP_DETERMINENETWORKSTATUS_BEGIN);
            break;
        case PROJPROP_DETERMINENETWORKSTATUS_BEGIN:
            // Highlight the current activity by making it bold
            m_DetermineConnectionStatusCtrl->SetFont(fontBold);
            SetNextState(PROJPROP_DETERMINENETWORKSTATUS_EXECUTE);
            break;
        case PROJPROP_DETERMINENETWORKSTATUS_EXECUTE:
            // Attempt to determine if we are even connected to a network
            wxSleep(2);

            // Replace with the function call that really does the work.
            if (!((CWizAttachProject*)GetParent())->IsDiagFlagsSet(WIZDEBUG_ERRNETDETECTION)) {
                m_DetermineConnectionStatusImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizsuccess.xpm")));
                SetDeterminingConnectionStatusSucceeded(true);
            } else {
                m_DetermineConnectionStatusImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizfailure.xpm")));
                SetDeterminingConnectionStatusSucceeded(false);
            }
            m_DetermineConnectionStatusCtrl->SetFont(fontOriginal);

            // Say something useful to go with this condition
            m_FinalProjectPropertiesStatusCtrl->SetLabel(_("One or more problems detected, click Next to troubleshoot the\nproblem."));

            SetNextState(PROJPROP_END);
            break;
        default:
            bPostNewEvent = false;
            break;
    }

    Update();

    if (bPostNewEvent) {
        CProjectPropertiesPageEvent TransitionEvent(wxEVT_PROJECTPROPERTIES_STATECHANGE, this);
        AddPendingEvent(TransitionEvent);
    }
}


/*!
 * CAccountKeyPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CAccountKeyPage, wxWizardPage )

/*!
 * CAccountKeyPage event table definition
 */

BEGIN_EVENT_TABLE( CAccountKeyPage, wxWizardPage )

////@begin CAccountKeyPage event table entries
////@end CAccountKeyPage event table entries

END_EVENT_TABLE()

/*!
 * CAccountKeyPage constructors
 */

CAccountKeyPage::CAccountKeyPage( )
{
}

CAccountKeyPage::CAccountKeyPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CAuthenticatorPage creator
 */

bool CAccountKeyPage::Create( wxWizard* parent )
{
////@begin CAccountKeyPage member initialisation
    m_AccountKeyStaticCtrl = NULL;
    m_AccountKeyCtrl = NULL;
////@end CAccountKeyPage member initialisation

////@begin CAccountKeyPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CAccountKeyPage creation
    return TRUE;
}

/*!
 * Control creation for CAuthenticatorPage
 */

void CAccountKeyPage::CreateControls()
{    
////@begin CAccountKeyPage content construction
    CAccountKeyPage* itemWizardPage47 = this;

    wxBoxSizer* itemBoxSizer48 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage47->SetSizer(itemBoxSizer48);

    wxStaticText* itemStaticText49 = new wxStaticText;
    itemStaticText49->Create( itemWizardPage47, wxID_STATIC, _("Account Key"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText49->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer48->Add(itemStaticText49, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText50 = new wxStaticText;
    itemStaticText50->Create( itemWizardPage47, wxID_STATIC, _("Do you have your project account key handy?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer48->Add(itemStaticText50, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer48->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText52 = new wxStaticText;
    itemStaticText52->Create( itemWizardPage47, wxID_STATIC, _("This project does not support account management through this\nwizard and uses BOINC's account key authentication."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer48->Add(itemStaticText52, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText53 = new wxStaticText;
    itemStaticText53->Create( itemWizardPage47, wxID_STATIC, _("An account key is a string of 32 random letters and numbers that\nare assigned during the account creation process and is treated\nlike a username and password on other web based systems.  It will\nhave been sent to you via email as part of the confirmation email\nmessage. Please copy and paste it into the text box below."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer48->Add(itemStaticText53, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText54 = new wxStaticText;
    itemStaticText54->Create( itemWizardPage47, wxID_STATIC, _("An account key typically looks like:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer48->Add(itemStaticText54, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText55 = new wxStaticText;
    itemStaticText55->Create( itemWizardPage47, wxID_STATIC, _("82412313ac88e9a3638f66ea82186948"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText55->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, FALSE, _T("Courier New")));
    itemBoxSizer48->Add(itemStaticText55, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxFlexGridSizer* itemFlexGridSizer56 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer56->AddGrowableCol(1);
    itemBoxSizer48->Add(itemFlexGridSizer56, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_AccountKeyStaticCtrl = new wxStaticText;
    m_AccountKeyStaticCtrl->Create( itemWizardPage47, ID_ACCOUNTKEYSTATICCTRL, _("Account key:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer56->Add(m_AccountKeyStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountKeyCtrl = new wxTextCtrl;
    m_AccountKeyCtrl->Create( itemWizardPage47, ID_ACCOUNTKEYCTRL, _T(""), wxDefaultPosition, wxSize(225, -1), 0 );
    itemFlexGridSizer56->Add(m_AccountKeyCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Set validators
    m_AccountKeyCtrl->SetValidator( wxTextValidator(wxFILTER_ALPHANUMERIC, & m_strAccountKey) );
////@end CAccountKeyPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CAccountKeyPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CAccountKeyPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_COMPLETIONPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CAccountKeyPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CAccountKeyPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CAccountKeyPage bitmap retrieval
    return wxNullBitmap;
////@end CAccountKeyPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CAccountKeyPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CAccountKeyPage icon retrieval
    return wxNullIcon;
////@end CAccountKeyPage icon retrieval
}


/*!
 * CAccountInfoPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CAccountInfoPage, wxWizardPage )

/*!
 * CAccountInfoPage event table definition
 */

BEGIN_EVENT_TABLE( CAccountInfoPage, wxWizardPage )

////@begin CAccountInfoPage event table entries
    EVT_RADIOBUTTON( ID_ACCOUNTCREATECTRL, CAccountInfoPage::OnAccountCreateCtrlSelected )

    EVT_RADIOBUTTON( ID_ACCOUNTUSEEXISTINGCTRL, CAccountInfoPage::OnAccountUseExistingCtrlSelected )

////@end CAccountInfoPage event table entries

END_EVENT_TABLE()

/*!
 * CAccountInfoPage constructors
 */

CAccountInfoPage::CAccountInfoPage( )
{
}

CAccountInfoPage::CAccountInfoPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * AccountInfoPage creator
 */

bool CAccountInfoPage::Create( wxWizard* parent )
{
////@begin CAccountInfoPage member initialisation
    m_AccountCreateCtrl = NULL;
    m_AccountUseExistingCtrl = NULL;
    m_AccountEmailAddressStaticCtrl = NULL;
    m_AccountEmailAddressCtrl = NULL;
    m_AccountPasswordStaticCtrl = NULL;
    m_AccountPasswordCtrl = NULL;
    m_AccountConfirmPasswordStaticCtrl = NULL;
    m_AccountConfirmPasswordCtrl = NULL;
////@end CAccountInfoPage member initialisation

////@begin CAccountInfoPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CAccountInfoPage creation
    return TRUE;
}

/*!
 * Control creation for AccountInfoPage
 */

void CAccountInfoPage::CreateControls()
{    
////@begin CAccountInfoPage content construction
    CAccountInfoPage* itemWizardPage59 = this;

    wxBoxSizer* itemBoxSizer60 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage59->SetSizer(itemBoxSizer60);

    wxStaticText* itemStaticText61 = new wxStaticText;
    itemStaticText61->Create( itemWizardPage59, wxID_STATIC, _("Account Information"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText61->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer60->Add(itemStaticText61, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText62 = new wxStaticText;
    itemStaticText62->Create( itemWizardPage59, wxID_STATIC, _("Do you wish to use an existing account or create a new one?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer60->Add(itemStaticText62, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer60->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText64 = new wxStaticText;
    itemStaticText64->Create( itemWizardPage59, wxID_STATIC, _("If this is the first time you have attempted to attach to this project then\nyou should create a new account.  If you already have an account you\nshould use your existing email address and password to attach to the\nproject."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer60->Add(itemStaticText64, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer65 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer65->AddGrowableCol(1);
    itemBoxSizer60->Add(itemFlexGridSizer65, 0, wxGROW|wxALL, 5);

    m_AccountCreateCtrl = new wxRadioButton;
    m_AccountCreateCtrl->Create( itemWizardPage59, ID_ACCOUNTCREATECTRL, _("Create new account"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    m_AccountCreateCtrl->SetValue(FALSE);
    itemFlexGridSizer65->Add(m_AccountCreateCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountUseExistingCtrl = new wxRadioButton;
    m_AccountUseExistingCtrl->Create( itemWizardPage59, ID_ACCOUNTUSEEXISTINGCTRL, _("Use existing account"), wxDefaultPosition, wxDefaultSize, 0 );
    m_AccountUseExistingCtrl->SetValue(FALSE);
    itemFlexGridSizer65->Add(m_AccountUseExistingCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer68 = new wxFlexGridSizer(3, 2, 0, 0);
    itemFlexGridSizer68->AddGrowableCol(1);
    itemBoxSizer60->Add(itemFlexGridSizer68, 0, wxGROW|wxALL, 5);

    m_AccountEmailAddressStaticCtrl = new wxStaticText;
    m_AccountEmailAddressStaticCtrl->Create( itemWizardPage59, ID_ACCOUNTEMAILADDRESSSTATICCTRL, _("Email address:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer68->Add(m_AccountEmailAddressStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountEmailAddressCtrl = new wxTextCtrl;
    m_AccountEmailAddressCtrl->Create( itemWizardPage59, ID_ACCOUNTEMAILADDRESSCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer68->Add(m_AccountEmailAddressCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountPasswordStaticCtrl = new wxStaticText;
    m_AccountPasswordStaticCtrl->Create( itemWizardPage59, ID_ACCOUNTPASSWORDSTATICCTRL, _("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer68->Add(m_AccountPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountPasswordCtrl = new wxTextCtrl;
    m_AccountPasswordCtrl->Create( itemWizardPage59, ID_ACCOUNTPASSWORDCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer68->Add(m_AccountPasswordCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountConfirmPasswordStaticCtrl = new wxStaticText;
    m_AccountConfirmPasswordStaticCtrl->Create( itemWizardPage59, ID_ACCOUNTCONFIRMPASSWORDSTATICCTRL, _("Confirm password:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer68->Add(m_AccountConfirmPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountConfirmPasswordCtrl = new wxTextCtrl;
    m_AccountConfirmPasswordCtrl->Create( itemWizardPage59, ID_ACCOUNTCONFIRMPASSWORDCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer68->Add(m_AccountConfirmPasswordCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Set validators
    m_AccountEmailAddressCtrl->SetValidator( wxGenericValidator(& m_strAccountEmailAddress) );
    m_AccountPasswordCtrl->SetValidator( wxGenericValidator(& m_strAccountPassword) );
    m_AccountConfirmPasswordCtrl->SetValidator( wxGenericValidator(& m_strAccountConfirmPassword) );
////@end CAccountInfoPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CAccountInfoPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CAccountInfoPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_ACCOUNTCREATIONPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CAccountInfoPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CAccountInfoPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CAccountInfoPage bitmap retrieval
    return wxNullBitmap;
////@end CAccountInfoPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CAccountInfoPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CAccountInfoPage icon retrieval
    return wxNullIcon;
////@end CAccountInfoPage icon retrieval
}


/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_ACCOUNTUSEXISTINGBUTTON
 */

void CAccountInfoPage::OnAccountUseExistingCtrlSelected( wxCommandEvent& event )
{
    m_AccountConfirmPasswordStaticCtrl->Hide();
    m_AccountConfirmPasswordCtrl->Hide();
}


/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_ACCOUNTCREATEBUTTON
 */

void CAccountInfoPage::OnAccountCreateCtrlSelected( wxCommandEvent& event )
{
    m_AccountConfirmPasswordStaticCtrl->Show();
    m_AccountConfirmPasswordCtrl->Show();
}


/*!
 * CProjectPropertiesPage custom event definition
 */
DEFINE_EVENT_TYPE(wxEVT_ACCOUNTCREATION_STATECHANGE)


/*!
 * CAccountCreationPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CAccountCreationPage, wxWizardPage )

/*!
 * CAccountCreationPage event table definition
 */

BEGIN_EVENT_TABLE( CAccountCreationPage, wxWizardPage )

    EVT_ACCOUNTCREATION_STATECHANGE( CAccountCreationPage::OnStateChange )

////@begin CAccountCreationPage event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, CAccountCreationPage::OnPageChanged )

////@end CAccountCreationPage event table entries

END_EVENT_TABLE()

/*!
 * CAccountCreationPage constructors
 */

CAccountCreationPage::CAccountCreationPage( )
{
}

CAccountCreationPage::CAccountCreationPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CProjectPropertiesPage creator
 */

bool CAccountCreationPage::Create( wxWizard* parent )
{
////@begin CAccountCreationPage member initialisation
    m_ProjectCommunitcationsImageCtrl = NULL;
    m_ProjectCommunitcationsCtrl = NULL;
    m_FinalAccountCreationStatusCtrl = NULL;
////@end CAccountCreationPage member initialisation
    m_bProjectCommunitcationsSucceeded = false;
    m_bProjectUnavailable = false;
    m_bProjectAccountAlreadyExists = false;
    m_iCurrentState = ACCOUNTCREATION_INIT;

////@begin CAccountCreationPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CAccountCreationPage creation
    return TRUE;
}

/*!
 * Control creation for CProjectPropertiesPage
 */

void CAccountCreationPage::CreateControls()
{    
////@begin CAccountCreationPage content construction
    CAccountCreationPage* itemWizardPage75 = this;

    wxBoxSizer* itemBoxSizer76 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage75->SetSizer(itemBoxSizer76);

    wxStaticText* itemStaticText77 = new wxStaticText;
    itemStaticText77->Create( itemWizardPage75, wxID_STATIC, _("Account Creation"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText77->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer76->Add(itemStaticText77, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText78 = new wxStaticText;
    itemStaticText78->Create( itemWizardPage75, wxID_STATIC, _("This wizard is now attempting to create a new account or validate your\nexisting account."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer76->Add(itemStaticText78, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer76->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText80 = new wxStaticText;
    itemStaticText80->Create( itemWizardPage75, wxID_STATIC, _("If this wizard cannot reach the project server, it'll attempt to contact a\ncouple known good websites in an effort to help diagnose the problem."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer76->Add(itemStaticText80, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer81 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer76->Add(itemFlexGridSizer81, 0, wxALIGN_LEFT|wxALL, 5);

    wxBitmap m_ProjectCommunitcationsImageCtrlBitmap(itemWizardPage75->GetBitmapResource(wxT("res/wizquestion.xpm")));
    m_ProjectCommunitcationsImageCtrl = new wxStaticBitmap;
    m_ProjectCommunitcationsImageCtrl->Create( itemWizardPage75, ID_PROJECTCOMMUNICATIONSIMAGECTRL, m_ProjectCommunitcationsImageCtrlBitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemFlexGridSizer81->Add(m_ProjectCommunitcationsImageCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProjectCommunitcationsCtrl = new wxStaticText;
    m_ProjectCommunitcationsCtrl->Create( itemWizardPage75, ID_PROJECTCOMMUNICATIONSCTRL, _("Communicating with BOINC project"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer81->Add(m_ProjectCommunitcationsCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_FinalAccountCreationStatusCtrl = new wxStaticText;
    m_FinalAccountCreationStatusCtrl->Create( itemWizardPage75, ID_FINALACCOUNTCREATIONSTATUSCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer76->Add(m_FinalAccountCreationStatusCtrl, 0, wxALIGN_LEFT|wxALL, 5);

////@end CAccountCreationPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CAccountCreationPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CAccountCreationPage::GetNext() const
{
    if (GetProjectCommunitcationsSucceeded() && GetProjectAccountAlreadyExists()) {
        // The requested account already exists
        return PAGE_TRANSITION_NEXT(ID_ERRACCOUNTALREADYEXISTSPAGE);
    } else if (GetProjectCommunitcationsSucceeded()) {
        // We were successful in creating or retrieving an account
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONPAGE);
    } else {
        // The project much be down for maintenance
        return PAGE_TRANSITION_NEXT(ID_ERRPROJECTUNAVAILABLEPAGE);
    } 
    return NULL;
}

/*!
 * Should we show tooltips?
 */

bool CAccountCreationPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CAccountCreationPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    if (name == wxT("res/wizquestion.xpm"))
    {
        wxBitmap bitmap(wizquestion_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizsuccess.xpm"))
    {
        wxBitmap bitmap(wizsuccess_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizfailure.xpm"))
    {
        wxBitmap bitmap(wizfailure_xpm);
        return bitmap;
    }
    return wxNullBitmap;
}

/*!
 * Get icon resources
 */

wxIcon CAccountCreationPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CAccountCreationPage icon retrieval
    return wxNullIcon;
////@end CAccountCreationPage icon retrieval
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ACCOUNTCREATIONPAGE
 */

void CAccountCreationPage::OnPageChanged( wxWizardEvent& event )
{
    if (event.GetDirection() == false) return;

    SetProjectCommunitcationsSucceeded(false);
    SetProjectUnavailable(false);
    SetProjectAccountAlreadyExists(false);
    SetNextState(ACCOUNTCREATION_INIT);

    CAccountCreationPageEvent TransitionEvent(wxEVT_ACCOUNTCREATION_STATECHANGE, this);
    AddPendingEvent(TransitionEvent);
}

/*!
 * wxEVT_ACCOUNTCREATION_STATECHANGE event handler for ID_ACCOUNTCREATIONPAGE
 */

void CAccountCreationPage::OnStateChange( CAccountCreationPageEvent& event )
{
    bool bPostNewEvent = true;

    wxFont fontOriginal = m_FinalAccountCreationStatusCtrl->GetFont();
    wxFont fontBold = m_FinalAccountCreationStatusCtrl->GetFont();
    fontBold.SetWeight(wxBOLD);

    switch(GetCurrentState()) {
        case ACCOUNTCREATION_INIT:
            // Set initial bitmaps to question marks since we don't yet know how
            //   things will turn out.
            m_ProjectCommunitcationsImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizquestion.xpm")));

            // Clear out any text that might exist in the final status field
            m_FinalAccountCreationStatusCtrl->SetLabel(wxT(""));

            SetNextState(ACCOUNTCREATION_PROJECTCOMM_BEGIN);
            break;
        case ACCOUNTCREATION_PROJECTCOMM_BEGIN:
            // Highlight the current activity by making it bold
            m_ProjectCommunitcationsCtrl->SetFont(fontBold);

            SetNextState(ACCOUNTCREATION_PROJECTCOMM_EXECUTE);
            break;
        case ACCOUNTCREATION_PROJECTCOMM_EXECUTE:
            // Attempt to retrieve the projectís account creation policies
            wxSleep(2);

            if (!((CWizAttachProject*)GetParent())->IsDiagFlagsSet(WIZDEBUG_ERRPROJECTCOMM)) {
                m_ProjectCommunitcationsImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizsuccess.xpm")));
                SetProjectCommunitcationsSucceeded(true);

                if (((CWizAttachProject*)GetParent())->IsDiagFlagsSet(WIZDEBUG_ERRACCOUNTALREADYEXISTS)) {
                    SetProjectAccountAlreadyExists(true);
                } else {
                    SetProjectAccountAlreadyExists(false);
                }

                // Say something useful to go with this condition
                m_FinalAccountCreationStatusCtrl->SetLabel(_("To continue, click Next."));
            } else {
                m_ProjectCommunitcationsImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizfailure.xpm")));
                SetProjectCommunitcationsSucceeded(false);

                // Say something useful to go with this condition
                m_FinalAccountCreationStatusCtrl->SetLabel(_("One or more problems detected, click Next to troubleshoot the\nproblem."));
            }
            m_ProjectCommunitcationsCtrl->SetFont(fontOriginal);

            SetNextState(ACCOUNTCREATION_END);
            break;
        default:
            bPostNewEvent = false;
            break;
    }

    Update();

    if (bPostNewEvent) {
        CAccountCreationPageEvent TransitionEvent(wxEVT_ACCOUNTCREATION_STATECHANGE, this);
        AddPendingEvent(TransitionEvent);
    }
}


/*!
 * CCompletionPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CCompletionPage, wxWizardPage )

/*!
 * CCompletionPage event table definition
 */

BEGIN_EVENT_TABLE( CCompletionPage, wxWizardPage )

////@begin CCompletionPage event table entries
////@end CCompletionPage event table entries

END_EVENT_TABLE()

/*!
 * CCompletionPage constructors
 */

CCompletionPage::CCompletionPage( )
{
}

CCompletionPage::CCompletionPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CAccountResultPage creator
 */

bool CCompletionPage::Create( wxWizard* parent )
{
////@begin CCompletionPage member initialisation
////@end CCompletionPage member initialisation

////@begin CCompletionPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CCompletionPage creation
    return TRUE;
}

/*!
 * Control creation for CAccountResultPage
 */

void CCompletionPage::CreateControls()
{    
////@begin CCompletionPage content construction
    CCompletionPage* itemWizardPage85 = this;

    wxBoxSizer* itemBoxSizer86 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage85->SetSizer(itemBoxSizer86);

    wxStaticText* itemStaticText87 = new wxStaticText;
    itemStaticText87->Create( itemWizardPage85, wxID_STATIC, _("Wizard Completion"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText87->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer86->Add(itemStaticText87, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText88 = new wxStaticText;
    itemStaticText88->Create( itemWizardPage85, wxID_STATIC, _("Congratulations"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer86->Add(itemStaticText88, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer86->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

////@end CCompletionPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CCompletionPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CCompletionPage::GetNext() const
{
    return NULL;
}

/*!
 * Should we show tooltips?
 */

bool CCompletionPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CCompletionPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CCompletionPage bitmap retrieval
    return wxNullBitmap;
////@end CCompletionPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CCompletionPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CCompletionPage icon retrieval
    return wxNullIcon;
////@end CCompletionPage icon retrieval
}


/*!
 * CErrProjectUnavailablePage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrProjectUnavailablePage, wxWizardPage )

/*!
 * CErrProjectUnavailablePage event table definition
 */

BEGIN_EVENT_TABLE( CErrProjectUnavailablePage, wxWizardPage )

////@begin CErrProjectUnavailablePage event table entries
////@end CErrProjectUnavailablePage event table entries

END_EVENT_TABLE()

/*!
 * CErrProjectUnavailablePage constructors
 */

CErrProjectUnavailablePage::CErrProjectUnavailablePage( )
{
}

CErrProjectUnavailablePage::CErrProjectUnavailablePage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrProjectUnavailable creator
 */

bool CErrProjectUnavailablePage::Create( wxWizard* parent )
{
////@begin CErrProjectUnavailablePage member initialisation
////@end CErrProjectUnavailablePage member initialisation

////@begin CErrProjectUnavailablePage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrProjectUnavailablePage creation
    return TRUE;
}

/*!
 * Control creation for CErrProjectUnavailable
 */

void CErrProjectUnavailablePage::CreateControls()
{    
////@begin CErrProjectUnavailablePage content construction
    CErrProjectUnavailablePage* itemWizardPage90 = this;

    wxBoxSizer* itemBoxSizer91 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage90->SetSizer(itemBoxSizer91);

    wxStaticText* itemStaticText92 = new wxStaticText;
    itemStaticText92->Create( itemWizardPage90, wxID_STATIC, _("Project Temporarily Unavailable"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText92->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer91->Add(itemStaticText92, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText93 = new wxStaticText;
    itemStaticText93->Create( itemWizardPage90, wxID_STATIC, _("The project may be down for maintenance."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer91->Add(itemStaticText93, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer91->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

////@end CErrProjectUnavailablePage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrProjectUnavailablePage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrProjectUnavailablePage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_COMPLETIONPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CErrProjectUnavailablePage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrProjectUnavailablePage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrProjectUnavailablePage bitmap retrieval
    return wxNullBitmap;
////@end CErrProjectUnavailablePage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrProjectUnavailablePage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrProjectUnavailablePage icon retrieval
    return wxNullIcon;
////@end CErrProjectUnavailablePage icon retrieval
}


/*!
 * CErrNoInternetConnectionPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrNoInternetConnectionPage, wxWizardPage )

/*!
 * CErrNoInternetConnectionPage event table definition
 */

BEGIN_EVENT_TABLE( CErrNoInternetConnectionPage, wxWizardPage )

////@begin CErrNoInternetConnectionPage event table entries
////@end CErrNoInternetConnectionPage event table entries

END_EVENT_TABLE()

/*!
 * CErrNoInternetConnectionPage constructors
 */

CErrNoInternetConnectionPage::CErrNoInternetConnectionPage( )
{
}

CErrNoInternetConnectionPage::CErrNoInternetConnectionPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrNoInternetConnection creator
 */

bool CErrNoInternetConnectionPage::Create( wxWizard* parent )
{
////@begin CErrNoInternetConnectionPage member initialisation
////@end CErrNoInternetConnectionPage member initialisation

////@begin CErrNoInternetConnectionPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrNoInternetConnectionPage creation
    return TRUE;
}

/*!
 * Control creation for CErrNoInternetConnection
 */

void CErrNoInternetConnectionPage::CreateControls()
{    
////@begin CErrNoInternetConnectionPage content construction
    CErrNoInternetConnectionPage* itemWizardPage95 = this;

    wxBoxSizer* itemBoxSizer96 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage95->SetSizer(itemBoxSizer96);

    wxStaticText* itemStaticText97 = new wxStaticText;
    itemStaticText97->Create( itemWizardPage95, wxID_STATIC, _("No Internet Connection Detected"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText97->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer96->Add(itemStaticText97, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText98 = new wxStaticText;
    itemStaticText98->Create( itemWizardPage95, wxID_STATIC, _("Could not communicate with the desired project or any of the known\ncomputers on the Internet."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer96->Add(itemStaticText98, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer96->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

////@end CErrNoInternetConnectionPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrNoInternetConnectionPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrNoInternetConnectionPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_PROJECTINFOPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CErrNoInternetConnectionPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrNoInternetConnectionPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrNoInternetConnectionPage bitmap retrieval
    return wxNullBitmap;
////@end CErrNoInternetConnectionPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrNoInternetConnectionPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrNoInternetConnectionPage icon retrieval
    return wxNullIcon;
////@end CErrNoInternetConnectionPage icon retrieval
}

/*!
 * CErrAccountAlreadyExistsPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrAccountAlreadyExistsPage, wxWizardPage )

/*!
 * CErrAccountAlreadyExistsPage event table definition
 */

BEGIN_EVENT_TABLE( CErrAccountAlreadyExistsPage, wxWizardPage )

////@begin CErrAccountAlreadyExistsPage event table entries
////@end CErrAccountAlreadyExistsPage event table entries

END_EVENT_TABLE()

/*!
 * CErrAccountAlreadyExistsPage constructors
 */

CErrAccountAlreadyExistsPage::CErrAccountAlreadyExistsPage( )
{
}

CErrAccountAlreadyExistsPage::CErrAccountAlreadyExistsPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrAccountAlreadyExists creator
 */

bool CErrAccountAlreadyExistsPage::Create( wxWizard* parent )
{
////@begin CErrAccountAlreadyExistsPage member initialisation
////@end CErrAccountAlreadyExistsPage member initialisation

////@begin CErrAccountAlreadyExistsPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrAccountAlreadyExistsPage creation
    return TRUE;
}

/*!
 * Control creation for CErrAccountAlreadyExists
 */

void CErrAccountAlreadyExistsPage::CreateControls()
{    
////@begin CErrAccountAlreadyExistsPage content construction
    CErrAccountAlreadyExistsPage* itemWizardPage100 = this;

    wxBoxSizer* itemBoxSizer101 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage100->SetSizer(itemBoxSizer101);

    wxStaticText* itemStaticText102 = new wxStaticText;
    itemStaticText102->Create( itemWizardPage100, wxID_STATIC, _("Account Already Exists"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText102->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer101->Add(itemStaticText102, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText103 = new wxStaticText;
    itemStaticText103->Create( itemWizardPage100, wxID_STATIC, _("The requested account is already in use."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer101->Add(itemStaticText103, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer101->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

////@end CErrAccountAlreadyExistsPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrAccountAlreadyExistsPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrAccountAlreadyExistsPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_ACCOUNTINFOPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CErrAccountAlreadyExistsPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrAccountAlreadyExistsPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrAccountAlreadyExistsPage bitmap retrieval
    return wxNullBitmap;
////@end CErrAccountAlreadyExistsPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrAccountAlreadyExistsPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrAccountAlreadyExistsPage icon retrieval
    return wxNullIcon;
////@end CErrAccountAlreadyExistsPage icon retrieval
}


/*!
 * CErrAccountCreationDisabledPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrAccountCreationDisabledPage, wxWizardPage )

/*!
 * CErrAccountCreationDisabledPage event table definition
 */

BEGIN_EVENT_TABLE( CErrAccountCreationDisabledPage, wxWizardPage )

////@begin CErrAccountCreationDisabledPage event table entries
////@end CErrAccountCreationDisabledPage event table entries

END_EVENT_TABLE()

/*!
 * CErrAccountCreationDisabledPage constructors
 */

CErrAccountCreationDisabledPage::CErrAccountCreationDisabledPage( )
{
}

CErrAccountCreationDisabledPage::CErrAccountCreationDisabledPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrAccountCreationDisabledPage creator
 */

bool CErrAccountCreationDisabledPage::Create( wxWizard* parent )
{
////@begin CErrAccountCreationDisabledPage member initialisation
////@end CErrAccountCreationDisabledPage member initialisation

////@begin CErrAccountCreationDisabledPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrAccountCreationDisabledPage creation
    return TRUE;
}

/*!
 * Control creation for CErrAccountCreationDisabledPage
 */

void CErrAccountCreationDisabledPage::CreateControls()
{    
////@begin CErrAccountCreationDisabledPage content construction
    CErrAccountCreationDisabledPage* itemWizardPage105 = this;

    wxBoxSizer* itemBoxSizer106 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage105->SetSizer(itemBoxSizer106);

    wxStaticText* itemStaticText107 = new wxStaticText;
    itemStaticText107->Create( itemWizardPage105, wxID_STATIC, _("Account Creation Disabled"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText107->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer106->Add(itemStaticText107, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText108 = new wxStaticText;
    itemStaticText108->Create( itemWizardPage105, wxID_STATIC, _("This project is not accepting any new clients at this time."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer106->Add(itemStaticText108, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer106->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

////@end CErrAccountCreationDisabledPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrAccountCreationDisabledPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrAccountCreationDisabledPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_COMPLETIONPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CErrAccountCreationDisabledPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrAccountCreationDisabledPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrAccountCreationDisabledPage bitmap retrieval
    return wxNullBitmap;
////@end CErrAccountCreationDisabledPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrAccountCreationDisabledPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrAccountCreationDisabledPage icon retrieval
    return wxNullIcon;
////@end CErrAccountCreationDisabledPage icon retrieval
}


/*!
 * CErrProxyInfoPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrProxyInfoPage, wxWizardPage )

/*!
 * CErrProxyInfoPage event table definition
 */

BEGIN_EVENT_TABLE( CErrProxyInfoPage, wxWizardPage )

////@begin CErrProxyInfoPage event table entries
////@end CErrProxyInfoPage event table entries

END_EVENT_TABLE()

/*!
 * CErrProxyInfoPage constructors
 */

CErrProxyInfoPage::CErrProxyInfoPage( )
{
}

CErrProxyInfoPage::CErrProxyInfoPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrProxyInfoPage creator
 */

bool CErrProxyInfoPage::Create( wxWizard* parent )
{
////@begin CErrProxyInfoPage member initialisation
////@end CErrProxyInfoPage member initialisation

////@begin CErrProxyInfoPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrProxyInfoPage creation
    return TRUE;
}

/*!
 * Control creation for CErrProxyInfoPage
 */

void CErrProxyInfoPage::CreateControls()
{    
////@begin CErrProxyInfoPage content construction
    CErrProxyInfoPage* itemWizardPage110 = this;

    wxBoxSizer* itemBoxSizer111 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage110->SetSizer(itemBoxSizer111);

    wxStaticText* itemStaticText112 = new wxStaticText;
    itemStaticText112->Create( itemWizardPage110, wxID_STATIC, _("Proxy Configuration"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText112->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer111->Add(itemStaticText112, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText113 = new wxStaticText;
    itemStaticText113->Create( itemWizardPage110, wxID_STATIC, _("Do you need to configure a proxy server?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer111->Add(itemStaticText113, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer111->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

////@end CErrProxyInfoPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrProxyInfoPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrProxyInfoPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_ERRPROXYHTTPPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CErrProxyInfoPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrProxyInfoPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrProxyInfoPage bitmap retrieval
    return wxNullBitmap;
////@end CErrProxyInfoPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrProxyInfoPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrProxyInfoPage icon retrieval
    return wxNullIcon;
////@end CErrProxyInfoPage icon retrieval
}

/*!
 * CErrProxyHTTPPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrProxyHTTPPage, wxWizardPage )

/*!
 * CErrProxyHTTPPage event table definition
 */

BEGIN_EVENT_TABLE( CErrProxyHTTPPage, wxWizardPage )

////@begin CErrProxyHTTPPage event table entries
    EVT_BUTTON( ID_HTTPAUTODETECT, CErrProxyHTTPPage::OnAutodetectClick )

////@end CErrProxyHTTPPage event table entries

END_EVENT_TABLE()

/*!
 * CErrProxyHTTPPage constructors
 */

CErrProxyHTTPPage::CErrProxyHTTPPage( )
{
}

CErrProxyHTTPPage::CErrProxyHTTPPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrProxyHTTPPage creator
 */

bool CErrProxyHTTPPage::Create( wxWizard* parent )
{
////@begin CErrProxyHTTPPage member initialisation
    m_ProxyHTTPServerStaticCtrl = NULL;
    m_ProxyHTTPServerCtrl = NULL;
    m_ProxyHTTPPortStaticCtrl = NULL;
    m_ProxyHTTPPortCtrl = NULL;
    m_ProxyHTTPUsernameStaticCtrl = NULL;
    m_ProxyHTTPUsernameCtrl = NULL;
    m_ProxyHTTPPasswordStaticCtrl = NULL;
    m_ProxyHTTPPasswordCtrl = NULL;
////@end CErrProxyHTTPPage member initialisation

////@begin CErrProxyHTTPPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrProxyHTTPPage creation
    return TRUE;
}

/*!
 * Control creation for CErrProxyHTTPPage
 */

void CErrProxyHTTPPage::CreateControls()
{    
////@begin CErrProxyHTTPPage content construction
    CErrProxyHTTPPage* itemWizardPage115 = this;

    wxBoxSizer* itemBoxSizer116 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage115->SetSizer(itemBoxSizer116);

    wxStaticText* itemStaticText117 = new wxStaticText;
    itemStaticText117->Create( itemWizardPage115, wxID_STATIC, _("Proxy Configuration - HTTP Proxy"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText117->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer116->Add(itemStaticText117, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText118 = new wxStaticText;
    itemStaticText118->Create( itemWizardPage115, wxID_STATIC, _("Do you need to configure a proxy server?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer116->Add(itemStaticText118, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer116->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer116->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxButton* itemButton121 = new wxButton;
    itemButton121->Create( itemWizardPage115, ID_HTTPAUTODETECT, _("Autodetect"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer116->Add(itemButton121, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer122 = new wxFlexGridSizer(3, 2, 0, 0);
    itemFlexGridSizer122->AddGrowableCol(1);
    itemBoxSizer116->Add(itemFlexGridSizer122, 0, wxGROW|wxALL, 5);

    m_ProxyHTTPServerStaticCtrl = new wxStaticText;
    m_ProxyHTTPServerStaticCtrl->Create( itemWizardPage115, ID_PROXYHTTPSERVERSTATICCTRL, _("Server:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer122->Add(m_ProxyHTTPServerStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer124 = new wxFlexGridSizer(1, 3, 0, 0);
    itemFlexGridSizer124->AddGrowableCol(0);
    itemFlexGridSizer122->Add(itemFlexGridSizer124, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ProxyHTTPServerCtrl = new wxTextCtrl;
    m_ProxyHTTPServerCtrl->Create( itemWizardPage115, ID_PROXYHTTPSERVERCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer124->Add(m_ProxyHTTPServerCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPPortStaticCtrl = new wxStaticText;
    m_ProxyHTTPPortStaticCtrl->Create( itemWizardPage115, ID_PROXYHTTPPORTSTATICCTRL, _("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer124->Add(m_ProxyHTTPPortStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPPortCtrl = new wxTextCtrl;
    m_ProxyHTTPPortCtrl->Create( itemWizardPage115, ID_PROXYHTTPPORTCTRL, _T(""), wxDefaultPosition, wxSize(50, -1), 0 );
    itemFlexGridSizer124->Add(m_ProxyHTTPPortCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPUsernameStaticCtrl = new wxStaticText;
    m_ProxyHTTPUsernameStaticCtrl->Create( itemWizardPage115, ID_PROXYHTTPUSERNAMESTATICCTRL, _("User Name:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer122->Add(m_ProxyHTTPUsernameStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPUsernameCtrl = new wxTextCtrl;
    m_ProxyHTTPUsernameCtrl->Create( itemWizardPage115, ID_PROXYHTTPUSERNAMECTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer122->Add(m_ProxyHTTPUsernameCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPPasswordStaticCtrl = new wxStaticText;
    m_ProxyHTTPPasswordStaticCtrl->Create( itemWizardPage115, ID_PROXYHTTPPASSWORDSTATICCTRL, _("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer122->Add(m_ProxyHTTPPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPPasswordCtrl = new wxTextCtrl;
    m_ProxyHTTPPasswordCtrl->Create( itemWizardPage115, ID_PROXYHTTPPASSWORDCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer122->Add(m_ProxyHTTPPasswordCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Set validators
    m_ProxyHTTPServerCtrl->SetValidator( wxTextValidator(wxFILTER_NONE, & m_strProxyHTTPServer) );
    m_ProxyHTTPPortCtrl->SetValidator( wxTextValidator(wxFILTER_NUMERIC, & m_strProxyHTTPPort) );
    m_ProxyHTTPUsernameCtrl->SetValidator( wxTextValidator(wxFILTER_NONE, & m_strProxyHTTPUsername) );
    m_ProxyHTTPPasswordCtrl->SetValidator( wxTextValidator(wxFILTER_NONE, & m_strProxyHTTPPassword) );
////@end CErrProxyHTTPPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrProxyHTTPPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrProxyHTTPPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_ERRPROXYSOCKSPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CErrProxyHTTPPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrProxyHTTPPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrProxyHTTPPage bitmap retrieval
    return wxNullBitmap;
////@end CErrProxyHTTPPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrProxyHTTPPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrProxyHTTPPage icon retrieval
    return wxNullIcon;
////@end CErrProxyHTTPPage icon retrieval
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_HTTPAUTODETECT
 */

void CErrProxyHTTPPage::OnAutodetectClick( wxCommandEvent& event )
{
    event.Skip();
}


/*!
 * CErrProxySOCKSPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrProxySOCKSPage, wxWizardPage )

/*!
 * CErrProxySOCKSPage event table definition
 */

BEGIN_EVENT_TABLE( CErrProxySOCKSPage, wxWizardPage )

////@begin CErrProxySOCKSPage event table entries
    EVT_BUTTON( ID_SOCKSAUTODETECT, CErrProxySOCKSPage::OnAutodetectClick )

////@end CErrProxySOCKSPage event table entries

END_EVENT_TABLE()

/*!
 * CErrProxySOCKSPage constructors
 */

CErrProxySOCKSPage::CErrProxySOCKSPage( )
{
}

CErrProxySOCKSPage::CErrProxySOCKSPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrProxyInfoPage creator
 */

bool CErrProxySOCKSPage::Create( wxWizard* parent )
{
////@begin CErrProxySOCKSPage member initialisation
    m_ProxySOCKSServerStaticCtrl = NULL;
    m_ProxySOCKSServerCtrl = NULL;
    m_ProxySOCKSPortStaticCtrl = NULL;
    m_ProxySOCKSPortCtrl = NULL;
    m_ProxySOCKSUsernameStaticCtrl = NULL;
    m_ProxySOCKSUsernameCtrl = NULL;
    m_ProxySOCKSPasswordStaticCtrl = NULL;
    m_ProxySOCKSPasswordCtrl = NULL;
////@end CErrProxySOCKSPage member initialisation

////@begin CErrProxySOCKSPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrProxySOCKSPage creation
    return TRUE;
}

/*!
 * Control creation for CErrProxyInfoPage
 */

void CErrProxySOCKSPage::CreateControls()
{    
////@begin CErrProxySOCKSPage content construction
    CErrProxySOCKSPage* itemWizardPage132 = this;

    wxBoxSizer* itemBoxSizer133 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage132->SetSizer(itemBoxSizer133);

    wxStaticText* itemStaticText134 = new wxStaticText;
    itemStaticText134->Create( itemWizardPage132, wxID_STATIC, _("Proxy Configuration - SOCKS Proxy"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText134->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer133->Add(itemStaticText134, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText135 = new wxStaticText;
    itemStaticText135->Create( itemWizardPage132, wxID_STATIC, _("Do you need to configure a proxy server?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer133->Add(itemStaticText135, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer133->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer133->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxButton* itemButton138 = new wxButton;
    itemButton138->Create( itemWizardPage132, ID_SOCKSAUTODETECT, _("Autodetect"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer133->Add(itemButton138, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer139 = new wxFlexGridSizer(3, 2, 0, 0);
    itemFlexGridSizer139->AddGrowableCol(1);
    itemBoxSizer133->Add(itemFlexGridSizer139, 0, wxGROW|wxALL, 5);

    m_ProxySOCKSServerStaticCtrl = new wxStaticText;
    m_ProxySOCKSServerStaticCtrl->Create( itemWizardPage132, ID_PROXYSOCKSSERVERSTATICCTRL, _("Server:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer139->Add(m_ProxySOCKSServerStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer141 = new wxFlexGridSizer(1, 3, 0, 0);
    itemFlexGridSizer141->AddGrowableCol(0);
    itemFlexGridSizer139->Add(itemFlexGridSizer141, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ProxySOCKSServerCtrl = new wxTextCtrl;
    m_ProxySOCKSServerCtrl->Create( itemWizardPage132, ID_PROXYSOCKSSERVERCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer141->Add(m_ProxySOCKSServerCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSPortStaticCtrl = new wxStaticText;
    m_ProxySOCKSPortStaticCtrl->Create( itemWizardPage132, ID_PROXYSOCKSPORTSTATICCTRL, _("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer141->Add(m_ProxySOCKSPortStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSPortCtrl = new wxTextCtrl;
    m_ProxySOCKSPortCtrl->Create( itemWizardPage132, ID_PROXYSOCKSPORTCTRL, _T(""), wxDefaultPosition, wxSize(50, -1), 0 );
    itemFlexGridSizer141->Add(m_ProxySOCKSPortCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSUsernameStaticCtrl = new wxStaticText;
    m_ProxySOCKSUsernameStaticCtrl->Create( itemWizardPage132, ID_PROXYSOCKSUSERNAMESTATICCTRL, _("User Name:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer139->Add(m_ProxySOCKSUsernameStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSUsernameCtrl = new wxTextCtrl;
    m_ProxySOCKSUsernameCtrl->Create( itemWizardPage132, ID_PROXYSOCKSUSERNAMECTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer139->Add(m_ProxySOCKSUsernameCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSPasswordStaticCtrl = new wxStaticText;
    m_ProxySOCKSPasswordStaticCtrl->Create( itemWizardPage132, ID_PROXYSOCKSPASSWORDSTATICCTRL, _("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer139->Add(m_ProxySOCKSPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSPasswordCtrl = new wxTextCtrl;
    m_ProxySOCKSPasswordCtrl->Create( itemWizardPage132, ID_PROXYSOCKSPASSWORDCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer139->Add(m_ProxySOCKSPasswordCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Set validators
    m_ProxySOCKSServerCtrl->SetValidator( wxTextValidator(wxFILTER_NONE, & m_strProxySOCKSServer) );
    m_ProxySOCKSPortCtrl->SetValidator( wxTextValidator(wxFILTER_NUMERIC, & m_strProxySOCKSPort) );
    m_ProxySOCKSUsernameCtrl->SetValidator( wxTextValidator(wxFILTER_NONE, & m_strProxySOCKSUsername) );
    m_ProxySOCKSPasswordCtrl->SetValidator( wxTextValidator(wxFILTER_NONE, & m_strProxySOCKSPassword) );
////@end CErrProxySOCKSPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrProxySOCKSPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrProxySOCKSPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_ERRPROXYCOMPLETIONPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CErrProxySOCKSPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrProxySOCKSPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrProxySOCKSPage bitmap retrieval
    return wxNullBitmap;
////@end CErrProxySOCKSPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrProxySOCKSPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrProxySOCKSPage icon retrieval
    return wxNullIcon;
////@end CErrProxySOCKSPage icon retrieval
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SOCKSAUTODETECT
 */

void CErrProxySOCKSPage::OnAutodetectClick( wxCommandEvent& event )
{
    event.Skip();
}


/*!
 * CErrProxyComplationPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrProxyComplationPage, wxWizardPage )

/*!
 * CErrProxyComplationPage event table definition
 */

BEGIN_EVENT_TABLE( CErrProxyComplationPage, wxWizardPage )

////@begin CErrProxyComplationPage event table entries
////@end CErrProxyComplationPage event table entries

END_EVENT_TABLE()

/*!
 * CErrProxyComplationPage constructors
 */

CErrProxyComplationPage::CErrProxyComplationPage( )
{
}

CErrProxyComplationPage::CErrProxyComplationPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrProxyComplationPage creator
 */

bool CErrProxyComplationPage::Create( wxWizard* parent )
{
////@begin CErrProxyComplationPage member initialisation
////@end CErrProxyComplationPage member initialisation

////@begin CErrProxyComplationPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrProxyComplationPage creation
    return TRUE;
}

/*!
 * Control creation for CErrProxyComplationPage
 */

void CErrProxyComplationPage::CreateControls()
{    
////@begin CErrProxyComplationPage content construction
    CErrProxyComplationPage* itemWizardPage149 = this;

    wxBoxSizer* itemBoxSizer150 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage149->SetSizer(itemBoxSizer150);

    wxStaticText* itemStaticText151 = new wxStaticText;
    itemStaticText151->Create( itemWizardPage149, wxID_STATIC, _("Proxy Configuration Completion"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText151->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer150->Add(itemStaticText151, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText152 = new wxStaticText;
    itemStaticText152->Create( itemWizardPage149, wxID_STATIC, _("Do you need to configure a proxy server?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer150->Add(itemStaticText152, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer150->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

////@end CErrProxyComplationPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrProxyComplationPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrProxyComplationPage::GetNext() const
{
    return PAGE_TRANSITION_NEXT(ID_PROJECTPROPERTIESPAGE);
}

/*!
 * Should we show tooltips?
 */

bool CErrProxyComplationPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrProxyComplationPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrProxyComplationPage bitmap retrieval
    return wxNullBitmap;
////@end CErrProxyComplationPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrProxyComplationPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrProxyComplationPage icon retrieval
    return wxNullIcon;
////@end CErrProxyComplationPage icon retrieval
}

