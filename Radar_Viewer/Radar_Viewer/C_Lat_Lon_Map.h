#ifndef C_LAT_LON_MAP_H
#define C_LAT_LON_MAP_H
//-----------------------------------------
//			Lat_Lon_Map.h
//-----------------------------------------
#include "C_Obstacles_Map.h"
#include "C_Radar_Post.h"
#include "C_SCREEN_VIDEO.h"
//-----------------------------------------
//	using namespace:	System
//-----------------------------------------
using namespace System;
//-----------------------------------------
//		Class:	C_Lat_Lon_Map
//-----------------------------------------
public ref class C_Lat_Lon_Map
{
	//-----------------------------------------
	//				Fields
	//-----------------------------------------
private:
	//-----------------------------------------
	//		Data structures
	//-----------------------------------------
	C_Obstacles_Map^				Obstacles_Map;
	C_Radar_Post^					Current_Radar_Post;
	C_SCREEN_VIDEO^					Screen_Video;
	//-----------------------------------------
	//		Graphics
	//-----------------------------------------
	Panel^							Map_Panel;
	Graphics^						Map_Panel_Graphics;

	Panel^							MAP_Chart_Panel;
	Graphics^						MAP_Chart_Panel_Graphics;
	//-----------------------------------------
	//		Auxiliaries
	//-----------------------------------------
	int								Video_Start_Time;
	int								Video_End_Time;
	int								Video_Frame_Time_Sec;
	//------------------------------------
	//		Constructors/Destructor
	//------------------------------------
public:
	C_Lat_Lon_Map();
	~C_Lat_Lon_Map();
	// --------------------------------------------------
	//  Set_Radar_Post  
	//  Haim Otachi		09/12/2015
	// 	Description:	set the pointer to Current_Radar_Post:
	//						1. the current radar position
	//						2. the current detections that belongs to current radar position 
	// 	Reference: 
	//  Input value:	pointer to Current_Radar_Post.
	//  Return Value: 
	// --------------------------------------------------
	void Set_Radar_Post(C_Radar_Post^ Current_Radar_Post_Other);
	// --------------------------------------------------
	//  Set_Step_Radar_Post 
	//  Haim Otachi		28/12/2015
	//	Update:			this function is for 'real time'
	// 	Description:	set the pointer to Current_Radar_Post:
	//						1. the current radar position
	//						2. the current detections that belongs to current radar position 
	// 	Reference: 
	//  Input value:	pointer to Current_Radar_Post.
	//  Return Value: 
	// --------------------------------------------------
	void Set_Step_Radar_Post(C_Radar_Post^ Current_Radar_Post_Other);
	// --------------------------------------------------
	//  Set_Obstacles_Map  
	//  Haim Otachi		09/12/2015
	// 	Description:	set the pointer to Obstacles_Map for plot.
	// 	Reference: 
	//  Input value:	pointer to to Obstacles_Map.
	//  Return Value: 
	// --------------------------------------------------
	void Set_Obstacles_Map(C_Obstacles_Map^ Obstacles_Map_Other);
	// --------------------------------------------------
	//  Set_TOM_Map  
	//  Haim Otachi		17/04/2015
	// 	Description:	set the pointer to TOM Map for plot.
	// 	Reference: 
	//  Input value:	pointer to TOM Map for plot.
	//  Return Value: 
	// --------------------------------------------------
	void Set_TOM_Map(C_Obstacles_Map^ TOM_Map_Other);
	// --------------------------------------------------
	//  Set_Video_File_Name  
	//  Haim Otachi		09/12/2015
	// 	Description:	set the pointer to Video file name for plotting video on the screen.
	// 	Reference: 
	//  Input value:	pointer to Video file name.
	//  Return Value: 
	// --------------------------------------------------
	void Set_Video_File_Name(char* Video_file_name_other);
	// --------------------------------------------------
	//  Set_Video_Parameters 
	//  Haim Otachi		09/12/2015
	// 	Description:	set the parameters of the video:
	//						1. Video_Start_Time.
	//						2. Video_End_Time.
	// 	Reference: 
	//  Input value:	parameters of the video.
	//  Return Value: 
	// --------------------------------------------------
	void Set_Video_Parameters(int Video_Start_Time_Other, int Video_End_Time_Other);
	//-------------------------------------------
	//		Set: Show Detections
	//-------------------------------------------
	void Set_Show_Detections(bool new_detections_status);
	//-------------------------------------------
	//		Set: Show Trajectories
	//-------------------------------------------
	void Set_Show_Trajectories(bool new_trajectories_status);

	//-------------------------------------------
	//		Operator Overloading
	//-------------------------------------------
	void operator=(C_Lat_Lon_Map^ Next_Radar_Post_Other);
	//-----------------------------------------
	//			Public Methods
	//-----------------------------------------
	public:		
	void Initialize(Panel^ Map_Panel_Other, PictureBox^ Map_Video_Other, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other);
	void Initialize(Panel^ Map_Panel_Other, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other);
	//-----------------------------------------
	//			Private Methods
	//-----------------------------------------
	private:
	String^		Plot_Next_Radar_Post();

	void		Plot_Frame_Of_Time_On_Screen();
	void		Plot_TOM_To_Screen();
	void		Plot_Obstacles_To_Screen();
	void		Clear_Map_Panel();

	int GPS_TOW_to_UTC(int TOW_sec);
	int GPS_UTC_to_TOW(int UTC);
};
#endif



