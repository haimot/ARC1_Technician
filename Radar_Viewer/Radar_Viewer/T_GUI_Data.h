#ifndef T_GUI_Data_H
#define T_GUI_Data_H

#include "T_Radar_Data.h"
#include "T_Simulator_Data.h"
#include "T_Viewer_Data.h"
#include "T_General_Data.h"

//-----------------------------------------
//		Struct:		T_GUI_Status
//-----------------------------------------
typedef struct T_GUI_Data
{
	//-----------------------------------------
	//		Data of Radar struct
	//-----------------------------------------
	T_Radar_Data Radar_Data;
	//-----------------------------------------
	//		General data
	//-----------------------------------------
	T_General_Data General_Data;
	//-----------------------------------------
	//		Data of Flight Simulation
	//-----------------------------------------
	T_Simulator_Data Simulator_Data;
	//-----------------------------------------
	//		Data of Viewer
	//-----------------------------------------
	T_Viewer_Data Viewer_Data;

} T_GUI_Status;
#endif




