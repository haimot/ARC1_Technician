#ifndef C_SCOPE_H
#define C_SCOPE_H

using namespace System;

public ref class C_Scope
{
	//-------------------------------------------
	//				Fields
	//-------------------------------------------
	double*			Samples_buffer;

	int				start_range; 
	int				end_range; 
	int				step_range;
	//-------------------------------------------
	//				Constructor
	//-------------------------------------------
	public:			C_Scope();
	//-------------------------------------------
	//				Methods
	//-------------------------------------------
	public:
	void	Clear_data(void);
	void	plot_data_1a(double *Samples_buffer, int start_range, int end_range, int step_range);
	void	plot_data_1b(double *Samples_buffer, int start_range, int end_range, int step_range);
	void	plot_data_2a(double *Samples_buffer, int start_range, int end_range, int step_range);
	void	plot_data_2b(double *Samples_buffer, int start_range, int end_range, int step_range);
	void	show_GPS(String^ time, String^ latit, String^ longit, String^ altit);
	void	set_mode(E_LEGEND_MODE legend_mode);

	void	Scope_Load(System::Object^  sender, System::EventArgs^  e);
};

#endif