#include "C_Lab_Calibrator.h"
#using <System.dll>
#include <stdio.h>
#include <string.h>
//#include <fstream>
//#include <msclr\marshal.h>

#define		MAX_STRING_LENGTH				512

using namespace System;
using namespace System::IO;
//using namespace msclr::interop;
using namespace System::IO::Ports;
//using namespace System::Threading;

// --------------------------------------------------
//  C_Lab_Calibrator
//  Alon Slapak		8/3/2016
// 	Description:	Constructor
// 	Reference:		
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
C_Lab_Calibrator::C_Lab_Calibrator()
{
	UART_message = gcnew array<unsigned char>(UART_MESSAGE_LENGTH);
	//-----------------------------------------
	//	Create a new SerialPort object
	//-----------------------------------------
	pSerialPort = gcnew SerialPort();

	Calibrator_COM_port = new char;
	Calibrator_file_name = new char;

	strcpy(Calibrator_COM_port, "");
	strcpy(Calibrator_file_name, "");

	Doppler_start_Hz = 0.0;
	Doppler_stop_Hz = 0.0;
	Doppler_step_Hz = 0.0;
	Doppler_repeat = 0.0;	
}
// --------------------------------------------------
//  ~C_Lab_Calibrator
//  Alon Slapak		8/3/2016
// 	Description:	Destructor
// 	Reference:		
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
C_Lab_Calibrator::~C_Lab_Calibrator()
{
	pSerialPort->Close();
}
// --------------------------------------------------
//  COM_port_Open
//  Alon Slapak		8/3/2016
// 	Description:	Set the COM port of the calibrator
// 	Reference:		
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
bool C_Lab_Calibrator::COM_port_Open(char* com_port, String^ %return_message)
{
	//-------------------------------------
	//     Allow the user to set the appropriate properties.
	//-------------------------------------
	pSerialPort->PortName = gcnew String(com_port);
	pSerialPort->BaudRate = 9600;
	pSerialPort->Parity = IO::Ports::Parity::None;
	pSerialPort->DataBits = 8;
	pSerialPort->StopBits = IO::Ports::StopBits::One;
	//-------------------------------------
	//	  Set the read/write timeouts
	//-------------------------------------
	pSerialPort->ReadTimeout = 5000;
	pSerialPort->WriteTimeout = 5000;
	//-------------------------------------
	//	  Open COM port
	//-------------------------------------
	try
	{
		pSerialPort->Open();
		return_message = gcnew String("The COM Port is:  " + gcnew String(com_port));
	}
	catch (IO::IOException^ ioex)
	{
		return_message = gcnew String("The error message is:  " + ioex->Message);
		return false;		
	}
	return true;
}
// --------------------------------------------------
//  Close_COM_port
//  Alon Slapak		8/3/2016
// 	Description:	Closing COM port
// 	Reference:		
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
void C_Lab_Calibrator::COM_port_Close()
{
	pSerialPort->Close();
}
// --------------------------------------------------
//  Lab_Set_Doppler
//  Alon Slapak		8/3/2016
// 	Description:	Set Doppler value in Hz
// 	Reference:		
//	Input Value:	the doopler value in Hz
//  Return Value:	
// --------------------------------------------------
bool C_Lab_Calibrator::Lab_Set_Doppler(short Doppler_Hz)
{
	for (int k = 1; k < UART_REPEAT_TRIAL; k++)
	{
		//--------------------------------------------------
		//            Write DOPPLER
		//--------------------------------------------------
		pSerialPort->DiscardOutBuffer();
		UART_message[0] = (char)((Doppler_Hz >> 8) & 0xFF);
		UART_message[1] = (char)(Doppler_Hz & 0xFF);
		UART_message[2] = UART_MESSAGE_WRITE_DOPPLER;
		pSerialPort->Write(UART_message, 0, 3);
		//--------------------------------------------------
		//            Read Doppler
		//--------------------------------------------------
		System::Threading::Thread::Sleep(40);
		short Doppler_received_Hz = Lab_Get_Doppler();
		//--------------------------------------------------
		//            Verify
		//--------------------------------------------------
		if (Doppler_Hz == Doppler_received_Hz)
		{
			return true;
		}
	}
	return false;
}
// --------------------------------------------------
//  Lab_Get_Doppler
//  Alon Slapak		8/3/2016
// 	Description:	Get Doppler value in Hz
// 	Reference:		
//	Input Value:	
//  Return Value:	the Doppler value in Hz
// --------------------------------------------------
short C_Lab_Calibrator::Lab_Get_Doppler()
{
	pSerialPort->DiscardInBuffer();
	pSerialPort->DiscardOutBuffer();
	//--------------------------------------
	//            Send read command
	//--------------------------------------
	UART_message[0] = 0;
	UART_message[1] = 0;
	UART_message[2] = UART_MESSAGE_READ_DOPPLER;
	pSerialPort->Write(UART_message, 0, 3);
	//--------------------------------------
	//            Read data
	//--------------------------------------
	System::Threading::Thread::Sleep(40);
	int number_of_bytes_read;
	number_of_bytes_read = pSerialPort->Read(UART_message, 0, 3);
	if ((number_of_bytes_read != UART_MESSAGE_LENGTH) || (UART_message[2] != UART_MESSAGE_OK))
	{
		return -9999;
	}
	return (short)((UART_message[0] << 8) + UART_message[1]);
}
// --------------------------------------------------
//  Lab_Set_SNR
//  Haim Otachi		17/3/2016
// 	Description:	Set SNR value in dB
// 	Reference:		
//	Input Value:	the SNR value in dB
//  Return Value:	
// --------------------------------------------------
bool C_Lab_Calibrator::Lab_Set_SNR(short SNR_dB)
{
	for (int k = 1; k < UART_REPEAT_TRIAL; k++)
	{
		//--------------------------------------------------
		//            Write SNR
		//--------------------------------------------------
		pSerialPort->DiscardOutBuffer();
		UART_message[0] = (char)((SNR_dB >> 8) & 0xFF);
		UART_message[1] = (char)(SNR_dB & 0xFF);
		UART_message[2] = UART_MESSAGE_WRITE_SNR;
		pSerialPort->Write(UART_message, 0, 3);
		//--------------------------------------------------
		//            Read SNR
		//--------------------------------------------------
		System::Threading::Thread::Sleep(40);
		short SNR_received_dB = Lab_Get_SNR();
		//--------------------------------------------------
		//            Verify
		//--------------------------------------------------
		if (SNR_dB == SNR_received_dB)
		{
			return true;
		}
	}
	return false;
}
// --------------------------------------------------
//  Lab_Get_SNR
//  Haim Otachi		17/3/2016
// 	Description:	Get SNR value in dB
// 	Reference:		
//	Input Value:	
//  Return Value:	the SNR value in dB
// --------------------------------------------------
short C_Lab_Calibrator::Lab_Get_SNR()
{
	pSerialPort->DiscardInBuffer();
	pSerialPort->DiscardOutBuffer();
	//--------------------------------------
	//            Send read command
	//--------------------------------------
	UART_message[0] = 0;
	UART_message[1] = 0;
	UART_message[2] = UART_MESSAGE_READ_SNR;
	pSerialPort->Write(UART_message, 0, 3);
	//--------------------------------------
	//            Read data
	//--------------------------------------
	System::Threading::Thread::Sleep(40);
	int number_of_bytes_read;
	number_of_bytes_read = pSerialPort->Read(UART_message, 0, 3);
	if ((number_of_bytes_read != UART_MESSAGE_LENGTH) || (UART_message[2] != UART_MESSAGE_OK))
	{
		return -9999;
	}
	return (short)((UART_message[0] << 8) + UART_message[1]);
}






















//#pragma region added by Haim Otachi at 15/03/2016
////-------------------------------------
////			Public Methods
////-------------------------------------
void C_Lab_Calibrator::LAB_START()
{
//	char                 Experiment_type[MAX_STRING_LENGTH];
//	std::fstream         protocol_file;
//	//-------------------------------------------
//	//		 If the file is opened
//	//-------------------------------------------	
//	if (Open_Protocol(protocol_file) == true)
//	{
//		//-------------------------------------------
//		//     Read the experiment typ
//		//-------------------------------------------
//		protocol_file >> Experiment_type;
//		//-------------------------------------------
//		//     Doppler experiment
//		//-------------------------------------------
//		Doppler_Experiment();
//	}
//	
}
////-------------------------------------
////			Private Methods
////-------------------------------------
void /*float***/	C_Lab_Calibrator::Prepare_Array_For_Results()
{
	////--------------------------------------------------
	////     Prepare array for results
	////--------------------------------------------------
	//float** results_array = new ; //= (float**)malloc(Doppler_repeat * sizeof(float*));

	//for (int k = 0; k < Doppler_repeat; k++)
	//{
	//	//results_array[k] = (float*)malloc((int)((Doppler_stop_Hz - Doppler_start_Hz) / Doppler_step_Hz + 1) * sizeof(float));
	//}

	//return results_array;
}

//bool C_Lab_Calibrator::Open_Protocol(std::fstream% protocol_file)
//{
//	char              temp_string[MAX_STRING_LENGTH];
//	marshal_context^  context = gcnew marshal_context();
//	//-------------------------------------------
//	//     Open the file to read the obstacles
//	//-------------------------------------------		
//	const char* protocol_file_name_of_calibrator = context->marshal_as<const char*>(Protocol_file_name);
//	protocol_file.open(protocol_file_name_of_calibrator, std::ios_base::in);
//	if (protocol_file.is_open())
//	{
//		//--------------------------------------------------
//		//				load protocol
//		//--------------------------------------------------
//		protocol_file >> temp_string >> Calibrator_COM_port;
//		protocol_file >> temp_string >> Doppler_start_Hz;
//		protocol_file >> temp_string >> Doppler_stop_Hz;
//		protocol_file >> temp_string >> Doppler_step_Hz;
//		protocol_file >> temp_string >> Doppler_repeat;
//		protocol_file >> temp_string >> reults_file_name;
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//void C_Lab_Calibrator::Doppler_Experiment()
//{
//	//--------------------------------------------------
//	//     Prepare array for results
//	//--------------------------------------------------
//	float** results_array = Prepare_Array_For_Results();
//	//--------------------------------------------------
//	//     Run protocol
//	//--------------------------------------------------
//	Run_Protocol();
//}
//
//void C_Lab_Calibrator::Run_Protocol()
//{
//	String^				 return_message;
//	if (COM_port_Open(Calibrator_COM_port, return_message) == true)
//	{
//
//	}
//}
//#pragma endregion