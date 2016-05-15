#ifndef C_GUI_Status_H
#define C_GUI_Status_H

#include "T_GUI_Data.h"
#include "T_DISAPLAY_fields.h"
#include "C_Point2D.h"
//-----------------------------------------
//		Field of Initial data
//-----------------------------------------
#define		RELIABILITY_THRESHOLd						7
#define		WIRE_SEGMENT_LENGTH_METEr					8
#define		MAX_RANGE_ERROR_METER						9
//-----------------------------------------
//		Class:		C_INITIAL_data
//-----------------------------------------
public ref class C_GUI_Status
{
	#pragma region Private Fields
	//-----------------------------------------
	//			Public Fields
	//-----------------------------------------
	public:
	T_GUI_Data*					GUI_Data;
	T_DISAPLAY_fields*			disaplay_fields;
	//-----------------------------------------
	//			Private Fields
	//-----------------------------------------
	//	this pointer points to 'TxRx_control' array into 'FLASH_fields' struct 
	private:  
	int						control_MODE_index;
	T_TxRx_control*			current_TxRx_control;
	#pragma endregion
	
	#pragma region Constructor / Destructor
	public:
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	C_GUI_Status();
	//-------------------------------------
	//			Destructor
	//-------------------------------------
	~C_GUI_Status();
	//-------------------------------------
	//			Copy Constructor
	//-------------------------------------
	C_GUI_Status(C_GUI_Status% GUI_Status_Other);
	#pragma endregion

	#pragma region Property
	//-------------------------------------------
	//				Radar_Data
	//-------------------------------------------
	property T_Radar_Data Radar_Data { T_Radar_Data get(); }
	//-------------------------------------------
	//				General_Data
	//-------------------------------------------
	property T_General_Data General_Data { T_General_Data get(); }
	//-------------------------------------------
	//				Radar_Speed
	//-------------------------------------------
	property int Radar_Speed { int get(); }
	//-------------------------------------------
	//				Radar_Range
	//-------------------------------------------
	property int Radar_Range { int get(); }
	//-------------------------------------------
	//				Radar_FOV
	//-------------------------------------------
	property int Radar_FOV { int get(); }
	//-------------------------------------------
	//				Radar_Refresh_Time
	//-------------------------------------------
	property int Radar_Refresh_Time { int get(); }
	//-------------------------------------------
	//				Route_New
	//-------------------------------------------
	property bool Route_New { bool get(); }
	//-------------------------------------------
	//				Show Detections
	//-------------------------------------------
	property bool Show_Detections { bool get(); }
	//-------------------------------------------
	//				Show Trajectories
	//-------------------------------------------
	property bool Show_Trajectories { bool get(); }
	//-------------------------------------------
	//				Variance_Position_Wires
	//-------------------------------------------
	property int Variance_Position_Wires { int get(); }
	//-------------------------------------------
	//				False_Alarm_Rate
	//-------------------------------------------
	property int False_Alarm_Rate { int get(); }
	//-------------------------------------------
	//				Max_Range_Error_Meter
	//-------------------------------------------
	property int Max_Range_Error_Meter { int get(); }
	//-------------------------------------------
	//				Radar_Min_Range
	//-------------------------------------------
	property int Radar_Min_Range { int get(); void set(int Radar_Min_Range_Other); }
	//-------------------------------------------
	//				Reliability_Threshold
	//-------------------------------------------
	property int Reliability_Threshold { int get(); }
	//-------------------------------------------
	//				Wire_Segment_Length_Meter
	//-------------------------------------------
	property int Wire_Segment_Length_Meter { int get(); }
	//-------------------------------------------
	//				Screen_Width
	//-------------------------------------------
	property int Screen_Width { int get(); void set(int New_Screen_Width); }
	//-------------------------------------------
	//				Screen_Width of simulator
	//-------------------------------------------
	property int Screen_Width_Of_Simulator { int get(); }
	//-------------------------------------------
	//				Screen_Width of viewer
	//-------------------------------------------
	property int Screen_Width_Of_Viewer { int get(); void set(int New_Screen_Width_Meter); }
	//-------------------------------------------
	//				GPS_Latitude of simulator
	//-------------------------------------------
	property double Simulator_GPS_Latitude { double get(); }
	//-------------------------------------------
	//				GPS_Longitude of simulator
	//-------------------------------------------
	property double Simulator_GPS_Longitude { double get(); }
	//-------------------------------------------
	//				Meter_Per_Pixel of simulator
	//-------------------------------------------
	property double Meter_Per_Pixel_Of_Simulator { double get(); void set(double Meter_Per_Pixel); }
	//-------------------------------------------
	//				OBSTACLES_File_Name Of Flight Simulator
	//-------------------------------------------
	property char* Simulator_TOM_File_Name { char* get(); void set(char* OBSTACLES_file_name); }
	//-------------------------------------------
	//				EXPERIMENT_Directory Of Flight Simulator
	//-------------------------------------------
	property char* Simulator_EXPERIMENT_Directory_File_Name { char* get(); void set(char* EXPERIMENT_Directory); }
	//-------------------------------------------
	//				DETECTIONS_Folder Of Flight Simulator
	//-------------------------------------------
	property char* Simulator_DETECTIONS_Folder_File_Name { char* get(); void set(char* DETECTIONS_Folder); }
	//-------------------------------------------
	//				GPS_Latitude of Viewer
	//-------------------------------------------
	property double Viewer_GPS_Latitude { double get(); void set(double GPS_Latitude); }
	//-------------------------------------------
	//				GPS_Longitude of Viewer
	//-------------------------------------------
	property double Viewer_GPS_Longitude { double get(); void set(double GPS_Longitude); }
	//-------------------------------------------
	//				Meter_Per_Pixel of Viewer
	//-------------------------------------------
	property double Meter_Per_Pixel_Of_Viewer { double get(); void set(double Meter_Per_Pixel); }
	//-------------------------------------------
	//				OBSTACLES_File_Name Of Viewer
	//-------------------------------------------
	property char* Viewer_TOM_File_Name { char* get(); void set(char* OBSTACLES_file_name); }
	//-------------------------------------------
	//				DETECTIONS_Folder Of Viewer
	//-------------------------------------------
	property char* DETECTIONS_Folder_Of_Viewer { char* get(); void set(char* DETECTIONS_Folder); }
	//-------------------------------------------
	//				TxRx_Control of 'DISAPLAY_fields-->FLASH_fields' struct
	//-------------------------------------------
	property T_TxRx_control TxRx_Control[int] { T_TxRx_control get(int index); }
	#pragma endregion

	#pragma region Public_Methods
	//-------------------------------------------
	//			Public Methods
	//-------------------------------------------	
	void		Initialize();

	bool		Read_Data_From_File();
	bool		Save_Data_To_File();

	C_Point2D	Find_Delta(double theta);
	generic<typename T> void Update(int newValue, T GUI_Data_New_Value);
	//-----------------------------------------------------------
	//			Function relative to 'disaplay_fields --> DEBUG controls'
	//-----------------------------------------------------------
	void		Update_Debug_SNAPSHOT_Type(E_SNAPSHOT_type snapshot_type_index);
	void		Update_Debug_MATLAB_Script_Index(int matlab_script_index);
	void		Update_Debug_MATLAB_Script(System::String^ matlab_script);
	void		Update_Debug_Log_Folder(System::String^ debug_log_folder);
	//-----------------------------------------------------------
	//			Function relative to 'disaplay_fields --> FLASH controls'
	//-----------------------------------------------------------
	void		Update_Flash_Controls(int choice, int control_MODE_index, int32_t value);
	double		Calc_Batch_Duartion();

	double		Update_Velocity_Buffers(uint32_t maximal_doppler);
	uint32_t	Update_Number_Of_Buffers(uint32_t current_number_of_buffers);

	void		Update_TxRx_Control();

	//int			create_experiment_folder();
	//-----------------------------------------------------------
	//			Function relative to 'disaplay_fields --> MAINTENANCE controls'
	//-----------------------------------------------------------
	generic<typename T>
	void		Update_Maintenance_Controls(int choice, T value);
	#pragma endregion

	#pragma region Private_Methods
	//-------------------------------------------
	//			Private Methods
	//-------------------------------------------
	private:
	bool		Read_GUI_Status_From_File();
	bool		Save_GUI_Status_TO_File();
	void		Initialize_GUI_Status();

	bool		Read_DISAPLAY_fields_Data_From_File();
	bool		Save_DISAPLAY_fields_To_File();
	void		Initialize_DISAPLAY_fields();
	#pragma endregion
};

#endif