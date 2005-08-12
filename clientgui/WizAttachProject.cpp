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
#include "error_numbers.h"
#include "network.h"

////@begin includes
////@end includes

#include "WizAttachProject.h"

////@begin XPM images
#include "res/attachprojectwizard.xpm"
#include "res/wizprogress1.xpm"
#include "res/wizprogress2.xpm"
#include "res/wizprogress3.xpm"
#include "res/wizprogress4.xpm"
#include "res/wizfailure.xpm"
#include "res/wizsuccess.xpm"
////@end XPM images


/*!
 * CWizAttachProject global helper macros
 */
#define PAGE_TRANSITION_NEXT(id) \
    ((CWizAttachProject*)GetParent())->PushPageTransition((wxWizardPage*)this, id)

#define PAGE_TRANSITION_BACK \
    ((CWizAttachProject*)GetParent())->PopPageTransition()

#define CHECK_DEBUG_FLAG(id) \
    ((CWizAttachProject*)GetParent())->IsDiagFlagsSet(id)


/*!
 * CWizAttachProject type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CWizAttachProject, wxWizard )

/*!
 * CWizAttachProject event table definition
 */

BEGIN_EVENT_TABLE( CWizAttachProject, wxWizard )

    EVT_BUTTON(wxID_BACKWARD, CWizAttachProject::OnWizardBack)
    EVT_BUTTON(wxID_FORWARD, CWizAttachProject::OnWizardNext)

////@begin CWizAttachProject event table entries
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
    m_CompletionErrorPage = NULL;
    m_ErrProjectNotDetectedPage = NULL;
    m_ErrProjectUnavailablePage = NULL;
    m_ErrNoInternetConnectionPage = NULL;
    m_ErrAccountAlreadyExistsPage = NULL;
    m_ErrAccountCreationDisabledPage = NULL;
    m_ErrProxyInfoPage = NULL;
    m_ErrProxyHTTPPage = NULL;
    m_ErrProxySOCKSPage = NULL;
    m_ErrProxyCompletionPage = NULL;
    m_ErrRefCountPage = NULL;
////@end CWizAttachProject member initialisation

    // Button pointer cache
    m_pbtnBack = NULL;
    m_pbtnNext = NULL;

    // Wizard support
    m_ulDiagFlags = 0;
    
    // Cancel Checking
    m_bCancelInProgress = false;

    // Global wizard status
    project_config.clear();
    old_proxy_info.clear();
    new_proxy_info.clear();
    account_in.clear();
    account_out.clear();

////@begin CWizAttachProject creation
    wxBitmap wizardBitmap(GetBitmapResource(wxT("res/attachprojectwizard.xpm")));
    wxWizard::Create( parent, id, _("Attach to Project"), wizardBitmap, pos );

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
    m_CompletionErrorPage = new CCompletionErrorPage;
    m_CompletionErrorPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_CompletionErrorPage);
    m_ErrProjectNotDetectedPage = new CErrProjectNotDetectedPage;
    m_ErrProjectNotDetectedPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrProjectNotDetectedPage);
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
    m_ErrRefCountPage = new CErrRefCountPage;
    m_ErrRefCountPage->Create( itemWizard1 );

    itemWizard1->FitToPage(m_ErrRefCountPage);
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
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_CompletionErrorPage = id: '%d', location: '%p'"), ID_COMPLETIONERRORPAGE, m_CompletionErrorPage);
    wxLogTrace(wxT("Function Status"), wxT("CWizAttachProject::CreateControls -     m_ErrProjectNotDetectedPage = id: '%d', location: '%p'"), ID_ERRPROJECTNOTDETECTEDPAGE, m_ErrProjectNotDetectedPage);
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

void CWizAttachProject::OnWizardBack( wxCommandEvent& event ) {
    if (!GetBackButton()) SetBackButton((wxButton*)event.GetEventObject());
    event.Skip();
}

void CWizAttachProject::OnWizardNext( wxCommandEvent& event ) {
    if (!GetNextButton()) SetNextButton((wxButton*)event.GetEventObject());
    event.Skip();
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
    bool bNoNextPageDetected = false;

    bNoNextPageDetected |= (page == m_CompletionPage);
    bNoNextPageDetected |= (page == m_CompletionErrorPage);
    bNoNextPageDetected |= (page == m_ErrProjectNotDetectedPage);
    bNoNextPageDetected |= (page == m_ErrProjectUnavailablePage);
    bNoNextPageDetected |= (page == m_ErrNoInternetConnectionPage);
    bNoNextPageDetected |= (page == m_ErrAccountAlreadyExistsPage);
    bNoNextPageDetected |= (page == m_ErrAccountCreationDisabledPage);

    if (bNoNextPageDetected)
        return false;
    return true;
}

/*!
 * Determine if the wizard page has a previous page
 */

bool CWizAttachProject::HasPrevPage( wxWizardPage* page )
{
    if ((page == m_WelcomePage) || (page == m_CompletionErrorPage))
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

wxWizardPage* CWizAttachProject::PopPageTransition() {
    wxWizardPage* pPage = NULL;
    if (GetCurrentPage()) {
        if (m_PageTransition.size() > 0) {
            pPage = m_PageTransition.top();
            m_PageTransition.pop();
            if ((pPage == m_ProjectPropertiesPage) || (pPage == m_AccountCreationPage)) {
                // We want to go back to the page before we attempted to communicate
                //   with any server.
                pPage = m_PageTransition.top();
                m_PageTransition.pop();
            }
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

        if (ID_COMPLETIONERRORPAGE == ulPageID)
            pPage = m_CompletionErrorPage;

        if (ID_ERRPROJECTNOTDETECTEDPAGE == ulPageID)
            pPage = m_ErrProjectNotDetectedPage;

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

void CWizAttachProject::ProcessCancelEvent( wxWizardEvent& event ) {
    int iRetVal = ::wxMessageBox(
        _("Do you really want to cancel?"), 
        _("Question"),
        wxICON_QUESTION | wxYES_NO,
        this
    );

    // Page specific rules - Disable the validator(s)
    if (wxYES == iRetVal) {
        if (GetCurrentPage() == m_ProjectInfoPage) {
            m_ProjectInfoPage->m_ProjectUrlCtrl->SetValidator(wxDefaultValidator);
        } else if (GetCurrentPage() == m_AccountKeyPage) {
            m_AccountKeyPage->m_AccountKeyCtrl->SetValidator(wxDefaultValidator);
        } else if (GetCurrentPage() == m_AccountInfoPage) {
            m_AccountInfoPage->m_AccountEmailAddressCtrl->SetValidator(wxDefaultValidator);
            m_AccountInfoPage->m_AccountPasswordCtrl->SetValidator(wxDefaultValidator);
            m_AccountInfoPage->m_AccountConfirmPasswordCtrl->SetValidator(wxDefaultValidator);
        } else if (GetCurrentPage() == m_ErrProxyHTTPPage) {
            m_ErrProxyHTTPPage->m_ProxyHTTPServerCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyHTTPPage->m_ProxyHTTPPortCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyHTTPPage->m_ProxyHTTPUsernameCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyHTTPPage->m_ProxyHTTPPasswordCtrl->SetValidator(wxDefaultValidator);
        } else if (GetCurrentPage() == m_ErrProxySOCKSPage) {
            m_ErrProxySOCKSPage->m_ProxySOCKSServerCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxySOCKSPage->m_ProxySOCKSPortCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxySOCKSPage->m_ProxySOCKSUsernameCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxySOCKSPage->m_ProxySOCKSPasswordCtrl->SetValidator(wxDefaultValidator);
        }
    }

    // Generic rules
    if (GetCurrentPage() != m_WelcomePage) {
        event.Veto();
        if (wxYES == iRetVal) {
            m_bCancelInProgress = true;
            SimulateNextButton();
        }
    } else {
        if (wxYES != iRetVal) {
            event.Veto();
        }
    }
}

void CWizAttachProject::SimulateNextButton() {
    if (!GetNextButton()) return;
    wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, GetNextButton()->GetId());
    event.SetEventObject(GetNextButton());
    AddPendingEvent(event);
}

void CWizAttachProject::SimulateBackButton() {
    if (!GetBackButton()) return;
    wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, GetBackButton()->GetId());
    event.SetEventObject(GetNextButton());
    AddPendingEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CWelcomePage::OnPageChanged )
    EVT_WIZARD_PAGE_CHANGING( -1, CWelcomePage::OnPageChanging )
    EVT_WIZARD_CANCEL( -1, CWelcomePage::OnCancel )

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
#if defined(__WXDEBUG__)
    m_ErrProjectPropertiesCtrl = NULL;
#endif
#if defined(__WXDEBUG__)
    m_ErrProjectCommCtrl = NULL;
#endif
#if defined(__WXDEBUG__)
    m_ErrProjectPropertiesURLCtrl = NULL;
#endif
#if defined(__WXDEBUG__)
    m_ErrAccountCreationDisabledCtrl = NULL;
#endif
#if defined(__WXDEBUG__)
    m_ErrClientAccountCreationDisabledCtrl = NULL;
#endif
#if defined(__WXDEBUG__)
    m_ErrAccountAlreadyExistsCtrl = NULL;
#endif
#if defined(__WXDEBUG__)
    m_ErrGoogleCommCtrl = NULL;
#endif
#if defined(__WXDEBUG__)
    m_ErrYahooCommCtrl = NULL;
#endif
#if defined(__WXDEBUG__)
    m_ErrNetDetectionCtrl = NULL;
#endif
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
    itemStaticText4->Create( itemWizardPage2, wxID_STATIC, _("Attach to Project"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText4->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText;
    itemStaticText5->Create( itemWizardPage2, wxID_STATIC, _("We will not guild you through the process of attaching to a\nproject."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText5, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer3->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

#if defined(__WXDEBUG__)
    wxStaticBox* itemStaticBoxSizer7Static = new wxStaticBox(itemWizardPage2, wxID_ANY, _("Debug Flags"));
    wxStaticBoxSizer* itemStaticBoxSizer7 = new wxStaticBoxSizer(itemStaticBoxSizer7Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer7, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer8 = new wxFlexGridSizer(-1, 2, 0, 0);
    itemFlexGridSizer8->AddGrowableCol(0);
    itemFlexGridSizer8->AddGrowableCol(1);
    itemStaticBoxSizer7->Add(itemFlexGridSizer8, 0, wxGROW|wxALL, 5);

    m_ErrProjectPropertiesCtrl = new wxCheckBox;
    m_ErrProjectPropertiesCtrl->Create( itemWizardPage2, ID_ERRPROJECTPROPERTIES, _("Project Properties Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrProjectPropertiesCtrl->SetValue(FALSE);
    itemFlexGridSizer8->Add(m_ErrProjectPropertiesCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrProjectCommCtrl = new wxCheckBox;
    m_ErrProjectCommCtrl->Create( itemWizardPage2, ID_ERRPROJECTCOMM, _("Project Comm Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrProjectCommCtrl->SetValue(FALSE);
    itemFlexGridSizer8->Add(m_ErrProjectCommCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrProjectPropertiesURLCtrl = new wxCheckBox;
    m_ErrProjectPropertiesURLCtrl->Create( itemWizardPage2, ID_ERRPROJECTPROPERTIESURL, _("Project Properties URL Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrProjectPropertiesURLCtrl->SetValue(FALSE);
    itemFlexGridSizer8->Add(m_ErrProjectPropertiesURLCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrAccountCreationDisabledCtrl = new wxCheckBox;
    m_ErrAccountCreationDisabledCtrl->Create( itemWizardPage2, ID_ERRACCOUNTCREATIONDISABLED, _("Account Creation Disabled"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrAccountCreationDisabledCtrl->SetValue(FALSE);
    itemFlexGridSizer8->Add(m_ErrAccountCreationDisabledCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrClientAccountCreationDisabledCtrl = new wxCheckBox;
    m_ErrClientAccountCreationDisabledCtrl->Create( itemWizardPage2, ID_ERRCLIENTACCOUNTCREATIONDISABLED, _("Client Account Creation Disabled"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrClientAccountCreationDisabledCtrl->SetValue(FALSE);
    itemFlexGridSizer8->Add(m_ErrClientAccountCreationDisabledCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrAccountAlreadyExistsCtrl = new wxCheckBox;
    m_ErrAccountAlreadyExistsCtrl->Create( itemWizardPage2, ID_ERRACCOUNTALREADYEXISTS, _("Account Already Exists"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrAccountAlreadyExistsCtrl->SetValue(FALSE);
    itemFlexGridSizer8->Add(m_ErrAccountAlreadyExistsCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrGoogleCommCtrl = new wxCheckBox;
    m_ErrGoogleCommCtrl->Create( itemWizardPage2, ID_ERRGOOGLECOMM, _("Google Comm Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrGoogleCommCtrl->SetValue(FALSE);
    itemFlexGridSizer8->Add(m_ErrGoogleCommCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    itemFlexGridSizer8->Add(5, 5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrYahooCommCtrl = new wxCheckBox;
    m_ErrYahooCommCtrl->Create( itemWizardPage2, ID_ERRYAHOOCOMM, _("Yahoo Comm Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrYahooCommCtrl->SetValue(FALSE);
    itemFlexGridSizer8->Add(m_ErrYahooCommCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    itemFlexGridSizer8->Add(5, 5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ErrNetDetectionCtrl = new wxCheckBox;
    m_ErrNetDetectionCtrl->Create( itemWizardPage2, ID_ERRNETDETECTION, _("Net Detection Failure"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    m_ErrNetDetectionCtrl->SetValue(FALSE);
    itemFlexGridSizer8->Add(m_ErrNetDetectionCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

#endif

    wxStaticText* itemStaticText20 = new wxStaticText;
    itemStaticText20->Create( itemWizardPage2, wxID_STATIC, _("To continue, click Next."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText20, 0, wxALIGN_LEFT|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else {
        return PAGE_TRANSITION_NEXT(ID_PROJECTINFOPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WELCOMEPAGE
 */

void CWelcomePage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGING event handler for ID_WELCOMEPAGE
 */

void CWelcomePage::OnPageChanging( wxWizardEvent& event )
{
    if (event.GetDirection() == false) return;

    unsigned long ulFlags = 0;

#if defined(__WXDEBUG__)
    if (m_ErrProjectPropertiesCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRPROJECTPROPERTIES;
#endif
#if defined(__WXDEBUG__)
    if (m_ErrProjectPropertiesURLCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRPROJECTPROPERTIESURL;
#endif
#if defined(__WXDEBUG__)
    if (m_ErrProjectCommCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRPROJECTCOMM;
#endif
#if defined(__WXDEBUG__)
    if (m_ErrGoogleCommCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRGOOGLECOMM;
#endif
#if defined(__WXDEBUG__)
    if (m_ErrYahooCommCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRYAHOOCOMM;
#endif
#if defined(__WXDEBUG__)
    if (m_ErrAccountAlreadyExistsCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRACCOUNTALREADYEXISTS;
#endif
#if defined(__WXDEBUG__)
    if (m_ErrAccountCreationDisabledCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRACCOUNTCREATIONDISABLED;
#endif
#if defined(__WXDEBUG__)
    if (m_ErrClientAccountCreationDisabledCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRCLIENTACCOUNTCREATIONDISABLED;
#endif
#if defined(__WXDEBUG__)
    if (m_ErrNetDetectionCtrl->GetValue()) 
        ulFlags |= WIZDEBUG_ERRNETDETECTION;
#endif

    ((CWizAttachProject*)GetParent())->SetDiagFlags( ulFlags );
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_WELCOMEPAGE
 */

void CWelcomePage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CProjectInfoPage::OnPageChanged )
    EVT_WIZARD_PAGE_CHANGING( -1, CProjectInfoPage::OnPageChanging )
    EVT_WIZARD_CANCEL( -1, CProjectInfoPage::OnCancel )

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
    CProjectInfoPage* itemWizardPage21 = this;

    wxBoxSizer* itemBoxSizer22 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage21->SetSizer(itemBoxSizer22);

    wxStaticText* itemStaticText23 = new wxStaticText;
    itemStaticText23->Create( itemWizardPage21, wxID_STATIC, _("Project URL"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText23->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer22->Add(itemStaticText23, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText24 = new wxStaticText;
    itemStaticText24->Create( itemWizardPage21, wxID_STATIC, _("Enter the project homepage URL."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer22->Add(itemStaticText24, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer22->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText26 = new wxStaticText;
    itemStaticText26->Create( itemWizardPage21, wxID_STATIC, _("You can copy and paste the URL from your browser�s address bar."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer22->Add(itemStaticText26, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer22->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer28 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer28->AddGrowableCol(1);
    itemBoxSizer22->Add(itemFlexGridSizer28, 0, wxALIGN_LEFT|wxALL, 5);

    m_ProjectUrlStaticCtrl = new wxStaticText;
    m_ProjectUrlStaticCtrl->Create( itemWizardPage21, ID_PROJECTURLSTATICCTRL, _("Project URL:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer28->Add(m_ProjectUrlStaticCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProjectUrlCtrl = new wxTextCtrl;
    m_ProjectUrlCtrl->Create( itemWizardPage21, ID_PROJECTURLCTRL, _T(""), wxDefaultPosition, wxSize(250, -1), 0 );
    itemFlexGridSizer28->Add(m_ProjectUrlCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer22->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText32 = new wxStaticText;
    itemStaticText32->Create( itemWizardPage21, wxID_STATIC, _("For a list of BOINC-based projects go to:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer22->Add(itemStaticText32, 0, wxALIGN_LEFT|wxALL, 5);

    wxHyperLink* itemHyperLink33 = new wxHyperLink;
    itemHyperLink33->Create( itemWizardPage21, ID_PROJECRINFOBOINCLINK, wxT("http://boinc.berkeley.edu/"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
    itemBoxSizer22->Add(itemHyperLink33, 0, wxALIGN_LEFT|wxALL, 5);

    // Set validators
    m_ProjectUrlCtrl->SetValidator( CValidateURL( & m_strProjectURL) );
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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else {
        return PAGE_TRANSITION_NEXT(ID_PROJECTPROPERTIESPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_PROJECTINFOPAGE
 */

void CProjectInfoPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGING event handler for ID_PROJECTINFOPAGE
 */

void CProjectInfoPage::OnPageChanging( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_PROJECTINFOPAGE
 */

void CProjectInfoPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_CANCEL( -1, CProjectPropertiesPage::OnCancel )

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
    m_ProjectPropertiesGaugeCtrl = NULL;
////@end CProjectPropertiesPage member initialisation
    m_bProjectPropertiesSucceeded = false;
    m_bProjectPropertiesURLFailure = false;
    m_bProjectAccountCreationDisabled = false;
    m_bProjectClientAccountCreationDisabled = false;
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
    CProjectPropertiesPage* itemWizardPage34 = this;

    wxBoxSizer* itemBoxSizer35 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage34->SetSizer(itemBoxSizer35);

    wxStaticText* itemStaticText36 = new wxStaticText;
    itemStaticText36->Create( itemWizardPage34, wxID_STATIC, _("Communicating with Project"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText36->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer35->Add(itemStaticText36, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer35->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer38 = new wxFlexGridSizer(0, 1, 0, 0);
    itemFlexGridSizer38->AddGrowableCol(0);
    itemBoxSizer35->Add(itemFlexGridSizer38, 0, wxGROW|wxALL, 5);

    m_ProjectPropertiesGaugeCtrl = new wxGauge;
    m_ProjectPropertiesGaugeCtrl->Create( itemWizardPage34, ID_PROJECTPROPERTIESGAUGECTRL, 25, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_PROGRESSBAR );
    m_ProjectPropertiesGaugeCtrl->SetValue(1);
    itemFlexGridSizer38->Add(m_ProjectPropertiesGaugeCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else if (GetProjectPropertiesSucceeded() && GetProjectAccountCreationDisabled()) {
        // Account Creation Disabled
        return PAGE_TRANSITION_NEXT(ID_ERRACCOUNTCREATIONDISABLEDPAGE);
    } else if (GetProjectPropertiesSucceeded() && GetProjectClientAccountCreationDisabled()) {
        // Client Account Creation Disabled - Use Legacy Authentication Scheme
        return PAGE_TRANSITION_NEXT(ID_ACCOUNTKEYPAGE);
    } else if (GetProjectPropertiesSucceeded()) {
        // We were successful in retrieving the project properties
        return PAGE_TRANSITION_NEXT(ID_ACCOUNTINFOPAGE);
    } else if (!GetProjectPropertiesSucceeded() && GetProjectPropertiesURLFailure()) {
        // Not a BOINC based project
        return PAGE_TRANSITION_NEXT(ID_ERRPROJECTNOTDETECTEDPAGE);
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

void CProjectPropertiesPage::StartProgress(wxGauge* pGauge) {
    pGauge->SetValue(1);
}

void CProjectPropertiesPage::IncrementProgress(wxGauge* pGauge) {
    pGauge->SetValue(pGauge->GetValue() + 1);
    Update();
}

void CProjectPropertiesPage::FinishProgress(wxGauge* pGauge) {
    pGauge->SetValue(pGauge->GetRange());
    Update();
}

/*!
 * Get bitmap resources
 */

wxBitmap CProjectPropertiesPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    if (name == wxT("res/wizprogress1.xpm"))
    {
        wxBitmap bitmap(wizprogress1_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizprogress2.xpm"))
    {
        wxBitmap bitmap(wizprogress2_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizprogress3.xpm"))
    {
        wxBitmap bitmap(wizprogress3_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizprogress4.xpm"))
    {
        wxBitmap bitmap(wizprogress4_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizfailure.xpm"))
    {
        wxBitmap bitmap(wizfailure_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizsuccess.xpm"))
    {
        wxBitmap bitmap(wizsuccess_xpm);
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
    SetProjectClientAccountCreationDisabled(false);
    SetCommunicateYahooSucceeded(false);
    SetCommunicateGoogleSucceeded(false);
    SetDeterminingConnectionStatusSucceeded(false);
    SetNextState(PROJPROP_INIT);

    CProjectPropertiesPageEvent TransitionEvent(wxEVT_PROJECTPROPERTIES_STATECHANGE, this);
    AddPendingEvent(TransitionEvent);
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_PROJECTPROPERTIESPAGE
 */

void CProjectPropertiesPage::OnCancel( wxWizardEvent& event ) {
}

/*!
 * wxEVT_PROJECTPROPERTIES_STATECHANGE event handler for ID_PROJECTPROPERTIESPAGE
 */

void CProjectPropertiesPage::OnStateChange( CProjectPropertiesPageEvent& event )
{
    CMainDocument* pDoc      = wxGetApp().GetDocument();
    PROJECT_CONFIG* pc       = &((CWizAttachProject*)GetParent())->project_config;
    bool bPostNewEvent = true;
    int iReturnValue = 0;
    bool bSuccessfulCondition = false;

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    switch(GetCurrentState()) {
        case PROJPROP_INIT:
            // Change the cursor to an hourglass
            ::wxBeginBusyCursor();

            StartProgress(m_ProjectPropertiesGaugeCtrl);

            SetNextState(PROJPROP_RETRPROJECTPROPERTIES_BEGIN);
            break;
        case PROJPROP_RETRPROJECTPROPERTIES_BEGIN:
            SetNextState(PROJPROP_RETRPROJECTPROPERTIES_EXECUTE);
            break;
        case PROJPROP_RETRPROJECTPROPERTIES_EXECUTE:
            // Attempt to retrieve the project�s account creation policies
            pDoc->rpc.get_project_config(
                ((CWizAttachProject*)GetParent())->m_ProjectInfoPage->GetProjectURL().c_str()
            );

            // Wait until we are done processing the request.
            iReturnValue = ERR_IN_PROGRESS;
            while (ERR_IN_PROGRESS == iReturnValue) {
                iReturnValue = pDoc->rpc.get_project_config_poll(*pc);
                IncrementProgress(m_ProjectPropertiesGaugeCtrl);
                wxSleep(1);
            }

            // We either successfully retrieved the project's account creation 
            //   policies or we were able to talk to the web server and found out
            //   they do not support account creation through the wizard.  In either
            //   case we should claim success and set the correct flags to show the
            //   correct 'next' page.
            bSuccessfulCondition = (BOINC_SUCCESS == iReturnValue) || (ERR_ACCT_CREATION_DISABLED == iReturnValue);
            if (bSuccessfulCondition && !CHECK_DEBUG_FLAG(WIZDEBUG_ERRPROJECTPROPERTIES)) {
                SetProjectPropertiesSucceeded(true);

                bSuccessfulCondition = pc->account_creation_disabled;
                if (bSuccessfulCondition || CHECK_DEBUG_FLAG(WIZDEBUG_ERRACCOUNTCREATIONDISABLED)) {
                    SetProjectAccountCreationDisabled(true);
                } else {
                    SetProjectAccountCreationDisabled(false);
                }

                bSuccessfulCondition = pc->client_account_creation_disabled;
                if (bSuccessfulCondition || CHECK_DEBUG_FLAG(WIZDEBUG_ERRCLIENTACCOUNTCREATIONDISABLED)) {
                    SetProjectClientAccountCreationDisabled(true);
                } else {
                    SetProjectClientAccountCreationDisabled(false);
                }


                SetNextState(PROJPROP_CLEANUP);
            } else {
                SetProjectPropertiesSucceeded(false);

                bSuccessfulCondition = (HTTP_STATUS_NOT_FOUND == iReturnValue) || (ERR_GETHOSTBYNAME == iReturnValue);
                if (bSuccessfulCondition || CHECK_DEBUG_FLAG(WIZDEBUG_ERRPROJECTPROPERTIESURL)) {
                    SetProjectPropertiesURLFailure(true);
                } else {
                    SetProjectPropertiesURLFailure(false);
                }

                SetNextState(PROJPROP_COMMUNICATEYAHOO_BEGIN);
            }
            break;
        case PROJPROP_COMMUNICATEYAHOO_BEGIN:
            SetNextState(PROJPROP_COMMUNICATEYAHOO_EXECUTE);
            break;
        case PROJPROP_COMMUNICATEYAHOO_EXECUTE:
            // Attempt to successfully download the Yahoo homepage
            pDoc->rpc.lookup_website(LOOKUP_YAHOO);

            // Wait until we are done processing the request.
            iReturnValue = ERR_IN_PROGRESS;
            while (ERR_IN_PROGRESS == iReturnValue) {
                iReturnValue = pDoc->rpc.lookup_website_poll();
                IncrementProgress(m_ProjectPropertiesGaugeCtrl);
                wxSleep(1);
            }

            if ((BOINC_SUCCESS == iReturnValue) && !CHECK_DEBUG_FLAG(WIZDEBUG_ERRYAHOOCOMM)) {
                SetCommunicateYahooSucceeded(true);
            } else {
                SetCommunicateYahooSucceeded(false);
            }
            SetNextState(PROJPROP_COMMUNICATEGOOGLE_BEGIN);
            break;
        case PROJPROP_COMMUNICATEGOOGLE_BEGIN:
            SetNextState(PROJPROP_COMMUNICATEGOOGLE_EXECUTE);
            break;
        case PROJPROP_COMMUNICATEGOOGLE_EXECUTE:
            // Attempt to successfully download the Google homepage
            pDoc->rpc.lookup_website(LOOKUP_GOOGLE);

            // Wait until we are done processing the request.
            iReturnValue = ERR_IN_PROGRESS;
            while (ERR_IN_PROGRESS == iReturnValue) {
                iReturnValue = pDoc->rpc.lookup_website_poll();
                IncrementProgress(m_ProjectPropertiesGaugeCtrl);
                wxSleep(1);
            }

            if ((BOINC_SUCCESS == iReturnValue) && !CHECK_DEBUG_FLAG(WIZDEBUG_ERRGOOGLECOMM)) {
                SetCommunicateGoogleSucceeded(true);
            } else {
                SetCommunicateGoogleSucceeded(false);
            }
            SetNextState(PROJPROP_DETERMINENETWORKSTATUS_BEGIN);
            break;
        case PROJPROP_DETERMINENETWORKSTATUS_BEGIN:
            SetNextState(PROJPROP_DETERMINENETWORKSTATUS_EXECUTE);
            break;
        case PROJPROP_DETERMINENETWORKSTATUS_EXECUTE:
            // Attempt to determine if we are even connected to a network
            bSuccessfulCondition = CONNECTED_STATE_CONNECTED == get_connected_state();
            if (bSuccessfulCondition && !CHECK_DEBUG_FLAG(WIZDEBUG_ERRNETDETECTION)) {
                SetDeterminingConnectionStatusSucceeded(true);
            } else {
                SetDeterminingConnectionStatusSucceeded(false);
            }

            SetNextState(PROJPROP_CLEANUP);
            break;
        case PROJPROP_CLEANUP:
            FinishProgress(m_ProjectPropertiesGaugeCtrl);
            SetNextState(PROJPROP_END);
            break;
        default:
            // Allow a glimps of what the result was before advancing to the next page.
            wxSleep(1);
            ((CWizAttachProject*)GetParent())->SimulateNextButton();

            // Change the cursor to a normal cursor
            ::wxEndBusyCursor();

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
    EVT_WIZARD_PAGE_CHANGED( -1, CAccountKeyPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CAccountKeyPage::OnCancel )

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
    CAccountKeyPage* itemWizardPage40 = this;

    wxBoxSizer* itemBoxSizer41 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage40->SetSizer(itemBoxSizer41);

    wxStaticText* itemStaticText42 = new wxStaticText;
    itemStaticText42->Create( itemWizardPage40, wxID_STATIC, _("Account Key"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText42->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer41->Add(itemStaticText42, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText43 = new wxStaticText;
    itemStaticText43->Create( itemWizardPage40, wxID_STATIC, _("Do you have your project account key handy?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer41->Add(itemStaticText43, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer41->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText45 = new wxStaticText;
    itemStaticText45->Create( itemWizardPage40, wxID_STATIC, _("This project uses BOINC's account key authentication instead of\na username and password."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer41->Add(itemStaticText45, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText46 = new wxStaticText;
    itemStaticText46->Create( itemWizardPage40, wxID_STATIC, _("During the account creation process on the project�s homepage, an\naccount is assigned an account key which is sent to you in email.\nAccount keys are strings of 32 random letters and numbers and\nare treated like a username and password on other web based\nsystems. Please copy and paste it into the text box below."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer41->Add(itemStaticText46, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText47 = new wxStaticText;
    itemStaticText47->Create( itemWizardPage40, wxID_STATIC, _("An account key typically looks like:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer41->Add(itemStaticText47, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText48 = new wxStaticText;
    itemStaticText48->Create( itemWizardPage40, wxID_STATIC, _("82412313ac88e9a3638f66ea82186948"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText48->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, FALSE, _T("Courier New")));
    itemBoxSizer41->Add(itemStaticText48, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    itemBoxSizer41->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer50 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer50->AddGrowableCol(1);
    itemBoxSizer41->Add(itemFlexGridSizer50, 0, wxGROW|wxALL, 5);

    m_AccountKeyStaticCtrl = new wxStaticText;
    m_AccountKeyStaticCtrl->Create( itemWizardPage40, ID_ACCOUNTKEYSTATICCTRL, _("Account key:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer50->Add(m_AccountKeyStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountKeyCtrl = new wxTextCtrl;
    m_AccountKeyCtrl->Create( itemWizardPage40, ID_ACCOUNTKEYCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer50->Add(m_AccountKeyCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Set validators
    m_AccountKeyCtrl->SetValidator( CValidateAccountKey( & m_strAccountKey) );
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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else {
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ACCOUNTKEYPAGE
 */

void CAccountKeyPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ACCOUNTKEYPAGE
 */

void CAccountKeyPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CAccountInfoPage::OnPageChanged )
    EVT_WIZARD_PAGE_CHANGING( -1, CAccountInfoPage::OnPageChanging )
    EVT_WIZARD_CANCEL( -1, CAccountInfoPage::OnCancel )

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
    m_AccountInfoDescriptionStaticCtrl = NULL;
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
    CAccountInfoPage* itemWizardPage53 = this;

    wxBoxSizer* itemBoxSizer54 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage53->SetSizer(itemBoxSizer54);

    wxStaticText* itemStaticText55 = new wxStaticText;
    itemStaticText55->Create( itemWizardPage53, wxID_STATIC, _("Account Information"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText55->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer54->Add(itemStaticText55, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText56 = new wxStaticText;
    itemStaticText56->Create( itemWizardPage53, wxID_STATIC, _("Do you wish to use an existing account or create a new one?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer54->Add(itemStaticText56, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer54->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    m_AccountInfoDescriptionStaticCtrl = new wxStaticText;
    m_AccountInfoDescriptionStaticCtrl->Create( itemWizardPage53, ID_ACCOUTINFODESCRIPTIONSTATICCTRL, _("If this is the first time you have attempted to attach to this project then\nyou should create a new account.  If you already have an account you\nshould use your existing email address and password to attach to the\nproject."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer54->Add(m_AccountInfoDescriptionStaticCtrl, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer59 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer59->AddGrowableCol(1);
    itemBoxSizer54->Add(itemFlexGridSizer59, 0, wxGROW|wxALL, 5);

    m_AccountCreateCtrl = new wxRadioButton;
    m_AccountCreateCtrl->Create( itemWizardPage53, ID_ACCOUNTCREATECTRL, _("Create new account"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    m_AccountCreateCtrl->SetValue(FALSE);
    itemFlexGridSizer59->Add(m_AccountCreateCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountUseExistingCtrl = new wxRadioButton;
    m_AccountUseExistingCtrl->Create( itemWizardPage53, ID_ACCOUNTUSEEXISTINGCTRL, _("Use existing account"), wxDefaultPosition, wxDefaultSize, 0 );
    m_AccountUseExistingCtrl->SetValue(FALSE);
    itemFlexGridSizer59->Add(m_AccountUseExistingCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer62 = new wxFlexGridSizer(3, 2, 0, 0);
    itemFlexGridSizer62->AddGrowableCol(1);
    itemBoxSizer54->Add(itemFlexGridSizer62, 0, wxGROW|wxALL, 5);

    m_AccountEmailAddressStaticCtrl = new wxStaticText;
    m_AccountEmailAddressStaticCtrl->Create( itemWizardPage53, ID_ACCOUNTEMAILADDRESSSTATICCTRL, _("Email address:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer62->Add(m_AccountEmailAddressStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountEmailAddressCtrl = new wxTextCtrl;
    m_AccountEmailAddressCtrl->Create( itemWizardPage53, ID_ACCOUNTEMAILADDRESSCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer62->Add(m_AccountEmailAddressCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountPasswordStaticCtrl = new wxStaticText;
    m_AccountPasswordStaticCtrl->Create( itemWizardPage53, ID_ACCOUNTPASSWORDSTATICCTRL, _("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer62->Add(m_AccountPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountPasswordCtrl = new wxTextCtrl;
    m_AccountPasswordCtrl->Create( itemWizardPage53, ID_ACCOUNTPASSWORDCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer62->Add(m_AccountPasswordCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountConfirmPasswordStaticCtrl = new wxStaticText;
    m_AccountConfirmPasswordStaticCtrl->Create( itemWizardPage53, ID_ACCOUNTCONFIRMPASSWORDSTATICCTRL, _("Confirm password:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer62->Add(m_AccountConfirmPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AccountConfirmPasswordCtrl = new wxTextCtrl;
    m_AccountConfirmPasswordCtrl->Create( itemWizardPage53, ID_ACCOUNTCONFIRMPASSWORDCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer62->Add(m_AccountConfirmPasswordCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else {
        return PAGE_TRANSITION_NEXT(ID_ACCOUNTCREATIONPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ACCOUNTINFOPAGE
 */

void CAccountInfoPage::OnPageChanged( wxWizardEvent& event ) 
{
    if (event.GetDirection() == false) return;

    if (((CWizAttachProject*)GetParent())->project_config.uses_username) {
        m_AccountEmailAddressStaticCtrl->SetLabel(
            _("Username:")
        );
        m_AccountInfoDescriptionStaticCtrl->SetLabel(
            _("If this is the first time you have attempted to attach to this project then\n"
              "you should create a new account.  If you already have an account you\n"
              "should use your existing username and password to attach to the\n"
              "project.")
        );
    } else {
        m_AccountEmailAddressStaticCtrl->SetLabel(
            _("Email address:")
        );
        m_AccountInfoDescriptionStaticCtrl->SetLabel(
            _("If this is the first time you have attempted to attach to this project then\n"
              "you should create a new account.  If you already have an account you\n"
              "should use your existing email address and password to attach to the\n"
              "project.")
        );
    }
    Fit();
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGING event handler for ID_ACCOUNTINFOPAGE
 */

void CAccountInfoPage::OnPageChanging( wxWizardEvent& event )
{
    if (event.GetDirection() == false) return;

    if (!((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        wxString strTitle = _("Attach to Project Wizard");
        wxString strMessage = wxT("");
        bool     bDisplayError = false;

        // Validate a new account against the account creation policies
        if (m_AccountCreateCtrl->GetValue()) {
            // Verify minimum password length
            unsigned int iMinLength = ((CWizAttachProject*)GetParent())->project_config.min_passwd_length;
            wxString strPassword = m_AccountPasswordCtrl->GetValue();

            if (strPassword.Length() < iMinLength) {
                strMessage.Printf(
                    _("The minimum password length for this project is %d. Please choose a different password."),
                    iMinLength
                );
                bDisplayError = true;
            }

            // Verify that the password and confirmation password math.
            if (m_AccountPasswordCtrl->GetValue() != m_AccountConfirmPasswordCtrl->GetValue()) {
                strMessage = _("The password and confirmation password do not match. Please type them again.");
                bDisplayError = true;
            }
        }

        if (bDisplayError) {
            ::wxMessageBox(
                strMessage,
                strTitle,
                wxICON_ERROR | wxOK,
                this
            );

            event.Veto();
        }
    }
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ACCOUNTINFOPAGE
 */

void CAccountInfoPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_CANCEL( -1, CAccountCreationPage::OnCancel )

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
    m_iProjectCommunitcationsProgressImage = 0;

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
    CAccountCreationPage* itemWizardPage69 = this;

    wxBoxSizer* itemBoxSizer70 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage69->SetSizer(itemBoxSizer70);

    wxStaticText* itemStaticText71 = new wxStaticText;
    itemStaticText71->Create( itemWizardPage69, wxID_STATIC, _("Communicating with Project"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText71->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer70->Add(itemStaticText71, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer70->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer73 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer70->Add(itemFlexGridSizer73, 0, wxALIGN_LEFT|wxALL, 5);

    wxBitmap m_ProjectCommunitcationsImageCtrlBitmap(itemWizardPage69->GetBitmapResource(wxT("res/wizprogress1.xpm")));
    m_ProjectCommunitcationsImageCtrl = new wxStaticBitmap;
    m_ProjectCommunitcationsImageCtrl->Create( itemWizardPage69, ID_PROJECTCOMMUNICATIONSIMAGECTRL, m_ProjectCommunitcationsImageCtrlBitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemFlexGridSizer73->Add(m_ProjectCommunitcationsImageCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProjectCommunitcationsCtrl = new wxStaticText;
    m_ProjectCommunitcationsCtrl->Create( itemWizardPage69, ID_PROJECTCOMMUNICATIONSCTRL, _("Communicating with the project."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer73->Add(m_ProjectCommunitcationsCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_FinalAccountCreationStatusCtrl = new wxStaticText;
    m_FinalAccountCreationStatusCtrl->Create( itemWizardPage69, ID_FINALACCOUNTCREATIONSTATUSCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer70->Add(m_FinalAccountCreationStatusCtrl, 0, wxALIGN_LEFT|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else if (GetProjectCommunitcationsSucceeded()) {
        // We were successful in creating or retrieving an account
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONPAGE);
    } else if (!GetProjectCommunitcationsSucceeded() && GetProjectAccountAlreadyExists()) {
        // The requested account already exists
        return PAGE_TRANSITION_NEXT(ID_ERRACCOUNTALREADYEXISTSPAGE);
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

void CAccountCreationPage::SetupProgressImage(wxStaticBitmap* pImage, int& iImageIndex) {
    iImageIndex = 1;
    pImage->SetBitmap(GetBitmapResource(wxT("res/wizprogress1.xpm")));
}

void CAccountCreationPage::IncrementProgressImage(wxStaticBitmap* pImage, int& iImageIndex) {
    wxString strBuffer;

    iImageIndex += 1;
    if (4 < iImageIndex) iImageIndex = 1;

    strBuffer.Printf(wxT("res/wizprogress%d.xpm"), iImageIndex);

    pImage->SetBitmap(GetBitmapResource(strBuffer));
    Update();
}

/*!
 * Get bitmap resources
 */

wxBitmap CAccountCreationPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    if (name == wxT("res/wizprogress1.xpm"))
    {
        wxBitmap bitmap(wizprogress1_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizprogress2.xpm"))
    {
        wxBitmap bitmap(wizprogress2_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizprogress3.xpm"))
    {
        wxBitmap bitmap(wizprogress3_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizprogress4.xpm"))
    {
        wxBitmap bitmap(wizprogress4_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizfailure.xpm"))
    {
        wxBitmap bitmap(wizfailure_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizsuccess.xpm"))
    {
        wxBitmap bitmap(wizsuccess_xpm);
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
 * wxEVT_WIZARD_CANCEL event handler for ID_ACCOUNTCREATIONPAGE
 */

void CAccountCreationPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
}

/*!
 * wxEVT_ACCOUNTCREATION_STATECHANGE event handler for ID_ACCOUNTCREATIONPAGE
 */

void CAccountCreationPage::OnStateChange( CAccountCreationPageEvent& event )
{
    CMainDocument* pDoc      = wxGetApp().GetDocument();
    ACCOUNT_IN* ai           = &((CWizAttachProject*)GetParent())->account_in;
    ACCOUNT_OUT* ao          = &((CWizAttachProject*)GetParent())->account_out;
    bool bPostNewEvent = true;
    int iReturnValue = 0;
    bool bSuccessfulCondition = false;

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    wxFont fontOriginal = m_FinalAccountCreationStatusCtrl->GetFont();
    wxFont fontBold = m_FinalAccountCreationStatusCtrl->GetFont();
    fontBold.SetWeight(wxBOLD);

    switch(GetCurrentState()) {
        case ACCOUNTCREATION_INIT:
            // Change the cursor to an hourglass
            ::wxBeginBusyCursor();

            // Set initial bitmap
            SetupProgressImage(m_ProjectCommunitcationsImageCtrl, m_iProjectCommunitcationsProgressImage);

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
            // Attempt to create the account or reterieve the authenticator.
            ai->clear();
            ao->clear();
            if (((CWizAttachProject*)GetParent())->m_AccountInfoPage->m_AccountCreateCtrl->GetValue()) {
                if (!((CWizAttachProject*)GetParent())->project_config.uses_username) {
                    ai->email_addr = ((CWizAttachProject*)GetParent())->m_AccountInfoPage->GetAccountEmailAddress().c_str();
                    ai->user_name = ::wxGetUserName().c_str();
                } else {
                    ai->email_addr = wxT("");
                    ai->user_name = ((CWizAttachProject*)GetParent())->m_AccountInfoPage->GetAccountEmailAddress().c_str();
                }
                ai->passwd = ((CWizAttachProject*)GetParent())->m_AccountInfoPage->GetAccountPassword().c_str();
                ai->url = ((CWizAttachProject*)GetParent())->m_ProjectInfoPage->GetProjectURL().c_str();
                pDoc->rpc.create_account(*ai);

                // Wait until we are done processing the request.
                iReturnValue = ERR_IN_PROGRESS;
                while (ERR_IN_PROGRESS == iReturnValue) {
                    iReturnValue = pDoc->rpc.create_account_poll(*ao);
                    wxSleep(1);
 
                    // Show a glimer of progress by incrementing the progress bitmap
                    IncrementProgressImage(m_ProjectCommunitcationsImageCtrl, m_iProjectCommunitcationsProgressImage);
               }
            } else {
                if (!((CWizAttachProject*)GetParent())->project_config.uses_username) {
                    ai->email_addr = ((CWizAttachProject*)GetParent())->m_AccountInfoPage->GetAccountEmailAddress().c_str();
                } else {
                    ai->user_name= ((CWizAttachProject*)GetParent())->m_AccountInfoPage->GetAccountEmailAddress().c_str();
                }
                ai->passwd = ((CWizAttachProject*)GetParent())->m_AccountInfoPage->GetAccountPassword().c_str();
                ai->url = ((CWizAttachProject*)GetParent())->m_ProjectInfoPage->GetProjectURL().c_str();
                pDoc->rpc.lookup_account(*ai);

                // Wait until we are done processing the request.
                iReturnValue = ERR_IN_PROGRESS;
                while (ERR_IN_PROGRESS == iReturnValue) {
                    iReturnValue = pDoc->rpc.lookup_account_poll(*ao);
                    wxSleep(1);

                    // Show a glimer of progress by incrementing the progress bitmap
                    IncrementProgressImage(m_ProjectCommunitcationsImageCtrl, m_iProjectCommunitcationsProgressImage);
                }
            }

            if ((BOINC_SUCCESS == iReturnValue) && !CHECK_DEBUG_FLAG(WIZDEBUG_ERRPROJECTCOMM)) {
                m_ProjectCommunitcationsImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizsuccess.xpm")));
                SetProjectCommunitcationsSucceeded(true);
            } else {
                m_ProjectCommunitcationsImageCtrl->SetBitmap(GetBitmapResource(wxT("res/wizfailure.xpm")));
                SetProjectCommunitcationsSucceeded(false);

                if ((ERR_NONUNIQUE_EMAIL == iReturnValue) || CHECK_DEBUG_FLAG(WIZDEBUG_ERRACCOUNTALREADYEXISTS)) {
                    SetProjectAccountAlreadyExists(true);
                } else {
                    SetProjectAccountAlreadyExists(false);
                }
            }

            SetNextState(ACCOUNTCREATION_CLEANUP);
            break;
        case ACCOUNTCREATION_CLEANUP:
            m_ProjectCommunitcationsCtrl->SetFont(fontOriginal);
            SetNextState(ACCOUNTCREATION_END);
            break;
        default:
            // Allow a glimps of what the result was before advancing to the next page.
            wxSleep(1);
            ((CWizAttachProject*)GetParent())->SimulateNextButton();

            // Change the cursor to a normal cursor
            ::wxEndBusyCursor();

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
    EVT_WIZARD_PAGE_CHANGED( -1, CCompletionPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CCompletionPage::OnCancel )
    EVT_WIZARD_FINISHED( ID_COMPLETIONPAGE, CCompletionPage::OnFinished )

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
 * CCompletionPage creator
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
 * Control creation for CCompletionPage
 */

void CCompletionPage::CreateControls()
{    
////@begin CCompletionPage content construction
    CCompletionPage* itemWizardPage77 = this;

    wxBoxSizer* itemBoxSizer78 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage77->SetSizer(itemBoxSizer78);

    wxStaticText* itemStaticText79 = new wxStaticText;
    itemStaticText79->Create( itemWizardPage77, wxID_STATIC, _("Completing the Attach to Project\nWizard"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText79->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer78->Add(itemStaticText79, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText80 = new wxStaticText;
    itemStaticText80->Create( itemWizardPage77, wxID_STATIC, _("You have successfully completed the Attach to Project wizard."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer78->Add(itemStaticText80, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer78->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText82 = new wxStaticText;
    itemStaticText82->Create( itemWizardPage77, wxID_STATIC, _("BOINC will now attach to the following project with the following\naccount:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer78->Add(itemStaticText82, 0, wxALIGN_LEFT|wxALL, 5);

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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_COMPLETIONPAGE
 */

void CCompletionPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_COMPLETIONPAGE
 */

void CCompletionPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
}

/*!
 * wxEVT_WIZARD_FINISHED event handler for ID_COMPLETIONPAGE
 */

void CCompletionPage::OnFinished( wxWizardEvent& event ) {
#if 0
    CMainDocument* pDoc      = wxGetApp().GetDocument();

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    // If the wizard was successful and everything is cool, tell the
    //   core client to attach to the project with the authenticator.
    if ( m_AccountCreationPage->GetProjectCommunitcationsSucceeded() &&
         account_out.authenticator.length() > 0 &&
         account_in.url.length() > 0
       )
    {
        pDoc->rpc.project_attach(
            account_in.url.c_str(),
            account_out.authenticator.c_str()
        );
    } else {
#if defined(__WXDEBUG__)
        if (!m_AccountCreationPage->GetProjectCommunitcationsSucceeded()) {
            ::wxMessageBox(
                wxT("m_AccountCreationPage->GetProjectCommunitcationsSucceeded() = false"),
                wxT("Attach to Project Wizard"),
                wxICON_ERROR | wxOK,
                this
            );
        } else if (account_in.url.length() == 0) {
            ::wxMessageBox(
                wxT("account_in.url.length() == 0"),
                wxT("Attach to Project Wizard"),
                wxICON_ERROR | wxOK,
                this
            );
        } else if (account_out.authenticator.length() == 0) {
            ::wxMessageBox(
                wxT("account_out.authenticator.length() == 0"),
                wxT("Attach to Project Wizard"),
                wxICON_ERROR | wxOK,
                this
            );
        }
#endif
    }
#endif
    // Let the framework clean everything up.
    event.Skip();
}

/*!
 * CCompletionErrorPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CCompletionErrorPage, wxWizardPage )

/*!
 * CCompletionErrorPage event table definition
 */

BEGIN_EVENT_TABLE( CCompletionErrorPage, wxWizardPage )

////@begin CCompletionErrorPage event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, CCompletionErrorPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CCompletionErrorPage::OnCancel )

////@end CCompletionErrorPage event table entries

END_EVENT_TABLE()

/*!
 * CCompletionErrorPage constructors
 */

CCompletionErrorPage::CCompletionErrorPage( )
{
}

CCompletionErrorPage::CCompletionErrorPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CAccountResultPage creator
 */

bool CCompletionErrorPage::Create( wxWizard* parent )
{
////@begin CCompletionErrorPage member initialisation
////@end CCompletionErrorPage member initialisation

////@begin CCompletionErrorPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CCompletionErrorPage creation
    return TRUE;
}

/*!
 * Control creation for CAccountResultPage
 */

void CCompletionErrorPage::CreateControls()
{    
////@begin CCompletionErrorPage content construction
    CCompletionErrorPage* itemWizardPage83 = this;

    wxBoxSizer* itemBoxSizer84 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage83->SetSizer(itemBoxSizer84);

    wxStaticText* itemStaticText85 = new wxStaticText;
    itemStaticText85->Create( itemWizardPage83, wxID_STATIC, _("Completing the Attach to Project\nWizard"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText85->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer84->Add(itemStaticText85, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer84->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText87 = new wxStaticText;
    itemStaticText87->Create( itemWizardPage83, wxID_STATIC, _("The Attach to Project Wizard did not complete successfully,\neither because you clicked Cancel or because an error\noccurred."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer84->Add(itemStaticText87, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer84->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText89 = new wxStaticText;
    itemStaticText89->Create( itemWizardPage83, wxID_STATIC, _("To close this wizard, click Finish."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer84->Add(itemStaticText89, 0, wxALIGN_LEFT|wxALL, 5);

////@end CCompletionErrorPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CCompletionErrorPage::GetPrev() const
{
    return NULL;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CCompletionErrorPage::GetNext() const
{
    return NULL;
}

/*!
 * Should we show tooltips?
 */

bool CCompletionErrorPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CCompletionErrorPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CCompletionErrorPage bitmap retrieval
    return wxNullBitmap;
////@end CCompletionErrorPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CCompletionErrorPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CCompletionErrorPage icon retrieval
    return wxNullIcon;
////@end CCompletionErrorPage icon retrieval
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_COMPLETIONERRORPAGE
 */

void CCompletionErrorPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_COMPLETIONERRORPAGE
 */

void CCompletionErrorPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
}

/*!
 * CErrProjectNotDetectedPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrProjectNotDetectedPage, wxWizardPage )

/*!
 * CErrProjectNotDetectedPage event table definition
 */

BEGIN_EVENT_TABLE( CErrProjectNotDetectedPage, wxWizardPage )

////@begin CErrProjectNotDetectedPage event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, CErrProjectNotDetectedPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CErrProjectNotDetectedPage::OnCancel )

////@end CErrProjectNotDetectedPage event table entries

END_EVENT_TABLE()

/*!
 * CErrProjectNotDetectedPage constructors
 */

CErrProjectNotDetectedPage::CErrProjectNotDetectedPage( )
{
}

CErrProjectNotDetectedPage::CErrProjectNotDetectedPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrProjectUnavailable creator
 */

bool CErrProjectNotDetectedPage::Create( wxWizard* parent )
{
////@begin CErrProjectNotDetectedPage member initialisation
////@end CErrProjectNotDetectedPage member initialisation

////@begin CErrProjectNotDetectedPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrProjectNotDetectedPage creation
    return TRUE;
}

/*!
 * Control creation for CErrProjectUnavailable
 */

void CErrProjectNotDetectedPage::CreateControls()
{    
////@begin CErrProjectNotDetectedPage content construction
    CErrProjectNotDetectedPage* itemWizardPage90 = this;

    wxBoxSizer* itemBoxSizer91 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage90->SetSizer(itemBoxSizer91);

    wxStaticText* itemStaticText92 = new wxStaticText;
    itemStaticText92->Create( itemWizardPage90, wxID_STATIC, _("Project Not Detected"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText92->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer91->Add(itemStaticText92, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer91->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText94 = new wxStaticText;
    itemStaticText94->Create( itemWizardPage90, wxID_STATIC, _("The project URL provided does not appear to be a BOINC-based\nproject."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer91->Add(itemStaticText94, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText95 = new wxStaticText;
    itemStaticText95->Create( itemWizardPage90, wxID_STATIC, _("You should checkout the project�s homepage for news about\npossible project issues and verify that the project URL provided is\ncorrect."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer91->Add(itemStaticText95, 0, wxALIGN_LEFT|wxALL, 5);

////@end CErrProjectNotDetectedPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrProjectNotDetectedPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrProjectNotDetectedPage::GetNext() const
{
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    }
    return NULL;
}

/*!
 * Should we show tooltips?
 */

bool CErrProjectNotDetectedPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrProjectNotDetectedPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrProjectNotDetectedPage bitmap retrieval
    return wxNullBitmap;
////@end CErrProjectNotDetectedPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrProjectNotDetectedPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrProjectNotDetectedPage icon retrieval
    return wxNullIcon;
////@end CErrProjectNotDetectedPage icon retrieval
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ERRPROJECTNOTDETECTEDPAGE
 */

void CErrProjectNotDetectedPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ERRPROJECTNOTDETECTEDPAGE
 */

void CErrProjectNotDetectedPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CErrProjectUnavailablePage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CErrProjectUnavailablePage::OnCancel )

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
 * CErrProjectUnavailablePage creator
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
 * Control creation for CErrProjectUnavailablePage
 */

void CErrProjectUnavailablePage::CreateControls()
{    
////@begin CErrProjectUnavailablePage content construction
    CErrProjectUnavailablePage* itemWizardPage96 = this;

    wxBoxSizer* itemBoxSizer97 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage96->SetSizer(itemBoxSizer97);

    wxStaticText* itemStaticText98 = new wxStaticText;
    itemStaticText98->Create( itemWizardPage96, wxID_STATIC, _("Project Temporarily Unavailable"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText98->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer97->Add(itemStaticText98, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer97->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText100 = new wxStaticText;
    itemStaticText100->Create( itemWizardPage96, wxID_STATIC, _("We could not talk to the server, please try again later."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer97->Add(itemStaticText100, 0, wxALIGN_LEFT|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ERRPROJECTUNAVAILABLEPAGE
 */

void CErrProjectUnavailablePage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ERRPROJECTUNAVAILABLEPAGE
 */

void CErrProjectUnavailablePage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CErrNoInternetConnectionPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CErrNoInternetConnectionPage::OnCancel )

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
    CErrNoInternetConnectionPage* itemWizardPage101 = this;

    wxBoxSizer* itemBoxSizer102 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage101->SetSizer(itemBoxSizer102);

    wxStaticText* itemStaticText103 = new wxStaticText;
    itemStaticText103->Create( itemWizardPage101, wxID_STATIC, _("No Internet Connection Detected"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText103->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer102->Add(itemStaticText103, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer102->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText105 = new wxStaticText;
    itemStaticText105->Create( itemWizardPage101, wxID_STATIC, _("Please verify you have an internet connection and try again."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer102->Add(itemStaticText105, 0, wxALIGN_LEFT|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ERRNOINTERNETCONNECTIONPAGE
 */

void CErrNoInternetConnectionPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ERRNOINTERNETCONNECTIONPAGE
 */

void CErrNoInternetConnectionPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CErrAccountAlreadyExistsPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CErrAccountAlreadyExistsPage::OnCancel )

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
    CErrAccountAlreadyExistsPage* itemWizardPage106 = this;

    wxBoxSizer* itemBoxSizer107 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage106->SetSizer(itemBoxSizer107);

    wxStaticText* itemStaticText108 = new wxStaticText;
    itemStaticText108->Create( itemWizardPage106, wxID_STATIC, _("Account Already Exists"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText108->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer107->Add(itemStaticText108, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer107->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText110 = new wxStaticText;
    itemStaticText110->Create( itemWizardPage106, wxID_STATIC, _("The requested account is already in use."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer107->Add(itemStaticText110, 0, wxALIGN_LEFT|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ERRACCOUNTALREADYEXISTSPAGE
 */

void CErrAccountAlreadyExistsPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ERRACCOUNTALREADYEXISTSPAGE
 */

void CErrAccountAlreadyExistsPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CErrAccountCreationDisabledPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CErrAccountCreationDisabledPage::OnCancel )

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
    CErrAccountCreationDisabledPage* itemWizardPage111 = this;

    wxBoxSizer* itemBoxSizer112 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage111->SetSizer(itemBoxSizer112);

    wxStaticText* itemStaticText113 = new wxStaticText;
    itemStaticText113->Create( itemWizardPage111, wxID_STATIC, _("Account Creation Disabled"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText113->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer112->Add(itemStaticText113, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer112->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText115 = new wxStaticText;
    itemStaticText115->Create( itemWizardPage111, wxID_STATIC, _("This project is not accepting any new accounts at this time."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer112->Add(itemStaticText115, 0, wxALIGN_LEFT|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ERRACCOUNTCREATIONDISABLEDPAGE
 */

void CErrAccountCreationDisabledPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ERRACCOUNTCREATIONDISABLEDPAGE
 */

void CErrAccountCreationDisabledPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CErrProxyInfoPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CErrProxyInfoPage::OnCancel )

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
    CErrProxyInfoPage* itemWizardPage116 = this;

    wxBoxSizer* itemBoxSizer117 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage116->SetSizer(itemBoxSizer117);

    wxStaticText* itemStaticText118 = new wxStaticText;
    itemStaticText118->Create( itemWizardPage116, wxID_STATIC, _("Proxy Configuration"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText118->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer117->Add(itemStaticText118, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText119 = new wxStaticText;
    itemStaticText119->Create( itemWizardPage116, wxID_STATIC, _("Do you need to configure a proxy server?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer117->Add(itemStaticText119, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer117->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else {
        return PAGE_TRANSITION_NEXT(ID_ERRPROXYHTTPPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ERRPROXYINFOPAGE
 */

void CErrProxyInfoPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ERRPROXYINFOPAGE
 */

void CErrProxyInfoPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CErrProxyHTTPPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CErrProxyHTTPPage::OnCancel )

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
    CErrProxyHTTPPage* itemWizardPage121 = this;

    wxBoxSizer* itemBoxSizer122 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage121->SetSizer(itemBoxSizer122);

    wxStaticText* itemStaticText123 = new wxStaticText;
    itemStaticText123->Create( itemWizardPage121, wxID_STATIC, _("Proxy Configuration - HTTP Proxy"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText123->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer122->Add(itemStaticText123, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText124 = new wxStaticText;
    itemStaticText124->Create( itemWizardPage121, wxID_STATIC, _("Do you need to configure a proxy server?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer122->Add(itemStaticText124, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer122->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer122->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxButton* itemButton127 = new wxButton;
    itemButton127->Create( itemWizardPage121, ID_HTTPAUTODETECT, _("Autodetect"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer122->Add(itemButton127, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer128 = new wxFlexGridSizer(3, 2, 0, 0);
    itemFlexGridSizer128->AddGrowableCol(1);
    itemBoxSizer122->Add(itemFlexGridSizer128, 0, wxGROW|wxALL, 5);

    m_ProxyHTTPServerStaticCtrl = new wxStaticText;
    m_ProxyHTTPServerStaticCtrl->Create( itemWizardPage121, ID_PROXYHTTPSERVERSTATICCTRL, _("Server:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer128->Add(m_ProxyHTTPServerStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer130 = new wxFlexGridSizer(1, 3, 0, 0);
    itemFlexGridSizer130->AddGrowableCol(0);
    itemFlexGridSizer128->Add(itemFlexGridSizer130, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ProxyHTTPServerCtrl = new wxTextCtrl;
    m_ProxyHTTPServerCtrl->Create( itemWizardPage121, ID_PROXYHTTPSERVERCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer130->Add(m_ProxyHTTPServerCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPPortStaticCtrl = new wxStaticText;
    m_ProxyHTTPPortStaticCtrl->Create( itemWizardPage121, ID_PROXYHTTPPORTSTATICCTRL, _("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer130->Add(m_ProxyHTTPPortStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPPortCtrl = new wxTextCtrl;
    m_ProxyHTTPPortCtrl->Create( itemWizardPage121, ID_PROXYHTTPPORTCTRL, _T(""), wxDefaultPosition, wxSize(50, -1), 0 );
    itemFlexGridSizer130->Add(m_ProxyHTTPPortCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPUsernameStaticCtrl = new wxStaticText;
    m_ProxyHTTPUsernameStaticCtrl->Create( itemWizardPage121, ID_PROXYHTTPUSERNAMESTATICCTRL, _("User Name:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer128->Add(m_ProxyHTTPUsernameStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPUsernameCtrl = new wxTextCtrl;
    m_ProxyHTTPUsernameCtrl->Create( itemWizardPage121, ID_PROXYHTTPUSERNAMECTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer128->Add(m_ProxyHTTPUsernameCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPPasswordStaticCtrl = new wxStaticText;
    m_ProxyHTTPPasswordStaticCtrl->Create( itemWizardPage121, ID_PROXYHTTPPASSWORDSTATICCTRL, _("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer128->Add(m_ProxyHTTPPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxyHTTPPasswordCtrl = new wxTextCtrl;
    m_ProxyHTTPPasswordCtrl->Create( itemWizardPage121, ID_PROXYHTTPPASSWORDCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer128->Add(m_ProxyHTTPPasswordCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else {
        return PAGE_TRANSITION_NEXT(ID_ERRPROXYSOCKSPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ERRPROXYHTTPPAGE
 */

void CErrProxyHTTPPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ERRPROXYHTTPPAGE
 */

void CErrProxyHTTPPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CErrProxySOCKSPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CErrProxySOCKSPage::OnCancel )

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
    CErrProxySOCKSPage* itemWizardPage138 = this;

    wxBoxSizer* itemBoxSizer139 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage138->SetSizer(itemBoxSizer139);

    wxStaticText* itemStaticText140 = new wxStaticText;
    itemStaticText140->Create( itemWizardPage138, wxID_STATIC, _("Proxy Configuration - SOCKS Proxy"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText140->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer139->Add(itemStaticText140, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText141 = new wxStaticText;
    itemStaticText141->Create( itemWizardPage138, wxID_STATIC, _("Do you need to configure a proxy server?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer139->Add(itemStaticText141, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer139->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer139->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxButton* itemButton144 = new wxButton;
    itemButton144->Create( itemWizardPage138, ID_SOCKSAUTODETECT, _("Autodetect"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer139->Add(itemButton144, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer145 = new wxFlexGridSizer(3, 2, 0, 0);
    itemFlexGridSizer145->AddGrowableCol(1);
    itemBoxSizer139->Add(itemFlexGridSizer145, 0, wxGROW|wxALL, 5);

    m_ProxySOCKSServerStaticCtrl = new wxStaticText;
    m_ProxySOCKSServerStaticCtrl->Create( itemWizardPage138, ID_PROXYSOCKSSERVERSTATICCTRL, _("Server:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer145->Add(m_ProxySOCKSServerStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer147 = new wxFlexGridSizer(1, 3, 0, 0);
    itemFlexGridSizer147->AddGrowableCol(0);
    itemFlexGridSizer145->Add(itemFlexGridSizer147, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    m_ProxySOCKSServerCtrl = new wxTextCtrl;
    m_ProxySOCKSServerCtrl->Create( itemWizardPage138, ID_PROXYSOCKSSERVERCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer147->Add(m_ProxySOCKSServerCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSPortStaticCtrl = new wxStaticText;
    m_ProxySOCKSPortStaticCtrl->Create( itemWizardPage138, ID_PROXYSOCKSPORTSTATICCTRL, _("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer147->Add(m_ProxySOCKSPortStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSPortCtrl = new wxTextCtrl;
    m_ProxySOCKSPortCtrl->Create( itemWizardPage138, ID_PROXYSOCKSPORTCTRL, _T(""), wxDefaultPosition, wxSize(50, -1), 0 );
    itemFlexGridSizer147->Add(m_ProxySOCKSPortCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSUsernameStaticCtrl = new wxStaticText;
    m_ProxySOCKSUsernameStaticCtrl->Create( itemWizardPage138, ID_PROXYSOCKSUSERNAMESTATICCTRL, _("User Name:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer145->Add(m_ProxySOCKSUsernameStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSUsernameCtrl = new wxTextCtrl;
    m_ProxySOCKSUsernameCtrl->Create( itemWizardPage138, ID_PROXYSOCKSUSERNAMECTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer145->Add(m_ProxySOCKSUsernameCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSPasswordStaticCtrl = new wxStaticText;
    m_ProxySOCKSPasswordStaticCtrl->Create( itemWizardPage138, ID_PROXYSOCKSPASSWORDSTATICCTRL, _("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer145->Add(m_ProxySOCKSPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ProxySOCKSPasswordCtrl = new wxTextCtrl;
    m_ProxySOCKSPasswordCtrl->Create( itemWizardPage138, ID_PROXYSOCKSPASSWORDCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer145->Add(m_ProxySOCKSPasswordCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else {
        return PAGE_TRANSITION_NEXT(ID_ERRPROXYCOMPLETIONPAGE);
    }
    return NULL;
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
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ERRPROXYSOCKSPAGE
 */

void CErrProxySOCKSPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ERRPROXYSOCKSPAGE
 */

void CErrProxySOCKSPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
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
    EVT_WIZARD_PAGE_CHANGED( -1, CErrProxyComplationPage::OnPageChanged )
    EVT_WIZARD_CANCEL( -1, CErrProxyComplationPage::OnCancel )

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
    CErrProxyComplationPage* itemWizardPage155 = this;

    wxBoxSizer* itemBoxSizer156 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage155->SetSizer(itemBoxSizer156);

    wxStaticText* itemStaticText157 = new wxStaticText;
    itemStaticText157->Create( itemWizardPage155, wxID_STATIC, _("Proxy Configuration Completion"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText157->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer156->Add(itemStaticText157, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText158 = new wxStaticText;
    itemStaticText158->Create( itemWizardPage155, wxID_STATIC, _("Do you need to configure a proxy server?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer156->Add(itemStaticText158, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer156->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

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
    if (((CWizAttachProject*)GetParent())->IsCancelInProgress()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else {
        return PAGE_TRANSITION_NEXT(ID_PROJECTPROPERTIESPAGE);
    }
    return NULL;
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

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ERRPROXYCOMPLETIONPAGE
 */

void CErrProxyComplationPage::OnPageChanged( wxWizardEvent& event ) {
    event.Skip();
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ERRPROXYCOMPLETIONPAGE
 */

void CErrProxyComplationPage::OnCancel( wxWizardEvent& event ) {
    ((CWizAttachProject*)GetParent())->ProcessCancelEvent(event);
}

/*!
 * CErrRefCountPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CErrRefCountPage, wxWizardPage )

/*!
 * CErrRefCountPage event table definition
 */

BEGIN_EVENT_TABLE( CErrRefCountPage, wxWizardPage )

////@begin CErrRefCountPage event table entries
////@end CErrRefCountPage event table entries

END_EVENT_TABLE()

/*!
 * CErrRefCountPage constructors
 */

CErrRefCountPage::CErrRefCountPage( )
{
}

CErrRefCountPage::CErrRefCountPage( wxWizard* parent )
{
    Create( parent );
}

/*!
 * CErrRefCountPage creator
 */

bool CErrRefCountPage::Create( wxWizard* parent )
{
////@begin CErrRefCountPage member initialisation
////@end CErrRefCountPage member initialisation

////@begin CErrRefCountPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPage::Create( parent, wizardBitmap );

    CreateControls();
    GetSizer()->Fit(this);
////@end CErrRefCountPage creation
    return TRUE;
}

/*!
 * Control creation for CErrRefCountPage
 */

void CErrRefCountPage::CreateControls()
{    
////@begin CErrRefCountPage content construction
    CErrRefCountPage* itemWizardPage160 = this;

    wxBoxSizer* itemBoxSizer161 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage160->SetSizer(itemBoxSizer161);

    wxStaticText* itemStaticText162 = new wxStaticText;
    itemStaticText162->Create( itemWizardPage160, wxID_STATIC, _("Ref Count Page"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText162->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer161->Add(itemStaticText162, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText163 = new wxStaticText;
    itemStaticText163->Create( itemWizardPage160, wxID_STATIC, _("This page should never be used in the wizard itself."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer161->Add(itemStaticText163, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer161->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText165 = new wxStaticText;
    itemStaticText165->Create( itemWizardPage160, wxID_STATIC, _("This page just increases the refcount of various bitmap resources\nso that DialogBlocks doesn't nuke the refences to them."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer161->Add(itemStaticText165, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer166 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer161->Add(itemBoxSizer166, 0, wxALIGN_LEFT|wxALL, 5);

    wxBitmap itemStaticBitmap167Bitmap(itemWizardPage160->GetBitmapResource(wxT("res/wizprogress1.xpm")));
    wxStaticBitmap* itemStaticBitmap167 = new wxStaticBitmap;
    itemStaticBitmap167->Create( itemWizardPage160, wxID_STATIC, itemStaticBitmap167Bitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemBoxSizer166->Add(itemStaticBitmap167, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmap itemStaticBitmap168Bitmap(itemWizardPage160->GetBitmapResource(wxT("res/wizprogress2.xpm")));
    wxStaticBitmap* itemStaticBitmap168 = new wxStaticBitmap;
    itemStaticBitmap168->Create( itemWizardPage160, wxID_STATIC, itemStaticBitmap168Bitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemBoxSizer166->Add(itemStaticBitmap168, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmap itemStaticBitmap169Bitmap(itemWizardPage160->GetBitmapResource(wxT("res/wizprogress3.xpm")));
    wxStaticBitmap* itemStaticBitmap169 = new wxStaticBitmap;
    itemStaticBitmap169->Create( itemWizardPage160, wxID_STATIC, itemStaticBitmap169Bitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemBoxSizer166->Add(itemStaticBitmap169, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmap itemStaticBitmap170Bitmap(itemWizardPage160->GetBitmapResource(wxT("res/wizprogress4.xpm")));
    wxStaticBitmap* itemStaticBitmap170 = new wxStaticBitmap;
    itemStaticBitmap170->Create( itemWizardPage160, wxID_STATIC, itemStaticBitmap170Bitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemBoxSizer166->Add(itemStaticBitmap170, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmap itemStaticBitmap171Bitmap(itemWizardPage160->GetBitmapResource(wxT("res/wizfailure.xpm")));
    wxStaticBitmap* itemStaticBitmap171 = new wxStaticBitmap;
    itemStaticBitmap171->Create( itemWizardPage160, wxID_STATIC, itemStaticBitmap171Bitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemBoxSizer166->Add(itemStaticBitmap171, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmap itemStaticBitmap172Bitmap(itemWizardPage160->GetBitmapResource(wxT("res/wizsuccess.xpm")));
    wxStaticBitmap* itemStaticBitmap172 = new wxStaticBitmap;
    itemStaticBitmap172->Create( itemWizardPage160, wxID_STATIC, itemStaticBitmap172Bitmap, wxDefaultPosition, wxSize(16, 16), 0 );
    itemBoxSizer166->Add(itemStaticBitmap172, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end CErrRefCountPage content construction
}

/*!
 * Gets the previous page.
 */

wxWizardPage* CErrRefCountPage::GetPrev() const
{
    return NULL;
}

/*!
 * Gets the next page.
 */

wxWizardPage* CErrRefCountPage::GetNext() const
{
    return NULL;
}

/*!
 * Should we show tooltips?
 */

bool CErrRefCountPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CErrRefCountPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CErrRefCountPage bitmap retrieval
    if (name == wxT("res/wizprogress1.xpm"))
    {
        wxBitmap bitmap(wizprogress1_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizprogress2.xpm"))
    {
        wxBitmap bitmap(wizprogress2_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizprogress3.xpm"))
    {
        wxBitmap bitmap(wizprogress3_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizprogress4.xpm"))
    {
        wxBitmap bitmap(wizprogress4_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizfailure.xpm"))
    {
        wxBitmap bitmap(wizfailure_xpm);
        return bitmap;
    }
    else if (name == wxT("res/wizsuccess.xpm"))
    {
        wxBitmap bitmap(wizsuccess_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end CErrRefCountPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CErrRefCountPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CErrRefCountPage icon retrieval
    return wxNullIcon;
////@end CErrRefCountPage icon retrieval
}
