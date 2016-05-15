//------------------------------------------------
//	Communication with DSP and System status
//	Haim Otachi	  04/01/2016
//----------------------------------------------------
#include "Real_Time_Thread.h"
#include <msclr\marshal.h>
#include <fstream>
#include <math.h>
#include <direct.h>
//-----------------------------------------
//		DATA
//-----------------------------------------
#define FFTC_ZERO_PADDING_MUL		2
//-----------------------------------------
//		FILES & FOLDERS
//		Changes by:
//			Haim Otachi 11/01/2016:  Add 'define' from ARC1_Technician.h
//-----------------------------------------
#define	SNAPSHOT_SAMPLES_FILE		"snapshot_samples.bin"
#define	MATLAB_SCRIPTS_PATH			"..\\MATLAB_SCRIPTS"
//-----------------------------------------
//	using namespace:
//			1.	DSP_Communication
//			2.  System::Net::NetworkInformation
//
//			3.	std
//			4.  System::Drawing
//			5.  msclr::interop
//-----------------------------------------
using namespace std;
using namespace System::Drawing;
using namespace msclr::interop;

#pragma region Constructor / Destructor
// --------------------------------------------------
//  Real_Time_Thread - Default Constructor
//  Haim Otachi     04/01/2016
// 	Description:	the function initialize the any objects of the class with default parameters
// 	Reference: 
//  Return Value:	
// --------------------------------------------------
Real_Time_Thread::Real_Time_Thread() 
{
	system_status = gcnew C_SYSTEM_status;
	dsp_communication = gcnew C_DSP_Communication;

	Matlab_Script_Name = gcnew String("");
}
// --------------------------------------------------
//  Real_Time_Thread - Destructor
//  Haim Otachi     04/01/2016
// 	Description:	the function delete the any objects of the class
// 	Reference: 
//  Return Value:	
// --------------------------------------------------
Real_Time_Thread::~Real_Time_Thread() 
{
	//-------------------------------------
	//	  delete the 'system_status' object
	//-------------------------------------
	delete system_status;
	//-------------------------------------
	//	  delete the 'dsp_communication' object
	//-------------------------------------
	delete dsp_communication;
	//----------------------------------
	// Matlab engine
	//----------------------------------
	if (Matlab_engine != NULL)
	{
		engClose(Matlab_engine);
		Matlab_engine = NULL;
	}
}
#pragma endregion

// --------------------------------------------------
//  Get_Message 
//  Haim Otachi     01/02/2016
// 	Description:	the function return the current message from the system.
// 	Reference: 
//  Return Value:	current message from the system.
// --------------------------------------------------
String^	Real_Time_Thread::Get_Message()
{
	return Message;
}
// --------------------------------------------------
//  Get_Buffer_Short 
//  Haim Otachi     01/02/2016
// 	Description:	the function return the p_buffer_short
// 	Reference: 
//  Return Value:	p_buffer_short.
// --------------------------------------------------
int16_t* Real_Time_Thread::Get_Buffer_Short()
{
	return p_buffer_short;
}
// --------------------------------------------------
//  Set_Matlab_Script_Name 
//  Haim Otachi     03/02/2016
// 	Description:	the function return the update the name of the current matlab script
// 	Reference: 
//  Return Value:	
// --------------------------------------------------
void Real_Time_Thread::Set_Matlab_Script_Name(String^ new_matlab_script_name)
{
	Matlab_Script_Name = new_matlab_script_name;
}
#pragma region Public Methods
// --------------------------------------------------
//  Initialize
//  Haim Otachi     10/01/2016
// 	Description:	the function initialize the system_status object of the class
// 	Reference: 
//	Input Value:	other pointer to C_SYSTEM_status class
//  Return Value:	an appropriate message of Matlab_engine.
// --------------------------------------------------
String^ Real_Time_Thread::Initialize(C_SYSTEM_status^ system_status_other)
{
	//-------------------------------------
	//	  we update the 'system_status' object with real data
	//-------------------------------------
	system_status = system_status_other;
	//-----------------------------------------
	// Call engOpen with a NULL string. This starts a MATLAB process
	// on the current host using the command "matlab".
	//-----------------------------------------
	return gcnew String(Start_MATLAB_Engine());
}
// --------------------------------------------------
//  Start_MATLAB_Engine
//  Updated by Haim Otachi		11/01/2016
//	Change:						Add the content function from 'MyForm.cpp'
// 	Description:				the function Call engOpen with a NULL string. This starts a MATLAB process on the current host using the command "matlab".
//								the function returns appropriate message. 
// 	Reference: 
//	Input Value:	
//  Return Value:				an appropriate message of Matlab_engine: if can start MATLAB engine or not
// --------------------------------------------------
String^	Real_Time_Thread::Start_MATLAB_Engine()
{
	if (!(Matlab_engine = engOpen("")))
	{
		return gcnew String("Can't start MATLAB engine");
		Matlab_engine = NULL;
	}
	else
	{
		return gcnew String("start MATLAB engine...");
	}
}
// --------------------------------------------------
//  Read_SYSTEM_Status
//  Alon Slapak					25/2/2015
//  Updated by Haim Otachi		10/01/2016
//	Change:						Add function from 'MyForm.cpp'
// 	Description:				Invoke ethernet thread for TCP read. The idea is to avoid blocking the
//								the monitor because of the blocking "connect"
// 	Reference:					http://www.codeproject.com/Articles/12740/Threads-with-Windows-Forms-Controls-in-Managed-C
//								http://www.drdobbs.com/cpp/ccli-threading-part-i/184402018
//								http://www.drdobbs.com/cpp/ccli-threading-part-ii/184402029
//	Input Value:	
//  Return Value:				GOOD/FAULT
// --------------------------------------------------
int	Real_Time_Thread::Read_SYSTEM_Status()
{	
	//---------------------------------------
	//	check if can read system status
	//---------------------------------------
	if (dsp_communication->DSP_read_SYSTEM_status((char*)system_status->system_control_0, sizeof(T_SYSTEM_control_0)) == FAULT)
	{
		system_status->Ethernet_message_status = FAULT;			
		return FAULT;
	}

	system_status->Ethernet_message_status = GOOD;
	return GOOD;
		
}
// --------------------------------------------------
//  PC_Command_Start_Work
//  Alon Slapak					18/10/2014
//  Updated by Haim Otachi		11/01/2016
//	Change:						Add function from 'MyForm.cpp'
// 	Description:				The function checks if PC COMMAND can start working and return an appropriate value: true or false.
// 	Reference: 
//	Input Value:	
//  Return Value:				True/False 
// --------------------------------------------------
bool Real_Time_Thread::PC_Command_Start_Work_CIRC()
{
	//--------------------------------
	//		"Start work" to radar
	//--------------------------------
	if (dsp_communication->DSP_command(PC_COMMAND_START_WORK_CIRC) == FAULT)
	{
		return false;
	}
	else
	{
		return true;
	}
}
// --------------------------------------------------
//  PC_Command_Reset_ARC
//  Haim Otachi					24/01/2014
// 	Description:				???
// 	Reference: 
//	Input Value:	
//  Return Value:				True/False 
// --------------------------------------------------
bool Real_Time_Thread::PC_Command_Reset_ARC()
{
	if (dsp_communication->DSP_command(PC_COMMAND_RESET_ARC) == FAULT)
	{
		return false;
	}
	else
	{
		return true;
	}	
}
// --------------------------------------------------
//  Send_System_Control_To_DSP
//  Alon Slapak					14/4/2015
//  Updated by Haim Otachi		11/01/2016
//	Change:						Add function from 'MyForm.cpp'
// 	Description:				Send SYSTEM_control to DSP and return appropriate message
// 	Reference: 
//	Input Value:	
//  Return Value:				True/False 
// --------------------------------------------------
bool Real_Time_Thread::Send_System_Control_To_DSP()
{
	if (dsp_communication->DSP_send(SEND_SYSTEM_CONTROL, (char*)system_status->system_control_1, sizeof(T_SYSTEM_control_1)) == FAULT)
	{
		return false;
	}
	else
	{
		return true;
	}
}
// --------------------------------------------------
//  Initialize_Computer_Networks
//  Updated by Haim Otachi		11/01/2016
//	Change:						Add the content function from 'MyForm.cpp'
// 	Description:				The function get all Computer networks from DSP and if it's possible the function return true else return false.
// 	Reference: 
//	Input Value:	
//  Return Value:				True/False 
// --------------------------------------------------
bool Real_Time_Thread::Initialize_Computer_Networks()
{
	//---------------------------------------------
	//			Get all Computer networks
	//---------------------------------------------
	IPGlobalProperties^ computerProperties = IPGlobalProperties::GetIPGlobalProperties();
	nics = NetworkInterface::GetAllNetworkInterfaces();
	if ((nics == nullptr) || (nics->Length < 1))
	{
		return false;
	}
	return true;
}
// --------------------------------------------------
//  Scan_ETHERNET_Link
//  Updated by Haim Otachi		11/01/2016
//	Change:						Add the content function from 'MyForm.cpp'.
// 	Description:				The function Scan for the ETHERNET link with DSP and returns an appropriate message.
// 	Reference: 
//	Input Value:	
//  Return Value:				The appropriate message
// --------------------------------------------------
String^ Real_Time_Thread::Scan_ETHERNET_Link()
{
	System::Collections::IEnumerator^ myEnum4 = nics->GetEnumerator();
	while (myEnum4->MoveNext())
	{
		NetworkInterface^ adapter = safe_cast<NetworkInterface ^>(myEnum4->Current);
		IPInterfaceProperties^ properties = adapter->GetIPProperties();
		//--------------------------------------------------------------------------
		//								Ethernet found
		//--------------------------------------------------------------------------
		if (adapter->NetworkInterfaceType == NetworkInterfaceType::Ethernet)
		{		
			//-------------------------------------
			//	update the status of the Ethernet's speed
			//-------------------------------------
			system_status->Ethernet_speed = adapter->Speed;
			if (system_status->Ethernet_speed > 0)
			{
				//-------------------------------------------------------------------
				//					Detect link speed
				//-------------------------------------------------------------------
				if (adapter->Speed == 1000000000)
				{
					Message = gcnew System::String(L"1 Gbps");
				}
				else if (adapter->Speed == 100000000)
				{
					Message = gcnew System::String(L"100 Mbps");
				}
				else if (adapter->Speed == 10000000)
				{
					Message = gcnew System::String(L"10 Mbps");
				}
				else
				{
					Message = system_status->Ethernet_speed.ToString();
				}
				//----------------------------------------------------------------------------------------
				// Indicate link ok (> 100Mb)
				//----------------------------------------------------------------------------------------
				if (system_status->Ethernet_speed >= 100000000)
				{
					system_status->Ethernet_link_status = ETHERNET_PHY;
					return Message;
				}				
			}
		}
	}
	return gcnew System::String(L"");
	
}
// --------------------------------------------------
//  Socket_Is_Available
//  Updated by Haim Otachi		11/01/2016
//	Change:						Add the content function from 'MyForm.cpp'.
// 	Description:				The function Check if socket is available.
// 	Reference: 
//	Input Value:	
//  Return Value:				The appropriate message
// --------------------------------------------------
int Real_Time_Thread::Socket_Is_Available()
{
	//---------------------------------------
	//		check if socket is available
	//---------------------------------------
	if (dsp_communication->DSP_connect() == GOOD)
	{
		//---------------------------------------
		//	check if can read system status
		//---------------------------------------
		if (Read_SYSTEM_Status() == GOOD)
		{			
			system_status->Ethernet_link_status = ETHERNET_GOOD;
			return GOOD;
		}
		else
		{		
			dsp_communication->DSP_disconnect();
			system_status->Ethernet_link_status = ETHERNET_OFF;
			return FAULT;			
		}
	}
	else
	{
		system_status->Ethernet_link_status = ETHERNET_OFF;
		return FAULT;
	}
}
// --------------------------------------------------
//  If_Calibrate_Target
//  Haim Otachi		11/01/2016
// 	Description:	Calibrate target
// 	Reference: 
//	Input Value:	
//  Return Value:	an appropriate message
// --------------------------------------------------
String^	Real_Time_Thread::If_Calibrator_Calibrate()
{
	if (dsp_communication->DSP_command(PC_COMMAND_CALIBRATE_CALIBRATOR) == FAULT)
	{
		return gcnew System::String("Error Clibrating external target.");
	}
	else
	{
		return gcnew System::String("Finished calibrating external target...");
	}
}
// --------------------------------------------------
//  If_Probe_Calibrate
//  Haim Otachi		11/01/2016
// 	Description:	Calibrate target
// 	Reference: 
//	Input Value:	
//  Return Value:	an appropriate message
// --------------------------------------------------
String^	Real_Time_Thread::If_Probe_Calibrate()
{
	if (dsp_communication->DSP_command(PC_COMMAND_CALIBRATE_PROBE) == FAULT)
	{
		return gcnew System::String("Error Clibrating probe.");
	}
	else
	{
		return gcnew System::String("Finished calibrating probe...");
	}
}
// --------------------------------------------------
//  Send_COMMAND_SNAPSHOT
//  Haim Otachi			2/1/2016
// 	description:		???
// 	reference:
//	input value:	
//  return value:	
// --------------------------------------------------
int	Real_Time_Thread::Send_Command_SNAPSHOT()
{
	if (dsp_communication->DSP_snapshot_command(system_status->SNAPSHOT_descriptor) == FAULT)
	{
		return FAULT;
	}
	return GOOD;
}
// --------------------------------------------------
//  Process_Snapshot
//  Alon Slapak 12/3/2015
//	Changes by:
//		Haim Otachi 11/01/2016:  Add function from MyForm.cpp
//
// 	Description:	Take snapshot measurement and plot
// 	Reference:	
//	Input Value:	buffer for the received samples
//  Return Value:	True/False
// --------------------------------------------------
bool Real_Time_Thread::Process_Snapshot(char* LOG_Path)
{
	char					MatlabScript[MAX_STRING_LENGTH];
	char					MatlabPath[MAX_STRING_LENGTH];
	char					MatlabError[MAX_STRING_LENGTH];
	char					CurrentPath[MAX_STRING_LENGTH];
	char					file_name[MAX_STRING_LENGTH];

	marshal_context ^		context = gcnew marshal_context();
	mxArray					*mxVector;
	string					Error_message;
	double					*Error_line = NULL;
	fstream					file_handle;

	uint32_t				i, j, l;
	int						buffer_size_double;
	double*					p_buffer_double;
	double*					p_buffer_cpi_double;
	int32_t					buffer_size_cpi_short;
	//-------------------------------------------
	//	Casting to double
	//-------------------------------------------
	buffer_size_double = system_status->SNAPSHOT_descriptor->SNAPSHOT_number_of_samples * sizeof(double) + sizeof(uint32_t);
	p_buffer_double = (double*)malloc(buffer_size_double);
	for (i = 0; i < system_status->SNAPSHOT_descriptor->SNAPSHOT_number_of_samples; i++)
	{
		p_buffer_double[i] = (double)p_buffer_short[i] / 32767;
	}
	buffer_size_double = ((system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples / system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation) * (system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers >> FFTC_ZERO_PADDING_MUL) * sizeof(double) * 2 * 2 + 2 * sizeof(uint32_t)) * 2;
	p_buffer_cpi_double = (double*)malloc(buffer_size_double);
	buffer_size_cpi_short = (system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples / system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation) * (system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers >> FFTC_ZERO_PADDING_MUL) * 2 * 2 * 2;
	for (i += sizeof(uint32_t), j = 0, l = i + sizeof(uint32_t); i < (buffer_size_cpi_short + l); i++, j++)
	{
		if (j == (0.5 * buffer_size_cpi_short))
		{
			i += sizeof(uint32_t);
		}
		p_buffer_cpi_double[j] = (double)p_buffer_short[i] / 32767;
	}
	//----------------------------------------------
	//   save to file
	//----------------------------------------------
	sprintf_s(file_name, "%s\\%s", LOG_Path, SNAPSHOT_SAMPLES_FILE);
	file_handle.open(file_name, ios::out | ios::binary);
	if (file_handle.fail())
	{
		free(p_buffer_double);
		free(p_buffer_cpi_double);
		return false;
	}
	file_handle.write((char*)p_buffer_double, system_status->SNAPSHOT_descriptor->SNAPSHOT_number_of_samples * sizeof(double));
	file_handle.write((char*)p_buffer_cpi_double, buffer_size_cpi_short * sizeof(double));
	file_handle.close();
	//-------------------------------------------
	//		LOG path -> MATLAB workspace
	//-------------------------------------------
	mxVector = mxCreateString(LOG_Path);
	engPutVariable(Matlab_engine, "LOG_path", mxVector);
	mxDestroyArray(mxVector);
	//-------------------------------------------
	//		SAMPLES file name -> MATLAB workspace
	//-------------------------------------------
	mxVector = mxCreateString(SNAPSHOT_SAMPLES_FILE);
	engPutVariable(Matlab_engine, "SAMPLES_file", mxVector);
	mxDestroyArray(mxVector);
	//-------------------------------------------
	//		TxRx_control_WORK -> MATLAB workspace
	//-------------------------------------------
	mxVector = mxCreateNumericMatrix(1, sizeof(T_TxRx_control), mxUINT32_CLASS, mxREAL);
	memcpy((void *)mxGetPr(mxVector), (void *)(&(system_status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK)), sizeof(T_TxRx_control));
	engPutVariable(Matlab_engine, "TxRx_control_WORK", mxVector);
	mxDestroyArray(mxVector);
	//-------------------------------------------
	//		SYSTEM_control.Rx_correction -> MATLAB workspace
	//-------------------------------------------
	mxVector = mxCreateNumericMatrix(1, sizeof(double) * 8, mxDOUBLE_CLASS, mxREAL);
	memcpy((void *)mxGetPr(mxVector), (void *)(&(system_status->system_control_0->SYSTEM_control_shadow.Rx_correction)), sizeof(double) * 8);
	engPutVariable(Matlab_engine, "Rx_correction", mxVector);
	mxDestroyArray(mxVector);
	//-------------------------------------------
	//		DET_algorithms -> MATLAB workspace
	//-------------------------------------------
	mxVector = mxCreateNumericMatrix(1, sizeof(T_DET_algorithms), mxUINT32_CLASS, mxREAL);
	memcpy((void *)mxGetPr(mxVector), (void *)(&(system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms)), sizeof(T_DET_algorithms));
	engPutVariable(Matlab_engine, "DET_algorithms", mxVector);
	mxDestroyArray(mxVector);
	//-------------------------------------------
	//		SENSOR_data -> MATLAB workspace
	//-------------------------------------------
	mxVector = mxCreateNumericMatrix(1, sizeof(T_SENSOR_data), mxDOUBLE_CLASS, mxREAL);
	memcpy((void *)mxGetPr(mxVector), (void *)(&(system_status->system_control_0->SENSOR_data)), sizeof(T_SENSOR_data));
	engPutVariable(Matlab_engine, "SENSOR_data", mxVector);
	mxDestroyArray(mxVector);
	//-------------------------------------------
	//		MATLAB goto script path
	//-------------------------------------------
	_getcwd(CurrentPath, MAX_STRING_LENGTH);
	sprintf_s(MatlabPath, "cd %s\\%s", CurrentPath, MATLAB_SCRIPTS_PATH);
	engEvalString(Matlab_engine, MatlabPath);
	//-------------------------------------------
	//		Run MATLAB script
	//-------------------------------------------
	Message = gcnew String("Processing data.");
	sprintf_s(MatlabScript, "%s", Matlab_Script_Name);
	engEvalString(Matlab_engine, MatlabScript);
	//-------------------------------------------
	//		Retrive MATLAB Error
	//-------------------------------------------
	sprintf_s(MatlabError, "Processing done.");
	mxVector = engGetVariable(Matlab_engine, "Error_message");
	if (mxVector != NULL)
	{
		Error_message = mxArrayToString(mxVector);
		sprintf_s(MatlabError, "%s", Error_message.c_str());
		mxDestroyArray(mxVector);
	}
	mxVector = engGetVariable(Matlab_engine, "Error_line");
	if (mxVector != NULL)
	{
		Error_line = mxGetPr(mxVector);
		sprintf_s(MatlabError, "%s in line: %5.f", Error_message.c_str(), *Error_line);
		mxDestroyArray(mxVector);
	}
	Message = gcnew String(MatlabError);
	free(p_buffer_double);
	return true;
}


String^	Real_Time_Thread::Read_Flash()
{
	if (dsp_communication->DSP_command(PC_COMMAND_SYSTEM_CONTROL_FROM_FLASH) == FAULT)
	{
		return gcnew String("Error sending Read from FLASH command.");
	}
	else
	{
		return gcnew String("Read from FLASH command was sent.");
	}
}

String^	Real_Time_Thread::Flash_Write()
{
	if (dsp_communication->DSP_command(PC_COMMAND_SYSTEM_CONTROL_TO_FLASH) == FAULT)
	{
		return gcnew String("Error sending Write to FLASH command.");
	}
	else
	{
		return gcnew String("Write to FLASH command was sent.");
	}
}

bool Real_Time_Thread::SENSOR_Config()
{
	if (dsp_communication->DSP_command(PC_COMMAND_RESET_SENSOR) == FAULT)
	{
		return false;
	}
	return true;
}

bool Real_Time_Thread::BOOT_UPLOADER(char* fileName, T_BUL_config* pBUL_config)
{
	if (dsp_communication->DSP_connect() == GOOD)
	{
		if (dsp_communication->DSP_send_BUL_image(fileName, pBUL_config) == FAULT)
		{
			return false;
		}
	}
	return true;
}

bool Real_Time_Thread::Sending_Command_Get_SNAPSHOT()
{
	if (dsp_communication->DSP_snapshot_command(system_status->SNAPSHOT_descriptor) == FAULT)
	{
		return false;
	}
	return true;
}

bool Real_Time_Thread::PC_Command_Start_Work_HV()
{
	if (dsp_communication->DSP_command(PC_COMMAND_START_WORK_HV) == FAULT)
	{
		return false;
	}
	return true;
}

bool Real_Time_Thread::PC_Command_Stop_Work()
{
	if (dsp_communication->DSP_command(PC_COMMAND_STOP_WORK) == FAULT)
	{
		return false;
	}
	return true;
}

//this function comes from 'MyForm.cpp'
bool Real_Time_Thread::Read_SNAPSHOT()
{
	//-------------------------------------------
	//	Find the important parameters to DSP receive
	//-------------------------------------------
	_Uint32t snapshot_number_of_samples = system_status->SNAPSHOT_descriptor->SNAPSHOT_number_of_samples * sizeof(short) + sizeof(uint32_t);
	_Uint32t range_samples = system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples;
	_Uint32t range_decimation = system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation;
	_Uint32t number_of_buffers = system_status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers >> FFTC_ZERO_PADDING_MUL;
	//-------------------------------------------
	//	calculate the 'buffer_size_short'
	//-------------------------------------------
	buffer_size_short = snapshot_number_of_samples  + ((range_samples / range_decimation) * number_of_buffers * sizeof(int16_t) * 2 * 2 + 2 * sizeof(uint32_t)) * 2;
	//-------------------------------------------
	//	Initialize the 'p_buffer_short'
	//-------------------------------------------
	p_buffer_short = (short*)malloc(buffer_size_short);
	//-------------------------------------------
	//	read SNAPSHOT data (short) 
	//-------------------------------------------
	if (dsp_communication->DSP_receive(READ_SNAPSHOT, (char*)p_buffer_short, buffer_size_short) != GOOD)
	{
		system_status->Monitor_Operation_mode = OPERATION_OFF;
		free(p_buffer_short);
		return false;
	}
	return true;
}

bool Real_Time_Thread::Read_Obstacles_Map(char* pbuffer, int size)
{
	if (dsp_communication->DSP_receive(READ_OBSTACLES_MAP, pbuffer, size) != GOOD)
	{
		return false;
	}
	return true;
}
#pragma endregion