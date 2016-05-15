//-----------------------------------------
//		This is the main DLL file.
//-----------------------------------------
#include "C_Data_Recording.h"
#include <iostream>
#include <math.h>

#define  PI       3.14159265358979323846

//-------------------------------------
//			Default Constructor
//-------------------------------------
C_Data_Recording::C_Data_Recording()
{
	//-------------------------------------
	//				malloc
	//-------------------------------------
	Radar_Massage = (T_Radar_Massage*)malloc(sizeof(T_Radar_Massage));
	Trajectories = (T_Trajectories*)malloc(sizeof(T_Trajectories));
	//-------------------------------------
	//	   initialize to zero values
	//-------------------------------------
	memset(Radar_Massage, 0, sizeof(T_Radar_Massage));
	memset(Trajectories, 0, sizeof(T_Trajectories));

	Radar_Massage->TARGETS_data.Targets_number = 0;
}


//-------------------------------------------
//		Get/Set  new data recording
//-------------------------------------------
void C_Data_Recording::set_Data_Recording(T_SENSOR_data SENSOR_data_Other, T_TARGETS_data TARGETS_data_Other, T_Trajectories Trajectories_Other)
{
	//-------------------------------------------
	//			set radar message
	//-------------------------------------------
	set_Radar_Massage(SENSOR_data_Other, TARGETS_data_Other);
	//-------------------------------------------
	//			set trajectories
	//-------------------------------------------
	set_Trajectories(Trajectories_Other);
}
//-------------------------------------------
//		Get/Set  Target
//-------------------------------------------
T_Radar_Massage* C_Data_Recording::get_Radar_Massage() { return Radar_Massage; }
void C_Data_Recording::set_Radar_Massage(T_Radar_Massage* Radar_Massage_Other) 
{ 
	Radar_Massage = Radar_Massage_Other;
}
void C_Data_Recording::set_Radar_Massage(T_SENSOR_data SENSOR_data_Other, T_TARGETS_data TARGETS_data_Other)
{
	Radar_Massage->SENSOR_data = SENSOR_data_Other;
	Radar_Massage->TARGETS_data = TARGETS_data_Other;
}

T_Trajectories* C_Data_Recording::get_Trajectories() { return Trajectories; }
void C_Data_Recording::set_Trajectories(T_Trajectories Trajectories_Other)
{
	*Trajectories = Trajectories_Other;
}
//-------------------------------------------
//		Operator Overloading
//-------------------------------------------
void C_Data_Recording::operator=(C_Data_Recording% target_other)
{
	Radar_Massage = target_other.Radar_Massage;
}

void C_Data_Recording::Add_Detection(double Polarization, double Azimuth, double Range, double Reliability)
{
	//-------------------------------------------
	//		Update the Polarization of the Radar
	//-------------------------------------------
	Radar_Massage->TARGETS_data.Targets_array[(int)Radar_Massage->TARGETS_data.Targets_number].Polarization_ratio_L = Polarization;
	Radar_Massage->TARGETS_data.Targets_array[(int)Radar_Massage->TARGETS_data.Targets_number].Polarization_ratio_R = Polarization;
	//-------------------------------------------
	//		Update the Azimuth of the Radar
	//-------------------------------------------
	Radar_Massage->TARGETS_data.Targets_array[(int)Radar_Massage->TARGETS_data.Targets_number].Azimuth_H = Azimuth;
	Radar_Massage->TARGETS_data.Targets_array[(int)Radar_Massage->TARGETS_data.Targets_number].Azimuth_V = Azimuth;
	//-------------------------------------------
	//		Update the Range of the Radar
	//-------------------------------------------
	Radar_Massage->TARGETS_data.Targets_array[(int)Radar_Massage->TARGETS_data.Targets_number].Range = Range;
	//-------------------------------------------
	//		Update the Reliability of the Radar
	//-------------------------------------------
	Radar_Massage->TARGETS_data.Targets_array[(int)Radar_Massage->TARGETS_data.Targets_number].Target_reliability = Reliability;
	(int)Radar_Massage->TARGETS_data.Targets_number++;
}
void C_Data_Recording::Add_Detection(T_TARGETS_data% T_TARGETS_data)
{
	Radar_Massage->TARGETS_data = T_TARGETS_data;
}
// --------------------------------------------------
//  Initialize_noise_Of_Targets
//  Haim Otachi		1/1/2016
// 	Description:	the function initialize the Noise_Level array of target
// 	Reference: 
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
double* C_Data_Recording::Initialize_noise_Of_Targets()
{
	double* noise = new double[4];
	//-------------------------------------------
	//		fill the noise array with new data
	//-------------------------------------------
	noise[0] = 20 * log10((double)Radar_Massage->TARGETS_data.Noise_Level[0] / 32767);
	noise[1] = 20 * log10((double)Radar_Massage->TARGETS_data.Noise_Level[1] / 32767);
	noise[2] = 20 * log10((double)Radar_Massage->TARGETS_data.Noise_Level[2] / 32767);
	noise[3] = 20 * log10((double)Radar_Massage->TARGETS_data.Noise_Level[3] / 32767);

	return noise;
}

void C_Data_Recording::Restart()
{
	Radar_Massage->TARGETS_data.Targets_number = 0;
}

