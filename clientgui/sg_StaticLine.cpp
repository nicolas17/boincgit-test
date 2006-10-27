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

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "sg_StaticLine.h"
#endif

#include "stdwx.h"
#include "sg_StaticLine.h" 


BEGIN_EVENT_TABLE(CStaticLine, wxWindow) 
        EVT_PAINT(CStaticLine::OnPaint) 
END_EVENT_TABLE() 


CStaticLine::CStaticLine(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : 
    wxPanel(parent, id, pos, size, style, name) 
{ 
	m_lineCol = wxColour(255,0,255);
}


void CStaticLine::SetLineColor(wxColour col) {
	m_lineCol = col;
}


void CStaticLine::OnPaint(wxPaintEvent& WXUNUSED(event)) { 
    wxPaintDC dc(this); 
    wxPen pen = wxPen(m_lineCol);
    pen.SetWidth(1);
    dc.SetPen(pen);
    dc.DrawLine(0, 0, GetSize().GetWidth(), 0); 
} 
