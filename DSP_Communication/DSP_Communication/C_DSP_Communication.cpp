// This is the main DLL file.
//------------------------------------------------
//	Communicatino with DSP
//	Alon Slapak	5/10/2014
//	Reference:
//----------------------------------------------------
#include "C_DSP_Communication.h"
#include <fstream>
//-----------------------------------------
//		MISC. parameters
//-----------------------------------------
#define GOOD						0
#define FAULT						1
//-----------------------------------------
//			Ethernet
//-----------------------------------------
#define ETHERNET_BUFFER_LENGTH		1024
#define ETHERNET_BUFFER_LENGTH		1024
#define ETHERNET_IP_ADDRESS			"192.168.2.100"
#define ETHERNET_MESSAGING_PORT		7
#define ETHERNET_RECORDING_PORT		8
#define	ETHERNET_TIME_OUT			10000					//[Micro-Seconds]
#define	ETHERNET_PING				12345
//-----------------------------------------
//		using namespace:	std
//-----------------------------------------
using namespace std;
//-----------------------------------------
//		Main namespace:	DSP_Communication
//-----------------------------------------
namespace DSP_Communication
{
	// --------------------------------------------------
	//  C_DSP_Communication 
	//  Alon Slapak 5/10/2014
	// 	Description:	Constructor
	// 	Reference: 
	//
	//  Return Value: 
	// --------------------------------------------------
	C_DSP_Communication::C_DSP_Communication() {}
	// --------------------------------------------------
	//  ~C_DSP_Communication  
	//  Alon Slapak 5/10/2014
	// 	Description:	Destructor
	// 	Reference: 
	//
	//  Return Value: 
	// --------------------------------------------------
	C_DSP_Communication::~C_DSP_Communication() {}
	// --------------------------------------------------
	//  DSP_connect
	//  Alon Slapak 29/12/2015
	// 	Description:	Open socket
	// 	Reference: 
	//
	//  Return Value: 
	// --------------------------------------------------
	int C_DSP_Communication::DSP_connect()
	{
		if (Ethernet_TCP_Client.Ethernet_TCP_Connect(ETHERNET_MESSAGING_PORT) == FAULT)
		{
			return FAULT;
		}
		return GOOD;
	}
	// --------------------------------------------------
	//  DSP_disconnect
	//  Alon Slapak 29/12/2015
	// 	Description:	Close socket
	// 	Reference: 
	//
	//  Return Value: 
	// --------------------------------------------------
	int C_DSP_Communication::DSP_disconnect()
	{
		if (Ethernet_TCP_Client.Ethernet_TCP_Disconnect() == FAULT)
		{
			return FAULT;
		}
		return GOOD;
	}
	// --------------------------------------------------
	//  DSP_command  
	//  Alon Slapak 4/3/2015
	// 	Description: Send command to DSP:
	//					- Send command.
	// 	Reference: 
	//	Input value:	Command (E_PC_command) to the DSP
	//  Return Value:  GOOD/FAULT
	// --------------------------------------------------
	int C_DSP_Communication::DSP_command(int command_to_DSP)
	{
		//---------------------------------------
		//			 Send command
		//---------------------------------------
		if (Ethernet_TCP_Client.Ethernet_TCP_Send((char*)&command_to_DSP, sizeof(command_to_DSP)) == FAULT)
		{
			return FAULT;
		}
		return GOOD;
	}
	// --------------------------------------------------
	//  DSP_send_BUL_image  
	//  Alon Slapak 5/10/2014
	// 	Description: Send BOOT image to DSP	
	// 	Reference: 
	//  Input value:  image file name, configuration struct
	//  Return Value: GOOD/FAULT
	// --------------------------------------------------
	int C_DSP_Communication::DSP_send_BUL_image(char* fileName, T_BUL_config* pBUL_config)
	{
		int						number_of_bytes_to_send;
		int						number_of_bytes_left;
		char					buffer[ETHERNET_BUFFER_LENGTH];
		//---------------------------------------
		//	Send command
		//---------------------------------------
		if (DSP_command(SEND_BUL_IMAGE) == FAULT)
		{
			return FAULT;
		}
		//---------------------------------------
		//	send configuration structure
		//---------------------------------------
		if (Ethernet_TCP_Client.Ethernet_TCP_Send((char*)pBUL_config, sizeof(T_BUL_config)) == FAULT)
		{
			return FAULT;
		}
		//---------------------------------------
		//	send BUL image from file
		//---------------------------------------
		fstream file_handle(fileName, ios::in | ios::binary);
		if (file_handle.fail())
		{
			return FAULT;
		}
		number_of_bytes_left = pBUL_config->image_size;
		do
		{
			//  Buffer length to read
			if (number_of_bytes_left < ETHERNET_BUFFER_LENGTH)
				number_of_bytes_to_send = number_of_bytes_left;
			else
				number_of_bytes_to_send = ETHERNET_BUFFER_LENGTH;
			//  read from file
			file_handle.read((char*)buffer, number_of_bytes_to_send);
			//  Send buffer
			if ((Ethernet_TCP_Client.Ethernet_TCP_Send((char*)buffer, number_of_bytes_to_send) == FAULT))
			{
				printf("Error writing image file: %d bytes left.\n", number_of_bytes_left);
				file_handle.close();
				return FAULT;
			}
			number_of_bytes_left -= number_of_bytes_to_send;
		} while (number_of_bytes_left > 0);
		file_handle.close();
		//--------------------------------------
		//  clean up
		//--------------------------------------
		return GOOD;
	}
	// --------------------------------------------------
	//  DSP_send  
	//  Alon Slapak 3/11/2014
	// 	Description: Send general TAKS message	
	// 	Reference: 
	//  Input value:	Command to DSP (E_PC_command), pointer to buffer, and buffer size.
	//  Return Value:	GOOD/FAULT
	// --------------------------------------------------
	int C_DSP_Communication::DSP_send(int command_to_DSP, char* pbuffer, int size)
	{
		//---------------------------------------
		//	Send command
		//---------------------------------------
		if (DSP_command(command_to_DSP) == FAULT)
		{
			return FAULT;
		}
		//---------------------------------------
		//	send message
		//---------------------------------------
		if (Ethernet_TCP_Client.Ethernet_TCP_Send((char*)pbuffer, size) == FAULT)
		{
			return FAULT;
		}

		return GOOD;
	}
	// --------------------------------------------------
	//  DSP_receive 
	//  Alon Slapak 3/11/2014
	// 	Description:	
	// 	Reference: 
	// Input value:		Command to DSP (E_PC_command), pointer to buffer, and buffer size.
	//  Return Value:	GOOD/FAULT
	//  TODO:			REMOVE size  
	// --------------------------------------------------
	int C_DSP_Communication::DSP_receive(int command_to_DSP, char* pbuffer, int size)
	{
		int						bytes_received;
		int						number_of_bytes_left;
		int						iResult;
		char					*pBuf;
		//---------------------------------------
		//	Send command
		//---------------------------------------
		if (DSP_command(command_to_DSP) == FAULT)
		{
			return FAULT;
		}
		//---------------------------------------
		//	Read data to buffer
		//---------------------------------------
		number_of_bytes_left = size;
		pBuf = pbuffer;
		//  Read buffer
		iResult = Ethernet_TCP_Client.Ethernet_TCP_Receive(pBuf, size, &bytes_received);
		//  Validate read length
		if (iResult == FAULT)
		{
			printf("Error downloading buffer: %d bytes received.\n", bytes_received);
			return FAULT;
		}
		return GOOD;
	}
	// --------------------------------------------------
	//  DSP_snapshot_command  
	//  Alon Slapak 11/3/2018
	// 	Description: send the DSp to acquire the snapshot.  	
	// 	Reference: 
	//	Input Value:  pointer to the snapshot descriptor
	//  Return Value:  GOOD/FAULT
	// --------------------------------------------------
	int C_DSP_Communication::DSP_snapshot_command(T_SNAPSHOT_descriptor* SNAPSHOT_descriptor)
	{
		//---------------------------------------
		//	Send command
		//---------------------------------------
		if (DSP_command(PC_COMMAND_SNAPSHOT) == FAULT)
		{
			return FAULT;
		}
		//---------------------------------------
		//	send configuration structure
		//---------------------------------------
		if (Ethernet_TCP_Client.Ethernet_TCP_Send((char*)SNAPSHOT_descriptor, sizeof(T_SNAPSHOT_descriptor)) == FAULT)
		{
			return FAULT;
		}
		return GOOD;
	}
	// --------------------------------------------------
	//  DSP_read_SYSTEM_status_task 
	//  Alon Slapak 24/2/2015
	// 	Description:	
	// 	Reference: 
	//
	//  Return Value: 
	// --------------------------------------------------
	void C_DSP_Communication::DSP_read_SYSTEM_status_task()
	{
		int							bytes_received;
		int							number_of_bytes_left;
		int							iResult;
		//---------------------------------------
		//	Send command
		//---------------------------------------
		if (DSP_command(READ_SYSTEM_STATUS) == FAULT)
		{
			*client_messaging_status = FAULT;
			return;
		}
		//---------------------------------------
		//	Read data to buffer
		//---------------------------------------
		number_of_bytes_left = client_buffer_size;
		do
		{
			//  Read buffer
			iResult = Ethernet_TCP_Client.Ethernet_TCP_Receive((char*)client_buffer_pointer, ETHERNET_BUFFER_LENGTH, &bytes_received);
			//  Validate read length
			if ((iResult == FAULT) || ((bytes_received != ETHERNET_BUFFER_LENGTH) && (bytes_received != number_of_bytes_left)))
			{
				printf("Error downloading buffer: %d bytes received.\n", bytes_received);
				Ethernet_TCP_Client.Ethernet_TCP_Disconnect();
				*client_messaging_status = FAULT;
				return;
			}
			number_of_bytes_left -= bytes_received;
			client_buffer_pointer += ETHERNET_BUFFER_LENGTH;

		} while (number_of_bytes_left > 0);
		//---------------------------------------
		//	Disconnect from socket
		//---------------------------------------
		if (Ethernet_TCP_Client.Ethernet_TCP_Disconnect() == FAULT)
		{
			*client_messaging_status = FAULT;
			return;
		}
		*client_messaging_status = GOOD;
	}
	// --------------------------------------------------
	//  DSP_read_SYSTEM_status_task 
	//  Alon Slapak 24/2/2015
	// 	Description:	
	// 	Reference: 
	//
	//  Return Value: 
	// --------------------------------------------------
	int C_DSP_Communication::DSP_read_SYSTEM_status(char* pbuffer, int buffer_size)
	{
		int							bytes_received;
		int							iResult;
		char*						buffer = pbuffer;
		//---------------------------------------
		//	Send command
		//---------------------------------------
		if (DSP_command(READ_SYSTEM_STATUS) == FAULT)
		{
			return FAULT;
		}
		//---------------------------------------
		//	Read data to buffer
		//---------------------------------------
		iResult = Ethernet_TCP_Client.Ethernet_TCP_Receive((char*)buffer, buffer_size, &bytes_received);
		//  Validate read length
		if (iResult == FAULT)
		{
			printf("Error downloading buffer: %d bytes received.\n", bytes_received);
			return FAULT;
		}
		return GOOD;
	}
}

