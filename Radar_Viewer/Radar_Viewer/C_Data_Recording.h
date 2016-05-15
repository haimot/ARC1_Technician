	#ifndef C_DATA_RECORDING_H
#define C_DATA_RECORDING_H
//-----------------------------------------
//			C_Data_Recording.h
//-----------------------------------------
#include "T_Radar_Massage.h"
#include "T_Trajectories.h"

public ref class C_Data_Recording
{
	//-----------------------------------------
	//				Fields
	//-----------------------------------------
	private:
	T_Radar_Massage*		Radar_Massage;
	T_Trajectories*			Trajectories;

	public:
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	C_Data_Recording();

	//-------------------------------------------
	//		Get/Set  new data recording
	//-------------------------------------------
	void					set_Data_Recording(T_SENSOR_data SENSOR_data_Other, T_TARGETS_data TARGETS_data_Other, T_Trajectories Trajectories_Other);
	//-------------------------------------------
	//		Get/Set  Radar_Massage
	//-------------------------------------------
	T_Radar_Massage*		get_Radar_Massage();
	void					set_Radar_Massage(T_Radar_Massage* Radar_Massage_Other);
	void					set_Radar_Massage(T_SENSOR_data SENSOR_data_Other, T_TARGETS_data TARGETS_data_Other);
	//-------------------------------------------
	//		Get/Set  Trajectories
	//-------------------------------------------
	T_Trajectories*			get_Trajectories();
	void					set_Trajectories(T_Trajectories Trajectories_Other);
	//-------------------------------------------
	//				Methods
	//-------------------------------------------
	void					Add_Detection(double Polarization, double Azimuth, double Range, double Reliability);
	void					Add_Detection(T_TARGETS_data% T_TARGETS_data);

	double*					Initialize_noise_Of_Targets();

	void					Restart();
	//-------------------------------------------
	//		 Overloading Operator
	//-------------------------------------------
	void operator=(C_Data_Recording% target_other);
};
#endif

