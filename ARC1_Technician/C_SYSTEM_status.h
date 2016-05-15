#ifndef C_SYSTEM_STATUS_H
#define C_SYSTEM_STATUS_H
//-----------------------------------------
//			C_SYSTEM_status.h 
//   Communication with Main Thread and Real Time Thread
//-----------------------------------------
#include "T_SYSTEM_control_0.h"
#include "T_SYSTEM_control_1.h"
#include "C_GUI_Status.h"
//-----------------------------------------
//		MISC. parameters
//-----------------------------------------
#define GOOD						0
#define FAULT						1
//-----------------------------------------
//		Enum:		E_MONITOR_OPERATION_MODE
//	
//		Changes by:
//				Haim Otachi 04/01/2016:  Add structures from ARC1_Technician.h
//-----------------------------------------
typedef enum
{
	OPERATION_OFF = 0,
	OPERATION_WORK,
	OPERATION_SNAPSHOT,
	OPERATION_RECORDING
}	E_MONITOR_OPERATION_MODE;
//-----------------------------------------
//		ref class:   C_SYSTEM_status
//-----------------------------------------
public ref class C_SYSTEM_status
{
	#pragma region Private Fields
	//-----------------------------------------
	//			Public Fields
	//-----------------------------------------
	public:
	T_SYSTEM_control_0*				system_control_0;
	T_SYSTEM_control_1*				system_control_1;
	T_SNAPSHOT_descriptor*			SNAPSHOT_descriptor;

	int64_t							Ethernet_speed;
	E_ETEHRNET_STATUS				Ethernet_link_status;
	int								Ethernet_message_status;

	int								Ethernet_server_status;
	int								Ethernet_server_on;
	int								Ethernet_server_connected_to_client;

	E_MONITOR_OPERATION_MODE		Monitor_Operation_mode;
	bool							Monitor_Operation_Recording;
	int								Operation_retry_count;

	double							correction1I;
	
	C_GUI_Status^					GUI_Status;
	//-------------------------------------
	//		Message fields for output
	//-------------------------------------
	System::String^					Message;
	#pragma endregion

	#pragma region Constructor / Destructor
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	public:			C_SYSTEM_status();
	//-------------------------------------
	//			Destructor
	//-------------------------------------
	public:			~C_SYSTEM_status();
	#pragma endregion

	#pragma region Methods
	//-------------------------------------
	//			Public Methods
	//-------------------------------------
	public:
	void				Initialize(C_GUI_Status^  GUI_Status_Other);
	System::String^		Update_Rx_Correction_I();
	
	char**				System_Health_status();
	void				Update_SNAPSHOT_Descriptor();
	

	void                Flash_Display_Fields_To_System_Control();
	void				Flash_System_Shadow_To_Display_Fields();
	void				Reset_Rx_Correction();

	//bool				Save_Snapshot_Samples_To_File(char* file_name);
	//-------------------------------------
	//			Private Methods
	//-------------------------------------
	private:
	uint32_t			Calc_Decimated_Range_Samples();
	#pragma endregion
};
#endif