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


GtkStatusIcon*      g_pStatusIcon;
NotifyNotification* g_pNotification;


//-----------------------------------------------------------------------------

extern "C" {

    static void
    status_icon_activate(GtkStatusIcon*, wxTaskBarIconEx* taskBarIcon)
    {
        wxTaskBarIconExEvent eventLeftDClick(wxEVT_TASKBAR_LEFT_DCLICK, taskBarIcon);
        taskBarIcon->ProcessEvent(eventLeftDClick);
    }

    static void
    status_icon_popup_menu(GtkStatusIcon*, guint, guint, wxTaskBarIconEx* taskBarIcon)
    {
        wxTaskBarIconExEvent eventDown(wxEVT_TASKBAR_RIGHT_DOWN, taskBarIcon);
        taskBarIcon->ProcessEvent(eventDown);
        wxTaskBarIconExEvent eventUp(wxEVT_TASKBAR_RIGHT_UP, taskBarIcon);
        taskBarIcon->ProcessEvent(eventUp);
    }

    static void
    statis_icon_notification_closed(NotifyNotification* notification, wxTaskBarIconEx* taskBarIcon)
    {
        int id, closed_reason;
        GValue val = { 0, };

        g_value_init(&val, G_TYPE_PARAM_UINT);

        g_object_get_property(G_OBJECT(notification), "id", val);
        id = g_value_get_int(&val);

        g_object_get_property(G_OBJECT(notification), "closed-reason", val);
        closed_reason = g_value_get_int(&val);

        if (id == taskBarIcon->GetNotificationID()) {
            fprintf(stdout, "Notification Closed: id: %d closed-reason: %d", id, closed_reason);
        }

        g_value_unset(&val);
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
    m_iTaskbarID = 1;
    m_iNotificationID = 1;
    g_pStatusIcon = NULL;
    g_pNotification = NULL;

    notify_init((const char*)wxString(wxTaskBarExWindow).mb_str());
}

wxTaskBarIconEx::wxTaskBarIconEx( wxChar* szWindowTitle, wxInt32 iTaskbarID )
{
    m_pWnd = NULL;
    m_iTaskbarID = iTaskbarID;
    m_iNotificationID = iTaskbarID;
    g_pStatusIcon = NULL;
    g_pNotification = NULL;

    notify_init((const char*)wxString(szWindowTitle).mb_str());
}

wxTaskBarIconEx::~wxTaskBarIconEx()
{
    if (m_pWnd)
    {
        m_pWnd->PopEventHandler();
        m_pWnd->Destroy();
        m_pWnd = NULL;
    }

    if (g_pStatusIcon)
    {
        g_object_unref(g_pStatusIcon);
        g_pStatusIcon = NULL;
    }

    if (g_pNotification)
    {
        notify_notification_close(g_pNotification, NULL);
        g_pNotification = NULL;
    }
}

bool wxTaskBarIconEx::IsIconInstalled() const {
    return g_pStatusIcon;
}


// Operations
bool wxTaskBarIconEx::SetIcon(const wxIcon& icon, const wxString& message)
{
    if (!IsOK())
        return false;

    if (!icon.Ok())
        return false;

    wxBitmap bitmap = icon;

    if (!g_pStatusIcon)
    {
        g_pStatusIcon = gtk_status_icon_new_from_pixbuf(bitmap.GetPixbuf());
        g_signal_connect(g_pStatusIcon, "activate", G_CALLBACK(status_icon_activate), this);
        g_signal_connect(g_pStatusIcon, "popup_menu", G_CALLBACK(status_icon_popup_menu), this);
    }

    gtk_status_icon_set_from_pixbuf(g_pStatusIcon, bitmap.GetPixbuf());
    if (!message.empty())
    {
        gtk_status_icon_set_tooltip(g_pStatusIcon, message.mb_str());
    }
    gtk_status_icon_set_visible(g_pStatusIcon, TRUE);

    return true;
}

bool wxTaskBarIconEx::SetBalloon(const wxIcon& icon, const wxString title, const wxString message, unsigned int iconballoon)
{
    wxLogTrace(wxT("Function Start/End"), wxT("wxTaskBarIconEx::SetBalloon - Function Begin"));

    bool retval = false;
    GError* error = NULL;
    GValue val = { 0, };

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

    if (!g_pNotification)
    {
        g_pNotification = 
            notify_notification_new_with_status_icon(
                title.mb_str(),
                message.mb_str(),
                desired_icon,
                g_pStatusIcon
            );

        g_value_init(&val, G_TYPE_PARAM_UINT);
        g_value_set_int(&val, m_iNotificationID);

        g_object_set_property(G_OBJECT(notification), "id", val);

        g_signal_connect(g_pNotification, "closed", G_CALLBACK(statis_icon_notification_closed), this);
    }
    else
    {
        notify_notification_update(
            g_pNotification,
            title.mb_str(),
            message.mb_str(),
            desired_icon
        );
    }

    retval = notify_notification_show(g_pNotification, &error);
    g_clear_error(&error);
    g_value_unset(&val);

    wxLogTrace(wxT("Function Start/End"), wxT("wxTaskBarIconEx::SetBalloon - Function End"));
    return retval;
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

    if (g_pStatusIcon)
    {
        g_object_unref(g_pStatusIcon);
        g_pStatusIcon = NULL;
    }

    if (g_pNotification)
    {
        notify_notification_close(g_pNotification, NULL);
        g_pNotification = NULL;
    }

    return true;
}

bool wxTaskBarIconEx::PopupMenu(wxMenu* menu)
{
#if wxUSE_MENUS

    if (m_pWnd == NULL)
    {
        m_pWnd = new wxTopLevelWindow(NULL, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
        m_pWnd->PushEventHandler(this);
    }

    wxPoint point(-1, -1);
#ifdef __WXUNIVERSAL__
    point = wxGetMousePosition();
#endif

    m_pWnd->PopupMenu(menu, point);

#endif // wxUSE_MENUS
    return true;
}

