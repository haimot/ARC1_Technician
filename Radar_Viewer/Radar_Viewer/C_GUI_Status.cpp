#include "C_GUI_Status.h"
#include <fstream>
#include <msclr\marshal.h>

#pragma region define controls
#define		PI												3.14159265358979323846
//-----------------------------------------
//		FILES & FOLDERS
//-----------------------------------------
#define		INITIAL_VALUES_FILE_NAME_OF_GUI_Status			"GUI_Status_INIT_FORM.bin"
#define		INITIAL_VALUES_FILE_NAME_OF_disaplay_fields		"DISAPLAY_FIELDS_INIT_FORM.bin"
#define		MAX_STRING_LENGTH								512
//-----------------------------------------
//		Obstacles map
//-----------------------------------------
#define		MAX_RANGE_ERROR									100	   //[m]
#define		RELIABILITY_THRESHOLD							25
#define		WIRE_SEGMENT_LENGTH_METER						400
//-----------------------------------------
//		Display
//-----------------------------------------
#define		MAP_BASE_LAT									32.056143
#define		MAP_BASE_LON									34.931614
//-----------------------------------------
//		Field of Initial data
//-----------------------------------------
#define		ROUTE_STATUS								0
#define		RADAR_SPEED									1
#define		RADAR_REFRESH_TIME							2
#define		RADAR_RANGE									3
#define		RADAR_FOV									4
#define		VARIANCE_POSITION_WIRES						5
#define		SHOW_DETECTIONS								6
#define     SHOW_TRAJECTORIES							7
//#define		RELIABILITY_THRESHOLd						7
//#define		WIRE_SEGMENT_LENGTH_METEr					8
//#define		MAX_RANGE_ERROR_METER						9
#define		FALSE_ALARM_RATE							10

#define		UTM_COORDINATE_Latitude_Of_Simulator		11
#define		UTM_COORDINATE_Longitude_Of_Simulator		12

#define		UTM_COORDINATE_Latitude_Of_Viewer			13
#define		UTM_COORDINATE_Longitude_Of_Viewer			14

#define     SCREEN_WIDTH_OF_SIMULATOR					15
//-----------------------------------------------------------
//			TxRx_control	controls
//-----------------------------------------------------------
#define			PROFILE_AD9910A							1
#define			PROFILE_AD9910B							2

#define			CHIP_LENGTH_AD9910A						3
#define			CHIP_LENGTH_AD9910B						4

#define			SELECT_TX1								5
#define			SELECT_TX2								6
#define			SELECT_TX3								7

#define         SELECT_PROBE							8
#define         IO_UPDATE_RATE							9

#define         TX_1_ON									10	
#define         TX_2_ON									11
#define         TX_3_ON									12	

#define         E_PROBE_ON								13	
#define         E_TX_LO_TR								14
#define			E_ANT_SAMPLE_SELECT						15

#define         ATTN_TX_1								16
#define         ATTN_TX_2								17
#define         ATTN_TX_3								18
#define         ATTN_RX_1								19
#define         ATTN_RX_2								20
#define         ATTN_RX_3								21
#define         ATTN_RX_4								22

#define			AD9910_SET_AUX_DAC_A					23
#define			AD9910_SET_AUX_DAC_B					24

#define			BUFFER_LENGTH							25
#define			FIFO_LENGTH								26
#define			E_IO_UPDATE_ON							27
//-----------------------------------------------------------
//			DET_algorithms	controls
//-----------------------------------------------------------
#define			OFFSET_SAMPLES							28
#define			RANGE_SAMPLES							29

#define			TARGET_DETECTION_1ST_THRESHOLD			30
#define			TARGET_DETECTION_2ST_THRESHOLD			31

#define			Range_DECIMATION						32
#define			AGC_THRESHOLD							33
//-----------------------------------------------------------
//			TGT_calibrate	controls
//-----------------------------------------------------------
#define			PROBE_START_SAMPLE						34
#define			PROBE_END_SAMPLE						35
#define			CALIBRATOR_START_SAMPLE					36
#define			CALIBRATOR_END_SAMPLE					37
//-----------------------------------------------------------
//			PROBE_test	controls
//-----------------------------------------------------------
#define			PROBE_TEST_PROFILE						38
#define			PROBE_TEST_GAIN							39
//-----------------------------------------------------------
//			TxRx_MODE	controls
//-----------------------------------------------------------
#define			TXRX_MODE								40
//-----------------------------------------------------------
//			SYSTEM_ID	controls
//-----------------------------------------------------------
#define			SYSTEM_ID								41

#define         RF2_Support								42
//-----------------------------------------------------------
//			MAINTENANCE	controls
//-----------------------------------------------------------
#define			RESET_AFTER_BOOT_UPLOAD					43
#define			OUTFILE_DIRECTORY_OMR					44
#define			OUTFILE_DIRECTORY_DET					45
#define			OUTFILE_DIRECTORY_CHAB					46
#define			OUTFILE_DIRECTORY_MCU					47
#define			OUTFILE_DIRECTORY_RF_MCU				48
//-----------------------------------------------------------
//			Batch duration - FPGA
//-----------------------------------------------------------
#define			ZERO_PADDING							4
#pragma endregion

using namespace System;
using namespace msclr::interop;

using std::ifstream;
using std::fstream;
using std::ios;

#pragma region Constructor / Destructor
// --------------------------------------------------
//  C_GUI_Status - Default Constructor
//  Haim Otachi     28/12/2015
// 	Description:	the function initialize the:
//						1. 'GUI_Status' 
//						2. 'disaplay_fields' 
//					structs with simple 'malloc'
// 	Reference: 
//
//  Return Value:	
// --------------------------------------------------
C_GUI_Status::C_GUI_Status()
{ 
	//-----------------------------------------
	//				Malloc 
	//-----------------------------------------
	GUI_Data = (T_GUI_Data*)malloc(sizeof(T_GUI_Data));
	disaplay_fields = (T_DISAPLAY_fields*)malloc(sizeof(T_DISAPLAY_fields));
	current_TxRx_control = (T_TxRx_control*)malloc(sizeof(T_TxRx_control));
}
//-------------------------------------
//			Copy Constructor
//-------------------------------------
C_GUI_Status::C_GUI_Status(C_GUI_Status% GUI_Status_Other)
{
	GUI_Data = GUI_Status_Other.GUI_Data;
}
// --------------------------------------------------
//  C_GUI_Status - Destructor
//  Haim Otachi     28/12/2015
// 	Description:	the function delete the:
//						1. 'GUI_Status' 
//						2. 'disaplay_fields' 
//
//					structs with delete function
// 	Reference: 
//
//  Return Value:	
// --------------------------------------------------
C_GUI_Status::~C_GUI_Status()
{
	//-------------------------------------
	//	  delete the 'GUI_Status' object
	//-------------------------------------
	if (GUI_Data != NULL)
	{
		free(GUI_Data);
		GUI_Data = NULL;
	}
	//-------------------------------------
	//	  delete the 'disaplay_fields' object
	//-------------------------------------
	if (disaplay_fields != NULL)
	{
		free(disaplay_fields);
		disaplay_fields = NULL;
	}
}
#pragma endregion

#pragma region Property
//-------------------------------------------
//				Radar_Data
//-------------------------------------------
T_Radar_Data C_GUI_Status::Radar_Data::get() { return GUI_Data->Radar_Data; }
//-------------------------------------------
//				General_Data
//-------------------------------------------
T_General_Data C_GUI_Status::General_Data::get() { return GUI_Data->General_Data; }
//-------------------------------------------
//				Radar_Speed
//-------------------------------------------
int C_GUI_Status::Radar_Speed::get() { return GUI_Data->Radar_Data.Radar_Speed; }
//-------------------------------------------
//				Radar_Range
//-------------------------------------------
int C_GUI_Status::Radar_Range::get() { return GUI_Data->Radar_Data.Radar_Max_Range; }
//-------------------------------------------
//				Radar_FOV
//-------------------------------------------
int C_GUI_Status::Radar_FOV::get() { return GUI_Data->Radar_Data.Radar_FOV; }
//-------------------------------------------
//				Radar_Refresh_Time
//-------------------------------------------
int C_GUI_Status::Radar_Refresh_Time::get() { return GUI_Data->Radar_Data.Radar_Refresh_Time; }
//-------------------------------------------
//				Route_New
//-------------------------------------------
bool C_GUI_Status::Route_New::get() { return GUI_Data->Radar_Data.Route_New; }
//-------------------------------------------
//				Show Detections
//-------------------------------------------
bool C_GUI_Status::Show_Detections::get(){ return GUI_Data->General_Data.Show_Detections; }
//-------------------------------------------
//				Show Trajectories
//-------------------------------------------
bool C_GUI_Status::Show_Trajectories::get(){ return GUI_Data->General_Data.Show_Trajectories; }
//-------------------------------------------
//				Variance_Position_Wires
//-------------------------------------------
int C_GUI_Status::Variance_Position_Wires::get() { return GUI_Data->General_Data.Variance_Position_Wires; }
//-------------------------------------------
//				False_Alarm_Rate
//-------------------------------------------
int C_GUI_Status::False_Alarm_Rate::get() { return GUI_Data->General_Data.False_Alarm_Rate; }
//-------------------------------------------
//				Max_Range_Error_Meter
//-------------------------------------------
int C_GUI_Status::Max_Range_Error_Meter::get() { return GUI_Data->General_Data.Max_Error_Range_Meter; }
//-------------------------------------------
//				Radar_Min_Range
//-------------------------------------------
int C_GUI_Status::Radar_Min_Range::get()
{
	return  GUI_Data->Radar_Data.Radar_Min_Range;
}
void C_GUI_Status::Radar_Min_Range::set(int Radar_Min_Range_Other)
{
	GUI_Data->Radar_Data.Radar_Min_Range = Radar_Min_Range_Other;
}
//-------------------------------------------
//				Reliability_Threshold
//-------------------------------------------
int C_GUI_Status::Reliability_Threshold::get() { return GUI_Data->General_Data.Reliability_Threshold; }
//-------------------------------------------
//				Wire_Segment_Length_Meter
//-------------------------------------------
int C_GUI_Status::Wire_Segment_Length_Meter::get() { return GUI_Data->General_Data.Wire_Segment_Length_Meter; }
//-------------------------------------------
//				Screen_Width
//-------------------------------------------
int C_GUI_Status::Screen_Width::get() { return GUI_Data->General_Data.Screen_Width; }
void C_GUI_Status::Screen_Width::set(int New_Screen_Width) { GUI_Data->General_Data.Screen_Width = New_Screen_Width; }
//-------------------------------------------
//				Screen_Width of simulator
//-------------------------------------------
int C_GUI_Status::Screen_Width_Of_Simulator::get() { return GUI_Data->Simulator_Data.Screen_Width; }
//-------------------------------------------
//				Screen_Width of viewer
//-------------------------------------------
int C_GUI_Status::Screen_Width_Of_Viewer::get() { return GUI_Data->Viewer_Data.Screen_Width_meter; }
void C_GUI_Status::Screen_Width_Of_Viewer::set(int New_Screen_Width_Meter) { GUI_Data->Viewer_Data.Screen_Width_meter = New_Screen_Width_Meter; }
//-------------------------------------------
//				GPS_Latitude of simulator
//-------------------------------------------
double C_GUI_Status::Simulator_GPS_Latitude::get() { return GUI_Data->Simulator_Data.GPS_latitude; }
//-------------------------------------------
//				GPS_Longitude of simulator
//-------------------------------------------
double C_GUI_Status::Simulator_GPS_Longitude::get() { return GUI_Data->Simulator_Data.GPS_longitude; }
//-------------------------------------------
//				Meter_Per_Pixel of simulator
//-------------------------------------------
double C_GUI_Status::Meter_Per_Pixel_Of_Simulator::get() { return GUI_Data->Simulator_Data.Meter_Per_Pixel; }
void C_GUI_Status::Meter_Per_Pixel_Of_Simulator::set(double Meter_Per_Pixel) { GUI_Data->Simulator_Data.Meter_Per_Pixel = Meter_Per_Pixel; }
//-------------------------------------------
//				OBSTACLES_File_Name Of Flight Simulator
//-------------------------------------------
char* C_GUI_Status::Simulator_TOM_File_Name::get() { return GUI_Data->Simulator_Data.OBSTACLES_file_name; }
void C_GUI_Status::Simulator_TOM_File_Name::set(char* OBSTACLES_file_name) { strcpy_s(GUI_Data->Simulator_Data.OBSTACLES_file_name, OBSTACLES_file_name); }
//-------------------------------------------
//				EXPERIMENT_Directory Of Flight Simulator
//-------------------------------------------
char* C_GUI_Status::Simulator_EXPERIMENT_Directory_File_Name::get() { return GUI_Data->Simulator_Data.EXPERIMENT_directory; }
void C_GUI_Status::Simulator_EXPERIMENT_Directory_File_Name::set(char* EXPERIMENT_Directory) { strcpy_s(GUI_Data->Simulator_Data.EXPERIMENT_directory, EXPERIMENT_Directory); }
//-------------------------------------------
//				DETECTIONS_Folder Of Flight Simulator
//-------------------------------------------
char* C_GUI_Status::Simulator_DETECTIONS_Folder_File_Name::get() { return GUI_Data->Simulator_Data.DETECTIONS_folder; }
void C_GUI_Status::Simulator_DETECTIONS_Folder_File_Name::set(char* DETECTIONS_Folder) { strcpy_s(GUI_Data->Simulator_Data.DETECTIONS_folder, DETECTIONS_Folder); }
//-------------------------------------------
//				GPS_Latitude of Viewer
//-------------------------------------------
double C_GUI_Status::Viewer_GPS_Latitude::get() { return GUI_Data->Viewer_Data.GPS_latitude; }
void C_GUI_Status::Viewer_GPS_Latitude::set(double GPS_Latitude) { GUI_Data->Viewer_Data.GPS_latitude = GPS_Latitude; }
//-------------------------------------------
//				GPS_Longitude of Viewer
//-------------------------------------------
double C_GUI_Status::Viewer_GPS_Longitude::get() { return GUI_Data->Viewer_Data.GPS_longitude; }
void C_GUI_Status::Viewer_GPS_Longitude::set(double GPS_Longitude) { GUI_Data->Viewer_Data.GPS_longitude = GPS_Longitude; }
//-------------------------------------------
//				OBSTACLES_File_Name Of Viewer
//-------------------------------------------
char* C_GUI_Status::Viewer_TOM_File_Name::get() { return GUI_Data->Viewer_Data.OBSTACLES_file_name; }
void C_GUI_Status::Viewer_TOM_File_Name::set(char* OBSTACLES_file_name) { strcpy_s(GUI_Data->Viewer_Data.OBSTACLES_file_name, OBSTACLES_file_name); }
//-------------------------------------------
//				DETECTIONS_Folder Of Viewer
//-------------------------------------------
char* C_GUI_Status::DETECTIONS_Folder_Of_Viewer::get() { return GUI_Data->Viewer_Data.DETECTIONS_folder; }
void C_GUI_Status::DETECTIONS_Folder_Of_Viewer::set(char* DETECTIONS_Folder) { strcpy_s(GUI_Data->Viewer_Data.DETECTIONS_folder, DETECTIONS_Folder); }
//-------------------------------------------
//				Meter_Per_Pixel of Viewer
//-------------------------------------------
double C_GUI_Status::Meter_Per_Pixel_Of_Viewer::get() { return GUI_Data->Viewer_Data.Meter_Per_Pixel; }
void C_GUI_Status::Meter_Per_Pixel_Of_Viewer::set(double Meter_Per_Pixel) { GUI_Data->Viewer_Data.Meter_Per_Pixel = Meter_Per_Pixel; }
//-------------------------------------------
//				TxRx_Control of 'DISAPLAY_fields-->FLASH_fields' struct
//-------------------------------------------
T_TxRx_control C_GUI_Status::TxRx_Control::get(int index)
{
	return  disaplay_fields->FLASH_fields.TxRx_control[index];
}
//void C_GUI_Status::set(int index, T_TxRx_control% TxRx_control_Other)
//{
//	disaplay_fields->FLASH_fields.TxRx_control[index] = TxRx_control_Other;
//}
#pragma endregion

#pragma region Public Methods
// --------------------------------------------------
//  Initialize  
//  Haim Otachi     2/1/2016
// 	Description:	The function Initialize all object and parameters of the class
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
void C_GUI_Status::Initialize()
{
	//-------------------------------------------
	//	  Default values for GUI data
	//-------------------------------------------
	Initialize_GUI_Status();
	//-------------------------------------------
	//	  Default values for dispaly fields
	//-------------------------------------------
	Initialize_DISAPLAY_fields();
}
generic<typename T> void C_GUI_Status::Update(int newValue, T GUI_Data_New_Value)
{
	switch (newValue)
	{
		case ROUTE_STATUS:
			GUI_Data->Radar_Data.Route_New = (bool)GUI_Data_New_Value;
			break;
		case RADAR_SPEED:
			GUI_Data->Radar_Data.Radar_Speed = (int)GUI_Data_New_Value;
			break;
		case RADAR_REFRESH_TIME:
			GUI_Data->Radar_Data.Radar_Refresh_Time = (int)GUI_Data_New_Value;
			break;
		case RADAR_RANGE:
			GUI_Data->Radar_Data.Radar_Max_Range = (int)GUI_Data_New_Value;
			break;
		case RADAR_FOV:
			GUI_Data->Radar_Data.Radar_FOV = (int)GUI_Data_New_Value;
			break;
		case VARIANCE_POSITION_WIRES:
			GUI_Data->General_Data.Variance_Position_Wires = (int)GUI_Data_New_Value;
			break;
		case SHOW_DETECTIONS:
			GUI_Data->General_Data.Show_Detections = (bool)GUI_Data_New_Value;
			break;
		case SHOW_TRAJECTORIES:
			GUI_Data->General_Data.Show_Trajectories = (bool)GUI_Data_New_Value;
			break;
		/*case RELIABILITY_THRESHOLd:
			GUI_Data->General_Data.Reliability_Threshold = (int)GUI_Data_New_Value;
			break;*/
		case WIRE_SEGMENT_LENGTH_METEr:
			GUI_Data->General_Data.Wire_Segment_Length_Meter = (int)GUI_Data_New_Value;
			break;
		case MAX_RANGE_ERROR_METER:
			GUI_Data->General_Data.Max_Error_Range_Meter = (int)GUI_Data_New_Value;
			break;
		case FALSE_ALARM_RATE:
			GUI_Data->General_Data.False_Alarm_Rate = (int)GUI_Data_New_Value;
			break;
		case UTM_COORDINATE_Latitude_Of_Simulator:
			GUI_Data->Simulator_Data.GPS_latitude = (float)GUI_Data_New_Value;
			break;
		case UTM_COORDINATE_Longitude_Of_Simulator:
			GUI_Data->Simulator_Data.GPS_longitude = (float)GUI_Data_New_Value;
			break;
		case UTM_COORDINATE_Latitude_Of_Viewer:
			GUI_Data->Simulator_Data.GPS_latitude = (float)GUI_Data_New_Value;
			break;
		case UTM_COORDINATE_Longitude_Of_Viewer:
			GUI_Data->Simulator_Data.GPS_longitude = (float)GUI_Data_New_Value;
			break;
		case SCREEN_WIDTH_OF_SIMULATOR:
			GUI_Data->Simulator_Data.Screen_Width = (int)GUI_Data_New_Value;
			break;
	}
}
// --------------------------------------------------
//  Read_Data_From_File  
//  Haim Otachi     03/01/2016
// 	Description:	The function read data from file, that means:
//						1. Read data from file in relation to 'GUI_Status' struct.
//						2. Read data from file in relation to 'disaplay_fields' struct.
//
//					and then, for every call we return 'True or False' depending on each function.
//					i.e., any function returns a Boolean value: True or False.
// 	Reference: 
//  Input value:
//  Return Value:   True/False
// --------------------------------------------------
bool C_GUI_Status::Read_Data_From_File()
{
	//-----------------------------------------
	//	read data from file for 'GUI_Status' object and return True/False
	//-----------------------------------------
	if (Read_GUI_Status_From_File() == false)
	{
		return false;
	}
	//-----------------------------------------
	//	read data from file for 'disaplay_fields' object and return True/False
	//-----------------------------------------
	if (Read_DISAPLAY_fields_Data_From_File() == false)
	{
		return false;
	}
	
	return true;
}
// --------------------------------------------------
//  Save_Data_To_File  
//  Haim Otachi     21/09/2015
// 	Description:	The function save data to file
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
bool C_GUI_Status::Save_Data_To_File()
{
	//-------------------------------------------
	//	Save the data in the file: GUI_Status_INIT_FORM.bin
	//-------------------------------------------
	if (Save_GUI_Status_TO_File() == false)
	{
		return false;
	}
	//-------------------------------------------
	//	Save the data in the file: DISAPLAY_FIELDS_INIT_FORM.bin
	//-------------------------------------------
	if (Save_DISAPLAY_fields_To_File() == false)
	{
		return false;
	}
	return true;
}
// --------------------------------------------------
//  Find_Delta  
//  Haim Otachi     21/09/2015
// 	Description:	???
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
C_Point2D C_GUI_Status::Find_Delta(double theta)
{
	C_Point2D delta;

	double delta_X = (double)(cos(theta) * GUI_Data->General_Data.Wire_Segment_Length_Meter / 2) / 1e6;
	double delta_Y = (double)(sin(theta) * GUI_Data->General_Data.Wire_Segment_Length_Meter / 2) / 1e6;

	delta.X = delta_X;
	delta.Y = delta_Y;

	return delta;
}
// --------------------------------------------------
//  Update_Debug_Log  
//  Haim Otachi     29/12/2015
// 	Description:	???
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_GUI_Status::Update_Debug_SNAPSHOT_Type(E_SNAPSHOT_type snapshot_type_index)
{
	disaplay_fields->DEBUG_fields.SNAPSHOT_type = snapshot_type_index;
}
// --------------------------------------------------
//  Update_Debug_Log  
//  Haim Otachi     29/12/2015
// 	Description:	???
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_GUI_Status::Update_Debug_MATLAB_Script_Index(int matlab_script_index)
{
	disaplay_fields->DEBUG_fields.MATLAB_script_index = matlab_script_index;
}
// --------------------------------------------------
//  matlab_script  
//  Haim Otachi     03/02/2016
// 	Description:	???
// 	Reference: 
//  Input value:	the matlab script name
//  Return Value: 
// --------------------------------------------------
void C_GUI_Status::Update_Debug_MATLAB_Script(System::String^ matlab_script)
{
	//-----------------------------------------------------------
	//		we create new object of 'marshal_context' of microsoft to convert from String^ to const char*	
	//-----------------------------------------------------------
	marshal_context ^ context = gcnew marshal_context();
	//-----------------------------------------------------------
	//			update the 'debug_log_folder' on the system
	//-----------------------------------------------------------
	sprintf_s(disaplay_fields->DEBUG_fields.MATLAB_script, context->marshal_as<const char*>(matlab_script));
}
// --------------------------------------------------
//  Update_Debug_Log  
//  Haim Otachi     29/12/2015
// 	Description:	???
// 	Reference: 
//  Input value:	log folder name of String^ type
//  Return Value: 
// --------------------------------------------------
void C_GUI_Status::Update_Debug_Log_Folder(System::String^ debug_log_folder)
{
	//-----------------------------------------------------------
	//		we create new object of 'marshal_context' of microsoft to convert from String^ to const char*	
	//-----------------------------------------------------------
	marshal_context ^ context = gcnew marshal_context();
	//-----------------------------------------------------------
	//			update the 'debug_log_folder' on the system
	//-----------------------------------------------------------
	sprintf_s(disaplay_fields->DEBUG_fields.LOG_folder, context->marshal_as<const char*>(debug_log_folder));
}
// --------------------------------------------------
//  Update_Flash_TxRx_Control  
//  Haim Otachi     30/12/2015
// 	Description:	???
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
void C_GUI_Status::Update_Flash_Controls(int choice, int control_MODE_index_other, int32_t value)
{
	//-----------------------------------------
	//		we update our pointer to 'TxRx_control' array
	//-----------------------------------------
	control_MODE_index = control_MODE_index_other;
	//-----------------------------------------
	//		we update the system with correct new data relative to user's choice
	//-----------------------------------------
	switch (choice)
	{
		//-----------------------------------------------------------
		//			Updating relative to 'TxRx_control' array
		//-----------------------------------------------------------
		case PROFILE_AD9910A:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].Profile_AD9910A = value;
			break;

		case PROFILE_AD9910B:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].Profile_AD9910B = value;
			break;

		case CHIP_LENGTH_AD9910A:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].chip_length_AD9910A = value;
			break;

		case CHIP_LENGTH_AD9910B:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].chip_length_AD9910B = value;
			break;

		case SELECT_TX1:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].IF_SELECT_TX1 = value;
			break;

		case SELECT_TX2:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].IF_SELECT_TX2 = value;
			break;

		case SELECT_TX3:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].IF_SELECT_TX3 = value;
			break;

		case SELECT_PROBE:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].IF_SELECT_PROBE = value;
			break;

		case IO_UPDATE_RATE:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].IO_UPDATE_rate = value;
			break;

		case TX_1_ON:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].TX1_ON = value;
			break;

		case TX_2_ON:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].TX2_ON = value;
			break;

		case TX_3_ON:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].TX3_ON = value;
			break;

		case E_PROBE_ON:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].PROBE_ON = value;
			break;

		case E_TX_LO_TR:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].TX_LO_TR = value;
			break;

		case E_ANT_SAMPLE_SELECT:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].ANT_SAMPLE_SELECT = value;
			break;

		case ATTN_TX_1:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].ATTN_TX1 = value;
			break;

		case ATTN_TX_2:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].ATTN_TX2 = value;
			break;

		case ATTN_TX_3:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].ATTN_TX3 = value;
			break;

		case ATTN_RX_1:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].ATTN_RX1 = value;
			break;

		case ATTN_RX_2:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].ATTN_RX2 = value;
			break;

		case ATTN_RX_3:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].ATTN_RX3 = value;
			break;

		case ATTN_RX_4:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].ATTN_RX4 = value;
			break;

		case AD9910_SET_AUX_DAC_A:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].AD9910_Set_aux_dac_A = value;
			break;

		case AD9910_SET_AUX_DAC_B:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].AD9910_Set_aux_dac_B = value;
			break;

		case BUFFER_LENGTH:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].Buffer_length = value;
			break;

		case FIFO_LENGTH:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].FIFO_length = value;
			break;

		case E_IO_UPDATE_ON:
			disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].IO_UPDATE_ON = value;
			break;
		//-----------------------------------------------------------
		//			Updating relative to 'DET_algorithms'
		//-----------------------------------------------------------
		case OFFSET_SAMPLES:
			disaplay_fields->FLASH_fields.DET_algorithms.OFFSET_samples = value;
			break;

		case RANGE_SAMPLES:
			disaplay_fields->FLASH_fields.DET_algorithms.RANGE_samples = value;
			break;

		case TARGET_DETECTION_1ST_THRESHOLD:
			disaplay_fields->FLASH_fields.DET_algorithms.Target_detection_1st_threshold = value;
			break;

		case TARGET_DETECTION_2ST_THRESHOLD:
			disaplay_fields->FLASH_fields.DET_algorithms.Target_detection_2nd_threshold = value;
			break;

		case Range_DECIMATION:
			disaplay_fields->FLASH_fields.DET_algorithms.Range_decimation = value;
			break;

		/*case MINIMUM_RANGE_METER:
			disaplay_fields->FLASH_fields.DET_algorithms.Minimum_range_meter = value;
			break;*/

		case AGC_THRESHOLD:
			disaplay_fields->FLASH_fields.DET_algorithms.AGC_threshold = value;
			break;
		//-----------------------------------------------------------
		//			Updating relative to 'TGT_calibrate'
		//-----------------------------------------------------------
		case PROBE_START_SAMPLE:
			disaplay_fields->FLASH_fields.TGT_calibrate.Probe_start_sample = value;
			break;

		case PROBE_END_SAMPLE:
			disaplay_fields->FLASH_fields.TGT_calibrate.Probe_end_sample = value;
			break;

		case CALIBRATOR_START_SAMPLE:
			disaplay_fields->FLASH_fields.TGT_calibrate.Calibrator_start_sample = value;
			break;

		case CALIBRATOR_END_SAMPLE:
			disaplay_fields->FLASH_fields.TGT_calibrate.Calibrator_end_sample = value;
			break;
		//-----------------------------------------------------------
		//			Updating relative to 'PROBE_test'
		//-----------------------------------------------------------
		case PROBE_TEST_PROFILE:
			disaplay_fields->FLASH_fields.PROBE_test.PROBE_TEST_profile = value;
			break;

		case PROBE_TEST_GAIN:
			disaplay_fields->FLASH_fields.PROBE_test.PROBE_TEST_gain = value;
			break;
		//-----------------------------------------------------------
		//Updating relative to 'TxRx_MODE'
		//-----------------------------------------------------------
		case TXRX_MODE:
			disaplay_fields->FLASH_fields.TxRx_MODE = (E_TxRx_MODE)value;
			break;
		//-----------------------------------------------------------
		//Updating relative to 'System_ID'
		//-----------------------------------------------------------
		case SYSTEM_ID:
			disaplay_fields->FLASH_fields.System_ID = value;
			break;

		case RF2_Support:
			disaplay_fields->FLASH_fields.Enable_RF2_Support = value;
			break;
	}
}
// --------------------------------------------------
//  Calc_Batch_Duartion  
//  Haim Otachi     30/12/2015
// 	Description:	???
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
double C_GUI_Status::Calc_Batch_Duartion()
{
	double batch_duartion = 0;
	//--------------------------------------------------------
	//			Find the number of buffers from 'DET_algorithms' struct
	//--------------------------------------------------------
	double number_of_buffers = (double)disaplay_fields->FLASH_fields.DET_algorithms.Number_of_buffers / ZERO_PADDING;
	//--------------------------------------------------------
	//			Find the new value of 'IO_Update_rate'  
	//--------------------------------------------------------
	double IO_New_rate = (double)(disaplay_fields->FLASH_fields.TxRx_control[control_MODE_index].IO_UPDATE_rate / 1000);
	//--------------------------------------------------------
	//			calculate the batch duatrion
	//--------------------------------------------------------
	batch_duartion = number_of_buffers / IO_New_rate;
	//--------------------------------------------------------
	//			return the 'batch_duartion' value
	//--------------------------------------------------------
	return batch_duartion;
}
// --------------------------------------------------
//  Update_Number_Of_Buffers  
//  Haim Otachi     30/12/2015
// 	Description:	???
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
uint32_t C_GUI_Status::Update_Number_Of_Buffers(uint32_t current_number_of_buffers)
{
	uint32_t		new_number_of_buffers;    // has to be 128, 256, 512, ..., 4096
	uint32_t		old_number_of_buffers = disaplay_fields->FLASH_fields.DET_algorithms.Number_of_buffers;
	//--------------------------------------------------------
	//			
	//--------------------------------------------------------
	if (current_number_of_buffers < 128)
	{
		current_number_of_buffers = 128;
	}
	if (current_number_of_buffers > 4096)
	{
		current_number_of_buffers = 4096;
	}
	if (old_number_of_buffers < 128)
	{
		old_number_of_buffers = 128;
	}
	if (old_number_of_buffers > 4096)
	{
		old_number_of_buffers = 4096;
	}
	//--------------------------------------------------------
	//			calculate the old number of buffers again
	//--------------------------------------------------------
	old_number_of_buffers = (uint32_t)pow(2, ceil(log2(old_number_of_buffers)));
	//--------------------------------------------------------
	//			
	//--------------------------------------------------------
	new_number_of_buffers = old_number_of_buffers;
	//--------------------------------------------------------
	//			
	//--------------------------------------------------------
	if ((current_number_of_buffers > old_number_of_buffers) && (current_number_of_buffers < 4096))
	{
		new_number_of_buffers = old_number_of_buffers * 2;
	}
	if ((current_number_of_buffers < old_number_of_buffers) && (current_number_of_buffers > 128))
	{
		new_number_of_buffers = old_number_of_buffers / 2;
	}
	//--------------------------------------------------------
	//		Update the number of buffers with new data	
	//--------------------------------------------------------
	disaplay_fields->FLASH_fields.DET_algorithms.Number_of_buffers = new_number_of_buffers;
	//--------------------------------------------------------
	//		return the new number of buffers
	//--------------------------------------------------------
	return new_number_of_buffers;
}
// --------------------------------------------------
//  Update_Velocity_Buffers  
//  Haim Otachi     30/12/2015
// 	Description:	???
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
double C_GUI_Status::Update_Velocity_Buffers(uint32_t maximal_doppler)
{
	disaplay_fields->FLASH_fields.DET_algorithms.Maximal_doppler = maximal_doppler;
	//--------------------------------------------------------
	//			Find the new value of 'IO_Update_rate'  
	//--------------------------------------------------------
	double IO_New_rate = (double)(disaplay_fields->FLASH_fields.TxRx_control->IO_UPDATE_rate);
	//--------------------------------------------------------
	//			Find the number of buffers from 'DET_algorithms' struct
	//--------------------------------------------------------
	double number_of_buffers = (double)(disaplay_fields->FLASH_fields.DET_algorithms.Number_of_buffers);
	//--------------------------------------------------------
	//			calculate the 'f_doppler'
	//--------------------------------------------------------
	double f_doppler = IO_New_rate / number_of_buffers;
	//--------------------------------------------------------
	//			calculate the 'v_doppler' with 'f_doppler'
	//--------------------------------------------------------
	double v_doppler = f_doppler * (30.0/98.0) / 2;
	//--------------------------------------------------------
	//			calculate the velocity buffers
	//--------------------------------------------------------
	double vel_buff = (double)(disaplay_fields->FLASH_fields.DET_algorithms.Maximal_doppler) * v_doppler;
	//--------------------------------------------------------
	//			return the velocity buffers
	//--------------------------------------------------------
	return vel_buff;
}
// --------------------------------------------------
//  Update_Maintenance_Controls  
//  Haim Otachi     30/12/2015
// 	Description:	???
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
generic<typename T> void C_GUI_Status::Update_Maintenance_Controls(int choice, T value)
{
	//-----------------------------------------------------------
	//		we create new object of 'marshal_context' of microsoft to convert from String^ to const char*	
	//-----------------------------------------------------------
	marshal_context ^ context = gcnew marshal_context();
	//-------------------------------------
	//			
	//-------------------------------------
	switch (choice)
	{
		case RESET_AFTER_BOOT_UPLOAD:
			disaplay_fields->MAINTENANCE_fields.reset_after_boot_upload = (int32_t)value;
			break;

		case OUTFILE_DIRECTORY_OMR:
			sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_OMR, context->marshal_as<const char*>((System::String^)value));
			break;

		case OUTFILE_DIRECTORY_DET:
			sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_DET, context->marshal_as<const char*>((System::String^)value));
			break;

		case OUTFILE_DIRECTORY_CHAB:
			sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_CHAB, context->marshal_as<const char*>((System::String^)value));
			break;

		case OUTFILE_DIRECTORY_MCU:
			sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_MCU, context->marshal_as<const char*>((System::String^)value));
			break;

		case OUTFILE_DIRECTORY_RF_MCU:
			sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_RF_MCU, context->marshal_as<const char*>((System::String^)value));
			break;
	}
}

// --------------------------------------------------
//  Update_TXRX_Control  
//  Haim Otachi     2/1/2016
// 	Description:	The function update the 'current_control_MODE_index' and after
//                  that update the 'current_TxRx_control'
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
void C_GUI_Status::Update_TxRx_Control()
{
	//-----------------------------------------------
	//	Take the current 'control_MODE'
	//-----------------------------------------------
	int current_control_MODE_index = disaplay_fields->FLASH_fields.TxRx_MODE;
	//-----------------------------------------------
	//	Update the current_TxRx_control array
	//-----------------------------------------------
	*current_TxRx_control = disaplay_fields->FLASH_fields.TxRx_control[current_control_MODE_index];
}

//// --------------------------------------------------
////  create_experiment_folder
////  Haim Otachi		2/1/2016
//// 	Description:	Create a folder to the experiment
//// 	Reference: 
////	Input Value:	pointer to experiment dirctory (for return)
////  Return Value:	GOOD/FAULT
//// --------------------------------------------------
//int	C_GUI_Status::create_experiment_folder()
//{
//	char						temp_string_1[MAX_STRING_LENGTH];
//	char						temp_string_2[MAX_STRING_LENGTH];
//	fstream						file_handle;
//	int							experiment_number;
//	SYSTEMTIME					mytime;
//
//	System::String^				returned_message;
//	//----------------------------------------------
//	//   Check the experiment folder validity
//	//----------------------------------------------
//	if (System::IO::Directory::Exists(gcnew String(DISAPLAY_fields->DEBUG_fields.LOG_folder)) == false)
//	{
//		//----------------------------------------------------
//		//		Message box  
//		//----------------------------------------------------
//		marshal_context ^ context = gcnew marshal_context();
//		if (MessageBox::Show(this, gcnew String("Error: LOG directory does not exist."), "ARC1", MessageBoxButtons::OKCancel,
//			MessageBoxIcon::Asterisk) == System::Windows::Forms::DialogResult::Cancel)
//		{
//			return FAULT;
//		}
//	}
//	//----------------------------------------------
//	//		open Experiment Number file
//	//----------------------------------------------
//
//}
#pragma endregion

#pragma region Private Methods
// --------------------------------------------------
//  Initialize_GUI_Status  
//  Haim Otachi     31/12/2015
// 	Description:	Initialize the default parameter for 'GUI_Status' object
// 	Reference: 
//  Input value:
//  Return Value:	
// --------------------------------------------------
void C_GUI_Status::Initialize_GUI_Status()
{
	//-------------------------------------------
	//	Initial General_Data struct of GUI data
	//-------------------------------------------
	GUI_Data->General_Data.False_Alarm_Rate						= 1;
	GUI_Data->General_Data.Max_Error_Range_Meter				= MAX_RANGE_ERROR;
	GUI_Data->General_Data.Reliability_Threshold				= RELIABILITY_THRESHOLD;
	GUI_Data->General_Data.Screen_Width							= 11;
	GUI_Data->General_Data.Show_Detections						= true;
	GUI_Data->General_Data.Show_Trajectories					= true;
	GUI_Data->General_Data.Variance_Position_Wires				= 50;
	GUI_Data->General_Data.Wire_Segment_Length_Meter			= WIRE_SEGMENT_LENGTH_METER;
	//-------------------------------------------
	//	Initial Radar_Data struct of GUI data
	//-------------------------------------------	
	GUI_Data->Radar_Data.Radar_FOV								= 180;
	GUI_Data->Radar_Data.Radar_Max_Range						= 1500;
	GUI_Data->Radar_Data.Radar_Min_Range						= 100;
	GUI_Data->Radar_Data.Radar_Refresh_Time						= 1;
	GUI_Data->Radar_Data.Radar_Speed							= 50;
	GUI_Data->Radar_Data.Route_New								= true;
	//-------------------------------------------
	//	Initial Simulator_Data struct of GUI data
	//-------------------------------------------
	GUI_Data->Simulator_Data.GPS_latitude						= (double)MAP_BASE_LAT;
	GUI_Data->Simulator_Data.GPS_longitude						= (double)MAP_BASE_LON;
	GUI_Data->Simulator_Data.Meter_Per_Pixel					= (double)0.0;
	GUI_Data->Simulator_Data.Screen_Width						= 11;

	sprintf_s(GUI_Data->Simulator_Data.OBSTACLES_file_name, "Enter obstacles file name...............");
	sprintf_s(GUI_Data->Simulator_Data.EXPERIMENT_directory, "Enter EXPERIMENT directory...............");
	sprintf_s(GUI_Data->Simulator_Data.DETECTIONS_folder, "Enter DETECTIONS folder...............");
	sprintf_s(GUI_Data->Simulator_Data.MAP_image_file, "Enter MAP image file...............");
	//-------------------------------------------
	//	Initial Viewer_Data struct of GUI data
	//-------------------------------------------
	GUI_Data->Viewer_Data.GPS_latitude							= (double)MAP_BASE_LAT;
	GUI_Data->Viewer_Data.GPS_longitude							= (double)MAP_BASE_LON;
	GUI_Data->Viewer_Data.Meter_Per_Pixel						= (double)0.0;
	GUI_Data->Viewer_Data.Screen_Width_meter					= 11;

	sprintf_s(GUI_Data->Viewer_Data.OBSTACLES_file_name, "Enter obstacles file name...............");
	sprintf_s(GUI_Data->Viewer_Data.EXPERIMENT_directory, "Enter EXPERIMENT directory...............");
	sprintf_s(GUI_Data->Viewer_Data.DETECTIONS_folder, "Enter DETECTIONS folder...............");
}
// --------------------------------------------------
//  Initialize_DISAPLAY_fields  
//  Haim Otachi     31/12/2015
// 	Description:	Initialize the default parameter for 'disaplay_fields' object
// 	Reference: 
//  Input value:
//  Return Value:	
// --------------------------------------------------
void C_GUI_Status::Initialize_DISAPLAY_fields()
{
	memset(disaplay_fields, 0, sizeof(T_DISAPLAY_fields));
	//-------------------------------------------
	//	Initialize the 'MAINTENANCE_fields' struct
	//-------------------------------------------
	sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_OMR, "Enter directory...............");
	sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_DET, "Enter directory...............");
	sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_CHAB, "Enter directory...............");
	sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_MCU, "Enter directory...............");
	sprintf_s(disaplay_fields->MAINTENANCE_fields.outFile_directory_RF_MCU, "Enter directory...............");
	//-------------------------------------------
	//	Initialize the 'DEBUG_fields' struct
	//-------------------------------------------
	sprintf_s(disaplay_fields->DEBUG_fields.LOG_folder, "Enter directory...............");
	//-------------------------------------------
	//	Initialize the 'FLASH_fields' struct
	//------------------------------------------
	//
	//	TxRx_control array
	//
	disaplay_fields->FLASH_fields.TxRx_control[0].Buffer_length = 1024;
	disaplay_fields->FLASH_fields.TxRx_control[1].Buffer_length = 1024;
	disaplay_fields->FLASH_fields.TxRx_control[2].Buffer_length = 1024;
}
// --------------------------------------------------
//  Read_GUI_Status_From_File  
//  Haim Otachi     31/12/2015
// 	Description:	The function read the all data that GUI need from the fila (if exist)
// 	Reference: 
//  Input value:
//  Return Value:	
// --------------------------------------------------
bool C_GUI_Status::Read_GUI_Status_From_File()
{
	fstream file_handle = fstream(INITIAL_VALUES_FILE_NAME_OF_GUI_Status, ios::in | ios::binary);
	if (file_handle.is_open())
	{
		//-------------------------------------------
		//	We find the current index of the first char in file
		//-------------------------------------------
		int begin = (int)file_handle.tellg();
		file_handle.seekg(0, ios::end);
		//-------------------------------------------
		//	 We find the current index of the Last char in file
		//-------------------------------------------
		int end = (int)file_handle.tellg();
		file_handle.seekg(0, ios::beg);
		//-------------------------------------------
		//	 if file length is equal to structure length
		//-------------------------------------------
		int size_of_data = sizeof(T_GUI_Data);
		if (end - begin == size_of_data)
		{
			file_handle.read((char*)GUI_Data, sizeof(T_GUI_Data));
		}
		else
		{
			//-------------------------------------------
			//	  Default values for GUI data
			//-------------------------------------------
			Initialize_GUI_Status();
		}
		file_handle.close();
		return true;
	}
	return false;	
}
// --------------------------------------------------
//  Read_Data_From_File  
//  Haim Otachi     28/12/2015
// 	Description:	The function read data from file
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
bool C_GUI_Status::Read_DISAPLAY_fields_Data_From_File()
{
	fstream file_handle = fstream(INITIAL_VALUES_FILE_NAME_OF_disaplay_fields, ios::in | ios::binary);
	if (file_handle.is_open())
	{
		//-------------------------------------------
		//	We find the current index of the first char in file
		//-------------------------------------------
		int begin = (int)file_handle.tellg();
		file_handle.seekg(0, ios::end);
		//-------------------------------------------
		//	 We find the current index of the Last char in file
		//-------------------------------------------
		int end = (int)file_handle.tellg();
		file_handle.seekg(0, ios::beg);
		//-------------------------------------------
		//	 if file length is equal to structure length
		//-------------------------------------------
		int size_of_data = sizeof(T_DISAPLAY_fields);
		if (end - begin == size_of_data)
		{
			file_handle.read((char*)disaplay_fields, sizeof(T_DISAPLAY_fields));
		}
		else
		{
			//-------------------------------------------
			//	  Default values for dispaly fields
			//-------------------------------------------
			Initialize_DISAPLAY_fields();
		}
		file_handle.close();
		return true;
	}
	return false;
}
// --------------------------------------------------
//  Save_GUI_Status_TO_File  
//  Haim Otachi     31/12/2015
// 	Description:	The function save data of 'GUI_Status' to file
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
bool C_GUI_Status::Save_GUI_Status_TO_File()
{
	try
	{
		//-------------------------------------------
		//	Save the data in the file: GUI_Status_INIT_FORM.bin
		//-------------------------------------------
		fstream file_handle = fstream(INITIAL_VALUES_FILE_NAME_OF_GUI_Status, ios::out | ios::binary);
		pin_ptr<int> p1 = &(GUI_Data->Radar_Data.Radar_Speed);
		file_handle.write((char*)(p1), sizeof(T_GUI_Data));
		file_handle.close();

		return true;
	}
	catch (Exception^ ex) { ex->Message; return false; }
}
// --------------------------------------------------
//  Save_DISAPLAY_fields_To_File  
//  Haim Otachi     31/12/2015
// 	Description:	The function save data of 'disaplay_fields' to file
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
bool C_GUI_Status::Save_DISAPLAY_fields_To_File()
{
	try
	{
		//-------------------------------------------
		//	Save the data in the file: DISAPLAY_FIELDS_INIT_FORM.bin
		//-------------------------------------------
		fstream file_handle = fstream(INITIAL_VALUES_FILE_NAME_OF_disaplay_fields, ios::out | ios::binary);
		file_handle.write((char*)disaplay_fields, sizeof(T_DISAPLAY_fields));
		file_handle.close();

		return true;
	}
	catch (Exception^ ex) { ex->Message; return false; }
}
#pragma endregion