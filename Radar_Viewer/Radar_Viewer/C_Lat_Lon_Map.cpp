// This is the main DLL file.

#include "C_Lat_Lon_Map.h"
//-----------------------------------------
//		Display
//-----------------------------------------
#define		SCREEN_SIZE_X				600
#define		SCREEN_SIZE_Y				600
//-----------------------------------------
//		Misc.
//-----------------------------------------
#define COLOR_TRUE					   	Color::Black
//-------------------------------------
//	Constructor
//-------------------------------------
C_Lat_Lon_Map::C_Lat_Lon_Map()
{
	//-----------------------------------------
	//		Data structures
	//-----------------------------------------	
	Obstacles_Map = gcnew C_Obstacles_Map();
	Current_Radar_Post = gcnew C_Radar_Post();
	Screen_Video = gcnew C_SCREEN_VIDEO();
	//-----------------------------------------
	//		Auxiliaries
	//-----------------------------------------
	Video_Start_Time = 0;
	Video_End_Time = 0;
	Video_Frame_Time_Sec = 0;
}

C_Lat_Lon_Map::~C_Lat_Lon_Map(){}
// --------------------------------------------------
//  Set_Radar_Post  
//  Haim Otachi		09/12/2015
// 	Description:	set the pointer to Current_Radar_Post:
//						1. the current radar position.
//						2. the current detections that belongs to current radar position.
// 	Reference: 
//  Input value:	pointer to Current_Radar_Post.
//  Return Value: 
// --------------------------------------------------
void C_Lat_Lon_Map::Set_Radar_Post(C_Radar_Post^ Current_Radar_Post_Other)
{
	//---------------------------------------------------
	//		Initialize the pointer to the Current_Radar_Post
	//---------------------------------------------------
	Current_Radar_Post = Current_Radar_Post_Other;
	//---------------------------------------------------
	//		Plot the next frame of time (of the radar post) on the screen
	//---------------------------------------------------
	//Plot_Frame_Of_Time_On_Screen();
	//---------------------------------------------------
	//		Plot the next radar post to the screen
	//---------------------------------------------------
	Plot_Next_Radar_Post();
}
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
void C_Lat_Lon_Map::Set_Step_Radar_Post(C_Radar_Post^ Current_Radar_Post_Other)
{
	//---------------------------------------------------
	//		Initialize the pointer to the Current_Radar_Post
	//---------------------------------------------------
	Current_Radar_Post = Current_Radar_Post_Other;
	//---------------------------------------------------
	//		Plot the next radar post to the screen
	//---------------------------------------------------
	Plot_Next_Radar_Post();
}
// --------------------------------------------------
//  Set_Obstacles_Map  
//  Haim Otachi		09/12/2015
// 	Description:	set the pointer to Obstacles_Map for plot.
// 	Reference: 
//  Input value:	pointer to to Obstacles_Map.
//  Return Value: 
// --------------------------------------------------
void C_Lat_Lon_Map::Set_Obstacles_Map(C_Obstacles_Map^ Obstacles_Map_Other)
{
	//---------------------------------------------------
	//		Initialize the pointer to the Obstacles_Map
	//---------------------------------------------------
	Obstacles_Map = Obstacles_Map_Other;
	//---------------------------------------------------
	//		Plot the obstacles map on the screen
	//---------------------------------------------------
	Plot_Obstacles_To_Screen();
}
// --------------------------------------------------
//  Set_TOM_Map  
//  Haim Otachi		17/04/2015
// 	Description:	set the pointer to TOM Map for plot.
// 	Reference: 
//  Input value:	pointer to TOM Map for plot.
//  Return Value: 
// --------------------------------------------------
void C_Lat_Lon_Map::Set_TOM_Map(C_Obstacles_Map^ TOM_Map_Other)
{
	//---------------------------------------------------
	//		Initialize the pointer to the Obstacles_Map
	//---------------------------------------------------
	Obstacles_Map = TOM_Map_Other;
	//---------------------------------------------------
	//		Plot the obstacles map on the screen
	//---------------------------------------------------
	Plot_TOM_To_Screen();
}
// --------------------------------------------------
//  Set_Video_File_Name  
//  Haim Otachi		09/12/2015
// 	Description:	set the pointer to Video file name for plotting video on the screen.
// 	Reference: 
//  Input value:	pointer to Video file name.
//  Return Value: 
// --------------------------------------------------
void C_Lat_Lon_Map::Set_Video_File_Name(char* Video_file_name)
{
	Screen_Video->Set_Video_File(Video_file_name);
}
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
void C_Lat_Lon_Map::Set_Video_Parameters(int Video_Start_Time_Other, int Video_End_Time_Other)
{
	Video_Start_Time = Video_Start_Time_Other;
	Video_End_Time = Video_End_Time_Other;
}
//-------------------------------------------
//		Set: Show Detections
//-------------------------------------------
void C_Lat_Lon_Map::Set_Show_Detections(bool new_detections_status)
{
	Current_Radar_Post->Set_Show_Detections(new_detections_status);
}
//-------------------------------------------
//		Set: Show Trajectories
//-------------------------------------------
void C_Lat_Lon_Map::Set_Show_Trajectories(bool new_trajectories_status)
{
	Current_Radar_Post->Set_Show_Trajectories(new_trajectories_status);
}
// --------------------------------------------------
//  Plot_Next_Radar_Post_Offline  
//  Haim Otachi		 08/03/2016
// 	Description:	 Plot on the screen the one step of Map.
// 	Reference: 
//  Input value:
//  Return Value:	 String containing the status of the current step.
// --------------------------------------------------
String^ C_Lat_Lon_Map::Plot_Next_Radar_Post()
{
	//---------------------------------------------------
	//	We find the screen coordinates of the radar
	//---------------------------------------------------
	int Radar_Screen_X = (int)(Current_Radar_Post->radar_Path->PathPoints[0].X);
	int Radar_Screen_Y = (int)(Current_Radar_Post->radar_Path->PathPoints[0].Y);
	
	if ((Radar_Screen_X > 0) && (Radar_Screen_X < SCREEN_SIZE_X) && (Radar_Screen_Y > 0) && (Radar_Screen_Y < SCREEN_SIZE_Y))
	{
		//---------------------------------------------------
		//		Plot Radar to the screen:	draw arrow relative to heading of the radar
		//---------------------------------------------------	
		Current_Radar_Post->Draw_Arrow_Of_Heading();
	}
	//---------------------------------------------------
	//		Plot The detections of the radar
	//---------------------------------------------------
	Current_Radar_Post->Plot_Detections_To_Screen();
	//---------------------------------------------------
	//		Plot Thetrajectories o the radar
	//---------------------------------------------------
	Current_Radar_Post->Plot_Trajectories_To_Screen();
	return "";
}
// --------------------------------------------------
//  Plot_Obstacles_To_Screen  
//  Haim Otachi		17/09/2015
// 	Description:	Plotting the TOM on the screen 
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
void C_Lat_Lon_Map::Plot_Obstacles_To_Screen()
{
	//---------------------------------------------------
	//				Initial the screen
	//---------------------------------------------------
	Map_Panel_Graphics->Clear(Color::DarkGray);
	//---------------------------------------------------
	//				Print the obstacles to screen
	//---------------------------------------------------
	Obstacles_Map->Plot_Obstacles_To_Screen();
}
// --------------------------------------------------
//  Plot_TOM_To_Screen  
//  Haim Otachi		17/04/2015
// 	Description:	Plotting the TOM on the screen 
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
void C_Lat_Lon_Map::Plot_TOM_To_Screen()
{
	//---------------------------------------------------
	//		Initial the screen
	//---------------------------------------------------
	Map_Panel_Graphics->Clear(Color::DarkGray);
	//---------------------------------------------------
	//		Print the TOM obstacles to screen
	//---------------------------------------------------
	Obstacles_Map->Plot_TOM_To_Screen();
}
// --------------------------------------------------
//  Clear_Radar_Viewer  
//  Alon Slapak		09/12/2015
// 	Description:	Clear TOM and Radar_Route
// 	Reference:		
//  Input value:	
//  Return Value:	
// --------------------------------------------------	
void C_Lat_Lon_Map::Clear_Map_Panel()
{
	//-------------------------------------
	//	Clear screens
	//-------------------------------------
	Map_Panel_Graphics->Clear(Color::DarkGray);
	Screen_Video->Clear_Video_Panel();
}
// --------------------------------------------------
//  Initialize  
//  Haim Otachi		09/12/2015
// 	Description:	//1. Initialize the class parameters
//					2. Load TOM, detections and video if exist
//					//3. Arrange the viewer scale and position
// 	Reference:		
//  Input value:	//Struct of data from the GUI
//  Return Value:	Returned status message
// --------------------------------------------------
void C_Lat_Lon_Map::Initialize(Panel^ Map_Panel_Other, PictureBox^ Map_Video_Other, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other)
{
	//--------------------------------------------------
	//		Initialize the Viewer Panel and him Graphics
	//--------------------------------------------------
	Map_Panel = Map_Panel_Other;
	Map_Panel_Graphics = Map_Panel->CreateGraphics();
	//--------------------------------------------------
	//		Initialize the  Panel and him Graphics of obstacles map
	//--------------------------------------------------
	Obstacles_Map->Initialize(Map_Panel, C_Position(), Max_Range_Error_Meter_Other, Reliability_Threshold_Other);
	//--------------------------------------------------
	//		Initialize the  Panel and him Graphics of current radar route
	//--------------------------------------------------
	Current_Radar_Post->Initialize(Map_Panel_Other, C_Position(), Max_Range_Error_Meter_Other, Reliability_Threshold_Other);
	//--------------------------------------------------
	//		Initialize the Video Panel for the his show
	//--------------------------------------------------
	Screen_Video->Set_Video_Panel(Map_Video_Other);
}
// --------------------------------------------------
//  Initialize  
//  Haim Otachi		28/12/2015
// 	Description:	1. Initialize the class parameters
//					2. Load TOM, detections and video if exist
//					3. Arrange the viewer scale and position
// 	Reference:		
//  Input value:	Struct of data from the GUI
//  Return Value:	Returned status message
// --------------------------------------------------
void C_Lat_Lon_Map::Initialize(Panel^ Map_Panel_Other, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other)
{
	//--------------------------------------------------
	//		Initialize the Viewer Panel and him Graphics
	//--------------------------------------------------
	Map_Panel = Map_Panel_Other;
	Map_Panel_Graphics = Map_Panel->CreateGraphics();
	//--------------------------------------------------
	//		Initialize the  Panel and him Graphics of obstacles map
	//--------------------------------------------------
	Obstacles_Map->Initialize(Map_Panel, C_Position(), Max_Range_Error_Meter_Other, Reliability_Threshold_Other);
	//--------------------------------------------------
	//		Initialize the  Panel and him Graphics of current radar route
	//--------------------------------------------------
	Current_Radar_Post->Initialize(Map_Panel_Other, C_Position(), Max_Range_Error_Meter_Other, Reliability_Threshold_Other);
}
// --------------------------------------------------
//  GPS_TOW_to_UTC  
//  Alon Slapak		24.9.2015
//  Haim Otachi	    Update in 09/12/2015
// 	Description:	Translate from TOW (time of week - seconds from the 
//					begining of the week) from GPS to UTC (Coordinated Universal Time - HHMMSS)
// 	Reference: 
//  Input value:	GPS TOW [seconds]
//  Return Value:	GPS UTC (HHMMSS)
// --------------------------------------------------
int C_Lat_Lon_Map::GPS_TOW_to_UTC(int TOW_sec)
{
	int day, hour, minute, second, UTC;
	// --------------------------------------------
	//	extract dat, Hour, Minute, Second
	// --------------------------------------------
	day = (int)(TOW_sec / (60 * 60 * 24));
	TOW_sec -= day * (60 * 60 * 24);
	hour = (int)(TOW_sec / (60 * 60));
	TOW_sec -= hour * (60 * 60);
	minute = (int)(TOW_sec / 60);
	TOW_sec -= minute * 60;
	second = TOW_sec;
	// --------------------------------------------
	//	fit to UTC
	// --------------------------------------------
	/*hour += 1;
	minute -= 2; */
	// --------------------------------------------
	//	Translate to HHMMSS
	// --------------------------------------------
	UTC = second + 100 * minute + 10000 * hour;
	return UTC;
}
// --------------------------------------------------
//  GPS_UTC_to_TOW  
//  Alon Slapak 24.9.2015
//  Haim Otachi	    Update in 09/12/2015
// 	Description:	Translate from UTC (Coordinated Universal Time - HHMMSS) from GPS 
//					to TOW (time of week - seconds from the begining of the week)
// 	Reference: 
//  Input value:	GPS UTC
//  Return Value:	GPS TOW
// --------------------------------------------------
int C_Lat_Lon_Map::GPS_UTC_to_TOW(int UTC)
{
	int hour, minute, second, TOW;
	// --------------------------------------------
	//	translate to Hour, Minute, Second
	// --------------------------------------------
	hour = (int)(UTC / 10000);
	UTC -= hour * 10000;
	minute = (int)(UTC / 100);
	UTC -= minute * 100;
	second = UTC;
	// --------------------------------------------
	//	fit to TOW
	// --------------------------------------------
	hour -= 1;
	minute += 2;
	// --------------------------------------------
	//	Translate to seconds
	// --------------------------------------------
	TOW = hour * 3600 + minute * 60 + second;
	return TOW;
}
// --------------------------------------------------
//  Plot_Frame_Of_Time_On_Screen  
//  Haim Otachi		 09/12/2015
// 	Description:	 Plot the current frame on the screen if exist
// 	Reference: 
//  Input value:
//  Return Value:	
// --------------------------------------------------
void C_Lat_Lon_Map::Plot_Frame_Of_Time_On_Screen()
{
	//---------------------------------------------------
	//		check if the movie is exist
	//---------------------------------------------------
	try
	{
		//---------------------------------------------------
		//		Calculate the Time stamp of each post (seconds in the week - from sensor)
		//---------------------------------------------------
		Video_Frame_Time_Sec = GPS_TOW_to_UTC((int)(Current_Radar_Post->SENSOR_data.time));
		//--------------------------------------
		//			Plot movie
		//--------------------------------------
		if ((Video_Frame_Time_Sec >= Video_Start_Time) && (Video_Frame_Time_Sec <= Video_End_Time))
		{
			Screen_Video->plot_frame_of_time(GPS_UTC_to_TOW(Video_Frame_Time_Sec) - GPS_UTC_to_TOW(Video_Start_Time));
		}
		else
		{
			System::Threading::Thread::Sleep(200);
		}
		//return (Radar_Route.Get_Current_Time_Stamp_Of_SENSOR().ToString("N8") + L" mSec");
		//--------------------------------------
		//	Erase plot & plot TOM
		//--------------------------------------
		Map_Panel_Graphics->Clear(Color::DarkGray);
		Plot_TOM_To_Screen();
	}
	catch (System::Exception^ Ex)
	{
		Ex->Message;
	}
}
//-------------------------------------------
//		Operator Overloading
//-------------------------------------------
void C_Lat_Lon_Map::operator=(C_Lat_Lon_Map^ Next_Radar_Post_Other)
{
	//-----------------------------------------
	//		Data structures
	//-----------------------------------------
	Obstacles_Map				= Next_Radar_Post_Other->Obstacles_Map;
	Current_Radar_Post			= Next_Radar_Post_Other->Current_Radar_Post;
	Screen_Video				= Next_Radar_Post_Other->Screen_Video;
	//-----------------------------------------
	//		Graphics
	//-----------------------------------------
	Map_Panel					= Next_Radar_Post_Other->Map_Panel;
	Map_Panel_Graphics			= Next_Radar_Post_Other->Map_Panel_Graphics;
	//-----------------------------------------
	//		Auxiliaries
	//-----------------------------------------
	Video_Start_Time			= Next_Radar_Post_Other->Video_Start_Time;
	Video_End_Time				= Next_Radar_Post_Other->Video_End_Time;
	Video_Frame_Time_Sec		= Next_Radar_Post_Other->Video_Frame_Time_Sec;
}