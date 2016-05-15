#include "C_RDM.h"
#include <stdlib.h>
#include <math.h>

#define DBL_MIN         2.2250738585072014e-308 /* min positive value */

// --------------------------------------------------
//  C_RDM - Default Constructor
//  Haim Otachi     28/12/2015
// 	Description:	the function initialize the 'RDM'  structs with simple 'malloc'
// 	Reference: 
//
//  Return Value:	
// --------------------------------------------------
C_RDM::C_RDM()
{
	//-----------------------------------------
	//				Malloc 
	//-----------------------------------------
	RDM = (double*)malloc(sizeof(double));
	RDM_buffer_double = (double*)malloc(RDM_size_int16 * sizeof(double));
	//system_status = (T_SYSTEM_control_0*)malloc(RDM_size_int16 * sizeof(T_SYSTEM_control_0));
	RDM_View = gcnew PictureBox();
}
// --------------------------------------------------
//  C_RDM - Destructor
//  Haim Otachi     28/12/2015
// 	Description:	the function delete the 'RDM' structs with delete function
// 	Reference: 
//
//  Return Value:	
// --------------------------------------------------
C_RDM::~C_RDM()
{
	//-------------------------------------
	//	  delete the 'RDM' object
	//-------------------------------------
	if (RDM != NULL)
	{
		free(RDM);
		RDM = NULL;
	}
	//-------------------------------------
	//	  delete the 'RDM' object
	//-------------------------------------
	if (RDM_buffer_double != NULL)
	{
		free(RDM_buffer_double);
		RDM_buffer_double = NULL;
	}
	////-------------------------------------
	////	  delete the 'system_status' object
	////-------------------------------------
	//if (system_status != NULL)
	//{
	//	free(system_status);
	//	system_status = NULL;
	//}
}


void C_RDM::Initialize(PictureBox^	RDM_View_Other)
{
	RDM_View = RDM_View_Other;
}

double C_RDM::Update_RDM(Point% RDM_Point)
{
	double x_resolution, y_resolution;
	//-------------------------------------
	//	We take the 'Range_decimation', 'RANGE_samples' and 'Maximal_doppler' from the 'system_status' struct
	//-------------------------------------
	/*uint16_t	Range_decimation = system_status->SYSTEM_control_shadow.DET_algorithms.Range_decimation;
	uint32_t	RANGE_samples = system_status->SYSTEM_control_shadow.DET_algorithms.RANGE_samples;
	uint16_t	Maximal_doppler = system_status->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler;*/

	uint16_t	Range_decimation = 1;
	uint32_t	RANGE_samples = 1;
	uint16_t	Maximal_doppler = 1;
	//-------------------------------------
	//	find the x and y resolution
	//-------------------------------------
	x_resolution = (double)(RDM_View->Width) / (Range_decimation / RANGE_samples);
	y_resolution = (double)(RDM_View->Height) / (Maximal_doppler * 2);
	//-------------------------------------
	//	we update the x and y coordinates of Point p from resolution coordinates
	//-------------------------------------
	RDM_Point.X = (int)((double)RDM_Point.X / x_resolution);
	RDM_Point.Y = (int)((double)RDM_Point.Y / y_resolution);
	//-------------------------------------
	//	we calculate the number of raws, length of line and 'point_index'
	//-------------------------------------
	int	number_of_raws = RANGE_samples / Range_decimation;
	int line_length = number_of_raws * 4;
	int point_index = Maximal_doppler * 2 * line_length + RDM_Point.Y * line_length + RDM_Point.X * 4;
	double log_value = (double)(log10(abs(*(RDM + point_index + 0) / 32767) + abs(*(RDM + point_index + 1) / 32767) + DBL_MIN) * 20);

	return log_value;
}