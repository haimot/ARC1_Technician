#include "C_Radar_Post.h"
//-----------------------------------------
//		Obstacles map
//-----------------------------------------
#define			PI								3.14159265358979323846

#define			MAX_DETECTIONS					100
#define			MAX_TRAJECTORIES				30
#define			MAX_POINTS_IN_OBSTACLE			100
//-----------------------------------------
//		Display
//-----------------------------------------
#define			SCREEN_SIZE_X					600
#define			SCREEN_SIZE_Y					600

#define			OBSTACLE_PYLON					1
#define			OBSTACLE_WIRE					2

using namespace System;

#pragma region Constructor
//-------------------------------------
//			Default Constructor
//-------------------------------------
C_Radar_Post::C_Radar_Post()
{
	//-------------------------------------
	//	Constructor:    Initial the Detections_Array array 
	//-------------------------------------
	Detections_Array = gcnew array<C_Detections^>(MAX_DETECTIONS);
	for (int i = 0; i < MAX_DETECTIONS; ++i)
	{
		Detections_Array[i] = gcnew C_Detections;
	}
	//-------------------------------------
	//	Constructor:    Initial the Trajectories array 
	//-------------------------------------
	trajectories_Array = gcnew array<C_Detections^>(MAX_TRAJECTORIES);
	for (int i = 0; i < MAX_TRAJECTORIES; ++i)
	{
		trajectories_Array[i] = gcnew C_Detections;
	}
	//-----------------------------------------
	// Create a Graphic object.
	//-----------------------------------------
	Radar_Post_Panel				= gcnew Panel;
	Radar_Post_Panel_Graphics		= Radar_Post_Panel->CreateGraphics();

	Detection_Panel_Graphics		= Radar_Post_Panel->CreateGraphics();
	Trajectories_Panel_Graphics		= Radar_Post_Panel->CreateGraphics();
	//-----------------------------------------
	// Create a GraphicsPath object.
	//-----------------------------------------
	radar_Path						= gcnew GraphicsPath;
	translate_radar_Matrix			= gcnew Matrix;
	rotate_radar_Matrix				= gcnew Matrix;

	base_meter_per_pixel_for_scale  = 0;
	//-----------------------------------------
	// Create a GraphicsPath object for detection.
	//-----------------------------------------
	detection_Path_Pylon			= gcnew GraphicsPath;
	detection_Path_Wire				= gcnew GraphicsPath;

	translate_detection_Matrix		= gcnew Matrix;
	//-----------------------------------------
	// Create a GraphicsPath object for trajectory.
	//-----------------------------------------
	trajectory_Path_Pylon			= gcnew GraphicsPath;
	trajectory_Path_Wire			= gcnew GraphicsPath;
	
	translate_trajectory_Matrix		= gcnew Matrix;
	//---------------------------------------------------
	//		Initialize the color of the helicopter's pen
	//---------------------------------------------------	
	AdjustableArrowCap^ bigArrow	= gcnew AdjustableArrowCap(5, 5);
	Pen_helicopter					= gcnew Pen(Brushes::Red, 3.0f);
	Pen_helicopter->CustomEndCap	= bigArrow;
	//---------------------------------------------------
	//		Initialize the color of the detection's pen
	//---------------------------------------------------
	Pen_detection					= gcnew Pen(Color::Blue, 2.0f);

	Pen_detection_Pylon				= gcnew Pen(Color::Magenta, 2.0f);
	Pen_detection_Wire				= gcnew Pen(Color::Blue, 2.0f);
	//---------------------------------------------------
	//		Initialize the color of the trajectory's pen
	//---------------------------------------------------
	Pen_trajectory = gcnew SolidBrush(Color::Yellow);
	// -----------------------------------
	// Create solid brush and size
	// -----------------------------------
	blackBrush = gcnew SolidBrush(Color::Black);
	size_of_rectangle = Size(10, 10);
	//---------------------------------------------------
	//					malloc
	//---------------------------------------------------
	sensor_data = (T_SENSOR_data*)malloc(sizeof(T_SENSOR_data));

	radar_position					= C_Position();
	plot_noice_route_of_radar		= false;

	show_detections					= true;
	show_trajectories				= true;

	Create_Radar_Shape();
	Create_Detection_Shape();
	Create_Trajectory_Shape();
}
//-------------------------------------
//				Destructor
//-------------------------------------
C_Radar_Post::~C_Radar_Post() 
{ 
	if (radar_Path)
	{
		delete  radar_Path;
	}

	if (translate_radar_Matrix)
	{
		delete  translate_radar_Matrix;
	}

	if (rotate_radar_Matrix)
	{
		delete  rotate_radar_Matrix;
	}

	if (Pen_helicopter)
	{
		delete  Pen_helicopter;
	}

	if (Pen_detection)
	{
		delete  Pen_detection;
	}

	if (Pen_trajectory)
	{
		delete  Pen_trajectory;
	}

	if (blackBrush)
	{
		delete  blackBrush;
	}

	if (sensor_data != NULL)
	{
		delete  sensor_data;
		sensor_data = NULL;
	}	
}
#pragma endregion

#pragma region Set And Get functions
//-------------------------------------------
//		Property: Radar_Position
//-------------------------------------------
C_Position C_Radar_Post::Radar_Position::get() { return radar_position; }
void C_Radar_Post::Radar_Position::set(C_Position Position_other)
{
	radar_position = Position_other;
}
//-------------------------------------------
//		Property: Current Radar Position In UTM
//-------------------------------------------
C_UTM_Coordinates C_Radar_Post::Radar_Position_In_UTM::get() { return radar_position.get_Object_in_UTM_Position(); }
void C_Radar_Post::Radar_Position_In_UTM::set(C_UTM_Coordinates Radar_UTM_other)
{
	radar_position.set_Object_in_UTM_Position(Radar_UTM_other);
}
//-------------------------------------------
//		Property: Current Detection
//-------------------------------------------
C_Detections^ C_Radar_Post::Current_Detection::get() { return Detections_Array[number_of_detections - 1]; }
//-------------------------------------------
//		Property: get Radar_in_UTM_North of obstacle position in Detection_Array of C_Detection class
//-------------------------------------------
double C_Radar_Post::Radar_in_UTM_North::get() { return radar_position.get_Radar_in_UTM_North(); }
//-------------------------------------------
//		Property: SENSOR_data
//-------------------------------------------
T_SENSOR_data C_Radar_Post::SENSOR_data::get() { return *sensor_data; }
//-------------------------------------------
//		Set: Show Detections
//-------------------------------------------
void C_Radar_Post::Set_Show_Detections(bool new_detections_status)
{
	show_detections = new_detections_status;
}
//-------------------------------------------
//		Set: Show Trajectories
//-------------------------------------------
void C_Radar_Post::Set_Show_Trajectories(bool new_trajectories_status)
{
	show_trajectories = new_trajectories_status;
}
//-------------------------------------------
//		Set: Base_Meter_Per_Pixel_For_Scale
//-------------------------------------------
void C_Radar_Post::Set_Base_Meter_Per_Pixel_For_Scale(double meter_per_pixel_other)
{
	base_meter_per_pixel_for_scale = meter_per_pixel_other;
}
#pragma endregion

#pragma region Methods
// --------------------------------------------------
//  Update_Meter_Per_Pixel
//  Haim Otachi     ???
// 	Description:	Update the C_POSITION reference parameters of the radar position and the detections
//					Meter_Per_Pixel
// 	Reference:		
//  Input value:	new value of Meter_Per_Pixel
//  Return Value:	
// --------------------------------------------------
void C_Radar_Post::Update_Meter_Per_Pixel(double Meter_Per_Pixel_Other)
{
	//------------------------
	//	Initalized radar position (C_POSITION)
	//------------------------
	radar_position.set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
	//------------------------
	//	Initalized detections (C_POSITION)
	//------------------------
	for (int i = 0; i < number_of_detections; i++)
	{
		Detections_Array[i]->Set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
	}
	//------------------------
	//	Initalized trajectories (C_POSITION)
	//------------------------
	for (int i = 0; i < number_of_trajectories; i++)
	{
		trajectories_Array[i]->Set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
	}
}
// --------------------------------------------------
//  Update_Screen_in_UTM
//  Haim Otachi     ???
// 	Description:	initalize the C_POSITION reference parameters of the radar position and the detections
//					Screen_in_UTM
// 	Reference:		
//  Input value:	UTM values of the screen origin
//  Return Value:	
// --------------------------------------------------
void C_Radar_Post::Update_Screen_in_UTM(C_Position% Screen_Bottom_Left)
{
	//------------------------
	//	Initalized radar position (C_POSITION)
	//------------------------
	radar_position.set_Screen_in_UTM_Position(Screen_Bottom_Left.get_Object_in_UTM_Position());
	//------------------------
	//	Initalized detections (C_POSITION)
	//------------------------
	for (int i = 0; i < number_of_detections; i++)
	{
		Detections_Array[i]->Set_Radar_In_UTM_Position(radar_position);
	}
	//------------------------
	//	Initalized trajectories (C_POSITION)
	//------------------------
	for (int i = 0; i < number_of_trajectories; i++)
	{
		trajectories_Array[i]->Set_Radar_In_UTM_Position(radar_position);
	}
}
// --------------------------------------------------
//  Add_Radar_Post  
//  Haim Otachi		08/10/2015
// 	Description:	gets the struct of the target from the radar message, and parsing it to the 
//					detections pertianing this post and add this organ to radar post.
// 	Reference: 
//  Input value:	Pointer to the targets data within the radar message
//  Return Value: 
// --------------------------------------------------
bool C_Radar_Post::Add_Radar_Post(T_Radar_Massage% Radar_Massage)
{
	try
	{
		//-----------------------------------------------
		// Assigning Sensor data
		//-----------------------------------------------
		*sensor_data = Radar_Massage.SENSOR_data;
		//-----------------------------------------------
		// Assigning Radar_position
		//-----------------------------------------------
		radar_position.set_Object_in_UTM_Position(sensor_data->Latitude, sensor_data->Longitude, sensor_data->Altitude);
		//------------------------------------------
		//	Radar heading is to the defined as East = x = zero azimuth
		//	So we compensate by subtracting PI/2. Alon 24.9.2015.
		//------------------------------------------
		radar_position.set_Radar_in_UTM_North(sensor_data->ATT_YAW * PI / 180);
		//-----------------------------------------------
		//		Assigning Number_Of_Detections
		//-----------------------------------------------
		number_of_detections = (int)Radar_Massage.TARGETS_data.Targets_number;
		//-----------------------------------------------
		// Assigning Detections_Array
		//-----------------------------------------------
		for (int i = 0; i < number_of_detections; i++)
		{
			//-----------------------------------------------
			// Update the 'Meter_Per_Pixel' of current obstacle
			//-----------------------------------------------
			Detections_Array[i]->Set_Meter_Per_Pixel(radar_position.get_Meter_Per_Pixel());
			//-----------------------------------------------
			// Update the 'Screen_In_UTM_Origin' of current obstacle
			//-----------------------------------------------
			Detections_Array[i]->Set_Screen_In_UTM_Origin(radar_position);
			//-----------------------------------------------
			// Add the new current detection that was detected
			//-----------------------------------------------
			Detections_Array[i]->Add_Detection(Radar_Massage.TARGETS_data.Targets_array[i], *sensor_data);
			//-----------------------------------------------
			// 
			//-----------------------------------------------
			Detections_Array[i]->Set_Screen_Position(radar_position.Screen_X, radar_position.Screen_Y);
		}
		return true;
	}
	catch (Exception^ ex) { ex->Message; return false; }
}
//// --------------------------------------------------
////  Add_Radar_Post  
////  Haim Otachi		08/10/2015
//// 	Description:	gets the struct of the target from the radar message, and parsing it to the 
////					detections pertianing this post and add this organ to radar post.
//// 	Reference: 
////  Input value:	Pointer to the targets data within the radar message
////  Return Value: 
//// --------------------------------------------------
//bool C_Radar_Post::Add_Radar_Post(T_Radar_Massage% Radar_Massage, T_Trajectories% Trajectories)
//{
//	try
//	{
//		//-----------------------------------------------
//		// Assigning Sensor data
//		//-----------------------------------------------
//		*sensor_data = Radar_Massage.SENSOR_data;
//		//-----------------------------------------------
//		// Assigning Radar_position
//		//-----------------------------------------------
//		radar_position.set_Object_in_UTM_Position(sensor_data->Latitude, sensor_data->Longitude, sensor_data->Altitude);
//		//------------------------------------------
//		//	Radar heading is to the defined as East = x = zero azimuth
//		//	So we compensate by subtracting PI/2. Alon 24.9.2015.
//		//------------------------------------------
//		//
//		// for real time
//		//
//		radar_position.set_Radar_in_UTM_North(sensor_data->ATT_YAW * PI / 180);
//		//
//		// for offline
//		//
//		//radar_position.set_Radar_in_UTM_North(sensor_data->ATT_YAW);
//		//-----------------------------------------------
//		//		Assigning Number_Of_Detections
//		//-----------------------------------------------
//		number_of_detections = (int)Radar_Massage.TARGETS_data.Targets_number;
//		//-----------------------------------------------
//		// Assigning Detections_Array
//		//-----------------------------------------------
//		for (int i = 0; i < number_of_detections; i++)
//		{
//			//-----------------------------------------------
//			// Update the 'Meter_Per_Pixel' of current obstacle
//			//-----------------------------------------------
//			Detections_Array[i]->Set_Meter_Per_Pixel(radar_position.get_Meter_Per_Pixel());
//			//-----------------------------------------------
//			// Update the 'Screen_In_UTM_Origin' of current obstacle
//			//-----------------------------------------------
//			Detections_Array[i]->Set_Screen_In_UTM_Origin(radar_position);
//			//-----------------------------------------------
//			// Add the new current detection that was detected
//			//-----------------------------------------------
//			Detections_Array[i]->Add_Detection(Radar_Massage.TARGETS_data.Targets_array[i], *sensor_data);
//			//-----------------------------------------------
//			// 
//			//-----------------------------------------------
//			Detections_Array[i]->Set_Screen_Position(radar_position.Screen_X, radar_position.Screen_Y);
//		}
//		//-----------------------------------------------
//		//		Assigning Number_Of_Trajectories
//		//      MAX_TRAJEC_NR - trajectoriesData array length
//		//-----------------------------------------------
//		number_of_trajectories = 0; 
//		//-----------------------------------------------
//		// Assigning Detections_Array
//		//-----------------------------------------------
//		for (int i = 0; i < MAX_TRAJEC_NR; i++)
//		{
//			//-----------------------------------------------
//			//  check if current trajectory is exist
//			//-----------------------------------------------
//			if (Trajectories.trajectoriesData[i].isEmpty == false)
//			{
//				if (Trajectories.trajectoriesData[i].deathFrame > Trajectories.frameNrAct)
//				{
//					//-----------------------------------------------
//					// Update the 'Meter_Per_Pixel' of current obstacle
//					//-----------------------------------------------
//					trajectories_Array[i]->Set_Meter_Per_Pixel(radar_position.get_Meter_Per_Pixel());
//					//-----------------------------------------------
//					// Update the 'Screen_In_UTM_Origin' of current obstacle
//					//-----------------------------------------------
//					trajectories_Array[i]->Set_Screen_In_UTM_Origin(radar_position);
//					//-----------------------------------------------
//					// Add the new current detection that was detected
//					//-----------------------------------------------
//					trajectories_Array[i]->Add_Trajectory(Trajectories.trajectoriesData[i], *sensor_data);
//					//-----------------------------------------------
//					// 
//					//-----------------------------------------------
//					trajectories_Array[i]->Set_Screen_Position(radar_position.Screen_X, radar_position.Screen_Y);
//					//-----------------------------------------------
//					// 
//					//-----------------------------------------------
//					number_of_trajectories++; 
//				}
//			}
//		}
//		return true;
//	}
//	catch (Exception^ ex) { ex->Message; return false; }
//}

// --------------------------------------------------
//  Add_Radar_Post  
//  Haim Otachi		08/10/2015
// 	Description:	gets the struct of the target from the radar message, and parsing it to the 
//					detections pertianing this post and add this organ to radar post.
// 	Reference: 
//  Input value:	Pointer to the targets data within the radar message
//  Return Value: 
// --------------------------------------------------
bool C_Radar_Post::Add_Radar_Post(T_Radar_Massage% Radar_Massage, T_Trajectories% Trajectories)
{
	try
	{
		//-----------------------------------------------
		// Assigning Sensor data
		//-----------------------------------------------
		*sensor_data = Radar_Massage.SENSOR_data;
		//-----------------------------------------------
		// Assigning Radar_position
		//-----------------------------------------------
		radar_position.set_Object_in_UTM_Position(sensor_data->Latitude, sensor_data->Longitude, sensor_data->Altitude);
		//------------------------------------------
		//	Radar heading is to the defined as East = x = zero azimuth
		//	So we compensate by subtracting PI/2. Alon 24.9.2015.
		//------------------------------------------
		radar_position.set_Radar_in_UTM_North(sensor_data->ATT_YAW * PI / 180);
		//-----------------------------------------------
		//	 Create Radar shape .
		//-----------------------------------------------
		Create_Radar_Shape();
		//-----------------------------------------------
		//		Assigning Number_Of_Detections
		//-----------------------------------------------
		number_of_detections = (int)Radar_Massage.TARGETS_data.Targets_number;
		//-----------------------------------------------
		// Assigning Detections_Array
		//-----------------------------------------------
		for (int i = 0; i < number_of_detections; i++)
		{
			//-----------------------------------------------
			// Update the 'Meter_Per_Pixel' of current obstacle
			//-----------------------------------------------
			Detections_Array[i]->Set_Meter_Per_Pixel(radar_position.get_Meter_Per_Pixel());
			//-----------------------------------------------
			// Update the 'Screen_In_UTM_Origin' of current obstacle
			//-----------------------------------------------
			Detections_Array[i]->Set_Screen_In_UTM_Origin(radar_position);
			//-----------------------------------------------
			// Add the new current detection that was detected
			//-----------------------------------------------
			Detections_Array[i]->Add_Detection(Radar_Massage.TARGETS_data.Targets_array[i], *sensor_data);
		}
		//-----------------------------------------------
		//		Translate the Detection shape.
		//-----------------------------------------------
		Translate_Detection_Shape(
			(float)(radar_position.get_Meter_Per_Pixel() / 10),
			(float)(radar_position.get_Meter_Per_Pixel() / 10));
		//-----------------------------------------------
		//		Assigning Number_Of_Trajectories
		//      MAX_TRAJEC_NR - trajectoriesData array length
		//-----------------------------------------------
		number_of_trajectories = 0;
		//-----------------------------------------------
		// Assigning Detections_Array
		//-----------------------------------------------
		for (int i = 0; i < MAX_TRAJEC_NR; i++)
		{
			//-----------------------------------------------
			//  check if current trajectory is exist
			//-----------------------------------------------
			if (Trajectories.trajectoriesData[i].isEmpty == false)
			{
				if (Trajectories.trajectoriesData[i].deathFrame > Trajectories.frameNrAct)
				{
					//-----------------------------------------------
					// Update the 'Meter_Per_Pixel' of current obstacle
					//-----------------------------------------------
					trajectories_Array[i]->Set_Meter_Per_Pixel(radar_position.get_Meter_Per_Pixel());
					//-----------------------------------------------
					// Update the 'Screen_In_UTM_Origin' of current obstacle
					//-----------------------------------------------
					trajectories_Array[i]->Set_Screen_In_UTM_Origin(radar_position);
					//-----------------------------------------------
					// Add the new current detection that was detected
					//-----------------------------------------------
					trajectories_Array[i]->Add_Trajectory(Trajectories.trajectoriesData[i], *sensor_data);
					//-----------------------------------------------
					// 
					//-----------------------------------------------
					number_of_trajectories++;
				}
			}
		}
		return true;
	}
	catch (Exception^ ex) { ex->Message; return false; }
}
// --------------------------------------------------
//  Add_Obstacle  
//  Haim Otachi		08/10/2015
// 	Description:	Add new obstacle to 'radar_post_array' of the 'Radar_Route' and increase the 
//					pointer to this structure 
// 	Reference: 
//  Input value:	Pointer to the new obstacle position by 'C_Position' class
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Add_Obstacle(C_Position% Point_Obstacle_other)
{
	Detections_Array[number_of_detections]->Set_Obstacle_Position(Point_Obstacle_other);
	number_of_detections++;
}
void C_Radar_Post::Add_Detection(double Polarization, double Azimuth, double Range, double Reliability)
{
	Detections_Array[number_of_detections]->Add_Detection(Polarization, Azimuth, Range, Reliability);
}
// --------------------------------------------------
//  Plot_Trajectories_To_Screen  
//  Haim Otachi			15/03/2016
// 	Description:		Plot all trajectories of current Radar Position
// 	Reference: 
//  Input value:		Pointer to Graphics element to diaply on
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Plot_Trajectories_To_Screen()

{
	//---------------------------------------------------
	//		check the status of 'show_trajectories' 
	//---------------------------------------------------
	if (show_trajectories == true)
	{
		if (base_meter_per_pixel_for_scale != radar_position.get_Meter_Per_Pixel())
		{
			//
			//	create 'trajectory_Path_Pylon' again with new data.
			//
			if (trajectory_Path_Pylon->PointCount != 0)
			{
				//---------------------------------------------------
				// we take the trajectories point of pylon into 'trajectories_point_pylon' array.
				//---------------------------------------------------
				array<PointF>^ trajectories_point_pylon = trajectory_Path_Pylon->PathPoints;
				trajectory_Path_Pylon->Reset();
				for (int i = 0; i < trajectories_point_pylon->Length - 3; i = i + 3)
				{
					trajectories_point_pylon[i].X = (float)(
						trajectories_point_pylon[i].X *
						(radar_position.get_Meter_Per_Pixel() / 10)
						);

					trajectories_point_pylon[i].Y = (float)(
						trajectories_point_pylon[i].Y *
						(radar_position.get_Meter_Per_Pixel() / 10)
						);

					array<Point>^ trajectories_pylon = {
						//
						//	Trajectory_Screen_P1
						//
						Point((int)(trajectories_point_pylon[i].X - 10), (int)(trajectories_point_pylon[i].Y - 5)),
						//
						//	Trajectory_Screen_P2
						//
						Point((int)trajectories_point_pylon[i].X, (int)(trajectories_point_pylon[i].Y - 10)),
						//
						//	Trajectory_Screen_P3
						//
						Point((int)(trajectories_point_pylon[i].X + 10), (int)(trajectories_point_pylon[i].Y - 5))
					};

					trajectory_Path_Pylon->AddPolygon(trajectories_pylon);
				}
			}
			//
			//	create 'trajectory_Path_Wire' again with new data.
			//
			if (trajectory_Path_Wire->PointCount != 0)
			{
				//---------------------------------------------------
				// we take the trajectories point of pylon into 'trajectories_point_pylon' array.
				//---------------------------------------------------
				array<PointF>^ trajectories_point_wire = trajectory_Path_Wire->PathPoints;
				trajectory_Path_Wire->Reset();
				for (int i = 0; i < trajectories_point_wire->Length - 3; i = i + 3)
				{
					trajectories_point_wire[i].X = (float)(
						trajectories_point_wire[i].X *
						(radar_position.get_Meter_Per_Pixel() / 10)
						);

					trajectories_point_wire[i].Y = (float)(
						trajectories_point_wire[i].Y *
						(radar_position.get_Meter_Per_Pixel() / 10)
						);

					array<Point>^ trajectories_wire = {
						//
						//	Trajectory_Screen_P1
						//
						Point((int)(trajectories_point_wire[i].X - 10), (int)(trajectories_point_wire[i].Y - 5)),
						//
						//	Trajectory_Screen_P2
						//
						Point((int)trajectories_point_wire[i].X, (int)(trajectories_point_wire[i].Y - 10)),
						//
						//	Trajectory_Screen_P3
						//
						Point((int)(trajectories_point_wire[i].X + 10), (int)(trajectories_point_wire[i].Y - 5))
					};

					trajectory_Path_Wire->AddPolygon(trajectories_wire);
				}
			}
		}
		//-----------------------------------------
		// Fill graphics path of 'Pylon' to screen.
		//-----------------------------------------
		Trajectories_Panel_Graphics->FillPath(Pen_trajectory, trajectory_Path_Pylon);
		//-----------------------------------------
		// Fill graphics path of 'Wire' to screen.
		//-----------------------------------------
		Trajectories_Panel_Graphics->FillPath(Pen_trajectory, trajectory_Path_Wire);
	}
}
// --------------------------------------------------
//  Plot_Detections_To_Screen  
//  Haim Otachi			08/03/2016
// 	Description:		Plot all detection of current Radar Position
// 	Reference: 
//  Input value:		Pointer to Graphics element to diaply on
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Plot_Detections_To_Screen()
{
	//---------------------------------------------------
	//		check the status of 'show_detections' 
	//---------------------------------------------------
	if (show_detections == true)
	{	
		if (base_meter_per_pixel_for_scale != radar_position.get_Meter_Per_Pixel())
		{
			//
			//	create 'detection_Path_Pylon' again with new data.
			//
			if (detection_Path_Pylon->PointCount != 0)
			{
				array<PointF>^ detections_points_pylon = detection_Path_Pylon->PathPoints;
				detection_Path_Pylon->Reset();
				for (int i = 0; i < detections_points_pylon->Length - 4; i = i + 4)
				{
					detections_points_pylon[i].X = (float)(
						detections_points_pylon[i].X *
						(radar_position.get_Meter_Per_Pixel() / 10)
						);

					detections_points_pylon[i].Y = (float)(
						detections_points_pylon[i].Y *
						(radar_position.get_Meter_Per_Pixel() / 10)
						);

					detection_Path_Pylon->AddRectangle(RectangleF(detections_points_pylon[i], size_of_rectangle));
				}
			}
			//
			//	create 'detection_Path_Wire' again with new data.
			//
			if (detection_Path_Wire->PointCount != 0)
			{
				array<PointF>^ detections_points_wire = detection_Path_Wire->PathPoints;
				detection_Path_Wire->Reset();
				for (int i = 0; i < detections_points_wire->Length - 4; i = i + 4)
				{
					detections_points_wire[i].X = (float)(
						detections_points_wire[i].X *
						(radar_position.get_Meter_Per_Pixel() / 10)
						);

					detections_points_wire[i].Y = (float)(
						detections_points_wire[i].Y *
						(radar_position.get_Meter_Per_Pixel() / 10)
						);

					detection_Path_Wire->AddRectangle(RectangleF(detections_points_wire[i], size_of_rectangle));
				}
			}
		}
		//-------------------------------------------
		// draw detection to screen
		//-------------------------------------------
		Detection_Panel_Graphics->DrawPath(Pen_detection_Pylon, detection_Path_Pylon);
		Detection_Panel_Graphics->DrawPath(Pen_detection_Wire, detection_Path_Wire);	
	}
}
// --------------------------------------------------
//  Restart  
//  Haim Otachi			21/10/2015
// 	Description:		???
// 	Reference: 
//  Input value:		
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Restart() { current_detection = 0; }
// --------------------------------------------------
//  Restart  
//  Haim Otachi			21/10/2015
// 	Description:		???
// 	Reference: 
//  Input value:		
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Clear() { current_detection = 0; number_of_detections = 0; }

bool C_Radar_Post::Line_angle(C_Position% Pylon_1, C_Position% Pylon_2)
{
	//--------------------------------------------------
	//	 take the radar north value from the current radar post 
	// --------------------------------------------------
	double Radar_YAW = radar_position.get_Radar_in_UTM_North();
	//---------------------------------------------------
	//	  update the angle 'Radar YAW' of the 'Pylon_1'
	//---------------------------------------------------
	Pylon_1.set_Radar_in_UTM_North(Radar_YAW);
	//---------------------------------------------------
	//	  update the angle 'Radar YAW' of the 'Pylon_2'
	//---------------------------------------------------
	Pylon_2.set_Radar_in_UTM_North(Radar_YAW);
	//---------------------------------------------------
	//	calculate the Line angle between 3 points: 
	//				1. Radar Position
	//				2. Obstacle Position 1	(Pylon_1)
	//				3. Obstacle Position 2	(Pylon_2)
	//---------------------------------------------------
	double Line_angle_1 = radar_position.Line_angle(Pylon_1, Pylon_2);
	double Line_angle_2 = radar_position.Line_angle(Pylon_2, Pylon_1);

	if ((Line_angle_1 < PI / 2) && (Line_angle_2 < PI / 2))
	{
		return true;
}
return false;
}

double C_Radar_Post::Distance_To(C_Position% Position_Other)
{
	return radar_position.Distance_To(Position_Other);
}

double C_Radar_Post::Azimuth_To(C_Position% Position_Other)
{
	return radar_position.Azimuth_To(Position_Other);
}
#pragma endregion

// --------------------------------------------------
//  Initial_Radar_Position  
//  Haim Otachi			05/11/2015
// 	Description:		The function initial the Radar_Position object and his detections	
// 	Reference: 
//  Input value:		new Radar routing Position value for initial the cell
//  Return Value:		True or False
// --------------------------------------------------
bool C_Radar_Post::Initialize(Panel^ Radar_Post_Panel_Other,C_Position% Radar_routing_Position, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other)
{
	try
	{
		//--------------------------------------------------
		//		Initialize the Viewer Panel and him Graphics
		//--------------------------------------------------
		Radar_Post_Panel			= Radar_Post_Panel_Other;
		Radar_Post_Panel_Graphics	= Radar_Post_Panel->CreateGraphics();

		Detection_Panel_Graphics	= Radar_Post_Panel->CreateGraphics();
		Trajectories_Panel_Graphics = Radar_Post_Panel->CreateGraphics();
		//----------------------------------------------
		//  update the Radar_Post_array in current index with new Radar Position values (Radar_routing_Position)
		//----------------------------------------------
		radar_position = Radar_routing_Position;
		//----------------------------------------------
		//  update the Radar_Post_array in current index with new 'Obstacles' of this radar
		//----------------------------------------------
		current_detection = 0;
		while (current_detection < MAX_POINTS_IN_OBSTACLE)
		{
			Detections_Array[current_detection]->Initialize(Radar_Post_Panel, Radar_routing_Position, Max_Range_Error_Meter_Other, Reliability_Threshold_Other);
			current_detection++;
		}
		//----------------------------------------------
		//  update the Radar_Post_array in current index with new 'trajectories' of this radar
		//----------------------------------------------
		current_trajectory = 0;
		while (current_trajectory < MAX_TRAJECTORIES)
		{
			trajectories_Array[current_trajectory]->Initialize(Radar_Post_Panel, Radar_routing_Position, Max_Range_Error_Meter_Other, Reliability_Threshold_Other);
			current_trajectory++;
		}
		return true;
	}
	catch (Exception^ Ex)
	{
		Ex->Message;
		return false;
	}
}
// --------------------------------------------------
//  Target_is_in_RADAR_FOV  
//  Haim Otachi			05/11/2015
// 	Description:		
// 	Reference: 
//  Input value:		
//  Return Value:		
// --------------------------------------------------
bool C_Radar_Post::Target_is_in_RADAR_FOV(C_Position% Position, int Radar_Max_Range, int Radar_FOV, double Variance_Position_Wires)
{
	// --------------------------------------------------
	//	 take the radar north value from the current radar post 
	// --------------------------------------------------
	double Radar_YAW = radar_position.get_Radar_in_UTM_North();
	//---------------------------------------------------
	//		we Update the Coordinate Of radar position of the target
	//---------------------------------------------------
	Position.set_Radar_in_UTM_Position(radar_position.get_Object_in_UTM_Position());
	//---------------------------------------------------
	//	    we update the angle 'Radar YAW' of the current target
	//---------------------------------------------------
	Position.set_Radar_in_UTM_North(Radar_YAW);
	// --------------------------------------------------
	//	   Calculate the range from Radar to target
	// --------------------------------------------------
	double target_range = Distance_To(Position);
	// --------------------------------------------------
	//	   Calculate the azimuth from Radar to target
	// --------------------------------------------------
	double target_angle = Azimuth_To(Position);
	// --------------------------------------------------
	//	 we calculate if target is in Radar FOV
	// --------------------------------------------------
	if ((target_range <= Radar_Max_Range) && (fabs(target_angle - Radar_YAW) <= Radar_FOV / 2))
	{
		//----------------------------------
		//			add noise to PNI
		//-----------------------------------
		double noise_X = (double)((rand() % 100) - 50) / 50 * Variance_Position_Wires;
		double noise_Y = (double)((rand() % 100) - 50) / 50 * Variance_Position_Wires;
		C_CartesianPoint noise_Cartesian(noise_X, noise_Y);
		Position += noise_Cartesian;
		//---------------------------------------------------
		//		Save the data of target_PNI of current obstacle that was detected
		//---------------------------------------------------
		Add_Obstacle(Position);
		return true;
	}
	return false;
}
// --------------------------------------------------
//  Update_Min_max
//  Haim Otachi		07/12/2015
// 	Description:	the function calculate the minimum and maximum points in UTM coordinate unit
//					of the border:
//							1. Screen_Bottom_Left -	the minimum point of Latitude and Longitude
//							2. Screen_Top_Right	  -	the maximum point of Latitude and Longitude
//
//					and update them in objects:  'Screen_Bottom_Left', 'Screen_Top_Right'
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Find_Min_Max(double& Max_Lat, double& Max_Lon, double& Min_Lat, double& Min_Lon)
{
	//-------------------------------------------
	//		find the minimum and maximum of current position of the radar
	//-------------------------------------------
	if (radar_position.Latitude > Max_Lat)
	{
		Max_Lat = radar_position.Latitude;
	}
	if (radar_position.Longitude > Max_Lon)
	{
		Max_Lon = radar_position.Longitude;
	}
	if (radar_position.Latitude < Min_Lat)
	{
		Min_Lat = radar_position.Latitude;
	}
	if (radar_position.Longitude < Min_Lon)
	{
		Min_Lon = radar_position.Longitude;
	}
}
// --------------------------------------------------
//  Draw_Arrow_Of_Heading
//  Haim Otachi		04/01/2016
// 	Description:	the function created "Arrow" that represents the heading of the radar
//					and view the direction vector of the Radar's movement.
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Draw_Arrow_Of_Heading()
{
	//-------------------------------------------
	//		we take the radar yaw of the current step the radar = Radar_in_UTM_Position;
	//		and find the 'Heading' of the radar.
	//-------------------------------------------
	double heading = radar_position.get_Radar_in_UTM_North() * (180 / PI); // Heading in degrees
	//-------------------------------------------
	//		we take the x and y coordinates of the radar = (x,y)
	//-------------------------------------------
	PointF base_Rotate_Point = Point((int)(radar_Path->PathPoints[0].X), (int)(radar_Path->PathPoints[0].Y));
	//-------------------------------------------
	// 1.	Create a matrix 
	// 2.	rotate it 'heading + 180' degrees 
	// 3.	translate it with parameters = (translate_x, translate_y).
	//-------------------------------------------
	//
	//	Create a matrix
	//
	rotate_radar_Matrix = gcnew Matrix;
	//
	//	rotate it 'heading + 180' degrees
	//
	rotate_radar_Matrix->RotateAt((float)heading + 180, base_Rotate_Point, MatrixOrder::Append);
	//
	//	translate it with parameters = (translate_x, translate_y)
	//
	if (base_meter_per_pixel_for_scale != radar_position.get_Meter_Per_Pixel())
	{
		rotate_radar_Matrix->Translate(
			(float)(-radar_Path->PathPoints[0].X + radar_Path->PathPoints[0].X * radar_position.get_Meter_Per_Pixel() / 10),
			(float)(-radar_Path->PathPoints[0].Y + radar_Path->PathPoints[0].Y * radar_position.get_Meter_Per_Pixel() / 10),
			MatrixOrder::Append);
	}
	Radar_Post_Panel_Graphics->Transform = rotate_radar_Matrix;
	//-------------------------------------------
	//	 Drawing the radar position on the screen
	//-------------------------------------------
	Radar_Post_Panel_Graphics->DrawPath(Pen_helicopter, radar_Path);
	//-------------------------------------------
	//	 Dispose of 'rotate_radar_Matrix'
	//-------------------------------------------
	delete rotate_radar_Matrix;
}
// --------------------------------------------------
//  Create_Radar_Shape
//  Haim Otachi		18/04/2016
// 	Description:	
//					
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Create_Radar_Shape()
{
	//-------------------------------------------
	//  Dispose 'radar_Path' position of the radar. 
	//-------------------------------------------
	radar_Path->Reset();
	//-------------------------------------------
	//  create two point for draw: 
	//        1. base point.
	//		  2. second point relative him.
	//-------------------------------------------
	Point	base_point_of_radar = Point(radar_position.Screen_X, SCREEN_SIZE_Y - radar_position.Screen_Y);
	Point	high_point_relative_radar = Point(radar_position.Screen_X, SCREEN_SIZE_Y - (radar_position.Screen_Y - 30));
	//-------------------------------------------
	// build the 'radar_Path'
	//-------------------------------------------
	radar_Path->AddLine(base_point_of_radar, high_point_relative_radar);	
}
// --------------------------------------------------
//  Create_Detection_Shape
//  Haim Otachi		18/04/2016
// 	Description:	
//					
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Create_Detection_Shape()
{
	Point Detection_Screen;
	//-------------------------------------------
	//  Dispose 'detection_Path' points relative to current position of the radar.
	//-------------------------------------------
	detection_Path_Pylon->Reset();
	detection_Path_Wire->Reset();

	current_detection = 0;
	while (current_detection < number_of_detections)
	{
		//-------------------------------------------
		//	We find the screen coordinates of the current target
		//-------------------------------------------
		Detection_Screen.X = (int)(
			Detections_Array[current_detection]->Get_Pylon_1().Screen_X + radar_Path->PathPoints[0].X - 5);

		Detection_Screen.Y = (int)(
			SCREEN_SIZE_Y - (Detections_Array[current_detection]->Get_Pylon_1().Screen_Y + radar_position.Screen_Y) + 5);
		//-------------------------------------------
		//	
		//-------------------------------------------
		switch (Detections_Array[current_detection]->Get_Obstacle_Type())
		{
			//-------------------------------------------
			//	Add current 'Pylon' target to 'Path' array
			//-------------------------------------------
			case OBSTACLE_PYLON:
				detection_Path_Pylon->AddRectangle(Rectangle(Detection_Screen, size_of_rectangle));
				break;
				//-------------------------------------------
				//	Add current 'Wire' target to 'Path' array
				//-------------------------------------------
			case OBSTACLE_WIRE:
				detection_Path_Wire->AddRectangle(Rectangle(Detection_Screen, size_of_rectangle));
				break;
		}

		current_detection++;
	}
}
// --------------------------------------------------
//  Create_Trajectory_Shape
//  Haim Otachi		18/04/2016
// 	Description:	
//					
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Create_Trajectory_Shape()
{
	float screen_x_trajectory;
	float screen_y_trajectory;
	//-------------------------------------------
	//  Dispose 'trajectory_Path' points relative to current position of the radar.
	//-------------------------------------------
	trajectory_Path_Pylon->Reset();
	trajectory_Path_Wire->Reset();

	current_trajectory = 0;
	while (current_trajectory < number_of_trajectories)
	{
		//-------------------------------------------
		//	We find the screen coordinates of the current trajectory
		//-------------------------------------------
		screen_x_trajectory = trajectories_Array[current_trajectory]->Get_Pylon_1().Screen_X + radar_Path->PathPoints[0].X;
		screen_y_trajectory = (float)(SCREEN_SIZE_Y - (trajectories_Array[current_trajectory]->Get_Pylon_1().Screen_Y + radar_position.Screen_Y));

		array<Point>^ trajectories_points = { 
			//
			//	Trajectory_Screen_P1
			//
			Point((int)(screen_x_trajectory - 10),		(int)(screen_y_trajectory - 5)),
			//
			//	Trajectory_Screen_P2
			//
			Point((int)screen_x_trajectory,				(int)(screen_y_trajectory - 10)),
			//
			//	Trajectory_Screen_P3
			//
			Point((int)(screen_x_trajectory + 10),		(int)(screen_y_trajectory - 5))
		};
		//-------------------------------------------
		//	
		//-------------------------------------------
		switch (trajectories_Array[current_trajectory]->Get_Obstacle_Type())
		{
			//-------------------------------------------
			//	Add current 'Pylon' trajectory to 'Path' array
			//-------------------------------------------
			case OBSTACLE_PYLON:
				trajectory_Path_Pylon->AddPolygon(trajectories_points);
				break;
			//-------------------------------------------
			//	Add current 'Wire' trajectory to 'Path' array
			//-------------------------------------------
			case OBSTACLE_WIRE:
				trajectory_Path_Wire->AddPolygon(trajectories_points);
				break;
		}
		//-------------------------------------------
		//	We find the screen coordinates of the current target
		//-------------------------------------------
		current_trajectory++;
	}
}


void C_Radar_Post::Set_Screen_Coordinates(int screen_x, int screen_y)
{
	radar_position.set_Object_in_Screen_Position(screen_x, screen_y);
}

void C_Radar_Post::Update_Screen_Position()
{
	for (int i = 0; i < number_of_detections; ++i)
	{
		Detections_Array[i]->Set_Screen_Position(radar_position.Screen_X, radar_position.Screen_Y);
	}

	for (int i = 0; i < number_of_trajectories; ++i)
	{
		trajectories_Array[i]->Set_Screen_Position(radar_position.Screen_X, radar_position.Screen_Y);
	}
}
// --------------------------------------------------
//  Plot_Noice_Route_Of_Radar
//  Haim Otachi		02/04/2016
// 	Description:	
//					
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
void C_Radar_Post::Plot_Noice_Route_Of_Radar()
{
	//---------------------------------------------------
	//	Fields:		first and second points for ploting to screen
	//---------------------------------------------------
	C_Point2DInt	first_Screen_point;
	C_Point2DInt	second_Screen_point;
	//-------------------------------------------
	//		we take the radar yaw of the current step the radar = Radar_in_UTM_Position;
	//		and find the 'Heading' of the radar.
	//-------------------------------------------
	double radar_north = radar_position.get_Radar_in_UTM_North();
	double Heading = radar_north;/* / 180 * PI*/
	//-------------------------------------------
	//		we take the x and y coordinates of the radar = (x,y)
	//-------------------------------------------
	int x = radar_position.Screen_X;
	int y = radar_position.Screen_Y;
	//-------------------------------------------
	//		we calculate the delta x and delta y from the radar position to the "end position"  i.e., the arrow head. 
	//-------------------------------------------
	double delta_X = 30 * sin(Heading);
	double delta_Y = 30 * cos(Heading);
	//-------------------------------------------
	//		we calculate the 'end x' and 'end y' i.e.:
	//		end_x = x + delta_X.
	//		end_y = y + delta_Y.
	//-------------------------------------------
	int end_y = (int)(y + delta_Y);
	int end_x = (int)(x + delta_X);
	//-------------------------------------------
	//	we take the first and second point to plot
	//-------------------------------------------
	first_Screen_point.set_Point(end_x, end_y);
	second_Screen_point.set_Point(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	//-------------------------------------------
	//  Plot the main line, i.e., from the radar position to the end of line (the "head" of line)
	//-------------------------------------------
	Radar_Post_Panel_Graphics->DrawLine(Pen_helicopter, PointF((float)first_Screen_point.Screen_X, SCREEN_SIZE_Y - ((float)first_Screen_point.Screen_Y)), PointF((float)second_Screen_point.Screen_X, SCREEN_SIZE_Y - ((float)second_Screen_point.Screen_Y)));
}

void C_Radar_Post::Offset_Radar_Position(float delta_pixels_x, float delta_pixels_y)
{
	//-----------------------------------
	// Move the radar_route array (with his all points and his all detections and trajectories) to the next location:
	//	
	//				new_location_x = old_location_x + delta_pixels_x;
	//				new_location_y = old_location_y + delta_pixels_y;
	//-----------------------------------
	translate_radar_Matrix = gcnew Matrix;
	translate_radar_Matrix->Translate(delta_pixels_x, delta_pixels_y, MatrixOrder::Append);
	//
	//	translate the 'radar_Path' array with 'translate_radar_Matrix' offset.
	//
	radar_Path->Transform(translate_radar_Matrix);
	//
	//	translate the 'detection_Path_Pylon' and 'detection_Path_Wire' arrays 
	//	with 'translate_radar_Matrix' offset.
	//
	detection_Path_Pylon->Transform(translate_radar_Matrix);
	detection_Path_Wire->Transform(translate_radar_Matrix);
	//
	//	translate the 'trajectory_Path_Pylon' and 'trajectory_Path_Wire' arrays 
	//	with 'translate_radar_Matrix' offset.
	//
	trajectory_Path_Pylon->Transform(translate_radar_Matrix);
	trajectory_Path_Wire->Transform(translate_radar_Matrix);
	//-------------------------------------------
	//  Dispose 'translate_radar_Matrix' of the radar. 
	//-------------------------------------------
	delete translate_radar_Matrix;
}

void C_Radar_Post::Update_Scale(float scale_x, float scale_y)
{	
	/*array<PointF>^ detections_points = detection_Path_Wire->PathPoints;
	detection_Path_Wire->Reset();
	for (int i = 0; i < detections_points->Length - 4; i = i + 4)
	{
		detections_points[i].X = (float)(
			detections_points[i].X *
			(radar_position.get_Meter_Per_Pixel() / 10)
			);

		detections_points[i].Y = (float)(
			detections_points[i].Y *
			(radar_position.get_Meter_Per_Pixel() / 10)
			);

		detection_Path_Wire->AddRectangle(RectangleF(detections_points[i], size_of_rectangle));
	}*/
}

void C_Radar_Post::Translate_Radar_Shape(float delta_x, float delta_y)
{
	//-------------------------------------------
	// Create a matrix and translate the radar shape (=radarPath).
	//-------------------------------------------
	rotate_radar_Matrix = gcnew Matrix;
	rotate_radar_Matrix->Translate(delta_x, delta_y, MatrixOrder::Append);
	radar_Path->Transform(rotate_radar_Matrix);
	//-------------------------------------------
	//  Dispose 'rotate_radar_Matrix' the position of the radar.
	//-------------------------------------------
	delete rotate_radar_Matrix;
}

void C_Radar_Post::Translate_Detection_Shape(float delta_x, float delta_y)
{
	//-------------------------------------------
	// Create a matrix and translate the Detection shape (= detection_Path_Pylon && detection_Path_Wire)
	//-------------------------------------------
	rotate_radar_Matrix = gcnew Matrix;
	rotate_radar_Matrix->Translate(
		/*Detections_Array[0]->Get_Pylon_1().Screen_X + */ delta_x, 
		/*Detections_Array[0]->Get_Pylon_1().Screen_Y + */ delta_y, 
		MatrixOrder::Append);

	detection_Path_Pylon->Transform(rotate_radar_Matrix);
	detection_Path_Wire->Transform(rotate_radar_Matrix);
	//-------------------------------------------
	//  Dispose 'rotate_radar_Matrix' the position of the radar.
	//-------------------------------------------
	delete rotate_radar_Matrix;
}