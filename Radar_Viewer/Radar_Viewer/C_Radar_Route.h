#ifndef C_RADAR_ROUTE_H
#define C_RADAR_ROUTE_H
//-----------------------------------------
//			Radar_Route.h
//-----------------------------------------
#include "C_Radar_Post.h"
#include "T_Radar_Data.h"
#include "C_GUI_Status.h"
#include "C_Lat_Lon_Map.h"
#include "C_Data_Recording.h"

#define		MAX_STRING_LENGTH				512
//-----------------------------------------
//		Class:	C_Radar_Route
//-----------------------------------------
public ref class C_Radar_Route
{
	//-------------------------------------
	//				Fields
	//-------------------------------------
	private:
	//-------------------------------------
	//			posts realized as a linked-list in an array
	//-------------------------------------
	array<C_Radar_Post^>^				Radar_Post_array;
	int									index_to_post_in_the_Post_array;
	int									number_of_posts_in_the_Post_array;

	C_Lat_Lon_Map^						Next_Radar_Post;
	//-------------------------------------
	//			help pointer (only for me)
	//-------------------------------------
	C_Radar_Post^						Current_Radar_Post;
	//-----------------------------------------
	//		Graphics
	//-----------------------------------------
	Panel^								Route_Panel;
	Graphics^							Route_Panel_Graphics;

	//Panel^								Route_MAP_Chart_Panel;
	//Graphics^							Route_MAP_Chart_Panel_Graphics;
	//-----------------------------------------
	//		Auxiliaries:  Data of Radar struct
	//-----------------------------------------
	T_Radar_Data*						Radar_Data;
	double								Variance_Position_Wires;
	//-----------------------------------------
	//			Border of the Screen
	//-----------------------------------------
	public:
	C_Position							Screen_Top_Right;
	C_Position							Screen_Bottom_Left;
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	public: C_Radar_Route();
	//-------------------------------------
	//			Destructor
	//-------------------------------------
	public: ~C_Radar_Route();

	public:
	//-------------------------------------------
	//		get Current Radar Position
	//-------------------------------------------
	C_Position Get_Current_Radar_Position();
	//-------------------------------------------
	//		get Current Radar Post
	//-------------------------------------------
	C_Radar_Post^ Get_Current_Radar_Post();
	//-------------------------------------------
	//		Get Current Time Stamp of SENSOR_data
	//-------------------------------------------
	public: void Set_New_Route_Of_Radar(bool route_new);
	//-------------------------------------------
	//		Set Next Radar Post
	//-------------------------------------------
	void Set_Data_Of_Radar_Post(C_Lat_Lon_Map^	Next_Radar_Post_Other);
	//-------------------------------------------
	//		Set: Show Detections
	//-------------------------------------------
	void Set_Show_Detections(bool new_detections_status);
	//-------------------------------------------
	//		Set: Show Trajectories
	//-------------------------------------------
	void Set_Show_Trajectories(bool new_trajectories_status);
	//-------------------------------------------
	//		for QA of error function
	//-------------------------------------------
	int Get_Current_Number_Of_Post_In_Radar_Route();

	void Set_Screen_Coordinates(int screen_x, int screen_y);
	//-------------------------------------------
	//		Set: Base_Meter_Per_Pixel_For_Scale
	//-------------------------------------------
	void Set_Base_Meter_Per_Pixel_For_Scale(double meter_per_pixel_other);
	#pragma region Public Methods
	//-------------------------------------------
	//		Public Methods
	//-------------------------------------------
	public:
	void					Initialize(Panel^ Route_Panel_Other, C_Position% Radar_routing_Position, C_GUI_Status% GUI_Status);

	void					Initialize_Screen_Border();
	bool					Current_Point_In_Screen();

	bool					Load_From_File(char* file);
	void					Save_To_File(char* file);

	void					Update_Meter_Per_Pixel(double Meter_Per_Pixel_Other);
	void					Update_Screen_in_UTM(C_Position% Screen_Bottom_Left_Other);
	T_SENSOR_data			Update_Current_SENSOR_Data_Of_Radar_Post();

	C_Position				Calc_The_Next_Point();

	bool					Move_To_Next_Radar_Post();
	//
	//	TODO: remove this function 'Plot_Radar_Post()'
	//
	void					Plot_Radar_Post();

	void					Add_Radar_Post();
	bool					Add_Radar_Post(T_Radar_Massage% Radar_Massage);
	void					Add_Radar_Post(C_Position% Radar_post_other);
	bool					Add_Radar_Post(C_Data_Recording% Data_Recording_Other);

	void					Add_Obstacle_Position(C_Position% Obstacle_Position_Other);

	void					Calc_First_Point();
	bool					Calc_Detect_Pylon(C_Obstacles_Map% TOM, C_Position% target_PNI);
	bool					Calc_Detect_Wire(C_Obstacles_Map% TOM, C_Position% target_PNI);
	void					Calc_False_Alarm();

	void					Offset_Radar_Position(float delta_pixels_x, float delta_pixels_y);
	void					Update_Scale(float scale_x, float scale_y);
	void					Create_Radar_Route_Position();

	bool					Is_Empty();
	void					Clear();
	void					Restart();
	//-----------------------------------------
	//			real time functions 
	//-----------------------------------------	
	void					Add_New_Step_Radar_Post();
	bool					Move_To_Next_Step_Radar_Post();
	void					Update_Meter_Per_Pixel_For_Real_Time(double Meter_Per_Pixel_Other);
	void					Update_Screen_in_UTM_For_Real_Time(C_Position% Screen_Bottom_Left_Other);
	void					Update_Screen_Position();
	#pragma endregion

	#pragma region Private Methods
	//-------------------------------------------
	//		Private Methods
	//-------------------------------------------
	private:
	void					Initial_Radar_Position(Panel^ Route_Panel_Other, C_Position% Radar_routing_Position, int Max_Range_Error_Meter_Other, int Reliability_Threshold_Other);
	C_Point2DInt			Generate_Initial_Data();

	bool					Is_Pylon_Detectable(C_Obstacles_Map% TOM, C_Position% target_PNI);
	bool					Is_Wire_Detectable(C_Obstacles_Map% TOM, C_Position% target_PNI);

	C_Position				Calc_Border_Top_Right();
	C_Position				Calc_Border_Bottom_Left();
	C_CartesianPoint		Calc_Next_point();

	void					Update_Current_Radar_Post();
	void					Clear_Radar_Data();

	int						Calc_RDM_Size(char Radar_Data_File[MAX_STRING_LENGTH][MAX_STRING_LENGTH]);
	int						Find_Value_In_File(char File[MAX_STRING_LENGTH][MAX_STRING_LENGTH], char* Line);
	int						Find_Line_In_File(char File[MAX_STRING_LENGTH][MAX_STRING_LENGTH], char* Line);

	void					Find_Min_Max();
	#pragma endregion
};

#endif