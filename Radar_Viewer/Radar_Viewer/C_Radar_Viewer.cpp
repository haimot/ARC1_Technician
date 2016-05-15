// This is the main DLL file.
#include "C_Radar_Viewer.h"
#include "C_Lat_Lon_Map.h"
#include <fstream>
//-----------------------------------------
//		Display
//-----------------------------------------
#define SCREEN_SIZE_X					600
#define SCREEN_SIZE_Y					600
//-----------------------------------------
//		Misc.
//-----------------------------------------
#define COLOR_TRUE					   	Color::Black

using namespace System::IO;
using std::ifstream;
using std::fstream;
using std::ios;

namespace Radar_Viewer
{
	//-------------------------------------
	//	Constructor
	//-------------------------------------
	C_Radar_Viewer::C_Radar_Viewer()
	{
		New_Input					= gcnew C_Lat_Lon_Map();
		//-----------------------------------------
		//			Auxiliaries
		//-----------------------------------------
		Last_screen_point_of_wire	= gcnew C_Position;
		Point_mouse_move			= gcnew C_Position;

		Start_wire_from_mouse		= false;
	}
	// --------------------------------------------------
	//  Viewer_Step  
	//  Haim Otachi		 13/10/2015
	// 	Description:	 Run the viewer one step ahead
	// 	Reference: 
	//  Input value:
	//  Return Value:	String containing the status of the current step.
	// --------------------------------------------------
	C_Radar_Viewer::~C_Radar_Viewer()
	{
		if (New_Input)
		{
			delete New_Input;
		}
		
		if (Last_screen_point_of_wire)
		{
			delete Last_screen_point_of_wire;
		}

		if (Point_mouse_move)
		{
			delete Point_mouse_move;
		}

		if (Viewer_Panel)
		{
			delete Viewer_Panel;
		}

		if (Viewer_Panel_Graphics)
		{
			delete Viewer_Panel_Graphics;
		}
		
		if (MAP_Chart_Panel)
		{
			delete MAP_Chart_Panel;
		}

		if (MAP_Chart_Panel_Graphics)
		{
			delete MAP_Chart_Panel_Graphics;
		}		
	}
	//-------------------------------------------
	//		Set: Show Detections
	//-------------------------------------------
	void C_Radar_Viewer::Set_Show_Detections(bool new_detections_status)
	{
		Radar_Route.Set_Show_Detections(new_detections_status);
	}
	//-------------------------------------------
	//		Set: Show Trajectories
	//-------------------------------------------
	void C_Radar_Viewer::Set_Show_Trajectories(bool new_trajectories_status)
	{
		Radar_Route.Set_Show_Trajectories(new_trajectories_status);
	}
	////-------------------------------------------
	////		Set/Get: Base_Meter_Per_Pixel_For_Scale
	////-------------------------------------------
	//double C_Radar_Viewer::get_Base_Meter_Per_Pixel_For_Scale()
	//{
	//	Radar_Route.get_Base_Meter_Per_Pixel_For_Scale();
	//}
	void C_Radar_Viewer::Set_Base_Meter_Per_Pixel_For_Scale(double meter_per_pixel_other)
	{
		Radar_Route.Set_Base_Meter_Per_Pixel_For_Scale(meter_per_pixel_other);
	}


	String^ C_Radar_Viewer::Viewer_Step()
	{
		//--------------------------------------
		//	Print Path movement of the radar on the screen
		//--------------------------------------
		if (Radar_Route.Move_To_Next_Radar_Post())
		{
			return L"viewer running.";
		}
		return L"done";
	}
	// --------------------------------------------------
	//  Plot_Step_Position_Of_Radar  
	//  Haim Otachi		 28/12/2015
	//	Update:			 this function is for 'real Time'
	// 	Description:	 Run the viewer one step ahead and plot the current 
	//					 step position of the radar on the screen
	// 	Reference: 
	//  Input value:
	//  Return Value:	String containing the status of the current step.
	// --------------------------------------------------
	String^ C_Radar_Viewer::Plot_Step_Position_Of_Radar()
	{
		//-------------------------------------
		//	Clear the obstacles map
		//-------------------------------------
		Plot_TOM_On_Screen();
		//--------------------------------------
		//	Print Path movement of the radar on the screen
		//--------------------------------------
		if (Radar_Route.Move_To_Next_Step_Radar_Post())
		{
			return L"viewer running.";
		}
		return L"done";
	}
	// --------------------------------------------------
	//  Load_Movie  
	//  Haim Otachi		27/09/2015
	// 	Description:	1. Load and plot TOM
	//					2. Load and initialize video 
	// 	Reference:		
	//  Input value:	Struct of data from the GUI
	//  Return Value:	true for success, false else.
	// --------------------------------------------------
	bool C_Radar_Viewer::Load_Movie()
	{
		String^ AVI_file_name;
		String^ LOG_file_name;

		Collections::IEnumerator^ myEnum;
		char file_name[MAX_STRING_LENGTH];

		int Video_Start_Time = 0;
		int Video_End_Time = 0;
		//--------------------------------------------------
		//			
		//--------------------------------------------------
		String^ Directory_Path_Of_Files = gcnew String(GUI_Status.DETECTIONS_Folder_Of_Viewer);
		//--------------------------------------------------
		//		Make a reference to a directory		
		//--------------------------------------------------	
		DirectoryInfo^ dir = gcnew DirectoryInfo(Directory_Path_Of_Files);
		array<FileInfo^>^ fiArr = gcnew array<FileInfo^>(MAX_STRING_LENGTH);
		//--------------------------------------------------
		//		Get a reference to current MP4 file in that directory		
		//--------------------------------------------------		
		fiArr = dir->GetFiles("*.MP4");
		myEnum = fiArr->GetEnumerator();
		if (myEnum->MoveNext())
		{
			FileInfo^ Current_File = dynamic_cast<FileInfo^>(myEnum->Current);
			//--------------------------------------------------
			//		Display the name of the files
			//--------------------------------------------------
			AVI_file_name = Current_File->Name;
		}
		//--------------------------------------------------
		//		Get a reference to current LOG file in that directory		
		//--------------------------------------------------		
		fiArr = dir->GetFiles("*.LOG");
		myEnum = fiArr->GetEnumerator();
		if (myEnum->MoveNext())
		{
			FileInfo^ Current_File = dynamic_cast<FileInfo^>(myEnum->Current);
			//--------------------------------------------------
			//		Display the name of the files
			//--------------------------------------------------
			LOG_file_name = Current_File->Name;
		}
		//--------------------------------------------------
		//			Get vido and GPS file
		//--------------------------------------------------
		sprintf_s(file_name, "%s\\%s", GUI_Status.DETECTIONS_Folder_Of_Viewer, AVI_file_name);
		New_Input->Set_Video_File_Name(file_name);
		//--------------------------------------------------
		//			Find start time and end time of the movie
		//--------------------------------------------------
		char temp[MAX_STRING_LENGTH];
		char text_line[MAX_STRING_LENGTH];
		ifstream LOG_file;
		double time_sec;
		sprintf_s(file_name, "%s\\%s", GUI_Status.DETECTIONS_Folder_Of_Viewer, LOG_file_name);
		LOG_file.open(file_name);
		if (LOG_file.good())
		{
			//--------------------------------------------------
			// read 2 @Sonygps header lines
			//--------------------------------------------------
			LOG_file.getline(text_line, MAX_STRING_LENGTH);
			LOG_file.getline(text_line, MAX_STRING_LENGTH);
			//--------------------------------------------------
			// Video start time
			//--------------------------------------------------
			LOG_file.getline(text_line, MAX_STRING_LENGTH);
			LOG_file.getline(text_line, MAX_STRING_LENGTH);
			//--------------------------------------------------
			// parse the line into blank-delimited tokens
			// $GPRMC,110804.000,A,3128.1065,N,3447.1991,E,51.41,,200815,,,A*7D
			//--------------------------------------------------
			sscanf(text_line, "$GPRMC,%lf,%s", &time_sec, &temp);
			Video_Start_Time = (int)time_sec;
			//--------------------------------------------------
			// Video start time
			//--------------------------------------------------
			while (!LOG_file.eof())
			{
				//--------------------------------------------------
				// read 2-lines report from file
				//--------------------------------------------------
				LOG_file.getline(text_line, MAX_STRING_LENGTH);
				LOG_file.getline(text_line, MAX_STRING_LENGTH);
				//--------------------------------------------------
				// parse the line into blank-delimited tokens
				// $GPRMC,110804.000,A,3128.1065,N,3447.1991,E,51.41,,200815,,,A*7D
				//--------------------------------------------------
				sscanf(text_line, "$GPRMC,%lf,%s", &time_sec, &temp);
				Video_End_Time = (int)time_sec;
			}
			New_Input->Set_Video_Parameters(Video_Start_Time, Video_End_Time);
			Radar_Route.Set_Data_Of_Radar_Post(New_Input);
			LOG_file.close();
			return true;
		}
		else
		{
			return false;
		}
	}
	// --------------------------------------------------
	//  Load_TOM_From_File  
	//  Haim Otachi				09/10/2015
	// 	Description:	-> Load the obstacles (TOM) points from file .
	//					-> Update the Screen position, size and resolution of the screen .
	// 	Reference:		
	//  Input value:	
	//  Return Value:	true for succsess, false for fault
	// --------------------------------------------------
	bool C_Radar_Viewer::Load_TOM_From_File()
	{
		//--------------------------------------------------
		//			Load true obstacles map (TOM) from file
		//--------------------------------------------------
		if (TOM.Load_From_File(GUI_Status.Viewer_TOM_File_Name) == false)
		{
			return false;
		}
		//--------------------------------------------------
		//			Update Screen size & position 
		//--------------------------------------------------
		if (Reset_Radar_Viewer() == false)
		{
			return false;
		}
		return true;
	}
	// --------------------------------------------------
	//  Load_Detections_From_File  
	//  Alon Slapak		 21/10/2015
	// 	Description:	-> Load the detections from file .
	//					-> Update the Screen position, size and resolution of the screen .
	// 	Reference:		
	//  Input value:	
	//  Return Value:	true for succsess, false for fault
	// --------------------------------------------------
	bool C_Radar_Viewer::Load_Detections_From_File()
	{
		//--------------------------------------------------
		//			Load detections from file
		//--------------------------------------------------
		if (Radar_Route.Load_From_File(GUI_Status.DETECTIONS_Folder_Of_Viewer) == false)
		{
			return false;
		}
		//---------------------------------------------------
		// Load Movie 
		//--------------------------------------------------- 
		Load_Movie();
		//--------------------------------------------------
		//			Update Screen size & position 
		//--------------------------------------------------
		if (Reset_Radar_Viewer() == false)
		{
			return false;
		}
		return true;
	}
	// --------------------------------------------------
	//  Clear_Radar_Viewer  
	//  Alon Slapak		22/10/2015
	// 	Description:	Clear TOM and Radar_Route
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------	
	void C_Radar_Viewer::Clear_Radar_Viewer()
	{
		////-------------------------------------
		////	Clear the screen
		////-------------------------------------
		//Viewer_Panel_Graphics->Clear(Color::DarkGray);
		//////-------------------------------------
		//////	Clear the obstacles map
		//////-------------------------------------
		//Plot_TOM_On_Screen();
		//TOM.Clear();
		//-------------------------------------
		//	Clear data structures
		//-------------------------------------
		Radar_Route.Clear();
	}
	// --------------------------------------------------
	//  Reset_Radar_Viewer  
	//  Alon Slapak		25/10/2015
	// 	Description:	Reset the viewer size and position. Calculate the bottom-left and top-right corners of the
	//					screen as a union of the TOM coordinates and the radar-route corners. 
	// 	Reference:		
	//  Input value:	
	//  Return Value:	true for success, false else
	// --------------------------------------------------	
	bool C_Radar_Viewer::Reset_Radar_Viewer()
	{
		C_Position Screen_Top_Right;
		C_Position Screen_Bottom_Left;
		//-------------------------------------
		//	Initialize the Radar_Viewer screen corners
		//-------------------------------------
		double min_Lat = 89.999999; // Maximum possible lat
		double min_Lon = 179.999999; // Maximum possible lon
		double min_Alt = 0; // Maximum possible Alt

		double max_Lat = -89.999999; // Minimum possible lat
		double max_Lon = -179.999999; // Minimum possible lon
		double max_Alt = 0; // Minimum possible Alt

		if (Radar_Route.Is_Empty() == true)
		{
			min_Lat = fmax(min_Lat, Radar_Route.Screen_Bottom_Left.Latitude);
			min_Lon = fmax(min_Lon, Radar_Route.Screen_Bottom_Left.Longitude);
			min_Alt = fmax(min_Alt, Radar_Route.Screen_Bottom_Left.Altitude);
		}
		else
		{
			min_Lat = fmin(min_Lat, Radar_Route.Screen_Bottom_Left.Latitude);
			min_Lon = fmin(min_Lon, Radar_Route.Screen_Bottom_Left.Longitude);
			min_Alt = fmin(min_Alt, Radar_Route.Screen_Bottom_Left.Altitude);
		}

		if (TOM.Is_Empty() == true)
		{
			min_Lat = fmax(min_Lat, TOM.Screen_Bottom_Left.Latitude);
			min_Lon = fmax(min_Lon, TOM.Screen_Bottom_Left.Longitude);
			min_Alt = fmax(min_Alt, TOM.Screen_Bottom_Left.Altitude);
		}
		else
		{
			min_Lat = fmin(min_Lat, TOM.Screen_Bottom_Left.Latitude);
			min_Lon = fmin(min_Lon, TOM.Screen_Bottom_Left.Longitude);
			min_Alt = fmin(min_Alt, TOM.Screen_Bottom_Left.Altitude);
		}

		max_Lat = fmax(max_Lat, Radar_Route.Screen_Top_Right.Latitude);
		max_Lat = fmax(max_Lat, TOM.Screen_Top_Right.Latitude);

		max_Lon = fmax(max_Lon, Radar_Route.Screen_Top_Right.Longitude);
		max_Lon = fmax(max_Lon, TOM.Screen_Top_Right.Longitude);

		max_Alt = fmax(max_Alt, Radar_Route.Screen_Top_Right.Altitude);
		max_Alt = fmax(max_Alt, TOM.Screen_Top_Right.Altitude);

		Screen_Bottom_Left.set_Object_in_UTM_Position(min_Lat, min_Lon, min_Alt);
		Screen_Top_Right.set_Object_in_UTM_Position(max_Lat, max_Lon, max_Alt);
		//---------------------------------------------------
		// calculate the screen width
		//--------------------------------------------------- 
		C_CartesianPoint screen_size = Screen_Top_Right - Screen_Bottom_Left;
		double screen_width_meter = fmax(screen_size.X, screen_size.Y);
		if (screen_width_meter < 1000)
		{
			screen_width_meter = 5e3;
		}
		if (screen_width_meter > 30e3)
		{
			return false;
		}
		//---------------------------------------------------
		// Update viewer position and scale
		//--------------------------------------------------- 
		GUI_Status.Viewer_GPS_Latitude = min_Lat;
		GUI_Status.Viewer_GPS_Longitude = min_Lon;

		Set_Viewer_Scale(screen_width_meter);
		Set_Viewer_Position(Screen_Bottom_Left);
		// --------------------------------------------------
		//			we create TOM array for plotting
		// --------------------------------------------------
		Create_TOM_Array();
		Create_Radar_Route_Position();
		//---------------------------------------------------
		// Refreshing the TOM
		//--------------------------------------------------- 
		Plot_TOM_On_Screen();
		return true;
	}
	// --------------------------------------------------
	//  Initialize  
	//  Haim Otachi		27/09/2015
	// 	Description:	1. Initialize the class parameters
	//					2. Load TOM, detections and video if exist
	//					3. Arrange the viewer scale and position
	// 	Reference:		
	//  Input value:	Struct of data from the GUI
	//  Return Value:	Returned status message
	// --------------------------------------------------
	String^ C_Radar_Viewer::Initialize(Panel^ Viewer_Panel_other, PictureBox^ Viewer_Video_other, C_GUI_Status% GUI_Status_other)
	{
		String^ returned_message;

		GUI_Status.GUI_Data = GUI_Status_other.GUI_Data;
		//--------------------------------------------------
		//		Initialize the Viewer Panel and him Graphics
		//--------------------------------------------------
		Viewer_Panel = Viewer_Panel_other;
		Viewer_Panel_Graphics = Viewer_Panel->CreateGraphics();
		//--------------------------------------------------
		//		Initialize the Video Panel for the his show
		//--------------------------------------------------
		TOM.Initialize(Viewer_Panel, C_Position(), GUI_Status.Max_Range_Error_Meter, GUI_Status.Reliability_Threshold);
		//--------------------------------------------------
		//		Initialize the Video Panel for the his show
		//--------------------------------------------------
		New_Input->Initialize(Viewer_Panel, Viewer_Video_other, GUI_Status.Max_Range_Error_Meter, GUI_Status.Reliability_Threshold);
		Radar_Route.Set_Data_Of_Radar_Post(New_Input);
		//-----------------------------------------
		//		Update Radar_Routing array
		//-----------------------------------------
		Radar_Route.Initialize(Viewer_Panel, C_Position(), GUI_Status_other);
		//--------------------------------------------------
		//		Load TOM
		//--------------------------------------------------
		if (Load_TOM_From_File() == false)
		{
			returned_message = L"TOM file is incorrect.";
		}
		else
		{
			returned_message = L"TOM file was loaded.";
		}
		//--------------------------------------------------
		//		Load Detections
		//--------------------------------------------------
		if (Load_Detections_From_File() == false)
		{
			returned_message = L"Detections file is incorrect.";
		}
		else
		{
			returned_message = L"Detections file was loaded. Ready to play results.";
		}
		//--------------------------------------------------
		//		resize of the shapes
		//--------------------------------------------------
		if (Reset_Radar_Viewer() == false)
		{
			returned_message = "Dimensions error. Files cannot be displayed.";
		}
		return returned_message;
	}

	// --------------------------------------------------
	//  Initialize  
	//  Haim Otachi		27/09/2015
	// 	Description:	1. Initialize the class parameters
	//					2. Load TOM, detections and video if exist
	//					3. Arrange the viewer scale and position
	//					
	//					Real time function
	// 	Reference:		
	//  Input value:	Struct of data from the GUI
	//  Return Value:	Returned status message
	//// --------------------------------------------------
	//String^ C_Radar_Viewer::Initialize(Panel^ Viewer_Panel_other, PictureBox^ Viewer_Video_other, Chart^ MAP_Chart_other, C_GUI_Status% GUI_Status_other)
	//{
	//	String^ returned_message;
	//	GUI_Status.GUI_Data = GUI_Status_other.GUI_Data;
	//	//--------------------------------------------------
	//	//		Initialize the Viewer Panel and him Graphics
	//	//--------------------------------------------------
	//	Viewer_Panel = Viewer_Panel_other;
	//	Viewer_Panel_Graphics = Viewer_Panel->CreateGraphics();
	//	MAP_Chart_Panel = MAP_Chart_other;
	//	MAP_Chart_Panel_Graphics = MAP_Chart_Panel->CreateGraphics();
	//	//--------------------------------------------------
	//	//		Initialize the Video Panel for the his show
	//	//--------------------------------------------------
	//	TOM.Initialize(Viewer_Panel, MAP_Chart_Panel, C_Position(), GUI_Status.Max_Range_Error_Meter, GUI_Status.Reliability_Threshold);
	//	//--------------------------------------------------
	//	//		Initialize the Video Panel for the his show
	//	//--------------------------------------------------
	//	New_Input->Initialize(Viewer_Panel, Viewer_Video_other, MAP_Chart_Panel, GUI_Status.Max_Range_Error_Meter, GUI_Status.Reliability_Threshold);
	//	Radar_Route.Set_Data_Of_Radar_Post(New_Input);
	//	//-----------------------------------------
	//	//		Update Radar_Routing array
	//	//-----------------------------------------
	//	Radar_Route.Initialization_Of_Radar_Route(Viewer_Panel, C_Position(), GUI_Status_other);
	//	//--------------------------------------------------
	//	//		Load TOM
	//	//--------------------------------------------------
	//	if (Load_TOM_From_File() == false)
	//	{
	//		returned_message = L"TOM file is incorrect.";
	//	}
	//	else
	//	{
	//		returned_message = L"TOM file was loaded.";
	//	}
	//	//--------------------------------------------------
	//	//		Load Detections
	//	//--------------------------------------------------
	//	if (Load_Detections_From_File() == false)
	//	{
	//		returned_message = L"Detections file is incorrect.";
	//	}
	//	else
	//	{
	//		returned_message = L"Detections file was loaded. Ready to play results.";
	//	}
	//	//--------------------------------------------------
	//	//		Detections
	//	//--------------------------------------------------
	//	if (Reset_Radar_Viewer() == false)
	//	{
	//		returned_message = "Dimensions error. Files cannot be displayed.";
	//	}
	//	return returned_message;
	//}

	// --------------------------------------------------
	//  Initialize  
	//  Haim Otachi		28/12/2015
	// 	Description:	1. Initialize the class parameters
	//					2. Load TOM, detections and video if exist
	//					3. Arrange the viewer scale and position
	//
	//
	//
	// 	Reference:		
	//  Input value:	Struct of data from the GUI
	//  Return Value:	Returned status message
	// --------------------------------------------------
	String^ C_Radar_Viewer::Initialize(Panel^ Viewer_Panel_other, C_GUI_Status% GUI_Status_other)
	{
		String^ returned_message;

		GUI_Status.GUI_Data = GUI_Status_other.GUI_Data;
		//--------------------------------------------------
		//		Initialize the Viewer Panel and him Graphics
		//--------------------------------------------------
		Viewer_Panel = Viewer_Panel_other;
		Viewer_Panel_Graphics = Viewer_Panel->CreateGraphics();
		//--------------------------------------------------
		//		Initialize the Video Panel for the his show
		//--------------------------------------------------
		TOM.Initialize(Viewer_Panel, C_Position(), GUI_Status.Max_Range_Error_Meter, GUI_Status.Reliability_Threshold);
		//--------------------------------------------------
		//		Initialize the Video Panel for the his show
		//--------------------------------------------------
		New_Input->Initialize(Viewer_Panel, GUI_Status.Max_Range_Error_Meter, GUI_Status.Reliability_Threshold);
		Radar_Route.Set_Data_Of_Radar_Post(New_Input);
		//-----------------------------------------
		//		Update Radar_Routing array
		//-----------------------------------------
		Radar_Route.Initialize(Viewer_Panel, C_Position(), GUI_Status_other);
		//--------------------------------------------------
		//		Load TOM
		//--------------------------------------------------
		if (Load_TOM_From_File() == false)
		{
			returned_message = L"TOM file is incorrect.";
		}
		else
		{
			returned_message = L"TOM file was loaded.";
		}
		//--------------------------------------------------
		//		Load Detections
		//--------------------------------------------------
		if (Load_Detections_From_File() == false)
		{
			returned_message = L"Detections file is incorrect.";
		}
		else
		{
			returned_message = L"Detections file was loaded. Ready to play results.";
		}
		//--------------------------------------------------
		//		Detections
		//--------------------------------------------------
		if (Reset_Radar_Viewer() == false)
		{
			returned_message = "Dimensions error. Files cannot be displayed.";
		}
		return returned_message;
	}
	// --------------------------------------------------
	//  Set_Viewer_Position  
	//  Alon Slapak		22/10/2015
	// 	Description:	This function gets the position of the bottom-left point of the 
	//					screen and updated the graphical elements (e.g., TOM and radar route).
	// 	Reference:		
	//  Input value:	the requested screen_bottom_left
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Set_Viewer_Position(C_Position% screen_bottom_left)
	{
		GUI_Status.Viewer_GPS_Latitude = screen_bottom_left.Latitude;
		GUI_Status.Viewer_GPS_Longitude = screen_bottom_left.Longitude;

		if (TOM.Get_Number_Of_Obstacles() != 0)
		{
			TOM.Set_Screen_In_UTM_Origin(screen_bottom_left);
		}
		if (Radar_Route.Get_Current_Number_Of_Post_In_Radar_Route() != 0)
		{
			Radar_Route.Update_Screen_in_UTM(screen_bottom_left);
		}		
	}
	// --------------------------------------------------
	//  Offset_Viewer_Position  
	//  Alon Slapak		22/10/2015
	// 	Description:	This function gets an offset in pixels, and moves the  
	//					the graphical objects (e.g., TOM and radar route) accordingley by changing the 
	//					Lat/Lon of the screen.
	// 	Reference:		
	//  Input value:	the requested screen_bottom_left
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Offset_Viewer_Position(int delta_pixels_x, int delta_pixels_y)
	{
		//--------------------------------------------------
		//	Update Screen size to contain the TOM by 'Offset_TOM_Array' function.
		//--------------------------------------------------
		Offset_TOM_Array((float)(delta_pixels_x), (float)(delta_pixels_y));
		//--------------------------------------------------
		//	Update Screen size to contain the radar route by 'Offset_Radar_Position' function.
		//--------------------------------------------------
		Offset_Radar_Position((float)(delta_pixels_x), (float)(delta_pixels_y));
	}
	// --------------------------------------------------
	//  Real_Time_Offset_Viewer_Position  
	//  Haim Otachi		13/01/2015
	// 	Description:	This function gets an offset in pixels, and moves the  
	//					the graphical objects (e.g., TOM and radar route) accordingley by changing the 
	//					Lat/Lon of the screen.
	// 	Reference:		
	//  Input value:	the requested screen_bottom_left
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Real_Time_Offset_Viewer_Position(int delta_pixels_x, int delta_pixels_y)
	{
		C_CartesianPoint offset(delta_pixels_x * GUI_Status.Meter_Per_Pixel_Of_Viewer, -delta_pixels_y * GUI_Status.Meter_Per_Pixel_Of_Viewer);
		//--------------------------------------------------
		//			Update Screen size to contain the TOM
		//--------------------------------------------------
		C_Position Screen_Bottom_Left;
		Screen_Bottom_Left.set_Object_in_UTM_Position(GUI_Status.Viewer_GPS_Latitude, GUI_Status.Viewer_GPS_Longitude, 0);
		Screen_Bottom_Left -= offset;
		Set_Step_Viewer_Position(Screen_Bottom_Left);
		//Offset_TOM_Array(delta_pixels_x, delta_pixels_y);
		//Offset_Radar_Position(delta_pixels_x, delta_pixels_y);
	}
	// --------------------------------------------------
	//  Set_Viewer_Scale  
	//  Alon Slapak		21/10/2015
	// 	Description:	This function gets a request screen width in meter, and updates the GUI and 
	//					the graphical objects (e.g., TOM and radar route) with the appropriate
	//					meter_per_pixel.
	// 	Reference:		
	//  Input value:	the requested screen_width in meter
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Set_Viewer_Scale(double screen_width_meter)
	{
		double meter_per_pixel = screen_width_meter / SCREEN_SIZE_X;
		//---------------------------------------------------
		//			Update GUI_Status struct with new data 
		//---------------------------------------------------
		GUI_Status.Meter_Per_Pixel_Of_Viewer = meter_per_pixel;
		GUI_Status.Screen_Width_Of_Viewer = (int)screen_width_meter;
		//---------------------------------------------------
		//			Update TOM and radar_route
		//---------------------------------------------------
		TOM.Set_Meter_Per_Pixel(meter_per_pixel);
		Radar_Route.Update_Meter_Per_Pixel(meter_per_pixel);
		Radar_Route.Set_Base_Meter_Per_Pixel_For_Scale(meter_per_pixel);
	}
	// --------------------------------------------------
	//  Set_Scale  
	//  Haim Otachi		01/05/2016
	// 	Description:	???
	//					
	// 	Reference:		
	//  Input value:	the requested screen_width in meter
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Set_Scale(double screen_width_meter)
	{
		double meter_per_pixel = screen_width_meter / SCREEN_SIZE_X;
		//---------------------------------------------------
		//			Update TOM and radar_route
		//---------------------------------------------------
		TOM.Update_Scale((float)(meter_per_pixel / 10), (float)(meter_per_pixel / 10));		
		//Radar_Route.Update_Scale((float)(meter_per_pixel / 10), (float)(meter_per_pixel / 10));
		Radar_Route.Update_Meter_Per_Pixel(meter_per_pixel);


	}
	// --------------------------------------------------
	//  Set_Viewer_Scale  
	//  Alon Slapak		21/10/2015
	// 	Description:	This function gets a request screen width in meter, and updates the GUI and 
	//					the graphical objects (e.g., TOM and radar route) with the appropriate
	//					meter_per_pixel.
	// 	Reference:		
	//  Input value:	the requested screen_width in meter
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Set_Real_Time_Viewer_Scale(double screen_width_meter)
	{
		double meter_per_pixel = screen_width_meter / SCREEN_SIZE_X;
		//---------------------------------------------------
		//			Update GUI_Status struct with new data 
		//---------------------------------------------------
		GUI_Status.Meter_Per_Pixel_Of_Viewer = meter_per_pixel;
		GUI_Status.Screen_Width_Of_Viewer = (int)screen_width_meter;
		//---------------------------------------------------
		//			Update TOM and radar_route
		//---------------------------------------------------
		TOM.Set_Meter_Per_Pixel(meter_per_pixel);
		Radar_Route.Update_Meter_Per_Pixel_For_Real_Time(meter_per_pixel);
	}
	// --------------------------------------------------
	//  Clear_Screen  
	//  Haim Otachi  	03/11/2015
	// 	Description:	The function clear the screen, Supposedly: clear the pointers to TOM, EOM, and Radar_Route structures
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Clear_Screen()
	{
		//--------------------------------------------------
		//	Clear and Initialize the Video Panel for the his show
		//--------------------------------------------------
		TOM.Clear();
		TOM.Initialize(Viewer_Panel, C_Position(), GUI_Status.Max_Range_Error_Meter, GUI_Status.Reliability_Threshold);
		//--------------------------------------------------
		//	Clear and Initialize the Video Panel for the his show
		//--------------------------------------------------
		//EOM.Clear();
		//EOM.Initialize(Viewer_Panel, C_Position(), GUI_Status.Max_Range_Error_Meter, GUI_Status.Reliability_Threshold);
		//-----------------------------------------
		//	Clear, set up, and Update Radar_Routing array
		//-----------------------------------------
		Radar_Route.Clear();
		Radar_Route.Set_Data_Of_Radar_Post(New_Input);
		Radar_Route.Initialize(Viewer_Panel, C_Position(), GUI_Status);
	}
	// --------------------------------------------------
	//  Restart_Real_Time  
	//  Haim Otachi  	12/12/2015
	//  Update at		07/04/2016
	// 	Description:	The function restart the screen, Supposedly: restart the pointers to TOM, EOM, and Radar_Route structures
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Restart_Real_Time()
	{
		TOM.Restart();
		//EOM.Restart();
		Radar_Route.Restart();
	}
	// --------------------------------------------------
	//  Restart_Offline  
	//  Haim Otachi  	07/04/2016
	// 	Description:	The function restart the screen, Supposedly: restart the pointers to TOM, EOM, and Radar_Route structures
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Restart_Offline()
	{
		Viewer_Panel_Graphics->Clear(Color::DarkGray);
		TOM.Restart();
		//EOM.Restart();
		Radar_Route.Restart();
	}
	// --------------------------------------------------
	//  Plot_TOM_On_Screen  
	//  Haim Otachi  	10/12/2015
	// 	Description:	The function plot the TOM point on the screnn
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Plot_TOM_On_Screen()
	{
		// --------------------------------------------------
		// set the TOM obstacles into C_Lat_Lon_Map class and this class plot him
		// --------------------------------------------------
		New_Input->Set_TOM_Map(%TOM);
	}
	// --------------------------------------------------
	//  Create_TOM_Array  
	//  Haim Otachi  	20/04/2016
	// 	Description:	The function create the TOM array for plotting
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Create_TOM_Array()
	{
		TOM.Create_TOM_Array();
	}

	void C_Radar_Viewer::Create_Radar_Route_Position()
	{
		Radar_Route.Create_Radar_Route_Position();
	}

	void C_Radar_Viewer::Add_Radar_Post(C_Position% Radar_post_other)
	{
		Radar_Route.Add_Radar_Post(Radar_post_other);
	}

	#pragma region Real Time function
	// --------------------------------------------------
	//  Add_Radar_Post
	//  Haim Otachi  	24/12/2015
	// 	Description:	The function received new 'position' relative to radar from outside and added him to the system
	// 	Reference:		
	//  Input value:	new 'position' relative to radar
	//  Return Value:	
	// --------------------------------------------------
	bool C_Radar_Viewer::Add_Radar_Post(C_Data_Recording^  data_recording_of_radar)
	{
		//---------------------------------------------------
		//	Add new position of the radar (include his detections)
		//---------------------------------------------------
		if (Radar_Route.Add_Radar_Post(*data_recording_of_radar) == false)
		{
			return false;
		}		
		//--------------------------------------------------
		//			Update Screen size & position 
		//--------------------------------------------------
		if (Reset_Step_Radar_Position_Real_Time() == false)
		{
			return false;
		}
		return true;
	}
	// --------------------------------------------------
	//  Reset_Step_Radar_Position  
	//  Haim Otachi  	28/12/2015
	// 	Description:	Reset the viewer size and step position. Calculate the bottom-left and top-right corners of the
	//					screen and the radar-route corners. 
	// 	Reference:		
	//  Input value:	
	//  Return Value:	true for success, false else
	// --------------------------------------------------
	bool C_Radar_Viewer::Reset_Step_Radar_Position_Real_Time()
	{
		/*if (TOM.Is_Empty() == true)
		{
			Radar_Route.Set_Screen_Coordinates(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
		}*/

		Radar_Route.Create_Radar_Route_Position();

		return true;
	}
	// --------------------------------------------------
	//  Set_Step_Viewer_Scale  
	//  Haim Otachi		28/12/2015
	// 	Description:	This function gets a request screen width in meter, and updates the GUI and 
	//					the graphical objects (e.g., radar route) with the appropriate
	//					meter_per_pixel.
	// 	Reference:		
	//  Input value:	the requested screen_width in meter
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Set_Step_Viewer_Scale(double screen_width_meter)
	{
		double meter_per_pixel = screen_width_meter / SCREEN_SIZE_X;
		//---------------------------------------------------
		//			Update GUI_Status struct with new data 
		//---------------------------------------------------
		GUI_Status.Meter_Per_Pixel_Of_Viewer = meter_per_pixel;
		GUI_Status.Screen_Width_Of_Viewer = (int)screen_width_meter;
		//---------------------------------------------------
		//			Update the current position (some step) of the radar
		//---------------------------------------------------
		//TOM.Set_Meter_Per_Pixel(meter_per_pixel);
		TOM.Update_Scale((float)meter_per_pixel, (float)meter_per_pixel);
		Radar_Route.Update_Meter_Per_Pixel_For_Real_Time(meter_per_pixel);
	}
	// --------------------------------------------------
	//  Set_Step_Radar_Scale  
	//  Haim Otachi		06/03/2016
	// 	Description:	This function gets a request screen width in meter, and updates the 
	//					radar route with the appropriate meter_per_pixel.
	// 	Reference:		
	//  Input value:	the requested screen_width in meter
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Set_Step_Radar_Scale(double screen_width_meter)
	{
		double meter_per_pixel = screen_width_meter / SCREEN_SIZE_X;
		//---------------------------------------------------
		//			Update GUI_Status struct with new data 
		//---------------------------------------------------
		GUI_Status.Meter_Per_Pixel_Of_Viewer = meter_per_pixel;
		GUI_Status.Screen_Width_Of_Viewer = (int)screen_width_meter;
		//---------------------------------------------------
		//			Update the current position (some step) of the radar
		//---------------------------------------------------
		Radar_Route.Update_Meter_Per_Pixel_For_Real_Time(meter_per_pixel);
	}
	// --------------------------------------------------
	//  Set_Step_Viewer_Position  
	//  Haim Otachi		28/12/2015
	// 	Description:	This function gets the position of the bottom-left point of the 
	//					screen and updated the graphical elements (e.g., radar route).
	// 	Reference:		
	//  Input value:	the requested screen_bottom_left
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Set_Step_Viewer_Position(C_Position% screen_bottom_left)
	{
		//---------------------------------------------------
		//			Update GUI_Status struct with new data 
		//---------------------------------------------------
		GUI_Status.Viewer_GPS_Latitude = screen_bottom_left.Latitude;
		GUI_Status.Viewer_GPS_Longitude = screen_bottom_left.Longitude;
		//---------------------------------------------------
		//			Update the current position (some step) of the radar
		//---------------------------------------------------
		TOM.Set_Screen_In_UTM_Origin(screen_bottom_left);
		Radar_Route.Update_Screen_in_UTM_For_Real_Time(screen_bottom_left);
	}
	// --------------------------------------------------
	//  Set_Step_Radar_Position  
	//  Haim Otachi		06/03/2016
	// 	Description:	This function gets the position of the bottom-left point of the 
	//					screen and updated the radar route .
	// 	Reference:		
	//  Input value:	the requested screen_bottom_left
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Set_Step_Radar_Position(C_Position% screen_bottom_left)
	{
		//---------------------------------------------------
		//			Update the current position (some step) of the radar
		//---------------------------------------------------
		Radar_Route.Update_Screen_in_UTM_For_Real_Time(screen_bottom_left);
	}
	// --------------------------------------------------
	//  Update_RDM  
	//  Haim Otachi		31/12/2015
	// 	Description:	
	// 	Reference:		
	//  Input value:	the pointer to the 'RDM_View' from PictureBox^ type
	//  Return Value:	the function returns value if it's possible else returns zero
	// --------------------------------------------------
	double C_Radar_Viewer::Update_RDM(Point% RDM_Point)
	{
		return  RDM.Update_RDM(RDM_Point);
	}

	void C_Radar_Viewer::Add_Radar_Post()
	{
		Radar_Route.Add_New_Step_Radar_Post();
	}

	// --------------------------------------------------
	//  Erase_Line  
	//  Haim Otachi		03/11/2015
	// 	Description:	???
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Erase_Line()
	{
		//-------------------------------------------------------
		//	Define the pen: "pen_off" to erase the current line from the screen 
		//-------------------------------------------------------
		Pen^ pen_off = gcnew Pen(Color::Black);
		//-------------------------------------------------------
		//	We find the Point_mouse_move coordinate and convert him to PointF
		//-------------------------------------------------------
		PointF Point_Mouse_Move = PointF((float)(*Point_mouse_move).Screen_X, (float)(*Point_mouse_move).Screen_Y);
		//-------------------------------------------------------
		//	We find the Last_screen_point_of_wire coordinate and convert him to PointF
		//-------------------------------------------------------
		PointF Last_Screen_Point_Of_Wire = PointF((float)(*Last_screen_point_of_wire).Screen_X, SCREEN_SIZE_Y - (float)(*Last_screen_point_of_wire).Screen_Y);
		//-------------------------------------------------------
		//	We clear the line from the panel
		//-------------------------------------------------------
		Viewer_Panel_Graphics->DrawLine(pen_off, Last_Screen_Point_Of_Wire, Point_Mouse_Move);

		Start_wire_from_mouse = false;
	}
	// --------------------------------------------------
	//  Mouse_Move  
	//  Haim Otachi		03/11/2015
	// 	Description:	???
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Mouse_Move(int screen_x, int screen_y)
	{
		//-------------------------------------------------------
		//	
		//-------------------------------------------------------
		if (Start_wire_from_mouse)
		{
			//-------------------------------------------------------
			//	
			//-------------------------------------------------------
			Pen^ pen_on = gcnew Pen(Color::Orange);
			Pen^ pen_off = gcnew Pen(Color::Black);
			//-------------------------------------------------------
			//	We find the Point_mouse_move coordinate and convert him to PointF
			//-------------------------------------------------------
			PointF Point_Mouse_Move = PointF((float)(*Point_mouse_move).Screen_X, (float)(*Point_mouse_move).Screen_Y);
			//-------------------------------------------------------
			//	We find the Last_screen_point_of_wire coordinate and convert him to PointF
			//-------------------------------------------------------
			PointF Last_Screen_Point_Of_Wire = PointF((float)(*Last_screen_point_of_wire).Screen_X, SCREEN_SIZE_Y - (float)(*Last_screen_point_of_wire).Screen_Y);
			//-------------------------------------------------------
			//	We clean the Panel Graphics of simulator
			//-------------------------------------------------------
			Viewer_Panel_Graphics->DrawLine(pen_off, Last_Screen_Point_Of_Wire, Point_Mouse_Move);
			//-------------------------------------------------------
			//	Update the next point into: 'Point_Mouse_Move' and 'Point_mouse_move' 
			//-------------------------------------------------------
			Point_mouse_move->set_Object_in_Screen_Position(screen_x, screen_y);
			Point_Mouse_Move.X = (float)Point_mouse_move->Screen_X;
			Point_Mouse_Move.Y = (float)Point_mouse_move->Screen_Y;
			//-------------------------------------------------------
			//	plot wire to the screen
			//-------------------------------------------------------
			Viewer_Panel_Graphics->DrawLine(pen_on, Last_Screen_Point_Of_Wire, Point_Mouse_Move);
		}
	}
	// --------------------------------------------------
	//  Add_Pylon  
	//  Haim Otachi		03/11/2015
	// 	Description:	???
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Add_Pylon(int X_Pixel, int Y_Pixel)
	{
		C_Position New_Pylon_Position;
		New_Pylon_Position.set_Object_in_Screen_Position(X_Pixel, SCREEN_SIZE_Y - Y_Pixel);

		TOM.Add_Pylon(New_Pylon_Position);
		//-------------------------------------------------------
		//	Refresh wires and pylons plot
		//-------------------------------------------------------
		TOM.Plot_Obstacles_To_Screen();
	}
	// --------------------------------------------------
	//  Add_Wire  
	//  Haim Otachi		03/11/2015
	// 	Description:	???
	// 	Reference:		
	//  Input value:	
	//  Return Value:	
	// --------------------------------------------------
	void C_Radar_Viewer::Add_Wire(int X_Pixel, int Y_Pixel)
	{
		C_Position New_Wire_Position = *Point_mouse_move;
		New_Wire_Position.set_Object_in_Screen_Position(X_Pixel, SCREEN_SIZE_Y - Y_Pixel);

		if (Start_wire_from_mouse == true)
		{
			TOM.Add_Wire(*Last_screen_point_of_wire, New_Wire_Position);
		}

		TOM.Add_Pylon(New_Wire_Position);
		//-------------------------------------------------------
		//	Update the next point into: 'Last_screen_point_of_wire' and 'Point_mouse_move' 
		//-------------------------------------------------------
		*Last_screen_point_of_wire = New_Wire_Position;
		*Point_mouse_move = New_Wire_Position;
		Start_wire_from_mouse = true;
		//-------------------------------------------------------
		//	Refresh wires and pylons plot
		//-------------------------------------------------------
		TOM.Plot_Obstacles_To_Screen();
	}
	
	void C_Radar_Viewer::Offset_TOM_Array(float delta_pixels_x, float delta_pixels_y)
	{
		TOM.Offset_Array(delta_pixels_x, delta_pixels_y);
	}

	void C_Radar_Viewer::Offset_Radar_Position(float delta_pixels_x, float delta_pixels_y)
	{
		Radar_Route.Offset_Radar_Position(delta_pixels_x, delta_pixels_y);
	}
	#pragma endregion
}