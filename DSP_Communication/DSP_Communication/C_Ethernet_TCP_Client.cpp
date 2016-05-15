// This is the main DLL file.
//------------Ethernet_TCP_Client.h - This is the main DLL file----------------
//	Ethernet TCP SERVER interface
//	Alon Slapak	1/3/2015  
//  Update by Haim Otachi   25/11/2015
//	Reference:
//	MSDN:		http://msdn.microsoft.com/en-us/library/windows/desktop/ms737591(v=vs.85).aspx
//	Beej's UG:	http://beej.us/guide/bgnet/output/html/multipage/intro.html
//-----------------------------------------------------------------------------
#include "C_Ethernet_TCP_Client.h"
#include <WS2tcpip.h>

#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
//-----------------------------------------
//		MISC. parameters
//-----------------------------------------
#define GOOD						0
#define FAULT						1
//-----------------------------------------
//		Ethernet
//-----------------------------------------
#define ETHERNET_IP_ADDRESS			"192.168.2.100"
#define ETHERNET_MESSAGING_PORT		7
#define ETHERNET_RECORDING_PORT		8
//-----------------------------------------
//		Main namespace:	DSP_Communication
//-----------------------------------------
namespace DSP_Communication
{
	// --------------------------------------------------
	//  C_Ethernet_TCP_Client  (constructor)
	//  Alon Slapak 3/10/2014
	// 	Description:	Constructor
	// 	Reference: 
	//
	//  Return Value: 
	// --------------------------------------------------
	C_Ethernet_TCP_Client::C_Ethernet_TCP_Client()
	{
		//-----------------------------------------------
		//		Initialize Winsock
		//-----------------------------------------------
		WSADATA			wsaData;
		int				iResult;
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != NO_ERROR)
		{
			WSADATA_status = FAULT;
		}
		else
		{
			WSADATA_status = GOOD;
		}
		//-----------------------------------------------
		//		Initialize parameters
		//-----------------------------------------------
		socket_handle = INVALID_SOCKET;
	}
	// --------------------------------------------------
	//  ~C_Ethernet_TCP_Client  (Destructor)
	//  Alon Slapak 3/10/2014
	// 	Description:	Destructor
	//	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	C_Ethernet_TCP_Client::~C_Ethernet_TCP_Client()
	{
		WSACleanup();
	}
	// --------------------------------------------------
	//  Ethernet_TCP_Connect  
	//  Alon Slapak 3/10/2014
	// 	Description: Connect to socket. To avoid recv/send error which might block
	//				the progeam, we use non-blocking select() to monitor the socket.
	// 	Reference: http://codeverge.com/embarcadero.cppbuilder.cpp/timeout-on-tcp-connection-edit/1059636
	//  Input value:
	//  Return Value: GOOD/FAULT
	// --------------------------------------------------
	int C_Ethernet_TCP_Client::Ethernet_TCP_Connect(int port_number)
	{
		int				iResult;
		sockaddr_in		socket_adress;
		//----------------------------------------------
		// Create a SOCKET for connecting to server
		//----------------------------------------------
		socket_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // use IPv4, TCP stream sockets
		if (socket_handle == INVALID_SOCKET)
		{
			return FAULT;
		}
		//----------------------------------------------
		// Socet Address http://beej.us/guide/bgnet/output/html/multipage/sockaddr_inman.html
		//----------------------------------------------
		socket_adress.sin_family = AF_INET;
		socket_adress.sin_port = htons(port_number);
		inet_pton(AF_INET, ETHERNET_IP_ADDRESS, &socket_adress.sin_addr);
		
		memset(socket_adress.sin_zero, 0, 8);
		//----------------------------------------------
		// Connect to (blocking) socket
		//----------------------------------------------
		iResult = connect(socket_handle, (SOCKADDR*)&socket_adress, sizeof(SOCKADDR));
		if (iResult == SOCKET_ERROR)
		{
			closesocket(socket_handle);
			return FAULT;
		}
		return GOOD;
	}
	// --------------------------------------------------
	// Ethernet_TCP_Disconnect  
	//  Alon Slapak 3/10/2014
	// 	Description:	Disconnect from socket
	//	Reference: 
	//
	//  Return Value: 
	// --------------------------------------------------
	int C_Ethernet_TCP_Client::Ethernet_TCP_Disconnect()
	{
		//---------------------------------------
		//			Cleanup
		//---------------------------------------
		if (closesocket(socket_handle) == SOCKET_ERROR)
		{
			return FAULT;
		}
			
		return GOOD;
	}
	// --------------------------------------------------
	//  Ethernet_TCP_Send
	//  Alon Slapak 3/10/2014
	// 	Description:
	// 	Reference: 
	//  Input value:
	//			buffer			- pointer to buffer to send
	//			buffer_length	- number of bytes to send
	//  Return Value: GOOD/FAULT
	// --------------------------------------------------
	int C_Ethernet_TCP_Client::Ethernet_TCP_Send(char* buffer, int buffer_length)
	{
		int		iResult;
		iResult = send(socket_handle, buffer, buffer_length, 0);
		if (iResult == SOCKET_ERROR)
		{
			return FAULT;
		}
		return GOOD;
	}
	// --------------------------------------------------
	//  Ethernet_TCP_Receive
	//  Alon Slapak 3/10/2014
	// 	Description:
	// 	Reference: 
	//  Input value: 
	//			buffer			- pointer to buffer into which to receive
	//			buffer_length	- number of bytes to receive
	//  Return Value: FAULT or number of bytes received
	// --------------------------------------------------
	int C_Ethernet_TCP_Client::Ethernet_TCP_Receive(char* buffer, int buffer_length, int *bytes_received)
	{
		int		iResult;
		//----------------------------------------------
		// Receive buffer 
		//----------------------------------------------
		iResult = recv(socket_handle, buffer, buffer_length, MSG_WAITALL);
		if (iResult <= 0)
		{
			return FAULT;
		}

		*bytes_received = iResult;
		return GOOD;
	}
	// --------------------------------------------------
	//  Ethernet_TCP_GOOD
	//  Alon Slapak 7/10/2014
	// 	Description: Check if port is alive 
	// 	Reference:  http://www.experts-exchange.com/Programming/Microsoft_Development/Q_20699740.html
	//  Input value: 
	//  Return Value: GOOD/FAULT
	// --------------------------------------------------
	int C_Ethernet_TCP_Client::Ethernet_TCP_GOOD()
	{
		int				iResult;
		sockaddr_in		socket_adress;
		ULONG			NonBlk = 1;
		//----------------------------------------------
		// Create a SOCKET for connecting to server
		//----------------------------------------------
		socket_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // use IPv4, TCP stream sockets
		if (socket_handle == INVALID_SOCKET)
		{
			return FAULT;
		}
		//----------------------------------------------
		// Socet Address http://beej.us/guide/bgnet/output/html/multipage/sockaddr_inman.html
		//----------------------------------------------
		socket_adress.sin_family = AF_INET;
		socket_adress.sin_port = htons(ETHERNET_MESSAGING_PORT);
		inet_pton(AF_INET, ETHERNET_IP_ADDRESS, &socket_adress.sin_addr);
		
		memset(socket_adress.sin_zero, 0, 8);
		//----------------------------------------------
		// Set to Non-blocking mode
		//----------------------------------------------
		iResult = ioctlsocket(socket_handle, FIONBIO, &NonBlk);
		if (iResult != 0)
		{
			return FAULT;
		}
		//----------------------------------------------
		// Connect to Non-blocking socket
		//----------------------------------------------
		iResult = connect(socket_handle, (SOCKADDR*)&socket_adress, sizeof(SOCKADDR));
		if (iResult == SOCKET_ERROR)
		{
			fd_set		Write;
			FD_ZERO(&Write);
			FD_SET(socket_handle, &Write);

			TIMEVAL Timeout;
			Timeout.tv_sec = 0;
			Timeout.tv_usec = 10000;

			iResult = select(0, NULL, &Write, NULL, &Timeout);
			if (iResult < 1)		// The select function returns the total number of socket handles that are writable 
			{
				closesocket(socket_handle);
				return FAULT;
			}
		}
		closesocket(socket_handle);
		return GOOD;
	}
}