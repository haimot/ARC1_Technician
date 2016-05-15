#pragma once
#include "Scope.h"

namespace ARC1_Technician
{
	Scope::Scope(void)
	{
		InitializeComponent();
	}
	Scope::~Scope()
	{
		if (components)
		{
			delete components;
		}
	}
	// --------------------------------------------------
	//  Clean_data
	//  Alon Slapak		11/1/2015
	// 	Description:	Clear visual data
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void Scope::Clear_data()
	{
		B_SCOPE_H_LEFT->Series["Single1"]->Points->Clear();
		B_SCOPE_V_LEFT->Series["Single1"]->Points->Clear();
		B_SCOPE_H_RIGHT->Series["Single1"]->Points->Clear();
		B_SCOPE_V_RIGHT->Series["Single1"]->Points->Clear();
		B_SCOPE_H_LEFT->Series["Average1"]->Points->Clear();
		B_SCOPE_V_LEFT->Series["Average1"]->Points->Clear();
		B_SCOPE_H_RIGHT->Series["Average1"]->Points->Clear();
		B_SCOPE_V_RIGHT->Series["Average1"]->Points->Clear();
		B_SCOPE_H_LEFT->Series["Single2"]->Points->Clear();
		B_SCOPE_V_LEFT->Series["Single2"]->Points->Clear();
		B_SCOPE_H_RIGHT->Series["Single2"]->Points->Clear();
		B_SCOPE_V_RIGHT->Series["Single2"]->Points->Clear();
		B_SCOPE_H_LEFT->Series["Average2"]->Points->Clear();
		B_SCOPE_V_LEFT->Series["Average2"]->Points->Clear();
		B_SCOPE_H_RIGHT->Series["Average2"]->Points->Clear();
		B_SCOPE_V_RIGHT->Series["Average2"]->Points->Clear();	
	}
	// --------------------------------------------------
	//  plot_data
	//  Alon Slapak		17/12/2014
	// 	Description:	show data on the scope
	// 	Reference:		
	//	Input Value:	Samples_buffer		: pointer to data bufer
	//					start_range			: first tic on x-axis
	//					end_range			: last tic on x-axis
	//					step_range			: step between tics
	//					Single_correction	: bias (+ in dB) for single time record
	//					Average_correction	: bias (+ in dB) for average time record
	//  Return Value:	
	// --------------------------------------------------
	void Scope::plot_data_1a(double *Samples_buffer, int start_range, int end_range, int step_range)
	{
		int			i;
		double		range;
		//-------------------------------------------
		//		Drop to scope
		//-------------------------------------------
		B_SCOPE_H_LEFT->Series["Single1"]->Points->Clear();
		B_SCOPE_V_LEFT->Series["Single1"]->Points->Clear();
		B_SCOPE_H_RIGHT->Series["Single1"]->Points->Clear();
		B_SCOPE_V_RIGHT->Series["Single1"]->Points->Clear();
		for (i = start_range; i < end_range; i++)
		{
			range = (i - start_range) * step_range;
			B_SCOPE_H_LEFT->Series["Single1"]->Points->AddXY(range, 10 * log10(Samples_buffer[0 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_V_LEFT->Series["Single1"]->Points->AddXY(range, 10 * log10(Samples_buffer[1 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_H_RIGHT->Series["Single1"]->Points->AddXY(range, 10 * log10(Samples_buffer[2 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_V_RIGHT->Series["Single1"]->Points->AddXY(range, 10 * log10(Samples_buffer[3 * TIME_RECORD_LENGTH + i]));
		}
	}
	void Scope::plot_data_1b(double *Samples_buffer, int start_range, int end_range, int step_range)
	{
		int			i;
		double		range;
		//-------------------------------------------
		//		Drop to scope
		//-------------------------------------------
		B_SCOPE_H_LEFT->Series["Average1"]->Points->Clear();
		B_SCOPE_V_LEFT->Series["Average1"]->Points->Clear();
		B_SCOPE_H_RIGHT->Series["Average1"]->Points->Clear();
		B_SCOPE_V_RIGHT->Series["Average1"]->Points->Clear();
		for (i = start_range; i < end_range; i++)
		{
			range = (i - start_range) * step_range;
			B_SCOPE_H_LEFT->Series["Average1"]->Points->AddXY(range, 10 * log10(Samples_buffer[4 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_V_LEFT->Series["Average1"]->Points->AddXY(range, 10 * log10(Samples_buffer[5 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_H_RIGHT->Series["Average1"]->Points->AddXY(range, 10 * log10(Samples_buffer[6 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_V_RIGHT->Series["Average1"]->Points->AddXY(range, 10 * log10(Samples_buffer[7 * TIME_RECORD_LENGTH + i]));
		}
	}
	void Scope::plot_data_2a(double *Samples_buffer, int start_range, int end_range, int step_range)
	{
		int			i;
		double		range;
		//-------------------------------------------
		//		Drop to scope
		//-------------------------------------------
		B_SCOPE_H_LEFT->Series["Single2"]->Points->Clear();
		B_SCOPE_V_LEFT->Series["Single2"]->Points->Clear();
		B_SCOPE_H_RIGHT->Series["Single2"]->Points->Clear();
		B_SCOPE_V_RIGHT->Series["Single2"]->Points->Clear();
		for (i = start_range; i < end_range; i++)
		{
			range = (i - start_range) * step_range;
			B_SCOPE_H_LEFT->Series["Single2"]->Points->AddXY(range, 10 * log10(Samples_buffer[0 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_V_LEFT->Series["Single2"]->Points->AddXY(range, 10 * log10(Samples_buffer[1 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_H_RIGHT->Series["Single2"]->Points->AddXY(range, 10 * log10(Samples_buffer[2 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_V_RIGHT->Series["Single2"]->Points->AddXY(range, 10 * log10(Samples_buffer[3 * TIME_RECORD_LENGTH + i]));
		}
	}
	void Scope::plot_data_2b(double *Samples_buffer, int start_range, int end_range, int step_range)
	{
		int			i;
		double		range;
		//-------------------------------------------
		//		Drop to scope
		//-------------------------------------------
		B_SCOPE_H_LEFT->Series["Average2"]->Points->Clear();
		B_SCOPE_V_LEFT->Series["Average2"]->Points->Clear();
		B_SCOPE_H_RIGHT->Series["Average2"]->Points->Clear();
		B_SCOPE_V_RIGHT->Series["Average2"]->Points->Clear();
		for (i = start_range; i < end_range; i++)
		{
			range = (i - start_range) * step_range;
			B_SCOPE_H_LEFT->Series["Average2"]->Points->AddXY(range, 10 * log10(Samples_buffer[4 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_V_LEFT->Series["Average2"]->Points->AddXY(range, 10 * log10(Samples_buffer[5 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_H_RIGHT->Series["Average2"]->Points->AddXY(range, 10 * log10(Samples_buffer[6 * TIME_RECORD_LENGTH + i]));
			B_SCOPE_V_RIGHT->Series["Average2"]->Points->AddXY(range, 10 * log10(Samples_buffer[7 * TIME_RECORD_LENGTH + i]));
		}
	}
	// --------------------------------------------------
	//  show_GPS
	//  Alon Slapak		17/12/2014
	// 	Description:	show GPS (time, long, lat, alt) data on the scope
	// 	Reference:		
	//	Input Value:	message_string		: string containing the message
	//  Return Value:	
	// --------------------------------------------------
	void Scope::show_GPS(String^ time, String^ latit, String^ longit, String^ altit)
	{
		B_SENSOR_TIME->Text = time;
		B_SENSOR_LATITUDE->Text = latit;
		B_SENSOR_LONGITUDE->Text = longit;
		B_SENSOR_ALTITUDE->Text = altit;
		//B_Scope_message->Refresh();
	}
	// --------------------------------------------------
	//  set_mode
	//  Alon Slapak		8/1/2015
	// 	Description:	Set view mode (circular Polarization, H/V polarization, ...)
	// 	Reference:		
	//	Input Value:	mode of legend
	//  Return Value:	
	// --------------------------------------------------
	void Scope::set_mode(E_LEGEND_MODE legend_mode)
	{
		switch (legend_mode)
		{
			case LEGEND_CIRCULAR:
				B_LEGEND_TX1->Text = L"TX Circular:";
				B_LEGEND_TX2->Visible = false;
				B_LEGEND_2a->Visible = false;
				B_LEGEND_2b->Visible = false;
				B_LEGEND_2c->Visible = false;
				B_LEGEND_2d->Visible = false;
				break;

			case LEGEND_HV:
				B_LEGEND_TX1->Text = L"TX H:";
				B_LEGEND_TX2->Visible = true;
				B_LEGEND_2a->Visible = true;
				B_LEGEND_2b->Visible = true;
				B_LEGEND_2c->Visible = true;
				B_LEGEND_2d->Visible = true;
				break;
		}	
	}
	// --------------------------------------------------
	//  Scope_Load
	//  Alon Slapak		11/1/2015
	// 	Description:	Set view in center of screen
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void Scope::Scope_Load(System::Object^  sender, System::EventArgs^  e)
	{
		/*this->Left = extendedDisplay.WorkingArea.Left + (extendedDisplay.Bounds.Size.Width / 2) - (this.Size.Width / 2);
		this->Top = extendedDisplay.WorkingArea.Top + (extendedDisplay.Bounds.Size.Height / 2) - (this.Size.Height / 2);*/
	}
}