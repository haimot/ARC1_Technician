#ifndef REAL_TIME_THREAD_H
#define REAL_TIME_THREAD_H
//-----------------------------------------
//			Real_Time_Thread.h 
//   Communication with DSP and System status
//-----------------------------------------
#include "C_SYSTEM_status.h"
#include "C_DSP_Communication.h"
#include "engine.h"
//-----------------------------------------
//	using namespace:
//			1.	DSP_Communication
//			2.  System::Net::NetworkInformation
//-----------------------------------------
using namespace System;
using namespace DSP_Communication;
using namespace System::Net::NetworkInformation;
//-----------------------------------------
//		ref class:	Real_Time_Thread
//-----------------------------------------
public ref class Real_Time_Thread
{
	//-----------------------------------------
	//			Private Fields
	//-----------------------------------------
	private:
	C_SYSTEM_status^				system_status;
	C_DSP_Communication^			dsp_communication;	

	char*							buffer;
	short*							p_buffer_short;

	uint32_t						buffer_size_short;
	uint32_t						buffer_size_char;

	array<NetworkInterface^>^		nics;
	String^							Matlab_Script_Name;
	//-----------------------------------
	//  Matlab variables
	//-----------------------------------
	Engine							*Matlab_engine;
	//-------------------------------------
	//		Message fields for output
	//-------------------------------------
	String^							Message;
	//-----------------------------------------
	//			Constructor
	//-----------------------------------------
	public:							Real_Time_Thread();
	//-----------------------------------------
	//			Destructor
	//-----------------------------------------
	public:							~Real_Time_Thread();
	//-----------------------------------------
	//		Get: the current message from trhe system
	//-----------------------------------------
	String^							Get_Message();
	//-----------------------------------------
	//		Get: the p_buffer_short
	//-----------------------------------------
	int16_t*						Get_Buffer_Short();
	//-----------------------------------------
	//		Set: matlab script name
	//-----------------------------------------
	void							Set_Matlab_Script_Name(String^ new_matlab_script_name);
	//-----------------------------------------
	//			Public Methods
	//-----------------------------------------
	public:
	String^							Initialize(C_SYSTEM_status^ system_status_other);
	int								Socket_Is_Available();
	int								Send_Command_SNAPSHOT();
	bool							Read_SNAPSHOT();
	bool							Read_Obstacles_Map(char* pbuffer, int size);

	bool							PC_Command_Reset_ARC();
	bool							PC_Command_Start_Work_CIRC();
	bool							PC_Command_Start_Work_HV();
	bool							PC_Command_Stop_Work();

	bool							Send_System_Control_To_DSP();
								
	String^							If_Calibrator_Calibrate();
	String^							If_Probe_Calibrate();
	String^							Start_MATLAB_Engine();

	bool							Initialize_Computer_Networks();
	String^							Scan_ETHERNET_Link();
	bool							Process_Snapshot(char* LOG_Path);
	int								Read_SYSTEM_Status();

	String^							Read_Flash();
	String^							Flash_Write();

	bool							SENSOR_Config();
	bool							BOOT_UPLOADER(char* fileName, T_BUL_config* pBUL_config);
	bool							Sending_Command_Get_SNAPSHOT();
	//-----------------------------------------
	//			Private Methods
	//-----------------------------------------
};

#endif