#pragma once

#using <System.dll>

using namespace System;
using namespace System::IO;
using namespace System::IO::Ports;
using namespace System::Threading;

#define	UART_REPEAT_TRIAL				10
#define UART_MESSAGE_LENGTH				3

#define UART_MESSAGE_WRITE_DOPPLER		121
#define UART_MESSAGE_READ_DOPPLER		122

#define UART_MESSAGE_WRITE_SNR			129
#define UART_MESSAGE_READ_SNR			130

#define UART_MESSAGE_OK					255


ref class C_Lab_Calibrator
{
	//-------------------------------------
	//			Private Fields
	//-------------------------------------
	private:
	static SerialPort^		pSerialPort;
	array<unsigned char>^	UART_message;
	//
	//	added by Haim Otachi at 15/03/2016 from MyForm.h
	//
	char*					Calibrator_COM_port;
	char*					Calibrator_file_name;

	float					Doppler_start_Hz;
	float					Doppler_stop_Hz;
	float					Doppler_step_Hz;
	float					Doppler_repeat;	
	//-------------------------------------
	//			Public Fields
	//-------------------------------------
	public:
	String^					Protocol_file_name;
	//-------------------------------------
	//			Constructor
	//-------------------------------------
	public:					C_Lab_Calibrator();
	//-------------------------------------
	//			Destructor
	//-------------------------------------
	public:					~C_Lab_Calibrator();
	//-------------------------------------
	//			Public Methods
	//-------------------------------------
	public:
	bool					COM_port_Open(char* com_port, String^ %return_message);
	void					COM_port_Close();

	bool					Lab_Set_Doppler(short Doppler_Hz);
	short					Lab_Get_Doppler();

	bool					Lab_Set_SNR(short SNR_dB);
	short					Lab_Get_SNR();
	//
	//	added by Haim Otachi at 15/03/2016
	//
	void					LAB_START();
	//-------------------------------------
	//			Private Methods
	//
	//	added by Haim Otachi at 15/03/2016 from MyForm.h
	//
	//-------------------------------------
	private:
	void					Prepare_Array_For_Results();
};

