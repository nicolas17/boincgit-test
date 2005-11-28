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
#pragma implementation "ViewStatistics.h"
#endif

#include "stdwx.h"
#include "BOINCGUIApp.h"
#include "MainDocument.h"
#include "BOINCTaskCtrl.h"
#include "BOINCListCtrl.h"
#include "ViewStatistics.h"
#include "Events.h"
#include "util.h"


BEGIN_EVENT_TABLE (CPaintStatistics, wxPanel)
    EVT_PAINT(CPaintStatistics::OnPaint)
    EVT_SIZE(CPaintStatistics::OnSize)
END_EVENT_TABLE ()

CPaintStatistics::CPaintStatistics() {
	m_SelectedStatistic=0;
	heading=_("User Total");
	m_ModeViewStatistic=0;
	m_NextProjectStatistic=0;
}

CPaintStatistics::CPaintStatistics(
	wxWindow* parent, wxWindowID id, const wxPoint& pos,
	const wxSize& size, long style, const wxString& name
): wxPanel(parent, id, pos, size, style, name)
{
	m_SelectedStatistic=0;
	heading=_("User Total");
	m_ModeViewStatistic=0;
	m_NextProjectStatistic=0;
}

	void DrawGraph(wxPaintDC &dc, std::vector<PROJECT*>::const_iterator &i, wxCoord rectangle_x_start, wxCoord rectangle_x_end, wxCoord rectangle_y_start, wxCoord rectangle_y_end, wxColour grafColour, wxInt32 m_SelectedStatistic, double max_val_y, double min_val_y, double max_val_x, double min_val_x) {
		const double yscale=(rectangle_y_end-rectangle_y_start-2)/(max_val_y-min_val_y);
		const double xscale=(rectangle_x_end-rectangle_x_start-2)/(max_val_x-min_val_x);

		dc.SetPen(wxPen(grafColour , 2 , wxSOLID));

		wxCoord last_x=rectangle_x_start, last_y=0, xpos=rectangle_x_start, ypos=0;

		for (std::vector<DAILY_STATS>::const_iterator j=(*i)->statistics.begin(); j!=(*i)->statistics.end(); ++j) {

			ypos=(wxCoord)(rectangle_y_end - 1 - (yscale * (double)(j->user_total_credit-min_val_y)));
			xpos=(wxCoord)(rectangle_x_start + 1 + (xscale * (j->day-min_val_x)));

			switch (m_SelectedStatistic){ 
			case 0:{
				ypos=(wxCoord)(rectangle_y_end - 1 - (yscale * (double)(j->user_total_credit-min_val_y)));
				break;}
			case 1:{
				ypos=(wxCoord)(rectangle_y_end - 1 - (yscale * (double)(j->user_expavg_credit-min_val_y)));
				break;}
			case 2:{
				ypos=(wxCoord)(rectangle_y_end - 1 - (yscale * (double)(j->host_total_credit-min_val_y)));
				break;}
			case 3:{
				ypos=(wxCoord)(rectangle_y_end - 1 - (yscale * (double)(j->host_expavg_credit-min_val_y)));
				break;}
			}
			if (last_y!=0) {
				dc.DrawLine(xpos,ypos,last_x,last_y);
			}

			last_x=xpos;
			last_y=ypos;
		}
	
	}
	void DrawAxis(wxPaintDC &dc, wxCoord x_start, wxCoord x_end, wxCoord y_start, wxCoord y_end, double max_val_y, double min_val_y, double max_val_x, double min_val_x, wxString head_name, wxCoord &rectangle_x_start, wxCoord &rectangle_x_end, wxCoord &rectangle_y_start, wxCoord &rectangle_y_end) {
			dc.SetBrush(*wxLIGHT_GREY_BRUSH);
			dc.SetPen(wxPen(wxColour (0 , 0 , 0) , 1 , wxSOLID));

			wxCoord x, y, w_temp, h_temp, des_temp, lead_temp;
			dc.GetTextExtent(head_name, &w_temp, &h_temp, &des_temp, &lead_temp);

			x=x_start+((x_end-x_start)/2)-(w_temp/2);
			y=y_start;
			dc.DrawText (head_name, x, y);
			
			dc.GetTextExtent(wxString::Format(" %.1f", max_val_y), &w_temp, &h_temp, &des_temp, &lead_temp);

			rectangle_x_start=x_start+w_temp+2;
			rectangle_y_start=y_start+h_temp+h_temp+2;
			rectangle_x_end=x_end-2;
			rectangle_y_end=y_end-h_temp-2;

			wxDateTime dtTemp1;
			wxString strBuffer1;
			dtTemp1.Set((time_t)max_val_x);
			strBuffer1=dtTemp1.Format("  %d-%b-%y");
			dc.GetTextExtent(strBuffer1, &w_temp, &h_temp, &des_temp, &lead_temp);
			rectangle_x_end-=w_temp/2;
			if (rectangle_x_start<(x_start+(w_temp/2)+2)) rectangle_x_start=(x_start+(w_temp/2)+2);

			//Draw val
			dc.GetTextExtent(wxString::Format("%.1f", max_val_y), &w_temp, &h_temp, &des_temp, &lead_temp);
			dc.DrawRectangle(rectangle_x_start,rectangle_y_start,rectangle_x_end-rectangle_x_start,rectangle_y_end-rectangle_y_start);	
			dc.DrawText(wxString::Format("%.1f", max_val_y),rectangle_x_start-w_temp-2,rectangle_y_start-h_temp);

			dc.GetTextExtent(wxString::Format("%.1f", min_val_y), &w_temp, &h_temp, &des_temp, &lead_temp);
			dc.DrawText(wxString::Format("%.1f", min_val_y),rectangle_x_start-w_temp-2,rectangle_y_end-h_temp);
			
			int d_oy_count=1;
			d_oy_count=(int)((rectangle_y_end-rectangle_y_start)/(1.2*h_temp));
			if (d_oy_count>5) d_oy_count=5;
			if (d_oy_count<1) d_oy_count=1;
			
			double d_oy=(rectangle_y_end-rectangle_y_start)/d_oy_count;
			double d_oy_val=(max_val_y-min_val_y)/d_oy_count;
			for (double ny=1; ny<d_oy_count;ny+=1){
				dc.GetTextExtent(wxString::Format("%.1f", min_val_y+ny*d_oy_val), &w_temp, &h_temp, &des_temp, &lead_temp);
				dc.DrawText(wxString::Format("%.1f", min_val_y+ny*d_oy_val),rectangle_x_start-w_temp-2,(wxCoord)(rectangle_y_end-ny*d_oy)-h_temp);
				dc.SetPen(wxPen(wxColour (210 , 210 , 210) , 1 , wxSOLID));
				dc.DrawLine(rectangle_x_start+1,(wxCoord)(rectangle_y_end-ny*d_oy),rectangle_x_end-1,(wxCoord)(rectangle_y_end-ny*d_oy));
			}

			//Draw day numbers and lines marking the days
			dtTemp1.Set((time_t)max_val_x);
			strBuffer1=dtTemp1.Format("%d-%b-%y");
			dc.GetTextExtent(strBuffer1, &w_temp, &h_temp, &des_temp, &lead_temp);
			dc.DrawText(strBuffer1, rectangle_x_end-(w_temp/2), rectangle_y_end);
			dtTemp1.Set((time_t)min_val_x);
			strBuffer1=dtTemp1.Format("%d-%b-%y");
			dc.GetTextExtent(strBuffer1, &w_temp, &h_temp, &des_temp, &lead_temp);
			dc.DrawText(strBuffer1, rectangle_x_start-(w_temp/2), rectangle_y_end);

			int d_ox_count=1;
			d_ox_count=(int)((rectangle_x_end-rectangle_x_start)/(1.2*w_temp));
			if (d_ox_count>5) d_ox_count=5;
			if (d_ox_count<1) d_ox_count=1;
			
			double d_ox=(rectangle_x_end-rectangle_x_start)/d_ox_count;
			double d_ox_val=(max_val_x-min_val_x)/d_ox_count;
			for (double nx=1; nx<d_ox_count;nx+=1){
				dtTemp1.Set((time_t)(min_val_x+nx*d_ox_val));
				strBuffer1=dtTemp1.Format("%d-%b-%y");
				dc.GetTextExtent(strBuffer1, &w_temp, &h_temp, &des_temp, &lead_temp);
				dc.DrawText(strBuffer1, (wxCoord)(rectangle_x_start-(w_temp/2)+(nx*d_ox)), rectangle_y_end);
				
				dc.SetPen(wxPen(wxColour (210 , 210 , 210) , 1 , wxSOLID));
				dc.DrawLine((wxCoord)(rectangle_x_start+(nx*d_ox)),rectangle_y_start+1,(wxCoord)(rectangle_x_start+(nx*d_ox)),rectangle_y_end-1);
			}
	}

void CPaintStatistics::OnPaint(wxPaintEvent& WXUNUSED(event)) {

	//Init global
    CMainDocument* pDoc      = wxGetApp().GetDocument();

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

	PROJECTS *proj=&(pDoc->statistics_status);
	wxASSERT(proj);

	//Init drawing
	wxPaintDC dc (this);

    wxCoord width = 0, height = 0, heading_height=0;
    wxCoord rectangle_x_start=0, rectangle_y_start=0;
    wxCoord rectangle_x_end=0, rectangle_y_end=0;

	GetClientSize(&width, &height);

	dc.SetBackground(*wxWHITE_BRUSH);

	dc.SetTextForeground (GetForegroundColour ());
	dc.SetTextBackground (GetBackgroundColour ());

	wxFont heading_font(*wxSWISS_FONT);
	heading_font.SetWeight(wxBOLD);

	dc.SetFont(*wxSWISS_FONT);
	

	//Start drawing
	dc.BeginDrawing();

	dc.Clear();
	
	if ((m_ModeViewStatistic<0)||(m_ModeViewStatistic>2)) m_ModeViewStatistic=0;
	switch (m_ModeViewStatistic){
	case 0:{
		//Draw heading
		{
		dc.SetFont(heading_font);
		wxCoord w_temp, h_temp, des_temp, lead_temp;
		dc.GetTextExtent(heading, &w_temp, &h_temp, &des_temp, &lead_temp);
		heading_height=h_temp+lead_temp+5;
		dc.DrawText (heading, ((width/2)-(w_temp/2)), lead_temp+5);
		dc.SetFont(*wxSWISS_FONT);
		}

		//Number of Projects with statistics
		wxInt32 nb_proj=0;
		for (std::vector<PROJECT*>::const_iterator i=proj->projects.begin(); i!=proj->projects.end(); ++i) {
		if ((*i)->statistics.size()>1) ++nb_proj;
		}
		if (nb_proj==0) return;

		//How many rows/colums?
		wxInt32 nb_proj_row=0, nb_proj_col=0;
		if (nb_proj<4) {
			nb_proj_col=1;
			nb_proj_row=nb_proj;
		} else {
			nb_proj_col=2;
			nb_proj_row=(wxInt32)ceil(static_cast<double>(nb_proj/static_cast<double>(nb_proj_col)));
		}

		wxInt32 col=1, row=1; //Used to identify the actual row/col
	
		const double x_fac=width/nb_proj_col;
		const double y_fac=(height-heading_height)/nb_proj_row;
	
		wxInt32 count=-1;
	
		for (std::vector<PROJECT*>::const_iterator i=proj->projects.begin();i!=proj->projects.end(); ++i) {
			++count;

			//No statistics
			if ((*i)->statistics.size()<2) continue;

			//Find minimum/maximum value
			double min_val_y=10e32, max_val_y=0;
			double min_val_x=0, max_val_x=0;
			for (std::vector<DAILY_STATS>::const_iterator j=(*i)->statistics.begin(); j!=(*i)->statistics.end();++j) {
				if (0==min_val_x) min_val_x=j->day;
				max_val_x=j->day;
            
				switch (m_SelectedStatistic){
				case 0:{
					if (j->user_total_credit>max_val_y) max_val_y=j->user_total_credit;
					if (j->user_total_credit<min_val_y) min_val_y=j->user_total_credit;
					break;}
				case 1:{
					if (j->user_expavg_credit>max_val_y) max_val_y=j->user_expavg_credit;
					if (j->user_expavg_credit<min_val_y) min_val_y=j->user_expavg_credit;
					break;}
				case 2:{
					if (j->host_total_credit>max_val_y) max_val_y=j->host_total_credit;
					if (j->host_total_credit<min_val_y) min_val_y=j->host_total_credit;
					break;}
				case 3:{
					if (j->host_expavg_credit>max_val_y) max_val_y=j->host_expavg_credit;
					if (j->host_expavg_credit<min_val_y) min_val_y=j->host_expavg_credit;
					break;}
				}
			}
			min_val_y=min_val_y*0.999999-1;
			max_val_y=max_val_y*1.000001+1;
			if (min_val_y<0) min_val_y=0;
			if (max_val_y==min_val_y) max_val_y+=3;

			min_val_x=min_val_x*0.999999-1;
			max_val_x=max_val_x*1.000001+1;
			if (min_val_x<0) min_val_x=0;
			if (max_val_x==min_val_x) max_val_x+=3;

			//Where do we draw in?
			wxCoord x_start=0, y_start=0, x_end=0, y_end=0;
			x_start=(wxCoord)(x_fac*(double)(col-1));
			x_end=(wxCoord)(x_fac*((double)col));
			y_start=(wxCoord)(y_fac*(double)(row-1)+heading_height);
			y_end=(wxCoord)(y_fac*(double)row+heading_height);
		
			///Draw scale Draw Project name
			PROJECT* statistic = wxGetApp().GetDocument()->statistic(count);
			PROJECT* state_project = NULL;
			wxString head_name;
			std::string project_name;
			if (statistic) {
				state_project = pDoc->state.lookup_project(statistic->master_url);
				if (state_project) {
				state_project->get_name(project_name);
				head_name = wxString(project_name.c_str());
				}
			}
			DrawAxis(dc, x_start, x_end, y_start, y_end, max_val_y, min_val_y,max_val_x, min_val_x, head_name, rectangle_x_start, rectangle_x_end, rectangle_y_start, rectangle_y_end);

			///Draw graph
			wxColour grafColour=wxColour(0,0,0);
			switch (m_SelectedStatistic){
			case 0:{
				grafColour=wxColour(255,0,0);
				break;}
			case 1:{
				grafColour=wxColour(0,150,0);
				break;}
			case 2:{
				grafColour=wxColour(0,0,255);
				break;}
			case 3:{
				grafColour=wxColour(0,0,0);
				break;}
			}
			
			DrawGraph(dc, i, rectangle_x_start, rectangle_x_end, rectangle_y_start, rectangle_y_end, grafColour, m_SelectedStatistic,  max_val_y, min_val_y, max_val_x, min_val_x);
			//Change row/col
			if (col==nb_proj_col) {
				col=1;
				++row;
			} else {
				++col;
			}
		}
		break;
		}
	case 1:{
		//Draw heading
		{
		dc.SetFont(heading_font);
		wxCoord w_temp, h_temp, des_temp, lead_temp;
		dc.GetTextExtent(heading, &w_temp, &h_temp, &des_temp, &lead_temp);
		heading_height=h_temp+lead_temp+5;
		dc.DrawText (heading, ((width/2)-(w_temp/2)), lead_temp+5);
		dc.SetFont(*wxSWISS_FONT);
		}
	
		//Number of Projects with statistics
		wxInt32 nb_proj=0;
		for (std::vector<PROJECT*>::const_iterator i=proj->projects.begin(); i!=proj->projects.end(); ++i) {
		if ((*i)->statistics.size()>1) ++nb_proj;
		}
		if (nb_proj==0) break;///return;
		
		if ((m_NextProjectStatistic<0)||(m_NextProjectStatistic>=nb_proj)) m_NextProjectStatistic=0;
		
		wxInt32 count=-1;
	
		for (std::vector<PROJECT*>::const_iterator i=proj->projects.begin();i!=proj->projects.end(); ++i) {
			++count;
			//No statistics
			if ((*i)->statistics.size()<2) continue;
			if (count!=m_NextProjectStatistic) continue;

			//Find minimum/maximum value
			double min_val_y=10e32, max_val_y=0;
			double min_val_x=0, max_val_x=0;
			for (std::vector<DAILY_STATS>::const_iterator j=(*i)->statistics.begin(); j!=(*i)->statistics.end();++j) {
				if (0==min_val_x) min_val_x=j->day;
				max_val_x=j->day;
            
				switch (m_SelectedStatistic){
				case 0:{
					if (j->user_total_credit>max_val_y) max_val_y=j->user_total_credit;
					if (j->user_total_credit<min_val_y) min_val_y=j->user_total_credit;
					break;}
				case 1:{
					if (j->user_expavg_credit>max_val_y) max_val_y=j->user_expavg_credit;
					if (j->user_expavg_credit<min_val_y) min_val_y=j->user_expavg_credit;
					break;}
				case 2:{
					if (j->host_total_credit>max_val_y) max_val_y=j->host_total_credit;
					if (j->host_total_credit<min_val_y) min_val_y=j->host_total_credit;
					break;}
				case 3:{
					if (j->host_expavg_credit>max_val_y) max_val_y=j->host_expavg_credit;
					if (j->host_expavg_credit<min_val_y) min_val_y=j->host_expavg_credit;
					break;}
				}
			}
			min_val_y=min_val_y*0.999999-1;
			max_val_y=max_val_y*1.000001+1;
			if (min_val_y<0) min_val_y=0;
			if (max_val_y==min_val_y) max_val_y+=3;

			min_val_x=min_val_x*0.999999-1;
			max_val_x=max_val_x*1.000001+1;
			if (min_val_x<0) min_val_x=0;
			if (max_val_x==min_val_x) max_val_x+=3;

			//Where do we draw in?
			wxCoord x_start=0, y_start=0, x_end=0, y_end=0;
			x_start=(wxCoord)(0);
			x_end=(wxCoord)(width);
			y_start=(wxCoord)(heading_height);
			y_end=(wxCoord)(height);
		
			///Draw scale Draw Project name
			PROJECT* statistic = wxGetApp().GetDocument()->statistic(count);
			PROJECT* state_project = NULL;
			wxString head_name;
			std::string project_name;
			if (statistic) {
				state_project = pDoc->state.lookup_project(statistic->master_url);
				if (state_project) {
				state_project->get_name(project_name);
				head_name = wxString(project_name.c_str());
				}
			}
			DrawAxis(dc, x_start, x_end, y_start, y_end, max_val_y, min_val_y,max_val_x, min_val_x, head_name, rectangle_x_start, rectangle_x_end, rectangle_y_start, rectangle_y_end);

			///Draw graph
			wxColour grafColour=wxColour(0,0,0);
			switch (m_SelectedStatistic){
			case 0:{
				grafColour=wxColour(255,0,0);
				break;}
			case 1:{
				grafColour=wxColour(0,150,0);
				break;}
			case 2:{
				grafColour=wxColour(0,0,255);
				break;}
			case 3:{
				grafColour=wxColour(0,0,0);
				break;}
			}
			DrawGraph(dc, i, rectangle_x_start, rectangle_x_end, rectangle_y_start, rectangle_y_end, grafColour, m_SelectedStatistic,  max_val_y, min_val_y, max_val_x, min_val_x);
			break;
		}
		break;
		}
	case 2:{
		//Number of Projects with statistics
		wxInt32 nb_proj=0;
		for (std::vector<PROJECT*>::const_iterator i=proj->projects.begin(); i!=proj->projects.end(); ++i) {
		if ((*i)->statistics.size()>1) ++nb_proj;
		}
		if (nb_proj==0) break;///return;
		
		if ((m_NextProjectStatistic<0)||(m_NextProjectStatistic>=nb_proj)) m_NextProjectStatistic=0;
		
		wxInt32 count=-1;
	
		for (std::vector<PROJECT*>::const_iterator i=proj->projects.begin();i!=proj->projects.end(); ++i) {
			++count;
			//No statistics
			if ((*i)->statistics.size()<2) continue;
			if (count!=m_NextProjectStatistic) continue;

			for (int m_SelectedStatistic_1=0; m_SelectedStatistic_1<=3;++m_SelectedStatistic_1) {
			//Find minimum/maximum value
			double min_val_y=10e32, max_val_y=0;
			double min_val_x=0, max_val_x=0;
			for (std::vector<DAILY_STATS>::const_iterator j=(*i)->statistics.begin(); j!=(*i)->statistics.end();++j) {
				if (0==min_val_x) min_val_x=j->day;
				max_val_x=j->day;
            
				switch (m_SelectedStatistic_1){
				case 0:{
					if (j->user_total_credit>max_val_y) max_val_y=j->user_total_credit;
					if (j->user_total_credit<min_val_y) min_val_y=j->user_total_credit;
					break;}
				case 1:{
					if (j->user_expavg_credit>max_val_y) max_val_y=j->user_expavg_credit;
					if (j->user_expavg_credit<min_val_y) min_val_y=j->user_expavg_credit;
					break;}
				case 2:{
					if (j->host_total_credit>max_val_y) max_val_y=j->host_total_credit;
					if (j->host_total_credit<min_val_y) min_val_y=j->host_total_credit;
					break;}
				case 3:{
					if (j->host_expavg_credit>max_val_y) max_val_y=j->host_expavg_credit;
					if (j->host_expavg_credit<min_val_y) min_val_y=j->host_expavg_credit;
					break;}
				}
			}
			min_val_y=min_val_y*0.999999-1;
			max_val_y=max_val_y*1.000001+1;
			if (min_val_y<0) min_val_y=0;
			if (max_val_y==min_val_y) max_val_y+=3;

			min_val_x=min_val_x*0.999999-1;
			max_val_x=max_val_x*1.000001+1;
			if (min_val_x<0) min_val_x=0;
			if (max_val_x==min_val_x) max_val_x+=3;

			//Draw heading
			PROJECT* statistic = wxGetApp().GetDocument()->statistic(count);
			PROJECT* state_project = NULL;
			wxString head_name;
			std::string project_name;
			if (statistic) {
				state_project = pDoc->state.lookup_project(statistic->master_url);
				if (state_project) {
				state_project->get_name(project_name);
				head_name = wxString(project_name.c_str());
				}
			}
			//Draw heading
			{
			dc.SetFont(heading_font);
			wxCoord w_temp, h_temp, des_temp, lead_temp;
			dc.GetTextExtent(head_name, &w_temp, &h_temp, &des_temp, &lead_temp);
			heading_height=h_temp+lead_temp+5;
			dc.DrawText (head_name, ((width/2)-(w_temp/2)), lead_temp+5);
			dc.SetFont(*wxSWISS_FONT);
			}
			
			//Where do we draw in?
			wxCoord x_start=0, y_start=0, x_end=0, y_end=0;
			switch (m_SelectedStatistic_1){
			case 0:{
				x_start=(wxCoord)(0);
				x_end=(wxCoord)(width/2.0);
				y_start=(wxCoord)(heading_height);
				y_end=(wxCoord)(heading_height+(height-heading_height)/2.0);
				head_name=_("User Total");
				break;}
			case 1:{
				x_start=(wxCoord)(width/2.0);
				x_end=(wxCoord)(width);
				y_start=(wxCoord)(heading_height);
				y_end=(wxCoord)(heading_height+(height-heading_height)/2.0);
				head_name=_("User Average");
				break;}
			case 2:{
				x_start=(wxCoord)(0);
				x_end=(wxCoord)(width/2.0);
				y_start=(wxCoord)(heading_height+(height-heading_height)/2.0);
				y_end=(wxCoord)(height);
				head_name=_("Host Total");
				break;}
			case 3:{
				x_start=(wxCoord)(width/2.0);
				x_end=(wxCoord)(width);
				y_start=(wxCoord)(heading_height+(height-heading_height)/2.0);
				y_end=(wxCoord)(height);
				head_name=_("Host Average");
				break;}
			}
		
			///Draw scale Draw Project name
			DrawAxis(dc, x_start, x_end, y_start, y_end, max_val_y, min_val_y,max_val_x, min_val_x, head_name, rectangle_x_start, rectangle_x_end, rectangle_y_start, rectangle_y_end);

			///Draw graph
			wxColour grafColour=wxColour(0,0,0);
			switch (m_SelectedStatistic_1){
			case 0:{
				grafColour=wxColour(255,0,0);
				break;}
			case 1:{
				grafColour=wxColour(0,150,0);
				break;}
			case 2:{
				grafColour=wxColour(0,0,255);
				break;}
			case 3:{
				grafColour=wxColour(0,0,0);
				break;}
			}
			DrawGraph(dc, i, rectangle_x_start, rectangle_x_end, rectangle_y_start, rectangle_y_end, grafColour, m_SelectedStatistic_1,  max_val_y, min_val_y, max_val_x, min_val_x);
			}
			break;
		}
		break;
		}
	default:{
		m_ModeViewStatistic=0;
		break;
		}
	}
	dc.EndDrawing();
}

void CPaintStatistics::OnSize(wxSizeEvent& event) {
    Refresh(TRUE, NULL);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(CViewStatistics, CBOINCBaseView)

BEGIN_EVENT_TABLE (CViewStatistics, CBOINCBaseView)
    EVT_BUTTON(ID_TASK_STATISTICS_USERTOTAL, CViewStatistics::OnStatisticsUserTotal)
    EVT_BUTTON(ID_TASK_STATISTICS_USERAVERAGE, CViewStatistics::OnStatisticsUserAverage)
    EVT_BUTTON(ID_TASK_STATISTICS_HOSTTOTAL, CViewStatistics::OnStatisticsHostTotal)
    EVT_BUTTON(ID_TASK_STATISTICS_HOSTAVERAGE, CViewStatistics::OnStatisticsHostAverage)
    EVT_BUTTON(ID_TASK_STATISTICS_MODEVIEW, CViewStatistics::OnStatisticsModeView)
    EVT_BUTTON(ID_TASK_STATISTICS_NEXTPROJECT, CViewStatistics::OnStatisticsNextProject)
    EVT_LIST_ITEM_SELECTED(ID_LIST_STATISTICSVIEW, CViewStatistics::OnListSelected)
    EVT_LIST_ITEM_DESELECTED(ID_LIST_STATISTICSVIEW, CViewStatistics::OnListDeselected)
END_EVENT_TABLE ()


CViewStatistics::CViewStatistics()
{}


CViewStatistics::CViewStatistics(wxNotebook* pNotebook) :
    CBOINCBaseView(pNotebook) 
{
	CTaskItemGroup* pGroup = NULL;
	CTaskItem*      pItem = NULL;

    //
    // Setup View
    //
    wxFlexGridSizer* itemFlexGridSizer = new wxFlexGridSizer(2, 0, 0);
    wxASSERT(itemFlexGridSizer);

    itemFlexGridSizer->AddGrowableRow(0);
    itemFlexGridSizer->AddGrowableCol(1);
    
    m_pTaskPane = new CBOINCTaskCtrl(this, ID_TASK_STATISTICSVIEW, DEFAULT_TASK_FLAGS);
    wxASSERT(m_pTaskPane);

	m_PaintStatistics = new CPaintStatistics(this, ID_LIST_STATISTICSVIEW, wxDefaultPosition, wxSize(-1, -1), 0);
	wxASSERT(m_PaintStatistics);

    itemFlexGridSizer->Add(m_pTaskPane, 1, wxGROW|wxALL, 1);
    itemFlexGridSizer->Add(m_PaintStatistics, 1, wxGROW|wxALL, 1);

    SetSizer(itemFlexGridSizer);

    Layout();


	pGroup = new CTaskItemGroup( _("Tasks") );
	m_TaskGroups.push_back( pGroup );

	pItem = new CTaskItem(
        _("Show user total"),
        wxT(""),
        ID_TASK_STATISTICS_USERTOTAL 
    );
    pGroup->m_Tasks.push_back( pItem );

	pItem = new CTaskItem(
        _("Show user average"),
        wxT(""),
        ID_TASK_STATISTICS_USERAVERAGE 
    );
    pGroup->m_Tasks.push_back( pItem );

	pItem = new CTaskItem(
        _("Show host total"),
        wxT(""),
        ID_TASK_STATISTICS_HOSTTOTAL 
    );
    pGroup->m_Tasks.push_back( pItem );

	pItem = new CTaskItem(
        _("Show host average"),
        wxT(""),
        ID_TASK_STATISTICS_HOSTAVERAGE 
    );
    pGroup->m_Tasks.push_back( pItem );

	pItem = new CTaskItem(
        _("Mode view"),
        wxT(""),
        ID_TASK_STATISTICS_MODEVIEW 
    );
    pGroup->m_Tasks.push_back( pItem );

	pItem = new CTaskItem(
        _("Next project"),
        wxT(""),
        ID_TASK_STATISTICS_NEXTPROJECT 
    );
    pGroup->m_Tasks.push_back( pItem );
        

    // Create Task Pane Items
    m_pTaskPane->UpdateControls();

    UpdateSelection();
}

CViewStatistics::~CViewStatistics() {
    EmptyTasks();
}


wxString& CViewStatistics::GetViewName() {
    static wxString strViewName(_("Statistics"));
    return strViewName;
}


void CViewStatistics::OnStatisticsUserTotal( wxCommandEvent& WXUNUSED(event) ) {
    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsUserTotal - Function Begin"));

    CMainFrame* pFrame      = wxGetApp().GetFrame();

    wxASSERT(pFrame);
    wxASSERT(wxDynamicCast(pFrame, CMainFrame));

    pFrame->UpdateStatusText(_("Updating charts..."));
	m_PaintStatistics->heading=_("User Total");
	m_PaintStatistics->m_SelectedStatistic=0;
    pFrame->UpdateStatusText(wxT(""));

    UpdateSelection();
    pFrame->FireRefreshView();

    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsUserTotal - Function End"));
}


void CViewStatistics::OnStatisticsUserAverage( wxCommandEvent& WXUNUSED(event) ) {
    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsUserAverage - Function Begin"));

    CMainFrame* pFrame      = wxGetApp().GetFrame();

    wxASSERT(pFrame);
    wxASSERT(wxDynamicCast(pFrame, CMainFrame));

    pFrame->UpdateStatusText(_("Updating charts..."));
	m_PaintStatistics->heading=_("User Average");
	m_PaintStatistics->m_SelectedStatistic=1;
    pFrame->UpdateStatusText(wxT(""));

    UpdateSelection();
    pFrame->FireRefreshView();

    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsUserAverage - Function End"));
}


void CViewStatistics::OnStatisticsHostTotal( wxCommandEvent& WXUNUSED(event) ) {
    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsHostTotal - Function Begin"));

    CMainFrame* pFrame      = wxGetApp().GetFrame();

    wxASSERT(pFrame);
    wxASSERT(wxDynamicCast(pFrame, CMainFrame));

    pFrame->UpdateStatusText(_("Updating charts..."));
	m_PaintStatistics->heading=_("Host Total");
	m_PaintStatistics->m_SelectedStatistic=2;
    pFrame->UpdateStatusText(wxT(""));

    UpdateSelection();
    pFrame->FireRefreshView();

    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsHostTotal - Function End"));
}


void CViewStatistics::OnStatisticsHostAverage( wxCommandEvent& WXUNUSED(event) ) {
    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsHostAverage - Function Begin"));

    CMainFrame* pFrame      = wxGetApp().GetFrame();

    wxASSERT(pFrame);
    wxASSERT(wxDynamicCast(pFrame, CMainFrame));

    pFrame->UpdateStatusText(_("Updating charts..."));
	m_PaintStatistics->heading=_("Host Average");
	m_PaintStatistics->m_SelectedStatistic=3;
    pFrame->UpdateStatusText(wxT(""));

    UpdateSelection();
    pFrame->FireRefreshView();

    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsHostAverage - Function End"));
}

void CViewStatistics::OnStatisticsModeView( wxCommandEvent& WXUNUSED(event) ) {
    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsModeView - Function Begin"));

    CMainFrame* pFrame      = wxGetApp().GetFrame();

    wxASSERT(pFrame);
    wxASSERT(wxDynamicCast(pFrame, CMainFrame));

    pFrame->UpdateStatusText(_("Updating charts..."));
	m_PaintStatistics->m_ModeViewStatistic++;
    pFrame->UpdateStatusText(wxT(""));

    UpdateSelection();
    pFrame->FireRefreshView();

    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsModeView - Function End"));
}

void CViewStatistics::OnStatisticsNextProject( wxCommandEvent& WXUNUSED(event) ) {
    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsNextProject - Function Begin"));

    CMainFrame* pFrame      = wxGetApp().GetFrame();

    wxASSERT(pFrame);
    wxASSERT(wxDynamicCast(pFrame, CMainFrame));

    pFrame->UpdateStatusText(_("Updating charts..."));
	m_PaintStatistics->m_NextProjectStatistic++;
    pFrame->UpdateStatusText(wxT(""));

    UpdateSelection();
    pFrame->FireRefreshView();

    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::OnStatisticsNextProject - Function End"));
}


bool CViewStatistics::OnSaveState(wxConfigBase* pConfig) {
    bool bReturnValue = true;

    wxASSERT(pConfig);
    wxASSERT(m_pTaskPane);

    if (!m_pTaskPane->OnSaveState(pConfig)) {
        bReturnValue = false;
    }

    return bReturnValue;
}


bool CViewStatistics::OnRestoreState(wxConfigBase* pConfig) {
    wxASSERT(pConfig);
    wxASSERT(m_pTaskPane);

    if (!m_pTaskPane->OnRestoreState(pConfig)) {
        return false;
    }

    return true;
}


void CViewStatistics::OnListRender( wxTimerEvent& WXUNUSED(event) ) {
    CMainDocument* pDoc      = wxGetApp().GetDocument();

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

	if (pDoc->GetStatisticsCount()) {
		m_PaintStatistics->Refresh();
	}
}


void CViewStatistics::UpdateSelection() {
    CBOINCBaseView::UpdateSelection();
}


const char *BOINC_RCSID_7aadb93333 = "$Id$";
