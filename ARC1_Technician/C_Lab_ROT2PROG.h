#pragma once

#using <System.dll>

using namespace System;
using namespace System::IO;
using namespace System::IO::Ports;
using namespace System::Threading;

#define	ROT2COM_WRITE_MESSAGE_LENGTH	13
#define	ROT2COM_READ_MESSAGE_LENGTH		12
//-------------------------------------
//		class:		C_Lab_ROT2PROG
//-------------------------------------
ref class C_Lab_ROT2PROG
{
	//-------------------------------------
	//			Private Fields
	//-------------------------------------
	char*						Rotator_COM_port;
	char*						Rotator_file_name;
	//-------------------------------------
	//			Public Fields
	//-------------------------------------
	public:
	static SerialPort^			pSerialPort;
	array<unsigned char>^		ROT2PROG_write_message;
	array<unsigned char>^		ROT2PROG_read_message;

	float						Azimuth_resolution;
	float						Elevation_resolution;
	float						Current_azimuth;
	float						Current_elevation;

	float						rotator_azimuth;
	float						rotator_elevation;
	
	String^						Protocol_file_name;
	//-------------------------------------
	//			Constructor
	//-------------------------------------
	public:						C_Lab_ROT2PROG();
	//-------------------------------------
	//			Destructor
	//-------------------------------------
	public:						~C_Lab_ROT2PROG();
	//-------------------------------------
	//			Public Methods
	//-------------------------------------
	bool						Start_Rotator();

	bool						COM_port_Open(String^ com_port, String^ %return_message);
	void						COM_port_Close();
			
	void						Rot2prog_set_position(float azimuth, float elevation);
	void						Rot2prog_get_position();

	float						get_Rotator_Azimuth();
	float						get_Rotator_Elevation();
};

