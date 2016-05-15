
#ifndef T_SENSOR_DATA_H
#define T_SENSOR_DATA_H
//-----------------------------------------
//		Struct:		T_SENSOR_data
//-----------------------------------------
typedef struct T_SENSOR_data
{
	//-------------------------
	//			ISL						Unit:			Description:
	//-------------------------								
	double INS_YAW;						//deg			Yaw angle relative to true north
	double INS_PITCH;					//deg			Pitch angle relative to horizon
	double INS_ROLL;					//deg			Pool angle relative to horizon

	double Latitude;					//deg			Estimated position in geodetic latitude
	double Longitude;					//deg			Estimated position in geodetic longitude
	double Altitude;					//m				Estimated height above ellipsoid. (WGS84)

	double VelocityX;					//m/s			Estimated velocity in NED frame. (North)
	double VelocityY;					//m/s			Estimated velocity in NED frame. (East)
	double VelocityZ;					//m/s			Estimated velocity in NED frame. (Down)

	double AccelX;						//m/s^2			Estimated acceleration in body frame. (X-axis)
	double AccelY;						//m/s^2			Estimated acceleration in body frame. (Y-axis)
	double AccelZ;						//m/s^2			Estimated acceleration in body frame. (Z-axis)

	double AngularRateX;				//rad/s			Estimated angular rate in body frame. (X-axis)
	double AngularRateY;				//rad/s			Estimated angular rate in body frame. (Y-axis)
	double AngularRateZ;				//rad/s			Estimated angular rate in body frame. (Z-axis)
	//-------------------------
	//			INS						
	//-------------------------
	double time;						//sec			GPS time of week in seconds.
	double Health;						//              GPS & INS Health indicator

	double AttUncertainty;				//deg			Uncertainty in attitude estimate.
	double PosUncertainty;				//m				Uncertainty in position estimate.
	double VelUncertainty;				//m/s			Uncertainty in velocity estimate.
	//-------------------------
	//		Attitude					
	//-------------------------						
	double ATT_YAW;						//deg			Yaw angle 
	double ATT_PITCH;					//deg			Pitch angle 
	double ATT_ROLL;					//deg			Pool angle 
}T_SENSOR_data;
#endif