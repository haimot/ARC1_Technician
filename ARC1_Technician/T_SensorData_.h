#ifndef _T_SENSOR_DATA__H
#define _T_SENSOR_DATA__H
//-------------------------------------------
//		Struct:		T_RecyclingFifo_
//-------------------------------------------
typedef struct T_SensorData_
{
	double		vX;
	double		vY;
	double		vZ;

	double		v;
	double		deltaZ;

	double		acX;
	double		acY;
	double		acZ;
} T_SensorData_;
#endif