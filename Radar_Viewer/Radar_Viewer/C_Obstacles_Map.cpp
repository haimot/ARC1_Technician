//-----------------------------------------
// This is the main DLL file.
//-----------------------------------------
#include <fstream>
#include "C_Obstacles_Map.h"
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
//		Obstacles map
//-----------------------------------------
#define		MAX_DETECTIONS					100
#define		PI								3.14159265358979323846
//-------------------------------------
//			Default Constructor
//-------------------------------------
C_Obstacles_Map::C_Obstacles_Map() : number_of_obstacles(0), index_of_current_obstacle(0)
{
	Obstacles_Map_Panel = gcnew Panel();

	obstacles = gcnew array<C_Detections^>(MAX_DETECTIONS);
	for (int i = 0; i < MAX_DETECTIONS; i++)
	{
		obstacles[i] = gcnew C_Detections;
	}

	TOM_Path = gcnew GraphicsPath;
	// -----------------------------------
	// Create a new custom pen.
	// -----------------------------------
	pen_TOM = gcnew Pen(Color::Black, 1.0F);
	// -----------------------------------
	// Create solid brush and size
	// -----------------------------------
	blackBrush = gcnew SolidBrush(Color::Black);
	size_of_rectangle = Size(5, 5);
}
//-------------------------------------
//			Destructor
//-------------------------------------
C_Obstacles_Map::~C_Obstacles_Map()
{
	if (Obstacles_Map_Panel)
	{
		delete Obstacles_Map_Panel;
	}

	if (TOM_Path)
	{
		delete TOM_Path;
	}
	// -----------------------------------
	// Dispose of the custom pen.
	// -----------------------------------
	if (pen_TOM)
	{
		delete pen_TOM;
	}
	// -----------------------------------
	// Dispose of the custom whiteBrush.
	// -----------------------------------
	if (blackBrush)
	{
		delete blackBrush;
	}
}
#pragma region Set And Get functions
// --------------------------------------------------
//  Set_Meter_Per_Pixel
//  Haim Otachi		28/10/2015
// 	Description:	The function Update the Meter Per Pixel of Pylon and Wire objects
// 	Reference: 
//	Input Value:	New value of Meter Per Pixel
//  Return Value: 
// --------------------------------------------------
void C_Obstacles_Map::Set_Meter_Per_Pixel(double Meter_Per_Pixel_Other)
{
	for (int i = 0; i < number_of_obstacles; i++)
	{
		obstacles[i]->Set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
	}
	//-------------------------------------------
	//	update the new Meter Per Pixel of structure
	//-------------------------------------------
	Screen_Bottom_Left.set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
	Screen_Top_Right.set_Meter_Per_Pixel(Meter_Per_Pixel_Other);
}
// --------------------------------------------------
//  Set_Screen_in_UTM
//  Haim Otachi		28/10/2015
// 	Description:	The function Update the Screen unit in UTM coordinate of Pylon and Wire objects
// 	Reference: 
//	Input Value:	New value of Screen unit of utm coordinate
//  Return Value: 
// --------------------------------------------------
void C_Obstacles_Map::Set_Screen_In_UTM_Origin(C_Position% Screen_Bottom_Left_Other)
{
	for (int i = 0; i < number_of_obstacles; i++)
	{
		obstacles[i]->Set_Screen_In_UTM_Origin(Screen_Bottom_Left_Other);
	}
}
// --------------------------------------------------
//  Radar_In_UTM_Position
//  Haim Otachi		24/11/2015
// 	Description:	The function Update the Radar in UTM position of the Radar relative to 'Pylon' and 'Wire'
// 	Reference: 
//	Input Value:	New value of Radar_In_UTM_Position
//  Return Value: 
// --------------------------------------------------
void C_Obstacles_Map::Set_Radar_In_UTM_Position(C_Position% Radar_In_UTM_Position)
{
	for (int i = 0; i < number_of_obstacles; i++)
	{
		obstacles[i]->Set_Radar_In_UTM_Position(Radar_In_UTM_Position);
	}
}
// --------------------------------------------------
//  Set_Radar_North
//  Haim Otachi		08/11/2015
// 	Description:	The function Update the Radar Yaw of the radar relative to 'Pylon' and 'Wire'
// 	Reference: 
//	Input Value:	New value of Radar Yaw
//  Return Value: 
// --------------------------------------------------
void C_Obstacles_Map::Set_Radar_North(double Radar_North)
{
	for (int i = 0; i < number_of_obstacles; i++)
	{
		obstacles[i]->Set_Radar_North(Radar_North);
	}
}
// --------------------------------------------------
//  Get_Pylon_1  
//  Haim Otachi    09/11/2015
// 	Description:    
// 	Reference:		
//  Input value:    
//  Return Value:	the position of 'Pylon_1'
// --------------------------------------------------
C_Position C_Obstacles_Map::Get_Pylon_1()
{
	C_Detections^ Current_Detection = obstacles[index_of_current_obstacle];
	return Current_Detection->Get_Pylon_1();
}
// --------------------------------------------------
//  Get_Pylon_2  
//  Haim Otachi    09/11/2015
// 	Description:    
// 	Reference:		
//  Input value:    
//  Return Value:	the position of 'Pylon_2'
// --------------------------------------------------
C_Position C_Obstacles_Map::Get_Pylon_2()
{
	C_Detections^ Current_Detection = obstacles[index_of_current_obstacle];
	return Current_Detection->Get_Pylon_2();
}
// --------------------------------------------------
//  Get_Number_Of_Obstacles  
//  Haim Otachi    06/03/2016
// 	Description:    
// 	Reference:		
//  Input value:    
//  Return Value:	number_of_obstacles
// --------------------------------------------------
int C_Obstacles_Map::Get_Number_Of_Obstacles()
{
	return number_of_obstacles;
}
// --------------------------------------------------
//  Get_Current_Obstacle_Type  
//  Haim Otachi    09/11/2015
// 	Description:    
// 	Reference:		
//  Input value:    
//  Return Value:	the Obstacle Type of the current obstacle map
// --------------------------------------------------
int C_Obstacles_Map::Get_Obstacle_Type()
{
	return obstacles[index_of_current_obstacle]->Get_Obstacle_Type();
}
// --------------------------------------------------
//  Get/Set:	   Reliability_Threshold 
//  Haim Otachi    09/11/2015
// 	Description:    
// 	Reference:		
//  Input value:    
//  Return Value:	the Reliability Threshold of the current obstacle map
// --------------------------------------------------
double C_Obstacles_Map::Get_Reliability_Threshold()
{
	return obstacles[index_of_current_obstacle]->Get_Reliability();
}
void C_Obstacles_Map::Set_Reliability_Threshold(double Reliability_Threshold)
{
	obstacles[number_of_obstacles]->Set_Reliability(Reliability_Threshold);
}

C_Detections^ C_Obstacles_Map::Obstacles::get(int current_index)
{
	return obstacles[current_index];
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
void C_Obstacles_Map::Initialize(Panel^ Obstacles_Map_Panel_other, C_Position% Init_Screen_Bottom_Left, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other)
{
	//--------------------------------------------------
	//		Initialize the Viewer Panel and him Graphics
	//--------------------------------------------------
	Obstacles_Map_Panel = Obstacles_Map_Panel_other;
	Obstacles_Map_Panel_Graphics = Obstacles_Map_Panel->CreateGraphics();
	//-------------------------------------------
	//	 Update all cells of data base with the primary data
	//-------------------------------------------
	for (int i = 0; i < MAX_DETECTIONS; i++)
	{
		obstacles[i]->Initialize(Obstacles_Map_Panel, Init_Screen_Bottom_Left, Max_Range_Error_Meter_Other, Reliability_Threshold_Other);
	}
	//-------------------------------------------
	//	 Update bottom left size of border with the primary data
	//-------------------------------------------
	Screen_Bottom_Left = Init_Screen_Bottom_Left;
}
// -----------------------------------------------------------
//  Load_From_File  
//  Haim Otachi		28/10/2015
// 	Description:	Load the obstacles point from the outside file to our system
// 	Reference: 
//  Input value:    path of the file / name of the file
//  Return Value: 
// -----------------------------------------------------------
bool C_Obstacles_Map::Load_From_File(char* file_name)
{
	//-------------------------------------------
	//				Fields
	//-------------------------------------------
	fstream file_stream;
	int Number_Of_Obstacles = 0;
	//-------------------------------------------
	//	 Open the file to read the obstacles
	//-------------------------------------------
	file_stream.open(file_name, std::ios_base::in);
	if (file_stream.is_open())
	{
		//-------------------------------------------
		//	 Read the number of obstacles from file
		//-------------------------------------------
		file_stream >> Number_Of_Obstacles;
		number_of_obstacles = Number_Of_Obstacles;
		// --------------------------------------------------
		//	load from file the obstacles (points) of Pylon/Wire
		// --------------------------------------------------
		for (int i = 0; i < number_of_obstacles; i++)
		{
			obstacles[i]->Load_From_File(file_stream);
		}
		// --------------------------------------------------
		//			close the file
		// --------------------------------------------------
		file_stream.close();
		// --------------------------------------------------
		//			we find the minimum and maximum points of border
		// --------------------------------------------------
		Find_Min_Max();

		return true;
	}
	return false;
}
// --------------------------------------------------
//  Save_To_File  
//  Haim Otachi     28/10/2015
// 	Description:	The function Save the obstacles point in the file 
// 	Reference: 
//  Input value:	path of the file / name of the file
//  Return Value: 
// --------------------------------------------------
void C_Obstacles_Map::Save_To_File(char* file_name)
{
	//-------------------------------------------
	//				Fields
	//-------------------------------------------
	fstream file_stream;
	// --------------------------------------------------
	//			Open the file to write
	// --------------------------------------------------
	file_stream.open(file_name, std::ios_base::out);
	if (file_stream.is_open())
	{
		// --------------------------------------------------
		//	write to file the number of obstacles 
		// --------------------------------------------------
		file_stream << number_of_obstacles << '\n';
		// --------------------------------------------------
		//	save in file the obstacles (points) of Pylon/Wire
		// --------------------------------------------------
		for (int i = 0; i < number_of_obstacles; i++)
		{
			obstacles[i]->Save_To_File(file_stream);
		}
		// --------------------------------------------------
		//			close the file
		// --------------------------------------------------
		file_stream.close();
	}
}
// -----------------------------------------------------------
//  Plot_Obstacles_To_Screen  
//  Haim Otachi		08/11/2015
// 	Description:	plot obstacles to screen
// 	Reference: 
//  Input value:	pointer to the panel graphics of the screen, color object to draw on canvas and 'Reliability_Threshold'
//					for General reliability level
//  Return Value: 
// -----------------------------------------------------------
// ALON: Consider using the mecahnism of initialization of the Graphics^ and other values as in the video class
void C_Obstacles_Map::Plot_Obstacles_To_Screen()
{
	for (int i = 0; i < number_of_obstacles; ++i)
	{
		obstacles[i]->Plot_Obstacles_To_Screen();
	}
}
// -----------------------------------------------------------
//  Plot_TOM_To_Screen  
//  Haim Otachi		17/04/2015
// 	Description:	plot TOM to screen
// 	Reference: 
//  Input value:	pointer to the panel graphics of the screen, color object to draw on canvas and 'Reliability_Threshold'
//					for General reliability level
//  Return Value: 
// -----------------------------------------------------------
void C_Obstacles_Map::Plot_TOM_To_Screen()
{
	// -----------------------------------
	//  draw the transformed ellipse to the screen
	//------------------------------------
	Obstacles_Map_Panel_Graphics->DrawPath(pen_TOM, TOM_Path);
}
// -----------------------------------------------------------
//  Update_TOM_Array  
//  Haim Otachi		20/04/2016
// 	Description:	Update TOM Array value by new delta pixels of x and y.
// 	Reference: 
//  Input value:	pointer to the panel graphics of the screen, color object to draw on canvas and 'Reliability_Threshold'
//					for General reliability level
//  Return Value: 
// -----------------------------------------------------------
void C_Obstacles_Map::Offset_Array(float delta_pixels_x, float delta_pixels_y)
{
	//-----------------------------------
	// Move the TOM array (with his all points) to the next location:
	//	
	// new_location_x = old_location_x + delta_pixels_x;
	// new_location_y = old_location_y + delta_pixels_y;
	//-----------------------------------
	Matrix^	translateMatrix = gcnew Matrix;
	translateMatrix->Translate(delta_pixels_x, delta_pixels_y);
	TOM_Path->Transform(translateMatrix);
	delete translateMatrix;
}
// -----------------------------------------------------------
//  Create_TOM_Array()  
//  Haim Otachi		20/04/2016
// 	Description:	create TOM array for plotting.
// 	Reference: 
//  Input value:	
//					
//  Return Value: 
// -----------------------------------------------------------
void C_Obstacles_Map::Create_TOM_Array()
{
	int					counter_wires = 0;
	int					x_point = 0;
	int					y_point = 0;
	int					pylon_position_shift = (int)(PYLON_SIZE_TRUE / 2);

	double				new_x = 0;
	double				new_y = 0;

	GraphicsPath^		currentPath = gcnew GraphicsPath;
	array<Point>^		TOM_Array_Help = gcnew array<Point>(2);

	Rectangle			pylon_1;
	Rectangle			pylon_2;

	Point				p;

	TOM_Path->Reset();

	int i = 0, j = 0;
	while (i < number_of_obstacles)
	{
		// -----------------------------------
		//			'Pylon' case
		//------------------------------------
		if (obstacles[i]->Get_Obstacle_Type() == OBSTACLE_PYLON)
		{
			x_point = obstacles[i]->Get_Pylon_1().Screen_X - pylon_position_shift;
			y_point = SCREEN_SIZE_Y - (obstacles[i]->Get_Pylon_1().Screen_Y - pylon_position_shift);

			if (j == 1)
			{
				currentPath->Reset();
				TOM_Array_Help[j] = Point(x_point, y_point);

				if (counter_wires == 1)
				{
					TOM_Path->StartFigure();
					//-----------------------------------
					//	add the first pylon of wire to 'TOM_Path' array
					//------------------------------------
					p.X = TOM_Array_Help[0].X - 2;
					p.Y = TOM_Array_Help[0].Y - 2;

					pylon_1 = Rectangle(p, size_of_rectangle);
					currentPath->AddRectangle(pylon_1);
					//-----------------------------------
					//	add the current wire to 'TOM_Path' array
					//------------------------------------
					currentPath->AddLine(TOM_Array_Help[0], TOM_Array_Help[1]);
					//-----------------------------------
					//	add the second pylon of wire to 'TOM_Path' array
					//------------------------------------
					p.X = TOM_Array_Help[1].X - 2;
					p.Y = TOM_Array_Help[1].Y - 2;

					pylon_2 = Rectangle(p, size_of_rectangle);
					currentPath->AddRectangle(pylon_2);

					counter_wires = 0;
				}
				else
				{
					TOM_Path->StartFigure();
					//-----------------------------------
					//	add the single pylon of wire to 'TOM_Path' array	
					//------------------------------------
					p.X = TOM_Array_Help[1].X - 2;
					p.Y = TOM_Array_Help[1].Y - 2;

					pylon_2 = Rectangle(p, size_of_rectangle);
					currentPath->AddRectangle(pylon_2);
				}

				TOM_Path->AddPath(currentPath, false);
				j = 0;
			}
			// -----------------------------------
			//		we need to fill the array
			//------------------------------------
			else
			{
				TOM_Array_Help[j] = Point(x_point, y_point);
				j++;
				i++;
			}
		}
		// -----------------------------------
		//			'Wire' case
		//------------------------------------
		else
		{
			counter_wires++;
			i++;
		}
	}
}
// --------------------------------------------------
//  Insert_new_obstacle_Wire
//  Haim Otachi 16/8/2015
// 	Description:	Insert new Wire to the obstacles map 
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
void C_Obstacles_Map::Add_Wire(C_Position% Last_screen_point_of_wire, C_Position% new_wire_position)
{
	obstacles[number_of_obstacles]->Add_Wire(Last_screen_point_of_wire, new_wire_position);
	number_of_obstacles++;
}
// --------------------------------------------------
//  Add_Pylon  
//  Haim Otachi     15/10/2015
// 	Description:    the function add new pylon to the system of EOM/TOM
// 	Reference:		
//  Input value:    new pylon of C_Position class
//  Return Value:	
// --------------------------------------------------
void C_Obstacles_Map::Add_Pylon(C_Position% New_Pylon)
{
	obstacles[number_of_obstacles]->Add_Pylon(New_Pylon);
	number_of_obstacles++;
}
// --------------------------------------------------
//  Check_True  
//  Haim Otachi     28/10/2015
// 	Description:    the function check if the 'index_of_current_obstacle' is smaller than 'number_of_obstacles'
//                  And return 'true' or 'false' Depends on the situation
// 	Reference:		
//  Input value:    
//  Return Value:	true or false 
// --------------------------------------------------
bool C_Obstacles_Map::Check_True()
{
	return index_of_current_obstacle < number_of_obstacles;
}
// --------------------------------------------------
//  Update_To_Next_Cell  
//  Haim Otachi     28/10/2015
// 	Description:	The function promotes one to value of the pointer to next cell
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
void C_Obstacles_Map::Move_To_Next_Cell()
{
	index_of_current_obstacle++;
}
// --------------------------------------------------
//  Restart  
//  Haim Otachi     28/10/2015
// 	Description:	The function reset the pointer of the system
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
void C_Obstacles_Map::Restart()
{
	index_of_current_obstacle = 0;

	Obstacles_Map_Panel_Graphics->Transform = gcnew Matrix;
}
// --------------------------------------------------
//  Clear  
//  Haim Otachi     28/10/2015
// 	Description:	The function initialize the pointer and the size of the system
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
void C_Obstacles_Map::Clear()
{
	//-------------------------------------
	//	reset the pointers to structure
	//-------------------------------------
	index_of_current_obstacle = 0;
	number_of_obstacles = 0;
	//-------------------------------------
	//	reset the Extreme points of border
	//-------------------------------------
	Screen_Bottom_Left = C_Position();
	Screen_Top_Right = C_Position();

	Obstacles_Map_Panel_Graphics->Transform = gcnew Matrix;
}
#pragma endregion

#pragma region Error Function
double C_Obstacles_Map::operator - (C_Obstacles_Map% Obstacles_Map_Other)
{
	C_Obstacles_Map^ EOM = this;
	C_Obstacles_Map% TOM = Obstacles_Map_Other;
	//------------------------------------------------------
	//						Fields
	//------------------------------------------------------
	double RISK_MD = 0.5;
	double RISK_FA = 0.5;
	//------------------------------------------------------
	//	Calculate error function: Matching_EOM_to_TOM part
	//------------------------------------------------------
	EOM->Match_to(TOM);
	//------------------------------------------------------
	//	Calculate error function: Matching_TOM_to_EOM part
	//------------------------------------------------------
	TOM.Match_to(*EOM);
	//------------------------------------------------------
	//	Calculate error function: FA_err() part
	//------------------------------------------------------
	double estimation_error_FA = FA_err(TOM);
	//------------------------------------------------------
	//	Calculate error function: MD_err() part
	//------------------------------------------------------
	double estimation_error_MD = MD_err(TOM);
	//------------------------------------------------------
	//	return the distance between TOM and EOM = 'Error Function'
	//------------------------------------------------------
	return estimation_error_FA * RISK_FA + estimation_error_MD * RISK_MD;
}
// --------------------------------------------------
//  Matching_EOM_to_TOM  
//  Haim Otachi     15/10/2015
// 	Description:    Matching from EOM to TOM
// 	Reference:		EOM obstacle map object
//  Input value:    TOM obstacle map object
//  Return Value:	
// --------------------------------------------------
void C_Obstacles_Map::Match_to(C_Obstacles_Map% Obstacles_Map_Other)
{
	C_Position pi_1_Of_TOM;
	C_Position pi_2_Of_TOM;

	C_Position pi_1_Of_EOM;
	C_Position pi_2_Of_EOM;

	double minimum_range;
	// --------------------------------------------------
	//						Pylon
	// --------------------------------------------------
	C_Detections^ pylonE;
	C_Detections^ pylonT;

	for (int i = 0; i < number_of_obstacles; ++i)
	{
		minimum_range = DBL_MAX;
		pylonE = obstacles[i];
		if (pylonE->Get_Obstacle_Type() == OBSTACLE_PYLON)
		{
			//pylonE->Set_Matching_Index(-1);
			pylonE->Set_Matching_Index_Of_Pylon_1(-1);
			for (int j = 0; j < Obstacles_Map_Other.number_of_obstacles; ++j)
			{
				pylonT = Obstacles_Map_Other.obstacles[j];
				if (pylonT->Get_Obstacle_Type() == OBSTACLE_PYLON)
				{
					// --------------------------------------------------
					//	we take the pylon 1 of EOM (estimated obstacles map)
					// --------------------------------------------------
					pi_1_Of_EOM = pylonE->Get_Pylon_1();
					// --------------------------------------------------
					//	we take the pylon 1 of TOM (True obstacles map)
					// --------------------------------------------------
					pi_1_Of_TOM = pylonT->Get_Pylon_1();
					// --------------------------------------------------
					//	calculate the distance between 2 pi
					// --------------------------------------------------
					double distance_between_Two_Phi = pi_1_Of_TOM.Distance_between_Two_Phi(pi_1_Of_EOM);
					if (distance_between_Two_Phi < minimum_range)
					{
						minimum_range = distance_between_Two_Phi;
						//pylonE->Set_Matching_Index(j);
						pylonE->Set_Matching_Index_Of_Pylon_1(j);
					}
				}
			}
		}
	}
	// --------------------------------------------------
	//						Wire
	// --------------------------------------------------
	C_Detections^ wireE;
	C_Detections^ wireT;

	for (int i = 0; i < number_of_obstacles; ++i)
	{
		minimum_range = DBL_MAX;
		wireE = obstacles[i];
		if (wireE->Get_Obstacle_Type() == OBSTACLE_WIRE)
		{
			wireE->Set_Matching_Index(-1);
			wireE->Set_Matching_Index_Of_Pylon_1(-1);
			wireE->Set_Matching_Index_Of_Pylon_2(-1);

			for (int j = 0; j < Obstacles_Map_Other.number_of_obstacles; ++j)
			{
				wireT = Obstacles_Map_Other.obstacles[j];
				if (wireT->Get_Obstacle_Type() == OBSTACLE_WIRE)
				{
					double d1;
					double d2;
					// --------------------------------------------------
					//	we take the pylon of wire 1 of EOM (estimated obstacles map)
					// --------------------------------------------------
					pi_1_Of_EOM = wireE->Get_Pylon_1();
					// --------------------------------------------------
					//	we take the pylon of wire 2 of EOM (estimated obstacles map)
					// --------------------------------------------------
					pi_2_Of_EOM = wireE->Get_Pylon_2();
					// --------------------------------------------------
					//	we take the pylon of wire 1 of TOM (True obstacles map)
					// --------------------------------------------------
					pi_1_Of_TOM = wireT->Get_Pylon_1();
					// --------------------------------------------------
					//	we take the pylon of wire 2 of TOM (True obstacles map)
					// --------------------------------------------------
					pi_2_Of_TOM = wireT->Get_Pylon_2();

					d1 = pi_1_Of_TOM.Distance_between_Two_Phi(pi_1_Of_EOM);
					d2 = pi_2_Of_TOM.Distance_between_Two_Phi(pi_2_Of_EOM);

					if (((d1 + d2) / 2) < minimum_range)
					{
						minimum_range = (d1 + d2) / 2;
						wireE->Set_Matching_Index(j);
						wireE->Set_Matching_Index_Of_Pylon_1(1);
						wireE->Set_Matching_Index_Of_Pylon_2(2);
					}

					d1 = pi_2_Of_TOM.Distance_between_Two_Phi(pi_1_Of_EOM);
					d2 = pi_1_Of_TOM.Distance_between_Two_Phi(pi_2_Of_EOM);

					if (((d1 + d2) / 2) < minimum_range)
					{
						minimum_range = (d1 + d2) / 2;
						wireE->Set_Matching_Index(j);
						wireE->Set_Matching_Index_Of_Pylon_1(2);
						wireE->Set_Matching_Index_Of_Pylon_2(1);
					}
				}
			}
		}
	}
}
// --------------------------------------------------
//  FA_Pylon_error  
//  Haim Otachi     15/10/2015
// 	Description:	calculate the FA Pylon error
// 	Reference:		EOM obstacle map object
//  Input value:    TOM obstacle map object
//  Return Value:	estimation_error_FA_Pylon
// --------------------------------------------------
double C_Obstacles_Map::FA_Pylon_error(C_Obstacles_Map% TOM)
{
	double D_max = 150;
	double Cnr = 0.2; // 0 <= Cnr <= 1
	double Clf = pow(10, -4); // 0 < Clf

	double delta = 0;
	double Rnr = 0;
	double Rlf = 0;
	double epsilon = 0;

	double estimation_error_FA_Pylon = 0;
	// --------------------------------------------------
	//	Find the FA C_Pylon error
	// --------------------------------------------------
	for (int i = 0; i < number_of_obstacles; ++i)
	{
		C_Detections^ pylonE = obstacles[i];
		if (pylonE->Get_Obstacle_Type() == OBSTACLE_PYLON)
		{
			C_Detections^ pylonT = TOM.obstacles[pylonE->Get_Matching_Index()];
			if (pylonT->Get_Obstacle_Type() == OBSTACLE_PYLON)
			{
				// --------------------------------------------------
				//	we take the pylon 1 of EOM (estimated obstacles map)
				// --------------------------------------------------
				C_Position  pi_Hat = pylonE->Get_Pylon_1();
				// --------------------------------------------------
				//	we take the pylon 1 of TOM (True obstacles map)
				// --------------------------------------------------
				C_Position  temp_Pi = pylonT->Get_Pylon_1();
				// --------------------------------------------------
				//	calculate the distance between 2 pi
				// --------------------------------------------------
				delta = temp_Pi.DeltaFunction(pi_Hat, D_max);
				Rnr = temp_Pi.RnrFunction(pi_Hat, Cnr);
				Rlf = temp_Pi.RlfFunction(Clf);
				epsilon = delta * Rnr * Rlf;

				if (estimation_error_FA_Pylon < epsilon)
				{
					estimation_error_FA_Pylon = epsilon;
				}
			}
		}
	}
	return estimation_error_FA_Pylon;
}
// --------------------------------------------------
//  FA_Wire_error  
//  Haim Otachi     15/10/2015
// 	Description:	calculate the FA Wire error
// 	Reference:		EOM obstacle map object
//  Input value:    TOM obstacle map object
//  Return Value:	estimation_error_FA_Wire
// --------------------------------------------------
double C_Obstacles_Map::FA_Wire_error(C_Obstacles_Map% TOM)
{
	double D_max = 150;
	double Cnr = 0.2; // 0 <= Cnr <= 1
	double Clf = pow(10, -4); // 0 < Clf

	double delta = 0;
	double Rnr = 0;
	double Rlf = 0;
	double epsilon = 0;
	double epsilon_1 = 0;
	double epsilon_2 = 0;

	double estimation_error_FA_Wire = 0;
	// --------------------------------------------------
	//	Find the FA C_Pylon error
	// --------------------------------------------------
	for (int i = 0; i < number_of_obstacles; ++i)
	{
		C_Detections^ wireE = obstacles[i];
		if (wireE->Get_Obstacle_Type() == OBSTACLE_WIRE)
		{
			//first part
			C_Detections^ wireT = TOM.obstacles[wireE->Get_Matching_Index()];
			if (wireT->Get_Obstacle_Type() == OBSTACLE_WIRE)
			{
				C_Position temp_pi;
				C_Position pi_Hat;

				if (wireE->Get_Matching_Index_Of_Pylon_1() == 1)
				{
					temp_pi = wireT->Get_Pylon_1();
				}
				else if (wireE->Get_Matching_Index_Of_Pylon_1() == 2)
				{
					temp_pi = wireT->Get_Pylon_2();
				}
				// --------------------------------------------------
				//	We calculate the average range of the PNI road to the Wire
				// --------------------------------------------------
				double range_pylon_left = 0;
				double range_pylon_right = 0;

				double theta_pylon_left = 0;
				double theta_pylon_right = 0;

				double Cos_theta_pylon_left = 0;
				double Cos_theta_pylon_right = 0;

				double Average_Range = 0;
				// --------------------------------------------------
				//			We take the r_1 and r_2
				// --------------------------------------------------
				range_pylon_left = wireT->Get_Pylon_1().Get_Range();
				range_pylon_right = wireT->Get_Pylon_2().Get_Range();
				// --------------------------------------------------
				//			We take the theta_1 and theta_2
				// --------------------------------------------------
				theta_pylon_left = wireT->Get_Pylon_1().Get_Azimuth() - PI / 2;
				theta_pylon_right = wireT->Get_Pylon_2().Get_Azimuth() - PI / 2;
				// --------------------------------------------------
				//			We calculate the 'cos' of theta_1 and theta_2 - QA
				// --------------------------------------------------
				Cos_theta_pylon_left = cos(theta_pylon_left);
				Cos_theta_pylon_right = cos(theta_pylon_right);
				// --------------------------------------------------
				//			We calculate the average range 
				// --------------------------------------------------
				Average_Range = ((range_pylon_left * Cos_theta_pylon_left) + (range_pylon_right * Cos_theta_pylon_right)) / 2;

				pi_Hat = wireE->Get_Pylon_1();
				delta = temp_pi.DeltaFunction(pi_Hat, D_max);
				Rnr = temp_pi.RnrFunction(pi_Hat, Cnr);

				temp_pi.Set_Range(Average_Range);
				Rlf = temp_pi.RlfFunction(Clf);
				epsilon_1 = delta * Rnr * Rlf;

				if (wireE->Get_Matching_Index_Of_Pylon_2() == 1)
				{
					temp_pi = wireT->Get_Pylon_1();
				}
				else if (wireE->Get_Matching_Index_Of_Pylon_2() == 2)
				{
					temp_pi = wireT->Get_Pylon_2();
				}

				pi_Hat = wireE->Get_Pylon_2();
				delta = temp_pi.DeltaFunction(pi_Hat, D_max);
				Rnr = temp_pi.RnrFunction(pi_Hat, Cnr);

				temp_pi.Set_Range(Average_Range);
				Rlf = temp_pi.RlfFunction(Clf);
				epsilon_1 = delta * Rnr * Rlf;

				epsilon = (epsilon_1 + epsilon_2) / 2;
				if (estimation_error_FA_Wire < epsilon)
				{
					estimation_error_FA_Wire = epsilon;
				}
			}
		}
	}
	return estimation_error_FA_Wire;
}
// --------------------------------------------------
//  MD_Pylon_error  
//  Haim Otachi     15/10/2015
// 	Description:	calculate the MD Pylon error
// 	Reference:		TOM obstacle map object
//  Input value:    EOM obstacle map object
//  Return Value:	estimation_error_MD_Pylon
double C_Obstacles_Map::MD_Pylon_error(C_Obstacles_Map% Obstacles_Map_Other)
{
	double D_max = 150;
	double epsilon = 0;
	double Clf = pow(10, -4); // 0 < Clf

	double estimation_error_MD_Pylon = 0;
	// --------------------------------------------------
	//	Find the MD C_Pylon error
	// --------------------------------------------------
	C_Detections^ pylonE;
	C_Detections^ pylonT;

	C_Position pi_Hat;
	C_Position temp_pi;

	for (int i = 0; i < number_of_obstacles; ++i)
	{
		pylonT = obstacles[i];
		if (pylonT->Get_Obstacle_Type() == OBSTACLE_PYLON)
		{
			if (pylonT->Get_Matching_Index() >= 0)
			{
				pylonE = Obstacles_Map_Other.obstacles[pylonT->Get_Matching_Index()];
				if (pylonE->Get_Obstacle_Type() == OBSTACLE_PYLON)
				{
					temp_pi = pylonE->Get_Pylon_1();
					pi_Hat = Obstacles_Map_Other.obstacles[i]->Get_Pylon_1();

					if (temp_pi.DeltaFunction(pi_Hat, D_max) == 1)
					{
						epsilon = temp_pi.RlfFunction(Clf);
					}
					else
					{
						epsilon = 0;
					}
					if (estimation_error_MD_Pylon < epsilon)
					{
						estimation_error_MD_Pylon = epsilon;
					}
				}
			}
		}
	}
	return estimation_error_MD_Pylon;
}
// --------------------------------------------------
//  MD_Wire_error  
//  Haim Otachi     15/10/2015
// 	Description:	calculate the MD Wire error
// 	Reference:		EOM obstacle map object
//  Input value:    TOM obstacle map object
//  Return Value:	estimation_error_MD_Wire
// --------------------------------------------------
double C_Obstacles_Map::MD_Wire_error(C_Obstacles_Map% Obstacles_Map_Other)
{
	double D_max = 150;
	double Clf = pow(10, -4); // 0 < Clf
	double epsilon = 0;

	double estimation_error_MD_Wire = 0;
	// --------------------------------------------------
	//	Find the MD C_Wire error
	// --------------------------------------------------
	C_Detections^ wireE;
	C_Detections^ wireT;

	for (int i = 0; i < number_of_obstacles; ++i)
	{
		wireE = obstacles[i];
		if (wireE->Get_Obstacle_Type() == OBSTACLE_WIRE)
		{
			wireT = Obstacles_Map_Other.obstacles[wireE->Get_Matching_Index()];
			if (wireT->Get_Obstacle_Type() == OBSTACLE_WIRE)
			{
				C_Position temp_pi;
				C_Position pi_Hat;

				temp_pi = wireT->Get_Pylon_1();
				pi_Hat = wireE->Get_Pylon_1();
				//--------------------------------------------------
				//	We calculate the average range of the PNI road to the Wire
				//--------------------------------------------------
				double range_pylon_left = 0;
				double range_pylon_right = 0;

				double theta_pylon_left = 0;
				double theta_pylon_right = 0;

				double Cos_theta_pylon_left = 0;
				double Cos_theta_pylon_right = 0;

				double Average_Range = 0;
				// --------------------------------------------------
				//			We take the r_1 and r_2
				// --------------------------------------------------
				range_pylon_left = wireT->Get_Pylon_1().Get_Range();
				range_pylon_right = wireT->Get_Pylon_2().Get_Range();
				// --------------------------------------------------
				//			We take the theta_1 and theta_2
				// --------------------------------------------------
				theta_pylon_left = wireT->Get_Pylon_1().Get_Azimuth() - PI / 2;
				theta_pylon_right = wireT->Get_Pylon_2().Get_Azimuth() - PI / 2;
				// --------------------------------------------------
				//			We calculate the 'cos' of theta_1 and theta_2 - QA
				// --------------------------------------------------
				Cos_theta_pylon_left = cos(theta_pylon_left);
				Cos_theta_pylon_right = cos(theta_pylon_right);
				// --------------------------------------------------
				//			We calculate the average range 
				// --------------------------------------------------
				Average_Range = ((range_pylon_left * Cos_theta_pylon_left) + (range_pylon_right * Cos_theta_pylon_right)) / 2;

				if (temp_pi.DeltaFunction(pi_Hat, D_max) == 1)
				{
					temp_pi.Set_Range(Average_Range);
					epsilon = temp_pi.RlfFunction(Clf);
				}
				else
				{
					epsilon = 0;
				}
				if (estimation_error_MD_Wire < epsilon)
				{
					estimation_error_MD_Wire = epsilon;
				}

				temp_pi = wireT->Get_Pylon_2();
				pi_Hat = wireE->Get_Pylon_2();

				if (temp_pi.DeltaFunction(pi_Hat, D_max) == 1)
				{
					temp_pi.Set_Range(Average_Range);
					epsilon = temp_pi.RlfFunction(Clf);
				}
				else
				{
					epsilon = 0;
				}
				if (estimation_error_MD_Wire < epsilon)
				{
					estimation_error_MD_Wire = epsilon;
				}
			}
		}
	}
	return estimation_error_MD_Wire;
}
// --------------------------------------------------
//  FA_err  
//  Haim Otachi     15/10/2015
// 	Description:	calculate the FA error
// 	Reference:		EOM obstacle map object
//  Input value:    TOM obstacle map object
//  Return Value:	max value between 'estimation_error_FA_Pylon' and 'estimation_error_FA_Wire'
// --------------------------------------------------
double C_Obstacles_Map::FA_err(C_Obstacles_Map% OBSTACLE)
{
	double estimation_error_FA_Pylon = FA_Pylon_error(OBSTACLE);
	double estimation_error_FA_Wire = FA_Wire_error(OBSTACLE);

	return fmax(estimation_error_FA_Pylon, estimation_error_FA_Wire);
}
// --------------------------------------------------
//  MD_err  
//  Haim Otachi     15/10/2015
// 	Description:	calculate the MD error
// 	Reference:		EOM obstacle map object
//  Input value:    TOM obstacle map object
//  Return Value:	max value between 'estimation_error_MD_Pylon' and 'estimation_error_MD_Wire'
// --------------------------------------------------
double C_Obstacles_Map::MD_err(C_Obstacles_Map% OBSTACLE)
{
	C_Obstacles_Map^ EOM = this;
	C_Obstacles_Map% TOM = OBSTACLE;

	double estimation_error_MD_Pylon = TOM.MD_Pylon_error(*EOM);
	double estimation_error_MD_Wire = EOM->MD_Wire_error(TOM);

	return fmax(estimation_error_MD_Pylon, estimation_error_MD_Wire);
}
#pragma endregion

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
bool C_Obstacles_Map::Is_Empty()
{
	double Bottom_Latitude = Screen_Bottom_Left.Latitude;
	double Bottom_Longitude = Screen_Bottom_Left.Longitude;
	//---------------------------------------------------
	//	check if the 'Screen_Bottom_Left' is equal to Zero
	//---------------------------------------------------
	if (Bottom_Latitude != 0 || Bottom_Longitude != 0)
	{
		return false;
	}
	return true;
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
void C_Obstacles_Map::Find_Min_Max()
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
	for (int i = 0; i < number_of_obstacles; i++)
	{
		//-------------------------------------------
		//		find the minimum and maximum of current point
		//-------------------------------------------
		obstacles[i]->Find_Min_Max(max_Lat, max_Lon, min_Lat, min_Lon);
	}
	//-------------------------------------------
	//	 Finalizing: Updating the border of the screen relative the minimum and maximum in UTM coordinate unit
	//-------------------------------------------
	Screen_Top_Right.set_Object_in_UTM_Position(max_Lat, max_Lon, max_Alt);
	Screen_Bottom_Left.set_Object_in_UTM_Position(min_Lat, min_Lon, min_Alt);
}

void C_Obstacles_Map::Update_Scale(float scale_x, float scale_y)
{
	// -----------------------------------
	// Create a matrix and scale it.
	// -----------------------------------
	Matrix^ myMatrix = gcnew Matrix;
	myMatrix->Scale(scale_x, scale_y, MatrixOrder::Append);
	// -----------------------------------
	// Draw the rectangle to the screen again after applying the transform.
	// -----------------------------------
	Obstacles_Map_Panel_Graphics->Transform = myMatrix;
	delete myMatrix;
}