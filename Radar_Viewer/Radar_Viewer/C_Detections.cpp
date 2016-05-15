#include <iomanip>      // std::setprecision
#include "C_Detections.h"
//-----------------------------------------
//		Display
//-----------------------------------------
#define			SCREEN_SIZE_X					600
#define			SCREEN_SIZE_Y					600

#define			OBSTACLE_PYLON					1
#define			OBSTACLE_WIRE					2
#define			OBSTACLE_UNKNOWN				3
#define			OBSTACLE_GROUND					4

#define			PYLON_SIZE_TRUE					5
//-----------------------------------------
//		Misc.
//-----------------------------------------
#define			COLOR_TRUE					   	Color::Black

#define			PI								3.14159265358979323846
//-------------------------------------
//			Default Constructor
//-------------------------------------
C_Detections::C_Detections() : obstacle_type(0), matching_index(0), reliability_threshold(0), max_error_range_meter(0)
{
	//-------------------------------------
	//			Data of first detection
	//-------------------------------------
	pylon_1 = C_Position();
	//-------------------------------------
	//			Data of second detection
	//-------------------------------------
	pylon_2 = C_Position();
	//-------------------------------------
	//			the PNI data op 'pylon' opr 'wire'
	//-------------------------------------
	PNI_Data_of_detection = (T_PNI*)malloc(sizeof(T_PNI));
	//---------------------------------------------------
	//		Initialize the color of the obstacles 
	//---------------------------------------------------
	Pen_target_pylon	=	gcnew Pen(Color::Blue);
	Pen_target_wire		=	gcnew Pen(Color::Yellow);
	Pen_target_unknown	=	gcnew Pen(Color::Green);
}
//-------------------------------------
//				Destructor
//-------------------------------------
C_Detections::~C_Detections()
{
	delete	Pen_target_pylon;
	delete	Pen_target_wire;
	delete	Pen_target_unknown;

	delete  PNI_Data_of_detection;
}

#pragma region Set/Get Methods
//--------------------------------------------------
// Update_Meter_Per_Pixel
// Haim Otachi		08/11/2015
// Description:		The function Update the Meter Per Pixel of Pylon and Wire objects
//				    (Pylon_1 and Pylon_2 of the radar)
// Reference: 
// Input Value:		New value of Meter Per Pixel
// Return Value: 
//--------------------------------------------------
void C_Detections::Set_Meter_Per_Pixel(double Meter_Per_Pixel_Other)
{
	//-------------------------------------------
	//	Update the Meter Per Pixel of first detection (Pylon_1)
	//-------------------------------------------
	pylon_1.set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
	//-------------------------------------------
	//	Update the Meter Per Pixel of second detection (Pylon_2)
	//-------------------------------------------
	pylon_2.set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
}
// --------------------------------------------------
//  Set_Screen_in_UTM
//  Haim Otachi		08/11/2015
// 	Description:	The function Update the Screen unit in UTM coordinate of Pylon and Wire objects
// 	Reference: 
//	Input Value:	New value of Screen unit of utm coordinate
//  Return Value: 
// --------------------------------------------------
void C_Detections::Set_Screen_In_UTM_Origin(C_Position% Screen_Bottom_Left_Other)
{
	//-------------------------------------------
	//	Update the Screen unit in UTM coordinate of first detection (Pylon_1)
	//-------------------------------------------
	pylon_1.set_Screen_in_UTM_Position(Screen_Bottom_Left_Other.get_Object_in_UTM_Position());
	//-------------------------------------------
	//	Update the Screen unit in UTM coordinate of second detection (Pylon_2)
	//-------------------------------------------
	pylon_2.set_Screen_in_UTM_Position(Screen_Bottom_Left_Other.get_Object_in_UTM_Position());
}
// --------------------------------------------------
//  Set_Radar_North
//  Haim Otachi		08/11/2015
// 	Description:	The function Update the Radar Yaw of the radar relative to 'Pylon' and 'Wire'
// 	Reference: 
//	Input Value:	New value of Radar Yaw
//  Return Value: 
// --------------------------------------------------
void C_Detections::Set_Radar_North(double Radar_North)
{
	//-------------------------------------------
	//	Update the Screen unit in UTM coordinate of first detection (Pylon_1)
	//-------------------------------------------
	pylon_1.set_Radar_in_UTM_North(Radar_North);
	//-------------------------------------------
	//	Update the Screen unit in UTM coordinate of second detection (Pylon_2)
	//-------------------------------------------
	pylon_2.set_Radar_in_UTM_North(Radar_North);
}
// --------------------------------------------------
//  Set_Radar_In_UTM_Position
//  Haim Otachi		08/11/2015
// 	Description:	The function Update the Radar Yaw of the radar relative to 'Pylon' and 'Wire'
// 	Reference: 
//	Input Value:	New value of Radar Yaw
//  Return Value: 
// --------------------------------------------------
void C_Detections::Set_Radar_In_UTM_Position(C_Position% Radar_In_UTM_Position)
{
	//-------------------------------------------
	//	Update the Screen unit in UTM coordinate of first detection (Pylon_1)
	//-------------------------------------------
	pylon_1.set_Radar_in_UTM_Position(Radar_In_UTM_Position.get_Object_in_UTM_Position());
	//-------------------------------------------
	//	Update the Screen unit in UTM coordinate of second detection (Pylon_2)
	//-------------------------------------------
	pylon_2.set_Radar_in_UTM_Position(Radar_In_UTM_Position.get_Object_in_UTM_Position());
}
// --------------------------------------------------
//  Property: Reliability  (Set/Get)
//  Haim Otachi     08/11/2015
// 	Description:	Set Reliability of detection
// 	Reference: 
//  Input value:	Reliability
//  Return Value: 
// --------------------------------------------------
double C_Detections::Get_Reliability() { return PNI_Data_of_detection->Target_reliability; }
void C_Detections::Set_Reliability(double Reliability)
{
	//-------------------------------------------
	//	Update the 'Reliability' of detection ('Pylon'/'Wire')
	//-------------------------------------------
	PNI_Data_of_detection->Target_reliability = Reliability;
}
// --------------------------------------------------
//  Get_Position_Of_Pylon_1  
//  Haim Otachi    09/11/2015
// 	Description:    
// 	Reference:		
//  Input value:    
//  Return Value:	the position of 'Pylon_1'
// --------------------------------------------------
C_Position C_Detections::Get_Pylon_1() { return pylon_1; }
// --------------------------------------------------
//  Get_Position_Of_Pylon_2  
//  Haim Otachi    09/11/2015
// 	Description:    
// 	Reference:		
//  Input value:    
//  Return Value:	the position of 'Pylon_2'
// --------------------------------------------------
C_Position C_Detections::Get_Pylon_2() { return pylon_2; }
// --------------------------------------------------
//  Get_Current_Obstacle_Type  
//  Haim Otachi    09/11/2015
// 	Description:    
// 	Reference:		
//  Input value:    
//  Return Value:	the Obstacle Type of the current obstacle map
// --------------------------------------------------
int C_Detections::Get_Obstacle_Type() { return obstacle_type; }
void C_Detections::Set_Obstacle_Type(int Obstacle_Type)
{
	//-------------------------------------------
	//	Update the 'Obstacle_Type' of detection ('Pylon' or 'Wire')
	//-------------------------------------------
	obstacle_type = Obstacle_Type;
}

int C_Detections::Get_Matching_Index() { return matching_index; }
void C_Detections::Set_Matching_Index(int Matching_Index) { matching_index = Matching_Index; }

void C_Detections::Set_Obstacle_Position(C_Position% Obstacle_Position_other)
{
	pylon_1 = Obstacle_Position_other;
	pylon_2 = Obstacle_Position_other;
}
//-------------------------------------------
//			Set/Get: Current Matching_Index_Of_Pylon_1
//-------------------------------------------
int C_Detections::Get_Matching_Index_Of_Pylon_1()
{
	return matching_index_of_pylon_1;
}
void C_Detections::Set_Matching_Index_Of_Pylon_1(int Matching_Index_Of_Pylon_1)
{
	matching_index_of_pylon_1 = Matching_Index_Of_Pylon_1;
}
//-------------------------------------------
//			Set/Get: Current Matching_Index_Of_Pylon_2
//-------------------------------------------
int C_Detections::Get_Matching_Index_Of_Pylon_2()
{
	return matching_index_of_pylon_2;
}
void C_Detections::Set_Matching_Index_Of_Pylon_2(int Matching_Index_Of_Pylon_2)
{
	matching_index_of_pylon_2 = Matching_Index_Of_Pylon_2;
}

Point^ C_Detections::operator=(C_Detections^ detections_other)
{
	Point^ point;
	point->X = pylon_1.Screen_X;
	point->Y = pylon_1.Screen_Y;
	return point;
}
#pragma endregion

#pragma region Public Methods
// -----------------------------------------------------------
//  Initialize  
//  Haim Otachi		09/11/2015
// 	Description:	initial the objects of the class with the first data of: 'Screen_In_UTM_Position' and 'Meter_PerPixel'
//					.............
// 	Reference: 
//  Input value:    Screen_Bottom_Left object
//  Return Value: 
// -----------------------------------------------------------
void C_Detections::Initialize(Panel^ Detection_Panel_Other, C_Position% Init_Screen_Bottom_Left, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other)
{
	//--------------------------------------------------
	//		Initialize the Viewer Panel and him Graphics
	//--------------------------------------------------
	Detection_Panel = Detection_Panel_Other;
	Detection_Panel_Graphics = Detection_Panel->CreateGraphics();
	//-------------------------------------------
	//	Initial the first point in screen_in_UTM coordinates and Meter_Per_Pixel
	//-------------------------------------------
	pylon_1 = Init_Screen_Bottom_Left;
	//-------------------------------------------
	//	Initial the second point in screen_in_UTM coordinates and Meter_Per_Pixel
	//-------------------------------------------
	pylon_2 = Init_Screen_Bottom_Left;
	//-------------------------------------------
	//	Initial the reliability threshold value for print 'Pylon' or 'Wire'
	//-------------------------------------------
	max_error_range_meter = Max_Range_Error_Meter_Other;
	//-------------------------------------------
	//	Initial the reliability threshold value for print 'Pylon' or 'Wire'
	//-------------------------------------------
	reliability_threshold = Reliability_Threshold_Other;
}
// --------------------------------------------------
//  Save_To_File  
//  Haim Otachi     08/11/2015
// 	Description:	the function save the data of 2 detections: Pylon_1 and Pylon_2
//                  in  the file
// 	Reference: 
//  Input value:	file_stream by fstream object
//  Return Value: 
// --------------------------------------------------
void C_Detections::Save_To_File(fstream% file_stream)
{
	// --------------------------------------------------
	//		Save to file the 'Obstacle Type' of detection
	// --------------------------------------------------
	file_stream << obstacle_type << '\t';
	// --------------------------------------------------
	//		Save to file the 'First point' of detection
	// --------------------------------------------------
	file_stream << std::fixed << std::setprecision(6) << pylon_1.Latitude << '\t' << std::fixed << std::setprecision(6) << pylon_1.Longitude << '\t';
	// --------------------------------------------------
	//		Save to file the 'Second point' of detection
	// --------------------------------------------------
	if (obstacle_type == OBSTACLE_PYLON)
	{
		file_stream << "00.000000" << '\t' << "00.000000" << '\t';
	}
	else if (obstacle_type == OBSTACLE_WIRE)
	{
		// --------------------------------------------------
		//		Save to file the 'First point' of detection
		// --------------------------------------------------
		file_stream << std::fixed << std::setprecision(6) << pylon_2.Latitude << '\t' << std::fixed << std::setprecision(6) << pylon_2.Longitude << '\t';
	}
	// --------------------------------------------------
	//		Write to file the 'Obstacle Reliability' of TOM
	// --------------------------------------------------
	file_stream << std::fixed << std::setprecision(0) << PNI_Data_of_detection->Target_reliability << '\n';
}
// --------------------------------------------------
//  Load_From_File  
//  Haim Otachi     07/12/2015
// 	Description:	the function load the data of 2 detections: Pylons and wires
//                  from the file
// 	Reference: 
//  Input value:	'file_name' - the path of the file that containers the TOM 
//  Return Value: 
// --------------------------------------------------
void C_Detections::Load_From_File(fstream% file_stream)
{
	int Obstacle_Type = 0;

	double Lat_from_file = 0;
	double Lon_from_file = 0;
	double Reliability_from_file = 0;
	//-------------------------------------------
	//	 Read the 'obstacle type' of the current object (Pylon/Wire) 
	//-------------------------------------------
	file_stream >> Obstacle_Type;
	obstacle_type = Obstacle_Type;
	//-------------------------------------------
	//	 Read the 'first point' from file
	//-------------------------------------------
	file_stream >> Lat_from_file >> Lon_from_file;
	pylon_1.set_Object_in_UTM_Position(Lat_from_file, Lon_from_file, 80);
	//-------------------------------------------
	//	 Read the 'second point' from file
	//-------------------------------------------
	if (obstacle_type == OBSTACLE_PYLON)
	{
		file_stream >> Lat_from_file >> Lon_from_file;
	}
	else if (obstacle_type == OBSTACLE_WIRE)
	{
		file_stream >> Lat_from_file >> Lon_from_file;
		pylon_2.set_Object_in_UTM_Position(Lat_from_file, Lon_from_file, 80);
	}
	//-------------------------------------------
	//	  Read and Update the 'Reliability_Threshold'
	//-------------------------------------------
	file_stream >> Reliability_from_file;
	PNI_Data_of_detection->Target_reliability = Reliability_from_file;
}
// -----------------------------------------------------------
//  Plot_Obstacles_To_Screen  
//  Haim Otachi		08/11/2015
// 	Description:	plot obstacles to screen
// 	Reference: 
//  Input value:
//  Return Value: 
// -----------------------------------------------------------
void C_Detections::Plot_Obstacles_To_Screen()
{
	//-------------------------------------------------------
	//	Check to see if the 'Reliability_Threshold' is enough reliable
	//-------------------------------------------------------
	if (PNI_Data_of_detection->Target_reliability >= reliability_threshold)
	{
		//-------------------------------------------------------
		//					Plot pylon
		//-------------------------------------------------------
		if (obstacle_type == OBSTACLE_PYLON)
		{
			Plot_Pylon();
		}
		//-------------------------------------------------------
		//					Plot wire
		//-------------------------------------------------------
		else if (obstacle_type == OBSTACLE_WIRE)
		{
			Plot_Wire();
		}
	}
}
// -----------------------------------------------------------
//  Plot_TOM_To_Screen  
//  Haim Otachi		17/04/2015
// 	Description:	plot TOM to screen
// 	Reference: 
//  Input value:
//  Return Value: 
// -----------------------------------------------------------
void C_Detections::Plot_TOM_To_Screen()
{
	//-------------------------------------------------------
	//	Check to see if the 'Reliability_Threshold' is enough reliable
	//-------------------------------------------------------
	if (PNI_Data_of_detection->Target_reliability >= reliability_threshold)
	{
		//-------------------------------------------------------
		//					Plot pylon
		//-------------------------------------------------------
		if (obstacle_type == OBSTACLE_PYLON)
		{
			Plot_Pylon();
		}
		//-------------------------------------------------------
		//					Plot wire
		//-------------------------------------------------------
		else if (obstacle_type == OBSTACLE_WIRE)
		{
			Plot_Wire();
		}
	}
}
//--------------------------------------------------
// Add_Pylon  
// Haim Otachi     08/11/2015
//	Description:    the function add new pylon to the system of EOM/TOM
//	Reference:		
// Input value:    new pylon of C_Position class
// Return Value:	
//--------------------------------------------------
void C_Detections::Add_Pylon(C_Position% New_Pylon)
{
	//---------------------------------
	//  define the 'Obstacle Type' of target
	//---------------------------------
	obstacle_type = OBSTACLE_PYLON;
	//---------------------------------
	//  Add the current point (Pylon)
	//---------------------------------
	pylon_1 = New_Pylon;
	PNI_Data_of_detection->Target_reliability = 100;
}
// --------------------------------------------------
//  Add_Wire  
//  Haim Otachi     08/11/2015
// 	Description:    the function add new Wire to the system of EOM/TOM
// 	Reference:		
//  Input value:    2 objects point of C_Position class: 'First_Point_Of_Pylon' and 'Second_Point_Of_Pylon'
//  Return Value:	
// --------------------------------------------------
void C_Detections::Add_Wire(C_Position% First_Point_Of_Pylon, C_Position% Second_Point_Of_Pylon)
{
	//---------------------------------
	//  define the 'Obstacle Type' of target
	//---------------------------------
	obstacle_type = OBSTACLE_WIRE;
	//---------------------------------
	//  Add the first point (Pylon)
	//---------------------------------	
	pylon_1 = First_Point_Of_Pylon;
	PNI_Data_of_detection->Target_reliability = 100;
	//---------------------------------
	//  Add the second point (Pylon)
	//---------------------------------
	pylon_2 = Second_Point_Of_Pylon;
	PNI_Data_of_detection->Target_reliability = 100;
}
// --------------------------------------------------
//  Add_Detection  
//  Haim Otachi		08/10/2015
// 	Description:	Set the detection position (C_POSITION) 
//					given rasdar position & heading, relative range and relative azimuth.
// 	Reference: 
//  Input value:	radar position, radar heading, relative range and relative azimuth
//  Return Value: 
// --------------------------------------------------
void C_Detections::Add_Detection(T_PNI% PNI, T_SENSOR_data% SENSOR_data)
{
	*PNI_Data_of_detection = PNI;
	double	estimated_azimuth = 0;
	//-------------------------------------------
	//		Calculate the Polarization of the Radar
	//-------------------------------------------
	if (145 < PNI.Polarization_ratio_L)
	{
		PNI.Polarization_ratio_L -= 180;
	}
	if (145 < PNI.Polarization_ratio_R)
	{
		PNI.Polarization_ratio_R -= 180;
	}
	double Average_Polarization = ((PNI.Polarization_ratio_L + PNI.Polarization_ratio_R) / 2) - SENSOR_data.ATT_ROLL;

	if (Average_Polarization > 180)
	{
		Average_Polarization -= 180;
	}
	if (Average_Polarization < 0)
	{
		Average_Polarization += 180;
	}
	//-------------------------------------------
	//		if Average_Polarization between (0,30) or (150,180) degrees
	//-------------------------------------------
	if ((Average_Polarization < 30) || (150 < Average_Polarization))
	{
		estimated_azimuth = PNI.Azimuth_H;
		obstacle_type = OBSTACLE_WIRE;
	}
	//-------------------------------------------
	//		if Average_Polarization between (30,60) or (120,150) degrees
	//-------------------------------------------
	else if ((Average_Polarization < 60) || (120 < Average_Polarization))
	{
		estimated_azimuth = (PNI.Azimuth_H + PNI.Azimuth_V) / 2;
		obstacle_type = OBSTACLE_UNKNOWN;
	}
	//-------------------------------------------
	//		if Average_Polarization between (60,120) degrees
	//-------------------------------------------
	else
	{
		estimated_azimuth = PNI.Azimuth_V;
		obstacle_type = OBSTACLE_PYLON;
	}
	//-------------------------------------------
	//		Update the UTM position of radar In Target field
	//-------------------------------------------
	pylon_1.set_Radar_in_UTM_Position(SENSOR_data.Latitude, SENSOR_data.Longitude, SENSOR_data.Altitude);
	//------------------------------------------
	//	Radar heading is to the defined as East = x = zero azimuth
	//	So we compensate by subtracting PI/2. Alon 24.9.2015.
	//------------------------------------------
	pylon_1.set_Radar_in_UTM_North(SENSOR_data.ATT_YAW *PI / 180.0);
	//------------------------------------------
	//	AoA in DSP is positive counter-clockwise. Alon 24.9.2015.
	//------------------------------------------
	pylon_1.set_Object_in_Spherica_Position(PNI.Range, PI / 2 - estimated_azimuth*PI / 180.0, PI / 2);
}
// --------------------------------------------------
//  Add_Detection  
//  Haim Otachi		08/10/2015
// 	Description:	Set the detection position (C_POSITION) 
//					given rasdar position & heading, relative range and relative azimuth.
// 	Reference: 
//  Input value:	Polarization, Azimuth, Range, Reliability (radar position, radar heading, relative range and relative azimuth)
//  Return Value: 
// --------------------------------------------------
void C_Detections::Add_Detection(double& Polarization, double& Azimuth, double& Range, double& Reliability)
{
	//-------------------------------------------
	//		Update the Polarization of the Radar
	//-------------------------------------------
	PNI_Data_of_detection->Polarization_ratio_L = Polarization;
	PNI_Data_of_detection->Polarization_ratio_R = Polarization;
	//-------------------------------------------
	//		Update the Azimuth of the Radar
	//-------------------------------------------
	PNI_Data_of_detection->Azimuth_H = Azimuth;
	PNI_Data_of_detection->Azimuth_V = Azimuth;
	//-------------------------------------------
	//		Update the Range of the Radar
	//-------------------------------------------
	PNI_Data_of_detection->Range = Range;
	//-------------------------------------------
	//		Update the Reliability of the Radar
	//-------------------------------------------
	PNI_Data_of_detection->Target_reliability = Reliability;
}
// --------------------------------------------------
//  Add_Trajectory  
//  Haim Otachi		02/03/2016
// 	Description:	???
//					
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_Detections::Add_Trajectory(T_Trajectory% Trajectory, T_SENSOR_data% SENSOR_data)
{
	//-------------------------------------------
	//		if current trajectory is exist
	//-------------------------------------------
	if (Trajectory.isEmpty == false)
	{
		double range = Trajectory.xEstVct[0];
		double estimated_azimuth = Trajectory.xEstVct[2];
		//double velocity	= Trajectory.xEstVct[1];
		//-------------------------------------------
		//		
		//-------------------------------------------
		//if (Trajectory.trjType == 1)
		if ((Trajectory.xEstVct[3] * 180 / PI < 30) || Trajectory.xEstVct[3] * 180 / PI >(180 - 30))
		{
			obstacle_type = OBSTACLE_WIRE;
		}
		//-------------------------------------------
		//		
		//-------------------------------------------
		else if 
			((Trajectory.xEstVct[3] / PI * 180 < (90 - 30)) || (Trajectory.xEstVct[3] / PI * 180 > (90 + 30)))
		{
			obstacle_type = OBSTACLE_GROUND;
		}
		else
		{
			obstacle_type = OBSTACLE_PYLON;
		}
		//else if (Trajectory.trjType == 2)
		//{
		//	obstacle_type = OBSTACLE_PYLON;
		//}
		////-------------------------------------------
		////		
		////-------------------------------------------
		//else	//(Trajectory.trjType == 3)
		//{
		//	obstacle_type = OBSTACLE_GROUND;
		//}
		// Wire
		//	if (Trajectory.xEstVct[3] / pi * 180 < H_ploarization_degs) || (Trajectory.xEstVct[3] / pi * 180 > (180 - H_ploarization_degs))
		//		tragectories_array_raw(tragectories_counter_raw, 3) = 2;
		// non _target
		//	else if(Trajectory.xEstVct[3] / pi * 180 < (90 - V_ploarization_degs)) || (xEstVct(frame_counter, i, 4) / pi * 180 > (90 + V_ploarization_degs))
		//	tragectories_array_raw(tragectories_counter_raw, 3) = 3;
		//
		// Pylon
		//
		//	else
		//	tragectories_array_raw(tragectories_counter_raw, 3) = 1;
		//-------------------------------------------
		//		Update the UTM position of radar In Target field
		//-------------------------------------------
		pylon_1.set_Radar_in_UTM_Position(SENSOR_data.Latitude, SENSOR_data.Longitude, SENSOR_data.Altitude);
		//------------------------------------------
		//	Radar heading is to the defined as East = x = zero azimuth
		//	So we compensate by subtracting PI/2. Alon 24.9.2015.
		//------------------------------------------
		pylon_1.set_Radar_in_UTM_North(SENSOR_data.ATT_YAW *PI / 180.0);
		//------------------------------------------
		//	AoA in DSP is positive counter-clockwise. Alon 24.9.2015.
		//  estimated_azimuth - in radian.
		//------------------------------------------
		pylon_1.set_Object_in_Spherica_Position(range, PI/2 - estimated_azimuth , PI / 2);
	}
}

void C_Detections::Plot_Detection_To_Screen()
{
	//-------------------------------------------
	//	We find the screen coordinates of the current target
	//-------------------------------------------
	int Detection_Screen_X = pylon_1.Screen_X;
	int Detection_Screen_Y = pylon_1.Screen_Y;

	if ((Detection_Screen_X > 0) && (Detection_Screen_X < SCREEN_SIZE_X) && (Detection_Screen_Y > 0) && (Detection_Screen_Y < SCREEN_SIZE_Y))
	{
		if (PNI_Data_of_detection->Range > max_error_range_meter && PNI_Data_of_detection->Target_reliability >= reliability_threshold)
		{
			//---------------------------------------------------
			//		Plot target
			//---------------------------------------------------	
			switch (obstacle_type)
			{
				case OBSTACLE_PYLON:
					Detection_Panel_Graphics->DrawRectangle(Pen_target_pylon, Detection_Screen_X - 5, SCREEN_SIZE_Y - (Detection_Screen_Y - 5), 10, 10);
					break;
				case OBSTACLE_WIRE:
					Detection_Panel_Graphics->DrawRectangle(Pen_target_wire, Detection_Screen_X - 5, SCREEN_SIZE_Y - (Detection_Screen_Y - 5), 10, 10);
					break;
				case OBSTACLE_UNKNOWN:
					Detection_Panel_Graphics->DrawRectangle(Pen_target_unknown, Detection_Screen_X - 2, SCREEN_SIZE_Y - (Detection_Screen_Y - 2), 4, 4);
					break;
			}
		}
	}
}

void C_Detections::Plot_Trajectory_To_Screen(int screen_x, int screen_y)
{
	//-------------------------------------------
	//	We find the screen coordinates of the current target
	//-------------------------------------------
	int Trajectory_Screen_X = pylon_1.Screen_X + screen_x;
	int Trajectory_Screen_Y = pylon_1.Screen_Y + screen_y;

	if ((Trajectory_Screen_X > 0) && (Trajectory_Screen_X < SCREEN_SIZE_X) && (Trajectory_Screen_Y > 0) && (Trajectory_Screen_Y < SCREEN_SIZE_Y))
	{
		if (pylon_1.Get_Range() > max_error_range_meter)
		{
			//---------------------------------------------------
			//		Plot target
			//---------------------------------------------------	
			switch (obstacle_type)
			{
			case OBSTACLE_PYLON:
				Draw_Triangular_Of_Detection(Pen_target_pylon, screen_x, screen_y);
				break;
			case OBSTACLE_WIRE:
				Draw_Triangular_Of_Detection(Pen_target_wire, screen_x, screen_y);
				break;
			case OBSTACLE_UNKNOWN:
				Draw_Triangular_Of_Detection(Pen_target_unknown, screen_x, screen_y);
				break;
			}
		}
	}
}
// --------------------------------------------------
//  Plot_Detection_To_Screen_In_Offline_Mode
//  Haim Otachi		31/03/2016
// 	Description:	the function plot the detections on the screen.
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Detections::Plot_Detection_To_Screen_In_Offline_Mode(int screen_x, int screen_y)
{
	//-------------------------------------------
	//	We find the screen coordinates of the current target
	//-------------------------------------------
	int Detection_Screen_X = pylon_1.Screen_X + screen_x;
	int Detection_Screen_Y = pylon_1.Screen_Y + screen_y;

	double x = Detection_Screen_X - 5;
	double y = SCREEN_SIZE_Y - (Detection_Screen_Y - 5);

	if ((Detection_Screen_X > 0) && (Detection_Screen_X < SCREEN_SIZE_X) && (Detection_Screen_Y > 0) && (Detection_Screen_Y < SCREEN_SIZE_Y))
	{
		int new_Target_reliability = (int)(PNI_Data_of_detection->Target_reliability - 16);

		if (PNI_Data_of_detection->Range > max_error_range_meter && ((new_Target_reliability & 12 == 12) || (new_Target_reliability & 3 == 3)))
		{
				//---------------------------------------------------
				//		Plot target
				//---------------------------------------------------	
				switch (obstacle_type)
				{
					case OBSTACLE_PYLON:
						Detection_Panel_Graphics->DrawRectangle(Pen_target_pylon, Detection_Screen_X - 5, SCREEN_SIZE_Y - (Detection_Screen_Y - 5), 10, 10);
						break;
					case OBSTACLE_WIRE:
						Detection_Panel_Graphics->DrawRectangle(Pen_target_wire, Detection_Screen_X - 5, SCREEN_SIZE_Y - (Detection_Screen_Y - 5), 10, 10);
						break;
					case OBSTACLE_UNKNOWN:
						Detection_Panel_Graphics->DrawRectangle(Pen_target_unknown, Detection_Screen_X - 2, SCREEN_SIZE_Y - (Detection_Screen_Y - 2), 4, 4);
						break;
					case OBSTACLE_GROUND:
						//Detection_Panel_Graphics->DrawRectangle(Pen_target_unknown, Detection_Screen_X - 2, SCREEN_SIZE_Y - (Detection_Screen_Y - 2), 4, 4);
						break;
				}
		}
	}
}
// --------------------------------------------------
//  Update_Min_max
//  Haim Otachi		07/12/2015
// 	Description:	the function calculate the minimum and maximum points in UTM coordinate unit
//					of the border:
//							1. Screen_Bottom_Left -	the minimum point of Latitude and Longitude
//							2. Screen_Top_Right	  -	the maximum point of Latitude and Longitude
//					
//					and update them in arguments:  Max_Lat, Max_Lon, Min_Lat, Min_Lon
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Detections::Find_Min_Max(double& Max_Lat, double& Max_Lon, double& Min_Lat, double& Min_Lon)
{
	//-------------------------------------------
	//		find the minimum and maximum of first point: 'Pylon' situation
	//-------------------------------------------
	if (pylon_1.Latitude > Max_Lat)
	{
		Max_Lat = pylon_1.Latitude;
	}
	if (pylon_1.Longitude > Max_Lon)
	{
		Max_Lon = pylon_1.Longitude;
	}
	if (pylon_1.Latitude < Min_Lat)
	{
		Min_Lat = pylon_1.Latitude;
	}
	if (pylon_1.Longitude < Min_Lon)
	{
		Min_Lon = pylon_1.Longitude;
	}
	//-------------------------------------------
	//		find the minimum and maximum of second point: 'Wire' situation
	//-------------------------------------------
	if (obstacle_type == OBSTACLE_WIRE)
	{
		if (pylon_2.Latitude > Max_Lat)
		{
			Max_Lat = pylon_2.Latitude;
		}
		if (pylon_2.Longitude > Max_Lon)
		{
			Max_Lon = pylon_2.Longitude;
		}
		if (pylon_2.Latitude < Min_Lat)
		{
			Min_Lat = pylon_2.Latitude;
		}
		if (pylon_2.Longitude < Min_Lon)
		{
			Min_Lon = pylon_2.Longitude;
		}
	}
}

void C_Detections::Set_Screen_Position(int screen_x, int screen_y)
{
	pylon_1.set_Object_in_Screen_Position(pylon_1.Screen_X + screen_x, pylon_1.Screen_Y + screen_y);
	pylon_2.set_Object_in_Screen_Position(pylon_2.Screen_X + screen_x, pylon_2.Screen_Y + screen_y);
}
#pragma endregion

#pragma region Private Methods
// -----------------------------------------------------------
//  Plot_Pylon  
//  Haim Otachi		08/11/2015
// 	Description:	the function plot the 'Pylon' obstacle to screen
// 	Reference: 
//  Input value:
//  Return Value: 
// -----------------------------------------------------------
void C_Detections::Plot_Pylon()
{
	//---------------------------------
	//  Initialize the pen of the 'Pylon' for the plot on the screen.
	//---------------------------------
	Pen^ Pen_pylon = gcnew Pen(COLOR_TRUE);
	//---------------------------------
	//  Calculate the 'pylon_position_shift' for the print
	//---------------------------------
	int pylon_position_shift = (int)(PYLON_SIZE_TRUE / 2);
	//---------------------------------
	//  Find the screen position
	//---------------------------------
	C_Point2DInt obstacle_Screen_1 = pylon_1.get_Object_in_Screen_Position();
	//---------------------------------
	//  Plot pylon on screen
	//---------------------------------
	Detection_Panel_Graphics->DrawRectangle(Pen_pylon, (int)obstacle_Screen_1.Screen_X - pylon_position_shift, (int)(SCREEN_SIZE_Y - obstacle_Screen_1.Screen_Y - pylon_position_shift), PYLON_SIZE_TRUE, PYLON_SIZE_TRUE);
}
// --------------------------------------------------
//  Plot_Wire
//  Haim Otachi		08/11/2015
// 	Description:	the function plot the 'Wire' obstacle to screen
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Detections::Plot_Wire()
{
	//---------------------------------
	//  Initialize the pen of the 'Wire' for the plot on the screen.
	//---------------------------------
	Pen^ Pen_wire = gcnew Pen(COLOR_TRUE);
	//---------------------------------
	//  Find the screen position
	//---------------------------------
	C_Point2DInt obstacle_Screen_1, obstacle_Screen_2;
	//-------------------------------------------
	//	save the first point of the wire for plotting
	//-------------------------------------------
	obstacle_Screen_1 = pylon_1.get_Object_in_Screen_Position();
	//-------------------------------------------
	//	save the second point of the wire for plotting
	//-------------------------------------------
	obstacle_Screen_2 = pylon_2.get_Object_in_Screen_Position();
	//-------------------------------------------
	//  Plot wire on screen
	//-------------------------------------------
	Detection_Panel_Graphics->DrawLine(Pen_wire, PointF((float)obstacle_Screen_1.Screen_X, SCREEN_SIZE_Y - ((float)obstacle_Screen_1.Screen_Y)), PointF((float)obstacle_Screen_2.Screen_X, SCREEN_SIZE_Y - ((float)obstacle_Screen_2.Screen_Y)));
}
// --------------------------------------------------
//  Draw_Triangular_Of_Detection
//  Haim Otachi		27/03/2016
// 	Description:	???
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Detections::Draw_Triangular_Of_Detection(Pen^ Pen_Trajectory, int screen_x, int screen_y)
{
	//-------------------------------------------
	//		we take the radar yaw of the current step the radar = Radar_in_UTM_Position;
	//		and find the 'Heading' of the radar.
	//-------------------------------------------
	double radar_north = pylon_1.get_Radar_in_UTM_North();
	double Heading = radar_north;
	//-------------------------------------------
	//		we take the x and y coordinates of the radar = (x,y)
	//-------------------------------------------
	int x = pylon_1.Screen_X + screen_x;
	int y = pylon_1.Screen_Y + screen_y;
	//-------------------------------------------
	//		we calculate the delta x and delta y from the radar position to the "end position"  i.e., the arrow head. 
	//-------------------------------------------
	double delta_X = 10 * sin(Heading);
	double delta_Y = 10 * cos(Heading);
	//-------------------------------------------
	//		we calculate the 'end x' and 'end y' i.e.:
	//		end_x = x + delta_X.
	//		end_y = y + delta_Y.
	//-------------------------------------------
	int end_y = (int)(y + delta_Y);
	int end_x = (int)(x + delta_X);
	//-------------------------------------------
	//	We find the part of the left arrow point; (x,y)
	//-------------------------------------------
	int	part_of_left_arrow_x = (int)(x + 15 * sin((-135 * PI / 180) + radar_north));
	int	part_of_left_arrow_y = (int)(y + 15 * cos((-135 * PI / 180) + radar_north));
	//-------------------------------------------
	//	We find the part of the right arrow point; (x,y)
	//-------------------------------------------
	int	part_of_right_arrow_x = (int)(x + 15 * sin((135 * PI / 180) + radar_north));
	int	part_of_right_arrow_y = (int)(y + 15 * cos((135 * PI / 180) + radar_north));
	//-------------------------------------------
	//	plot to screen the lower line of arrow head 
	//-------------------------------------------
	Point^	left_triangular		= gcnew Point(part_of_left_arrow_x, SCREEN_SIZE_Y - part_of_left_arrow_y);
	Point^	right_triangular	= gcnew Point(part_of_right_arrow_x, SCREEN_SIZE_Y - part_of_right_arrow_y);
	Point^	Vertex_triangular	= gcnew Point(x, SCREEN_SIZE_Y - y);
	array<Point>^ curvePoints	= { Vertex_triangular, left_triangular, right_triangular };

	// Draw polygon to screen.
	Detection_Panel_Graphics->DrawPolygon(Pen_Trajectory, curvePoints);

	// Create solid brush.
	SolidBrush^ Pen_Trajectory_Brush = gcnew SolidBrush(Color::Yellow);

	// Fill polygon to screen.
	Detection_Panel_Graphics->FillPolygon(Pen_Trajectory_Brush, curvePoints);
}
#pragma endregion




