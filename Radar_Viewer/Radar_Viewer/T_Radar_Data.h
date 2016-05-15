#ifndef T_RADAR_DATA_H
#define T_RADAR_DATA_H
//-----------------------------------------
//		Struct:		T_Radar_Data
//-----------------------------------------
public struct T_Radar_Data
{
	//-----------------------------------------
	//		Data of Radar
	//-----------------------------------------
	int		Radar_Speed;
	int		Radar_Max_Range;
	int		Radar_Min_Range;	// added by haim otachi at 07/01/2016 and used in 'MAP' panel tab control on the monitor
	int		Radar_FOV;
	int		Radar_Refresh_Time;
	bool	Route_New;

	float	Radar_Initial_YAW;
	float	Radar_Delta_YAW;
	float	Radar_YAW;

	double	Time_Stamp;
};
#endif




