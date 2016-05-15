#ifndef C_DETECTIONS_H
#define C_DETECTIONS_H

#include "T_PNI.h"
#include "T_SENSOR_data.h"
#include "T_Trajectory.h"
#include "C_Position.h"
#include <fstream>
//-----------------------------------------
//	using namespace:	ROD_Position
//						System::Windows::Forms
//						System::Drawing
//
//	using				std::fstream
//-----------------------------------------
using namespace ROD_Position;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using std::fstream;
//-----------------------------------------
//		Class:		C_Detections
//-----------------------------------------
public ref class C_Detections
{
	//-------------------------------------
	//			Fields
	//-------------------------------------
private:
	//-------------------------------------
	//			Data of first detection
	//-------------------------------------
	C_Position				pylon_1;
	int						matching_index_of_pylon_1;
	//-------------------------------------
	//			Data of second detection
	//-------------------------------------
	C_Position				pylon_2;
	int						matching_index_of_pylon_2;
	//-------------------------------------
	//			the PNI data op 'pylon' opr 'wire'
	//-------------------------------------
	T_PNI*					PNI_Data_of_detection;
	//-----------------------------------------
	//		Auxiliaries
	//-----------------------------------------
	int						obstacle_type;
	int						matching_index;
	//
	// reliability threshold for print detection - 'Pylon' or 'Wire' .
	//
	int						reliability_threshold;
	int						max_error_range_meter;
	//-----------------------------------------
	//		Graphics
	//-----------------------------------------
	Panel^					Detection_Panel;
	Graphics^				Detection_Panel_Graphics;

	//Panel^					Detection_MAP_Chart_Panel;
	//Graphics^				Detection_MAP_Chart_Panel_Graphics;
	//-----------------------------------------
	//	The color of the printed obstacles:		
	//			1.
	//			2.	
	//			3.
	//-----------------------------------------
	Pen^					Pen_target_pylon;
	Pen^					Pen_target_wire;
	Pen^					Pen_target_unknown;

	public:
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	C_Detections();
	//-------------------------------------
	//			Destructor
	//-------------------------------------
	~C_Detections();
	//-------------------------------------------
	//			Set Screen in UTM position
	//-------------------------------------------
	void Set_Screen_In_UTM_Origin(C_Position% Screen_Bottom_Left_Other);
	//-------------------------------------------
	//			Set Radar In UTM Position
	//-------------------------------------------
	void Set_Radar_In_UTM_Position(C_Position% Radar_In_UTM_Position);
	//-------------------------------------------
	//			Get  the pylon_1 of the obstacle map OBJECT
	//-------------------------------------------
	C_Position Get_Pylon_1();
	//-------------------------------------------
	//			Get  the pylon_2 of the obstacle map OBJECT
	//-------------------------------------------
	C_Position Get_Pylon_2();
	//-------------------------------------------
	//			Set Obstacle_Position
	//-------------------------------------------
	void Set_Obstacle_Position(C_Position% Obstacle_Position_other);
	//-------------------------------------------
	//			Set: Meter Per Pixel
	//-------------------------------------------
	void Set_Meter_Per_Pixel(double Meter_Per_Pixel_Other);
	//-------------------------------------------
	//			Set: Radar North
	//-------------------------------------------
	void Set_Radar_North(double Radar_North);

	void Set_Screen_Position(int screen_x, int screen_y);
	//-------------------------------------------
	//			Set/Get: Reliability
	//-------------------------------------------
	double Get_Reliability();
	void Set_Reliability(double Reliability);
	//-------------------------------------------
	//			Set/Get: Current Obstacle type of the obstacle map OBJECT
	//-------------------------------------------
	int Get_Obstacle_Type();
	void Set_Obstacle_Type(int Obstacle_Type);
	//-------------------------------------------
	//			Set/Get: Current Matching_Index
	//-------------------------------------------
	int Get_Matching_Index();
	void Set_Matching_Index(int Matching_Index);
	//-------------------------------------------
	//			Set/Get: Current Matching_Index_Of_Pylon_1
	//-------------------------------------------
	int Get_Matching_Index_Of_Pylon_1();
	void Set_Matching_Index_Of_Pylon_1(int Matching_Index_Of_Pylon_1);
	//-------------------------------------------
	//			Set/Get: Current Matching_Index_Of_Pylon_2
	//-------------------------------------------
	int Get_Matching_Index_Of_Pylon_2();
	void Set_Matching_Index_Of_Pylon_2(int Matching_Index_Of_Pylon_2);

	Point^ operator=(C_Detections^ detections_other);
	//-------------------------------------
	//			Methods
	//-------------------------------------
	public:
	void	Initialize(Panel^ Detection_Panel_Other, C_Position% Init_Screen_Bottom_Left, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other);
	
	void	Load_From_File(fstream% file_stream);
	void	Save_To_File(fstream% file_stream);

	void	Plot_TOM_To_Screen();
	void	Plot_Obstacles_To_Screen();
	void	Plot_Detection_To_Screen();
	void	Plot_Trajectory_To_Screen(int screen_x, int screen_y);
	//
	//	Offline Functions
	//
	void	Plot_Detection_To_Screen_In_Offline_Mode(int screen_x, int screen_y);

	void	Add_Pylon(C_Position% New_Pylon);
	void	Add_Wire(C_Position% First_Point_Of_Pylon, C_Position% Second_Point_Of_Pylon);

	void	Add_Detection(T_PNI% PNI, T_SENSOR_data% SENSOR_data);
	void	Add_Detection(double& Polarization, double& Azimuth, double& Range, double& Reliability);
	void	Add_Trajectory(T_Trajectory% Trajectory, T_SENSOR_data% SENSOR_data);

	void	Find_Min_Max(double& Max_Lat, double& Max_Lon, double& Min_Lat, double& Min_Lon);

private:
	void	Plot_Pylon();
	void	Plot_Wire();

	void    Draw_Triangular_Of_Detection(Pen^ Pen_Trajectory, int screen_x, int screen_y);
};
#endif




