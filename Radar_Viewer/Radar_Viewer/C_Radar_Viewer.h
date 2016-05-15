#ifndef C_RADAR_VIEWER_H
#define C_RADAR_VIEWER_H
//-----------------------------------------
//	Radar_Viewer --> C_Radar_Viewer.h
//-----------------------------------------
#include "C_GUI_Status.h"
#include "C_Data_Recording.h"
#include "C_Radar_Route.h"
#include "C_Obstacles_Map.h"
#include "C_Lat_Lon_Map.h"
#include "C_RDM.h"


namespace Radar_Viewer
{
	public ref class C_Radar_Viewer
	{
		//-----------------------------------------
		//				Fields
		//-----------------------------------------
		private:
		//-----------------------------------------
		//		Data structures
		//-----------------------------------------
		C_Obstacles_Map			EOM;
		C_Obstacles_Map			TOM;

		C_Radar_Route			Radar_Route;
		C_Lat_Lon_Map^			New_Input;

		C_RDM					RDM;
		//-----------------------------------------
		//			Auxiliaries
		//-----------------------------------------
		C_Position^				Last_screen_point_of_wire;
		C_Position^				Point_mouse_move;

		bool					Start_wire_from_mouse;
		//-----------------------------------------
		//		GUI data
		//-----------------------------------------
		C_GUI_Status			GUI_Status;
		//-----------------------------------------
		//		Graphics
		//-----------------------------------------
		Panel^					Viewer_Panel;
		Graphics^				Viewer_Panel_Graphics;

		Panel^					MAP_Chart_Panel;
		Graphics^				MAP_Chart_Panel_Graphics;
		//-----------------------------------------
		//				Constructor
		//-----------------------------------------
		public:					C_Radar_Viewer();
		//
		// TODO: 
		//
		~C_Radar_Viewer();
		////-------------------------------------------
		////		Set/Get: Base_Meter_Per_Pixel_For_Scale
		////-------------------------------------------
		//double get_Base_Meter_Per_Pixel_For_Scale();
		void Set_Base_Meter_Per_Pixel_For_Scale(double meter_per_pixel_other);
		//-------------------------------------------
		//		Set: Show Detections
		//-------------------------------------------
		void Set_Show_Detections(bool new_detections_status);
		//-------------------------------------------
		//		Set: Show Trajectories
		//-------------------------------------------
		void Set_Show_Trajectories(bool new_trajectories_status);
		//-----------------------------------------
		//				Public Methods
		//-----------------------------------------
		public:
		String^					Initialize(Panel^ Viewer_Panel_other, PictureBox^ Viewer_Video_other, C_GUI_Status% GUI_Status_other);
		String^					Initialize(Panel^ Viewer_Panel_other, C_GUI_Status% GUI_Status_other);

		void					Clear_Radar_Viewer();
		bool					Reset_Radar_Viewer();
		
		String^					Viewer_Step();

		void					Add_Radar_Post(C_Position% Radar_post_other);

		bool					Load_TOM_From_File();
		bool					Load_Detections_From_File();

		void					Set_Viewer_Scale(double screen_width_meter);
		void					Set_Scale(double screen_width_meter);

		void					Offset_Viewer_Position(int delta_pixels_x, int delta_pixels_y);

		void					Erase_Line();
		void					Mouse_Move(int X_Pixel, int Y_Pixel);

		void					Add_Pylon(int X_Pixel, int Y_Pixel);
		void					Add_Wire(int X_Pixel, int Y_Pixel);

		void					Restart_Real_Time();
		void					Restart_Offline();
		void					Clear_Screen(); // remove this function

		void					Create_TOM_Array();
		void					Create_Radar_Route_Position();

		void					Plot_TOM_On_Screen();

		void					Offset_TOM_Array(float delta_pixels_x, float delta_pixels_y);
		void                    Offset_Radar_Position(float delta_pixels_x, float delta_pixels_y);

		double					Update_RDM(Point% RDM_Point);

		void					Add_Radar_Post();
		bool					Add_Radar_Post(C_Data_Recording^  data_recording_of_radar);

		bool					Reset_Step_Radar_Position_Real_Time();
		String^					Plot_Step_Position_Of_Radar();

		void					Set_Real_Time_Viewer_Scale(double screen_width_meter);

		// remove this function
		void					Real_Time_Offset_Viewer_Position(int delta_pixels_x, int delta_pixels_y);

		void					Set_Step_Viewer_Scale(double screen_width_meter);
		void					Set_Step_Radar_Scale(double screen_width_meter);

		void					Set_Step_Viewer_Position(C_Position% screen_bottom_left);
		void					Set_Step_Radar_Position(C_Position% screen_bottom_left);
		//-----------------------------------------
		//				Private Methods
		//-----------------------------------------
		private:
		bool					Load_Movie();
		void					Set_Viewer_Position(C_Position% screen_bottom_left);
	};
}
#endif



