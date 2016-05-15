//------------------------------------------------
//	Technician interface
//	ALon Slapak	3/10/2014
//	Reference:
//		http://stackoverflow.com/questions/11130915/windows-form-clr-application-in-visual-studio-2012-rc
//		http://mcn-www.jwu.ac.jp/~yokamoto/openwww/vsg/VCpp2012FormApp/
//----------------------------------------------------
#include "MyForm.h"
#include "Recovery_Flight.h"
#include "Loading_Page.h"
#include "T_Trajectories.h"
#include <iomanip>
#include <math.h>

#pragma region define controls
//-----------------------------------------------------------
//			TxRx_control	controls
//-----------------------------------------------------------
#define			PROFILE_AD9910A							1
#define			PROFILE_AD9910B							2

#define			CHIP_LENGTH_AD9910A						3
#define			CHIP_LENGTH_AD9910B						4

#define			SELECT_TX1								5
#define			SELECT_TX2								6
#define			SELECT_TX3								7

#define         SELECT_PROBE							8
#define         IO_UPDATE_RATE							9

#define         TX_1_ON									10	
#define         TX_2_ON									11
#define         TX_3_ON									12	

#define         E_PROBE_ON								13	
#define         E_TX_LO_TR								14
#define			E_ANT_SAMPLE_SELECT						15

#define         ATTN_TX_1								16
#define         ATTN_TX_2								17
#define         ATTN_TX_3								18
#define         ATTN_RX_1								19
#define         ATTN_RX_2								20
#define         ATTN_RX_3								21
#define         ATTN_RX_4								22

#define			AD9910_SET_AUX_DAC_A					23
#define			AD9910_SET_AUX_DAC_B					24

#define			BUFFER_LENGTH							25
#define			FIFO_LENGTH								26
#define			E_IO_UPDATE_ON							27
//-----------------------------------------------------------
//			DET_algorithms	controls
//-----------------------------------------------------------
#define			OFFSET_SAMPLES							28
#define			RANGE_SAMPLES							29

#define			TARGET_DETECTION_1ST_THRESHOLD			30
#define			TARGET_DETECTION_2ST_THRESHOLD			31

#define			Range_DECIMATION						32
#define			AGC_THRESHOLD							33
//-----------------------------------------------------------
//			TGT_calibrate	controls
//-----------------------------------------------------------
#define			PROBE_START_SAMPLE						34
#define			PROBE_END_SAMPLE						35

#define			CALIBRATOR_START_SAMPLE					36
#define			CALIBRATOR_END_SAMPLE					37
//-----------------------------------------------------------
//			PROBE_test	controls
//-----------------------------------------------------------
#define			PROBE_TEST_PROFILE						38
#define			PROBE_TEST_GAIN							39
//-----------------------------------------------------------
//			TxRx_MODE	controls
//-----------------------------------------------------------
#define			TXRX_MODE								40
//-----------------------------------------------------------
//			SYSTEM_ID	controls
//-----------------------------------------------------------
#define			SYSTEM_ID								41

#define         RF2_Support								42
//-----------------------------------------------------------
//			MAINTENANCE	controls
//-----------------------------------------------------------
#define			RESET_AFTER_BOOT_UPLOAD					43
#define			OUTFILE_DIRECTORY_OMR					44
#define			OUTFILE_DIRECTORY_DET					45
#define			OUTFILE_DIRECTORY_CHAB					46
#define			OUTFILE_DIRECTORY_MCU					47
#define			OUTFILE_DIRECTORY_RF_MCU				48
#pragma endregion

using namespace System::Net::NetworkInformation;
using namespace System::Windows::Media::Media3D;
using namespace System::Threading;

namespace ARC1_Technician
{
	#pragma region Constructor/Destructor 
	// --------------------------------------------------
	//  MyForm
	//  Alon Slapak 3/10/2014
	// 	Description:	Constructor:
	//						1. init controls
	//						2. Malloc buffers
	//						3. Read initial values from files
	//						4. 
	// 	Reference: 
	//	Input Value:	
	//  Return Value: 
	// --------------------------------------------------
	MyForm::MyForm()
	{
		//-----------------------------------------
		//	Initialize componenets - Wizard functino in the .h file
		//-----------------------------------------
		InitializeComponent();
		//-----------------------------------------
		//	Malloc 
		//-----------------------------------------	
		BUL_config = (T_BUL_config*)malloc(sizeof(T_BUL_config));	
		TARGETS_data = (T_TARGETS_data*)malloc(sizeof(T_TARGETS_data));
		data_recording_file_handle = new(fstream);
		//-----------------------------------------
		//	Initialize parameters
		//-----------------------------------------
		GUI_Status = gcnew C_GUI_Status;
		System_Status = gcnew C_SYSTEM_status;
		System_Status->Initialize(GUI_Status);
		//-----------------------------------------
		//	Read MATLAB scripts
		//-----------------------------------------
		fstream file_handle;
		char  fileName[MAX_STRING_LENGTH];
		char  line[MAX_STRING_LENGTH];
		int counter = 0;
		sprintf_s(fileName, "%s\\%s", MATLAB_SCRIPTS_PATH, MATLAB_SCRIPTS_NAME);
		file_handle.open(fileName, ios::in);
		//-----------------------------------------
		//			check the 'pwd' - ?
		//-----------------------------------------
		if (file_handle.fail())
		{
			this->B_MATLAB_script->Items->Add(gcnew String("No MATLAB scripts..."));
		}
		else
		{
			while (file_handle.getline(line, MAX_STRING_LENGTH))
			{
				this->B_MATLAB_script->Items->Add(gcnew String(line));
				counter++;
			}
			if (counter == 0)
			{
				this->B_MATLAB_script->Items->Add(gcnew String("No MATLAB scripts..."));
			}
		}
		file_handle.close();
		//-----------------------------------------
		//	Initialize the real time thread and return appropriate message of 'Matlab_engine'
		//-----------------------------------------
		My_Message(real_time_thread.Initialize(System_Status));
		//---------------------------------------------- -
		//	Put single point on screens for visualization
		//-----------------------------------------------
		B_RADAR_PLOT->Series["Wires"]->Points->AddXY(0, 0);

		B_SCOPE_H_LEFT->Series["Single1"]->Points->AddXY(0, 0);
		B_SCOPE_V_LEFT->Series["Single1"]->Points->AddXY(0, 0);

		B_SCOPE_H_RIGHT->Series["Single1"]->Points->AddXY(0, 0);
		B_SCOPE_V_RIGHT->Series["Single1"]->Points->AddXY(0, 0);

		B_PROBE_TEST_PLOT->Series["LH_I"]->Points->AddXY(0, 0);
		B_PROBE_TEST_PLOT->Series["LH_Q"]->Points->AddXY(0, 0);
		B_PROBE_TEST_PLOT->Series["LV_I"]->Points->AddXY(0, 0);
		B_PROBE_TEST_PLOT->Series["LV_Q"]->Points->AddXY(0, 0);
		B_PROBE_TEST_PLOT->Series["RH_I"]->Points->AddXY(0, 0);
		B_PROBE_TEST_PLOT->Series["RH_Q"]->Points->AddXY(0, 0);
		B_PROBE_TEST_PLOT->Series["RV_I"]->Points->AddXY(0, 0);
		B_PROBE_TEST_PLOT->Series["RV_Q"]->Points->AddXY(0, 0);


		PB_MAP_chart->Series["targets_pylons"]->Points->AddXY(5, 10);

		// Tempature valid init
		Temp_valid = 0;
		target_updated = false;
		//-----------------------------------------------
		//	Initialize the CHAB BUL to Deafult value
		//-----------------------------------------------
		CHAB_BUL_Selector->SelectedIndex = 0;
		//-----------------------------------------------
		//					Timer
		//-----------------------------------------------
		this->timer_DSP_messages->Interval = TIMER_INTERVAL;
		this->timer_DSP_messages->Enabled = true;
		//-----------------------------------------
		//	Read INITIAL DATA from file
		//-----------------------------------------
		if (GUI_Status->Read_Data_From_File() == true)
		{
			//-----------------------------------------
			//	Initialize the Radar Viewer
			//-----------------------------------------
			Radar_Viewer.Initialize(B_MAP_PANEL, gcnew PictureBox,*GUI_Status);
		}
		//-----------------------------------------------
		//	Put data in TABS
		//-----------------------------------------------
		B_tabControl->SelectedIndex = GUI_Status->disaplay_fields->TAB_index;
		

		Update_Work_Tab_Controls();
		Update_Debug_Tab_Controls();
		Update_Maintenance_Tab_Controls();
		Flash_Display_fields_to_Screen();
	}
	// --------------------------------------------------
	//  ~MyForm()
	//  Alon Slapak 3/10/2014
	// 	Description:	Destructor: Clean up any resources being used.
	// 	Reference: 
	//	Input Value:	
	//  Return Value: 
	// --------------------------------------------------
	MyForm::~MyForm()
	{
		//-----------------------------------------
		//	Clean up
		//-----------------------------------------
		if (components)
		{
			delete components;
		}

		if (BUL_config != NULL)
		{
			free(BUL_config);
			BUL_config = NULL;
		}
		
		if (data_recording_file_handle != NULL)
		{
			free(data_recording_file_handle);
			data_recording_file_handle = NULL;
		}
		//----------------------------------
		// Matlab engine
		//----------------------------------
		if (Matlab_engine != NULL)
		{
			engClose(Matlab_engine);
			Matlab_engine = NULL;
		}
	}
	#pragma endregion

	#pragma region GUI Methods
	//-----------------------------------------------------------
	//			DEBUG controls
	//-----------------------------------------------------------
	void MyForm::B_SNAPSHOT_TYPE_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Debug_SNAPSHOT_Type((E_SNAPSHOT_type)B_SNAPSHOT_TYPE->SelectedIndex);
	}
	void MyForm::B_MATLAB_script_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Debug_MATLAB_Script_Index(B_MATLAB_script->SelectedIndex);
		GUI_Status->Update_Debug_MATLAB_Script(B_MATLAB_script->Text);

	}
	void MyForm::B_LOG_FOLDER_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Debug_Log_Folder(B_LOG_FOLDER->Text);
	}
	//-----------------------------------------------------------
	//			FLASH controls
	//-----------------------------------------------------------
	#pragma region	Functions relative to  TxRx_control  array
	void MyForm::F_Profile_AD9910A_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(PROFILE_AD9910A, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_Profile_AD9910A->Value));
	}
	void MyForm::F_Profile_AD9910B_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(PROFILE_AD9910B, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_Profile_AD9910B->Value));
	}

	void MyForm::F_chip_length_AD9910A_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(CHIP_LENGTH_AD9910A, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_chip_length_AD9910A->Value));
	}
	void MyForm::F_chip_length_AD9910B_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(CHIP_LENGTH_AD9910B, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_chip_length_AD9910B->Value));
	}

	void MyForm::F_IF_SELECT_TX1_A_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(SELECT_TX1, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_IF_SELECT_TX1_B->Checked));
	}
	void MyForm::F_IF_SELECT_TX2_A_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(SELECT_TX2, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_IF_SELECT_TX2_B->Checked));
	}
	void MyForm::F_IF_SELECT_TX3_A_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(SELECT_TX3, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_IF_SELECT_TX3_B->Checked));	
	}

	void MyForm::F_IF_SELECT_PROBE_A_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(SELECT_PROBE, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_IF_SELECT_PROBE_B->Checked));
	}
	void MyForm::F_IO_UPDATE_rate_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(IO_UPDATE_RATE, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_IO_UPDATE_rate->Value * 1000));
		//--------------------------------------------------------
		//			Updating the batch duration
		//--------------------------------------------------------		
		F_BATCH_DURATION->Text = GUI_Status->Calc_Batch_Duartion().ToString("N2");
	}

	void MyForm::F_TX1_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(TX_1_ON, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_TX1_ON->Checked));
	}
	void MyForm::F_TX2_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(TX_2_ON, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_TX2_ON->Checked));
	}
	void MyForm::F_TX3_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(TX_3_ON, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_TX3_ON->Checked));
	}

	void MyForm::F_PROBE_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(E_PROBE_ON, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_PROBE_ON->Checked));
	}
	void MyForm::F_TX_LO_TR_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(E_TX_LO_TR, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_TX_LO_TR->Checked));
	}
	void MyForm::F_PROBE_SELECT_ANT_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(E_ANT_SAMPLE_SELECT, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_PROBE_SELECT_ANT->Checked));
	}

	void MyForm::F_ATTN_TX1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(ATTN_TX_1, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_ATTN_TX1->Value));
	}
	void MyForm::F_ATTN_TX2_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(ATTN_TX_2, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_ATTN_TX2->Value));
	}
	void MyForm::F_ATTN_TX3_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(ATTN_TX_3, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_ATTN_TX3->Value));
	}
	void MyForm::F_ATTN_RX1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(ATTN_RX_1, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_ATTN_RX1->Value));
	}
	void MyForm::F_ATTN_RX2_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(ATTN_RX_2, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_ATTN_RX2->Value));
	}
	void MyForm::F_ATTN_RX3_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(ATTN_RX_3, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_ATTN_RX3->Value));
	}
	void MyForm::F_ATTN_RX4_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(ATTN_RX_4, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_ATTN_RX4->Value));
	}

	void MyForm::F_AD9910_Set_aux_dac_A_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(AD9910_SET_AUX_DAC_A, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_AD9910_Set_aux_dac_A->Value));
	}
	void MyForm::F_AD9910_Set_aux_dac_B_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(AD9910_SET_AUX_DAC_B, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_AD9910_Set_aux_dac_B->Value));
	}

	void MyForm::F_Buffer_length_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(BUFFER_LENGTH, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_Buffer_length->Value));
	}
	void MyForm::F_FIFO_length_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(FIFO_LENGTH, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_FIFO_length->Value));
	}
	void MyForm::F_IO_UPDATE_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(E_IO_UPDATE_ON, F_TxRx_control_MODE->SelectedIndex, System::Convert::ToInt32(F_IO_UPDATE_ON->Checked));
	}
	#pragma endregion

	#pragma region	Functions relative to  DET_algorithms
	// --------------------------------------------------
	//  F_Number_of_buffers_ValueChanged  
	//  Haim Otachi    30/12/2015
	// 	Description:   The function update the system with the data (new number of buffers) and return this value
	// 	Reference: 
	//  Input value:
	//  Return Value:	new number of buffers
	// --------------------------------------------------
	void MyForm::F_Number_of_buffers_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//--------------------------------------------------------
		//			update the system with the data (new number of buffers) and return this value
		//--------------------------------------------------------		
		F_Number_of_buffers->Value = GUI_Status->Update_Number_Of_Buffers(System::Convert::ToInt32(F_Number_of_buffers->Value));
		//--------------------------------------------------------
		//			Updating the batch duration
		//--------------------------------------------------------		
		F_BATCH_DURATION->Text = GUI_Status->Calc_Batch_Duartion().ToString("N2");
	}
	void MyForm::F_AGC_threshold_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(AGC_THRESHOLD, 0, System::Convert::ToInt16(F_AGC_threshold->Value));
	}

	void MyForm::F_OFFSET_sample_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(OFFSET_SAMPLES, 0, System::Convert::ToInt32(F_OFFSET_sample->Value));
	}
	void MyForm::F_RANGE_meter_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(RANGE_SAMPLES, 0, System::Convert::ToInt32(F_RANGE_meter->Value / METERS_PER_SAMPLE));
	}

	void MyForm::Target_detection_1st_threshold_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(TARGET_DETECTION_1ST_THRESHOLD, 0, System::Convert::ToInt32(F_Target_detection_1st_threshold->Value));
	}
	void MyForm::Target_detection_2nd_threshold_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(TARGET_DETECTION_2ST_THRESHOLD, 0, System::Convert::ToInt32(F_Target_detection_2nd_threshold->Value));
	}
	// --------------------------------------------------
	//  F_MAX_VELOCITY_ValueChanged  
	//  Haim Otachi    30/12/2015
	// 	Description:   The function update the system with the data (new velocity buffers) and return this value
	// 	Reference: 
	//  Input value:
	//  Return Value:	new velocity buffers
	// --------------------------------------------------
	void MyForm::F_MAX_VELOCITY_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//--------------------------------------------------------
		//			Updating number of buffers
		//--------------------------------------------------------
		B_MAX_VELOCITY_MS->Text = GUI_Status->Update_Velocity_Buffers(System::Convert::ToInt32(F_MAX_VELOCITY->Value)).ToString("N0");
	}
	void MyForm::F_RANGE_DECIMATION_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(Range_DECIMATION, 0, System::Convert::ToInt32(F_RANGE_DECIMATION->Value));
	}
	void MyForm::F_MINIMUM_RANGE_METER_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//GUI_Status->Update_Flash_Controls(MINIMUM_RANGE_METER, 0, System::Convert::ToInt32(F_MINIMUM_RANGE_METER->Value));
	}
	#pragma endregion

	#pragma region	Functions relative to  TGT_calibrate
	void MyForm::F_PROBE_CALIBRATE_TGT_START_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(PROBE_START_SAMPLE, 0, System::Convert::ToInt32(F_PROBE_CALIBRATE_TGT_START->Value));
	}
	void MyForm::F_PROBE_CALIBRATE_TGT_END_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(PROBE_END_SAMPLE, 0, System::Convert::ToInt32(F_PROBE_CALIBRATE_TGT_END->Value));
	}
	void MyForm::F_CALIBRATOR_TGT_START_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(CALIBRATOR_START_SAMPLE, 0, System::Convert::ToInt32(F_CALIBRATOR_TGT_START->Value));
	}
	void MyForm::F_CALIBRATOR_TGT_END_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(CALIBRATOR_END_SAMPLE, 0, System::Convert::ToInt32(F_CALIBRATOR_TGT_END->Value));
	}
	#pragma endregion
	
	#pragma region	Functions relative to  PROBE_test
	void MyForm::F_PROBE_TEST_profile_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(PROBE_TEST_PROFILE, 0, System::Convert::ToInt32(F_PROBE_TEST_profile->Value));
	}
	void MyForm::F_PROBE_TEST_gain_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(PROBE_TEST_GAIN, 0, System::Convert::ToInt32(F_PROBE_TEST_gain->Value));
	}
	#pragma endregion
	
	void MyForm::F_TxRx_control_MODE_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(TXRX_MODE, 0, (E_TxRx_MODE)F_TxRx_control_MODE->SelectedIndex);
		Flash_Display_fields_to_Screen();
	}
	void MyForm::F_SYSTEM_ID_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(SYSTEM_ID, 0, System::Convert::ToInt32(F_SYSTEM_ID->Value));
	}
	void MyForm::F_RF2_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Flash_Controls(RF2_Support, 0, System::Convert::ToInt32(F_RF2_ON->Checked));
		//-----------------------------------------------------------
		//			if 'RF2' button is pressed
		//-----------------------------------------------------------
		if (F_RF2_ON->Checked == true)
		{
			F_ATTN_TX1->Enabled = false;
			F_ATTN_TX2->Enabled = false;

			F_ATTN_RX1->Enabled = false;
			F_ATTN_RX2->Enabled = false;
			F_ATTN_RX3->Enabled = false;
			F_ATTN_RX4->Enabled = false;

			F_IF_SELECT_TX1_A->Enabled = false;
			F_IF_SELECT_TX1_B->Enabled = false;

			F_IF_SELECT_TX2_A->Enabled = false;
			F_IF_SELECT_TX2_B->Enabled = false;

			F_IF_SELECT_TX3_A->Enabled = false;
			F_IF_SELECT_TX3_B->Enabled = false;

			F_IF_SELECT_PROBE_A->Enabled = false;
			F_IF_SELECT_PROBE_B->Enabled = false;

			F_TX1_ON->Enabled = false;
			F_TX2_ON->Enabled = false;
			F_TX3_ON->Enabled = false;

			F_TX_LO_TR->Enabled = false;
		}
		else
		{
			F_ATTN_TX1->Enabled = true;
			F_ATTN_TX2->Enabled = true;
		
			F_ATTN_RX1->Enabled = true;
			F_ATTN_RX2->Enabled = true;
			F_ATTN_RX3->Enabled = true;
			F_ATTN_RX4->Enabled = true;

			F_IF_SELECT_TX1_A->Enabled = true;
			F_IF_SELECT_TX1_A->Checked = false;

			F_IF_SELECT_TX1_B->Enabled = true;
			F_IF_SELECT_TX1_B->Checked = false;

			F_IF_SELECT_TX2_A->Enabled = true;
			F_IF_SELECT_TX2_A->Checked = false;

			F_IF_SELECT_TX2_B->Enabled = true;
			F_IF_SELECT_TX2_B->Checked = false;

			F_IF_SELECT_TX3_A->Enabled = true;
			F_IF_SELECT_TX3_A->Checked = false;

			F_IF_SELECT_TX3_B->Enabled = true;
			F_IF_SELECT_TX3_B->Checked = false;

			F_IF_SELECT_PROBE_A->Enabled = true;
			F_IF_SELECT_PROBE_A->Checked = false;

			F_IF_SELECT_PROBE_B->Enabled = true;
			F_IF_SELECT_PROBE_B->Checked = false;

			F_TX1_ON->Enabled = true;
			F_TX1_ON->Checked = false;

			F_TX2_ON->Enabled = true;
			F_TX2_ON->Checked = false;

			F_TX3_ON->Enabled = true;
			F_TX3_ON->Checked = false;

			F_TX_LO_TR->Enabled = true;
			F_TX_LO_TR->Checked = false;
		}
	}
	//-----------------------------------------------------------
	//			MAINTENANCE controls
	//-----------------------------------------------------------
	void MyForm::B_ResetAfterUpload_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Maintenance_Controls(RESET_AFTER_BOOT_UPLOAD, B_ResetAfterUpload->Checked);
	}
	void MyForm::B_Out_OMR_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Maintenance_Controls(OUTFILE_DIRECTORY_OMR, B_Out_OMR->Text);
	}
	void MyForm::B_Out_DET_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Maintenance_Controls(OUTFILE_DIRECTORY_DET, B_Out_DET->Text);
	}
	void MyForm::B_Out_CHAB_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Maintenance_Controls(OUTFILE_DIRECTORY_CHAB, B_Out_CHAB->Text);
	}
	void MyForm::B_Out_MCU_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Maintenance_Controls(OUTFILE_DIRECTORY_MCU, B_Out_MCU->Text);
	}
	void MyForm::B_Out_RF_MCU_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status->Update_Maintenance_Controls(OUTFILE_DIRECTORY_RF_MCU, B_Out_RF_MCU->Text);
	}
	//-----------------------------------------------------------
	//			WORK controls
	//-----------------------------------------------------------
	void MyForm::B_RDM_H_R_MouseClick(System::Object^  sender, System::EventArgs^  e)
	{
		if (System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation != 0)
		{
			Point RDM_Point = B_RDM_H_R->PointToClient(Cursor->Position);
			double RDM_H_R_log_value = Radar_Viewer.Update_RDM(RDM_Point);
			toolTipHR->SetToolTip(B_RDM_H_R, RDM_H_R_log_value.ToString());
		}	
	}
	void MyForm::B_RDM_V_R_MouseClick(System::Object^  sender, System::EventArgs^  e)
	{
		if (System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation != 0)
		{
			Point RDM_Point = B_RDM_V_R->PointToClient(Cursor->Position);
			double RDM_V_R_log_value = Radar_Viewer.Update_RDM(RDM_Point);
			toolTipHR->SetToolTip(B_RDM_V_R, RDM_V_R_log_value.ToString());
		}
	}
	void MyForm::B_RDM_H_L_MouseClick(System::Object^  sender, System::EventArgs^  e)
	{
		if (System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation != 0)
		{
			Point RDM_Point = B_RDM_H_L->PointToClient(Cursor->Position);
			double RDM_H_L_log_value = Radar_Viewer.Update_RDM(RDM_Point);
			toolTipHR->SetToolTip(B_RDM_H_L, RDM_H_L_log_value.ToString());
		}
	}
	void MyForm::B_RDM_V_L_MouseClick(System::Object^  sender, System::EventArgs^  e)
	{
		if (System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation != 0)
		{
			Point RDM_Point = B_RDM_V_L->PointToClient(Cursor->Position);
			double RDM_V_L_log_value = Radar_Viewer.Update_RDM(RDM_Point);
			toolTipHR->SetToolTip(B_RDM_V_L, RDM_V_L_log_value.ToString());
		}
	}
	void MyForm::B_tabControl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//---------------------------------------------------
		//	DISAPLAY_fields->TAB_index = B_tabControl->SelectedIndex;
		//---------------------------------------------------
		switch (this->B_tabControl->SelectedIndex)
		{
			//-----------------------------------------
			//				WORK
			//-----------------------------------------
			case 0:		
			{
				Update_Work_Tab_Controls();
				break;
			}
			//-----------------------------------------
			//				DEBUG
			//-----------------------------------------
			case 3:							 
			{
				Update_Debug_Tab_Controls();
				break;
			}
			//-----------------------------------------
			//				Maintenance
			//-----------------------------------------
			case 5:	
			{
				Update_Maintenance_Tab_Controls();
				break;
			}
			//-----------------------------------------
			//				Flash
			//-----------------------------------------
			case 4:	
			{
				Flash_Display_fields_to_Screen();
				break;
			}
		}
	}
	void MyForm::B_AUX_VIEW_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {}
	//-----------------------------------------------------------
	//			LAB Experiments Tab control Function
	//-----------------------------------------------------------
	//
	//	Calibrator function
	//	
	void MyForm::B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE_Click(System::Object^  sender, System::EventArgs^  e)
	{
		char                              file_name[MAX_STRING_LENGTH];
		//-------------------------------------------
		//        Browse for protocol file
		//-------------------------------------------
		B_SelectLogFile_Of_Calibrator->DefaultExt			= "txt";
		B_SelectLogFile_Of_Calibrator->Filter				= "Text files (*.txt)|*.txt|All files (*.*)|*.*";

		B_SelectLogFile_Of_Calibrator->ShowDialog();
		marshal_context^ context							= gcnew marshal_context();
		sprintf_s(file_name, context->marshal_as<const char*>(B_SelectLogFile_Of_Calibrator->FileName));

		B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE->Text			= B_SelectLogFile_Of_Calibrator->FileName;
		B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE->Refresh();
		//-------------------------------------------
		//   We save the current protocol file name of the Calibrator
		//-------------------------------------------
		Lab_Calibrator.Protocol_file_name					= B_SelectLogFile_Of_Calibrator->FileName;
	}
	// --------------------------------------------------
	//  B_LAB_CALIBRATOR_START_Click
	//  Alon Slapak		16/3/2016
	//	Updated by Haim Otachi at 28/03/2016.
	// 	Description:	LAB: Calibrator Start.
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_LAB_CALIBRATOR_START_Click(System::Object^  sender, System::EventArgs^  e)
	{
		String^				 return_message;
		
		char                 temp_string[MAX_STRING_LENGTH];
		char                 Experiment_type[MAX_STRING_LENGTH];
		char                 reults_file_name[MAX_STRING_LENGTH];
		char                 Calibrator_COM_port[MAX_STRING_LENGTH];
		fstream              protocol_file;
		marshal_context^	 context = gcnew marshal_context();
		int                  Number_Of_Obstacles = 0;
		bool				 perform_SNR_command;

		int                  Doppler_start_Hz;
		int                  Doppler_stop_Hz;
		int                  Doppler_step_Hz;
		int                  Doppler_repeat;
		
		int					 SNR_dB;
		//----------------------------------------
		// We create the main tharead of us relative to the system with the name - 'Main_Thread'.
		// after this line the thread is running.
		//
		//-------------------------------------------
		//     Open the file to read the obstacles
		//-------------------------------------------		
		const char* protocol_file_name_of_calibrator = context->marshal_as<const char*>(Lab_Calibrator.Protocol_file_name);
		protocol_file.open(protocol_file_name_of_calibrator, std::ios_base::in);
		if (protocol_file.is_open())
		{
			//-------------------------------------------
			//     Read the experiment typ
			//-------------------------------------------
			protocol_file >> Experiment_type;
			//--------------------------------------------------
			//     Doppler experiment
			//--------------------------------------------------
			if (strcmp(Experiment_type, "Doppler") == 0)
			{
				//int                               Doppler_counter;
				//--------------------------------------------------
				//				load protocol
				//--------------------------------------------------
				protocol_file >> temp_string >> Calibrator_COM_port;
				protocol_file >> temp_string >> Doppler_start_Hz;
				protocol_file >> temp_string >> Doppler_stop_Hz;
				protocol_file >> temp_string >> Doppler_step_Hz;
				protocol_file >> temp_string >> Doppler_repeat;
				protocol_file >> temp_string >> SNR_dB;
				protocol_file >> temp_string >> reults_file_name;
				B_LAB_TOTAL_CYCLES->Text = Doppler_repeat.ToString();
				B_LAB_TOTAL_CYCLES->Refresh();
				//--------------------------------------------------
				//     Prepare array for results
				//--------------------------------------------------
				float**  results_array_doppler = (float**)malloc(Doppler_repeat * sizeof(float*));
				double** results_array_velocity = (double**)malloc(Doppler_repeat * sizeof(double*));
				int**  results_array_snr = (int**)malloc(Doppler_repeat * sizeof(int*));

				for (int k = 0; k < Doppler_repeat; k++)
				{
					results_array_doppler[k] = (float*)malloc((int)((Doppler_stop_Hz - Doppler_start_Hz) / Doppler_step_Hz + 1) * sizeof(float));
					results_array_velocity[k] = (double*)malloc((int)((Doppler_stop_Hz - Doppler_start_Hz) / Doppler_step_Hz + 1) * sizeof(double));
					results_array_snr[k] = (int*)malloc((int)((Doppler_stop_Hz - Doppler_start_Hz) / Doppler_step_Hz + 1) * sizeof(int));
				}
				//--------------------------------------------------
				//     Run protocol
				//--------------------------------------------------
				if (Lab_Calibrator.COM_port_Open(Calibrator_COM_port, return_message) == true)
				{
					//--------------------------------------------------
					//				Run the monitor
					//--------------------------------------------------
					G_START_WORK_CIRC_Click(sender, e);
					timer_DSP_messages_Tick(sender, e);
					//--------------------------------------------------
					//	return the appropriate message about the end of the experiment.
					//--------------------------------------------------
					System::Threading::Thread::Sleep(200);
					My_Message(gcnew String("The experiment began."));
					if (int::Parse(B_LAB_SNR->Text) != -1)
					{
						perform_SNR_command = Lab_Calibrator.Lab_Set_SNR(SNR_dB);
					}
					else
					{
						perform_SNR_command = true;
					}
					//--------------------------------------------------
					//				Run the test
					//--------------------------------------------------
					if (perform_SNR_command == true)
					{
						for (int test_counter = 0; test_counter < Doppler_repeat; test_counter++)
						{
							int temp_counter = test_counter + 1;
							B_LAB_CYCLE->Text = temp_counter.ToString();
							B_LAB_CYCLE->Refresh();
							for (int Doppler_Hz = Doppler_start_Hz, Doppler_counter = 0; Doppler_Hz <= Doppler_stop_Hz; Doppler_Hz += Doppler_step_Hz, ++Doppler_counter)
							{
								B_LAB_DOPPLER->Text = Doppler_Hz.ToString();
								B_LAB_DOPPLER->Refresh();

								B_LAB_SNR->Text = SNR_dB.ToString();
								B_LAB_SNR->Refresh();

								results_array_doppler[test_counter][Doppler_counter] = (float)2;   // !!! Replace 3 with Doppler estimation from radar !!!!
								if (Lab_Calibrator.Lab_Set_Doppler(Doppler_Hz) == true)
								{
									//--------------------------------------------------
									//     Get Estimated Doppler to array
									//--------------------------------------------------						
									target_updated = false;

									while (target_updated == false)
									{
										System::Threading::Thread::Sleep(500);
										timer_DSP_messages_Tick(sender, e);
										this->Refresh();
										timer_DSP_messages_Tick(sender, e);
										this->Refresh();
									}

									results_array_doppler[test_counter][Doppler_counter] = (float)Doppler_Hz;
									results_array_velocity[test_counter][Doppler_counter] = TARGETS_data->Targets_array[0].Radial_velocity;
									results_array_snr[test_counter][Doppler_counter] = (int)SNR_dB;
								}
							}
						}
					}
					Lab_Calibrator.COM_port_Close();
					//-------------------------------------------------
					//     Save array to file
					//-------------------------------------------------
					fstream results_file;
					results_file.open(reults_file_name, std::ios_base::out);
					if (results_file.is_open())
					{
						results_file << "The experimental results are:" << std::endl << std::endl;
						results_file << std::setw(20)  << "Calibrator Doppler [Hz]"
									 << std::setw(30) << "Radar Velocity [m/sec]"
									 << std::setw(26) << "SNR [dB]"
									 << std::endl;

						results_file << std::setfill('-') << std::setw(100) << '-' << std::setfill(' ') << std::endl;
						for (int k = 0; k < Doppler_repeat; k++)
						{
							for (int Doppler_Hz = Doppler_start_Hz, Doppler_counter = 0; Doppler_Hz <= Doppler_stop_Hz; Doppler_Hz += Doppler_step_Hz, Doppler_counter++)
							{
								results_file 
											 //
											 //			print 'Hz' to file 
											 //
											 << std::setw(10) << results_array_doppler[k][Doppler_counter]
											 //
											 //			print 'velocity' to file 
											 //
											 << std::setw(30) << results_array_velocity[k][Doppler_counter]
											 //
											 //			print 'Snr' to file 
											 //
											 << std::setw(35) << results_array_snr[k][Doppler_counter]
											 << std::endl;
							}
						}
					}
					results_file.close();
					//-------------------------------------------------
					//     Free array
					//-------------------------------------------------
					for (int k = 0; k < Doppler_repeat; k++)
					{
						free(results_array_doppler[k]);
						free(results_array_velocity[k]);
					}
					free(results_array_doppler);
					free(results_array_velocity);
				}
			}
		}
		//-------------------------------------------------
		//   return the appropriate message about the connection
		//-------------------------------------------------
		My_Message(gcnew String(return_message));
		target_updated = false;
		//--------------------------------------------------
		//   close the protocol file
		//--------------------------------------------------
		protocol_file.close();	
		//--------------------------------------------------
		//				Stop the monitor
		//--------------------------------------------------
		G_STOP_WORK_Click(sender, e);
		//--------------------------------------------------
		//	return the appropriate message about the end of the experiment.
		//--------------------------------------------------
		System::Threading::Thread::Sleep(200);
		My_Message(gcnew String("The experiment is done..!!"));
	}
	//
	//	Rotator function
	//	
	void MyForm::B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE_Click(System::Object^  sender, System::EventArgs^  e)
	{
		String^				 return_message;

		char                 file_name[MAX_STRING_LENGTH];
		char                 temp_string[MAX_STRING_LENGTH];
		char                 Experiment_type[MAX_STRING_LENGTH];		
		char                 Rotator_COM_port[MAX_STRING_LENGTH];
		char                 reults_file_name[MAX_STRING_LENGTH];

		fstream              protocol_file;
		marshal_context^	 context = gcnew marshal_context();

		float				 rotator_azimuth;
		float				 rotator_elevation;
		//-------------------------------------------
		//        Browse for protocol file
		//-------------------------------------------
		B_SelectLogFile_Of_Rotator->DefaultExt = "txt";
		B_SelectLogFile_Of_Rotator->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

		B_SelectLogFile_Of_Rotator->ShowDialog();
		sprintf_s(file_name, context->marshal_as<const char*>(B_SelectLogFile_Of_Rotator->FileName));

		B_LAB_ROTATOR_DATA_FILE_TO_SAVE->Text = B_SelectLogFile_Of_Rotator->FileName;
		B_LAB_ROTATOR_DATA_FILE_TO_SAVE->Refresh();
		//-------------------------------------------
		//   We save the current protocol file name of the Rotator
		//-------------------------------------------
		Lab_ROT2PROG.Protocol_file_name = B_SelectLogFile_Of_Rotator->FileName;		
		//-------------------------------------------
		//     Open the file to read the obstacles
		//-------------------------------------------		
		const char* protocol_file_name_of_rotator = context->marshal_as<const char*>(Lab_ROT2PROG.Protocol_file_name);
		protocol_file.open(protocol_file_name_of_rotator, std::ios_base::in);
		if (protocol_file.is_open())
		{
			//-------------------------------------------
			//     Read the experiment typ
			//-------------------------------------------
			protocol_file >> Experiment_type;
			//--------------------------------------------------
			//     Doppler experiment
			//--------------------------------------------------
			if (strcmp(Experiment_type, "AOA") == 0)
			{
				//--------------------------------------------------
				//				load protocol
				//--------------------------------------------------
				protocol_file >> temp_string >> Rotator_COM_port;
				protocol_file >> temp_string >> rotator_azimuth;
				protocol_file >> temp_string >> rotator_elevation;
				protocol_file >> temp_string >> reults_file_name;
				//
				// Update the azimuth field and refresh the button
				//
				B_LAB_AZIMUTH->Text = rotator_azimuth.ToString();
				B_LAB_AZIMUTH->Refresh();
				//
				// Update the elevation field and refresh the button
				//
				B_LAB_ELEVATION->Text = rotator_elevation.ToString();
				B_LAB_ELEVATION->Refresh();
				//--------------------------------------------------
				//     Run protocol
				//--------------------------------------------------
				if (Lab_ROT2PROG.COM_port_Open(gcnew String(Rotator_COM_port), return_message) == true)
				{
					//My_Message(gcnew String("The experiment began."));
					//
					// close the port
					//
					Lab_ROT2PROG.COM_port_Close();
					//
					// Update the COM Port field and refresh the button
					//
					B_ROTATOR_COM_PORT->Text = gcnew String(Rotator_COM_port);
					B_ROTATOR_COM_PORT->Refresh();

					B_LAB_AZIMUTH_MIN_ValueChanged(sender, e);
					B_LAB_ELEVATION_MIN_ValueChanged(sender, e);
				}
				else
				{
					//-------------------------------------------------
					//   return the appropriate message about the connection
					//-------------------------------------------------
					My_Message(gcnew String(return_message));
				}
			}
		}
	}
	// --------------------------------------------------
	//  B_LAB_AZIMUTH_MIN_ValueChanged
	//  Alon Slapak		16/3/2016
	// 	Description:	LAB: Set Azimuth
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_LAB_AZIMUTH_MIN_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		String^				 return_message;

		if (my_Ignore_Evens == false)
		{
			if (Lab_ROT2PROG.COM_port_Open(B_ROTATOR_COM_PORT->Text, return_message) == true)
			{
				my_Ignore_Evens = true;
				B_LAB_AZIMUTH->Text = Decimal((float)((int)((float)(B_LAB_AZIMUTH->Value) / Lab_ROT2PROG.Azimuth_resolution) * Lab_ROT2PROG.Azimuth_resolution)).ToString();
				B_LAB_AZIMUTH->Refresh();
				B_LAB_ELEVATION->Text = Decimal((float)((int)((float)(B_LAB_ELEVATION->Value) / Lab_ROT2PROG.Elevation_resolution) * Lab_ROT2PROG.Elevation_resolution)).ToString();
				B_LAB_ELEVATION->Refresh();
				my_Ignore_Evens = false;
				//------------------------------------
				//		Set azimuth only
				//------------------------------------
				Lab_ROT2PROG.Rot2prog_set_position((float)B_LAB_AZIMUTH->Value, Lab_ROT2PROG.Current_elevation);
				//------------------------------------
				//		Monitor approach 
				//------------------------------------
				int counter = 0;
				float temp = (float)(B_LAB_AZIMUTH->Value);
				while (Lab_ROT2PROG.Current_azimuth != (float)(B_LAB_AZIMUTH->Value))
				{
					My_Message(gcnew String("Rotator is moving."));
					System::Threading::Thread::Sleep(1000);
					Lab_ROT2PROG.Rot2prog_get_position();
					B_CURRENT_AZIMUTH->Text = Lab_ROT2PROG.Current_azimuth.ToString();
					B_CURRENT_ELEVATION->Text = Lab_ROT2PROG.Current_elevation.ToString();
					B_CURRENT_AZIMUTH->Refresh();
					B_CURRENT_ELEVATION->Refresh();
					//My_Message(gcnew String(""));
					//System::Threading::Thread::Sleep(200);
				}
				//------------------------------------
				// Close COM
				//------------------------------------
				Lab_ROT2PROG.COM_port_Close();
			}
		}
	}
	// --------------------------------------------------
	//  B_LAB_ELEVATION_MIN_ValueChanged
	//  Alon Slapak		16/3/2016
	// 	Description:	LAB: Set eLEVATION
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_LAB_ELEVATION_MIN_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		String^				 return_message;
		if (my_Ignore_Evens == false)
		{
			if (Lab_ROT2PROG.COM_port_Open(B_ROTATOR_COM_PORT->Text, return_message) == true)
			{
				my_Ignore_Evens = true;
				B_LAB_AZIMUTH->Text = Decimal((float)((int)((float)(B_LAB_AZIMUTH->Value) / Lab_ROT2PROG.Azimuth_resolution) * Lab_ROT2PROG.Azimuth_resolution)).ToString();
				B_LAB_AZIMUTH->Refresh();
				B_LAB_ELEVATION->Text = Decimal((float)((int)((float)(B_LAB_ELEVATION->Value) / Lab_ROT2PROG.Elevation_resolution) * Lab_ROT2PROG.Elevation_resolution)).ToString();
				B_LAB_ELEVATION->Refresh();
				my_Ignore_Evens = false;
				//------------------------------------
				//		Set azimuth only
				//------------------------------------
				Lab_ROT2PROG.Rot2prog_set_position(Lab_ROT2PROG.Current_azimuth, (float)B_LAB_ELEVATION->Value);
				//------------------------------------
				//		Monitor approach 
				//------------------------------------
				int counter = 0;
				float temp = (float)(B_LAB_ELEVATION->Value);
				while (Lab_ROT2PROG.Current_elevation != (float)B_LAB_ELEVATION->Value)
				{
					System::Threading::Thread::Sleep(1000);
					Lab_ROT2PROG.Rot2prog_get_position();
					B_CURRENT_AZIMUTH->Text = Lab_ROT2PROG.Current_azimuth.ToString();
					B_CURRENT_ELEVATION->Text = Lab_ROT2PROG.Current_elevation.ToString();
					B_CURRENT_AZIMUTH->Refresh();
					B_CURRENT_ELEVATION->Refresh();
				}
				//------------------------------------
				// Close COM
				//------------------------------------
				Lab_ROT2PROG.COM_port_Close();
			}
		}
	}
	// --------------------------------------------------
	//  B_ROTATOR_TIMER_Tick
	//  Alon Slapak		22/3/2016
	// 	Description:	LAB: Show Clibrator status
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_ROTATOR_TIMER_Tick(System::Object^  sender, System::EventArgs^  e) {}

	void MyForm::B_ROTATOR_COM_PORT_VisibleChanged(System::Object^  sender, System::EventArgs^  e)
	{
		String^				 return_message;
		my_Ignore_Evens = true;
		if (Lab_ROT2PROG.COM_port_Open(B_ROTATOR_COM_PORT->Text, return_message) == true)
		{
			//------------------------------------
			//		Get current status
			//------------------------------------
			Lab_ROT2PROG.Rot2prog_get_position();
			//------------------------------------
			// Close COM
			//------------------------------------
			Lab_ROT2PROG.COM_port_Close();
			//------------------------------------
			//		Update controls
			//------------------------------------
			B_LAB_AZIMUTH->Increment = Decimal(Lab_ROT2PROG.Azimuth_resolution);
			B_LAB_ELEVATION->Increment = Decimal(Lab_ROT2PROG.Elevation_resolution);

			B_LAB_AZIMUTH->Value = Decimal(Lab_ROT2PROG.Current_azimuth);
			B_LAB_ELEVATION->Value = Decimal(Lab_ROT2PROG.Current_elevation);

			B_AZIMUTH_RESOLUTION->Text = Lab_ROT2PROG.Azimuth_resolution.ToString();
			B_ELEVATION_RESOLUTION->Text = Lab_ROT2PROG.Elevation_resolution.ToString();
			B_CURRENT_AZIMUTH->Text = Lab_ROT2PROG.Current_azimuth.ToString();
			B_CURRENT_ELEVATION->Text = Lab_ROT2PROG.Current_elevation.ToString();
			B_AZIMUTH_RESOLUTION->Refresh();
			B_ELEVATION_RESOLUTION->Refresh();
			B_CURRENT_AZIMUTH->Refresh();
			B_CURRENT_ELEVATION->Refresh();
		}
		my_Ignore_Evens = false;
	}

	void MyForm::B_ROTATOR_COM_PORT_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		String^				 return_message;
		my_Ignore_Evens = true;
		if (Lab_ROT2PROG.COM_port_Open(B_ROTATOR_COM_PORT->Text, return_message) == true)
		{
			//------------------------------------
			//		Get current status
			//------------------------------------
			Lab_ROT2PROG.Rot2prog_get_position();
			//------------------------------------
			// Close COM
			//------------------------------------
			Lab_ROT2PROG.COM_port_Close();
			//------------------------------------
			//		Update controls
			//------------------------------------
			B_LAB_AZIMUTH->Increment = Decimal(Lab_ROT2PROG.Azimuth_resolution);
			B_LAB_ELEVATION->Increment = Decimal(Lab_ROT2PROG.Elevation_resolution);

			B_LAB_AZIMUTH->Value = Decimal(Lab_ROT2PROG.Current_azimuth);
			B_LAB_ELEVATION->Value = Decimal(Lab_ROT2PROG.Current_elevation);

			B_AZIMUTH_RESOLUTION->Text = Lab_ROT2PROG.Azimuth_resolution.ToString();
			B_ELEVATION_RESOLUTION->Text = Lab_ROT2PROG.Elevation_resolution.ToString();
			B_CURRENT_AZIMUTH->Text = Lab_ROT2PROG.Current_azimuth.ToString();
			B_CURRENT_ELEVATION->Text = Lab_ROT2PROG.Current_elevation.ToString();
			B_AZIMUTH_RESOLUTION->Refresh();
			B_ELEVATION_RESOLUTION->Refresh();
			B_CURRENT_AZIMUTH->Refresh();
			B_CURRENT_ELEVATION->Refresh();
		}
		my_Ignore_Evens = false;
	}
	#pragma region Mouse Operations: B_MAP_PANEL (MAP Tab control Function)
	// --------------------------------------------------
	//  B_MAP_PANEL_MouseDown  
	//  Haim Otachi		28/12/2015
	// 	Description:	Take reference viewer position to serve for the mouse move function, so as to 
	//					move the viewer with the mouse.
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void MyForm::B_MAP_PANEL_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//-------------------------------------------------------
		//	LEFT: add WIRE
		//-------------------------------------------------------
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			mouse_x = e->X;
			mouse_y = e->Y;
		}
	}
	// --------------------------------------------------
	//  B_MAP_PANEL_KeyDown  
	//  Haim Otachi		10/03/2016
	// 	Description:	Take reference viewer position to serve for the mouse move function, so as to 
	//					move the viewer with the mouse.
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void MyForm::B_MAP_PANEL_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
	{
		//-------------------------------------------------------
		//	If down key of the keyboard was pressed
		//-------------------------------------------------------
		switch (e->KeyCode)
		{
			//
			//	casess for arrows of the keyboard
			//
			case Keys::Up:
				Radar_Viewer.Real_Time_Offset_Viewer_Position(0, -3);	
				break;
			case Keys::Down:
				Radar_Viewer.Real_Time_Offset_Viewer_Position(0, 3);
				break;
			case Keys::Right:				
				Radar_Viewer.Real_Time_Offset_Viewer_Position(3, 0);
				break;
			case Keys::Left:
				Radar_Viewer.Real_Time_Offset_Viewer_Position(-3, 0);
				break;
			//
			//	casess for 'zoom in' and 'zoom out' ('+' and '-' in the keyboard)
			//
			case Keys::Add:
				try
				{
					B_SCREEN_WIDTH_OF_VIEWER->Value -= 1;
					// --------------------------------------------------
					// Calculate the new scale
					// --------------------------------------------------
					double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
					Radar_Viewer.Set_Step_Viewer_Scale(screen_width_meter);
					// --------------------------------------------------
					// Refresh screen with new scale
					// --------------------------------------------------
					B_MAP_PANEL->Invalidate();
					//-----------------------------------------
					//	Plot the obstacles to the screen
					//-----------------------------------------
					Radar_Viewer.Plot_Step_Position_Of_Radar();
					//-----------------------------------------
					//	Update GUI controls
					//-----------------------------------------
					double scale = (double)GUI_Status->Screen_Width_Of_Viewer / 10;
					B_SCALE_VIEWER->Text = scale.ToString();
				}
				catch (Exception^ Ex)
				{
					Ex->Message;
				}
				break;
			case Keys::Subtract:
				try
				{
					B_SCREEN_WIDTH_OF_VIEWER->Value += 1;
					// --------------------------------------------------
					// Calculate the new scale
					// --------------------------------------------------
					double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
					Radar_Viewer.Set_Step_Viewer_Scale(screen_width_meter);
					// --------------------------------------------------
					// Refresh screen with new scale
					// --------------------------------------------------
					B_MAP_PANEL->Invalidate();
					//-----------------------------------------
					//	Plot the obstacles to the screen
					//-----------------------------------------
					Radar_Viewer.Plot_Step_Position_Of_Radar();
					//-----------------------------------------
					//	Update GUI controls
					//-----------------------------------------
					double scale = (double)GUI_Status->Screen_Width_Of_Viewer / 10;
					B_SCALE_VIEWER->Text = scale.ToString();
				}
				catch (Exception^ Ex)
				{
					Ex->Message;
				}
				break;
		}
		//Radar_Viewer.Real_Time_Offset_Viewer_Position(mouse_x - offset_x, mouse_y - offset_y);
		//offset_x = mouse_x;
		//offset_y = mouse_y;
		//-----------------------------------------
		//	Plot the TOM obstacles and the Radar to the screen
		//-----------------------------------------
		Radar_Viewer.Add_Radar_Post();
		Radar_Viewer.Plot_Step_Position_Of_Radar();
	}
	// --------------------------------------------------
	//  B_MAP_PANEL_MouseMove  
	//  Haim Otachi		28/12/2015
	// 	Description:	Move viewer when moving the mouse with left-button pressed
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void MyForm::B_MAP_PANEL_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			Radar_Viewer.Real_Time_Offset_Viewer_Position(e->X - mouse_x, e->Y - mouse_y);
			mouse_x = e->X;
			mouse_y = e->Y;
			//-----------------------------------------
			//	Plot the TOM obstacles and the Radar to the screen
			//-----------------------------------------
			Radar_Viewer.Add_Radar_Post();
			Radar_Viewer.Plot_Step_Position_Of_Radar();
		}
	}
	// --------------------------------------------------
	//  B_VIEWER_PANEL_MouseWheel  
	//  Haim Otachi		28/12/2015
	// 	Description:	Using the mouse wheel to change the scale of the viewer
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void MyForm::B_MAP_PANEL_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if ((e->Delta < 0) && (B_SCREEN_WIDTH_OF_VIEWER->Value > B_SCREEN_WIDTH_OF_VIEWER->Minimum))
		{
			B_SCREEN_WIDTH_OF_VIEWER->Value -= 1;
		}
		if ((e->Delta > 0) && (B_SCREEN_WIDTH_OF_VIEWER->Value < B_SCREEN_WIDTH_OF_VIEWER->Maximum))
		{
			B_SCREEN_WIDTH_OF_VIEWER->Value += 1;
		}
		// --------------------------------------------------
		// Calculate the new scale
		// --------------------------------------------------		
		double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
		Radar_Viewer.Set_Step_Viewer_Scale(screen_width_meter);
		//-----------------------------------------
		//	Plot the TOM obstacles and the Radar to the screen
		//-----------------------------------------
		Radar_Viewer.Plot_Step_Position_Of_Radar();
		//-----------------------------------------
		//	Update GUI controls
		//-----------------------------------------
		double scale = (double)GUI_Status->Screen_Width_Of_Viewer / 10;
		B_SCALE_VIEWER->Text = scale.ToString();
	}
	// --------------------------------------------------
	//  B_SCREEN_WIDTH_OF_VIEWER	
	//  Haim Otachi     11/10/2015
	// 	Description:	change radar screen width
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void MyForm::B_SCREEN_WIDTH_OF_VIEWER_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		try
		{
			// --------------------------------------------------
			// Calculate the new scale
			// --------------------------------------------------
			double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
			Radar_Viewer.Set_Step_Viewer_Scale(screen_width_meter);
			// --------------------------------------------------
			// Refresh screen with new scale
			// --------------------------------------------------
			B_MAP_PANEL->Invalidate();
			//-----------------------------------------
			//	Plot the obstacles to the screen
			//-----------------------------------------
			Radar_Viewer.Plot_Step_Position_Of_Radar();
			//-----------------------------------------
			//	Update GUI controls
			//-----------------------------------------
			double scale = (double)GUI_Status->Screen_Width_Of_Viewer / 10;
			B_SCALE_VIEWER->Text = scale.ToString();
		}
		catch (Exception^ Ex)
		{
			Ex->Message;
		}
	}
	void MyForm::B_ZOOM_IN_Click(System::Object^  sender, System::EventArgs^  e)
	{	
		if(B_SCREEN_WIDTH_OF_VIEWER->Value > B_SCREEN_WIDTH_OF_VIEWER->Minimum)
		{
			B_SCREEN_WIDTH_OF_VIEWER->Value -= 1;
			// --------------------------------------------------
			// Calculate the new scale
			// --------------------------------------------------
			double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
			Radar_Viewer.Set_Step_Viewer_Scale(screen_width_meter);
			// --------------------------------------------------
			// Refresh screen with new scale
			// --------------------------------------------------
			B_MAP_PANEL->Invalidate();
			//-----------------------------------------
			//	Plot the obstacles to the screen
			//-----------------------------------------
			Radar_Viewer.Plot_Step_Position_Of_Radar();
			//-----------------------------------------
			//	Update GUI controls
			//-----------------------------------------
			double scale = (double)GUI_Status->Screen_Width_Of_Viewer / 10;
			B_SCALE_VIEWER->Text = scale.ToString();
		}
	}
	void MyForm::B_ZOOM_OUT_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(B_SCREEN_WIDTH_OF_VIEWER->Value < B_SCREEN_WIDTH_OF_VIEWER->Maximum)
		{
			B_SCREEN_WIDTH_OF_VIEWER->Value += 1;
			// --------------------------------------------------
			// Calculate the new scale
			// --------------------------------------------------
			double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
			Radar_Viewer.Set_Step_Viewer_Scale(screen_width_meter);
			// --------------------------------------------------
			// Refresh screen with new scale
			// --------------------------------------------------
			B_MAP_PANEL->Invalidate();
			//-----------------------------------------
			//	Plot the obstacles to the screen
			//-----------------------------------------
			Radar_Viewer.Plot_Step_Position_Of_Radar();
			//-----------------------------------------
			//	Update GUI controls
			//-----------------------------------------
			double scale = (double)GUI_Status->Screen_Width_Of_Viewer / 10;
			B_SCALE_VIEWER->Text = scale.ToString();
		}
	}
	void MyForm::B_REAL_TIME_TOOL_EDIT_Click(System::Object^  sender, System::EventArgs^  e)
	{
		
	}
	
	#pragma endregion
	
	// --------------------------------------------------
	//  B_RE_FLIGHT_Click  
	//  Haim Otachi		04/01/2016
	// 	Description:	The function opens a new window that represent the 'recovery flight' of the radar from the data_recording file
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void MyForm::B_RE_FLIGHT_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Loading_Page loading_page;
		//-----------------------------------------------
		//	we initialize the new windows that we want to open
		//-----------------------------------------------
		//Recovery_Flight  recovery_flight;
		loading_page.Show();
		//System::Threading::Thread::Sleep(5000);
		//-----------------------------------------------
		//	Open the new windows for recovery flight
		//-----------------------------------------------
		//recovery_flight.ShowDialog();
	}

	void MyForm::B_MAX_ERROR_RANGE_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//-----------------------------------------
		//	Update new 'RELIABILITY THRESHOLd' value in the system
		//-----------------------------------------
		GUI_Status->Update(MAX_RANGE_ERROR_METER, Convert::ToInt32(B_MAX_ERROR_RANGE->Value));
		//-----------------------------------------
		//	Initialize the Radar Viewer again, so revalidate the system's parameters again
		//-----------------------------------------
		Radar_Viewer.Initialize(B_MAP_PANEL, gcnew PictureBox, *GUI_Status);
	}

	//void MyForm::B_RELIABILITY_THRESHOLD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	//{
	//	//-----------------------------------------
	//	//	Update new 'RELIABILITY THRESHOLd' value in the system
	//	//-----------------------------------------
	//	GUI_Status->Update(RELIABILITY_THRESHOLd, Convert::ToInt32(B_RELIABILITY_THRESHOLD->Value));
	//	//-----------------------------------------
	//	//	Initialize the Radar Viewer again, so revalidate the system's parameters again
	//	//-----------------------------------------
	//	Radar_Viewer.Initialize(B_MAP_PANEL, gcnew PictureBox, *GUI_Status);
	//}
	void MyForm::B_WIRE_SEGMENT_LENGTH_METER_ValueChanged(System::Object^  sender, System::EventArgs^  e){}
	#pragma endregion

	#pragma region Done
	// --------------------------------------------------
	//  My_Message
	//  Alon Slapak 3/10/2014
	// 	Description:	Put message on the GUI
	// 	Reference: 
	//	Input Value:	Message string
	//  Return Value: 
	// --------------------------------------------------
	void MyForm::My_Message(String^ message_string)
	{
		B_message->Text = message_string;
		B_message->Refresh();
	}
	// --------------------------------------------------
	//  GOOD_FAULT
	//  Alon Slapak 3/10/2014
	// 	Description:	translate GOOD/FAULT index to string
	// 	Reference: 
	//	Input Value:	GOOD/FAULT index
	//  Return Value:	"GOOD"/"FAULT" string
	// --------------------------------------------------
	String^ MyForm::GOOD_FAULT(UINT32_T integerValue)
	{
		switch (integerValue)
		{
		case GOOD:
			return "GOOD";
			break;
		case FAULT:
			return "FAULT";
			break;
		default:
			return integerValue.ToString();
		}
	}
	// --------------------------------------------------
	//  BUL_COLOR
	//  Alon Slapak 3/10/2014
	// 	Description:	translate status message index to color to alert in the GUI
	// 	Reference: 
	//	Input Value:	status message index
	//  Return Value:	Color
	// --------------------------------------------------
	Color MyForm::BUL_COLOR(int BUL_status_message)
	{
		switch (BUL_status_message)
		{
			//-----------------------------------------------
			//					DONE
			//-----------------------------------------------
		case 0:
			return System::Drawing::Color::Transparent;
			break;
			//-----------------------------------------------
			//					Error
			//-----------------------------------------------
		case 1:
			return System::Drawing::Color::Red;
			break;
			//-----------------------------------------------
			//					Ready
			//-----------------------------------------------
		case 2:
			return System::Drawing::Color::Transparent;
			break;
			//-----------------------------------------------
			//					Flashing
			//-----------------------------------------------
		case 3:
			return System::Drawing::Color::Olive;
			break;
			//-----------------------------------------------
			//					Verifying
			//-----------------------------------------------
		case 4:
			return System::Drawing::Color::Olive;
			break;
		default:
			return System::Drawing::Color::Olive;
		}
	}
	// --------------------------------------------------
	//  BG_COLOR
	//  Alon Slapak 3/10/2014
	// 	Description:	translate value to color to alert in the GUI
	// 	Reference: 
	//	Input Value:	value
	//  Return Value:	Color
	// --------------------------------------------------
	Color MyForm::BG_COLOR(UINT32_T integerValue)
	{
		switch (integerValue)
		{
		case GOOD:
			return System::Drawing::Color::Transparent;
			break;
		case FAULT:
			return System::Drawing::Color::Red;
			break;
		default:
			return System::Drawing::Color::Yellow;
		}
	}
	// --------------------------------------------------
	//  int2BULStatusMessages
	//  Alon Slapak 3/10/2014
	// 	Description:	translate Boot status message index to string
	// 	Reference: 
	//	Input Value:	Boot status message index
	//  Return Value:	Boot status message string
	// --------------------------------------------------
	String^	MyForm::int2BULStatusMessages(int BUL_status_message)
	{
		switch (BUL_status_message)
		{
		case 0:
			return "Done";
			break;
		case 1:
			return "Error";
			break;
		case 2:
			return "Ready";
			break;
		case 3:
			return "Flashing";
			break;
		case 4:
			return "Verifying";
			break;
		default:
			return BUL_status_message.ToString();
		}
	}
	// --------------------------------------------------
	//  Update_Status_ARC_Controls
	//  Alon Slapak						3/10/2014
	//  Updated by Haim Otachi at		29/12/2015
	// 	Description:					Update values in the controls of the Status group box
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Update_Status_ARC_Controls()
	{
		this->B_DEBUG_COUNT->Text = System_Status->system_control_0->ARC_status.DEBUG_COUNT.ToString();
		this->B_System_Health_Status->Text = System_Status->system_control_0->ARC_status.DEBUG_COUNT.ToString();
		//-----------------------------------------------
		//       DSP STATUS
		//-----------------------------------------------
		this->B_OMR_STATUS->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.STATUS_OMR);
		this->L_OMR_STATUS->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.STATUS_OMR);

		this->B_DET_STATUS->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.STATUS_DET);
		this->L_DET_STATUS->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.STATUS_DET);

		this->B_CHA_STATUS->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.STATUS_CHA);
		this->L_CHA_STATUS->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.STATUS_CHA);

		this->B_CHB_STATUS->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.STATUS_CHB);
		this->L_CHB_STATUS->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.STATUS_CHB);

		this->B_MCU_STATUS->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.STATUS_MCU);
		this->L_MCU_STATUS->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.STATUS_MCU);

		this->B_RF_MCU_STATUS->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.STATUS_RF_MCU);
		this->L_RF_MCU_STATUS->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.STATUS_RF_MCU);

		this->B_HMC830_PLL->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.HMC830_PLL);
		this->L_HMC830_PLL->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.HMC830_PLL);
		//-----------------------------------------------
		//       PERIPHERALS
		//-----------------------------------------------
		this->B_PERIPHERALS_AD6655_A->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.PERIPHERALS_AD6655_A);
		this->L_AD6655_A->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.PERIPHERALS_AD6655_A);

		this->B_PERIPHERALS_AD6655_B->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.PERIPHERALS_AD6655_B);
		this->L_AD6655_B->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.PERIPHERALS_AD6655_B);

		this->B_PERIPHERALS_FPGA_A->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.PERIPHERALS_FPGA_A);
		this->L_FPGA_A->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.PERIPHERALS_FPGA_A);

		this->B_PERIPHERALS_FPGA_B->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.PERIPHERALS_FPGA_B);
		this->L_FPGA_B->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.PERIPHERALS_FPGA_B);

		this->B_PERIPHERALS_LMK04828->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.PERIPHERALS_LMK04828);
		this->L_LMK04828->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.PERIPHERALS_LMK04828);

		this->B_PERIPHERALS_LMK01000->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.PERIPHERALS_LMK01000);
		this->L_LMK01000->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.PERIPHERALS_LMK01000);

		this->B_PERIPHERALS_AD9910_A->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.PERIPHERALS_AD9910_A);
		this->L_AD9910_A->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.PERIPHERALS_AD9910_A);

		this->B_PERIPHERALS_AD9910_B->Text = GOOD_FAULT(System_Status->system_control_0->ARC_status.PERIPHERALS_AD9910_B);
		this->L_AD9910_B->BackColor = BG_COLOR(System_Status->system_control_0->ARC_status.PERIPHERALS_AD9910_B);
		//-----------------------------------------------
		//      TEMPERATURE MCU
		//-----------------------------------------------
		this->B_MCU_TEMP->Text = System_Status->system_control_0->ARC_status.MCU_TEMPERATURE.ToString();
		if (System_Status->system_control_0->ARC_status.MCU_TEMPERATURE > 65)
			this->L_MCU_TEMP->BackColor = System::Drawing::Color::Red;
		else
			this->L_MCU_TEMP->BackColor = System::Drawing::Color::Transparent;
		//-----------------------------------------------
		//      TEMPERATURE UCD9222 DET internal
		//-----------------------------------------------
		this->B_UCD9222_DET_temperature_internal->Text = System_Status->system_control_0->ARC_status.UCD9222_DET_temperature_internal.ToString();
		if (System_Status->system_control_0->ARC_status.UCD9222_DET_temperature_internal > 90)
			this->L_UCD9222_DET_internal->BackColor = System::Drawing::Color::Red;
		else
			this->L_UCD9222_DET_internal->BackColor = System::Drawing::Color::Transparent;
		//-----------------------------------------------
		//      TEMPERATURE UCD9222 DET external
		//-----------------------------------------------
		this->B_UCD9222_DET_temperature_external->Text = System_Status->system_control_0->ARC_status.UCD9222_DET_temperature_external.ToString();
		if (System_Status->system_control_0->ARC_status.UCD9222_DET_temperature_external > 90)
			this->L_UCD9222_DET_external->BackColor = System::Drawing::Color::Red;
		else
			this->L_UCD9222_DET_external->BackColor = System::Drawing::Color::Transparent;
		//-----------------------------------------------
		//      TEMPERATURE UCD9222 CHA internal
		//-----------------------------------------------
		this->B_UCD9222_CHA_temperature_internal->Text = System_Status->system_control_0->ARC_status.UCD9222_CHA_temperature_internal.ToString();
		if (System_Status->system_control_0->ARC_status.UCD9222_CHA_temperature_internal > 90)
			this->L_UCD9222_CHA_internal->BackColor = System::Drawing::Color::Red;
		else
			this->L_UCD9222_CHA_internal->BackColor = System::Drawing::Color::Transparent;
		//-----------------------------------------------
		//      TEMPERATURE UCD9222 CHA external
		//-----------------------------------------------
		this->B_UCD9222_CHA_temperature_external->Text = System_Status->system_control_0->ARC_status.UCD9222_CHA_temperature_external.ToString();
		if (System_Status->system_control_0->ARC_status.UCD9222_CHA_temperature_external > 90)
			this->L_UCD9222_CHA_external->BackColor = System::Drawing::Color::Red;
		else
			this->L_UCD9222_CHA_external->BackColor = System::Drawing::Color::Transparent;
		//-----------------------------------------------
		//      TEMPERATURE RF MCU
		//-----------------------------------------------
		this->B_RF_MCU_TEMP->Text = System_Status->system_control_0->ARC_status.RF_MCU_temperature.ToString();
		if (System_Status->system_control_0->ARC_status.RF_MCU_temperature > 65)
			this->L_RF_MCU_TEMP->BackColor = System::Drawing::Color::Red;
		else
			this->L_RF_MCU_TEMP->BackColor = System::Drawing::Color::Transparent;
		//-----------------------------------------------
		//      TEMPERATURE RF
		//-----------------------------------------------
		this->B_RF_TEMP->Text = System_Status->system_control_0->ARC_status.RF_temperature.ToString();
		if (System_Status->system_control_0->ARC_status.RF_temperature > 90)
			this->L_RF_BOARD_TEMP->BackColor = System::Drawing::Color::Red;
		else
			this->L_RF_BOARD_TEMP->BackColor = System::Drawing::Color::Transparent;
		//-----------------------------------------------
		//      States-machines
		//-----------------------------------------------
		this->B_DET_WORK_STATE->Text = System_Status->system_control_0->ARC_status.DET_STATES_shadow.DET_WORK_STATE.ToString();
		this->B_DET_ACQUISITION_STATE->Text = System_Status->system_control_0->ARC_status.DET_STATES_shadow.DET_ACQUISITION_STATE.ToString();
		this->B_DET_BRAIN_STATE->Text = System_Status->system_control_0->ARC_status.DET_STATES_shadow.DET_BRAIN_STATE.ToString();
		this->B_DET_CALIBRATE_STATE->Text = System_Status->system_control_0->ARC_status.DET_STATES_shadow.DET_CALIBRATE_STATE.ToString();
		this->B_DET_FIRST_DETECTION_STATE->Text = System_Status->system_control_0->ARC_status.DET_STATES_shadow.DET_FIRST_DETECTION_STATE.ToString();
		this->B_DET_INITIALIZATION_STATE->Text = System_Status->system_control_0->ARC_status.DET_STATES_shadow.CHAB_INITIALIZATION_STATE.ToString();

		this->B_CHA_WORK_STATE->Text = System_Status->system_control_0->ARC_status.CHA_STATES_shadow.CHAB_WORK_STATE.ToString();
		this->B_CHB_WORK_STATE->Text = System_Status->system_control_0->ARC_status.CHB_STATES_shadow.CHAB_WORK_STATE.ToString();
		//-----------------------------------------------
		//      SW version
		//-----------------------------------------------
		this->B_OMR_VERSION->Text = System_Status->system_control_0->ARC_status.SW_VERSION_OMR.ToString();
		this->B_DET_VERSION->Text = System_Status->system_control_0->ARC_status.SW_VERSION_DET.ToString();
		this->B_CHA_VERSION->Text = System_Status->system_control_0->ARC_status.SW_VERSION_CHA.ToString();
		this->B_CHB_VERSION->Text = System_Status->system_control_0->ARC_status.SW_VERSION_CHB.ToString();
		this->B_MCU_VERSION->Text = System_Status->system_control_0->ARC_status.SW_VERSION_MCU.ToString();
		this->B_RF_MCU_Version->Text = System_Status->system_control_0->ARC_status.SW_VERSION_RF_MCU.ToString();	
	}
	// --------------------------------------------------
	//  Update_Sensor_Controls
	//  Alon Slapak 3/10/2014
	// 	Description:	Update values in the controls of the Sensor group box
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Update_Sensor_Controls()
	{
		int  NAV_Health = (int)System_Status->system_control_0->SENSOR_data.Health;
		BOOL INS_Health, GPS_Health;
		//-----------------------------------------
		//			SENSOR INS
		//-----------------------------------------
		this->B_SENSOR_INS_YAW->Text = System_Status->system_control_0->SENSOR_data.INS_YAW.ToString("N2");
		this->B_SENSOR_INS_PITCH->Text = System_Status->system_control_0->SENSOR_data.INS_PITCH.ToString("N2");
		this->B_SENSOR_INS_ROLL->Text = System_Status->system_control_0->SENSOR_data.INS_ROLL.ToString("N2");
		//-----------------------------------------
		//			SENSOR UTM Coordinates
		//-----------------------------------------
		this->B_SENSOR_LATITUDE->Text = System_Status->system_control_0->SENSOR_data.Latitude.ToString("N8");
		this->B_SENSOR_LONGITUDE->Text = System_Status->system_control_0->SENSOR_data.Longitude.ToString("N8");
		this->B_SENSOR_ALTITUDE->Text = System_Status->system_control_0->SENSOR_data.Altitude.ToString("N2");
		//-----------------------------------------
		//			SENSOR VELOCITY
		//-----------------------------------------
		this->B_SENSOR_VELOCITY_X->Text = System_Status->system_control_0->SENSOR_data.VelocityX.ToString("N2");
		this->B_SENSOR_VELOCITY_Y->Text = System_Status->system_control_0->SENSOR_data.VelocityY.ToString("N2");
		this->B_SENSOR_VELOCITY_Z->Text = System_Status->system_control_0->SENSOR_data.VelocityZ.ToString("N2");
		//-----------------------------------------
		//			SENSOR ACCELERATION
		//-----------------------------------------
		this->B_SENSOR_ACCELERATION_X->Text = System_Status->system_control_0->SENSOR_data.AccelX.ToString("N2");
		this->B_SENSOR_ACCELERATION_Y->Text = System_Status->system_control_0->SENSOR_data.AccelY.ToString("N2");
		this->B_SENSOR_ACCELERATION_Z->Text = System_Status->system_control_0->SENSOR_data.AccelZ.ToString("N2");
		//-----------------------------------------
		//			SENSOR ANGULAR RATE
		//-----------------------------------------
		this->B_SENSOR_ANGULAR_RATE_X->Text = System_Status->system_control_0->SENSOR_data.AngularRateX.ToString("N2");
		this->B_SENSOR_ANGULAR_RATE_Y->Text = System_Status->system_control_0->SENSOR_data.AngularRateY.ToString("N2");
		this->B_SENSOR_ANGULAR_RATE_Z->Text = System_Status->system_control_0->SENSOR_data.AngularRateZ.ToString("N2");
		//-----------------------------------------
		//			SENSOR TIME
		//-----------------------------------------
		this->B_SENSOR_TIME->Text = System_Status->system_control_0->SENSOR_data.time.ToString("N2");
		//-----------------------------------------
		//			???
		//-----------------------------------------
		this->B_SENSOR_AttUncertainty->Text = System_Status->system_control_0->SENSOR_data.AttUncertainty.ToString("N2");
		this->B_SENSOR_PosUncertainty->Text = System_Status->system_control_0->SENSOR_data.PosUncertainty.ToString("N2");
		this->B_SENSOR_VelUncertainty->Text = System_Status->system_control_0->SENSOR_data.VelUncertainty.ToString("N2");
		//-----------------------------------------
		//			SENSOR ATT
		//-----------------------------------------
		this->B_SENSOR_ATT_YAW->Text = System_Status->system_control_0->SENSOR_data.ATT_YAW.ToString("N2");
		this->B_SENSOR_ATT_PITCH->Text = System_Status->system_control_0->SENSOR_data.ATT_PITCH.ToString("N2");
		this->B_SENSOR_ATT_ROLL->Text = System_Status->system_control_0->SENSOR_data.ATT_ROLL.ToString("N2");

		if ((NAV_Health & 0x2) == 0x2)
		{
			INS_Health = TRUE;
		}
		else
		{
			INS_Health = FALSE;
		}
		if ((NAV_Health & 0x4) == 0x4)
		{
			GPS_Health = TRUE;
		}
		else
		{
			GPS_Health = FALSE;
		}

		if (INS_Health && GPS_Health)
		{
			this->B_Navigation_Status->Text = "GPS + INS";
			this->B_Navigation_Status->BackColor = System::Drawing::Color::Lime;
		}
		else
		{
			if (INS_Health)
			{
				this->B_Navigation_Status->Text = "INS";
				this->B_Navigation_Status->BackColor = System::Drawing::Color::Yellow;
			}
			else
			{
				if (GPS_Health)
				{
					this->B_Navigation_Status->Text = "GPS";
					this->B_Navigation_Status->BackColor = System::Drawing::Color::Yellow;
				}
				else
				{
					this->B_Navigation_Status->Text = "";
					this->B_Navigation_Status->BackColor = System::Drawing::Color::Red;
				}
			}
		}
	}
	// --------------------------------------------------
	//  Targets_Update_Controls
	//  Alon Slapak 3/10/2014
	// 	Description:	Update values in the controls of the Targets group box
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Targets_Update_Controls(T_TARGETS_data* pTARGETS_data)
	{
		double noise[4];
		double SNR[4][4];
		double Polarization_ratio[4];

		// Noise
		noise[0] = 20 * log10((double)pTARGETS_data->Noise_Level[0] / 32767);
		noise[1] = 20 * log10((double)pTARGETS_data->Noise_Level[1] / 32767);
		noise[2] = 20 * log10((double)pTARGETS_data->Noise_Level[2] / 32767);
		noise[3] = 20 * log10((double)pTARGETS_data->Noise_Level[3] / 32767);

		T_HL_Noise->Text = noise[0].ToString("N3");
		T_VL_Noise->Text = noise[1].ToString("N3");
		T_HR_Noise->Text = noise[2].ToString("N3");
		T_VR_Noise->Text = noise[3].ToString("N3");

		// SNR
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				SNR[i][j] = 20 * log10((sqrt((double)(pTARGETS_data->Targets_array[i].Gain[j])) / 32767) + DBL_MIN) - noise[j];
			}
			Polarization_ratio[i] = (pTARGETS_data->Targets_array[i].Polarization_ratio_L + pTARGETS_data->Targets_array[i].Polarization_ratio_R) / 2;
		}

		B_TGT_R_1->Text = pTARGETS_data->Targets_array[0].Range.ToString("N3");
		B_TGT_D_1->Text = pTARGETS_data->Targets_array[0].Azimuth_H.ToString("N3");
		B_TGT_P_1->Text = Polarization_ratio[0].ToString("N3");
		B_TGT_V_1->Text = pTARGETS_data->Targets_array[0].Radial_velocity.ToString("N3");
		B_TGT_AOA_H_1->Text = pTARGETS_data->Targets_array[0].Azimuth_H.ToString("N3");
		B_TGT_AOA_V_1->Text = pTARGETS_data->Targets_array[0].Azimuth_V.ToString("N3");
		B_TGT_POL_L_1->Text = pTARGETS_data->Targets_array[0].Polarization_ratio_L.ToString("N3");
		B_TGT_POL_R_1->Text = pTARGETS_data->Targets_array[0].Polarization_ratio_R.ToString("N3");
		B_TGT_HL_SNR_1->Text = SNR[0][0].ToString("N3");
		B_TGT_VL_SNR_1->Text = SNR[0][1].ToString("N3");
		B_TGT_HR_SNR_1->Text = SNR[0][2].ToString("N3");
		B_TGT_VR_SNR_1->Text = SNR[0][3].ToString("N3");
		B_TGT_RELIABILITY_1->Text = pTARGETS_data->Targets_array[0].Target_reliability.ToString("N3");

		B_TGT_R_2->Text = pTARGETS_data->Targets_array[1].Range.ToString("N3");
		B_TGT_D_2->Text = pTARGETS_data->Targets_array[1].Azimuth_H.ToString("N3");
		B_TGT_P_2->Text = Polarization_ratio[1].ToString("N3");
		B_TGT_V_2->Text = pTARGETS_data->Targets_array[1].Radial_velocity.ToString("N3");
		B_TGT_AOA_H_2->Text = pTARGETS_data->Targets_array[1].Azimuth_H.ToString("N3");
		B_TGT_AOA_V_2->Text = pTARGETS_data->Targets_array[1].Azimuth_V.ToString("N3");
		B_TGT_POL_L_2->Text = pTARGETS_data->Targets_array[1].Polarization_ratio_L.ToString("N3");
		B_TGT_POL_R_2->Text = pTARGETS_data->Targets_array[1].Polarization_ratio_R.ToString("N3");
		B_TGT_HL_SNR_2->Text = SNR[1][0].ToString("N3");
		B_TGT_VL_SNR_2->Text = SNR[1][1].ToString("N3");
		B_TGT_HR_SNR_2->Text = SNR[1][2].ToString("N3");
		B_TGT_VR_SNR_2->Text = SNR[1][3].ToString("N3");
		B_TGT_RELIABILITY_2->Text = pTARGETS_data->Targets_array[1].Target_reliability.ToString("N3");

		B_TGT_R_3->Text = pTARGETS_data->Targets_array[2].Range.ToString("N3");
		B_TGT_D_3->Text = pTARGETS_data->Targets_array[2].Azimuth_H.ToString("N3");
		B_TGT_P_3->Text = Polarization_ratio[2].ToString("N3");
		B_TGT_V_3->Text = pTARGETS_data->Targets_array[2].Radial_velocity.ToString("N3");
		B_TGT_AOA_H_3->Text = pTARGETS_data->Targets_array[2].Azimuth_H.ToString("N3");
		B_TGT_AOA_V_3->Text = pTARGETS_data->Targets_array[2].Azimuth_V.ToString("N3");
		B_TGT_POL_L_3->Text = pTARGETS_data->Targets_array[2].Polarization_ratio_L.ToString("N3");
		B_TGT_POL_R_3->Text = pTARGETS_data->Targets_array[2].Polarization_ratio_R.ToString("N3");
		B_TGT_HL_SNR_3->Text = SNR[2][0].ToString("N3");
		B_TGT_VL_SNR_3->Text = SNR[2][1].ToString("N3");
		B_TGT_HR_SNR_3->Text = SNR[2][2].ToString("N3");
		B_TGT_VR_SNR_3->Text = SNR[2][3].ToString("N3");
		B_TGT_RELIABILITY_3->Text = pTARGETS_data->Targets_array[2].Target_reliability.ToString("N3");

		B_TGT_R_4->Text = pTARGETS_data->Targets_array[3].Range.ToString("N3");
		B_TGT_D_4->Text = pTARGETS_data->Targets_array[3].Azimuth_H.ToString("N3");
		B_TGT_P_4->Text = Polarization_ratio[3].ToString("N3");
		B_TGT_V_4->Text = pTARGETS_data->Targets_array[3].Radial_velocity.ToString("N3");
		B_TGT_AOA_H_4->Text = pTARGETS_data->Targets_array[3].Azimuth_H.ToString("N3");
		B_TGT_AOA_V_4->Text = pTARGETS_data->Targets_array[3].Azimuth_V.ToString("N3");
		B_TGT_POL_L_4->Text = pTARGETS_data->Targets_array[3].Polarization_ratio_L.ToString("N3");
		B_TGT_POL_R_4->Text = pTARGETS_data->Targets_array[3].Polarization_ratio_R.ToString("N3");
		B_TGT_HL_SNR_4->Text = SNR[3][0].ToString("N3");
		B_TGT_VL_SNR_4->Text = SNR[3][1].ToString("N3");
		B_TGT_HR_SNR_4->Text = SNR[3][2].ToString("N3");
		B_TGT_VR_SNR_4->Text = SNR[3][3].ToString("N3");
		B_TGT_RELIABILITY_4->Text = pTARGETS_data->Targets_array[3].Target_reliability.ToString("N3");

		B_TGT_R_5->Text = pTARGETS_data->Targets_array[4].Range.ToString("N3");
		B_TGT_D_5->Text = pTARGETS_data->Targets_array[4].Azimuth_H.ToString("N3");
		B_TGT_P_5->Text = pTARGETS_data->Targets_array[4].Polarization_ratio_L.ToString("N3");
		B_TGT_V_5->Text = pTARGETS_data->Targets_array[4].Radial_velocity.ToString("N3");
		B_TGT_AOA_H_5->Text = pTARGETS_data->Targets_array[4].Azimuth_H.ToString("N3");
		B_TGT_AOA_V_5->Text = pTARGETS_data->Targets_array[4].Azimuth_V.ToString("N3");
		B_TGT_POL_L_5->Text = pTARGETS_data->Targets_array[4].Polarization_ratio_L.ToString("N3");
		B_TGT_POL_R_5->Text = pTARGETS_data->Targets_array[4].Polarization_ratio_R.ToString("N3");
		B_TGT_RELIABILITY_5->Text = pTARGETS_data->Targets_array[4].Target_reliability.ToString("N3");
	}
	// --------------------------------------------------
	//  Update_Status_TxRx_Controls
	//  Alon Slapak 16/3/2018
	// 	Description:	Update values in controls reflecting the SYSTEM_FLASH
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Update_Status_TxRx_Controls(T_TxRx_control* TxRx_control)
	{
		double IO_UPDATE = (double)TxRx_control->IO_UPDATE_rate / 1000;

		this->B_Profile_AD9910A->Text = TxRx_control->Profile_AD9910A.ToString();
		this->B_Profile_AD9910B->Text = TxRx_control->Profile_AD9910B.ToString();
		this->B_chip_length_AD9910A->Text = TxRx_control->chip_length_AD9910A.ToString();
		this->B_chip_length_AD9910B->Text = TxRx_control->chip_length_AD9910B.ToString();
		this->B_AD9910_Set_aux_dac_A->Text = TxRx_control->AD9910_Set_aux_dac_A.ToString();
		this->B_AD9910_Set_aux_dac_B->Text = TxRx_control->AD9910_Set_aux_dac_B.ToString();
		this->B_IO_UPDATE_rate->Text = IO_UPDATE.ToString("N3");

		this->B_ATTN_TX1->Text = TxRx_control->ATTN_TX1.ToString();
		this->B_ATTN_TX2->Text = TxRx_control->ATTN_TX2.ToString();
		this->B_ATTN_TX3->Text = TxRx_control->ATTN_TX3.ToString();
		this->B_ATTN_RX1->Text = TxRx_control->ATTN_RX1.ToString();
		this->B_ATTN_RX2->Text = TxRx_control->ATTN_RX2.ToString();
		this->B_ATTN_RX3->Text = TxRx_control->ATTN_RX3.ToString();
		this->B_ATTN_RX4->Text = TxRx_control->ATTN_RX4.ToString();
		// --------------------------------------------------
		//			CTRL lines
		// --------------------------------------------------
		if (TxRx_control->TX1_ON != 0)
			this->B_TX_ON1->Text = L"ON";
		else
			this->B_TX_ON1->Text = L"OFF";
		if (TxRx_control->TX2_ON != 0)
			this->B_TX_ON2->Text = L"ON";
		else
			this->B_TX_ON2->Text = L"OFF";
		if (TxRx_control->TX3_ON != 0)
			this->B_TX_ON3->Text = L"ON";
		else
			this->B_TX_ON3->Text = L"OFF";
		if (TxRx_control->PROBE_ON != 0)
			this->B_SAMPLE_ON_OFF->Text = L"ON";
		else
			this->B_SAMPLE_ON_OFF->Text = L"OFF";
		if (TxRx_control->TX_LO_TR != 0)
			this->B_TX_LO_TR->Text = L"ON";
		else
			this->B_TX_LO_TR->Text = L"OFF";
		if (TxRx_control->IO_UPDATE_ON != 0)
			this->B_IO_UPDATE_ON->Text = L"ON";
		else
			this->B_IO_UPDATE_ON->Text = L"OFF";
		if (TxRx_control->ANT_SAMPLE_SELECT != 0)
			this->B_ANT_SAMPLE_SELECT->Text = L"SAMPLE";
		else
			this->B_ANT_SAMPLE_SELECT->Text = L"ANT";
		// --------------------------------------------------
		//			IF SELECT
		// --------------------------------------------------
		if (TxRx_control->IF_SELECT_TX1 != 0)
			this->B_IF_SELECT_TX1->Text = L"B";
		else
			this->B_IF_SELECT_TX1->Text = L"A";
		if (TxRx_control->IF_SELECT_TX2 != 0)
			this->B_IF_SELECT_TX2->Text = L"B";
		else
			this->B_IF_SELECT_TX2->Text = L"A";
		if (TxRx_control->IF_SELECT_TX3 != 0)
			this->B_IF_SELECT_TX3->Text = L"B";
		else
			this->B_IF_SELECT_TX3->Text = L"A";
		if (TxRx_control->IF_SELECT_PROBE != 0)
			this->B_IF_SELECT_PROBE->Text = L"B";
		else
			this->B_IF_SELECT_PROBE->Text = L"A";
		// --------------------------------------------------
		//			FPGA PCIe buffers
		// --------------------------------------------------
		this->B_Buffer_length->Text = TxRx_control->Buffer_length.ToString();
		this->B_FIFO_length->Text = TxRx_control->FIFO_length.ToString();
	}
	// --------------------------------------------------
	//  Update_Status_Controls
	//  Alon Slapak 21/12/2014
	//	Updated by Haim Otachi at 07/01/2016
	// 	Description:	Update values in controls reflecting the SYSTEM_FLASH
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Update_Status_Controls()
	{
		char calib_grade_string[MAX_STRING_LENGTH];
		int	calib_grade_noise, calib_grade_snr, calib_grade_mag, calib_grade_phase;
		// --------------------------------------------------
		//			ARC
		// --------------------------------------------------
		Update_Status_ARC_Controls();
		// --------------------------------------------------
		//			TxRx
		// --------------------------------------------------
		this->B_TxRx_control_MODE->Text = F_TxRx_control_MODE->Text;
		this->B_SYSTEM_ID->Text = System_Status->system_control_0->SYSTEM_control_shadow.System_ID.ToString();

		switch (GUI_Status->disaplay_fields->FLASH_fields.TxRx_MODE)
		{
			case TxRx_MODE_WORK:
				Update_Status_TxRx_Controls(&System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK);
				break;

			case TxRx_MODE_PROBE:
				Update_Status_TxRx_Controls(&System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_PROBE);
				break;

			case TxRx_MODE_CALIBRATOR:
				Update_Status_TxRx_Controls(&System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_CALIBRATOR);
				break;

			default:
				break;
		}

		if (System_Status->system_control_0->SYSTEM_control_shadow.Enable_RF2_Support != 0)
		{
			this->B_RF2_ON->Text = L"ON";
		}
			
		else
		{
			this->B_RF2_ON->Text = L"OFF";
		}			
		// --------------------------------------------------
		//			Calibration
		// --------------------------------------------------
		this->B_CORRECTION_LH_I->Text = System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[0].I.ToString("N6");
		this->B_CORRECTION_LH_Q->Text = System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[0].Q.ToString("N6");
		this->B_CORRECTION_LV_I->Text = System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[1].I.ToString("N6");
		this->B_CORRECTION_LV_Q->Text = System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[1].Q.ToString("N6");
		this->B_CORRECTION_RH_I->Text = System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[2].I.ToString("N6");
		this->B_CORRECTION_RH_Q->Text = System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[2].Q.ToString("N6");
		this->B_CORRECTION_RV_I->Text = System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[3].I.ToString("N6");
		this->B_CORRECTION_RV_Q->Text = System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[3].Q.ToString("N6");

		this->B_CALIBRATOR_LH_I->Text = System_Status->system_control_0->SYSTEM_control_shadow.Calibrator_correction[0].I.ToString("N6");
		this->B_CALIBRATOR_LH_Q->Text = System_Status->system_control_0->SYSTEM_control_shadow.Calibrator_correction[0].Q.ToString("N6");
		this->B_CALIBRATOR_LV_I->Text = System_Status->system_control_0->SYSTEM_control_shadow.Calibrator_correction[1].I.ToString("N6");
		this->B_CALIBRATOR_LV_Q->Text = System_Status->system_control_0->SYSTEM_control_shadow.Calibrator_correction[1].Q.ToString("N6");
		this->B_CALIBRATOR_RH_I->Text = System_Status->system_control_0->SYSTEM_control_shadow.Calibrator_correction[2].I.ToString("N6");
		this->B_CALIBRATOR_RH_Q->Text = System_Status->system_control_0->SYSTEM_control_shadow.Calibrator_correction[2].Q.ToString("N6");
		this->B_CALIBRATOR_RV_I->Text = System_Status->system_control_0->SYSTEM_control_shadow.Calibrator_correction[3].I.ToString("N6");
		this->B_CALIBRATOR_RV_Q->Text = System_Status->system_control_0->SYSTEM_control_shadow.Calibrator_correction[3].Q.ToString("N6");

		if (correction1I != System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[0].I)
		{
			My_Message("Calibration Coefficients Were Updated.");
			if (System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[0].I != 1)
			{
				calib_grade_noise = (System_Status->system_control_0->ARC_status.clib_grade / 1000) % 10;
				calib_grade_snr = (System_Status->system_control_0->ARC_status.clib_grade / 100) % 10;
				calib_grade_mag = (System_Status->system_control_0->ARC_status.clib_grade / 10) % 10;
				calib_grade_phase = System_Status->system_control_0->ARC_status.clib_grade % 10;
				sprintf_s(calib_grade_string, "Calibration Done!, Grades are: Noise: %d, SNR: %d, Mag: %d, Phase: %d.", calib_grade_noise, calib_grade_snr, calib_grade_mag, calib_grade_phase);
				My_Message(gcnew String(calib_grade_string));
			}
			correction1I = System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[0].I;
		}

		this->B_PROBE_CALIBRATE_TGT_START->Text = System_Status->system_control_0->SYSTEM_control_shadow.TGT_calibrate.Probe_start_sample.ToString();
		this->B_PROBE_CALIBRATE_TGT_END->Text = System_Status->system_control_0->SYSTEM_control_shadow.TGT_calibrate.Probe_end_sample.ToString();
		this->B_CALIBRATOR_TGT_START->Text = System_Status->system_control_0->SYSTEM_control_shadow.TGT_calibrate.Calibrator_start_sample.ToString();
		this->B_CALIBRATOR_TGT_END->Text = System_Status->system_control_0->SYSTEM_control_shadow.TGT_calibrate.Calibrator_end_sample.ToString();
		// --------------------------------------------------
		//			ALGORITHMS
		// --------------------------------------------------
		this->B_Target_detection_1st_threshold->Text = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Target_detection_1st_threshold.ToString();
		this->B_Target_detection_2nd_threshold->Text = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Target_detection_2nd_threshold.ToString();
		this->B_MAX_VELOCITY->Text = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler.ToString();
		this->B_RANGE_DECIMATION->Text = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation.ToString();
		this->B_Number_of_buffers->Text = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers.ToString();
		this->B_OFFSET_sample->Text = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.OFFSET_samples.ToString();
		int temp = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples * METERS_PER_SAMPLE;
		this->B_RANGE_meter->Text = temp.ToString();
		this->B_AGC_threshold->Text = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.AGC_threshold.ToString();
		//--------------------------------------------------------
		//			Updating the batch duration
		//--------------------------------------------------------
		double	   batch_duartion = 0;
		uint32_t   Number_of_buffers;
		uint32_t   IO_UPDATE_rate;

		switch (GUI_Status->disaplay_fields->FLASH_fields.TxRx_MODE)
		{
			case TxRx_MODE_WORK:
				Number_of_buffers = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers / 4;
				IO_UPDATE_rate = System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.IO_UPDATE_rate / 1000;
				batch_duartion = (double)Number_of_buffers / IO_UPDATE_rate;
				break;

			case TxRx_MODE_PROBE:
				Number_of_buffers = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers / 4;
				IO_UPDATE_rate = System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_PROBE.IO_UPDATE_rate / 1000;
				batch_duartion = (double)Number_of_buffers / IO_UPDATE_rate;
				break;

			case TxRx_MODE_CALIBRATOR:
				Number_of_buffers = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers / 4;
				IO_UPDATE_rate = System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_CALIBRATOR.IO_UPDATE_rate / 1000;
				batch_duartion = (double)Number_of_buffers / IO_UPDATE_rate;
				break;

			default:
				break;
		}

		B_BATCH_DURATION->Text = batch_duartion.ToString("N2");
		//-----------------------------------------------
		//      FREE variables
		//-----------------------------------------------
		this->B_OMR_FREE_1->Text = System_Status->system_control_0->OMR_DEBUG_frees.FREE_1.ToString("N6");
		this->B_OMR_FREE_2->Text = System_Status->system_control_0->OMR_DEBUG_frees.FREE_2.ToString("N6");
		this->B_OMR_FREE_3->Text = System_Status->system_control_0->OMR_DEBUG_frees.FREE_3.ToString("N6");
		this->B_OMR_FREE_4->Text = System_Status->system_control_0->OMR_DEBUG_frees.FREE_4.ToString("N6");
		this->B_DET_FREE_1->Text = System_Status->system_control_0->DET_DEBUG_frees.FREE_1.ToString("N6");
		this->B_DET_FREE_2->Text = System_Status->system_control_0->DET_DEBUG_frees.FREE_2.ToString("N6");
		this->B_DET_FREE_3->Text = System_Status->system_control_0->DET_DEBUG_frees.FREE_3.ToString("N6");
		this->B_DET_FREE_4->Text = System_Status->system_control_0->DET_DEBUG_frees.FREE_4.ToString("N6");
		this->B_CHA_FREE_1->Text = System_Status->system_control_0->CHA_DEBUG_frees.FREE_1.ToString("N6");
		this->B_CHA_FREE_2->Text = System_Status->system_control_0->CHA_DEBUG_frees.FREE_2.ToString("N6");
		this->B_CHA_FREE_3->Text = System_Status->system_control_0->CHA_DEBUG_frees.FREE_3.ToString("N6");
		this->B_CHA_FREE_4->Text = System_Status->system_control_0->CHA_DEBUG_frees.FREE_4.ToString("N6");
		this->B_CHB_FREE_1->Text = System_Status->system_control_0->CHB_DEBUG_frees.FREE_1.ToString("N6");
		this->B_CHB_FREE_2->Text = System_Status->system_control_0->CHB_DEBUG_frees.FREE_2.ToString("N6");
		this->B_CHB_FREE_3->Text = System_Status->system_control_0->CHB_DEBUG_frees.FREE_3.ToString("N6");
		this->B_CHB_FREE_4->Text = System_Status->system_control_0->CHB_DEBUG_frees.FREE_4.ToString("N6");
	}
	// --------------------------------------------------
	//  Update_Debug_Tab_Controls
	//  Alon Slapak 3/10/2014
	// 	Description:	Update values in the controls of the Debug tab
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Update_Debug_Tab_Controls()
	{
		//-----------------------------------------------
		//	Put data in ANALYSE parameters
		//-----------------------------------------------
		this->B_SNAPSHOT_TYPE->SelectedIndex = GUI_Status->disaplay_fields->DEBUG_fields.SNAPSHOT_type;
		this->B_MATLAB_script->SelectedIndex = GUI_Status->disaplay_fields->DEBUG_fields.MATLAB_script_index;
		this->B_LOG_FOLDER->Text = gcnew String(GUI_Status->disaplay_fields->DEBUG_fields.LOG_folder);
	}
	// --------------------------------------------------
	//  Update_Work_Tab_Controls
	//  Alon Slapak 3/10/2014
	// 	Description:	Update values in the controls of the Work tab
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Update_Work_Tab_Controls() {}
	// --------------------------------------------------
	//  Update_Maintenance_Tab_Controls
	//  Alon Slapak 3/10/2014
	// 	Description:	Update values in the controls of the Maintenance tab
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Update_Maintenance_Tab_Controls()
	{
		//-----------------------------------------------
		//	Put data in BUL parameters
		//-----------------------------------------------
		this->B_Out_OMR->Text = gcnew String(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_OMR);
		this->B_Out_DET->Text = gcnew String(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_DET);
		this->B_Out_CHAB->Text = gcnew String(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_CHAB);
		this->B_Out_MCU->Text = gcnew String(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_MCU);
		this->B_Out_RF_MCU->Text = gcnew String(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_RF_MCU);
		this->B_ResetAfterUpload->Checked = (GUI_Status->disaplay_fields->MAINTENANCE_fields.reset_after_boot_upload == 1);
	}
	// --------------------------------------------------
	//  Update_BUL_Controls
	//  Alon Slapak 3/10/2014
	// 	Description:	Update values in the BUL precess controls
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Update_BUL_Controls()
	{
		//-----------------------------------------------
		//	BUL_status_OMR
		//-----------------------------------------------
		this->B_BUL_status_OMR->Text = int2BULStatusMessages(System_Status->system_control_0->ARC_status.BUL_status_OMR);
		this->L_BUL_status_OMR->BackColor = BUL_COLOR(System_Status->system_control_0->ARC_status.BUL_status_OMR);
		//-----------------------------------------------
		//	BUL_status_DET
		//-----------------------------------------------
		this->B_BUL_status_DET->Text = int2BULStatusMessages(System_Status->system_control_0->ARC_status.BUL_status_DET);
		this->L_BUL_status_DET->BackColor = BUL_COLOR(System_Status->system_control_0->ARC_status.BUL_status_DET);
		//-----------------------------------------------
		//	BUL_status_CHA
		//-----------------------------------------------
		this->B_BUL_status_CHA->Text = int2BULStatusMessages(System_Status->system_control_0->ARC_status.BUL_status_CHA);
		this->L_BUL_status_CHA->BackColor = BUL_COLOR(System_Status->system_control_0->ARC_status.BUL_status_CHA);
		//-----------------------------------------------
		//	BUL_status_CHB
		//-----------------------------------------------
		this->B_BUL_status_CHB->Text = int2BULStatusMessages(System_Status->system_control_0->ARC_status.BUL_status_CHB);
		this->L_BUL_status_CHB->BackColor = BUL_COLOR(System_Status->system_control_0->ARC_status.BUL_status_CHB);
		//-----------------------------------------------
		//	BUL_status_MCU
		//-----------------------------------------------
		this->B_BUL_status_MCU->Text = int2BULStatusMessages(System_Status->system_control_0->ARC_status.BUL_status_MCU);
		this->L_BUL_status_MCU->BackColor = BUL_COLOR(System_Status->system_control_0->ARC_status.BUL_status_MCU);
		//-----------------------------------------------
		//	BUL_status_RF_MCU
		//-----------------------------------------------
		this->B_BUL_status_RF_MCU->Text = int2BULStatusMessages(System_Status->system_control_0->ARC_status.BUL_status_RF_MCU);
	}
	// --------------------------------------------------
	//  Flash_TxRx_fields_to_Screen
	//  Alon Slapak 16/3/2015
	// 	Description:	Update values in the TxRx controls of the flash tab
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Flash_TxRx_fields_to_Screen(T_TxRx_control* TxRx_control)
	{
		double IO_UPDATE_rate = (double)TxRx_control->IO_UPDATE_rate / 1000;
		//-----------------------------------------------
		//	TX signals
		//-----------------------------------------------
		this->F_Profile_AD9910A->Text = TxRx_control->Profile_AD9910A.ToString();
		this->F_Profile_AD9910B->Text = TxRx_control->Profile_AD9910B.ToString();
		this->F_chip_length_AD9910A->Text = TxRx_control->chip_length_AD9910A.ToString();
		this->F_chip_length_AD9910B->Text = TxRx_control->chip_length_AD9910B.ToString();
		this->F_AD9910_Set_aux_dac_A->Text = TxRx_control->AD9910_Set_aux_dac_A.ToString();
		this->F_AD9910_Set_aux_dac_B->Text = TxRx_control->AD9910_Set_aux_dac_B.ToString();
		this->F_IO_UPDATE_rate->Text = IO_UPDATE_rate.ToString("N3");

		this->F_ATTN_TX1->Text = TxRx_control->ATTN_TX1.ToString();
		this->F_ATTN_TX2->Text = TxRx_control->ATTN_TX2.ToString();
		this->F_ATTN_TX3->Text = TxRx_control->ATTN_TX3.ToString();
		this->F_ATTN_RX1->Text = TxRx_control->ATTN_RX1.ToString();
		this->F_ATTN_RX2->Text = TxRx_control->ATTN_RX2.ToString();
		this->F_ATTN_RX3->Text = TxRx_control->ATTN_RX3.ToString();
		this->F_ATTN_RX4->Text = TxRx_control->ATTN_RX4.ToString();
		//-----------------------------------------------
		//	RF card
		//-----------------------------------------------
		this->F_TX1_ON->Checked = (TxRx_control->TX1_ON != 0);
		this->F_TX2_ON->Checked = (TxRx_control->TX2_ON != 0);
		this->F_TX3_ON->Checked = (TxRx_control->TX3_ON != 0);
		this->F_TX_LO_TR->Checked = (TxRx_control->TX_LO_TR != 0);
		this->F_PROBE_ON->Checked = (TxRx_control->PROBE_ON != 0);
		this->F_IO_UPDATE_ON->Checked = (TxRx_control->IO_UPDATE_ON != 0);
		//-----------------------------------------------
		//	changed by haim otachi:		25/01/2016
		//-----------------------------------------------
		this->F_PROBE_SELECT_SAMPLE->Checked = (TxRx_control->ANT_SAMPLE_SELECT == 0);
		this->F_IF_SELECT_TX1_A->Checked = (TxRx_control->IF_SELECT_TX1 != 0);
		this->F_IF_SELECT_TX2_A->Checked = (TxRx_control->IF_SELECT_TX2 != 0);
		this->F_IF_SELECT_TX3_A->Checked = (TxRx_control->IF_SELECT_TX3 != 0);
		this->F_IF_SELECT_PROBE_A->Checked = (TxRx_control->IF_SELECT_PROBE != 0);

		this->F_PROBE_SELECT_ANT->Checked = (TxRx_control->ANT_SAMPLE_SELECT != 0);
		this->F_IF_SELECT_TX1_B->Checked = (TxRx_control->IF_SELECT_TX1 != 0);
		this->F_IF_SELECT_TX2_B->Checked = (TxRx_control->IF_SELECT_TX2 != 0);
		this->F_IF_SELECT_TX3_B->Checked = (TxRx_control->IF_SELECT_TX3 != 0);
		this->F_IF_SELECT_PROBE_B->Checked = (TxRx_control->IF_SELECT_PROBE != 0);

		// --------------------------------------------------
		//		Acquisition
		// --------------------------------------------------
		this->F_Buffer_length->Text = TxRx_control->Buffer_length.ToString();
		this->F_FIFO_length->Text = TxRx_control->FIFO_length.ToString();
	}
	// --------------------------------------------------
	//  Flash_Display_fields_to_Screen
	//  Alon Slapak 3/10/2014
	// 	Description:	Update values in the controls of the Maintenance tab
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Flash_Display_fields_to_Screen()
	{
		F_SYSTEM_ID->Text = GUI_Status->disaplay_fields->FLASH_fields.System_ID.ToString();
		//-----------------------------------------------
		//	Tx/Rx control mode
		//-----------------------------------------------
		F_TxRx_control_MODE->SelectedIndex = GUI_Status->disaplay_fields->FLASH_fields.TxRx_MODE;
		//-----------------------------------------------
		//	Tx/Rx control
		//-----------------------------------------------
		Flash_TxRx_fields_to_Screen(&GUI_Status->disaplay_fields->FLASH_fields.TxRx_control[F_TxRx_control_MODE->SelectedIndex]);
		this->F_RF2_ON->Checked = (GUI_Status->disaplay_fields->FLASH_fields.Enable_RF2_Support != 0);
		// --------------------------------------------------
		//		Calibration
		// --------------------------------------------------
		this->F_PROBE_CALIBRATE_TGT_START->Text = GUI_Status->disaplay_fields->FLASH_fields.TGT_calibrate.Probe_start_sample.ToString();
		this->F_PROBE_CALIBRATE_TGT_END->Text = GUI_Status->disaplay_fields->FLASH_fields.TGT_calibrate.Probe_end_sample.ToString();
		this->F_CALIBRATOR_TGT_START->Text = GUI_Status->disaplay_fields->FLASH_fields.TGT_calibrate.Calibrator_start_sample.ToString();
		this->F_CALIBRATOR_TGT_END->Text = GUI_Status->disaplay_fields->FLASH_fields.TGT_calibrate.Calibrator_end_sample.ToString();
		//-----------------------------------------------
		//		PROBE test
		//-----------------------------------------------
		this->F_PROBE_TEST_profile->Text = GUI_Status->disaplay_fields->FLASH_fields.PROBE_test.PROBE_TEST_profile.ToString();
		this->F_PROBE_TEST_gain->Text = GUI_Status->disaplay_fields->FLASH_fields.PROBE_test.PROBE_TEST_gain.ToString();
		// --------------------------------------------------
		//		Algorithms
		// --------------------------------------------------
		this->F_Target_detection_1st_threshold->Text = GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms.Target_detection_1st_threshold.ToString();
		this->F_Target_detection_2nd_threshold->Text = GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms.Target_detection_2nd_threshold.ToString();
		this->F_MAX_VELOCITY->Text = GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms.Maximal_doppler.ToString();
		this->F_RANGE_DECIMATION->Text = GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms.Range_decimation.ToString();
		this->F_Number_of_buffers->Text = GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms.Number_of_buffers.ToString();
		this->F_OFFSET_sample->Text = GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms.OFFSET_samples.ToString();
		int temp = GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms.RANGE_samples * METERS_PER_SAMPLE;
		this->F_RANGE_meter->Text = temp.ToString();
		this->F_AGC_threshold->Text = GUI_Status->disaplay_fields->FLASH_fields.DET_algorithms.AGC_threshold.ToString();
		// --------------------------------------------------
		//		Minimum range between radar and obstacles
		// --------------------------------------------------
		//this->B_RELIABILITY_THRESHOLD->Text = GUI_Status->GUI_Data->General_Data.Reliability_Threshold.ToString();
		this->B_MAX_ERROR_RANGE->Text = GUI_Status->GUI_Data->General_Data.Max_Error_Range_Meter.ToString();
	}
	// --------------------------------------------------
	//  MyForm_FormClosing
	//  Alon Slapak 3/10/2014
	// 	Description:	Save data on closing GUI
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		GUI_Status->Save_Data_To_File();
	}
	// --------------------------------------------------
	//  Load_map_Click
	//  Ronen Globinsky 11/08/2015
	// 	Description:	BROWSE for obstacle map file
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::B_LOAD_MAP_Click(System::Object^  sender, System::EventArgs^  e)
	{
		char OBSTACLES_File_Name_Of_Map[MAX_STRING_LENGTH];
		// --------------------------------------------------
		//			ask for file name
		// --------------------------------------------------
		B_fileBrowser_TOM->ShowDialog();
		// --------------------------------------------------
		//			Update Radat_Viewer with TOM file name
		// --------------------------------------------------
		marshal_context ^ context = gcnew marshal_context();
		sprintf_s(OBSTACLES_File_Name_Of_Map, context->marshal_as<const char*>(B_fileBrowser_TOM->FileName));
		GUI_Status->Viewer_TOM_File_Name = OBSTACLES_File_Name_Of_Map;
		// --------------------------------------------------
		//			Clear screen
		// --------------------------------------------------	
		Radar_Viewer.Clear_Screen();
		B_MAP_PANEL->Invalidate();
		//--------------------------------------
		//	Laod TOM and plot on screen
		//--------------------------------------
		if (Radar_Viewer.Load_TOM_From_File() == false)
		{
			My_Message("TOM file is incorrect.");
			return;
		}	
		
		B_SCREEN_WIDTH_OF_VIEWER->Value = (GUI_Status->Screen_Width_Of_Viewer / 1000);
		double scale = (double)GUI_Status->Screen_Width_Of_Viewer / 10;

		B_SCALE_VIEWER->Text = scale.ToString();
	}
	// --------------------------------------------------
	//  B_MAIN_config_Click
	//  Alon Slapak 3/10/2014
	// 	Description:	send config message to radar
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_MAIN_config_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->timer_DSP_messages->Enabled = false;
		//---------------------------------------------
		//			update SYSTEM_control
		//---------------------------------------------
		System_Status->Flash_Display_Fields_To_System_Control();
		//---------------------------------------------
		//			Send SYSTEM_control to DSP
		//---------------------------------------------
		My_Message("Sending MAIN config message...");
		if (real_time_thread.Send_System_Control_To_DSP() == false)
		{
			My_Message("Error MAIN configuring ARC1.");
		}
		My_Message("Finished MAIN config message...");
		this->timer_DSP_messages->Enabled = true;
	}
	// --------------------------------------------------
	//  B_FLASH_WRITE_Click
	//  Alon Slapak 22/12/2014
	// 	Description:	Send Write configuration to flash
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_FLASH_WRITE_Click(System::Object^  sender, System::EventArgs^  e)
	{
		My_Message(real_time_thread.Flash_Write());
	}
	// --------------------------------------------------
	//  B_MAIN_config_Click
	//  Alon Slapak 22/12/2014
	// 	Description:	Send read configuration to flash
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_FLASH_READ_Click(System::Object^  sender, System::EventArgs^  e)
	{
		My_Message(real_time_thread.Read_Flash());
	}
	// --------------------------------------------------
	//  B_FLASH_WRITE_TO_FILE_Click
	//  Alon Slapak 22/12/2014
	// 	Description:	save flash data to FILE
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_FLASH_WRITE_TO_FILE_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//---------------------------------------------
		//			update SYSTEM_control
		//---------------------------------------------
		System_Status->Flash_Display_Fields_To_System_Control();
		// --------------------------------------------
		//		structure to file
		// --------------------------------------------
		fstream file_handle = fstream(FLASH_VALUES_FILE_NAME, ios::out | ios::binary);
		if (file_handle.fail())
		{
			My_Message("Error opening FLASH file.");
			return;
		}
		file_handle.write((char*)System_Status->system_control_1, sizeof(T_SYSTEM_control_1));
		file_handle.close();
		My_Message("FLASH parameters were saved to file.");
	}
	// --------------------------------------------------
	//  B_FLASH_READ_FROM_FILE_Click
	//  Alon Slapak 22/12/2014
	// 	Description:	read flash data from FILE
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_FLASH_READ_FROM_FILE_Click(System::Object^  sender, System::EventArgs^  e)
	{
		fstream file_handle = fstream(FLASH_VALUES_FILE_NAME, ios::in | ios::binary);
		if (file_handle.fail())
		{
			My_Message("Error opening FLASH file.");
			return;
		}
		int	begin = (int)file_handle.tellg();
		file_handle.seekg(0, ios::end);
		int end = (int)file_handle.tellg();
		file_handle.seekg(0, ios::beg);
		//  if file length is equal to structure length
		if (end - begin == (sizeof(T_SYSTEM_control_1)))
		{
			file_handle.read((char*)System_Status->system_control_1, sizeof(T_SYSTEM_control_1));
		}
		else
		{
			My_Message("Error reading FLASH from file.");
			file_handle.close();
			return;
		}
		file_handle.close();
		Flash_Display_fields_to_Screen();
		My_Message("FLASH parameters were read from file.");
	}
	// --------------------------------------------------
	//  Free_Flight_MAP_Click
	//  Eran Rebenstock 25/10/2015
	// 	Description:	Set axis for map
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::Free_Flight_MAP_Click(System::Object^  sender, System::EventArgs^  e)
	{
		/*this->lbl_MAP_location->Text = "Free Flight";
		TOM_or_free_flight = 0;
		free_flight_lon = SYSTEM_status->SENSOR_data.Longitude - 0.015;
		free_flight_lat = SYSTEM_status->SENSOR_data.Latitude - 0.015;
		Plot_obstacles_map();*/
	}
	// --------------------------------------------------
	//  B_FLASH_RETRIVE_Click
	//  Alon Slapak 5/4/2015
	// 	Description:	Retrive flash fields from system status (shadow)
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_FLASH_RETRIVE_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//---------------------------------------------
		//	update SYSTEM_control:   Update Flash_fields from SYSTEM_control shadow
		//---------------------------------------------
		System_Status->Flash_System_Shadow_To_Display_Fields();
		Flash_Display_fields_to_Screen();
	}
	// --------------------------------------------------
	//  B_SENSOR_CONFIG_Click
	//  Alon Slapak 3/10/2014
	// 	Description:	Send config message to sensor
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_SENSOR_CONFIG_Click(System::Object^  sender, System::EventArgs^  e)
	{
		My_Message("Reseting SENSOR ...");
		if (real_time_thread.SENSOR_Config() == false)
		{
			My_Message("Error Reseting SENSOR self attitud.");
			return;
		}
		My_Message("Finished SENSOR reset...");
	}
	// --------------------------------------------------
	//  B_RESET_ARC_Click
	//  Eran Rebenstock 24/1/2016
	// 	Description:	Reset ARC1 DSPs & MCU
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_RESET_ARC_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//C_DSP_Communication		DSP_Communication;

		//----------------------------------------------------
		//		Message box  
		//----------------------------------------------------
		if (MessageBox::Show(this, gcnew String("Request ARC (DSPs & MCU) Reset"), "ARC1: Reset", MessageBoxButtons::OKCancel,
			MessageBoxIcon::Asterisk) == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}

		My_Message("Reseting ARC ...");
		if (real_time_thread.PC_Command_Reset_ARC() == false)
		{
			My_Message("Error Reseting ARC Card.");
			return;
		}
		My_Message("Finished ARC Reset Request, Please Stand By For Boot...");
	}
	// --------------------------------------------------
	//  B_OMR_Browse_Click
	//  Alon Slapak 3/10/2014
	// 	Description:	BROWSE for *.out file - Core0
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::B_OMR_Browse_Click(System::Object^  sender, System::EventArgs^  e)
	{
		B_folderBrowser_BUL->ShowDialog();
		//--------------------------------------
		//			Put value in ANALYSE_fields structure's field
		//--------------------------------------
		marshal_context ^ context = gcnew marshal_context();
		sprintf_s(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_OMR, context->marshal_as<const char*>(B_folderBrowser_BUL->SelectedPath));
		//--------------------------------------
		//			Put value in TEXTBOX
		//--------------------------------------
		this->B_Out_OMR->Text = gcnew String(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_OMR);
	}
	// --------------------------------------------------
	//  B_DET_Browse_Click
	//  Alon Slapak 29/1/2015
	// 	Description:	BROWSE for *.out file - Core1
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::B_DET_Browse_Click(System::Object^  sender, System::EventArgs^  e)
	{
		B_folderBrowser_BUL->ShowDialog();
		//--------------------------------------
		//			Put value in ANALYSE_fields structure's field
		//--------------------------------------
		marshal_context ^ context = gcnew marshal_context();
		sprintf_s(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_DET, context->marshal_as<const char*>(B_folderBrowser_BUL->SelectedPath));
		//--------------------------------------
		//			Put value in TEXTBOX
		//--------------------------------------
		this->B_Out_DET->Text = gcnew String(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_DET);
	}
	// --------------------------------------------------
	//  B_CHAB_Browse_Click
	//  Alon Slapak 3/10/2014
	// 	Description:	BROWSE for *.out file - Core2
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::B_CHAB_Browse_Click(System::Object^  sender, System::EventArgs^  e)
	{
		B_folderBrowser_BUL->ShowDialog();
		//--------------------------------------
		//			Put value in ANALYSE_fields structure's field
		//--------------------------------------
		marshal_context ^ context = gcnew marshal_context();
		sprintf_s(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_CHAB, context->marshal_as<const char*>(B_folderBrowser_BUL->SelectedPath));
		//--------------------------------------
		//			Put value in TEXTBOX
		//--------------------------------------
		this->B_Out_CHAB->Text = gcnew String(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_CHAB);
	}
	// --------------------------------------------------
	//  B_MCU_Browse_Click
	//  Alon Slapak 3/10/2014
	// 	Description:	BROWSE for *.out file - Core3
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::B_MCU_Browse_Click(System::Object^  sender, System::EventArgs^  e)
	{
		B_folderBrowser_BUL->ShowDialog();
		//--------------------------------------
		//			Put value in ANALYSE_fields structure's field
		//--------------------------------------
		marshal_context ^ context = gcnew marshal_context();
		sprintf_s(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_MCU, context->marshal_as<const char*>(B_folderBrowser_BUL->SelectedPath));
		//--------------------------------------
		//			Put value in TEXTBOX
		//--------------------------------------
		this->B_Out_MCU->Text = gcnew String(GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_MCU);
	}
	#pragma comment(lib, "Shell32.lib")    
	#include <ShellAPI.h> // without space also
	// --------------------------------------------------
	//  G_Upload_OMR_Click
	//  Alon Slapak 5/4/2015
	// 	Description:	BUL IMAGE UPLOAD
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::G_Upload_OMR_Click(System::Object^  sender, System::EventArgs^  e)
	{
		char								command[MAX_STRING_LENGTH];
		char								fileName[MAX_STRING_LENGTH];
		T_BUL_config						BUL_config;
		//----------------------------------------------------
		//		Message box  
		//----------------------------------------------------
		if (MessageBox::Show(this, gcnew String("Uploading Files to OMR"), "ARC1: Boot uploader", MessageBoxButtons::OKCancel,
			MessageBoxIcon::Asterisk) == System::Windows::Forms::DialogResult::Cancel)
		{
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//--------------------------
		// Copy *.out
		//--------------------------
		_chdir(BUL_MAD_FILES_OMR_PATH);
		sprintf_s(command, "DELTREE tmp");
		system(command);
		sprintf_s(command, "DELTREE images");
		system(command);
		sprintf_s(command, "copy %s\\ARC1_OMR_Core0\\Debug\\ARC1_OMR_Core0.out %s\\%s.out", GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_OMR, BUL_MAD_FILES_OMR_PATH, BUL_IMAGE_FILE_NAME_CORE0);
		system(command);
		sprintf_s(command, "copy %s\\ARC1_OMR_Core1\\Debug\\ARC1_OMR_Core1.out %s\\%s.out", GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_OMR, BUL_MAD_FILES_OMR_PATH, BUL_IMAGE_FILE_NAME_CORE1);
		system(command);
		sprintf_s(command, "copy %s\\ARC1_OMR_Core2\\Debug\\ARC1_OMR_Core2.out %s\\%s.out", GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_OMR, BUL_MAD_FILES_OMR_PATH, BUL_IMAGE_FILE_NAME_CORE2);
		system(command);
		//--------------------------
		// Create *.bin
		//--------------------------
		sprintf_s(command, "%s", "@rd /s /q tmp");
		system(command);
		if (system(NULL))
		{
			sprintf_s(command, "%s", "c:\\Python27\\python maptool.py maptoolCfg_C6678_bypass_prelink.json bypass-prelink");
			system(command);
		}
		else
		{
			My_Message("Cannot run MAD script");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//----------------------------------------------------
		//		find *.bin size  
		//----------------------------------------------------
		sprintf_s(fileName, "%s\\images\\%s.bin", BUL_MAD_FILES_OMR_PATH, BUL_IMAGE_FILE_NAME);
		fstream file_handle(fileName, std::ios::in | std::ios::binary);
		if (file_handle.fail())
		{
			My_Message("Error opening IMAGE file to upload.");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//-----------------------------------------
		// calculate number of bytes
		//-----------------------------------------
		int	begin_point = (int)file_handle.tellg();
		file_handle.seekg(0, ios::end);
		int end_point = (int)file_handle.tellg();
		file_handle.seekg(0, ios::beg);
		file_handle.close();
		//----------------------------------------------------
		//	Prepare config upload message 
		//----------------------------------------------------
		BUL_config.image_size = end_point - begin_point;
		BUL_config.target_dsp = 0;
		BUL_config.reset_after_upload = GUI_Status->disaplay_fields->MAINTENANCE_fields.reset_after_boot_upload;
		//----------------------------------------------------
		//	BOOT UPLOADER
		//----------------------------------------------------
		this->timer_DSP_messages->Enabled = false;
		if (real_time_thread.BOOT_UPLOADER(fileName, &BUL_config) == false)
		{
			My_Message("Error uploading BUL image to ARC1.");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		
		My_Message("Boot image was sent. Look at the BUL status...");
		this->timer_DSP_messages->Enabled = true;
	}
	// --------------------------------------------------
	//  G_Upload_DET_Click
	//  Alon Slapak 5/4/2015
	// 	Description:	BUL IMAGE UPLOAD
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::G_Upload_DET_Click(System::Object^  sender, System::EventArgs^  e)
	{
		char								command[MAX_STRING_LENGTH];
		char								fileName[MAX_STRING_LENGTH];
		T_BUL_config						BUL_config;
		//----------------------------------------------------
		//		Message box  
		//----------------------------------------------------
		if (MessageBox::Show(this, gcnew String("Uploading Files to DET"), "ARC1: Boot uploader", MessageBoxButtons::OKCancel,
			MessageBoxIcon::Asterisk) == System::Windows::Forms::DialogResult::Cancel)
		{
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//--------------------------
		// Copy *.out
		//--------------------------
		_chdir(BUL_MAD_FILES_DET_PATH);
		sprintf_s(command, "DELTREE tmp");
		system(command);
		sprintf_s(command, "DELTREE images");
		system(command);
		sprintf_s(command, "copy %s\\ARC1_DET_Core0\\Debug\\ARC1_DET_Core0.out %s\\%s.out", GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_DET, BUL_MAD_FILES_DET_PATH, BUL_IMAGE_FILE_NAME_CORE0);
		system(command);
		//--------------------------
		// Create *.bin
		//--------------------------
		sprintf_s(command, "%s", "@rd /s /q tmp");
		system(command);
		if (system(NULL))
		{
			sprintf_s(command, "%s", "c:\\Python27\\python maptool.py maptoolCfg_C6678_bypass_prelink.json bypass-prelink");
			system(command);
		}
		else
		{
			My_Message("Cannot run MAD script");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//----------------------------------------------------
		//		find *.bin size  
		//----------------------------------------------------
		sprintf_s(fileName, "%s\\images\\%s.bin", BUL_MAD_FILES_DET_PATH, BUL_IMAGE_FILE_NAME);
		fstream file_handle(fileName, std::ios::in | std::ios::binary);
		if (file_handle.fail())
		{
			My_Message("Error opening IMAGE file to upload.");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//-----------------------------------------
		// calculate number of bytes
		//-----------------------------------------
		int	begin_point = (int)file_handle.tellg();
		file_handle.seekg(0, ios::end);

		int end_point = (int)file_handle.tellg();
		file_handle.seekg(0, ios::beg);

		file_handle.close();
		//----------------------------------------------------
		//	Prepare config upload message 
		//----------------------------------------------------
		BUL_config.image_size = end_point - begin_point;
		BUL_config.target_dsp = 1;
		BUL_config.reset_after_upload = GUI_Status->disaplay_fields->MAINTENANCE_fields.reset_after_boot_upload;
		//----------------------------------------------------
		//	BOOT UPLOADER
		//----------------------------------------------------
		this->timer_DSP_messages->Enabled = false;
		if (real_time_thread.BOOT_UPLOADER(fileName, &BUL_config) == false)
		{
			My_Message("Error uploading BUL image to ARC1.");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		
		My_Message("Boot image was sent. Look at the BUL status...");
		this->timer_DSP_messages->Enabled = true;
	}
	// --------------------------------------------------
	//  G_Upload_CHAB_Click
	//  Alon Slapak 5/4/2015
	// 	Description:		Prepare file for NOR flash
	// 	Reference: 
	//				Execute exe files: http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044654269&id=1043284392
	//				Prepare "boot table format": http://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=0CCsQFjAC&url=http%3A%2F%2Fwww.deyisupport.com%2Fcfs-file.ashx%2F__key%2Fcommunityserver-discussions-components-files%2F53%2F0601.Booting-from-the-SPI-NOR-on-C6670.pdf&ei=pnssVITaL8iPPbuLgZgM&usg=AFQjCNGFKrS0IOq1NUWRINXU4piyB320qA&sig2=KxtMG8mBwMYKQ2YRC8WxQw&bvm=bv.76477589,d.bGQ
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::G_Upload_CHAB_Click(System::Object^  sender, System::EventArgs^  e)
	{
		char								command[MAX_STRING_LENGTH];
		char								fileName[MAX_STRING_LENGTH];
		T_BUL_config						BUL_config;
		//----------------------------------------------------
		//		Message box  
		//----------------------------------------------------
		if (MessageBox::Show(this, gcnew String("Uploading Files to CHAB"), "ARC1: Boot uploader", MessageBoxButtons::OKCancel,
			MessageBoxIcon::Asterisk) == System::Windows::Forms::DialogResult::Cancel)
		{
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//--------------------------
		// Copy *.out
		//--------------------------
		_chdir(BUL_MAD_FILES_CHAB_PATH);
		sprintf_s(command, "DELTREE tmp");
		system(command);
		sprintf_s(command, "DELTREE images");
		system(command);
		sprintf_s(command, "copy %s\\ARC1_CHAB_Core0\\Debug\\ARC1_CHAB_Core0.out %s\\%s.out", GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_CHAB, BUL_MAD_FILES_CHAB_PATH, BUL_IMAGE_FILE_NAME_CORE0);
		system(command);
		sprintf_s(command, "copy %s\\ARC1_CHAB_Core1\\Debug\\ARC1_CHAB_Core1.out %s\\%s.out", GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_CHAB, BUL_MAD_FILES_CHAB_PATH, BUL_IMAGE_FILE_NAME_CORE1);
		system(command);
		//--------------------------
		// Create *.bin
		//--------------------------
		sprintf_s(command, "%s", "@rd /s /q tmp");
		system(command);
		if (system(NULL))
		{
			sprintf_s(command, "%s", "c:\\Python27\\python maptool.py maptoolCfg_C6670_bypass_prelink.json bypass-prelink");
			system(command);
		}
		else
		{
			My_Message("Cannot run MAD script");
			this->timer_DSP_messages->Enabled = true;
			return;
		}

		//----------------------------------------------------
		//		find *.bin size  
		//----------------------------------------------------
		sprintf_s(fileName, "%s\\images\\%s.bin", BUL_MAD_FILES_CHAB_PATH, BUL_IMAGE_FILE_NAME);
		fstream file_handle(fileName, std::ios::in | std::ios::binary);
		if (file_handle.fail())
		{
			My_Message("Error opening IMAGE file to upload.");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//-----------------------------------------
		// calculate number of bytes
		//-----------------------------------------
		int	begin_point = (int)file_handle.tellg();
		file_handle.seekg(0, ios::end);
		int end_point = (int)file_handle.tellg();
		file_handle.seekg(0, ios::beg);
		file_handle.close();
		//----------------------------------------------------
		//	Prepare config upload message 
		//----------------------------------------------------
		BUL_config.image_size = end_point - begin_point;
		BUL_config.target_dsp = 2 + this->CHAB_BUL_Selector->SelectedIndex;
		BUL_config.reset_after_upload = GUI_Status->disaplay_fields->MAINTENANCE_fields.reset_after_boot_upload;
		//----------------------------------------------------
		//	BOOT UPLOADER
		//----------------------------------------------------
		this->timer_DSP_messages->Enabled = false;
		if (real_time_thread.BOOT_UPLOADER(fileName, &BUL_config) == false)
		{
			My_Message("Error uploading BUL image to ARC1.");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		My_Message("Boot image was sent. Look at the BUL status...");
		this->timer_DSP_messages->Enabled = true;
	}
	// --------------------------------------------------
	//  G_Upload_MCU_Click
	//  Ronen Globinsky 23/6/2015
	// 	Description:	BUL IMAGE UPLOAD
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void  MyForm::G_Upload_MCU_Click(System::Object^  sender, System::EventArgs^  e)
	{
		char						fileName[MAX_STRING_LENGTH];
		T_BUL_config				BUL_config;

		this->timer_DSP_messages->Enabled = false;
		//----------------------------------------------------
		//		Message box  
		//----------------------------------------------------
		if (MessageBox::Show(this, gcnew String("Uploading Files to MCU"), "ARC1: Boot uploader", MessageBoxButtons::OKCancel,
			MessageBoxIcon::Asterisk) == System::Windows::Forms::DialogResult::Cancel)
		{
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//----------------------------------------------------
		//		open boot image text file
		//----------------------------------------------------
		sprintf_s(fileName, "%s\\%s", GUI_Status->disaplay_fields->MAINTENANCE_fields.outFile_directory_MCU, BUL_IMAGE_FILE_NAME_MCU);
		fstream file_handle(fileName, std::ios::in);
		if (file_handle.fail())
		{
			My_Message("Error opening IMAGE file to upload.");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//-----------------------------------------
		// calculate number of bytes
		//-----------------------------------------
		int	begin_point = (int)file_handle.tellg();
		file_handle.seekg(0, ios::end);
		int end_point = (int)file_handle.tellg();
		file_handle.seekg(0, ios::beg);
		file_handle.close();
		//----------------------------------------------------
		//	Prepare config upload message 
		//----------------------------------------------------
		BUL_config.image_size = end_point - begin_point;
		BUL_config.target_dsp = 5;
		BUL_config.reset_after_upload = GUI_Status->disaplay_fields->MAINTENANCE_fields.reset_after_boot_upload;
		//----------------------------------------------------
		//	BOOT UPLOADER
		//----------------------------------------------------
		this->timer_DSP_messages->Enabled = false;
		if (real_time_thread.BOOT_UPLOADER(fileName, &BUL_config) == false)
		{
			My_Message("Error uploading BUL image to ARC1.");
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		My_Message("Boot image was sent. Look at the BUL status...");
		this->timer_DSP_messages->Enabled = true;
	}
	// --------------------------------------------------
	//  B_LOG_FOLDER_BROWSE_Click
	//  Alon Slapak 3/10/2014
	// 	Description:	BROWSE for LOG folder
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_LOG_FOLDER_BROWSE_Click(System::Object^  sender, System::EventArgs^  e)
	{
		B_SelectLOGfolder->ShowDialog();
		//--------------------------------------
		//			Put value in ANALYSE_fields structure's field
		//--------------------------------------
		marshal_context ^ context = gcnew marshal_context();
		sprintf_s(GUI_Status->disaplay_fields->DEBUG_fields.LOG_folder, context->marshal_as<const char*>(B_SelectLOGfolder->SelectedPath));
		//--------------------------------------
		//			Put value in TEXTBOX
		//--------------------------------------
		this->B_LOG_FOLDER->Text = gcnew String(GUI_Status->disaplay_fields->DEBUG_fields.LOG_folder);
	}
	// --------------------------------------------------
	//  Process_Snapshot
	//  Alon Slapak 12/3/2015
	// 	Description:	Take snapshot measurement and plot
	// 	Reference:	
	//	Input Value:	buffer for the received samples
	//  Return Value:	GOOD/FAULT
	// --------------------------------------------------
	int MyForm::Process_Snapshot()
	{
		char					LOG_Path[MAX_STRING_LENGTH];
		//----------------------------------------------
		//   Get the Experiment Directory and the filename
		//----------------------------------------------
		if (create_experiment_folder(LOG_Path) == FAULT)
		{
			return FAULT;
		}

		real_time_thread.Set_Matlab_Script_Name(B_MATLAB_script->Text);
		//TODO: fix this line with print of the message of the matlab
		while (real_time_thread.Process_Snapshot(LOG_Path) == false)
		{
			real_time_thread.Get_Message();
		}
		return GOOD;
	}
	// --------------------------------------------------
	//  IQ_correction
	//  Alon Slapak 15/4/2015
	// 	Description:	Multiplication of two complex numbers
	// 	Reference:	
	//	Input Value:	I1 + j * Q1, (dp_cplx)correction
	//  Return Value:	(dp_cplx) z 
	// --------------------------------------------------
	dp_cplx MyForm::IQ_correction(int16_t* I1, int16_t* Q1, dp_cplx correction)
	{
		dp_cplx		z;
		z.I = (double)(*I1) * correction.I - (double)(*Q1) * correction.Q;
		z.Q = (double)(*I1) * correction.Q + (double)(*Q1) * correction.I;
		return z;
	}
	// --------------------------------------------------
	//  complex_divisino
	//  Alon Slapak 16/4/2015
	// 	Description:	Division of two complex numbers
	// 	Reference:	
	//	Input Value:	dp_cplx		x,y
	//  Return Value:	dp_cplx		z
	// --------------------------------------------------
	dp_cplx MyForm::complex_division(dp_cplx x, dp_cplx y)
	{
		double	w;
		dp_cplx z;

		w = pow(y.I, 2) + pow(y.Q, 2);
		z.I = x.I * y.I + x.Q * y.Q;
		z.Q = -x.I * y.Q + x.Q * y.I;

		z.I = z.I / w;
		z.Q = z.Q / w;

		return z;
	}
	// --------------------------------------------------
	//  Process_obstacles_map
	//  Alon Slapak 31/3/2015
	// 	Description:	Take targets and polt obstacles map
	// 	Reference:	
	//	Input Value:	buffer for the received samples:
	//
	//			+---------------------------+
	//			|			RDM left		| + authentication	(start & end)
	//			+---------------------------+
	//			|			RDM right		| + authentication	(start & end)
	//			+---------------------------+
	//			| H/V/C	|		(double)
	//			+---------------------------+
	//			|			Targets			|
	//			+---------------------------+
	//			|			Trajectories	|			// updated by haim otacgi at 29/02/2016
	//			+---------------------------+
	//			| Authentication |		(int)	(start & end)
	//			+----------------+
	//
	//  Return Value:	GOOD/FAULT
	// --------------------------------
	{
		double				work_TX_mode;
		
		char*				p_targets;
		C_Data_Recording^	Data_Recording = gcnew C_Data_Recording;

		int16_t*			RDM_buffer_short;
		//int16_t*			CPI_buffer_short;

		uint32_t			RDM_size_int16;
		//uint32_t			CPI_size_int16;
		uint32_t			decimated_range_samples;

		uint32_t			*RDM_A_authentication_start, *RDM_B_authentication_start, *Targets_authentication_start;
		uint32_t			*RDM_A_authentication_end, *RDM_B_authentication_end, *Targets_authentication_end;
		
		T_Trajectories		Trajectories;
		uint32_t			*Point_To_Trajectories;		// added by haim otachi
		//-----------------------------------------------
		//		Parsing the data
		//-----------------------------------------------
		decimated_range_samples = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples / System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation;
		RDM_size_int16 = decimated_range_samples *  System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler * 2 * 2 * 2 * 2; // I/Q, L/R, H/V
		//CPI_size_int16 = decimated_range_samples *  (System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers >> FFTC_ZERO_PADDING_MUL) * 2 * 2 * 2;
		
		RDM_buffer_short = (int16_t*)pBuffer + 2;																			// RDM
		p_targets = (char*)(pBuffer + sizeof(double) + RDM_size_int16 * sizeof(int16_t) + sizeof(uint32_t) * (2 + 3));		// Targets
		work_TX_mode = *((double*)(p_targets - sizeof(double) - sizeof(uint32_t)));											// H/V/C	flag
		//-----------------------------------------------
		//					RDM A
		//-----------------------------------------------
		RDM_A_authentication_start = (uint32_t*)pBuffer;
		RDM_A_authentication_end = (uint32_t*)(&RDM_buffer_short[(RDM_size_int16 / 2)]);
		//-----------------------------------------------
		//					RDM B
		//-----------------------------------------------
		RDM_B_authentication_start = (uint32_t*)(&RDM_buffer_short[(RDM_size_int16 / 2) + 2]);
		RDM_B_authentication_end = (uint32_t*)(&RDM_buffer_short[(4 + RDM_size_int16)]);
		//-----------------------------------------------
		//					Targets
		//-----------------------------------------------
		Targets_authentication_start = (uint32_t*)(p_targets - sizeof(uint32_t));
		Targets_authentication_end = (uint32_t*)(p_targets + sizeof(T_TARGETS_data));
		//CPI_buffer_short = (int16_t*)(p_targets + sizeof(T_TARGETS_data) + 2 * sizeof(uint32_t) + sizeof(uint32_t) + (RDM_size_int16 / 2));
		//-----------------------------------------------
		//					Trajectories 
		//-----------------------------------------------
		Point_To_Trajectories = (uint32_t*)((uint8_t*)Targets_authentication_end + 2 * sizeof(uint32_t) + decimated_range_samples * System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler * 2 * 4);

		if ((*Targets_authentication_start == *Targets_authentication_end) && (*RDM_A_authentication_end == *RDM_A_authentication_start) && 
			(*RDM_B_authentication_end == *RDM_B_authentication_start) && (*RDM_A_authentication_start != 1) && (*RDM_A_authentication_start != local_data_authentication)
			&& (*Targets_authentication_start == *RDM_A_authentication_start) && (*RDM_A_authentication_start == *RDM_B_authentication_start))
		{
			local_data_authentication = *RDM_A_authentication_start;
			if (RDM_P != NULL)
			{
				free(RDM_P);
			}
			//-----------------------------------------------
			//		read  Targets from the Ethernet
			//-----------------------------------------------
			memcpy((char*)TARGETS_data, p_targets, sizeof(T_TARGETS_data));
			Targets_Sort_by_Reliability(TARGETS_data);
			target_updated = true;
			//-----------------------------------------------
			//		read  Trajectories from the Ethernet
			//-----------------------------------------------
			memcpy((char*)&Trajectories, Point_To_Trajectories, sizeof(T_Trajectories));
			//-----------------------------------------------
			//		Update data recording  of radar struct
			//-----------------------------------------------
			Data_Recording->set_Data_Recording(System_Status->system_control_0->SENSOR_data, *TARGETS_data, Trajectories);
			//---------------------------------------------------
			//		Add new detection to data base
			//---------------------------------------------------
			Radar_Viewer.Add_Radar_Post(Data_Recording);
			//-----------------------------------------------
			//			plot targets on 'MAP' panel screen
			//-----------------------------------------------			
			Radar_Viewer.Plot_Step_Position_Of_Radar();
			//-------------------------------------
			//	Clear data structure of the radar
			//-------------------------------------
			Radar_Viewer.Clear_Radar_Viewer();
			//-----------------------------------------------
			//		plot  RDM
			//-----------------------------------------------
			Plot_RDM((Byte*)(p_targets + sizeof(T_TARGETS_data) - sizeof(double) - sizeof(uint32_t)), TARGETS_data);
			//-----------------------------------------------
			//		Save recording data in file
			//-----------------------------------------------
			if (System_Status->Monitor_Operation_Recording == true)
			{
				//-----------------------------------------------
				//		Save:		SENSOR_data
				//-----------------------------------------------
				data_recording_file_handle->write((char*)(&(System_Status->system_control_0->SENSOR_data)), sizeof(T_SENSOR_data));
				//-----------------------------------------------
				//		Save:		Calibration Coefficients
				//-----------------------------------------------
				data_recording_file_handle->write((char*)(&(System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction)), sizeof(dp_cplx) * 4);
				//-----------------------------------------------
				//		Save:		TARGETS_data
				//-----------------------------------------------
				data_recording_file_handle->write((char*)(TARGETS_data), sizeof(T_TARGETS_data));
				//-----------------------------------------------
				//		Save:		RDM CH A
				//-----------------------------------------------
				data_recording_file_handle->write((char*)RDM_buffer_short, RDM_size_int16);
				//-----------------------------------------------
				//		Save:		RDM CH B
				//-----------------------------------------------
				data_recording_file_handle->write((char*)&RDM_buffer_short[(RDM_size_int16 / 2) + 4], RDM_size_int16);
				//-----------------------------------------------
				//		Save:		CPI CH A
				//-----------------------------------------------
				//data_recording_file_handle->write((char*)CPI_buffer_short, CPI_size_int16);
				//-----------------------------------------------
				//		Save:		CPI CH B
				//-----------------------------------------------
				//data_recording_file_handle->write((char*)&CPI_buffer_short[(CPI_size_int16 / 2) + 4], CPI_size_int16); 
				//-----------------------------------------------
				//		Save:		Trajectories
				//-----------------------------------------------
				data_recording_file_handle->write((char*)Point_To_Trajectories, sizeof(T_Trajectories));
			}
		}
		Radar_Viewer.Restart_Real_Time();
		-
	//  Targets_Sort_by_Reliability
	//  Alon Slapak		30/3/2015
	// 	Description:	Sort targets by the their reliability
	//					changed by Haim Otachi:		25/01/2016
	//							1.  T_TARGET --> T_PNI.
	//							2.  Targets  --> Targets_array.
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Targets_Sort_by_Reliability(T_TARGETS_data* pTARGETS_data)
	{
		int			i, j;
		//T_TARGET	temp;

		T_PNI		temp;

		// --------------------------------------------------
		//		Remove targets below minimal range
		// --------------------------------------------------
		for (i = 0; i < pTARGETS_data->Targets_number; i++)
		{
			//if (pTARGETS_data->Targets[i].Range < DISAPLAY_fields->FLASH_fields.DET_algorithms.Minimum_range_meter)
			if (pTARGETS_data->Targets_array[i].Range < 1)//200)
			{
				pTARGETS_data->Targets_array[i].Target_reliability = 0;
			}
		}
		// --------------------------------------------------
		//		Sort targets by rliability
		// --------------------------------------------------
		for (i = 0; i < pTARGETS_data->Targets_number - 1; i++)
		{
			for (j = i + 1; j < pTARGETS_data->Targets_number; j++)
			{
				if (pTARGETS_data->Targets_array[i].Target_reliability < pTARGETS_data->Targets_array[j].Target_reliability)
				{
					temp = (T_PNI)pTARGETS_data->Targets_array[i];
					(T_PNI)pTARGETS_data->Targets_array[i] = (T_PNI)pTARGETS_data->Targets_array[j];
					(T_PNI)pTARGETS_data->Targets_array[j] = temp;
				}
			}
		}

	}
	// --------------------------------------------------
	//  B_PROBE_TEST_Click
	//  Ronen Globinsky		13/1/2015
	// 	Description:	send command to DSP to run rx test using antenna probe
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_PROBE_TEST_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//----------------------------------------------
		//   Check the experiment folder validity
		//----------------------------------------------
		if (System::IO::Directory::Exists(gcnew String(GUI_Status->disaplay_fields->DEBUG_fields.LOG_folder)) == false)
		{
			//----------------------------------------------------
			//		Message box  
			//----------------------------------------------------
			marshal_context ^ context = gcnew marshal_context();
			if (MessageBox::Show(this, gcnew String("Error: LOG directory does not exist."), "ARC1", MessageBoxButtons::OKCancel,
				MessageBoxIcon::Asterisk) == System::Windows::Forms::DialogResult::Cancel)
			{
				return;
			}
		}
		//----------------------------------------------
		//  Start SNAPSHOT
		//----------------------------------------------
		this->timer_DSP_messages->Enabled = false;
		My_Message("Probe test start...");
		//----------------------------------------------
		//  SNAPSHOT_descriptor 
		//----------------------------------------------
		System_Status->SNAPSHOT_descriptor->SNAPSHOT_type = SNAPSHOT_PROBE_TEST;
		System_Status->SNAPSHOT_descriptor->SNAPSHOT_number_of_samples = System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_PROBE.Buffer_length * 8;
		//-------------------------------------------
		//		Sending COMMAND_GET_SNAPSHOT
		//-------------------------------------------
		My_Message("Sending GET SNAPSHOT command...");
		if (real_time_thread.Sending_Command_Get_SNAPSHOT() == false)
		{
			My_Message("Error sending GET SNAPSHOT command...");
		}
		else
		{
			My_Message("Waiting for data ready...");
			System_Status->Monitor_Operation_mode = OPERATION_SNAPSHOT;
		}
		//--------------------------------
		//		Signal get snapshot to timer
		//--------------------------------
		this->timer_DSP_messages->Enabled = true;
	}
	// --------------------------------------------------
	//  B_SNAPSHOT_Click
	//  Alon Slapak 3/10/2014
	// 	Description:	Take snapshot measurement
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_SNAPSHOT_Click(System::Object^  sender, System::EventArgs^  e)
	{
		uint32_t					buffer_size;
		uint32_t					decimated_range_samples;

		this->timer_DSP_messages->Enabled = false;
		//----------------------------------------------
		//  SNAPSHOT_descriptor 
		//----------------------------------------------
		try
		{
			decimated_range_samples = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples / System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation;
			System_Status->SNAPSHOT_descriptor->SNAPSHOT_type = (E_SNAPSHOT_type)B_SNAPSHOT_TYPE->SelectedIndex;
			switch (System_Status->SNAPSHOT_descriptor->SNAPSHOT_type)
			{
			case SNAPSHOT_CPI:
			{
				buffer_size = System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.Buffer_length * System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers;
				break;
			}
			case SNAPSHOT_PRE_FFT:
			{
				buffer_size = decimated_range_samples * System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler * 2;
				break;
			}
			case SNAPSHOT_RDM:
			{
				buffer_size = decimated_range_samples * System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler * 2;
				break;
			}
			}
			System_Status->SNAPSHOT_descriptor->SNAPSHOT_number_of_samples = buffer_size * 8;
			//-------------------------------------------
			//		Sending COMMAND_GET_SNAPSHOT
			//-------------------------------------------
			My_Message("Sending GET SNAPSHOT command...");
			if (real_time_thread.Sending_Command_Get_SNAPSHOT() == false)
			{
				this->timer_DSP_messages->Enabled = true;
				My_Message("Error sending GET SNAPSHOT command...");
				return;
			}
			//-------------------------------------------
			//		Wait for data ready
			//-------------------------------------------
			My_Message("Waiting for data ready...");
			//--------------------------------
			//		Signal get snapshot to timer
			//--------------------------------
			System_Status->Monitor_Operation_mode = OPERATION_SNAPSHOT;

			this->timer_DSP_messages->Enabled = true;
		}
		catch (Exception^ ex) { ex->Message; }
	}
	// --------------------------------------------------
	//  create_experiment_folder
	//  Ronen Globinsky 3/3/2015
	// 	Description:	Create a folder to the experiment
	// 	Reference: 
	//	Input Value:	pointer to experiment dirctory (for return)
	//  Return Value:	GOOD/FAULT
	// --------------------------------------------------
	int MyForm::create_experiment_folder(char* experiment_path)
	{
		char						temp_string_1[MAX_STRING_LENGTH];
		char						temp_string_2[MAX_STRING_LENGTH];
		fstream						file_handle;
		int							experiment_number;
		SYSTEMTIME					mytime;
		//----------------------------------------------
		//   Check the experiment folder validity
		//----------------------------------------------
		if (System::IO::Directory::Exists(gcnew String(GUI_Status->disaplay_fields->DEBUG_fields.LOG_folder)) == false)
		{
			//----------------------------------------------------
			//		Message box  
			//----------------------------------------------------
			marshal_context ^ context = gcnew marshal_context();
			if (MessageBox::Show(this, gcnew String("Error: LOG directory does not exist."), "ARC1", MessageBoxButtons::OKCancel,
				MessageBoxIcon::Asterisk) == System::Windows::Forms::DialogResult::Cancel)
			{
				return FAULT;
			}
		}
		//----------------------------------------------
		//		open Experiment Number file
		//----------------------------------------------
		sprintf_s(temp_string_1, "%s\\%s", GUI_Status->disaplay_fields->DEBUG_fields.LOG_folder, EXPERIMENT_NUMBER_FILE);
		file_handle.open(temp_string_1, ios::in);
		if (file_handle)
		{
			file_handle >> temp_string_2;
			experiment_number = atoi(temp_string_2);
			experiment_number = experiment_number + 1;
			file_handle.close();
		}
		else
		{
			experiment_number = 1;
		}
		file_handle.open(temp_string_1, ios::out);
		if (file_handle.fail())
		{
			My_Message("Error updating experiment number file.");
			return FAULT;
		}
		file_handle << experiment_number << std::endl;
		file_handle.close();
		//------------------------------------------------
		// Create Experiment directory
		//------------------------------------------------
		GetLocalTime(&mytime);
		sprintf_s(experiment_path, MAX_STRING_LENGTH, "%s\\Exp_%d_%d-%d-%d_%d-%d-%d", GUI_Status->disaplay_fields->DEBUG_fields.LOG_folder, experiment_number, mytime.wYear, mytime.wMonth, mytime.wDay, mytime.wHour, mytime.wMinute, mytime.wSecond);
		int err_Makedir = CreateDirectoryA(experiment_path, NULL);
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			My_Message("Directory already exist.");
		}
		if (GetLastError() == ERROR_PATH_NOT_FOUND)
		{
			My_Message("Error path for results directory not found.");
			this->timer_DSP_messages->Enabled = true;
			return FAULT;
		}
		return GOOD;
	}
	// --------------------------------------------------
	//  B_CALIBRATOR_CALIBRATE_Click
	//  Alon Slapak 3/10/2014
	// 	Description:	Calibrate target
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_CALIBRATOR_CALIBRATE_Click(System::Object^  sender, System::EventArgs^  e)
	{
		My_Message("Calibrating external target ...");
		//---------------------------------------------
		//	check if Calibrate target relative to calibrator and return an appropriate message
		//---------------------------------------------
		My_Message(real_time_thread.If_Calibrator_Calibrate());
	}
	// --------------------------------------------------
	//  B_PROBE_RESET_Click
	//  Alon Slapak 14/4/2015
	// 	Description:	Reset Rx_correction factors to 1.
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_PROBE_RESET_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->timer_DSP_messages->Enabled = false;
		//---------------------------------------------
		//			update SYSTEM_control
		//---------------------------------------------
		System_Status->Flash_Display_Fields_To_System_Control();
		//---------------------------------------------
		//			Reset Rx correction factors to 1 + 0i = complex 1
		//---------------------------------------------
		System_Status->system_control_1->Rx_correction[0].I = 1;
		System_Status->system_control_1->Rx_correction[0].Q = 0;
		System_Status->system_control_1->Rx_correction[1].I = 1;
		System_Status->system_control_1->Rx_correction[1].Q = 0;
		System_Status->system_control_1->Rx_correction[2].I = 1;
		System_Status->system_control_1->Rx_correction[2].Q = 0;
		System_Status->system_control_1->Rx_correction[3].I = 1;
		System_Status->system_control_1->Rx_correction[3].Q = 0;
		//---------------------------------------------
		//			Send SYSTEM_control to DSP
		//---------------------------------------------
		My_Message("Sending MAIN config message...");
		if (real_time_thread.Send_System_Control_To_DSP())
		{
			My_Message("Error MAIN configuring ARC1.");
		}
		My_Message("Finished MAIN config message...");
		this->timer_DSP_messages->Enabled = true;
	}
	// --------------------------------------------------
	//  B_CALIBRATOR_RESET_Click
	//  Alon Slapak 14/4/2015
	// 	Description:	Reset Rx_correction factors to 1.
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_CALIBRATOR_RESET_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->timer_DSP_messages->Enabled = false;
		//---------------------------------------------
		//			update SYSTEM_control
		//---------------------------------------------
		System_Status->Flash_Display_Fields_To_System_Control();
		//---------------------------------------------
		//			Reset Rx correction factors to 1 + 0i = complex 1
		//---------------------------------------------
		System_Status->system_control_1->Calibrator_correction[0].I = 1;
		System_Status->system_control_1->Calibrator_correction[0].Q = 0;
		System_Status->system_control_1->Calibrator_correction[1].I = 1;
		System_Status->system_control_1->Calibrator_correction[1].Q = 0;
		System_Status->system_control_1->Calibrator_correction[2].I = 1;
		System_Status->system_control_1->Calibrator_correction[2].Q = 0;
		System_Status->system_control_1->Calibrator_correction[3].I = 1;
		System_Status->system_control_1->Calibrator_correction[3].Q = 0;
		//---------------------------------------------
		//			Send SYSTEM_control to DSP
		//---------------------------------------------
		My_Message("Sending MAIN config message...");
		if (real_time_thread.Send_System_Control_To_DSP() == false)
		{
			My_Message("Error MAIN configuring ARC1.");
		}
		My_Message("Finished MAIN config message...");
		this->timer_DSP_messages->Enabled = true;
	}
	// --------------------------------------------------
	//  B_PROBE_CALIBRATE_Click
	//  Alon Slapak 3/10/2014
	// 	Description:	Calibrate target
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::B_PROBE_CALIBRATE_Click(System::Object^  sender, System::EventArgs^  e)
	{
		My_Message("Calibrating external target ...");
		//---------------------------------------------
		//	check if Calibrate target relative to probe and return an appropriate message
		//---------------------------------------------
		My_Message(real_time_thread.If_Probe_Calibrate());
	}
	// --------------------------------------------------
	//  W_RECORDING_START_Click
	//  Alon Slapak		18/12/2014
	// 	Description:	start recording data to log file
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::W_RECORDING_START_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//----------------------------------------------
		//   Open file
		//----------------------------------------------
		if (System_Status->Monitor_Operation_Recording == false)
		{
			if (Data_recording_start() == GOOD)
			{
				Path = gcnew String("images\\Media_Controls_Record_2_icon_32_pixel.png");
				image = gcnew Bitmap(Path, true);
				W_DATA_RECORDING->Image = image;
				System_Status->Monitor_Operation_Recording = true;
			}
		}
		else
		{
			if (Data_recording_stop() == GOOD)
			{
				Path = gcnew String("images\\Media_Controls_Record_icon_32_pixel.png");
				image = gcnew Bitmap(Path, true);
				W_DATA_RECORDING->Image = image;
				System_Status->Monitor_Operation_Recording = false;
			}
		}
	}
	// --------------------------------------------------
	//  Data_recording_start
	//  Alon Slapak		18/12/2014
	// 	Description:	start recording data to log file
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	GOOD/FAULT
	// --------------------------------------------------
	int MyForm::Data_recording_start()
	{
		char		experiment_path[MAX_STRING_LENGTH];
		char		experiment_file[MAX_STRING_LENGTH];
		fstream		file_handle;

		//----------------------------------------------
		//   Get the Experiment Directory
		//----------------------------------------------
		if (create_experiment_folder(experiment_path) == FAULT)
		{
			return FAULT;
		}
		//------------------------------------------------
		// Save LOG file
		//------------------------------------------------
		Save_experiment_data_file(experiment_path);
		//------------------------------------------------
		// open recording file
		//------------------------------------------------
		sprintf_s(experiment_file, "%s\\%s", experiment_path, DATA_RECORDING_FILE);
		data_recording_file_handle->open(experiment_file, ios::out | ios::binary);
		if (data_recording_file_handle->fail())
		{
			My_Message("Error opening file for recording.");
			return FAULT;
		}
		//------------------------------------------------
		// Message to screen
		//------------------------------------------------
		My_Message("Recording...");
		return GOOD;
	}
	// --------------------------------------------------
	//  Data_recording_stop
	//  Alon Slapak		18/12/2014
	// 	Description:	stop recording data to log file
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	GOOD/FAULT
	// --------------------------------------------------
	int MyForm::Data_recording_stop()
	{
		//------------------------------------------------
		// Close file
		//------------------------------------------------
		if (data_recording_file_handle != NULL)
		{
			data_recording_file_handle->close();
		}
		//------------------------------------------------
		// Message to screen
		//------------------------------------------------
		My_Message("Stopped recording");
		return GOOD;
	}
	// --------------------------------------------------
	//  G_START_WORK_CIRC_Click
	//  Alon Slapak		18/10/2014
	// 	Description:	Send start opperation to radar, and open displays
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::G_START_WORK_CIRC_Click(System::Object^  sender, System::EventArgs^  e)
	{
		local_authentication = 0;
		local_data_authentication = 0;
		//--------------------------------
		//		"Start work" to radar
		//--------------------------------
		if (real_time_thread.PC_Command_Start_Work_CIRC() == false)
		{
			My_Message("Error START WORK ARC1.");
		}
		else
		{
			//--------------------------------
			//		Open displays
			//--------------------------------
			Open_aux_view(LEGEND_CIRCULAR);
			//--------------------------------
			//		Prepare main form legend
			//--------------------------------
			this->B_SCOPE_H_LEFT->Series["Single1"]->Points->Clear();
			this->B_SCOPE_H_LEFT->Series["Average1"]->Points->Clear();
			this->B_SCOPE_V_LEFT->Series["Single1"]->Points->Clear();
			this->B_SCOPE_V_LEFT->Series["Average1"]->Points->Clear();
			this->B_SCOPE_H_RIGHT->Series["Single1"]->Points->Clear();
			this->B_SCOPE_H_RIGHT->Series["Average1"]->Points->Clear();
			this->B_SCOPE_V_RIGHT->Series["Single1"]->Points->Clear();
			this->B_SCOPE_V_RIGHT->Series["Average1"]->Points->Clear();

			this->B_SCOPE_H_LEFT->Series["Single2"]->Points->Clear();
			this->B_SCOPE_H_LEFT->Series["Average2"]->Points->Clear();
			this->B_SCOPE_V_LEFT->Series["Single2"]->Points->Clear();
			this->B_SCOPE_V_LEFT->Series["Average2"]->Points->Clear();
			this->B_SCOPE_H_RIGHT->Series["Single2"]->Points->Clear();
			this->B_SCOPE_H_RIGHT->Series["Average2"]->Points->Clear();
			this->B_SCOPE_V_RIGHT->Series["Single2"]->Points->Clear();
			this->B_SCOPE_V_RIGHT->Series["Average2"]->Points->Clear();
			//--------------------------------
			//		Disable other buttons
			//--------------------------------
			this->B_MAIN_config->Enabled = false;
			this->B_CALIBRATOR_CALIBRATE->Enabled = false;
			this->B_PROBE_CALIBRATE->Enabled = false;
			this->B_SNAPSHOT->Enabled = false;
			this->W_START_WORK_CIRC->Enabled = false;
			this->B_PROBE_TEST->Enabled = false;
			this->B_PROBE_RESET->Enabled = false;
			this->B_CALIBRATOR_RESET->Enabled = false;
			this->B_FLASH_READ->Enabled = false;
			this->B_FLASH_WRITE->Enabled = false;
			//--------------------------------
			//	Disable 'Re Flight' button
			//--------------------------------
			this->B_RE_FLIGHT->Enabled = false;
			//--------------------------------
			//		Enable recording
			//--------------------------------
			this->W_DATA_RECORDING->Enabled = true;
			//--------------------------------
			//		Signal stop work to timer
			//--------------------------------
			System_Status->Monitor_Operation_mode = OPERATION_WORK;
			//--------------------------------
			//		Message to screen
			//--------------------------------
			My_Message("Start working...");
		}
	}
	// --------------------------------------------------
	//  G_START_WORK_HV_Click
	//  Alon Slapak		6/1/2018
	// 	Description:	Send start opperation to radar, and open displays
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::G_START_WORK_HV_Click(System::Object^  sender, System::EventArgs^  e)
	{
		local_authentication = 0;
		//--------------------------------
		//		configure pulse type
		//--------------------------------
		if (RB_BARKER_PULSE->Checked == true)
		{
			System_Status->system_control_1->TxRx_control_WORK.Profile_AD9910A = 1;
			System_Status->system_control_1->TxRx_control_WORK.Profile_AD9910B = 1;
		}
		else if (RB_SINGLE_PULSE->Checked == true)
		{
			System_Status->system_control_1->TxRx_control_WORK.Profile_AD9910A = 7;
			System_Status->system_control_1->TxRx_control_WORK.Profile_AD9910B = 7;
		}
		//-------------------------------------------
		//		Sending config
		//-------------------------------------------
		My_Message("Sending MAIN config message...");
		if (real_time_thread.Send_System_Control_To_DSP() == false)
		{
			My_Message("Error MAIN configuring ARC1.");
		}
		My_Message("Finished MAIN config message...");
		Sleep(500);
		//--------------------------------
		//		"Start work" to radar
		//--------------------------------
		if (real_time_thread.PC_Command_Start_Work_HV() == FAULT)
		{
			My_Message("Error START WORK ARC1.");
		}
		else
		{
			//--------------------------------
			//		Open displays
			//--------------------------------
			Open_aux_view(LEGEND_HV);
			//--------------------------------
			//		Prepare main form legend
			//--------------------------------
			B_SCOPE_H_LEFT->Series["Single1"]->Points->Clear();
			B_SCOPE_H_LEFT->Series["Average1"]->Points->Clear();
			B_SCOPE_V_LEFT->Series["Single1"]->Points->Clear();
			B_SCOPE_V_LEFT->Series["Average1"]->Points->Clear();
			B_SCOPE_H_RIGHT->Series["Single1"]->Points->Clear();
			B_SCOPE_H_RIGHT->Series["Average1"]->Points->Clear();
			B_SCOPE_V_RIGHT->Series["Single1"]->Points->Clear();
			B_SCOPE_V_RIGHT->Series["Average1"]->Points->Clear();

			B_SCOPE_H_LEFT->Series["Single2"]->Points->Clear();
			B_SCOPE_H_LEFT->Series["Average2"]->Points->Clear();
			B_SCOPE_V_LEFT->Series["Single2"]->Points->Clear();
			B_SCOPE_V_LEFT->Series["Average2"]->Points->Clear();
			B_SCOPE_H_RIGHT->Series["Single2"]->Points->Clear();
			B_SCOPE_H_RIGHT->Series["Average2"]->Points->Clear();
			B_SCOPE_V_RIGHT->Series["Single2"]->Points->Clear();
			B_SCOPE_V_RIGHT->Series["Average2"]->Points->Clear();
			//--------------------------------
			//		Disable other buttons
			//--------------------------------
			B_MAIN_config->Enabled = false;
			B_CALIBRATOR_CALIBRATE->Enabled = false;
			B_PROBE_CALIBRATE->Enabled = false;
			B_SNAPSHOT->Enabled = false;
			W_START_WORK_CIRC->Enabled = false;
			B_PROBE_TEST->Enabled = false;
			B_PROBE_RESET->Enabled = false;
			B_CALIBRATOR_RESET->Enabled = false;
			B_FLASH_READ->Enabled = false;
			B_FLASH_WRITE->Enabled = false;
			//--------------------------------
			//		Enable recording
			//--------------------------------
			W_DATA_RECORDING->Enabled = true;
			//--------------------------------
			//		Signal start work to timer
			//--------------------------------
			System_Status->Monitor_Operation_mode = OPERATION_WORK;
			//--------------------------------
			//		Message to screen
			//--------------------------------
			My_Message("Start working...");
		}
	}
	// --------------------------------------------------
	//  G_STOP_WORK_Click
	//  Alon Slapak		18/10/2014
	// 	Description:	Send stop opperation to radar
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::G_STOP_WORK_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//--------------------------------
		//		Signal stop work to timer
		//--------------------------------
		System_Status->Monitor_Operation_mode = OPERATION_OFF;
		//--------------------------------
		//		Stop radar
		//--------------------------------
		if (real_time_thread.PC_Command_Stop_Work() == false)
		{
			My_Message("Error START WORK ARC1.");
		}
		else
		{
			//--------------------------------
			//		Close  Scope
			//--------------------------------
			delete scope;
			//--------------------------------
			//		Stop recording and disable recording
			//--------------------------------
			if (System_Status->Monitor_Operation_Recording == true)
			{
				if (Data_recording_stop() == GOOD)
				{
					//--------------------------------
					//	we return the image of the 'Recording' button to the default image of data recording
					//--------------------------------
					Path = gcnew String("images\\Media_Controls_Record_icon_32_pixel.png");
					image = gcnew Bitmap(Path, true);
					W_DATA_RECORDING->Image = image;
					//--------------------------------
					//	We change the status of the 'Monitor_Operation_Recording'
					//--------------------------------
					System_Status->Monitor_Operation_Recording = false;
				}
			}
			W_DATA_RECORDING->Enabled = false;
			//--------------------------------
			//		Enable other buttons
			//--------------------------------
			B_MAIN_config->Enabled = true;
			B_CALIBRATOR_CALIBRATE->Enabled = true;
			B_PROBE_CALIBRATE->Enabled = true;
			B_SNAPSHOT->Enabled = true;
			W_START_WORK_CIRC->Enabled = true;
			B_PROBE_TEST->Enabled = true;
			B_PROBE_RESET->Enabled = true;
			B_CALIBRATOR_RESET->Enabled = true;
			B_FLASH_READ->Enabled = true;
			B_FLASH_WRITE->Enabled = true;
			//--------------------------------
			//	Enable 'Re Flight' button
			//--------------------------------
			this->B_RE_FLIGHT->Enabled = true;
			//--------------------------------
			//		Message to screen
			//--------------------------------
			My_Message("Stop working...");
		}
	}
	// --------------------------------------------------
	//  Plot_probe_test
	//  Alon Slapak		16/4/2015
	// 	Description:	plot the probe_test results
	// 	Reference:		
	//	Input Value:	pointer to buffer
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Plot_probe_test(int16_t* pBuffer_short)
	{
		dp_cplx		Probe_correction[4];
		dp_cplx		IQ_corrected;
		int i;
		//----------------------------------------------
		//   calculate the Probe_correction factors
		// Note: in the DSP, Rx_correction = Calibrator_correction/Probe_correction
		//  therefore: Probe_correction = Calibrator_correction/Rx_correction
		//----------------------------------------------
		for (i = 0; i < 4; i++)
		{
			Probe_correction[i] = complex_division(System_Status->system_control_0->SYSTEM_control_shadow.Rx_correction[i], System_Status->system_control_0->SYSTEM_control_shadow.Calibrator_correction[i]);
		}
		//----------------------------------------------
		//   Clear buffers
		//----------------------------------------------
		B_PROBE_TEST_PLOT->Series["LH_I"]->Points->Clear();
		B_PROBE_TEST_PLOT->Series["LH_Q"]->Points->Clear();
		B_PROBE_TEST_PLOT->Series["LV_I"]->Points->Clear();
		B_PROBE_TEST_PLOT->Series["LV_Q"]->Points->Clear();
		B_PROBE_TEST_PLOT->Series["RH_I"]->Points->Clear();
		B_PROBE_TEST_PLOT->Series["RH_Q"]->Points->Clear();
		B_PROBE_TEST_PLOT->Series["RV_I"]->Points->Clear();
		B_PROBE_TEST_PLOT->Series["RV_Q"]->Points->Clear();
		//----------------------------------------------
		//   Plotting probe test
		//----------------------------------------------
		for (i = 0; i < (int)System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_PROBE.Buffer_length; i++)
		{
			IQ_corrected = IQ_correction(&pBuffer_short[i * 4 + 0], &pBuffer_short[i * 4 + 1], Probe_correction[0]);
			B_PROBE_TEST_PLOT->Series["LH_I"]->Points->AddXY(i, IQ_corrected.I / 32768);
			B_PROBE_TEST_PLOT->Series["LH_Q"]->Points->AddXY(i, IQ_corrected.Q / 32768);
			IQ_corrected = IQ_correction(&pBuffer_short[i * 4 + 2], &pBuffer_short[i * 4 + 3], Probe_correction[1]);
			B_PROBE_TEST_PLOT->Series["LV_I"]->Points->AddXY(i, IQ_corrected.I / 32768);
			B_PROBE_TEST_PLOT->Series["LV_Q"]->Points->AddXY(i, IQ_corrected.Q / 32768);
			IQ_corrected = IQ_correction(&pBuffer_short[4 * System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_PROBE.Buffer_length + i * 4 + 0], &pBuffer_short[4 * System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_PROBE.Buffer_length + i * 4 + 1], Probe_correction[2]);
			B_PROBE_TEST_PLOT->Series["RH_I"]->Points->AddXY(i, IQ_corrected.I / 32768);
			B_PROBE_TEST_PLOT->Series["RH_Q"]->Points->AddXY(i, IQ_corrected.Q / 32768);
			IQ_corrected = IQ_correction(&pBuffer_short[4 * System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_PROBE.Buffer_length + i * 4 + 2], &pBuffer_short[4 * System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_PROBE.Buffer_length + i * 4 + 3], Probe_correction[3]);
			B_PROBE_TEST_PLOT->Series["RV_I"]->Points->AddXY(i, IQ_corrected.I / 32768);
			B_PROBE_TEST_PLOT->Series["RV_Q"]->Points->AddXY(i, IQ_corrected.Q / 32768);
		}
		My_Message("Plot probe test done.");
	}
	// --------------------------------------------------
	//  Plot_RDM
	//  Alon Slapak		1/4/2015
	// 	Description:	plot the Range-Doppler maps
	// 	Reference:		
	//	Input Value:	pointer to buffer
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Plot_RDM(Byte* pBuffer_short, T_TARGETS_data* pTARGETS_data)
	{
		int			line_length;
		int			selected_RDM;

		int			number_of_lines = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler * 2;
		int			number_of_raws = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples / System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation;
		int			pic_size = number_of_lines * number_of_raws;

		Byte*		pic_H_L = (Byte*)pBuffer_short			/*malloc(pic_size)*/;
		Byte*		pic_V_L = pic_H_L + pic_size			/*(Byte*)malloc(pic_size)*/;
		Byte*		pic_H_R = pic_V_L + pic_size			/*(Byte*)malloc(pic_size)*/;
		Byte*		pic_V_R = pic_H_R + pic_size			/*(Byte*)malloc(pic_size)*/;

		Bitmap^		bmp_H_L = gcnew Bitmap(number_of_raws, number_of_lines, number_of_raws, System::Drawing::Imaging::PixelFormat::Format8bppIndexed, IntPtr(&pic_H_L[0]));
		Bitmap^		bmp_V_L = gcnew Bitmap(number_of_raws, number_of_lines, number_of_raws, System::Drawing::Imaging::PixelFormat::Format8bppIndexed, IntPtr(&pic_V_L[0]));
		Bitmap^		bmp_H_R = gcnew Bitmap(number_of_raws, number_of_lines, number_of_raws, System::Drawing::Imaging::PixelFormat::Format8bppIndexed, IntPtr(&pic_H_R[0]));
		Bitmap^		bmp_V_R = gcnew Bitmap(number_of_raws, number_of_lines, number_of_raws, System::Drawing::Imaging::PixelFormat::Format8bppIndexed, IntPtr(&pic_V_R[0]));
		//-------------------------------------------------------
		//		find the length of line
		//-------------------------------------------------------
		line_length = number_of_raws * 4;
		//-------------------------------------------------------
		//		Initialize the debug_timer 4 and 5
		//-------------------------------------------------------
		for_debug_timer_4 = clock();
		for_debug_timer_5 = clock();
		//------------------------------------------------
		//				Plot RDMs
		//------------------------------------------------
		B_RDM_H_L->SizeMode = PictureBoxSizeMode::StretchImage;
		B_RDM_V_L->SizeMode = PictureBoxSizeMode::StretchImage;
		B_RDM_H_R->SizeMode = PictureBoxSizeMode::StretchImage;
		B_RDM_V_R->SizeMode = PictureBoxSizeMode::StretchImage;

		bmp_H_L->RotateFlip(RotateFlipType::RotateNoneFlipY);
		bmp_V_L->RotateFlip(RotateFlipType::RotateNoneFlipY);
		bmp_H_R->RotateFlip(RotateFlipType::RotateNoneFlipY);
		bmp_V_R->RotateFlip(RotateFlipType::RotateNoneFlipY);

		B_RDM_H_L->Image = dynamic_cast<Image^>(bmp_H_L);
		B_RDM_V_L->Image = dynamic_cast<Image^>(bmp_V_L);
		B_RDM_H_R->Image = dynamic_cast<Image^>(bmp_H_R);
		B_RDM_V_R->Image = dynamic_cast<Image^>(bmp_V_R);

		for_debug_timer_6 = clock();
		wchar_t text_buffer[200] = { 0 }; //temporary buffer
		swprintf(text_buffer, _countof(text_buffer), L"    --- RDM plot Elapsed time: %f   %f \n", double(for_debug_timer_5 - for_debug_timer_4) / CLOCKS_PER_SEC, double(for_debug_timer_6 - for_debug_timer_5) / CLOCKS_PER_SEC); // convert
		OutputDebugStringW(text_buffer);
		//------------------------------------------------
		//			Plot single RDM
		//------------------------------------------------
		PB_RDM->SizeMode = PictureBoxSizeMode::StretchImage;
		////default RDM = H left;
		PB_RDM->Image = dynamic_cast<Image^>(bmp_H_L);
		Lbl_RDM->Text = "Left H";

		selected_RDM = lbox_select_RDM->SelectedIndex;
		switch (selected_RDM)
		{
			case 0:
				PB_RDM->Image = dynamic_cast<Image^>(bmp_H_L);
				Lbl_RDM->Text = "Left H";
				break;
			case 1:
				PB_RDM->Image = dynamic_cast<Image^>(bmp_V_L);
				Lbl_RDM->Text = "Left V";
				break;
			case 2:
				PB_RDM->Image = dynamic_cast<Image^>(bmp_H_R);
				Lbl_RDM->Text = "Right H";
				break;
			case 3:
				PB_RDM->Image = dynamic_cast<Image^>(bmp_V_R);
				Lbl_RDM->Text = "Right V";
				break;
		}
	}
	// --------------------------------------------------
	//  plot_A_SCOPE
	//  Alon Slapak		31/3/2015
	// 	Description:	show DOPPLER record on the A_scope
	// 	Reference:		
	//	Input Value:	Samples_buffer		: pointer to data bufer
	//					buffer_size_doubles : number of doubles in a line
	//					start_range			: first tic on x-axis
	//					end_range			: last tic on x-axis
	//					step_range			: step between tics
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::plot_A_SCOPE(double *Samples_buffer, int buffer_size_doubles, int start_range, int end_range, int step_range)
	{
		int			i;
		double		range;
		double		y_offset = 20 * log10(32767);
		//-------------------------------------------
		//		Drop to scope
		//-------------------------------------------
		this->B_SCOPE_H_LEFT->Series["Average1"]->Points->Clear();
		this->B_SCOPE_V_LEFT->Series["Average1"]->Points->Clear();
		this->B_SCOPE_H_RIGHT->Series["Average1"]->Points->Clear();
		this->B_SCOPE_V_RIGHT->Series["Average1"]->Points->Clear();
		for (i = start_range; i < end_range; i++)
		{
			range = (i * System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation - start_range) * step_range;
			this->B_SCOPE_H_LEFT->Series["Average1"]->Points->AddXY(range, 10 * log10(Samples_buffer[0 * buffer_size_doubles + i] + DBL_MIN) - y_offset);
			this->B_SCOPE_V_LEFT->Series["Average1"]->Points->AddXY(range, 10 * log10(Samples_buffer[1 * buffer_size_doubles + i] + DBL_MIN) - y_offset);
			this->B_SCOPE_H_RIGHT->Series["Average1"]->Points->AddXY(range, 10 * log10(Samples_buffer[2 * buffer_size_doubles + i] + DBL_MIN) - y_offset);
			this->B_SCOPE_V_RIGHT->Series["Average1"]->Points->AddXY(range, 10 * log10(Samples_buffer[3 * buffer_size_doubles + i] + DBL_MIN) - y_offset);
		}
	}
	// --------------------------------------------------
	//  Save_experiment_data_file
	//  Alon Slapak		8/1/2015
	// 	Description:	Save experiemtn data to file in experiment directory
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Save_experiment_data_file(char*  directory_path)
	{
		char			file_name[MAX_STRING_LENGTH];
		fstream			file_handle;
		SYSTEMTIME		mytime;

		GetLocalTime(&mytime);
		// --------------------------------------------------
		//		Open file
		// --------------------------------------------------
		sprintf_s(file_name, "%s\\%s", directory_path, EXPERIMENT_DATA_FILE);
		file_handle.open(file_name, ios::out);
		if (file_handle.fail())
		{
			My_Message("Error opening experiment data file for write.");
			return;
		}
		file_handle << "Date" << '\t' << mytime.wYear << "-" << mytime.wMonth << "-" << mytime.wDay << '\n';
		file_handle << "Time" << '\t' << mytime.wHour << "-" << mytime.wMinute << "-" << mytime.wSecond << '\n';
		file_handle << "Profile_AD9910A " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.Profile_AD9910A << '\n';
		file_handle << "Profile_AD9910B " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.Profile_AD9910B << '\n';
		file_handle << "chip_length_AD9910A " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.chip_length_AD9910A << '\n';
		file_handle << "chip_length_AD9910B " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.chip_length_AD9910B << '\n';
		file_handle << "IF_SELECT_TX1 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.IF_SELECT_TX1 << '\n';
		file_handle << "IF_SELECT_TX2 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.IF_SELECT_TX2 << '\n';
		file_handle << "IF_SELECT_TX3 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.IF_SELECT_TX3 << '\n';
		file_handle << "IF_SELECT_PROBE " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.IF_SELECT_PROBE << '\n';
		file_handle << "IO_UPDATE_rate " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.IO_UPDATE_rate << '\n';
		file_handle << "TX1_ON " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.TX1_ON << '\n';
		file_handle << "TX2_ON " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.TX2_ON << '\n';
		file_handle << "TX3_ON " << '\t' <<  System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.TX3_ON << '\n';
		file_handle << "PROBE_ON " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.PROBE_ON << '\n';
		file_handle << "TX_LO_TR " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.TX_LO_TR << '\n';
		file_handle << "ANT_SAMPLE_SELECT " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.ANT_SAMPLE_SELECT << '\n';
		file_handle << "ATTN_TX1 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.ATTN_TX1 << '\n';
		file_handle << "ATTN_TX2 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.ATTN_TX2 << '\n';
		file_handle << "ATTN_TX3 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.ATTN_TX3 << '\n';
		file_handle << "ATTN_RX1 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.ATTN_RX1 << '\n';
		file_handle << "ATTN_RX2 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.ATTN_RX2 << '\n';
		file_handle << "ATTN_RX3 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.ATTN_RX3 << '\n';
		file_handle << "ATTN_RX4 " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.ATTN_RX4 << '\n';
		file_handle << "AD9910_Set_aux_dac_A " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.AD9910_Set_aux_dac_A << '\n';
		file_handle << "AD9910_Set_aux_dac_B " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.AD9910_Set_aux_dac_B << '\n';
		file_handle << "Buffer_length " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.Buffer_length << '\n';
		file_handle << "FIFO_length " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.FIFO_length << '\n';
		file_handle << "IO_UPDATE_ON " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.TxRx_control_WORK.IO_UPDATE_ON << '\n';

		file_handle << "OFFSET_samples " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.OFFSET_samples << '\n';
		file_handle << "RANGE_samples " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples << '\n';
		file_handle << "Number_of_buffers " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers << '\n';
		file_handle << "Number_of_RDMs " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_RDMs << '\n';
		file_handle << "Target_detection_1st_threshold " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Target_detection_1st_threshold << '\n';
		file_handle << "Target_detection_2nd_threshold " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Target_detection_2nd_threshold << '\n';
		file_handle << "Maximal_doppler " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler << '\n';
		file_handle << "Range_decimation " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation << '\n';
		file_handle << "AGC_threshold " << '\t' << System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.AGC_threshold << '\n';

		file_handle.close();
	}
	// --------------------------------------------------
	//  Open_aux_view
	//  Alon Slapak		11/1/2015
	// 	Description:	Open Auxliliary view
	// 	Reference:		
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Open_aux_view(E_LEGEND_MODE legend_mode) {}
	// --------------------------------------------------
	//  System_Health_status
	//  Eran Rebenstock		13/7/2015
	// 	Description:	Check If The system is up
	//  TODO: Move this function to the 'Real Time Thread' class
	// 	Reference:
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::System_Health_status()
	{
		int32_t status = 0;
		int32_t temp_status = 0;
		int32_t dsp_status = 0;
		int32_t peripherals_status = 0;

		if (this->B_Ethernet_Status->BackColor == System::Drawing::Color::Lime)
		{
			//-------------------------------------------
			//					DSP
			//------------------------------------------- 
			dsp_status  = (System_Status->system_control_0->ARC_status.STATUS_OMR) | (System_Status->system_control_0->ARC_status.STATUS_DET) | (System_Status->system_control_0->ARC_status.STATUS_MCU);
			dsp_status |= (System_Status->system_control_0->ARC_status.STATUS_CHA) | (System_Status->system_control_0->ARC_status.STATUS_CHB);
			//-------------------------------------------
			//				PERIPHERALS
			//------------------------------------------- 
			peripherals_status  = (System_Status->system_control_0->ARC_status.PERIPHERALS_AD6655_A) | (System_Status->system_control_0->ARC_status.PERIPHERALS_AD6655_B);
			peripherals_status |= (System_Status->system_control_0->ARC_status.PERIPHERALS_FPGA_A)   | (System_Status->system_control_0->ARC_status.PERIPHERALS_FPGA_B);
			peripherals_status |= (System_Status->system_control_0->ARC_status.PERIPHERALS_LMK04828) | (System_Status->system_control_0->ARC_status.PERIPHERALS_LMK01000);
			peripherals_status |= (System_Status->system_control_0->ARC_status.PERIPHERALS_AD9910_A) | (System_Status->system_control_0->ARC_status.PERIPHERALS_AD9910_B);
			//-------------------------------------------
			//				TEMPERATURE
			//------------------------------------------- 
			temp_status  = (System_Status->system_control_0->ARC_status.MCU_TEMPERATURE > 65) | (System_Status->system_control_0->ARC_status.UCD9222_DET_temperature_internal > 90) | (System_Status->system_control_0->ARC_status.UCD9222_DET_temperature_external > 90);
			temp_status |= (System_Status->system_control_0->ARC_status.UCD9222_CHA_temperature_internal > 90) | (System_Status->system_control_0->ARC_status.UCD9222_CHA_temperature_external > 90);
			status = temp_status | dsp_status | peripherals_status;

			if (!status)
			{
				// If system is OK
				B_System_Health_Status->BackColor = System::Drawing::Color::Lime;
				B_message->BackColor = System::Drawing::Color::White;
				Temp_valid = 0;
			}
			else
			{
				// If system is faulty
				B_System_Health_Status->BackColor = System::Drawing::Color::Red;
				if (temp_status)
				{
					if (Temp_valid >= 100)
					{
						B_message->BackColor = System::Drawing::Color::Red;
						B_message->Text = "FAULT Temprature!";
					}
					else
					{
						B_System_Health_Status->BackColor = System::Drawing::Color::Lime;
						Temp_valid++;
					}
				}
				else
				{
					Temp_valid = 0;
					B_message->BackColor = System::Drawing::Color::White;
					if (dsp_status)
					{
						if (System_Status->system_control_0->ARC_status.STATUS_DET)
						{
							B_message->Text = "FAULT DET!";
						}
						else
						{
							if (System_Status->system_control_0->ARC_status.STATUS_CHA)
							{
								B_message->Text = "FAULT CHA!";
							}
							else
							{
								if (System_Status->system_control_0->ARC_status.STATUS_CHB)
								{
									B_message->Text = "FAULT CHB!";
								}
								else
								{
									if (System_Status->system_control_0->ARC_status.STATUS_MCU)
									{
										B_message->Text = "FAULT MCU!";
									}
								}
							}
						}
					}
					else
					{
						if (peripherals_status)
						{
							B_message->Text = "FAULT Peripherals!";
						}
					}
				}
			}
		}
		else
		{
			// If system is faulty
			B_System_Health_Status->BackColor = System::Drawing::Color::Red;
		}
	}
	// --------------------------------------------------
	//  Etherent_link_ok
	//  Alon Slapak					10/2/2015
	//  Updated by Haim Otachi		11/01/2016
	// 	Description:	Check the ethernet speed and availability and update the states machine
	// 	Reference:		https://msdn.microsoft.com/en-us/library/system.net.networkinformation.networkinterface.getipproperties(v=vs.110).aspx?cs-save-lang=1&cs-lang=cpp#code-snippet-1
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::Etherent_status_state_machine()
	{
		switch (System_Status->Ethernet_link_status)
		{
			case ETHERNET_OFF:
			{
				//----------------------------------------------------------------------------------------
				//  Ethernet status red & Disable status fields
				//----------------------------------------------------------------------------------------
				B_Ethernet_Status->Text = L"";
				B_Ethernet_Status->BackColor = System::Drawing::Color::Red;
				B_GROUP_STATUS->Enabled = false;
				B_GROUP_SENSOR->Enabled = false;
				B_GROUP_RF->Enabled = false;
				B_GROUP_STATE_MACHINES->Enabled = false;
				B_GROUP_ALGORITHMS->Enabled = false;
				B_GROUP_FREES->Enabled = false;
				//----------------------------------------------------------------------------------------
				//  Get all Computer networks
				//----------------------------------------------------------------------------------------
				if (real_time_thread.Initialize_Computer_Networks() == false)
				{
					break;
				}
				//----------------------------------------------------------------------------------------
				//  Scan for the ETHERNET link
				//----------------------------------------------------------------------------------------
				B_Ethernet_Status->Text = real_time_thread.Scan_ETHERNET_Link();
				//----------------------------------------------------------------------------------------
				// Indicate link ok (> 100Mb)
				//----------------------------------------------------------------------------------------
				if (System_Status->Ethernet_speed >= 100000000)
				{
					this->B_Ethernet_Status->BackColor = System::Drawing::Color::Orange;
				}
				break;
			}
		case ETHERNET_PHY:
		{
			//---------------------------------------
			//	Check if could to read SYSTEM status from DSP
			//  Updated by Haim Otachi at 10/01/2015
			//  the 'DSP_connect()' function was transferred to 'Real_Time_Thread' class
			//---------------------------------------			
			if (real_time_thread.Socket_Is_Available() == GOOD)
			{
				this->B_Ethernet_Status->BackColor = System::Drawing::Color::Lime;
				B_GROUP_STATUS->Enabled = true;
				B_GROUP_SENSOR->Enabled = true;
				B_GROUP_RF->Enabled = true;
				B_GROUP_STATE_MACHINES->Enabled = true;
				B_GROUP_ALGORITHMS->Enabled = true;
				B_GROUP_FREES->Enabled = true;
				//-----------------------------------------------
				//		SYSTEM_status --> screen
				//-----------------------------------------------
				Update_Sensor_Controls();
				Update_Status_Controls();
				Update_Debug_Tab_Controls();
				Update_BUL_Controls();
			}			
			break;
	}	
		case ETHERNET_GOOD:
			break;
		
		}
	}
	// --------------------------------------------------
	//  timer_DSP_messages_Tick
	//  Alon Slapak					17/10/2014
	//  Updated by Haim Otachi		10/01/2016
	// 	Description:				Main timer task to present data continuously.
	//								This is the Real Time Thread of the class according to UML and operated by another class that simulates a "Thread".
	// 	Reference:	
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void MyForm::timer_DSP_messages_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		string						Error_message;		
		double*						Error_line = NULL;
		char*						buffer;
		
		uint32_t					buffer_size_char;
		uint32_t					decimated_range_samples;

		for_debug_timer_1 = clock();
		//-----------------------------------------------
		//	Disable timer
		//-----------------------------------------------
		this->timer_DSP_messages->Enabled = false;
		Etherent_status_state_machine();
		System_Health_status();
		if (System_Status->Ethernet_link_status != ETHERNET_GOOD)
		{
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		//-----------------------------------------------
		//		DSP --> SYSTEM_status
		//-----------------------------------------------
		if (real_time_thread.Read_SYSTEM_Status() == FAULT)
		{
			System_Status->Ethernet_link_status = ETHERNET_OFF;
			this->timer_DSP_messages->Enabled = true;
			return;
		}
		else
		{
			this->B_Ethernet_Status->BackColor = System::Drawing::Color::Lime;
		}
		//-----------------------------------------------
		//		SYSTEM_status --> screen
		//-----------------------------------------------
		if (System_Status->Ethernet_message_status == GOOD)
		{
			Update_Sensor_Controls();
			Update_Status_Controls();
			Update_BUL_Controls();
		}
		//-------------------------------------------
		//-------------------------------------------
		//
		//		OPERATION_SNAPSHOT
		//
		//-------------------------------------------
		//-------------------------------------------
		if ((System_Status->Monitor_Operation_mode == OPERATION_SNAPSHOT))
		{
			if (System_Status->system_control_0->DATA_download.PC_data_authentication > 0)
			{
				//-------------------------------------------
				//	read SNAPSHOT data (short) 
				//-------------------------------------------
				if (real_time_thread.Read_SNAPSHOT() == false)
				{
					My_Message("Error loading snapshot data from ARC1.");
					this->timer_DSP_messages->Enabled = true;
					return;
				}
				//-------------------------------------------
				//	process SNAPSHOT data 
				//-------------------------------------------
				if (System_Status->SNAPSHOT_descriptor->SNAPSHOT_type != SNAPSHOT_PROBE_TEST)
				{
					Process_Snapshot();
				}
				else
				{
					Plot_probe_test(real_time_thread.Get_Buffer_Short());
				}
				//-------------------------------------------
				//	clean up
				//-------------------------------------------
				System_Status->Operation_retry_count = 0;
				System_Status->Monitor_Operation_mode = OPERATION_OFF;
			}
			else
			{
				System_Status->Operation_retry_count++;
				this->timer_DSP_messages->Enabled = true;
				if (System_Status->Operation_retry_count >= MAX_RETRY_NUMBER)
				{
					My_Message("Error reading snapshot authentication from ARC1.");
					System_Status->Monitor_Operation_mode = OPERATION_OFF;
					System_Status->Operation_retry_count = 0;
				}
			}
		}
		//-------------------------------------------
		//-------------------------------------------
		//
		//		OPERATION_WORK
		//
		//-------------------------------------------
		//-------------------------------------------
		if ((System_Status->Monitor_Operation_mode == OPERATION_WORK))
		{
			if (System_Status->system_control_0->DATA_download.PC_data_authentication != local_authentication)
			{
				local_authentication = System_Status->system_control_0->DATA_download.PC_data_authentication;
				//-------------------------------------------
				//	read WORK data
				//			+---------------------------+
				//			|			RDM left		| + authentications (start & end)
				//			+		-               -	+	
				//			|			RDM right		| + authentication	(start & end)
				//			+---------------------------+
				//			| H/V/C	|		(double)
				//			+---------------------------+
				//			|			Targets			|
				//			+---------------------------+
				//			| Authentication |		(int)	(start & end)
				//			+----------------+
				//-------------------------------------------
				decimated_range_samples = System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples / System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation;
				buffer_size_char = sizeof(T_TARGETS_data) + sizeof(double) + decimated_range_samples * System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler * 2 * sizeof(short) * 2 * 2 * 2 + sizeof(uint32_t) * (3 + 3);
				buffer_size_char += sizeof(uint32_t) + decimated_range_samples * System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Maximal_doppler * 2 * 4;
				//buffer_size_char += ((System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.RANGE_samples / System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Range_decimation) * (System_Status->system_control_0->SYSTEM_control_shadow.DET_algorithms.Number_of_buffers >> FFTC_ZERO_PADDING_MUL) * sizeof(int16_t) * 2 * 2 + 2 * sizeof(uint32_t)) * 2;

				double size = sizeof(T_Trajectories);
				buffer_size_char += sizeof(T_Trajectories);

				buffer = (char*)malloc(buffer_size_char);
				if (real_time_thread.Read_Obstacles_Map(buffer, buffer_size_char) == false)
				{
					My_Message("Error loading data from ARC1.");
					System_Status->Monitor_Operation_mode = OPERATION_OFF;
					free(buffer);
					this->timer_DSP_messages->Enabled = true;
					return;
				}
				//-------------------------------------------
				//	process OBSTACLES MAP data
				//-------------------------------------------
				Process_obstacles_map(buffer);
				free(buffer);
				//-------------------------------------------
				//	Clean up
				//-------------------------------------------
				System_Status->Operation_retry_count = 0;

				for_debug_timer_2 = clock();
				wchar_t text_buffer[200] = { 0 }; //temporary buffer
				swprintf(text_buffer, _countof(text_buffer), L"*** Elapsed time: 2 = %f \n", double(for_debug_timer_2 - for_debug_timer_1) / CLOCKS_PER_SEC); // convert
				OutputDebugStringW(text_buffer);
			}
			else
			{
				System_Status->Operation_retry_count++;
				this->timer_DSP_messages->Enabled = true;
				if (System_Status->Operation_retry_count >= MAX_RETRY_NUMBER)
				{
					My_Message("Error reading snapshot authentication from ARC1.");
					System_Status->Monitor_Operation_mode = OPERATION_OFF;
					System_Status->Operation_retry_count = 0;
				}
			}
		}
		for_debug_timer_3 = clock();
		wchar_t text_buffer[200] = { 0 }; //temporary buffer
		swprintf(text_buffer, _countof(text_buffer), L"Elapsed time: 3 = %f \n", double(for_debug_timer_3 - for_debug_timer_1) / CLOCKS_PER_SEC); // convert
		OutputDebugStringW(text_buffer);
		//-----------------------------------------------
		//	Enable timer
		//-----------------------------------------------
		this->timer_DSP_messages->Enabled = true;
	}
	// --------------------------------------------------
	//  B_VIEWER_PANEL_Paint  
	//  Haim Otachi     21/09/2015
	// 	Description:	Plot TOM after Paint event
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void MyForm::B_MAP_PANEL_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		Radar_Viewer.Plot_Step_Position_Of_Radar();
	}
	void MyForm::B_DETECTIONS_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		Radar_Viewer.Add_Radar_Post();
		Radar_Viewer.Set_Show_Detections(B_DETECTIONS->Checked);
		Radar_Viewer.Clear_Radar_Viewer();
	}
	void MyForm::B_TRAJECTORIES_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		Radar_Viewer.Add_Radar_Post();
		Radar_Viewer.Set_Show_Trajectories(B_TRAJECTORIES->Checked);
		Radar_Viewer.Clear_Radar_Viewer();
	}
	#pragma endregion

	#pragma region To check with Alon
	//// --------------------------------------------------
	////  W_RECORDING_PLAY_Click
	////  Alon Slapak		18/12/2014
	//// 	Description:	play recording data from log file
	//// 	Reference:		
	////	Input Value:	
	////  Return Value:	
	//// --------------------------------------------------
	//void MyForm::W_RECORDING_PLAY_Click(System::Object^  sender, System::EventArgs^  e)
	//{
	//	char		file_name[MAX_STRING_LENGTH];
	//	double		time_stamp, old_time_stamp;
	//	int			time_delay_mSec;
	//	//------------------------------------------------
	//	// Ask for log file name
	//	//------------------------------------------------
	//	this->B_SelectLogFile->InitialDirectory = gcnew String(DISAPLAY_fields->DEBUG_fields.LOG_folder);
	//	B_SelectLogFile->ShowDialog();
	//	marshal_context ^ context = gcnew marshal_context();
	//	sprintf_s(file_name, context->marshal_as<const char*>(B_SelectLogFile->FileName));
	//	//------------------------------------------------
	//	// Message to screen
	//	//------------------------------------------------
	//	My_Message("Playing data");
	//	//------------------------------------------------
	//	// Read file
	//	//------------------------------------------------
	//	fstream file_handle = fstream(file_name, ios::in | ios::binary);
	//	int	begin = (int)file_handle.tellg();
	//	file_handle.seekg(0, ios::end);
	//	int end = (int)file_handle.tellg();
	//	file_handle.seekg(0, ios::beg);
	//	if (end - begin <= 0)
	//	{
	//		My_Message("Error opening LOG file.");
	//	}
	//	else
	//	{
	//		//--------------------------------
	//		//		Open displays
	//		//--------------------------------
	//		//				if (Recording_display_traces == 1)
	//		//				{
	//		scope = gcnew Scope;
	//		scope->Show();
	//		//}
	//		//if (Recording_display_polar == 1)
	//		//{
	//		//	scope = gcnew Scope;
	//		//	scope->set_Number_Of_Buffers(MAIN_config_message->Number_of_buffers);
	//		//	scope->set_profile(MAIN_config_message->Profile_AD9910A);
	//		//	scope->Show();
	//		//}
	//		//------------------------------------------------
	//		// play file
	//		//------------------------------------------------
	//		file_handle.read((char*)(&old_time_stamp), sizeof(double)); 
	//		file_handle.seekg(0, ios::beg);
	//		while (!file_handle.eof())
	//		{
	//			//-------------------------------------------
	//			//		Read data
	//			//-------------------------------------------
	//			file_handle.read((char*)(&time_stamp), sizeof(double));
	//			file_handle.read((char*)Recording_samples_buffer, RAW_DATA_SIZE);
	//			//-------------------------------------------
	//			//		Wait to mimic real time display
	//			//-------------------------------------------
	//			time_delay_mSec = (int)((time_stamp - old_time_stamp) * 1000);
	//			Sleep(time_delay_mSec);			// wait [miliSeconds]
	//			old_time_stamp = time_stamp;
	//			//-------------------------------------------
	//			//		Drop to scope
	//			//-------------------------------------------
	//			//scope->plot_data((double*)Recording_samples_buffer, A_SCOPE_MIN_RANGE, A_SCOPE_MAX_RANGE, A_SCOPE_STEP_RANGE);
	//			//scope->show_message(time_stamp.ToString());
	//			scope->Refresh();
	//		}
	//		//--------------------------------
	//		//		Close  Scope
	//		//--------------------------------
	//		delete scope;
	//		//------------------------------------------------
	//		// Close file
	//		//------------------------------------------------
	//		file_handle.close();
	//	}
	//}

	// --------------------------------------------------
	//  plot_data
	//  Alon Slapak		17/12/2014
	// 	Description:	show data on the scope
	// 	Reference:		
	//	Input Value:	Samples_buffer		: pointer to data bufer
	//					start_range			: first tic on x-axis
	//					end_range			: last tic on x-axis
	//					step_range			: step between tics
	//					Single_correction	: bias (+ in dB) for single time record
	//					Average_correction	: bias (+ in dB) for average time record
	//  Return Value:	
	// --------------------------------------------------
	//void	MyForm::plot_data_2(double *Samples_buffer, int start_range, int end_range, int step_range)
	//{
	//	int			i;
	//	double		range;
	//	//-------------------------------------------
	//	//		Drop to scope
	//	//-------------------------------------------
	//	this->B_SCOPE_H_LEFT->Series["Single2"]->Points->Clear();
	//	this->B_SCOPE_H_LEFT->Series["Average2"]->Points->Clear();
	//	this->B_SCOPE_V_LEFT->Series["Single2"]->Points->Clear();
	//	this->B_SCOPE_V_LEFT->Series["Average2"]->Points->Clear();
	//	this->B_SCOPE_H_RIGHT->Series["Single2"]->Points->Clear();
	//	this->B_SCOPE_H_RIGHT->Series["Average2"]->Points->Clear();
	//	this->B_SCOPE_V_RIGHT->Series["Single2"]->Points->Clear();
	//	this->B_SCOPE_V_RIGHT->Series["Average2"]->Points->Clear();
	//	for (i = start_range; i < end_range; i++)
	//	{
	//		range = (i - start_range) * step_range;
	//		this->B_SCOPE_H_LEFT->Series["Average2"]->Points->AddXY(range, 10 * log10(Samples_buffer[4 * TIME_RECORD_LENGTH + i]));
	//		this->B_SCOPE_V_LEFT->Series["Average2"]->Points->AddXY(range, 10 * log10(Samples_buffer[5 * TIME_RECORD_LENGTH + i]));
	//		this->B_SCOPE_H_RIGHT->Series["Average2"]->Points->AddXY(range, 10 * log10(Samples_buffer[6 * TIME_RECORD_LENGTH + i]));
	//		this->B_SCOPE_V_RIGHT->Series["Average2"]->Points->AddXY(range, 10 * log10(Samples_buffer[7 * TIME_RECORD_LENGTH + i]));
	//	}
	//}

	#pragma endregion
}