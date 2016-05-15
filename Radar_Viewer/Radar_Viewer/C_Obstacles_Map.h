#ifndef C_OBSTACLES_MAP_H
#define C_OBSTACLES_MAP_H
//-----------------------------------------
//			C_Obstacles_Map.h file
//-----------------------------------------
#pragma once

#include <iostream>
#include "C_Detections.h"
//-----------------------------------------
//		Obstacles map
//-----------------------------------------
#define		OBSTACLE_PYLON					1
#define		OBSTACLE_WIRE					2
#define		OBSTACLE_UNKNOWN				3

using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
//-----------------------------------------
//		Class:	C_Obstacles_Map
//-----------------------------------------
public ref class C_Obstacles_Map
{
	//-------------------------------------
	//			Fields
	//-------------------------------------
	private:
	array<C_Detections^>^			obstacles;
	int								index_of_current_obstacle;
	int								number_of_obstacles;
	//-----------------------------------------
	//		Graphics
	//-----------------------------------------
	Panel^							Obstacles_Map_Panel;
	Graphics^						Obstacles_Map_Panel_Graphics;

	//Panel^						Obstacles_MAP_Chart_Panel;
	//Graphics^						Obstacles_MAP_Chart_Panel_Graphics;
	// -----------------------------------
	//		Create a path 
	//------------------------------------
	public:
	GraphicsPath^					TOM_Path;

	RectangleF						point_before_scale;
	RectangleF						point_after_scale;
	private:
	// -----------------------------------
	// Create a new custom pen
	// -----------------------------------
	Pen^							pen_TOM;
	// -----------------------------------
	// Create solid brush and size
	// -----------------------------------
	SolidBrush^						blackBrush;
	Size							size_of_rectangle;
	//-----------------------------------------
	//		Auxiliaries
	//-----------------------------------------
	public:
	C_Position						Screen_Top_Right;
	C_Position						Screen_Bottom_Left;
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	public: C_Obstacles_Map();
			~C_Obstacles_Map();

	public:
	//-------------------------------------------
	//			Get: the pylon_1 of the obstacle map OBJECT
	//-------------------------------------------
	C_Position Get_Pylon_1();
	//-------------------------------------------
	//			Get  the pylon_2 of the obstacle map OBJECT
	//-------------------------------------------
	C_Position Get_Pylon_2();
	//-------------------------------------------
	//			Get the number_of_obstacles
	//-------------------------------------------
	int Get_Number_Of_Obstacles();
	//-------------------------------------------
	//			Set: Screen in UTM
	//-------------------------------------------
	void Set_Screen_In_UTM_Origin(C_Position% Screen_Bottom_Left_Other);
	//-------------------------------------------
	//			Set Radar_In_UTM_Position
	//-------------------------------------------
	void Set_Radar_In_UTM_Position(C_Position% Radar_In_UTM_Position);
	//-------------------------------------------
	//			Set: Radar in UTM
	//-------------------------------------------
	void Set_Radar_North(double Radar_North);
	//-------------------------------------------
	//			Set: Meter Per Pixel
	//-------------------------------------------
	void Set_Meter_Per_Pixel(double Meter_Per_Pixel_Other);
	//-------------------------------------------
	//			Get: Obstacle type of the obstacle map OBJECT
	//-------------------------------------------
	int Get_Obstacle_Type();
	//-------------------------------------------
	//			Set/Get: Reliability threshold of the current obstacle map OBJECT
	//-------------------------------------------
	double Get_Reliability_Threshold();
	void Set_Reliability_Threshold(double Reliability_Threshold);
	//-------------------------------------------
	//			Property: Obstacles[int]
	//-------------------------------------------
	property C_Detections^ Obstacles[int] {C_Detections^ get(int current_index); }
	//-------------------------------------------
	//			Operator Overloading:   Error Function 
	//-------------------------------------------
	double operator-(C_Obstacles_Map% Obstacles_Map_Other);
	//-------------------------------------------
	//			 Methods
	//-------------------------------------------
	public:
	void Initialize(Panel^ Obstacles_Map_Panel_other, C_Position% Init_Screen_Bottom_Left, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other);

	bool Load_From_File(char* file_name);
	void Save_To_File(char* file_name);

	void Create_TOM_Array();
	void Plot_TOM_To_Screen();
	void Offset_Array(float delta_pixels_x, float delta_pixels_y);
	void Update_Scale(float scale_x, float scale_y);
	void Plot_Obstacles_To_Screen();

	void Add_Pylon(C_Position% New_Pylon);
	void Add_Wire(C_Position% Last_screen_point_of_wire, C_Position% new_wire_position);

	bool Is_Empty();
	bool Check_True();
	void Move_To_Next_Cell();
	void Restart();
	void Clear();

	private:
	void Find_Min_Max();
	//-------------------------------------------
	//			   Error Function 
	//-------------------------------------------
	void Match_to(C_Obstacles_Map% Obstacles_Map_Other);

	double FA_err(C_Obstacles_Map% TOM);
	double MD_err(C_Obstacles_Map% TOM);

	double FA_Pylon_error(C_Obstacles_Map% TOM);
	double FA_Wire_error(C_Obstacles_Map% TOM);

	double MD_Pylon_error(C_Obstacles_Map% EOM);
	double MD_Wire_error(C_Obstacles_Map% TOM);
};

#endif




