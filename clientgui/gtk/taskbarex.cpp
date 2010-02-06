/////////////////////////////////////////////////////////////////////////
// File:        src/gtk/taskbarex.cpp
// Purpose:     wxTaskBarIconEx
// Author:      Vaclav Slavik
// Modified by: Paul Cornett / Rom Walton
// Created:     2004/05/29
// RCS-ID:      $Id$
// Copyright:   (c) Vaclav Slavik, 2004
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "taskbarex.h"
#endif

#include "stdwx.h"

#include <gtk/gtk.h>
#include <libnotify/notify.h>

#include "BOINCGUIApp.h"
#include "gtk/taskbarex.h"
#include "BOINCTaskBar.h"


//-----------------------------------------------------------------------------

extern "C" {

    static void
    status_icon_activate(GtkStatusIcon*, wxTaskBarIconEx* taskBarIcon)
    {
        wxTaskBarIconEvent eventLeftDClick(wxEVT_TASKBAR_LEFT_DCLICK, taskBarIcon);
        taskBarIcon->SafelyProcessEvent(eventLeftDClick);
    }

    static void
    status_icon_popup_menu(GtkStatusIcon*, guint, guint, wxTaskBarIconEx* taskBarIcon)
    {
        wxTaskBarIconEvent eventDown(EVT_TASKBAR_RIGHT_DOWN, taskBarIcon);
        taskBarIcon->SafelyProcessEvent(eventDown);
        wxTaskBarIconEvent eventUp(EVT_TASKBAR_RIGHT_UP, taskBarIcon);
        taskBarIcon->SafelyProcessEvent(eventUp);
    }

    static void
    statis_icon_notification_closed(NotifyNotification *notification, wxTaskBarIconEx* taskBarIcon)
    {

    }
}


//-----------------------------------------------------------------------------


wxChar* wxTaskBarExWindow      = (wxChar*) wxT("wxTaskBarExWindow");


DEFINE_EVENT_TYPE( wxEVT_TASKBAR_CREATED )
DEFINE_EVENT_TYPE( wxEVT_TASKBAR_CONTEXT_MENU )
DEFINE_EVENT_TYPE( wxEVT_TASKBAR_SELECT )
DEFINE_EVENT_TYPE( wxEVT_TASKBAR_KEY_SELECT )
DEFINE_EVENT_TYPE( wxEVT_TASKBAR_BALLOON_SHOW )
DEFINE_EVENT_TYPE( wxEVT_TASKBAR_BALLOON_HIDE )
DEFINE_EVENT_TYPE( wxEVT_TASKBAR_BALLOON_TIMEOUT )
DEFINE_EVENT_TYPE( wxEVT_TASKBAR_BALLOON_USERCLICK )
DEFINE_EVENT_TYPE( wxEVT_TASKBAR_SHUTDOWN )

IMPLEMENT_DYNAMIC_CLASS(wxTaskBarIconEx, wxEvtHandler)

BEGIN_EVENT_TABLE (wxTaskBarIconEx, wxEvtHandler)
END_EVENT_TABLE ()


wxTaskBarIconEx::wxTaskBarIconEx()
{
    m_pWnd = NULL;
    m_iTaskbarID = 0;
    m_pStatusIcon = NULL;
    m_pNotification = NULL;

    notify_init(wxTaskBarExWindow);
}

wxTaskBarIconEx::wxTaskBarIconEx( wxChar* szWindowTitle, wxInt32 iTaskbarID )
{
    m_pWnd = NULL;
    m_iTaskbarID = iTaskbarID;
    m_pStatusIcon = NULL;
    m_pNotification = NULL;

    notify_init(szWindowTitle);
}

wxTaskBarIconEx::~wxTaskBarIconEx()
{
    if (m_pWnd)
    {
        m_pWnd->PopEventHandler();
        m_pWnd->Destroy();
        m_pWnd = NULL;
    }

    if (m_pStatusIcon)
    {
        g_object_unref(m_pStatusIcon);
        m_pStatusIcon = NULL;
    }

    if (m_pNotification)
    {
        notify_notification_close(m_pNotification, NULL);
        m_pNotification = NULL;
    }
}

// Operations
bool wxTaskBarIconEx::SetIcon(const wxIcon& icon, const wxString& message)
{
    if (!IsOK())
        return false;

    if (!icon.Ok())
        return false;

    wxBitmap bitmap = icon;

    if (!m_pStatusIcon)
    {
        m_pStatusIcon = gtk_status_icon_new_from_pixbuf(bitmap.GetPixbuf());
        g_signal_connect(m_pStatusIcon, "activate", G_CALLBACK(status_icon_activate), this);
        g_signal_connect(m_pStatusIcon, "popup_menu", G_CALLBACK(status_icon_popup_menu), this);
    }

    gtk_status_icon_set_from_pixbuf(m_pStatusIcon, bitmap.GetPixbuf());
    if (!message.empty())
    {
        gtk_status_icon_set_tooltip(m_pStatusIcon, message.mb_str());
    }
    gtk_status_icon_set_visible(m_pStatusIcon, TRUE);

    return true;
}

bool wxTaskBarIconEx::SetBalloon(const wxIcon& icon, const wxString title, const wxString message, unsigned int iconballoon)
{
    if (!IsOK())
        return false;

    if (!icon.Ok())
        return false;

    if (!SetIcon(icon, wxEmptyString))
        return false;

    gchar* desired_icon = NULL;
    switch(iconballoon)
    {
        case BALLOONTYPE_INFO:
            desired_icon = GTK_STOCK_DIALOG_INFO;
            break;
        case BALLOONTYPE_WARNING:
            desired_icon = GTK_STOCK_DIALOG_WARNING;
            break;
        case BALLOONTYPE_ERROR:
            desired_icon = GTK_STOCK_DIALOG_ERROR;
            break;
    }

    if (!m_pNotification)
    {
        m_pNotification = 
            notify_notification_new_with_status_icon(
                title.mb_str(),
                message.mb_str(),
                desired_icon,
                m_pStatusIcon
            );
        g_signal_connect(m_pNotification, "closed", NOTIFY_ACTION_CALLBACK(statis_icon_notification_closed), this);
    }
    else
    {
        notify_notification_update(
            m_pNotification,
            title.mb_str(),
            message.mb_str(),
            desired_icon
        );
    }

    return notify_notification_show(m_pNotification, NULL);
}

bool wxTaskBarIconEx::QueueBalloon(const wxIcon& icon, const wxString title, const wxString message, unsigned int iconballoon)
{
    // There isn't two classifications of notifications on Linux as there is on Windows
    return SetBalloon(icon, title, message, iconballoon);
}

bool wxTaskBarIconEx::RemoveIcon()
{
    if (!IsOK())
        return false;

    if (m_pWnd)
    {
        m_pWnd->PopEventHandler();
        m_pWnd->Destroy();
        m_pWnd = NULL;
    }

    if (m_pStatusIcon)
    {
        g_object_unref(m_pStatusIcon);
        m_pStatusIcon = NULL;
    }

    if (m_pNotification)
    {
        notify_notification_close(m_pNotification, NULL);
        m_pNotification = NULL;
    }

    return true;
}

bool wxTaskBarIconEx::PopupMenu(wxMenu* menu)
{
#if wxUSE_MENUS

    if (m_pWin == NULL)
    {
        m_pWin = new wxTopLevelWindow(NULL, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
        m_pWin->PushEventHandler(this);
    }

    wxPoint point(-1, -1);
#ifdef __WXUNIVERSAL__
    point = wxGetMousePosition();
#endif

    m_pWin->PopupMenu(menu, point);

#endif // wxUSE_MENUS
    return true;
}

