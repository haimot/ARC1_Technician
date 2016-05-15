//------------Ethernet_TCP_Client.h----------------
//	Ethernet TCP SERVER interface
//	Alon Slapak	1/3/2015  
//  Update by Haim Otachi   25/11/2015
//	Reference:
//	MSDN:		http://msdn.microsoft.com/en-us/library/windows/desktop/ms737591(v=vs.85).aspx
//	Beej's UG:	http://beej.us/guide/bgnet/output/html/multipage/intro.html
//-------------------------------------------------
#pragma once
//---------------------------------------
//			SOCKET header file - for use with the 'SOCKET' class
//---------------------------------------
#include <WinSock2.h>
//-----------------------------------------
//		namespace:	DSP_Communication
//-----------------------------------------
namespace DSP_Communication
{
	public ref class C_Ethernet_TCP_Client
	{
		//---------------------------------------
		//			Private Fields
		//---------------------------------------
		private:
		SOCKET		socket_handle;
		int			WSADATA_status;
		//---------------------------------------
		//			Constructor
		//---------------------------------------
		public:		C_Ethernet_TCP_Client();
		//---------------------------------------
		//			Destructor
		//---------------------------------------
		public:		~C_Ethernet_TCP_Client();
		//---------------------------------------
		//			Methods
		//---------------------------------------
		public:
		int			Ethernet_TCP_Connect(int port_number);
		int			Ethernet_TCP_Disconnect();

		int			Ethernet_TCP_Send(char* buffer, int bufLength);
		int			Ethernet_TCP_Receive(char* buffer, int buffer_length, int *bytes_received);
	
		int			Ethernet_TCP_GOOD();	
	};
}
