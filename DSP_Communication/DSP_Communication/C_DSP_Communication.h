#ifndef C_DSP_COMMUNICATION_H
#define C_DSP_COMMUNICATION_H
//-----------------------------------------
//		DSP_Communication.h 
//     Communication with DSP
//  Update by Haim Otachi   25/11/2015
//-----------------------------------------
#include "C_Ethernet_TCP_Client.h"
#include "T_BUL_config.h"
#include "T_SNAPSHOT_descriptor.h"
//-----------------------------------------
//		Enum of:	PC command
//-----------------------------------------
typedef enum
{
	PC_COMMAND_IDLE = 0,						// Do noting
	PC_COMMAND_START_DATA_RECORDING,			// Enable Data_recording_flag
	PC_COMMAND_STOP_DATA_RECORDING, 			// Disable Data_recording_flag
	PC_COMMAND_SYSTEM_CONTROL_TO_FLASH, 		// write SYSTEM_control from MEM to FLASH
	PC_COMMAND_SYSTEM_CONTROL_FROM_FLASH,		// read SYSTEM_control from FLASH to MEM
	PC_COMMAND_SYSTEM_CONTROL_FROM_PC,			// read SYSTEM_control from PC to MEM
	PC_COMMAND_BUL,								// write boot uploader (BUL) to flash
	PC_COMMAND_START_WORK_CIRC, 				// OMR mode <-- MODE_SAVE_CAF
	PC_COMMAND_START_WORK_HV, 					// OMR mode <-- MODE_START_WORK_HV
	PC_COMMAND_STOP_WORK, 						// OMR mode <-- MODE_START_WORK_CIRC
	PC_COMMAND_CALIBRATE_PROBE,					// Calibrate with probe
	PC_COMMAND_CALIBRATE_CALIBRATOR,			// Calibrate with calibrator
	PC_COMMAND_SNAPSHOT,						// operate the MODE_SAVE_SNAPSHOT
	PC_COMMAND_RESET_SENSOR, 					// Reset the Sensor piggy
	PC_COMMAND_RESET_ARC, 						// Reset the DSPs & MCU

	SEND_SYSTEM_CONTROL, 						// Send the SYSTEM_control from PC to OMR memory
	SEND_BUL_IMAGE, 							// Send BUL_image from PC and write it to flash

	READ_SYSTEM_STATUS, 						// Read SYSTEM_status to PC
	READ_SNAPSHOT, 								// Read Snapshot buffer to PC: I/Q from 4 channels, double
	READ_OBSTACLES_MAP							// Read obstacles Map to PC
} E_PC_command;
//-----------------------------------------
//		namespace:	DSP_Communication
//-----------------------------------------
namespace DSP_Communication
{
	public ref class C_DSP_Communication
	{
		//-----------------------------------------
		//			Private Fields
		//-----------------------------------------	
		private:	C_Ethernet_TCP_Client	Ethernet_TCP_Client;
		//-----------------------------------------
		//			Public Fields
		//-----------------------------------------
		public:
		volatile	char*	client_recording_status;
		volatile	char*	client_messaging_status;
		volatile	char*	client_buffer_pointer;
		volatile	int		client_buffer_size;
		//-----------------------------------------
		//			Constructor
		//-----------------------------------------
		public:		C_DSP_Communication();
		//-----------------------------------------
		//			Destructor
		//-----------------------------------------
		public:		~C_DSP_Communication();
		//-----------------------------------------
		//			Methods
		//-----------------------------------------
		public:
		int			DSP_connect();
		int			DSP_disconnect();

		int			DSP_command(int command_to_DSP);
		int			DSP_send(int command_to_DSP, char* pbuffer, int size);
		int			DSP_receive(int command_to_DSP, char* pbuffer, int size);

		int			DSP_send_BUL_image(char* fileName, T_BUL_config* pBUL_config);
		int			DSP_snapshot_command(T_SNAPSHOT_descriptor* SNAPSHOT_descriptor);
		
		void		DSP_read_SYSTEM_status_task();
		int			DSP_read_SYSTEM_status(char* p_buffer, int buffer_size);
	};
}
#endif
