#ifndef C_RADAR_POST_H
#define C_RADAR_POST_H

#include "C_Detections.h"
#include "T_SENSOR_data.h"
#include "T_Radar_Massage.h"
#include "T_Trajectories.h"

using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
//-----------------------------------------
//		Class:	C_Radar_Post
//-----------------------------------------
public ref class C_Radar_Post
{
	//-------------------------------------
	//				Fields
	//-------------------------------------
	private:
	C_Position							radar_position;
	bool								plot_noice_route_of_radar;
	//
	//	Detections Structure
	//
	array<C_Detections^>^				Detections_Array;
	int									current_detection;
	int									number_of_detections;

	bool								show_detections;
	//
	//	Trajectories Structure
	//
	array<C_Detections^>^				trajectories_Array;
	int									current_trajectory;
	int									number_of_trajectories;

	bool								show_trajectories;
	//-----------------------------------------
	//		Graphics
	//-----------------------------------------
	Panel^								Radar_Post_Panel;
	Graphics^							Radar_Post_Panel_Graphics;
	Graphics^							Detection_Panel_Graphics;
	Graphics^							Trajectories_Panel_Graphics;

	Panel^								Radar_Post_MAP_Chart_Panel;
	Graphics^							Radar_Post_MAP_Chart_Panel_Graphics;
	//-----------------------------------------
	// Create a GraphicsPath object for radar.
	//-----------------------------------------
	public:
	GraphicsPath^						radar_Path;
	Matrix^								translate_radar_Matrix;
	Matrix^								rotate_radar_Matrix;

	double								base_meter_per_pixel_for_scale;
	//-----------------------------------------
	// Create a GraphicsPath object for detection.
	//-----------------------------------------
	GraphicsPath^						detection_Path_Pylon;
	GraphicsPath^						detection_Path_Wire;

	Matrix^								translate_detection_Matrix;
	//-----------------------------------------
	// Create a GraphicsPath object for trajectory.
	//-----------------------------------------
	GraphicsPath^						trajectory_Path_Pylon;
	GraphicsPath^						trajectory_Path_Wire;
	
	Matrix^								translate_trajectory_Matrix;

	private:
	//-----------------------------------------
	//	The color of the printed radar:			'Pen_helicopter'
	//-----------------------------------------
	Pen^								Pen_helicopter;
	//-----------------------------------------
	//	The color of the printed detection:		'Pen_detectioner'
	//-----------------------------------------
	Pen^								Pen_detection;
	Pen^								Pen_detection_Pylon;
	Pen^								Pen_detection_Wire;
	//-----------------------------------------
	//	The color of the printed trajectory:	'Pen_trajectory'
	//-----------------------------------------
	SolidBrush^							Pen_trajectory;
	// -----------------------------------
	// Create solid brush and size
	// -----------------------------------
	SolidBrush^							blackBrush;
	Size								size_of_rectangle;

	public:
	T_SENSOR_data*						sensor_data;
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	public:
	C_Radar_Post();
	//-------------------------------------
	//				Destructor
	//-------------------------------------
	~C_Radar_Post();
	//-------------------------------------------
	//		Property: Radar_Position
	//-------------------------------------------
	property C_Position Radar_Position { C_Position get(); void set(C_Position Radar_Position_other); }
	//-------------------------------------------
	//		Property: Current Radar Position In UTM
	//-------------------------------------------
	property C_UTM_Coordinates Radar_Position_In_UTM {  C_UTM_Coordinates get(); void set(C_UTM_Coordinates Radar_UTM_other); }
	//-------------------------------------------
	//		Property: Current Detection
	//-------------------------------------------
	property C_Detections^ Current_Detection { C_Detections^ get(); }
	//-------------------------------------------
	//		Property: SENSOR_data
	//-------------------------------------------
	property T_SENSOR_data SENSOR_data { T_SENSOR_data get(); }
	//-------------------------------------------
	//		Property: get Radar_in_UTM_North of obstacle position in Detection_Array of C_Detection class
	//-------------------------------------------
	property double Radar_in_UTM_North { double get(); }
	//-------------------------------------------
	//		Set: Show Detections
	//-------------------------------------------
	void Set_Show_Detections(bool new_detections_status);
	//-------------------------------------------
	//		Set: Show Trajectories
	//-------------------------------------------
	void Set_Show_Trajectories(bool new_trajectories_status);


	void Set_Screen_Coordinates(int screen_x, int screen_y);
	void Update_Screen_Position();
	//-------------------------------------------
	//		Set: Base_Meter_Per_Pixel_For_Scale
	//-------------------------------------------
	void Set_Base_Meter_Per_Pixel_For_Scale(double meter_per_pixel_other);
	//-------------------------------------------
	//			 Public Methods
	//------------------------------------------
	public:
	bool			Initialize(Panel^ Radar_Post_Panel_Other, C_Position% Radar_routing_Position, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other);
	void			Update_Meter_Per_Pixel(double Meter_Per_Pixel_Other);
	void			Update_Screen_in_UTM(C_Position% Screen_Bottom_Left);

	void			Draw_Arrow_Of_Heading();
	void			Plot_Noice_Route_Of_Radar();
	void			Plot_Detections_To_Screen();
	void			Plot_Trajectories_To_Screen();

	bool			Add_Radar_Post(T_Radar_Massage% Radar_Massage);
	bool			Add_Radar_Post(T_Radar_Massage% Radar_Massage, T_Trajectories% Trajectories);

	void			Add_Obstacle(C_Position% Point_Obstacle_other);
	void			Add_Detection(double Polarization, double Azimuth, double Range, double Reliability);

	bool			Line_angle(C_Position% Pylon_1, C_Position% Pylon_2);
	double			Distance_To(C_Position% Position_Other);
	double			Azimuth_To(C_Position% Position_Other);

	bool			Target_is_in_RADAR_FOV(C_Position% Position, int Radar_Max_Range, int Radar_FOV, double Variance_Position_Wires);
	void			Find_Min_Max(double& Max_Lat, double& Max_Lon, double& Min_Lat, double& Min_Lon);

	void			Offset_Radar_Position(float delta_pixels_x, float delta_pixels_y);
	void			Update_Scale(float scale_x, float scale_y);
	//
	// Create Shapes
	//
	void			Create_Radar_Shape();
	void			Create_Detection_Shape();
	void			Create_Trajectory_Shape();
	//
	// Translate to Shapes
	//
	void			Translate_Radar_Shape(float delta_x, float delta_y);
	void			Translate_Detection_Shape(float delta_x, float delta_y);
	//-------------------------------------------
	//			 Private Methods
	//------------------------------------------
	private:
	void			Clear();
	void			Restart();

};

#endif