#ifndef T_RADAR_MESSAGE_H
#define T_RADAR_MESSAGE_H
//-----------------------------------------
//		Struct:		Target
//-----------------------------------------
#include "T_TARGETS_data.h"
#include "T_SENSOR_data.h"
#include "T_Calibrator.h"
#include "T_Trajectories.h"

typedef struct T_Radar_Massage
{
	T_SENSOR_data			SENSOR_data;
	T_Calibrator			Calibrator;
	T_TARGETS_data			TARGETS_data;
	//T_Trajectories			Trajectories;
}T_Radar_Massage;
#endif