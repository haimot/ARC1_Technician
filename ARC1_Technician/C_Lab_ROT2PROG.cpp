#include "C_Lab_ROT2PROG.h"
#using <System.dll>
//#include <iomanip>
//#include <msclr\marshal.h>
//#include <fstream>

#define		MAX_STRING_LENGTH				512

using namespace System;
using namespace System::IO;
using namespace System::IO::Ports;
//using namespace msclr::interop;
//using std::fstream;
// --------------------------------------------------
//  C_Lab_ROT2PROG
//  Alon Slapak		15/3/2016
// 	Description:	Constructor
// 	Reference:		
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
C_Lab_ROT2PROG::C_Lab_ROT2PROG()
{
	ROT2PROG_write_message = gcnew array<unsigned char>(ROT2COM_WRITE_MESSAGE_LENGTH);
	ROT2PROG_read_message = gcnew array<unsigned char>(ROT2COM_READ_MESSAGE_LENGTH);
	//-----------------------------------------
	//	Create a new SerialPort object
	//-----------------------------------------
	pSerialPort = gcnew SerialPort();
}
// --------------------------------------------------
//  ~C_Lab_ROT2PROG
//  Alon Slapak		15/3/2016
// 	Description:	Destructor
// 	Reference:		
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
C_Lab_ROT2PROG::~C_Lab_ROT2PROG()
{
	pSerialPort->Close();
}
// --------------------------------------------------
//  COM_port_Open
//  Alon Slapak		15/3/2016
// 	Description:	Set the COM port of the calibrator
// 	Reference:		
//	Input Value:	
//  Return Value:	true if secceeded, false else
// --------------------------------------------------
bool C_Lab_ROT2PROG::COM_port_Open(String^ com_port, String^ %return_message)
{
	//-------------------------------------
	//	Allow the user to set the appropriate properties.
	//-------------------------------------
	pSerialPort->PortName = com_port;
	pSerialPort->BaudRate = 600;
	pSerialPort->Parity = IO::Ports::Parity::None;
	pSerialPort->DataBits = 8;
	pSerialPort->StopBits = IO::Ports::StopBits::One;
	//-------------------------------------
	// Set the read/write timeouts
	//-------------------------------------
	pSerialPort->ReadTimeout = 5000;
	pSerialPort->WriteTimeout = 5000;
	//-------------------------------------
	// Open COM port
	//-------------------------------------
	try
	{
		pSerialPort->Open();
		return_message = gcnew String("The COM Port is:  " + com_port);
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
void C_Lab_ROT2PROG::COM_port_Close()
{
	pSerialPort->Close();
}
// --------------------------------------------------
//  Rot2prog_set_position
//  Alon Slapak 15/10/2014
// 	Description:	Update values in the azimuth and elevation
// 	Reference: http://ryeng.name/blog/3
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
void C_Lab_ROT2PROG::Rot2prog_set_position(float azimuth, float elevation)
{
	int		u_azimuth = (int)((azimuth + 360.0) / Azimuth_resolution);
	int		u_elevation = (int)((elevation + 360.0) / Elevation_resolution);


	// --------------------------------------------------
	//		Create message - Set 
	// --------------------------------------------------
	ROT2PROG_write_message[0] = 0x57;									/* S   */
	ROT2PROG_write_message[1] = 0x30 + (u_azimuth) / 1000;				/* H1  */
	ROT2PROG_write_message[2] = 0x30 + (u_azimuth % 1000) / 100;		/* H2  */
	ROT2PROG_write_message[3] = 0x30 + (u_azimuth % 100) / 10;			/* H3  */
	ROT2PROG_write_message[4] = 0x30 + (u_azimuth % 10);				/* H4  */
	
	ROT2PROG_write_message[5] = (int)(1.0 / Azimuth_resolution);
	
	ROT2PROG_write_message[6] = 0x30 + (u_elevation) / 1000;			/* V1  */
	ROT2PROG_write_message[7] = 0x30 + (u_elevation % 1000) / 100;		/* V2  */
	ROT2PROG_write_message[8] = 0x30 + (u_elevation % 100) / 10;		/* V3  */
	ROT2PROG_write_message[9] = 0x30 + (u_elevation % 10);				/* V4  */

	ROT2PROG_write_message[10] = (int)(1.0 / Elevation_resolution);

	ROT2PROG_write_message[11] = 0x2F;									/* K   */
	ROT2PROG_write_message[12] = 0x20;									/* END */
	// --------------------------------------------------
	//		Write message 
	// --------------------------------------------------
	pSerialPort->Write(ROT2PROG_write_message, 0, ROT2COM_WRITE_MESSAGE_LENGTH);
}
// --------------------------------------------------
//  Rot2prog_get_position
//  Alon Slapak 15/10/2014
// 	Description:	Update values in the azimuth and elevation
// 	Reference: http://ryeng.name/blog/3
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
void C_Lab_ROT2PROG::Rot2prog_get_position()
{
	int		number_of_bytes_read;

	pSerialPort->DiscardInBuffer();
	pSerialPort->DiscardOutBuffer();
	// --------------------------------------------------
	//		Create message - Request status
	// --------------------------------------------------
	ROT2PROG_write_message[0] = 0x57;			/* S   */
	ROT2PROG_write_message[1] = 0x00;			/* H1  */
	ROT2PROG_write_message[2] = 0x00;			/* H2  */
	ROT2PROG_write_message[3] = 0x00;			/* H3  */
	ROT2PROG_write_message[4] = 0x00;			/* H4  */

	ROT2PROG_write_message[6] = 0x00;			/* V1  */
	ROT2PROG_write_message[7] = 0x00;			/* V2  */
	ROT2PROG_write_message[8] = 0x00;			/* V3  */
	ROT2PROG_write_message[9] = 0x00;			/* V4  */

	ROT2PROG_write_message[11] = 0x1F;			/* K   */
	ROT2PROG_write_message[12] = 0x20;			/* END */
	// --------------------------------------------------
	//		Write message 
	// --------------------------------------------------
	pSerialPort->Write(ROT2PROG_write_message, 0, ROT2COM_WRITE_MESSAGE_LENGTH);
	// --------------------------------------------------
	//		Read message 
	// --------------------------------------------------
	System::Threading::Thread::Sleep(600);
	try
	{
		number_of_bytes_read = pSerialPort->Read(ROT2PROG_read_message, 0, ROT2COM_READ_MESSAGE_LENGTH);
	}
	catch (IOException^ e)
	{
		// TODO: Do something
		e->Message;
		Current_azimuth = -9999;
		return;
	}
	if (number_of_bytes_read != ROT2COM_READ_MESSAGE_LENGTH)
	{
		Current_azimuth = -9999;
		return;
	}
	// --------------------------------------------------
	//		parsing message 
	// --------------------------------------------------
	Current_azimuth = -360;
	Current_azimuth += ROT2PROG_read_message[1] * 100;
	Current_azimuth += ROT2PROG_read_message[2] * 10;
	Current_azimuth += ROT2PROG_read_message[3];
	Current_azimuth += (float)(ROT2PROG_read_message[4] / 10.0);

	Azimuth_resolution = (float)(1.0 / ROT2PROG_read_message[5]);
	Current_elevation = -360;

	Current_elevation += ROT2PROG_read_message[6] * 100;
	Current_elevation += ROT2PROG_read_message[7] * 10;
	Current_elevation += ROT2PROG_read_message[8];
	Current_elevation += (float)(ROT2PROG_read_message[9] / 10.0);

	Elevation_resolution = (float)(1.0 / ROT2PROG_read_message[10]);
}
// --------------------------------------------------
//  Start_Monitor
//  Alon Slapak		29/03/2016
// 	Description:	Start the Monitor
// 	Reference:		
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
bool C_Lab_ROT2PROG::Start_Rotator()
{
	//fstream              protocol_file;

	//char                 temp_string[MAX_STRING_LENGTH];
	//char                 Experiment_type[MAX_STRING_LENGTH];

	//marshal_context^	 context = gcnew marshal_context();
	////-------------------------------------------
	////     Open the file to read the obstacles
	////-------------------------------------------		
	//const char* protocol_file_name_of_rotator = context->marshal_as<const char*>(Protocol_file_name);
	//protocol_file.open(protocol_file_name_of_rotator, std::ios_base::in);
	//if (protocol_file.is_open())
	//{
	//	//-------------------------------------------
	//	//     Read the experiment typ
	//	//-------------------------------------------
	//	protocol_file >> Experiment_type;
	//	//--------------------------------------------------
	//	//     Doppler experiment
	//	//--------------------------------------------------
	//	if (strcmp(Experiment_type, "AOA") == 0)
	//	{
	//		//--------------------------------------------------
	//		//				load protocol
	//		//--------------------------------------------------
	//		protocol_file >> temp_string >> rotator_azimuth;
	//		protocol_file >> temp_string >> rotator_elevation;
	//	}
	//}
	return true;
}

float C_Lab_ROT2PROG::get_Rotator_Azimuth()
{
	return rotator_azimuth;
}
float C_Lab_ROT2PROG::get_Rotator_Elevation()
{
	return rotator_elevation;
}