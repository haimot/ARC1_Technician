#ifndef T_GENERAL_DATA_H
#define T_GENERAL_DATA_H

//-----------------------------------------
//		Struct:		T_General_Data
//-----------------------------------------
typedef struct T_General_Data
{
	int			Variance_Position_Wires;
	int			False_Alarm_Rate;
	int			Screen_Width;
	bool		Show_Detections;
	bool		Show_Trajectories;
	//bool		show_noice_route_of_radar;
	int			Max_Error_Range_Meter;
	int			Reliability_Threshold;
	int			Wire_Segment_Length_Meter;
} T_General_Data;

#endif

