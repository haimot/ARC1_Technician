// This is the main DLL file.
#include "C_Radar_Route.h"
//#include "C_Data_Recording.h"
#include "T_Trajectories.h"
//-----------------------------------------
//		Display
//-----------------------------------------
#define		SCREEN_SIZE_X					600
#define		SCREEN_SIZE_Y					600

#define		PI								3.14159265358979323846
#define		MAX_POSTS_IN_ROUTH				1000

#define		EXPERIMENT_DEF_FILE				"LOG.txt"
#define		EXPERIMENT_RECORDING_FILE		"data_recording.bin"

using namespace System::IO;
using std::ios;

//-------------------------------------
//		Constructor
//-------------------------------------
C_Radar_Route::C_Radar_Route()
{
	//-------------------------------------
	//	Initial the Radar_Post_array array 
	//-------------------------------------
	Radar_Post_array = gcnew array<C_Radar_Post^>(MAX_POSTS_IN_ROUTH);
	for (int i = 0; i < MAX_POSTS_IN_ROUTH; i++)
	{
		Radar_Post_array[i] = gcnew C_Radar_Post;
	}
	//-------------------------------------
	//	Null the data stracture indices
	//-------------------------------------
	index_to_post_in_the_Post_array = 0;
	number_of_posts_in_the_Post_array = 0;
	//-------------------------------------
	//	Initialize my help pointer
	//-------------------------------------
	Current_Radar_Post = Radar_Post_array[0];
	//-----------------------------------------
	//	Initialize Auxiliaries:  Data of Radar struct
	//-----------------------------------------
	Radar_Data = (T_Radar_Data*)malloc(sizeof(T_Radar_Data));
	//------------------------------------------
	// Initialize parameters
	//------------------------------------------
	Variance_Position_Wires = 0.0;
	Radar_Data->Radar_Delta_YAW = 0.0;
	Radar_Data->Radar_Initial_YAW = 0.0;
	Radar_Data->Radar_YAW = 0.0;
	Radar_Data->Time_Stamp = 0;
	//------------------------------------------
	// Initialize the border of screen
	//------------------------------------------
	Screen_Bottom_Left = C_Position();
	Screen_Top_Right = C_Position();
}
//-------------------------------------
//			Destructor
//-------------------------------------
C_Radar_Route::~C_Radar_Route()
{
	delete Radar_Post_array;
	delete Next_Radar_Post;
	delete Current_Radar_Post;

	if (Radar_Data != NULL)
	{
		delete Radar_Data;
		Radar_Data = NULL;
	}
}

#pragma region Set And Get functions
// --------------------------------------------------
//  get_Current_Radar_Position  
//  Haim Otachi			08/12/2015
// 	Description:		the function return the Current Radar Position of radar route			
// 	Reference: 
//  Input value:	
//  Return Value:		the Current Radar Position of radar route
// --------------------------------------------------
C_Position C_Radar_Route::Get_Current_Radar_Position()
{
	return Current_Radar_Post->Radar_Position;
}
// --------------------------------------------------
//  Get_Current_Radar_Post  
//  Haim Otachi			09/12/2015
// 	Description:		the function return the Current Radar Post of radar route			
// 	Reference: 
//  Input value:	
//  Return Value:		the Current Radar Post of radar route
// --------------------------------------------------
C_Radar_Post^ C_Radar_Route::Get_Current_Radar_Post()
{
	return Current_Radar_Post;
}
// --------------------------------------------------
//  Set_New_Route_Of_Radar  
//  Haim Otachi			08/12/2015
// 	Description:		the function update the situation of the radar i.e. 
//							- Route_New = true --> new fly of the radar.
//							- Route_New = false --> repeat fly of the radar.
// 	Reference: 
//  Input value:	
//  Return Value:		the current Time Stamp Of SENSOR data relative to new frame of video
// --------------------------------------------------
void C_Radar_Route::Set_New_Route_Of_Radar(bool route_new)
{
	Radar_Data->Route_New = route_new;
}
//-------------------------------------------
//		Set Next Radar Post
//-------------------------------------------
void C_Radar_Route::Set_Data_Of_Radar_Post(C_Lat_Lon_Map^ Next_Radar_Post_Other)
{
	Next_Radar_Post = Next_Radar_Post_Other;
}
//-------------------------------------------
//		Set: Show Detections
//-------------------------------------------
void C_Radar_Route::Set_Show_Detections(bool new_detections_status)
{
	for (int i = 0; i < number_of_posts_in_the_Post_array; ++i)
	{
		Radar_Post_array[i]->Set_Show_Detections(new_detections_status);
	}

	//Next_Radar_Post->Set_Show_Detections(new_detections_status);
	//Current_Radar_Post->Set_Show_Detections(new_detections_status);
}
//-------------------------------------------
//		Set: Show Trajectories
//-------------------------------------------
void C_Radar_Route::Set_Show_Trajectories(bool new_trajectories_status)
{
	for (int i = 0; i < number_of_posts_in_the_Post_array; ++i)
	{
		Radar_Post_array[i]->Set_Show_Trajectories(new_trajectories_status);
	}

	//Next_Radar_Post->Set_Show_Trajectories(new_trajectories_status);
	//Current_Radar_Post->Set_Show_Trajectories(new_trajectories_status);
}
//-------------------------------------------
//		for QA of error function
//-------------------------------------------
int C_Radar_Route::Get_Current_Number_Of_Post_In_Radar_Route()
{
	return number_of_posts_in_the_Post_array;
}

void C_Radar_Route::Set_Base_Meter_Per_Pixel_For_Scale(double meter_per_pixel_other)
{
	for (int i = 0; i < number_of_posts_in_the_Post_array; ++i)
	{
		Radar_Post_array[i]->Set_Base_Meter_Per_Pixel_For_Scale(meter_per_pixel_other);
	}
}
#pragma endregion

#pragma region Public Methods
// --------------------------------------------------
//  Initialization_Of_Radar_Route  
//  Haim Otachi		06/03/2016
// 	Description:					
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Initialize(Panel^ Route_Panel_Other, C_Position% Radar_routing_Position, C_GUI_Status% GUI_Status)
{
	//--------------------------------------------------
	//		Initialize the Viewer Panel and him Graphics
	//--------------------------------------------------
	Route_Panel = Route_Panel_Other;
	Route_Panel_Graphics = Route_Panel->CreateGraphics();
	//--------------------------------------------------
	//		Initial the radar post array of the radar route
	//--------------------------------------------------
	Initial_Radar_Position(Route_Panel_Other, Radar_routing_Position, GUI_Status.Max_Range_Error_Meter, GUI_Status.Reliability_Threshold);
	//-----------------------------------------
	//		Update the important parameter data of the current radar
	//-----------------------------------------
	*Radar_Data = GUI_Status.Radar_Data;
	//-----------------------------------------
	//		Update the Variance_Position_Wires 
	//-----------------------------------------
	Variance_Position_Wires = GUI_Status.Variance_Position_Wires;
}

// --------------------------------------------------
//  Current_Point_In_Screen  
//  Haim Otachi		08/12/2015
// 	Description:	the function check if radar position is located within the boundaries of the screen 		
// 	Reference: 
//  Input value:	
//  Return Value:	true / false
// --------------------------------------------------
bool C_Radar_Route::Current_Point_In_Screen()
{
	//-------------------------------------------
	//		we take the current UTM Coordinate of the Radar route 
	//-------------------------------------------
	double Radar_Longitude = Current_Radar_Post->Radar_Position.Longitude;
	double Radar_Latitude = Current_Radar_Post->Radar_Position.Latitude;
	//-------------------------------------------
	//		we take the current UTM Coordinate of the screen (border)
	//-------------------------------------------
	C_UTM_Coordinates Screen_Bottom_Left_In_UTM = Screen_Bottom_Left.get_Object_in_UTM_Position();
	C_UTM_Coordinates Screen_Top_Right_In_UTM = Screen_Top_Right.get_Object_in_UTM_Position();
	//-------------------------------------------
	//		we check if radar position is located within the boundaries of the screen 
	//-------------------------------------------
	if ((Radar_Longitude > Screen_Bottom_Left_In_UTM.Longitude) && (Radar_Longitude < Screen_Top_Right_In_UTM.Longitude) && (Radar_Latitude > Screen_Bottom_Left_In_UTM.Latitude) && (Radar_Latitude < Screen_Top_Right_In_UTM.Latitude))
	{
		return true;
}
return false;
}
// --------------------------------------------------
//  Load_From_File  
//  Haim Otachi		08/10/2015
// 	Description:	read the data_recirding.bin and translate to c_radar_route data structure				
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
bool C_Radar_Route::Load_From_File(char* experiment_folder)
{
	C_Data_Recording		detection;
	fstream					Recordings_file_handle;
	char					Log_File[MAX_STRING_LENGTH][MAX_STRING_LENGTH];
	//--------------------------------------
	//	Open the experiment LOG file
	//--------------------------------------
	char					experiment_file[MAX_STRING_LENGTH];
	sprintf_s(experiment_file, "%s\\%s", experiment_folder, EXPERIMENT_DEF_FILE);
	//---------------------------------------------------
	//		Read Data from LOG file to temp Data array
	//---------------------------------------------------
	std::fstream inFile(experiment_file);
	if (inFile.fail())
	{
		return false;
	}
	for (int i = 0; i < MAX_STRING_LENGTH; i++)
	{
		inFile.getline(Log_File[i], MAX_STRING_LENGTH);
	}
	inFile.close();
	//----------------------------------------------
	//   Check the experiment folder validity
	//----------------------------------------------
	if (Directory::Exists(gcnew String(experiment_folder)) == false)
	{
		return false;
	}
	//--------------------------------------
	//	Open the experiment data recording bin
	//--------------------------------------
	sprintf_s(experiment_file, "%s\\%s", experiment_folder, EXPERIMENT_RECORDING_FILE);
	Recordings_file_handle.open(experiment_file, std::ios::in | std::ios::binary);
	if (Recordings_file_handle.fail())
	{
		return false;
	}
	//-------------------------------------------
	//	 Initialize minimal point and maximal point
	//-------------------------------------------
	double min_Lat = 89.999999;					// Maximum possible lat
	double min_Lon = 179.999999;				// Maximum possible lon
	double min_Alt = 0;							// Maximum possible alt

	double max_Lat = -89.999999;				// Minimum possible lat
	double max_Lon = -179.999999;				// Minimum possible lon
	double max_Alt = 0;							// Minimum possible alt
	//---------------------------------------------------
	//	We calculate the 'RDM_size_int16' size
	//---------------------------------------------------	
	int RDM_size_int16 = Calc_RDM_Size(Log_File);
	//---------------------------------------------------	
	//	 We erase the pointer to the 'Radar_Post_Array' structure
	//---------------------------------------------------	
	Clear();
	//------------------------------------------------------
	//		Detections file --> Radar_Route (data structure)
	//------------------------------------------------------
	detection.Restart();
	pin_ptr<T_Radar_Massage> pinnedPtr_of_radar = detection.get_Radar_Massage();
	pin_ptr<T_Trajectories> pinnedPtr_of_trajectories = detection.get_Trajectories();

	Recordings_file_handle.clear();
	while (Recordings_file_handle.good())
	{
		//---------------------------------------------------
		//		Read target
		//---------------------------------------------------
		Recordings_file_handle.read((char*)(pinnedPtr_of_radar), sizeof(T_Radar_Massage));
		//---------------------------------------------------
		//		Read RDM points
		//---------------------------------------------------
		Recordings_file_handle.seekg(RDM_size_int16 * 2, ios::cur);
		//---------------------------------------------------
		//		Read Trajectories points
		//---------------------------------------------------
		Recordings_file_handle.read((char*)(pinnedPtr_of_trajectories), sizeof(T_Trajectories));
		//---------------------------------------------------
		//		update the current of Radar_Position coordinate
		//---------------------------------------------------
		Radar_Post_array[number_of_posts_in_the_Post_array]->Add_Radar_Post(*pinnedPtr_of_radar, *pinnedPtr_of_trajectories);
		number_of_posts_in_the_Post_array++;
		//-------------------------------------------
		//	update the current radar post value to new value	
		//-------------------------------------------
		Update_Current_Radar_Post();
		//---------------------------------------------------
		//		find LON/LAT range
		//---------------------------------------------------
		if (pinnedPtr_of_radar->SENSOR_data.Latitude > max_Lat)
		{
			max_Lat = pinnedPtr_of_radar->SENSOR_data.Latitude;
		}
		if (pinnedPtr_of_radar->SENSOR_data.Longitude > max_Lon)
		{
			max_Lon = pinnedPtr_of_radar->SENSOR_data.Longitude;
		}
		if (pinnedPtr_of_radar->SENSOR_data.Latitude < min_Lat)
		{
			min_Lat = pinnedPtr_of_radar->SENSOR_data.Latitude;
		}
		if (pinnedPtr_of_radar->SENSOR_data.Longitude < min_Lon)
		{
			min_Lon = pinnedPtr_of_radar->SENSOR_data.Longitude;
		}
		if (pinnedPtr_of_radar->SENSOR_data.Altitude > max_Alt)
		{
			max_Alt = pinnedPtr_of_radar->SENSOR_data.Altitude;
		}
		if (pinnedPtr_of_radar->SENSOR_data.Altitude < min_Alt)
		{
			min_Alt = pinnedPtr_of_radar->SENSOR_data.Altitude;
		}
	}
	Recordings_file_handle.close();
	//-------------------------------------------
	//	   Update the Screen_Top_Right and Screen_Bottom_Left values
	//-------------------------------------------
	Screen_Top_Right.set_Object_in_UTM_Position(max_Lat, max_Lon, max_Alt);
	Screen_Bottom_Left.set_Object_in_UTM_Position(min_Lat, min_Lon, min_Alt);
	return true;
}
// --------------------------------------------------
//  Save_To_File  
//  Haim Otachi			08/10/2015
// 	Description:	The function translate from c_radar_route to data_recording.bin format and saves to file 			
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Save_To_File(char* file) {}
// --------------------------------------------------
//  Update_Meter_Per_Pixel
//  Haim Otachi     ???
// 	Description:	initalize the C_POSITION reference parameters
//					Meter_Per_Pixel
// 	Reference:		
//  Input value:	Meter_Per_Pixel
//  Return Value:	
// --------------------------------------------------
void C_Radar_Route::Update_Meter_Per_Pixel(double Meter_Per_Pixel_Other)
{
	for (int i = 0; i < number_of_posts_in_the_Post_array; i++)
	{
		Radar_Post_array[i]->Update_Meter_Per_Pixel(Meter_Per_Pixel_Other);
	}

	Screen_Bottom_Left.set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
	Screen_Top_Right.set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
}
// --------------------------------------------------
//  Update_Screen_in_UTM
//  Haim Otachi     ???
// 	Description:	initalize the C_POSITION reference parameters
//					Screen_in_UTM
// 	Reference:		
//  Input value:	UTM values of the screen origin
//  Return Value:	
// --------------------------------------------------
void C_Radar_Route::Update_Screen_in_UTM(C_Position% Screen_Bottom_Left_Other)
{
	for (int i = 0; i < number_of_posts_in_the_Post_array; i++)
	{
		Radar_Post_array[i]->Update_Screen_in_UTM(Screen_Bottom_Left_Other);
	}
	Screen_Bottom_Left.set_Screen_in_UTM_Position(Screen_Bottom_Left_Other.get_Object_in_UTM_Position());
	Screen_Top_Right.set_Screen_in_UTM_Position(Screen_Bottom_Left_Other.get_Object_in_UTM_Position());
}
// --------------------------------------------------
//  Update_Current_SENSOR_Data_Of_Radar_Post
//  Haim Otachi     10/08/2015
// 	Description:	???					
// 	Reference:		
//  Input value:	
//  Return Value:	
// --------------------------------------------------
T_SENSOR_data C_Radar_Route::Update_Current_SENSOR_Data_Of_Radar_Post()
{
	double Radar_YAW = Radar_Data->Radar_YAW;

	Current_Radar_Post->sensor_data->time = Radar_Data->Time_Stamp;
	Current_Radar_Post->sensor_data->Latitude = Current_Radar_Post->Radar_Position.Latitude;
	Current_Radar_Post->sensor_data->Longitude = Current_Radar_Post->Radar_Position.Longitude;
	Current_Radar_Post->sensor_data->Altitude = Current_Radar_Post->Radar_Position.Altitude;

	Current_Radar_Post->sensor_data->ATT_ROLL = 0;
	Current_Radar_Post->sensor_data->ATT_PITCH = 0;
	Current_Radar_Post->sensor_data->ATT_YAW = Radar_YAW;

	Current_Radar_Post->sensor_data->VelocityX = Radar_YAW * sin(Radar_YAW * PI / 180);
	Current_Radar_Post->sensor_data->VelocityY = Radar_YAW * cos(Radar_YAW * PI / 180);
	Current_Radar_Post->sensor_data->VelocityZ = 0;

	return Current_Radar_Post->SENSOR_data;
}
// --------------------------------------------------
//  Move_To_Next_Point
//  Haim Otachi     03/11/2015
// 	Description:    the function calculate the next point of the radar and update this point in the radar_route array of the radar				
// 	Reference:		
//  Input value:	
//  Return Value:	
// --------------------------------------------------
C_Position C_Radar_Route::Calc_The_Next_Point()
{
	//-----------------------------------------------------------
	//			if the New Route is active
	//-----------------------------------------------------------
	if (Radar_Data->Route_New == true)
	{
		C_Position position;
		//-----------------------------------------------------------
		//			initial the position object
		//-----------------------------------------------------------
		position = Current_Radar_Post->Radar_Position;
		//-----------------------------------------------------------
		//			calculate the new point 
		//-----------------------------------------------------------
		position += Calc_Next_point();
		//-----------------------------------------------------------
		//		    Update the current Radar_North
		//-----------------------------------------------------------
		position.set_Radar_in_UTM_North(Radar_Data->Radar_YAW);
		Screen_Bottom_Left.set_Radar_in_UTM_North(Radar_Data->Radar_YAW);
		//-----------------------------------------------------------
		//			Add the new point to the Radar route array
		//-----------------------------------------------------------
		Add_Radar_Post(position);
	}
	//-----------------------------------------------------------
	//			if the Repeat Route is active
	//-----------------------------------------------------------
	else
	{
		//-----------------------------------------------------------
		//		    Update the current Radar_North
		//-----------------------------------------------------------
		double Radar_YAW = Radar_Post_array[number_of_posts_in_the_Post_array]->Radar_in_UTM_North;
		Screen_Bottom_Left.set_Radar_in_UTM_North(Radar_YAW);
		//-----------------------------------------------------------
		//			increase the pointer to Radar route array without make operation
		//-----------------------------------------------------------
		Add_Radar_Post();
	}
	//-----------------------------------------------------------
	//		we return the current position of the radar
	//-----------------------------------------------------------
	return Current_Radar_Post->Radar_Position;
}
// --------------------------------------------------
//  Plot_Radar_Post
//  Haim Otachi     ???
// 	Description:	Diplay Position and detections on screen
// 	Reference:		
//  Input value:	
//					1. Pointer to Graphics element to diaply on
//					2. Index to the number of post
//  Return Value:	
// --------------------------------------------------
void C_Radar_Route::Plot_Radar_Post()
{
	Pen^ Pen_helicopter = gcnew Pen(Color::Red);

	int Radar_Screen_X = Radar_Post_array[index_to_post_in_the_Post_array]->Radar_Position.Screen_X;
	int Radar_Screen_Y = Radar_Post_array[index_to_post_in_the_Post_array]->Radar_Position.Screen_Y;

	if ((Radar_Screen_X > 0) && (Radar_Screen_X < SCREEN_SIZE_X) && (Radar_Screen_Y > 0) && (Radar_Screen_Y < SCREEN_SIZE_Y))
	{
		//---------------------------------------------------
		//		Plot Radar to the screen
		//---------------------------------------------------	
		Route_Panel_Graphics->DrawRectangle(Pen_helicopter, Radar_Screen_X - 4, SCREEN_SIZE_Y - (Radar_Screen_Y - 4), 8, 8);
		//---------------------------------------------------
		//		Plot The detections of the radar
		//---------------------------------------------------
		//Radar_Post_array[index_to_post_in_the_Post_array]->Plot_Detections_To_Screen();
	}
}
// --------------------------------------------------
//  Plot_Next_Radar_Post
//  Haim Otachi     09/12/2015
// 	Description:	Diplay route on screen
// 	Reference:		
//  Input value:	
//  Return Value:	true if post can be displayed (posts linked list has not ended)
//					false if posts limked list has ended.
// --------------------------------------------------
bool C_Radar_Route::Move_To_Next_Radar_Post()
{
	if (index_to_post_in_the_Post_array < number_of_posts_in_the_Post_array)
	{ 
		//---------------------------------------------------
		//		Plot the current radar post
		//---------------------------------------------------
		Next_Radar_Post->Set_Radar_Post(Radar_Post_array[index_to_post_in_the_Post_array]);
		//---------------------------------------------------
		//		increase the pointer to the current radar post array
		//---------------------------------------------------
		index_to_post_in_the_Post_array++;
		return true;
	}
	else
	{
		index_to_post_in_the_Post_array = 0;
		return false;
	}
}
// --------------------------------------------------
//  Add_Radar_Post  
//  Haim Otachi			11/10/2015
// 	Description:		We are increasing in 1 the size of 'Radar_Post_array' array 					
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Add_Radar_Post()
{
	index_to_post_in_the_Post_array++;
	number_of_posts_in_the_Post_array++;

	Update_Current_Radar_Post();
}
// --------------------------------------------------
//  Add_Radar_Post  
//  Haim Otachi		17/09/2015
// 	Description: 					
// 	Reference: 
//  Input value:	Pointer to the radar message
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Add_Radar_Post(C_Position% Add_Radar_Post)
{
	//-------------------------------------------
	//	we add new position of the radar to the data base 
	//-------------------------------------------
	Radar_Post_array[number_of_posts_in_the_Post_array]->Radar_Position = Add_Radar_Post;
	//-------------------------------------------
	//	we update the pointer to the size of the data base 
	//  (increase the size of data base)
	//-------------------------------------------
	number_of_posts_in_the_Post_array++;
	//-------------------------------------------
	//	update the current radar post value to new value	
	//-------------------------------------------
	Update_Current_Radar_Post();
}
// --------------------------------------------------
//  Add_Obstacle_Position  
//  Haim Otachi			10/10/2015
// 	Description:		The function adds new Obstacle of the current point of radar route
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Add_Obstacle_Position(C_Position% Obstacle_Position_Other)
{
	Current_Radar_Post->Add_Obstacle(Obstacle_Position_Other);
}

bool C_Radar_Route::Calc_Detect_Pylon(C_Obstacles_Map% TOM, C_Position% target_PNI)
{
	//---------------------------------------------------
	//		Check if target is detectable
	//---------------------------------------------------
	if (Is_Pylon_Detectable(TOM, target_PNI) == true)
	{
		//---------------------------------------------------
		//		Save the data of target_PNI of current obstacle that was detected as a Pylon
		//---------------------------------------------------
		Current_Radar_Post->Add_Detection((PI / 2)*(180 / PI), target_PNI.Get_Azimuth(), target_PNI.Get_Range(), 100.0);
		return true;
}
return false;
}

bool C_Radar_Route::Calc_Detect_Wire(C_Obstacles_Map% TOM, C_Position% target_PNI)
{
	//---------------------------------------------------
	//		Check if target is detectable
	//---------------------------------------------------
	if (Is_Wire_Detectable(TOM, target_PNI) == true)
	{
		//---------------------------------------------------
		//		Save the data of target_PNI of current obstacle that was detected as a Wire
		//---------------------------------------------------
		Current_Radar_Post->Add_Detection(0, target_PNI.Get_Azimuth(), target_PNI.Get_Range(), 100.0);
		return true;
}
return false;
}
// --------------------------------------------------
//  Calc_Border_Screen  
//  Haim Otachi			31/10/2015
// 	Description:		The function calculate the border of the screen relative to radar route
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Initialize_Screen_Border()
{
	//---------------------------------------------------
	//		Initialize Screen Border: Screen borders to UTM: Note, Y=0 at the top side and increases to the bottom side
	//---------------------------------------------------
	Screen_Bottom_Left = Calc_Border_Bottom_Left();
	Screen_Top_Right = Calc_Border_Top_Right();
}
// --------------------------------------------------
//  Calc_First_Point  
//  Haim Otachi		31/10/2015
// 	Description:	Calc the First Point for the helicopter
// 	Reference:		
//  Input value:	
//  Return Value:	
// --------------------------------------------------
void C_Radar_Route::Calc_First_Point()
{
	C_Position position = Screen_Bottom_Left;
	//---------------------------------------------------
	//	 we clear the important parameter of the radar edge for the calculate the first point 
	//---------------------------------------------------
	Clear_Radar_Data();
	////---------------------------------------------------
	////	 initialize the pointer to the 'radar_route' structure
	////---------------------------------------------------
	//index_to_post_in_the_Post_array = 0;
	//---------------------------------------------------
	//	 calculate the first screen coordinates position to the first point of the radar
	//---------------------------------------------------
	position.set_Object_in_Screen_Position(Generate_Initial_Data());
	//---------------------------------------------------
	//	 update the current first point of the radar in the array
	//---------------------------------------------------
	Add_Radar_Post(position);
}
//// --------------------------------------------------
////  Calc_Video_Frame_Time_Sec  
////  Haim Otachi		31/10/2015
//// 	Description:	???
//// 	Reference:		
////  Input value:	
////  Return Value:	
//// --------------------------------------------------
//int C_Radar_Route::Calc_Video_Frame_Time_Sec()
//{
//	return GPS_TOW_to_UTC((int)(Current_Radar_Post->SENSOR_data.time));
//}
// --------------------------------------------------
//  Calc_False_Alarm  
//  Haim Otachi		01/11/2015
// 	Description:	???
// 	Reference:		
//  Input value:	
//  Return Value:	
// --------------------------------------------------
void C_Radar_Route::Calc_False_Alarm() {}
// --------------------------------------------------
//  Clear  
//  Haim Otachi			20/09/2015
// 	Description:	The function clear the Radar_Post_array 				
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Clear()
{
	index_to_post_in_the_Post_array = 0;
	number_of_posts_in_the_Post_array = 0;
	//-------------------------------------
	//	Null (max/min possible values) the coordinates range
	//-------------------------------------
	Screen_Bottom_Left = C_Position();
	Screen_Top_Right = C_Position();
}
// --------------------------------------------------
//  Restart  
//  Haim Otachi			08/10/2015
// 	Description:		The function restarts the index of the data structure Radar_Post_array 					
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Restart()
{
	index_to_post_in_the_Post_array = 0;
}
#pragma endregion

#pragma region Private Methods
// --------------------------------------------------
//  set_Initial_Radar_Position  
//  Haim Otachi			08/10/2015
// 	Description:		The function init the objects:  Screen_Bottom_Left and Screen_Top_Right					
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Initial_Radar_Position(Panel^ Route_Panel_Other, C_Position% Radar_routing_Position, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other)
{
	//-----------------------------------------------------------
	//			
	//-----------------------------------------------------------
	index_to_post_in_the_Post_array = 0;
	while (Radar_Post_array[index_to_post_in_the_Post_array]->Initialize(Route_Panel_Other, Radar_routing_Position, Max_Range_Error_Meter_Other, Reliability_Threshold_Other) == true)
	{
		//-----------------------------------------------------------
		//			initialize the 'Screen_Bottom_Left'
		//-----------------------------------------------------------
		//Screen_Bottom_Left = Radar_routing_Position;
		//-----------------------------------------------------------
		//			
		//-----------------------------------------------------------
		if (index_to_post_in_the_Post_array < MAX_POSTS_IN_ROUTH - 1)
		{
			index_to_post_in_the_Post_array++;
		}
		else
		{
			//-----------------------------------------------------------
			//	restart the used in radar_post_array and his pointer to his first cell
			//-----------------------------------------------------------
			index_to_post_in_the_Post_array = 0;
			break;
		}
	}
}
// --------------------------------------------------
//  Calc_Next_point  
//  Haim Otachi			28/10/2015
// 	Description:		The function calculate the next point of the radar on the screen		
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
C_CartesianPoint C_Radar_Route::Calc_Next_point()
{
	C_CartesianPoint position;
	C_CartesianPoint offset;

	int Radar_Refresh_Time = Radar_Data->Radar_Refresh_Time;
	int Radar_Speed = Radar_Data->Radar_Speed;
	float Radar_Delta_YAW = Radar_Data->Radar_Delta_YAW;
	float Radar_YAW = Radar_Data->Radar_YAW;
	//-----------------------------------------------------------
	//			calculate the new point 
	//-----------------------------------------------------------
	for (int i = 0; i < (int)(Radar_Speed / Radar_Refresh_Time); i++)
	{
		offset.set_point2D((double)(sin(Radar_YAW * PI / 180)), (double)(cos(Radar_YAW * PI / 180)));
		position += offset;
		//-----------------------------------------------------------
		//			update the Radar_YAW angle of simulator
		//-----------------------------------------------------------
		Radar_Data->Radar_YAW += Radar_Delta_YAW;
	}
	//-----------------------------------------------------------
	//			Update the Time_Stamp with new value
	//-----------------------------------------------------------
	Radar_Data->Time_Stamp += (float)(1.0 / Radar_Refresh_Time);
	return position;
}
// --------------------------------------------------
//  Is_Pylon_Detectable  
//  Haim Otachi			28/10/2015
// 	Description:		???				
// 	Reference: 
//  Input value:	    True obstacles map (TOM) and the target_PNI value
//  Return Value:		True or False
// --------------------------------------------------
bool C_Radar_Route::Is_Pylon_Detectable(C_Obstacles_Map% TOM, C_Position% target_PNI)
{
	int Radar_FOV = Radar_Data->Radar_FOV;
	int Radar_Max_Range = Radar_Data->Radar_Max_Range;

	target_PNI = TOM.Get_Pylon_1();
	//---------------------------------------------------
	//		Check if target is in radar FOV
	//---------------------------------------------------
	bool If_Target_is_in_RADAR_FOV = Current_Radar_Post->Target_is_in_RADAR_FOV(target_PNI, Radar_Max_Range, Radar_FOV, Variance_Position_Wires);
	if (If_Target_is_in_RADAR_FOV == true)
	{
		return true;
	}
return false;
}
// --------------------------------------------------
//  Is_Wire_Detectable  
//  Haim Otachi			28/10/2015
// 	Description:		???				
// 	Reference: 
//  Input value:	    True obstacles map (TOM) and the target_PNI value
//  Return Value:		True or False
// --------------------------------------------------
bool C_Radar_Route::Is_Wire_Detectable(C_Obstacles_Map% TOM, C_Position% target_PNI)
{
	int Radar_FOV = Radar_Data->Radar_FOV;
	int Radar_Max_Range = Radar_Data->Radar_Max_Range;

	C_Position Pylon_1 = TOM.Get_Pylon_1();
	C_Position Pylon_2 = TOM.Get_Pylon_2();
	//---------------------------------------------------
	//		Check if there is a PNI on the wire
	//---------------------------------------------------
	if (Current_Radar_Post->Line_angle(Pylon_1, Pylon_2) == true)
	{
		//---------------------------------------------------
		//		Get the PNI position
		//---------------------------------------------------
		target_PNI = Current_Radar_Post->Radar_Position;
		target_PNI = target_PNI.Line_point_projection(Pylon_1, Pylon_2);
		//---------------------------------------------------
		//		Check if target is in radar FAV
		//---------------------------------------------------
		bool If_Target_is_in_RADAR_FOV = Current_Radar_Post->Target_is_in_RADAR_FOV(target_PNI, Radar_Max_Range, Radar_FOV, Variance_Position_Wires);
		if (If_Target_is_in_RADAR_FOV == true)
		{
			return true;
		}
	}
	return false;
}
// --------------------------------------------------
//  Update_Current_Radar_Post  
//  Haim Otachi			28/10/2015
// 	Description:		The function update all the time the value of current radar post = Radar_Post_array[number_of_posts_in_the_Post_array - 1]
//					
// 	Reference: GPS_TOW_to_UTC
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Update_Current_Radar_Post()
{
	Current_Radar_Post = Radar_Post_array[number_of_posts_in_the_Post_array - 1];
}
// --------------------------------------------------
//  Clear_Radar_Data  
//  Haim Otachi			28/10/2015
// 	Description:		The function clear the part of 'Radar_Data' struct fields
//					
// 	Reference: GPS_TOW_to_UTC
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Route::Clear_Radar_Data()
{
	Radar_Data->Radar_Delta_YAW = 0.0;
	Radar_Data->Radar_Delta_YAW = 0.0;
	Radar_Data->Radar_YAW = 0.0;

	Radar_Data->Time_Stamp = 0.0;
}
// --------------------------------------------------
//  Generate_Initial_Data  
//  Haim Otachi				07/10/2015
// 	Description:			The function generate the first value of 'Radar_Initial_YAW' and 'Radar_Delta_YAW'
// 	Reference:		
//  Input value:	
//  Return Value:	
// --------------------------------------------------
C_Point2DInt C_Radar_Route::Generate_Initial_Data()
{
	C_Point2DInt point_other;

	Radar_Data->Radar_Initial_YAW = atan((float)((rand() % 100) - 50) / 1000) * 10;
	Radar_Data->Radar_Delta_YAW = (float)((rand() % 100) - 50) / 5000;
	point_other.set_Point(SCREEN_SIZE_X / 2 + (rand() % 100) - 50, 5);
	Radar_Data->Time_Stamp = 0;

	return point_other;
}
// --------------------------------------------------
//  Calc_Border_Top_Right  
//  Haim Otachi				28/10/2015
// 	Description:			The function calc the border of top right of the screen
// 	Reference:		
//  Input value:	
//  Return Value:	
// --------------------------------------------------
C_Position C_Radar_Route::Calc_Border_Top_Right()
{
	C_Position position;
	position = Radar_Post_array[0]->Radar_Position;
	position.set_Object_in_Screen_Position(SCREEN_SIZE_X, SCREEN_SIZE_Y);

	return position;
}
// --------------------------------------------------
//  Calc_Border_Bottom_Left  
//  Haim Otachi				28/10/2015
// 	Description:			The function calc the border of bottom left of the screen
// 	Reference:		
//  Input value:	
//  Return Value:	
// --------------------------------------------------
C_Position C_Radar_Route::Calc_Border_Bottom_Left()
{
	C_Position position;
	position = Radar_Post_array[0]->Radar_Position;
	position.set_Object_in_Screen_Position(0, 0);

	return position;
}
// --------------------------------------------------
//  Calc_RDM_Size  
//  Haim Otachi			08/10/2015
// 	Description:		calculate the size of the RDM from the experimaent log file
// 	Reference: 
//  Input value:	
//  Return Value:	RDM FILE
// --------------------------------------------------
int C_Radar_Route::Calc_RDM_Size(char file[MAX_STRING_LENGTH][MAX_STRING_LENGTH])
{
	int RDM_size_int16 = 0;

	try
	{
		//---------------------------------------------------
		//	We calculate the 'RDM_size_int16' size
		//---------------------------------------------------	
		int Maximal_doppler = Find_Value_In_File(file, "Maximal_doppler");
		int RANGE_samples = Find_Value_In_File(file, "RANGE_samples");
		int Range_decimation = Find_Value_In_File(file, "Range_decimation");
		if (Range_decimation != 0)
		{
			int decimated_range_samples = RANGE_samples / Range_decimation;
			RDM_size_int16 = Maximal_doppler * 2 * 2 * decimated_range_samples * 4;
		}
	}
		catch (Exception^ Ex) { Ex->Message; }
	//---------------------------------------------------
	//	return the RDM_size_int16 value
	//---------------------------------------------------
	return RDM_size_int16;
}
// --------------------------------------------------
//  Find_Line_In_File
//  Haim Otachi  17/09/2015
// 	Description:	
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
// the function find the index of line in file   //
// http://www.cplusplus.com/reference/string/string/find/
// http://www.cplusplus.com/reference/string/string/find_last_of/
//-----------------------------------------------//
int C_Radar_Route::Find_Line_In_File(char File[MAX_STRING_LENGTH][MAX_STRING_LENGTH], char* Line)
{
	// we save the current line input from user like a string
	std::string The_Input_Line = Line;
	int count = 0;
	for (int i = 0; i < MAX_STRING_LENGTH; i++)
	{
		std::string The_Current_Line = File[i];
		std::size_t found = The_Current_Line.find(The_Input_Line);
		if (found != std::string::npos)
		{
			return count;
		}
		else
		{
			count++;
		}
	}
	return -1;
}
// --------------------------------------------------
//  Find_Value_In_File
//  Haim Otachi  17/09/2015
// 	Description:	
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
// http://www.cplusplus.com/reference/string/string/substr/
// http://www.cplusplus.com/forum/general/13135/
// http://www.cplusplus.com/reference/string/string/length/
//-----------------------------------------------//
int C_Radar_Route::Find_Value_In_File(char File[MAX_STRING_LENGTH][MAX_STRING_LENGTH], char* Line)
{
	int index_of_line = Find_Line_In_File(File, Line);

	std::string The_Current_Line = File[index_of_line];
	std::string The_Input_Line = Line;
	int length = (int)The_Input_Line.length();
	std::string The_Number = The_Current_Line.substr(length);
	int Number = atoi(The_Number.c_str());

	return Number;
}
// --------------------------------------------------
//  Is_Empty
//  Haim Otachi		03/12/2015
// 	Description:	the function check if the border of the class: 'Screen_Bottom_Left' & 'Screen_Top_Right'
//					is equal to zero, and then intializes both with default parameters:
//					Screen_Bottom_Left = (89.999999, 179.999999, DBL_MAX)
//					Screen_Top_Right = (-89.999999, -179.999999, -DBL_MAX)
//					when:
//							1. 89.999999 -  Maximum possible latitude
//							2. 179.999999 - Maximum possible longitude
//
//							3. -89.999999 - Minimum possible latitude
//							4. -179.999999 - Minimum possible longitude
// 	Reference: 
//	Input Value:	
//  Return Value: 
//---------------------------------------------------
bool C_Radar_Route::Is_Empty()
{
	double Bottom_Latitude = Screen_Bottom_Left.Latitude;
	double Bottom_Longitude = Screen_Bottom_Left.Longitude;
	//---------------------------------------------------
	//	check if the 'Screen_Bottom_Left' is equal to Zero
	//---------------------------------------------------
	if (Bottom_Latitude != 0 && Bottom_Longitude != 0)
	{
		return false;
	}
	return true;
}

bool C_Radar_Route::Add_Radar_Post(T_Radar_Massage% Radar_Massage)
{
	//---------------------------------------------------
	//	Add new position of the radar (include his detections)
	//---------------------------------------------------
	if (Radar_Post_array[number_of_posts_in_the_Post_array]->Add_Radar_Post(Radar_Massage) == false)
	{
		return false;
	}
	//---------------------------------------------------
	//	increase the pointer to the array 
	//---------------------------------------------------
	number_of_posts_in_the_Post_array++;
	// --------------------------------------------------
	//			we find the minimum and maximum points of border
	// --------------------------------------------------
	Find_Min_Max();	
	return true;
}

bool C_Radar_Route::Add_Radar_Post(C_Data_Recording% Data_Recording_Other)
{
	//---------------------------------------------------
	//	Add new position of the radar (include his detections)
	//---------------------------------------------------	
	//if (Radar_Post_array[number_of_posts_in_the_Post_array]->Add_Radar_Post(*Data_Recording_Other.get_Radar_Massage()) == false)
	if (Radar_Post_array[number_of_posts_in_the_Post_array]->Add_Radar_Post(*Data_Recording_Other.get_Radar_Massage(), *Data_Recording_Other.get_Trajectories()) == false)
	{
		return false;
	}
	//---------------------------------------------------
	//	increase the pointer to the array 
	//---------------------------------------------------
	number_of_posts_in_the_Post_array++;
	// --------------------------------------------------
	//			we find the minimum and maximum points of border
	// --------------------------------------------------
	Find_Min_Max();
	return true;
}

void C_Radar_Route::Find_Min_Max()
{
	//-------------------------------------------
	//	 Initialize minimal and maximal point
	//-------------------------------------------
	double min_Lat = 89.999999; // Maximum possible lat
	double min_Lon = 179.999999; // Maximum possible lon
	double min_Alt = 0;

	double max_Lat = -89.999999; // Minimum possible lat
	double max_Lon = -179.999999; // Minimum possible lon
	double max_Alt = 0;
	//-------------------------------------------
	//	 we run on the data base
	//-------------------------------------------
	for (int i = 0; i < number_of_posts_in_the_Post_array; i++)
	{
		//-------------------------------------------
		//		find the minimum and maximum of current point
		//-------------------------------------------
		Radar_Post_array[i]->Find_Min_Max(max_Lat, max_Lon, min_Lat, min_Lon);
	}
	//-------------------------------------------
	//	 Finalizing: Updating the border of the screen relative the minimum and maximum in UTM coordinate unit
	//-------------------------------------------
	Screen_Top_Right.set_Object_in_UTM_Position(max_Lat, max_Lon, max_Alt);
	Screen_Bottom_Left.set_Object_in_UTM_Position(min_Lat, min_Lon, min_Alt);
}
#pragma endregion

#pragma region Real Time Functions 
void C_Radar_Route::Add_New_Step_Radar_Post()
{
	//-------------------------------------------
	//	we update the pointer to the size of the data base 
	//  (increase the size of data base)
	//-------------------------------------------
	number_of_posts_in_the_Post_array++;
	//-------------------------------------------
	//	update the current radar post value to new value	
	//-------------------------------------------
	Update_Current_Radar_Post();
}
// --------------------------------------------------
//  Move_To_Next_Step_Radar_Post
//  Haim Otachi     09/12/2015
// 	Description:	Diplay current step of radar on screen
// 	Reference:		
//  Input value:	
//  Return Value:	true if post can be displayed (posts linked list has not ended)
//					false if posts limked list has ended.
// --------------------------------------------------
bool C_Radar_Route::Move_To_Next_Step_Radar_Post()
{
	if (index_to_post_in_the_Post_array < number_of_posts_in_the_Post_array)
	{
		//---------------------------------------------------
		//		Plot the current radar post
		//---------------------------------------------------
		Next_Radar_Post->Set_Radar_Post(Radar_Post_array[index_to_post_in_the_Post_array]);
		return true;
	}
	else
	{
		return false;
	}
}
// --------------------------------------------------
//  Update_Meter_Per_Pixel_For_Real_Time
//  Haim Otachi     14/01/2015
// 	Description:	initalize the C_POSITION reference parameters
//					Meter_Per_Pixel
// 	Reference:		
//  Input value:	Meter_Per_Pixel
//  Return Value:	
// --------------------------------------------------
void C_Radar_Route::Update_Meter_Per_Pixel_For_Real_Time(double Meter_Per_Pixel_Other)
{
	Radar_Post_array[0]->Update_Meter_Per_Pixel(Meter_Per_Pixel_Other);

	Screen_Bottom_Left.set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
	Screen_Top_Right.set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
}
// --------------------------------------------------
//  Update_Screen_in_UTM_For_Real_Time
//  Haim Otachi     14/01/2015
// 	Description:	initalize the C_POSITION reference parameters
//					Screen_in_UTM
// 	Reference:		
//  Input value:	UTM values of the screen origin
//  Return Value:	
// --------------------------------------------------
void C_Radar_Route::Update_Screen_in_UTM_For_Real_Time(C_Position% Screen_Bottom_Left_Other)
{
	Radar_Post_array[0]->Update_Screen_in_UTM(Screen_Bottom_Left_Other);
	Screen_Bottom_Left.set_Screen_in_UTM_Position(Screen_Bottom_Left_Other.get_Object_in_UTM_Position());
	Screen_Top_Right.set_Screen_in_UTM_Position(Screen_Bottom_Left_Other.get_Object_in_UTM_Position());
}

void C_Radar_Route::Set_Screen_Coordinates(int screen_x, int screen_y)
{
	Radar_Post_array[0]->Set_Screen_Coordinates(screen_x, screen_y);
}

void C_Radar_Route::Update_Screen_Position()
{
	for (int i = 0; i < number_of_posts_in_the_Post_array; ++i)
	{
		Radar_Post_array[i]->Update_Screen_Position();
	}
}

void C_Radar_Route::Offset_Radar_Position(float delta_pixels_x, float delta_pixels_y)
{
	for (int i = 0; i < number_of_posts_in_the_Post_array; ++i)
	{
		Radar_Post_array[i]->Offset_Radar_Position(delta_pixels_x, delta_pixels_y);
	}
}

void C_Radar_Route::Create_Radar_Route_Position()
{
	for (int i = 0; i < number_of_posts_in_the_Post_array; ++i)
	{
		Radar_Post_array[i]->Create_Radar_Shape();
		Radar_Post_array[i]->Create_Detection_Shape();
		Radar_Post_array[i]->Create_Trajectory_Shape();
	}
}



void C_Radar_Route::Update_Scale(float scale_x, float scale_y)
{
	for (int i = 0; i < number_of_posts_in_the_Post_array; ++i)
	{
		Radar_Post_array[i]->Update_Scale(scale_x, scale_y);
	}
}
#pragma endregion