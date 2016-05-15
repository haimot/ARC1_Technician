#include "C_SYSTEM_status.h"
#include "C_DSP_Communication.h"
#include "T_SNAPSHOT_descriptor.h"
#include <string.h>
#include <stdlib.h>
//-----------------------------------------
//		MISC. parameters
//-----------------------------------------
#define GOOD							0
#define FAULT							1
//-----------------------------------------
//		FILES & FOLDERS
//		Changes by:
//			Haim Otachi 11/01/2016:  Add 'define' from ARC1_Technician.h
//-----------------------------------------
#define	SNAPSHOT_SAMPLES_FILE			"snapshot_samples.bin"

using namespace DSP_Communication;

#pragma region Constructor / Destructor
// --------------------------------------------------
//  C_SYSTEM_status - Default Constructor
//  Haim Otachi     28/12/2015
// 	Description:	the function initialize the: 'system_control_0' 
//					structs with simple 'malloc'
// 	Reference: 
//  Return Value:	
// --------------------------------------------------
C_SYSTEM_status::C_SYSTEM_status()
{
	//-----------------------------------------
	//				Malloc 
	//-----------------------------------------
	system_control_0 = (T_SYSTEM_control_0*)malloc(sizeof(T_SYSTEM_control_0));
	system_control_1 = (T_SYSTEM_control_1*)malloc(sizeof(T_SYSTEM_control_1));
	SNAPSHOT_descriptor = (T_SNAPSHOT_descriptor*)malloc(sizeof(T_SNAPSHOT_descriptor));

	correction1I = 0;

	memset(system_control_0, 0, sizeof(T_SYSTEM_control_0));
	memset(system_control_1, 0, sizeof(T_SYSTEM_control_1));

	Ethernet_link_status = ETHERNET_OFF;
	Ethernet_message_status = FAULT;

	Monitor_Operation_Recording = false;
	Monitor_Operation_mode = OPERATION_OFF;

	Operation_retry_count = 0;

	GUI_Status = gcnew C_GUI_Status;
}
// --------------------------------------------------
//  C_SYSTEM_status - Destructor
//  Haim Otachi     28/12/2015
// 	Description:	the function delete the: 'system_control_0' 
//					structs with delete function
// 	Reference: 
//  Return Value:	
// --------------------------------------------------
C_SYSTEM_status::~C_SYSTEM_status()
{
	//-------------------------------------
	//	  delete the 'system_control_0' object
	//-------------------------------------
	if (system_control_0 != NULL)
	{
		free(system_control_0);
		system_control_0 = NULL;
	}
	//-------------------------------------
	//	  delete the 'system_control' object
	//-------------------------------------
	if (system_control_1 != NULL)
	{
		free(system_control_1);
		system_control_1 = NULL;
	}
	//-------------------------------------
	//	  delete the 'SNAPSHOT_descriptor' object
	//-------------------------------------
	if (SNAPSHOT_descriptor != NULL)
	{
		free(SNAPSHOT_descriptor);
		SNAPSHOT_descriptor = NULL;
	}
}
#pragma endregion

#pragma region Methods
// --------------------------------------------------
//  Initialize
//  Haim Otachi		2/1/2016
// 	description:	The function initialize the 'GUI_Status' with the real data from the GUI
// 	reference:
//	input value:	
//  return value:	
// --------------------------------------------------
void C_SYSTEM_status::Initialize(C_GUI_Status^ GUI_Status_Other)
{
	//-------------------------------------
	//	  we update the 'GUI_Status' object with real data
	//-------------------------------------
	GUI_Status = GUI_Status_Other;
}

System::String^ C_SYSTEM_status::Update_Rx_Correction_I()
{
	if (correction1I != system_control_0->SYSTEM_control_shadow.Rx_correction[0].I)
	{
		correction1I = system_control_0->SYSTEM_control_shadow.Rx_correction[0].I;
		return gcnew System::String("Calibration Coefficients Were Updated.");
	}
	return  gcnew System::String("Calibration Coefficients unchanged.");
}


// --------------------------------------------------
//  system_health_status
//  eran rebenstock					13/7/2015
//  Updated by Haim Otachi at		2/1/2016
// 	description:	check if the system is up
// 	reference:
//	input value:	
//  return value:	
// --------------------------------------------------
char** C_SYSTEM_status::System_Health_status()
{
	//TODO: Move this function to the 'Real Time Thread' class
	return 0;
}
// --------------------------------------------------
//  Calc_Decimated_Range_Samples
//  Haim Otachi			2/1/2016
// 	description:		???
// 	reference:
//	input value:	
//  return value:	
// --------------------------------------------------
uint32_t C_SYSTEM_status::Calc_Decimated_Range_Samples()
{
	//-------------------------------------
	//			Find the 'RANGE_samples'
	//-------------------------------------
	uint32_t RANGE_samples = system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples;
	//-------------------------------------
	//			Find the 'Range_decimation'
	//-------------------------------------
	uint32_t Range_decimation = system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation;
	//-------------------------------------
	//			Calculate the 'decimated_range_samples'
	//-------------------------------------
	uint32_t decimated_range_samples = RANGE_samples / Range_decimation;
	//-------------------------------------
	//			return the 'decimated_range_samples'
	//-------------------------------------
	return decimated_range_samples;
}
// --------------------------------------------------
//  Update_SNAPSHOT_Descriptor
//  Haim Otachi			2/1/2016
// 	description:		???
// 	reference:
//	input value:	
//  return value:	
// --------------------------------------------------
void C_SYSTEM_status::Update_SNAPSHOT_Descriptor()
{
	uint32_t					buffer_size;
	uint32_t					decimated_range_samples;
	//----------------------------------------------
	//  Calculate the 'decimated_range_samples'
	//----------------------------------------------
	decimated_range_samples = Calc_Decimated_Range_Samples();
	//----------------------------------------------
	//  Take the SNAPSHOT type of 'SNAPSHOT_descriptor'
	//----------------------------------------------
	SNAPSHOT_descriptor->SNAPSHOT_type = GUI_Status->disaplay_fields->DEBUG_fields.SNAPSHOT_type;
	//----------------------------------------------
	//  calculate the buffer_size relative to SNAPSHOT type of 'SNAPSHOT_descriptor'
	//----------------------------------------------
	switch (SNAPSHOT_descriptor->SNAPSHOT_type)
	{
		case SNAPSHOT_CPI:
		{
			buffer_size = system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.Buffer_length * system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers;
			break;
		}
		case SNAPSHOT_PRE_FFT:
		{
			buffer_size = decimated_range_samples * system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers;
			break;
		}
		case SNAPSHOT_RDM:
		{
			buffer_size = decimated_range_samples * system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers;
			break;
		}
	}
	//----------------------------------------------
	//  Update the 'SNAPSHOT_number_of_samples' that belongs to 'SNAPSHOT_descriptor'
	//----------------------------------------------
	SNAPSHOT_descriptor->SNAPSHOT_number_of_samples = buffer_size * 8;
}
// --------------------------------------------------
//  Flash_Display_Fields_To_System_Control
//  Alon Slapak					1/4/2015
//  changed by Haim Otachi: 	2/1/2016
//								???
// 	Description:				Update SYSTEM_control (flash values) from screen (from the GUI)
// 	Reference: 
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
void C_SYSTEM_status::Flash_Display_Fields_To_System_Control()
{
	system_control_1->System_ID					= GUI_Status->disaplay_fields->FLASH_fields.System_ID;
	system_control_1->Enable_RF2_Support		= GUI_Status->disaplay_fields->FLASH_fields.Enable_RF2_Support;

	system_control_1->TxRx_control_WORK			= GUI_Status->TxRx_Control[0];
	system_control_1->TxRx_control_PROBE		= GUI_Status->TxRx_Control[1];
	system_control_1->TxRx_control_CALIBRATOR	= GUI_Status->TxRx_Control[2];
	
	system_control_1->PROBE_test				= GUI_Status->disaplay_fields->FLASH_fields.PROBE_test;
	system_control_1->TGT_calibrate				= GUI_Status->disaplay_fields->FLASH_fields.TGT_calibrate;	
	system_control_1->DET_algorithms			= GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms;
	//-------------------------------------------------------------------
	//		These are not updated from the screen but from the ARD's flash
	//-------------------------------------------------------------------
	system_control_1->Rx_correction[0] = system_control_0->SYSTEM_control_shadow.Rx_correction[0];
	system_control_1->Rx_correction[1] = system_control_0->SYSTEM_control_shadow.Rx_correction[1];
	system_control_1->Rx_correction[2] = system_control_0->SYSTEM_control_shadow.Rx_correction[2];
	system_control_1->Rx_correction[3] = system_control_0->SYSTEM_control_shadow.Rx_correction[3];

	system_control_1->Calibrator_correction[0] = system_control_0->SYSTEM_control_shadow.Calibrator_correction[0];
	system_control_1->Calibrator_correction[1] = system_control_0->SYSTEM_control_shadow.Calibrator_correction[1];
	system_control_1->Calibrator_correction[2] = system_control_0->SYSTEM_control_shadow.Calibrator_correction[2];
	system_control_1->Calibrator_correction[3] = system_control_0->SYSTEM_control_shadow.Calibrator_correction[3];

	// Eran 19.11.15 ZP
	for (int i = 0; i < 14; ++i)
	{
		system_control_1->DC_claculation[i][0] = system_control_0->SYSTEM_control_shadow.DC_claculation[i][0];
		system_control_1->DC_claculation[i][1] = system_control_0->SYSTEM_control_shadow.DC_claculation[i][1];
		system_control_1->DC_claculation[i][2] = system_control_0->SYSTEM_control_shadow.DC_claculation[i][2];
		system_control_1->DC_claculation[i][3] = system_control_0->SYSTEM_control_shadow.DC_claculation[i][3];
	}
}
// --------------------------------------------------
//  Flash_System_Shadow_To_Display_Fields
//  Haim Otachi		2/1/2016
// 	Description:	Update Flash_fields from SYSTEM_control shadow
// 	Reference: 
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
void C_SYSTEM_status::Flash_System_Shadow_To_Display_Fields()
{
	GUI_Status->disaplay_fields->FLASH_fields.System_ID = system_control_0->SYSTEM_control_shadow.System_ID;
	
	GUI_Status->disaplay_fields->FLASH_fields.TxRx_control[0] = system_control_0->SYSTEM_control_shadow.TxRx_control_WORK;
	GUI_Status->disaplay_fields->FLASH_fields.TxRx_control[1] = system_control_0->SYSTEM_control_shadow.TxRx_control_PROBE;
	GUI_Status->disaplay_fields->FLASH_fields.TxRx_control[2] = system_control_0->SYSTEM_control_shadow.TxRx_control_CALIBRATOR;

	GUI_Status->disaplay_fields->FLASH_fields.PROBE_test	  =	system_control_0->SYSTEM_control_shadow.PROBE_test;
	GUI_Status->disaplay_fields->FLASH_fields.TGT_calibrate	  =	system_control_0->SYSTEM_control_shadow.TGT_calibrate;
	GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms  =	system_control_0->SYSTEM_control_shadow.DET_algorithms;

	system_control_1->PROBE_test = GUI_Status->disaplay_fields->FLASH_fields.PROBE_test;
	system_control_1->TGT_calibrate = GUI_Status->disaplay_fields->FLASH_fields.TGT_calibrate;
	system_control_1->DET_algorithms = GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms;
}
// --------------------------------------------------
//  Reset_Rx_Correction
//  Haim Otachi		2/1/2016
// 	Description:	Reset Rx correction factors to 1 + 0i = complex 1
// 	Reference: 
//	Input Value:	
//  Return Value:	
// --------------------------------------------------
void C_SYSTEM_status::Reset_Rx_Correction()
{
	system_control_1->Rx_correction[0].I = 1;
	system_control_1->Rx_correction[0].Q = 0;
	system_control_1->Rx_correction[1].I = 1;
	system_control_1->Rx_correction[1].Q = 0;
	system_control_1->Rx_correction[2].I = 1;
	system_control_1->Rx_correction[2].Q = 0;
	system_control_1->Rx_correction[3].I = 1;
	system_control_1->Rx_correction[3].Q = 0;
}
#pragma endregion

#pragma region Private Methods
//bool C_SYSTEM_status::Save_Snapshot_Samples_To_File(char* file_name){}
#pragma endregion