#pragma once
#include "ARC1_Technician.h"
#include "C_DSP_Communication.h"
#include "C_SYSTEM_status.h"
#include "T_BUL_config.h"
#include "C_Radar_Viewer.h"
#include "Real_Time_Thread.h"
#include "C_Lab_Calibrator.h"
#include <stdio.h>
#include <msclr\marshal.h>
#include "C_Lab_ROT2PROG.h"
#include "Scope.h"
#include "engine.h"
#include <time.h>


namespace ARC1_Technician
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Threading;
	using namespace msclr::interop;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace DSP_Communication;
	using namespace Radar_Viewer;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		public:
			MyForm();
		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~MyForm();

		#pragma region Windows Form Controls
		private: System::Windows::Forms::Button^  B_FLASH_READ_FROM_FILE;
		private: System::Windows::Forms::Button^  B_FLASH_WRITE_TO_FILE;
		private: System::Windows::Forms::Label^  label84;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_SCOPE_V_RIGHT;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_SCOPE_V_LEFT;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_SCOPE_H_RIGHT;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_SCOPE_H_LEFT;
		private: System::Windows::Forms::PictureBox^  B_SATURATION_V_LEFT;
		private: System::Windows::Forms::PictureBox^  B_SATURATION_V_RIGHT;
		private: System::Windows::Forms::PictureBox^  B_SATURATION_H_RIGHT;
		private: System::Windows::Forms::PictureBox^  B_SATURATION_H_LEFT;
		private: System::Windows::Forms::Button^  W_DATA_RECORDING;
		private: System::Windows::Forms::Button^  B_PROBE_TEST;
		private: System::Windows::Forms::Panel^  panel7;
		private: System::Windows::Forms::RadioButton^  RB_BARKER_PULSE;
		private: System::Windows::Forms::RadioButton^  RB_SINGLE_PULSE;
		private: System::Windows::Forms::TextBox^  B_Out_DET;
		private: System::Windows::Forms::Button^  B_DET_Browse;
		private: System::Windows::Forms::TextBox^  B_Ethernet_Status;
		private: System::Windows::Forms::OpenFileDialog^  B_SelectLogFile_Of_Calibrator;
		private: System::Windows::Forms::TabControl^  B_tabControl;
		private: System::Windows::Forms::TabPage^  A_SCOPE_VIEW;
		private: System::Windows::Forms::TabPage^  Flash;
		private: System::Windows::Forms::Button^  B_FLASH_READ;
		private: System::Windows::Forms::Button^  B_FLASH_WRITE;
		private: System::Windows::Forms::TabPage^  Debug;
		private: System::Windows::Forms::Button^  B_MAIN_config;
		private: System::Windows::Forms::TabPage^  Mainenance;
		private: System::Windows::Forms::GroupBox^  groupBox9;
		private: System::Windows::Forms::Label^  L_BUL_status_MCU;
		private: System::Windows::Forms::TextBox^  B_BUL_status_OMR;
		private: System::Windows::Forms::TextBox^  B_BUL_status_DET;
		private: System::Windows::Forms::TextBox^  B_BUL_status_MCU;
		private: System::Windows::Forms::Label^  B_label1;
		private: System::Windows::Forms::Label^  L_BUL_status_OMR;
		private: System::Windows::Forms::Label^  L_BUL_status_CHB;
		private: System::Windows::Forms::Button^  B_OMR_Browse;
		private: System::Windows::Forms::Label^  L_BUL_status_DET;
		private: System::Windows::Forms::TextBox^  B_BUL_status_CHB;
		private: System::Windows::Forms::TextBox^  B_BUL_status_CHA;
		private: System::Windows::Forms::CheckBox^  B_ResetAfterUpload;
		private: System::Windows::Forms::TextBox^  B_Out_OMR;
		private: System::Windows::Forms::Label^  L_BUL_status_CHA;
		private: System::Windows::Forms::TextBox^  B_FIFO_length;
		private: System::Windows::Forms::TextBox^  B_Buffer_length;
		private: System::Windows::Forms::TextBox^  B_Number_of_buffers;
		private: System::Windows::Forms::Label^  label111;
		private: System::Windows::Forms::Label^  label112;
		private: System::Windows::Forms::Label^  label113;
		private: System::Windows::Forms::GroupBox^  B_GROUP_RF;
		private: System::Windows::Forms::TextBox^  B_ATTN_RX4;
		private: System::Windows::Forms::TextBox^  B_ATTN_RX3;
		private: System::Windows::Forms::TextBox^  B_ATTN_RX2;
		private: System::Windows::Forms::TextBox^  B_ATTN_RX1;
		private: System::Windows::Forms::TextBox^  B_ATTN_TX3;
		private: System::Windows::Forms::TextBox^  B_ATTN_TX2;
		private: System::Windows::Forms::TextBox^  B_ATTN_TX1;
		private: System::Windows::Forms::Label^  label116;
		private: System::Windows::Forms::Label^  label122;
		private: System::Windows::Forms::Label^  label123;
		private: System::Windows::Forms::Label^  label124;
		private: System::Windows::Forms::Label^  label125;
		private: System::Windows::Forms::Label^  label126;
		private: System::Windows::Forms::Label^  label127;
		private: System::Windows::Forms::Label^  label128;
		private: System::Windows::Forms::TextBox^  B_IO_UPDATE_rate;
		private: System::Windows::Forms::TextBox^  B_AD9910_Set_aux_dac_B;
		private: System::Windows::Forms::TextBox^  B_chip_length_AD9910B;
		private: System::Windows::Forms::TextBox^  B_Profile_AD9910B;
		private: System::Windows::Forms::TextBox^  B_AD9910_Set_aux_dac_A;
		private: System::Windows::Forms::TextBox^  B_chip_length_AD9910A;
		private: System::Windows::Forms::TextBox^  B_Profile_AD9910A;
		private: System::Windows::Forms::Label^  label129;
		private: System::Windows::Forms::Label^  label130;
		private: System::Windows::Forms::Label^  label131;
		private: System::Windows::Forms::Label^  label132;
		private: System::Windows::Forms::Label^  label133;
		private: System::Windows::Forms::Label^  label134;
		private: System::Windows::Forms::TextBox^  B_TX_ON3;
		private: System::Windows::Forms::TextBox^  B_TX_ON2;
		private: System::Windows::Forms::TextBox^  B_TX_ON1;
		private: System::Windows::Forms::Label^  label7;
		private: System::Windows::Forms::Label^  label6;
		private: System::Windows::Forms::Label^  label5;
		private: System::Windows::Forms::TextBox^  B_IO_UPDATE_ON;
		private: System::Windows::Forms::TextBox^  B_TX_LO_TR;
		private: System::Windows::Forms::TextBox^  B_SAMPLE_ON_OFF;
		private: System::Windows::Forms::Label^  label31;
		private: System::Windows::Forms::Label^  label30;
		private: System::Windows::Forms::Label^  label29;
		private: System::Windows::Forms::TextBox^  B_IF_SELECT_PROBE;
		private: System::Windows::Forms::TextBox^  B_IF_SELECT_TX3;
		private: System::Windows::Forms::TextBox^  B_IF_SELECT_TX2;
		private: System::Windows::Forms::TextBox^  B_IF_SELECT_TX1;
		private: System::Windows::Forms::TextBox^  B_ANT_SAMPLE_SELECT;
		private: System::Windows::Forms::Button^  W_START_WORK_CIRC;
		private: System::Windows::Forms::ListBox^  B_MATLAB_script;
		private: System::Windows::Forms::Label^  label64;
		private: System::Windows::Forms::Label^  label108;
		private: System::Windows::Forms::GroupBox^  B_GROUP_FREES;
		private: System::Windows::Forms::TextBox^  B_LOG_FOLDER;
		private: System::Windows::Forms::Button^  B_LOG_FOLDER_BROWSE;
		private: System::Windows::Forms::Label^  label66;
		private: System::Windows::Forms::FolderBrowserDialog^  B_SelectLOGfolder;
		private: System::Windows::Forms::GroupBox^  groupBox1;
		private: System::Windows::Forms::Button^  G_STOP_WORK;
		private: System::Windows::Forms::TextBox^  B_CHA_FREE_4;
		private: System::Windows::Forms::TextBox^  B_CHA_FREE_3;
		private: System::Windows::Forms::TextBox^  B_CHA_FREE_2;
		private: System::Windows::Forms::TextBox^  B_CHA_FREE_1;
		private: System::Windows::Forms::Label^  L_WORK;
		private: System::Windows::Forms::TextBox^  B_DET_WORK_STATE;
		private: System::Windows::Forms::TextBox^  B_CHB_FREE_2;
		private: System::Windows::Forms::TextBox^  B_CHB_FREE_1;
		private: System::Windows::Forms::TextBox^  B_CHB_FREE_4;
		private: System::Windows::Forms::TextBox^  B_CHB_FREE_3;
		private: System::Windows::Forms::Timer^  timer_DSP_messages;
		private: System::Windows::Forms::TextBox^  B_OMR_VERSION;
		private: System::Windows::Forms::TextBox^  B_DET_VERSION;
		private: System::Windows::Forms::Label^  label48;
		private: System::Windows::Forms::Label^  B_label10;
		private: System::Windows::Forms::TextBox^  B_MCU_VERSION;
		private: System::Windows::Forms::Label^  B_label11;
		private: System::Windows::Forms::Label^  label47;
		private: System::Windows::Forms::TextBox^  B_CHA_VERSION;
		private: System::Windows::Forms::TextBox^  B_CHB_VERSION;
		private: System::Windows::Forms::Label^  label46;
		private: System::Windows::Forms::GroupBox^  B_GROUP_SENSOR;
		private: System::Windows::Forms::Button^  B_SENSOR_CONFIG;
		private: System::Windows::Forms::TextBox^  B_SENSOR_TIME;
		private: System::Windows::Forms::TextBox^  B_SENSOR_VelUncertainty;
		private: System::Windows::Forms::TextBox^  B_SENSOR_PosUncertainty;
		private: System::Windows::Forms::TextBox^  B_SENSOR_AttUncertainty;
		private: System::Windows::Forms::Label^  label13;
		private: System::Windows::Forms::Label^  label10;
		private: System::Windows::Forms::Label^  label9;
		private: System::Windows::Forms::TextBox^  B_DET_FREE_4;
		private: System::Windows::Forms::TextBox^  B_DET_FREE_3;
		private: System::Windows::Forms::TextBox^  B_DET_FREE_2;
		private: System::Windows::Forms::TextBox^  B_DET_FREE_1;
		//
		//	DEBUG Tab Control
		//
		private: System::Windows::Forms::TextBox^		B_RF_MCU_STATUS;
		private: System::Windows::Forms::Label^			L_RF_MCU_STATUS;
		private: System::Windows::Forms::TextBox^		B_HMC830_PLL;
		private: System::Windows::Forms::Label^			L_HMC830_PLL;
		private: System::Windows::Forms::TextBox^		B_RF_MCU_TEMP;
		private: System::Windows::Forms::Label^			L_RF_MCU_TEMP;
		private: System::Windows::Forms::TextBox^		B_RF_TEMP;
		private: System::Windows::Forms::Label^			L_RF_BOARD_TEMP;
		

		private: System::Windows::Forms::TextBox^  B_OMR_FREE_4;
		private: System::Windows::Forms::TextBox^  B_OMR_FREE_3;
		private: System::Windows::Forms::TextBox^  B_OMR_FREE_2;
		private: System::Windows::Forms::TextBox^  B_OMR_FREE_1;
		private: System::Windows::Forms::Label^  label54;
		private: System::Windows::Forms::Label^  label50;
		private: System::Windows::Forms::TextBox^  B_message;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ANGULAR_RATE_Z;
		private: System::Windows::Forms::Label^  label65;
		private: System::Windows::Forms::Label^  label68;
		private: System::Windows::Forms::Label^  label69;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ACCELERATION_Z;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ACCELERATION_Y;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ACCELERATION_X;
		private: System::Windows::Forms::TextBox^  B_SENSOR_VELOCITY_Z;
		private: System::Windows::Forms::TextBox^  B_SENSOR_VELOCITY_Y;
		private: System::Windows::Forms::TextBox^  B_SENSOR_VELOCITY_X;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ALTITUDE;
		private: System::Windows::Forms::TextBox^  B_SENSOR_LONGITUDE;
		private: System::Windows::Forms::TextBox^  B_SENSOR_LATITUDE;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ANGULAR_RATE_Y;
		private: System::Windows::Forms::TextBox^  B_SENSOR_INS_ROLL;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ANGULAR_RATE_X;
		private: System::Windows::Forms::TextBox^  B_SENSOR_INS_PITCH;
		private: System::Windows::Forms::TextBox^  B_SENSOR_INS_YAW;
		private: System::Windows::Forms::Label^  label1003;
		private: System::Windows::Forms::Label^  label1002;
		private: System::Windows::Forms::Label^  label1001;
		private: System::Windows::Forms::Label^  lable10;
		private: System::Windows::Forms::Label^  label74;
		private: System::Windows::Forms::Label^  label75;
		private: System::Windows::Forms::Label^  label1006;
		private: System::Windows::Forms::Label^  label77;
		private: System::Windows::Forms::Label^  label1005;
		private: System::Windows::Forms::Label^  label1004;
		private: System::Windows::Forms::Label^  label80;
		private: System::Windows::Forms::Label^  label81;
		private: System::Windows::Forms::Label^  label85;
		private: System::Windows::Forms::TextBox^  B_SENSOR_INS_sd;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ATT_YAW;
		private: System::Windows::Forms::Label^  label86;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ATT_PITCH;
		private: System::Windows::Forms::Label^  label87;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ATT_ROLL;
		private: System::Windows::Forms::Label^  label88;
		private: System::Windows::Forms::Label^  label83;
		private: System::Windows::Forms::Label^  label82;
		private: System::Windows::Forms::Label^  label79;
		private: System::Windows::Forms::Label^  label93;
		private: System::Windows::Forms::Label^  label94;
		private: System::Windows::Forms::Label^  label95;
		private: System::Windows::Forms::Label^  label96;
		private: System::Windows::Forms::Label^  label92;
		private: System::Windows::Forms::Label^  label91;
		private: System::Windows::Forms::Label^  label90;
		private: System::Windows::Forms::Label^  label89;
		private: System::Windows::Forms::Label^  label67;
		private: System::Windows::Forms::Label^  label63;
		private: System::Windows::Forms::Label^  label62;
		private: System::Windows::Forms::Label^  label61;
		private: System::Windows::Forms::Label^  label56;
		private: System::Windows::Forms::Label^  label51;
		private: System::Windows::Forms::Label^  label57;
		private: System::Windows::Forms::Label^  label42;
		private: System::Windows::Forms::Label^  label58;
		private: System::Windows::Forms::Label^  label52;
		private: System::Windows::Forms::Label^  label59;
		private: System::Windows::Forms::Label^  label12;
		private: System::Windows::Forms::Label^  label53;
		private: System::Windows::Forms::Label^  label43;
		private: System::Windows::Forms::Label^  label55;
		private: System::Windows::Forms::Label^  label44;
		private: System::Windows::Forms::Label^  label49;
		private: System::Windows::Forms::Label^  label32;
		private: System::Windows::Forms::Label^  label40;
		private: System::Windows::Forms::Label^  label41;
		private: System::Windows::Forms::GroupBox^  groupBox6;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Label^  label28;
		private: System::Windows::Forms::NumericUpDown^  F_Profile_AD9910B;
		private: System::Windows::Forms::NumericUpDown^  F_Profile_AD9910A;
		private: System::Windows::Forms::NumericUpDown^  F_chip_length_AD9910A;
		private: System::Windows::Forms::NumericUpDown^  F_chip_length_AD9910B;
		private: System::Windows::Forms::NumericUpDown^  F_IO_UPDATE_rate;
		private: System::Windows::Forms::NumericUpDown^  F_AD9910_Set_aux_dac_B;
		private: System::Windows::Forms::NumericUpDown^  F_AD9910_Set_aux_dac_A;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label22;
		private: System::Windows::Forms::Label^  label8;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::Panel^  panel13;
		private: System::Windows::Forms::RadioButton^  F_IF_SELECT_PROBE_B;
		private: System::Windows::Forms::RadioButton^  F_IF_SELECT_PROBE_A;
		private: System::Windows::Forms::Panel^  panel4;
		private: System::Windows::Forms::RadioButton^  F_PROBE_SELECT_SAMPLE;
		private: System::Windows::Forms::RadioButton^  F_PROBE_SELECT_ANT;
		private: System::Windows::Forms::Label^  label99;
		private: System::Windows::Forms::NumericUpDown^  F_ATTN_RX4;
		private: System::Windows::Forms::Panel^  panel3;
		private: System::Windows::Forms::RadioButton^  F_IF_SELECT_TX3_B;
		private: System::Windows::Forms::RadioButton^  F_IF_SELECT_TX3_A;
		private: System::Windows::Forms::NumericUpDown^  F_ATTN_RX3;
		private: System::Windows::Forms::NumericUpDown^  F_ATTN_RX2;
		private: System::Windows::Forms::Panel^  panel2;
		private: System::Windows::Forms::RadioButton^  F_IF_SELECT_TX2_B;
		private: System::Windows::Forms::RadioButton^  F_IF_SELECT_TX2_A;
		private: System::Windows::Forms::NumericUpDown^  F_ATTN_RX1;
		private: System::Windows::Forms::CheckBox^  F_IO_UPDATE_ON;
		private: System::Windows::Forms::Panel^  panel1;
		private: System::Windows::Forms::RadioButton^  F_IF_SELECT_TX1_B;
		private: System::Windows::Forms::RadioButton^  F_IF_SELECT_TX1_A;
		private: System::Windows::Forms::NumericUpDown^  F_ATTN_TX3;
		private: System::Windows::Forms::NumericUpDown^  F_ATTN_TX2;
		private: System::Windows::Forms::NumericUpDown^  F_ATTN_TX1;
		private: System::Windows::Forms::Label^  label17;
		private: System::Windows::Forms::Label^  label18;
		private: System::Windows::Forms::CheckBox^  F_PROBE_ON;
		private: System::Windows::Forms::CheckBox^  F_TX1_ON;
		private: System::Windows::Forms::Label^  label19;
		private: System::Windows::Forms::CheckBox^  F_TX3_ON;
		private: System::Windows::Forms::Label^  label20;
		private: System::Windows::Forms::Label^  label21;
		private: System::Windows::Forms::CheckBox^  F_TX2_ON;
		private: System::Windows::Forms::CheckBox^  F_TX_LO_TR;
		private: System::Windows::Forms::Label^  label15;
		private: System::Windows::Forms::Label^  label16;
		private: System::Windows::Forms::Label^  label24;
		private: System::Windows::Forms::Label^  label26;
		private: System::Windows::Forms::Label^  label25;
		private: System::Windows::Forms::NumericUpDown^  F_FIFO_length;
		private: System::Windows::Forms::NumericUpDown^  F_Number_of_buffers;
		private: System::Windows::Forms::NumericUpDown^  F_Buffer_length;
		private: System::Windows::Forms::GroupBox^  groupBox10;
		private: System::Windows::Forms::NumericUpDown^  F_PROBE_CALIBRATE_TGT_START;
		private: System::Windows::Forms::Label^  label104;
		private: System::Windows::Forms::Label^  label105;
		private: System::Windows::Forms::NumericUpDown^  F_PROBE_CALIBRATE_TGT_END;
		private: System::Windows::Forms::NumericUpDown^  F_SYSTEM_ID;
		private: System::Windows::Forms::Label^  label72;
		private: System::Windows::Forms::TabPage^  RADAR_VIEW;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_RADAR_PLOT;
		private: System::Windows::Forms::ListBox^  B_SNAPSHOT_TYPE;
		private: System::Windows::Forms::Label^  label73;
		private: System::Windows::Forms::GroupBox^  groupBox5;
		private: System::Windows::Forms::TextBox^  B_TGT_V_3;
		private: System::Windows::Forms::TextBox^  B_TGT_P_3;
		private: System::Windows::Forms::TextBox^  B_TGT_D_3;
		private: System::Windows::Forms::TextBox^  B_TGT_R_3;
		private: System::Windows::Forms::Label^  label37;
		private: System::Windows::Forms::TextBox^  B_TGT_V_2;
		private: System::Windows::Forms::TextBox^  B_TGT_P_2;
		private: System::Windows::Forms::TextBox^  B_TGT_D_2;
		private: System::Windows::Forms::TextBox^  B_TGT_R_2;
		private: System::Windows::Forms::TextBox^  B_TGT_V_1;
		private: System::Windows::Forms::TextBox^  B_TGT_P_1;
		private: System::Windows::Forms::TextBox^  B_TGT_D_1;
		private: System::Windows::Forms::TextBox^  B_TGT_R_1;
		private: System::Windows::Forms::Label^  label36;
		private: System::Windows::Forms::Label^  label35;
		private: System::Windows::Forms::Label^  label34;
		private: System::Windows::Forms::Label^  label33;
		private: System::Windows::Forms::Label^  label23;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::TextBox^  B_RANGE_meter;
		private: System::Windows::Forms::Label^  label78;
		private: System::Windows::Forms::TextBox^  B_OFFSET_sample;
		private: System::Windows::Forms::Label^  label76;
		private: System::Windows::Forms::NumericUpDown^  F_RANGE_meter;
		private: System::Windows::Forms::NumericUpDown^  F_OFFSET_sample;
		private: System::Windows::Forms::Label^  label97;
		private: System::Windows::Forms::Label^  label101;
		private: System::Windows::Forms::GroupBox^  groupBox2;
		private: System::Windows::Forms::NumericUpDown^  F_PROBE_TEST_gain;
		private: System::Windows::Forms::Label^  label103;
		private: System::Windows::Forms::NumericUpDown^  F_PROBE_TEST_profile;
		private: System::Windows::Forms::Label^  label102;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_PROBE_TEST_PLOT;
		private: System::Windows::Forms::Label^  label107;
		private: System::Windows::Forms::Label^  label106;
		private: System::Windows::Forms::Label^  label11;
		private: System::Windows::Forms::TextBox^  B_Out_MCU;
		private: System::Windows::Forms::TextBox^  B_Out_CHAB;
		private: System::Windows::Forms::Button^  B_MCU_Browse;
		private: System::Windows::Forms::Button^  B_CHAB_Browse;
		private: System::Windows::Forms::Label^  label135;
		private: System::Windows::Forms::Label^  label121;
		private: System::Windows::Forms::NumericUpDown^  F_CALIBRATOR_TGT_START;
		private: System::Windows::Forms::Label^  label119;
		private: System::Windows::Forms::NumericUpDown^  F_CALIBRATOR_TGT_END;
		private: System::Windows::Forms::Label^  label120;
		private: System::Windows::Forms::Label^  label146;
		private: System::Windows::Forms::Label^  label98;
		private: System::Windows::Forms::ListBox^  F_TxRx_control_MODE;
		private: System::Windows::Forms::Label^  label100;
		private: System::Windows::Forms::Label^  label147;
		private: System::Windows::Forms::Label^  label149;
		private: System::Windows::Forms::Label^  label148;
		private: System::Windows::Forms::TextBox^  B_TxRx_control_MODE;
		private: System::Windows::Forms::TextBox^  B_SYSTEM_ID;
		private: System::Windows::Forms::Label^  L_ACQUISITION;
		private: System::Windows::Forms::TextBox^  B_DET_ACQUISITION_STATE;
		private: System::Windows::Forms::Label^  label38;
		private: System::Windows::Forms::TextBox^  B_DET_BRAIN_STATE;
		private: System::Windows::Forms::NumericUpDown^  F_Target_detection_1st_threshold;
		private: System::Windows::Forms::Label^  label39;
		private: System::Windows::Forms::Label^  label150;
		private: System::Windows::Forms::TextBox^  B_Target_detection_1st_threshold;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_H_4;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_V_4;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_L_4;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_R_4;
		private: System::Windows::Forms::TextBox^  B_TGT_RELIABILITY_4;
		private: System::Windows::Forms::TextBox^  B_TGT_V_4;
		private: System::Windows::Forms::TextBox^  B_TGT_P_4;
		private: System::Windows::Forms::TextBox^  B_TGT_D_4;
		private: System::Windows::Forms::TextBox^  B_TGT_R_4;
		private: System::Windows::Forms::Label^  label156;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_H_3;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_V_3;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_L_3;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_R_3;
		private: System::Windows::Forms::TextBox^  B_TGT_RELIABILITY_3;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_H_2;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_V_2;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_L_2;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_R_2;
		private: System::Windows::Forms::TextBox^  B_TGT_RELIABILITY_2;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_H_1;
		private: System::Windows::Forms::Label^  label155;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_V_1;
		private: System::Windows::Forms::Label^  label154;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_L_1;
		private: System::Windows::Forms::Label^  label153;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_R_1;
		private: System::Windows::Forms::Label^  label152;
		private: System::Windows::Forms::TextBox^  B_TGT_RELIABILITY_1;
		private: System::Windows::Forms::Label^  label151;
		private: System::Windows::Forms::Label^  label158;
		private: System::Windows::Forms::TextBox^  B_A_SCOPE_DOPPLER;
		private: System::Windows::Forms::NumericUpDown^  F_RANGE_DECIMATION;
		private: System::Windows::Forms::Label^  label160;
		private: System::Windows::Forms::NumericUpDown^  F_MAX_VELOCITY;
		private: System::Windows::Forms::Label^  label159;
		private: System::Windows::Forms::TextBox^  B_RANGE_DECIMATION;
		private: System::Windows::Forms::Label^  label162;
		private: System::Windows::Forms::TextBox^  B_MAX_VELOCITY;
		private: System::Windows::Forms::Label^  label161;
		private: System::Windows::Forms::GroupBox^  groupBox7;
		private: System::Windows::Forms::GroupBox^  B_GROUP_ALGORITHMS;
		private: System::Windows::Forms::TabPage^  RDM_VIEW;
		private: System::Windows::Forms::GroupBox^  B_GROUP_STATE_MACHINES;
		private: System::Windows::Forms::Label^  label164;
		private: System::Windows::Forms::Label^  label163;
		private: System::Windows::Forms::TextBox^  B_CHA_WORK_STATE;
		private: System::Windows::Forms::Label^  label168;
		private: System::Windows::Forms::Label^  label167;
		private: System::Windows::Forms::TextBox^  B_DET_FIRST_DETECTION_STATE;
		private: System::Windows::Forms::Label^  label166;
		private: System::Windows::Forms::TextBox^  B_DET_CALIBRATE_STATE;
		private: System::Windows::Forms::TextBox^  B_CHB_WORK_STATE;
		private: System::Windows::Forms::Button^  G_Upload_MCU;
		private: System::Windows::Forms::Button^  G_Upload_CHAB;
		private: System::Windows::Forms::Button^  G_Upload_DET;
		private: System::Windows::Forms::Button^  G_Upload_OMR;
		private: System::Windows::Forms::Button^  B_FLASH_RETRIVE;
		private: System::Windows::Forms::FolderBrowserDialog^  B_folderBrowser_BUL;
		private: System::Windows::Forms::OpenFileDialog^  B_fileBrowser_TOM;
		private: System::Windows::Forms::NumericUpDown^  F_AGC_threshold;
		private: System::Windows::Forms::Label^  label109;
		private: System::Windows::Forms::Label^  label110;
		private: System::Windows::Forms::TextBox^  B_AGC_threshold;
		private: System::Windows::Forms::TextBox^  F_BATCH_DURATION;
		private: System::Windows::Forms::Label^  label114;
		private: System::Windows::Forms::TextBox^  B_BATCH_DURATION;
		private: System::Windows::Forms::Label^  label115;
		private: System::Windows::Forms::Label^  label188;
		private: System::Windows::Forms::Label^  label189;
		private: System::Windows::Forms::Label^  label185;
		private: System::Windows::Forms::Label^  label187;
		private: System::Windows::Forms::Label^  label183;
		private: System::Windows::Forms::Label^  label184;
		private: System::Windows::Forms::Label^  label186;
		private: System::Windows::Forms::Label^  label182;
		private: System::Windows::Forms::Label^  label181;
		private: System::Windows::Forms::Label^  label180;
		private: System::Windows::Forms::Label^  label179;
		private: System::Windows::Forms::Label^  label178;
		private: System::Windows::Forms::Label^  label193;
		private: System::Windows::Forms::Label^  label192;
		private: System::Windows::Forms::Label^  label191;
		private: System::Windows::Forms::Label^  label190;
		private: System::Windows::Forms::PictureBox^  B_RDM_H_L;
		private: System::Windows::Forms::Label^  label197;
		private: System::Windows::Forms::Label^  label196;
		private: System::Windows::Forms::Label^  label195;
		private: System::Windows::Forms::Label^  label194;
		private: System::Windows::Forms::PictureBox^  B_RDM_V_R;
		private: System::Windows::Forms::PictureBox^  B_RDM_V_L;
		private: System::Windows::Forms::PictureBox^  B_RDM_H_R;
		private: System::Windows::Forms::Label^  Velocity_min_3;
		private: System::Windows::Forms::Label^  Velocity_min_1;
		private: System::Windows::Forms::Label^  Velocity_min_2;
		private: System::Windows::Forms::Label^  Velocity_min_4;
		private: System::Windows::Forms::Label^  Velocity_max_3;
		private: System::Windows::Forms::Label^  Velocity_max_4;
		private: System::Windows::Forms::Label^  Velocity_max_2;
		private: System::Windows::Forms::Label^  Velocity_max_1;
		private: System::Windows::Forms::Label^  Range_max_4;
		private: System::Windows::Forms::Label^  Range_max_3;
		private: System::Windows::Forms::Label^  Range_max_2;
		private: System::Windows::Forms::Label^  Range_max_1;
		private: System::Windows::Forms::Label^  label205;
		private: System::Windows::Forms::Label^  label204;
		private: System::Windows::Forms::Label^  label203;
		private: System::Windows::Forms::Label^  label202;
		private: System::Windows::Forms::Label^  label201;
		private: System::Windows::Forms::Label^  label200;
		private: System::Windows::Forms::Label^  label199;
		private: System::Windows::Forms::Label^  label198;
		private: System::Windows::Forms::Label^  label209;
		private: System::Windows::Forms::Label^  label208;
		private: System::Windows::Forms::Label^  label207;
		private: System::Windows::Forms::Label^  label206;
		private: System::Windows::Forms::NumericUpDown^  F_MINIMUM_RANGE_METER;
		private: System::Windows::Forms::Label^  label210;
		private: System::Windows::Forms::GroupBox^  groupBox18;
		private: System::Windows::Forms::GroupBox^  groupBox17;
		private: System::Windows::Forms::Label^  Range27;
		private: System::Windows::Forms::GroupBox^  groupBox16;
		private: System::Windows::Forms::Label^  Range26;
		private: System::Windows::Forms::GroupBox^  groupBox15;
		private: System::Windows::Forms::Label^  Range25;
		private: System::Windows::Forms::GroupBox^  groupBox14;
		private: System::Windows::Forms::Label^  Range24;
		private: System::Windows::Forms::GroupBox^  groupBox13;
		private: System::Windows::Forms::Label^  Range23;
		private: System::Windows::Forms::GroupBox^  groupBox12;
		private: System::Windows::Forms::Label^  Range22;
		private: System::Windows::Forms::GroupBox^  groupBox8;
		private: System::Windows::Forms::Label^  Range21;
		private: System::Windows::Forms::GroupBox^  groupBox4;
		private: System::Windows::Forms::GroupBox^  groupBox26;
		private: System::Windows::Forms::Label^  Velocity21;
		private: System::Windows::Forms::GroupBox^  groupBox25;
		private: System::Windows::Forms::Label^  Velocity22;
		private: System::Windows::Forms::GroupBox^  groupBox24;
		private: System::Windows::Forms::Label^  Velocity23;
		private: System::Windows::Forms::GroupBox^  groupBox23;
		private: System::Windows::Forms::GroupBox^  groupBox22;
		private: System::Windows::Forms::Label^  Velocity26;
		private: System::Windows::Forms::GroupBox^  groupBox21;
		private: System::Windows::Forms::Label^  Velocity25;
		private: System::Windows::Forms::GroupBox^  groupBox20;
		private: System::Windows::Forms::Label^  Velocity24;
		private: System::Windows::Forms::GroupBox^  groupBox19;
		private: System::Windows::Forms::GroupBox^  groupBox27;
		private: System::Windows::Forms::GroupBox^  groupBox81;
		private: System::Windows::Forms::GroupBox^  groupBox80;
		private: System::Windows::Forms::GroupBox^  groupBox79;
		private: System::Windows::Forms::GroupBox^  groupBox71;
		private: System::Windows::Forms::Label^  Range37;
		private: System::Windows::Forms::GroupBox^  groupBox72;
		private: System::Windows::Forms::Label^  Range36;
		private: System::Windows::Forms::GroupBox^  groupBox73;
		private: System::Windows::Forms::Label^  Range35;
		private: System::Windows::Forms::GroupBox^  groupBox74;
		private: System::Windows::Forms::Label^  Range34;
		private: System::Windows::Forms::GroupBox^  groupBox75;
		private: System::Windows::Forms::Label^  Range33;
		private: System::Windows::Forms::GroupBox^  groupBox76;
		private: System::Windows::Forms::Label^  Range32;
		private: System::Windows::Forms::GroupBox^  groupBox77;
		private: System::Windows::Forms::Label^  Range31;
		private: System::Windows::Forms::GroupBox^  groupBox78;
		private: System::Windows::Forms::GroupBox^  groupBox63;
		private: System::Windows::Forms::Label^  Range17;
		private: System::Windows::Forms::GroupBox^  groupBox64;
		private: System::Windows::Forms::Label^  Range16;
		private: System::Windows::Forms::GroupBox^  groupBox65;
		private: System::Windows::Forms::Label^  Range15;
		private: System::Windows::Forms::GroupBox^  groupBox66;
		private: System::Windows::Forms::Label^  Range14;
		private: System::Windows::Forms::GroupBox^  groupBox67;
		private: System::Windows::Forms::Label^  Range13;
		private: System::Windows::Forms::GroupBox^  groupBox68;
		private: System::Windows::Forms::Label^  Range12;
		private: System::Windows::Forms::GroupBox^  groupBox69;
		private: System::Windows::Forms::Label^  Range11;
		private: System::Windows::Forms::GroupBox^  groupBox70;
		private: System::Windows::Forms::GroupBox^  groupBox55;
		private: System::Windows::Forms::Label^  Range47;
		private: System::Windows::Forms::GroupBox^  groupBox56;
		private: System::Windows::Forms::Label^  Range46;
		private: System::Windows::Forms::GroupBox^  groupBox57;
		private: System::Windows::Forms::Label^  Range45;
		private: System::Windows::Forms::GroupBox^  groupBox58;
		private: System::Windows::Forms::Label^  Range44;
		private: System::Windows::Forms::GroupBox^  groupBox59;
		private: System::Windows::Forms::Label^  Range43;
		private: System::Windows::Forms::GroupBox^  groupBox60;
		private: System::Windows::Forms::Label^  Range42;
		private: System::Windows::Forms::GroupBox^  groupBox61;
		private: System::Windows::Forms::Label^  Range41;
		private: System::Windows::Forms::GroupBox^  groupBox62;
		private: System::Windows::Forms::GroupBox^  groupBox46;
		private: System::Windows::Forms::GroupBox^  groupBox47;
		private: System::Windows::Forms::Label^  Velocity31;
		private: System::Windows::Forms::GroupBox^  groupBox48;
		private: System::Windows::Forms::Label^  Velocity32;
		private: System::Windows::Forms::GroupBox^  groupBox49;
		private: System::Windows::Forms::Label^  Velocity33;
		private: System::Windows::Forms::GroupBox^  groupBox50;
		private: System::Windows::Forms::GroupBox^  groupBox51;
		private: System::Windows::Forms::Label^  Velocity36;
		private: System::Windows::Forms::GroupBox^  groupBox52;
		private: System::Windows::Forms::Label^  Velocity35;
		private: System::Windows::Forms::GroupBox^  groupBox53;
		private: System::Windows::Forms::Label^  Velocity34;
		private: System::Windows::Forms::GroupBox^  groupBox54;
		private: System::Windows::Forms::GroupBox^  groupBox37;
		private: System::Windows::Forms::GroupBox^  groupBox38;
		private: System::Windows::Forms::Label^  Velocity11;
		private: System::Windows::Forms::GroupBox^  groupBox39;
		private: System::Windows::Forms::Label^  Velocity12;
		private: System::Windows::Forms::GroupBox^  groupBox40;
		private: System::Windows::Forms::Label^  Velocity13;
		private: System::Windows::Forms::GroupBox^  groupBox41;
		private: System::Windows::Forms::GroupBox^  groupBox42;
		private: System::Windows::Forms::Label^  Velocity16;
		private: System::Windows::Forms::GroupBox^  groupBox43;
		private: System::Windows::Forms::Label^  Velocity15;
		private: System::Windows::Forms::GroupBox^  groupBox44;
		private: System::Windows::Forms::Label^  Velocity14;
		private: System::Windows::Forms::GroupBox^  groupBox45;
		private: System::Windows::Forms::GroupBox^  groupBox28;
		private: System::Windows::Forms::GroupBox^  groupBox29;
		private: System::Windows::Forms::Label^  Velocity41;
		private: System::Windows::Forms::GroupBox^  groupBox30;
		private: System::Windows::Forms::Label^  Velocity42;
		private: System::Windows::Forms::GroupBox^  groupBox31;
		private: System::Windows::Forms::Label^  Velocity43;
		private: System::Windows::Forms::GroupBox^  groupBox32;
		private: System::Windows::Forms::GroupBox^  groupBox33;
		private: System::Windows::Forms::Label^  Velocity46;
		private: System::Windows::Forms::GroupBox^  groupBox34;
		private: System::Windows::Forms::Label^  Velocity45;
		private: System::Windows::Forms::GroupBox^  groupBox35;
		private: System::Windows::Forms::Label^  Velocity44;
		private: System::Windows::Forms::GroupBox^  groupBox36;
		private: System::Windows::Forms::Label^  label213;
		private: System::Windows::Forms::GroupBox^  groupBox82;
		private: System::Windows::Forms::Label^  label214;
		private: System::Windows::Forms::Label^  label212;
		private: System::Windows::Forms::Label^  label215;
		private: System::Windows::Forms::Label^  label216;
		private: System::Windows::Forms::GroupBox^  groupBox83;
		private: System::Windows::Forms::Label^  label217;
		private: System::Windows::Forms::Label^  label218;
		private: System::Windows::Forms::Label^  label219;
		private: System::Windows::Forms::Label^  label220;
		private: System::Windows::Forms::GroupBox^  groupBox84;
		private: System::Windows::Forms::Label^  label221;
		private: System::Windows::Forms::Label^  label222;
		private: System::Windows::Forms::Label^  label223;
		private: System::Windows::Forms::Label^  label224;
		private: System::Windows::Forms::GroupBox^  groupBox85;
		private: System::Windows::Forms::Label^  label225;
		private: System::Windows::Forms::Label^  label226;
		private: System::Windows::Forms::Label^  label227;
		private: System::Windows::Forms::Label^  label228;
		private: System::Windows::Forms::TextBox^  B_MAX_VELOCITY_MS;
		private: System::Windows::Forms::ToolTip^  toolTipHR;
		private: System::Windows::Forms::ToolTip^  toolTipVR;
		private: System::Windows::Forms::ToolTip^  toolTipHL;
		private: System::Windows::Forms::ToolTip^  toolTipVL;
		private: System::Windows::Forms::PictureBox^  B_Color_Map;
		private: System::Windows::Forms::Label^  label211;
		private: System::Windows::Forms::TextBox^  B_DET_INITIALIZATION_STATE;
		private: System::Windows::Forms::Label^  label230;
		private: System::Windows::Forms::Label^  label229;
		private: System::Windows::Forms::Label^  label231;
		private: System::Windows::Forms::Label^  label232;
		private: System::Windows::Forms::Label^  label233;
		private: System::Windows::Forms::Label^  label234;
		private: System::Windows::Forms::Label^  label235;
		private: System::Windows::Forms::Label^  label236;
		private: System::Windows::Forms::Label^  label238;
		private: System::Windows::Forms::Label^  label237;
		private: System::Windows::Forms::Label^  label239;
		private: System::Windows::Forms::NumericUpDown^  F_Target_detection_2nd_threshold;
		private: System::Windows::Forms::Label^  label240;
		private: System::Windows::Forms::TextBox^  B_Target_detection_2nd_threshold;
		private: System::Windows::Forms::TextBox^  B_System_Health_Status;
		private: System::Windows::Forms::Label^  label71;
		private: System::Windows::Forms::Label^  L_OMR_STATUS;
		private: System::Windows::Forms::Label^  L_MCU_STATUS;
		private: System::Windows::Forms::Label^  L_CHB_STATUS;
		private: System::Windows::Forms::Label^  L_CHA_STATUS;
		private: System::Windows::Forms::Label^  L_DET_STATUS;
		private: System::Windows::Forms::Label^  L_LMK01000;
		private: System::Windows::Forms::Label^  L_LMK04828;
		private: System::Windows::Forms::Label^  L_FPGA_B;
		private: System::Windows::Forms::Label^  L_FPGA_A;
		private: System::Windows::Forms::Label^  L_AD6655_B;
		private: System::Windows::Forms::Label^  L_AD6655_A;
		private: System::Windows::Forms::TextBox^  B_DEBUG_COUNT;
		private: System::Windows::Forms::TextBox^  B_PERIPHERALS_LMK04828;
		private: System::Windows::Forms::TextBox^  B_PERIPHERALS_LMK01000;
		private: System::Windows::Forms::TextBox^  B_OMR_STATUS;
		private: System::Windows::Forms::Label^  L_UCD9222_DET_internal;
		private: System::Windows::Forms::TextBox^  B_DET_STATUS;
		private: System::Windows::Forms::Label^  L_UCD9222_DET_external;
		private: System::Windows::Forms::TextBox^  B_CHA_STATUS;
		private: System::Windows::Forms::Label^  L_UCD9222_CHA_external;
		private: System::Windows::Forms::TextBox^  B_CHB_STATUS;
		private: System::Windows::Forms::TextBox^  B_MCU_STATUS;
		private: System::Windows::Forms::TextBox^  B_PERIPHERALS_AD6655_A;
		private: System::Windows::Forms::TextBox^  B_PERIPHERALS_AD6655_B;
		private: System::Windows::Forms::TextBox^  B_MCU_TEMP;
		private: System::Windows::Forms::TextBox^  B_PERIPHERALS_FPGA_A;
		private: System::Windows::Forms::TextBox^  B_PERIPHERALS_FPGA_B;
		private: System::Windows::Forms::TextBox^  B_UCD9222_DET_temperature_internal;
		private: System::Windows::Forms::Label^  L_Counter;
		private: System::Windows::Forms::Label^  L_UCD9222_CHA_internal;
		private: System::Windows::Forms::TextBox^  B_UCD9222_CHA_temperature_internal;
		private: System::Windows::Forms::Label^  L_AD9910_B;
		private: System::Windows::Forms::Label^  L_AD9910_A;
		private: System::Windows::Forms::TextBox^  B_UCD9222_CHA_temperature_external;
		private: System::Windows::Forms::TextBox^  B_PERIPHERALS_AD9910_A;
		private: System::Windows::Forms::TextBox^  B_PERIPHERALS_AD9910_B;
		private: System::Windows::Forms::Label^  L_MCU_TEMP;
		private: System::Windows::Forms::GroupBox^  B_GROUP_STATUS;
		private: System::Windows::Forms::TabControl^  tabControl1;
		private: System::Windows::Forms::TabPage^  tabPage1;
		private: System::Windows::Forms::TabPage^  tabPage2;
		private: System::Windows::Forms::GroupBox^  groupBox11;
		private: System::Windows::Forms::Button^  B_CALIBRATOR_CALIBRATE;
		private: System::Windows::Forms::Button^  B_CALIBRATOR_RESET;
		private: System::Windows::Forms::Button^  B_PROBE_RESET;
		private: System::Windows::Forms::Label^  label177;
		private: System::Windows::Forms::Label^  label176;
		private: System::Windows::Forms::Label^  label175;
		private: System::Windows::Forms::Label^  label171;
		private: System::Windows::Forms::Label^  label170;
		private: System::Windows::Forms::Label^  label118;
		private: System::Windows::Forms::Label^  label117;
		private: System::Windows::Forms::Label^  label174;
		private: System::Windows::Forms::Label^  label173;
		private: System::Windows::Forms::Label^  label172;
		private: System::Windows::Forms::Label^  label136;
		private: System::Windows::Forms::Label^  label137;
		private: System::Windows::Forms::Label^  label165;
		private: System::Windows::Forms::Label^  label169;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_RV_Q;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_RH_Q;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_LH_Q;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_LV_Q;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_RV_I;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_RH_I;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_LH_I;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_LV_I;
		private: System::Windows::Forms::Label^  label145;
		private: System::Windows::Forms::Label^  label144;
		private: System::Windows::Forms::Label^  label143;
		private: System::Windows::Forms::Label^  label142;
		private: System::Windows::Forms::Label^  label141;
		private: System::Windows::Forms::Label^  label140;
		private: System::Windows::Forms::Label^  label139;
		private: System::Windows::Forms::Label^  label138;
		private: System::Windows::Forms::TextBox^  B_CORRECTION_RV_Q;
		private: System::Windows::Forms::TextBox^  B_CORRECTION_RH_Q;
		private: System::Windows::Forms::TextBox^  B_CORRECTION_LH_Q;
		private: System::Windows::Forms::TextBox^  B_CORRECTION_LV_Q;
		private: System::Windows::Forms::TextBox^  B_CORRECTION_RV_I;
		private: System::Windows::Forms::TextBox^  B_CORRECTION_RH_I;
		private: System::Windows::Forms::TextBox^  B_CORRECTION_LH_I;
		private: System::Windows::Forms::TextBox^  B_CORRECTION_LV_I;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_TGT_END;
		private: System::Windows::Forms::TextBox^  B_CALIBRATOR_TGT_START;
		private: System::Windows::Forms::TextBox^  B_PROBE_CALIBRATE_TGT_START;
		private: System::Windows::Forms::TextBox^  B_PROBE_CALIBRATE_TGT_END;
		private: System::Windows::Forms::Label^  label241;
		private: System::Windows::Forms::GroupBox^  groupBox86;
		private: System::Windows::Forms::PictureBox^  Polarization_Box;
		private: System::Windows::Forms::TextBox^  POL_Copy;
		private: System::Windows::Forms::Label^  label242;
		private: System::Windows::Forms::NumericUpDown^  F_POL_Target_selector;
		private: System::Windows::Forms::Label^  label243;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_H_5;
		private: System::Windows::Forms::TextBox^  B_TGT_AOA_V_5;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_L_5;
		private: System::Windows::Forms::TextBox^  B_TGT_POL_R_5;
		private: System::Windows::Forms::TextBox^  B_TGT_RELIABILITY_5;
		private: System::Windows::Forms::TextBox^  B_TGT_V_5;
		private: System::Windows::Forms::TextBox^  B_TGT_P_5;
		private: System::Windows::Forms::TextBox^  B_TGT_D_5;
		private: System::Windows::Forms::TextBox^  B_TGT_R_5;
		private: System::Windows::Forms::Label^  label157;
		private: System::Windows::Forms::Button^  B_PROBE_CALIBRATE;
		private: System::Windows::Forms::Button^  B_SNAPSHOT;
		private: System::Windows::Forms::TextBox^  B_UCD9222_DET_temperature_external;
		private: System::Windows::Forms::TextBox^  B_Navigation_Status;
		private: System::Windows::Forms::Label^  label244;
		private: System::Windows::Forms::GroupBox^  groupBox3;
		private: System::Windows::Forms::TextBox^  textBox2;
		private: System::Windows::Forms::TextBox^  T_VR_Noise;
		private: System::Windows::Forms::Label^  label248;
		private: System::Windows::Forms::TextBox^  T_HR_Noise;
		private: System::Windows::Forms::Label^  label250;
		private: System::Windows::Forms::TextBox^  T_VL_Noise;
		private: System::Windows::Forms::TextBox^  T_HL_Noise;

		private: System::Windows::Forms::Label^  label254;
		private: System::Windows::Forms::Label^  label255;
		private: System::Windows::Forms::TextBox^  B_TGT_HL_SNR_4;
		private: System::Windows::Forms::TextBox^  B_TGT_HL_SNR_3;
		private: System::Windows::Forms::TextBox^  B_TGT_HL_SNR_2;
		private: System::Windows::Forms::TextBox^  B_TGT_HL_SNR_1;
		private: System::Windows::Forms::Label^  label245;
		private: System::Windows::Forms::TextBox^  B_TGT_VR_SNR_4;
		private: System::Windows::Forms::TextBox^  B_TGT_HR_SNR_4;
		private: System::Windows::Forms::TextBox^  B_TGT_VR_SNR_3;
		private: System::Windows::Forms::TextBox^  B_TGT_VL_SNR_4;
		private: System::Windows::Forms::TextBox^  B_TGT_VR_SNR_2;
		private: System::Windows::Forms::TextBox^  B_TGT_HR_SNR_3;
		private: System::Windows::Forms::TextBox^  B_TGT_VR_SNR_1;
		private: System::Windows::Forms::Label^  label249;
		private: System::Windows::Forms::TextBox^  B_TGT_HR_SNR_2;
		private: System::Windows::Forms::TextBox^  B_TGT_VL_SNR_3;
		private: System::Windows::Forms::TextBox^  B_TGT_HR_SNR_1;
		private: System::Windows::Forms::Label^  label247;
		private: System::Windows::Forms::TextBox^  B_TGT_VL_SNR_2;
		private: System::Windows::Forms::TextBox^  B_TGT_VL_SNR_1;
		private: System::Windows::Forms::Label^  label246;
		private: System::Windows::Forms::TabPage^  MAP_VIEW;
		private: System::Windows::Forms::TabPage^  SINGLE_RDM_VIEW;
		private: System::Windows::Forms::Label^  label252;
		private: System::Windows::Forms::PictureBox^  PB_RDM_COLOR_MAP;
		private: System::Windows::Forms::GroupBox^  groupBox87;
		private: System::Windows::Forms::GroupBox^  groupBox88;
		private: System::Windows::Forms::Label^  lbl_velocity_6;
		private: System::Windows::Forms::GroupBox^  groupBox89;
		private: System::Windows::Forms::Label^  lbl_velocity_5;
		private: System::Windows::Forms::GroupBox^  groupBox90;
		private: System::Windows::Forms::Label^  lbl_velocity_4;
		private: System::Windows::Forms::GroupBox^  groupBox91;
		private: System::Windows::Forms::GroupBox^  groupBox92;
		private: System::Windows::Forms::Label^  lbl_velocity_1;
		private: System::Windows::Forms::GroupBox^  groupBox93;
		private: System::Windows::Forms::Label^  lbl_velocity_2;
		private: System::Windows::Forms::GroupBox^  groupBox94;
		private: System::Windows::Forms::Label^  lbl_velocity_3;
		private: System::Windows::Forms::GroupBox^  groupBox95;
		private: System::Windows::Forms::GroupBox^  groupBox96;
		private: System::Windows::Forms::GroupBox^  groupBox97;
		private: System::Windows::Forms::Label^  lbl_range_7;
		private: System::Windows::Forms::GroupBox^  groupBox98;
		private: System::Windows::Forms::Label^  lbl_range_6;
		private: System::Windows::Forms::GroupBox^  groupBox99;
		private: System::Windows::Forms::Label^  lbl_range_5;
		private: System::Windows::Forms::GroupBox^  groupBox100;
		private: System::Windows::Forms::Label^  lbl_range_4;
		private: System::Windows::Forms::GroupBox^  groupBox101;
		private: System::Windows::Forms::Label^  lbl_range_3;
		private: System::Windows::Forms::GroupBox^  groupBox102;
		private: System::Windows::Forms::Label^  lbl_range_2;
		private: System::Windows::Forms::GroupBox^  groupBox103;
		private: System::Windows::Forms::Label^  lbl_range_1;
		private: System::Windows::Forms::GroupBox^  groupBox104;
		private: System::Windows::Forms::Label^  label269;
		private: System::Windows::Forms::Label^  lbl_velocity_min;
		private: System::Windows::Forms::Label^  lbl_velocity_max;
		private: System::Windows::Forms::Label^  lbl_range_max;
		private: System::Windows::Forms::Label^  label274;
		private: System::Windows::Forms::Label^  Lbl_RDM;
		private: System::Windows::Forms::PictureBox^  PB_RDM;
		private: System::Windows::Forms::Label^  label282;
		private: System::Windows::Forms::Label^  label283;
		private: System::Windows::Forms::Label^  label284;
		private: System::Windows::Forms::Label^  label285;
		private: System::Windows::Forms::Label^  label286;
		private: System::Windows::Forms::Label^  label287;
		private: System::Windows::Forms::Label^  label288;
		private: System::Windows::Forms::Label^  label289;
		private: System::Windows::Forms::Label^  label253;
		private: System::Windows::Forms::Label^  label256;
		private: System::Windows::Forms::GroupBox^  groupBox105;
		private: System::Windows::Forms::Label^  label257;
		private: System::Windows::Forms::Label^  label258;
		private: System::Windows::Forms::Label^  label259;
		private: System::Windows::Forms::ListBox^  lbox_select_RDM;
		private: System::Windows::Forms::Label^  label260;
		private: System::Windows::Forms::Label^  label262;
		private: System::Windows::Forms::Label^  label261;
		private: System::Windows::Forms::GroupBox^  groupBox113;
		private: System::Windows::Forms::GroupBox^  groupBox112;
		private: System::Windows::Forms::GroupBox^  groupBox111;
		private: System::Windows::Forms::GroupBox^  groupBox110;
		private: System::Windows::Forms::GroupBox^  groupBox109;
		private: System::Windows::Forms::GroupBox^  groupBox108;
		private: System::Windows::Forms::GroupBox^  groupBox107;
		private: System::Windows::Forms::GroupBox^  groupBox106;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  PB_MAP_chart;
		private: System::Windows::Forms::Button^  Load_PB_MAP;
		private: System::Windows::Forms::Label^  lbl_MAP_location;

		private: System::Windows::Forms::Panel^  B_MAP_PANEL;
		private: System::Windows::Forms::FolderBrowserDialog^  B_BROWSE_DIR;
		private: System::Windows::Forms::Label^  label251;
		private: System::Windows::Forms::Label^  label263;
		private: System::Windows::Forms::Label^  label264;
		private: System::Windows::Forms::TrackBar^  B_SCREEN_WIDTH_OF_VIEWER;
		private: System::Windows::Forms::Panel^  panel5;
		private: System::Windows::Forms::Label^  B_SCALE_VIEWER;
		private: System::Windows::Forms::Label^  label265;



		private: System::Windows::Forms::ComboBox^  CHAB_BUL_Selector;




		private: System::Windows::Forms::Label^  label14;
		private: System::Windows::Forms::TextBox^  B_RF_MCU_Version;
		private: System::Windows::Forms::Label^  L_BUL_status_RF_MCU;
		private: System::Windows::Forms::TextBox^  B_BUL_status_RF_MCU;
		private: System::Windows::Forms::Button^  G_Upload_RF_MCU;
		private: System::Windows::Forms::Button^  B_RF_MCU_Browse;
		private: System::Windows::Forms::TextBox^  B_Out_RF_MCU;
		private: System::Windows::Forms::Label^  label27;
		private: System::Windows::Forms::Button^  Free_Flight_PB_MAP;

		private: System::Windows::Forms::Button^  B_RESET_ARC;
		private: System::Windows::Forms::Label^  label45;
		private: System::Windows::Forms::TextBox^  B_RF2_ON;
private: System::Windows::Forms::CheckBox^  F_RF2_ON;














private: System::Windows::Forms::TabPage^  LAB_Experiments;
private: System::Windows::Forms::Label^  label266;
private: System::Windows::Forms::Button^  B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE;
private: System::Windows::Forms::TextBox^  B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE;





















private: System::Windows::Forms::ToolTip^  TOOL_TIP_START;
private: System::Windows::Forms::ToolTip^  TOOL_TIP_STOP;
private: System::Windows::Forms::ToolTip^  TOOL_TIP_START_RECORD;
private: System::Windows::Forms::ToolStrip^  REAL_TIME_TOOL_STRIP;
private: System::Windows::Forms::ToolStripButton^  B_REAL_TIME_TOOL_EDIT;
private: System::Windows::Forms::ToolStripButton^  B_ZOOM_IN;
private: System::Windows::Forms::ToolStripButton^  B_ZOOM_OUT;
private: System::Windows::Forms::ToolStripButton^  B_RESET_SETTING;
private: System::Windows::Forms::ToolStripButton^  B_CLEAR_MAP;

private: System::Windows::Forms::ToolTip^  LOAD_MAP_TOOL_TIP;
private: System::Windows::Forms::ToolTip^  RE_FLIGHT_TOOL_TIP;

private: System::Windows::Forms::Button^  B_LOAD_MAP;
private: System::Windows::Forms::Button^  B_RE_FLIGHT;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
private: System::Windows::Forms::ToolStripButton^  B_CALCULATE_DISTANCE;





private: System::Windows::Forms::GroupBox^  B_ROTATOR_DATA;
private: System::Windows::Forms::NumericUpDown^  B_LAB_AZIMUTH;
private: System::Windows::Forms::Label^  lbl_azimuth;



private: System::Windows::Forms::Label^  B_AZIMUTH;
private: System::Windows::Forms::ComboBox^  B_ROTATOR_COM_PORT;


private: System::Windows::Forms::Label^  B_COM;
private: System::Windows::Forms::TextBox^  B_AZIMUTH_RESOLUTION;

private: System::Windows::Forms::Label^  label292;
private: System::Windows::Forms::TextBox^  B_CURRENT_ELEVATION;

private: System::Windows::Forms::Label^  label291;
private: System::Windows::Forms::TextBox^  B_CURRENT_AZIMUTH;

private: System::Windows::Forms::NumericUpDown^  B_LAB_ELEVATION;

private: System::Windows::Forms::Label^  label290;
private: System::Windows::Forms::TextBox^  B_ELEVATION_RESOLUTION;

private: System::Windows::Forms::Label^  label293;
private: System::Windows::Forms::GroupBox^  B_CALIBRATOR_DATA;
private: System::Windows::Forms::Label^  label280;
private: System::Windows::Forms::TextBox^  B_LAB_SNR;
private: System::Windows::Forms::Label^  label281;
private: System::Windows::Forms::Button^  B_LAB_CALIBRATOR_START;

private: System::Windows::Forms::Label^  label277;
private: System::Windows::Forms::TextBox^  B_LAB_TOTAL_CYCLES;
private: System::Windows::Forms::Label^  label276;
private: System::Windows::Forms::Label^  label275;
private: System::Windows::Forms::TextBox^  B_LAB_CYCLE;
private: System::Windows::Forms::TextBox^  B_LAB_DOPPLER;
private: System::Windows::Forms::Label^  label273;
private: System::Windows::Forms::Label^  label267;


private: System::Windows::Forms::ToolTip^  toolTip1;
private: System::Windows::Forms::Label^  label294;
private: System::Windows::Forms::Button^  B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE;
private: System::Windows::Forms::TextBox^  B_LAB_ROTATOR_DATA_FILE_TO_SAVE;
private: System::Windows::Forms::OpenFileDialog^  B_SelectLogFile_Of_Rotator;
private: System::Windows::Forms::GroupBox^  B_VISIBLE_OBSTACLES;
private: System::Windows::Forms::CheckBox^  B_TRAJECTORIES;
private: System::Windows::Forms::CheckBox^  B_DETECTIONS;
private: System::Windows::Forms::NumericUpDown^  B_MAX_ERROR_RANGE;


private: System::Windows::Forms::Label^  label270;








		private: System::ComponentModel::IContainer^  components;
		#pragma endregion

		private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea11 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::StripLine^  stripLine3 = (gcnew System::Windows::Forms::DataVisualization::Charting::StripLine());
			System::Windows::Forms::DataVisualization::Charting::StripLine^  stripLine4 = (gcnew System::Windows::Forms::DataVisualization::Charting::StripLine());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series28 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series29 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea12 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series30 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea13 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea14 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea15 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea16 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series31 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series32 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series33 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series34 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series35 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series36 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series37 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series38 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint2 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				m0) == '\\aA'
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea17 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend11 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series39 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series40 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series41 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series42 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea18 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend12 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series43 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series44 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series45 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series46 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea19 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend13 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series47 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series48 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series49 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series50 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea20 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend14 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series51 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series52 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series53 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series54 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->B_OMR_VERSION = (gcnew System::Windows::Forms::TextBox());
			this->B_DET_VERSION = (gcnew System::Windows::Forms::TextBox());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->B_label10 = (gcnew System::Windows::Forms::Label());
			this->B_MCU_VERSION = (gcnew System::Windows::Forms::TextBox());
			this->B_label11 = (gcnew System::Windows::Forms::Label());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->B_CHA_VERSION = (gcnew System::Windows::Forms::TextBox());
			this->B_CHB_VERSION = (gcnew System::Windows::Forms::TextBox());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label73 = (gcnew System::Windows::Forms::Label());
			this->B_MATLAB_script = (gcnew System::Windows::Forms::ListBox());
			this->B_SNAPSHOT_TYPE = (gcnew System::Windows::Forms::ListBox());
			this->label64 = (gcnew System::Windows::Forms::Label());
			this->B_LOG_FOLDER = (gcnew System::Windows::Forms::TextBox());
			this->B_LOG_FOLDER_BROWSE = (gcnew System::Windows::Forms::Button());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->B_DET_BRAIN_STATE = (gcnew System::Windows::Forms::TextBox());
			this->L_ACQUISITION = (gcnew System::Windows::Forms::Label());
			this->B_DET_ACQUISITION_STATE = (gcnew System::Windows::Forms::TextBox());
			this->L_WORK = (gcnew System::Windows::Forms::Label());
			this->B_DET_WORK_STATE = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_ANGULAR_RATE_Z = (gcnew System::Windows::Forms::TextBox());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->label69 = (gcnew System::Windows::Forms::Label());
			this->B_SENSOR_ACCELERATION_Z = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_ACCELERATION_Y = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_ACCELERATION_X = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_VELOCITY_Z = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_VELOCITY_Y = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_VELOCITY_X = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_ALTITUDE = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_LONGITUDE = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_LATITUDE = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_ANGULAR_RATE_Y = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_INS_ROLL = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_ANGULAR_RATE_X = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_INS_PITCH = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_INS_YAW = (gcnew System::Windows::Forms::TextBox());
			this->label1003 = (gcnew System::Windows::Forms::Label());
			this->label1002 = (gcnew System::Windows::Forms::Label());
			this->label1001 = (gcnew System::Windows::Forms::Label());
			this->lable10 = (gcnew System::Windows::Forms::Label());
			this->label74 = (gcnew System::Windows::Forms::Label());
			this->label75 = (gcnew System::Windows::Forms::Label());
			this->label1006 = (gcnew System::Windows::Forms::Label());
			this->label77 = (gcnew System::Windows::Forms::Label());
			this->label1005 = (gcnew System::Windows::Forms::Label());
			this->label1004 = (gcnew System::Windows::Forms::Label());
			this->label80 = (gcnew System::Windows::Forms::Label());
			this->label81 = (gcnew System::Windows::Forms::Label());
			this->timer_DSP_messages = (gcnew System::Windows::Forms::Timer(this->components));
			this->B_System_Health_Status = (gcnew System::Windows::Forms::TextBox());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->B_Ethernet_Status = (gcnew System::Windows::Forms::TextBox());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->B_message = (gcnew System::Windows::Forms::TextBox());
			this->B_GROUP_FREES = (gcnew System::Windows::Forms::GroupBox());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->label63 = (gcnew System::Windows::Forms::Label());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->B_CHB_FREE_4 = (gcnew System::Windows::Forms::TextBox());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->B_CHB_FREE_3 = (gcnew System::Windows::Forms::TextBox());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->B_CHB_FREE_2 = (gcnew System::Windows::Forms::TextBox());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->B_CHB_FREE_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_CHA_FREE_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_CHA_FREE_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_CHA_FREE_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_CHA_FREE_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_DET_FREE_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_DET_FREE_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_DET_FREE_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_DET_FREE_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_OMR_FREE_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_OMR_FREE_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_OMR_FREE_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_OMR_FREE_1 = (gcnew System::Windows::Forms::TextBox());
			this->G_STOP_WORK = (gcnew System::Windows::Forms::Button());
			this->B_SelectLOGfolder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->B_GROUP_SENSOR = (gcnew System::Windows::Forms::GroupBox());
			this->label108 = (gcnew System::Windows::Forms::Label());
			this->label93 = (gcnew System::Windows::Forms::Label());
			this->label94 = (gcnew System::Windows::Forms::Label());
			this->label95 = (gcnew System::Windows::Forms::Label());
			this->label96 = (gcnew System::Windows::Forms::Label());
			this->label92 = (gcnew System::Windows::Forms::Label());
			this->label91 = (gcnew System::Windows::Forms::Label());
			this->label90 = (gcnew System::Windows::Forms::Label());
			this->label89 = (gcnew System::Windows::Forms::Label());
			this->label85 = (gcnew System::Windows::Forms::Label());
			this->B_SENSOR_INS_sd = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_ATT_YAW = (gcnew System::Windows::Forms::TextBox());
			this->label86 = (gcnew System::Windows::Forms::Label());
			this->B_SENSOR_ATT_PITCH = (gcnew System::Windows::Forms::TextBox());
			this->label87 = (gcnew System::Windows::Forms::Label());
			this->B_SENSOR_ATT_ROLL = (gcnew System::Windows::Forms::TextBox());
			this->label88 = (gcnew System::Windows::Forms::Label());
			this->label84 = (gcnew System::Windows::Forms::Label());
			this->label83 = (gcnew System::Windows::Forms::Label());
			this->label82 = (gcnew System::Windows::Forms::Label());
			this->label79 = (gcnew System::Windows::Forms::Label());
			this->B_SENSOR_VelUncertainty = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_PosUncertainty = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_AttUncertainty = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_TIME = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->B_SENSOR_CONFIG = (gcnew System::Windows::Forms::Button());
			this->B_tabControl = (gcnew System::Windows::Forms::TabControl());
			this->MAP_VIEW = (gcnew System::Windows::Forms::TabPage());
			this->B_VISIBLE_OBSTACLES = (gcnew System::Windows::Forms::GroupBox());
			this->B_TRAJECTORIES = (gcnew System::Windows::Forms::CheckBox());
			this->B_DETECTIONS = (gcnew System::Windows::Forms::CheckBox());
			this->B_LOAD_MAP = (gcnew System::Windows::Forms::Button());
			this->B_RE_FLIGHT = (gcnew System::Windows::Forms::Button());
			this->label264 = (gcnew System::Windows::Forms::Label());
			this->B_MAP_PANEL = (gcnew System::Windows::Forms::Panel());
			this->REAL_TIME_TOOL_STRIP = (gcnew System::Windows::Forms::ToolStrip());
			this->B_REAL_TIME_TOOL_EDIT = (gcnew System::Windows::Forms::ToolStripButton());
			this->B_CALCULATE_DISTANCE = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->B_ZOOM_IN = (gcnew System::Windows::Forms::ToolStripButton());
			this->B_ZOOM_OUT = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->B_RESET_SETTING = (gcnew System::Windows::Forms::ToolStripButton());
			this->B_CLEAR_MAP = (gcnew System::Windows::Forms::ToolStripButton());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->B_SCALE_VIEWER = (gcnew System::Windows::Forms::Label());
			this->label265 = (gcnew System::Windows::Forms::Label());
			this->RDM_VIEW = (gcnew System::Windows::Forms::TabPage());
			this->label238 = (gcnew System::Windows::Forms::Label());
			this->label237 = (gcnew System::Windows::Forms::Label());
			this->B_Color_Map = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox81 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox80 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox79 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox71 = (gcnew System::Windows::Forms::GroupBox());
			this->Range37 = (gcnew System::Windows::Forms::Label());
			this->groupBox72 = (gcnew System::Windows::Forms::GroupBox());
			this->Range36 = (gcnew System::Windows::Forms::Label());
			this->groupBox73 = (gcnew System::Windows::Forms::GroupBox());
			this->Range35 = (gcnew System::Windows::Forms::Label());
			this->groupBox74 = (gcnew System::Windows::Forms::GroupBox());
			this->Range34 = (gcnew System::Windows::Forms::Label());
			this->groupBox75 = (gcnew System::Windows::Forms::GroupBox());
			this->Range33 = (gcnew System::Windows::Forms::Label());
			this->groupBox76 = (gcnew System::Windows::Forms::GroupBox());
			this->Range32 = (gcnew System::Windows::Forms::Label());
			this->groupBox77 = (gcnew System::Windows::Forms::GroupBox());
			this->Range31 = (gcnew System::Windows::Forms::Label());
			this->groupBox78 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox63 = (gcnew System::Windows::Forms::GroupBox());
			this->Range17 = (gcnew System::Windows::Forms::Label());
			this->groupBox64 = (gcnew System::Windows::Forms::GroupBox());
			this->Range16 = (gcnew System::Windows::Forms::Label());
			this->groupBox65 = (gcnew System::Windows::Forms::GroupBox());
			this->Range15 = (gcnew System::Windows::Forms::Label());
			this->groupBox66 = (gcnew System::Windows::Forms::GroupBox());
			this->Range14 = (gcnew System::Windows::Forms::Label());
			this->groupBox67 = (gcnew System::Windows::Forms::GroupBox());
			this->Range13 = (gcnew System::Windows::Forms::Label());
			this->groupBox68 = (gcnew System::Windows::Forms::GroupBox());
			this->Range12 = (gcnew System::Windows::Forms::Label());
			this->groupBox69 = (gcnew System::Windows::Forms::GroupBox());
			this->Range11 = (gcnew System::Windows::Forms::Label());
			this->groupBox70 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox55 = (gcnew System::Windows::Forms::GroupBox());
			this->Range47 = (gcnew System::Windows::Forms::Label());
			this->groupBox56 = (gcnew System::Windows::Forms::GroupBox());
			this->Range46 = (gcnew System::Windows::Forms::Label());
			this->groupBox57 = (gcnew System::Windows::Forms::GroupBox());
			this->Range45 = (gcnew System::Windows::Forms::Label());
			this->groupBox58 = (gcnew System::Windows::Forms::GroupBox());
			this->Range44 = (gcnew System::Windows::Forms::Label());
			this->groupBox59 = (gcnew System::Windows::Forms::GroupBox());
			this->Range43 = (gcnew System::Windows::Forms::Label());
			this->groupBox60 = (gcnew System::Windows::Forms::GroupBox());
			this->Range42 = (gcnew System::Windows::Forms::Label());
			this->groupBox61 = (gcnew System::Windows::Forms::GroupBox());
			this->Range41 = (gcnew System::Windows::Forms::Label());
			this->groupBox62 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox46 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox47 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity31 = (gcnew System::Windows::Forms::Label());
			this->groupBox48 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity32 = (gcnew System::Windows::Forms::Label());
			this->groupBox49 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity33 = (gcnew System::Windows::Forms::Label());
			this->groupBox50 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox51 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity36 = (gcnew System::Windows::Forms::Label());
			this->groupBox52 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity35 = (gcnew System::Windows::Forms::Label());
			this->groupBox53 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity34 = (gcnew System::Windows::Forms::Label());
			this->groupBox54 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox37 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox38 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity11 = (gcnew System::Windows::Forms::Label());
			this->groupBox39 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity12 = (gcnew System::Windows::Forms::Label());
			this->groupBox40 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity13 = (gcnew System::Windows::Forms::Label());
			this->groupBox41 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox42 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity16 = (gcnew System::Windows::Forms::Label());
			this->groupBox43 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity15 = (gcnew System::Windows::Forms::Label());
			this->groupBox44 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity14 = (gcnew System::Windows::Forms::Label());
			this->groupBox45 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox28 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox29 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity41 = (gcnew System::Windows::Forms::Label());
			this->groupBox30 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity42 = (gcnew System::Windows::Forms::Label());
			this->groupBox31 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity43 = (gcnew System::Windows::Forms::Label());
			this->groupBox32 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox33 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity46 = (gcnew System::Windows::Forms::Label());
			this->groupBox34 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity45 = (gcnew System::Windows::Forms::Label());
			this->groupBox35 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity44 = (gcnew System::Windows::Forms::Label());
			this->groupBox36 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox27 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox26 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity21 = (gcnew System::Windows::Forms::Label());
			this->groupBox25 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity22 = (gcnew System::Windows::Forms::Label());
			this->groupBox24 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity23 = (gcnew System::Windows::Forms::Label());
			this->groupBox23 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox22 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity26 = (gcnew System::Windows::Forms::Label());
			this->groupBox21 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity25 = (gcnew System::Windows::Forms::Label());
			this->groupBox20 = (gcnew System::Windows::Forms::GroupBox());
			this->Velocity24 = (gcnew System::Windows::Forms::Label());
			this->groupBox19 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox18 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox17 = (gcnew System::Windows::Forms::GroupBox());
			this->Range27 = (gcnew System::Windows::Forms::Label());
			this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
			this->Range26 = (gcnew System::Windows::Forms::Label());
			this->groupBox15 = (gcnew System::Windows::Forms::GroupBox());
			this->Range25 = (gcnew System::Windows::Forms::Label());
			this->groupBox14 = (gcnew System::Windows::Forms::GroupBox());
			this->Range24 = (gcnew System::Windows::Forms::Label());
			this->groupBox13 = (gcnew System::Windows::Forms::GroupBox());
			this->Range23 = (gcnew System::Windows::Forms::Label());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->Range22 = (gcnew System::Windows::Forms::Label());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->Range21 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label209 = (gcnew System::Windows::Forms::Label());
			this->label208 = (gcnew System::Windows::Forms::Label());
			this->label207 = (gcnew System::Windows::Forms::Label());
			this->label206 = (gcnew System::Windows::Forms::Label());
			this->Velocity_min_3 = (gcnew System::Windows::Forms::Label());
			this->Velocity_min_1 = (gcnew System::Windows::Forms::Label());
			this->Velocity_min_2 = (gcnew System::Windows::Forms::Label());
			this->Velocity_min_4 = (gcnew System::Windows::Forms::Label());
			this->Velocity_max_3 = (gcnew System::Windows::Forms::Label());
			this->Velocity_max_4 = (gcnew System::Windows::Forms::Label());
			this->Velocity_max_2 = (gcnew System::Windows::Forms::Label());
			this->Velocity_max_1 = (gcnew System::Windows::Forms::Label());
			this->Range_max_4 = (gcnew System::Windows::Forms::Label());
			this->Range_max_3 = (gcnew System::Windows::Forms::Label());
			this->Range_max_2 = (gcnew System::Windows::Forms::Label());
			this->Range_max_1 = (gcnew System::Windows::Forms::Label());
			this->label205 = (gcnew System::Windows::Forms::Label());
			this->label204 = (gcnew System::Windows::Forms::Label());
			this->label203 = (gcnew System::Windows::Forms::Label());
			this->label202 = (gcnew System::Windows::Forms::Label());
			this->label201 = (gcnew System::Windows::Forms::Label());
			this->label200 = (gcnew System::Windows::Forms::Label());
			this->label199 = (gcnew System::Windows::Forms::Label());
			this->label198 = (gcnew System::Windows::Forms::Label());
			this->label197 = (gcnew System::Windows::Forms::Label());
			this->label196 = (gcnew System::Windows::Forms::Label());
			this->label195 = (gcnew System::Windows::Forms::Label());
			this->label194 = (gcnew System::Windows::Forms::Label());
			this->B_RDM_V_R = (gcnew System::Windows::Forms::PictureBox());
			this->B_RDM_V_L = (gcnew System::Windows::Forms::PictureBox());
			this->B_RDM_H_R = (gcnew System::Windows::Forms::PictureBox());
			this->B_RDM_H_L = (gcnew System::Windows::Forms::PictureBox());
			this->label213 = (gcnew System::Windows::Forms::Label());
			this->groupBox82 = (gcnew System::Windows::Forms::GroupBox());
			this->label214 = (gcnew System::Windows::Forms::Label());
			this->label212 = (gcnew System::Windows::Forms::Label());
			this->label215 = (gcnew System::Windows::Forms::Label());
			this->label216 = (gcnew System::Windows::Forms::Label());
			this->groupBox83 = (gcnew System::Windows::Forms::GroupBox());
			this->label217 = (gcnew System::Windows::Forms::Label());
			this->label218 = (gcnew System::Windows::Forms::Label());
			this->label219 = (gcnew System::Windows::Forms::Label());
			this->label220 = (gcnew System::Windows::Forms::Label());
			this->groupBox84 = (gcnew System::Windows::Forms::GroupBox());
			this->label221 = (gcnew System::Windows::Forms::Label());
			this->label222 = (gcnew System::Windows::Forms::Label());
			this->label223 = (gcnew System::Windows::Forms::Label());
			this->label224 = (gcnew System::Windows::Forms::Label());
			this->groupBox85 = (gcnew System::Windows::Forms::GroupBox());
			this->label225 = (gcnew System::Windows::Forms::Label());
			this->label226 = (gcnew System::Windows::Forms::Label());
			this->label227 = (gcnew System::Windows::Forms::Label());
			this->label230 = (gcnew System::Windows::Forms::Label());
			this->label229 = (gcnew System::Windows::Forms::Label());
			this->label231 = (gcnew System::Windows::Forms::Label());
			this->label232 = (gcnew System::Windows::Forms::Label());
			this->label233 = (gcnew System::Windows::Forms::Label());
			this->label234 = (gcnew System::Windows::Forms::Label());
			this->label235 = (gcnew System::Windows::Forms::Label());
			this->label236 = (gcnew System::Windows::Forms::Label());
			this->label239 = (gcnew System::Windows::Forms::Label());
			this->SINGLE_RDM_VIEW = (gcnew System::Windows::Forms::TabPage());
			this->Free_Flight_PB_MAP = (gcnew System::Windows::Forms::Button());
			this->Load_PB_MAP = (gcnew System::Windows::Forms::Button());
			this->lbl_MAP_location = (gcnew System::Windows::Forms::Label());
			this->label262 = (gcnew System::Windows::Forms::Label());
			this->label261 = (gcnew System::Windows::Forms::Label());
			this->groupBox113 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox112 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox111 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox110 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox109 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox108 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox107 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox106 = (gcnew System::Windows::Forms::GroupBox());
			this->label260 = (gcnew System::Windows::Forms::Label());
			this->lbox_select_RDM = (gcnew System::Windows::Forms::ListBox());
			this->label253 = (gcnew System::Windows::Forms::Label());
			this->label256 = (gcnew System::Windows::Forms::Label());
			this->groupBox105 = (gcnew System::Windows::Forms::GroupBox());
			this->label257 = (gcnew System::Windows::Forms::Label());
			this->label258 = (gcnew System::Windows::Forms::Label());
			this->label259 = (gcnew System::Windows::Forms::Label());
			this->label252 = (gcnew System::Windows::Forms::Label());
			this->PB_RDM_COLOR_MAP = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox87 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox88 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_velocity_6 = (gcnew System::Windows::Forms::Label());
			this->groupBox89 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_velocity_5 = (gcnew System::Windows::Forms::Label());
			this->groupBox90 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_velocity_4 = (gcnew System::Windows::Forms::Label());
			this->groupBox91 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox92 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_velocity_1 = (gcnew System::Windows::Forms::Label());
			this->groupBox93 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_velocity_2 = (gcnew System::Windows::Forms::Label());
			this->groupBox94 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_velocity_3 = (gcnew System::Windows::Forms::Label());
			this->groupBox95 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox96 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox97 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_range_7 = (gcnew System::Windows::Forms::Label());
			this->groupBox98 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_range_6 = (gcnew System::Windows::Forms::Label());
			this->groupBox99 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_range_5 = (gcnew System::Windows::Forms::Label());
			this->groupBox100 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_range_4 = (gcnew System::Windows::Forms::Label());
			this->groupBox101 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_range_3 = (gcnew System::Windows::Forms::Label());
			this->groupBox102 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_range_2 = (gcnew System::Windows::Forms::Label());
			this->groupBox103 = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_range_1 = (gcnew System::Windows::Forms::Label());
			this->groupBox104 = (gcnew System::Windows::Forms::GroupBox());
			this->label269 = (gcnew System::Windows::Forms::Label());
			this->lbl_velocity_min = (gcnew System::Windows::Forms::Label());
			this->lbl_velocity_max = (gcnew System::Windows::Forms::Label());
			this->lbl_range_max = (gcnew System::Windows::Forms::Label());
			this->label274 = (gcnew System::Windows::Forms::Label());
			this->Lbl_RDM = (gcnew System::Windows::Forms::Label());
			this->PB_RDM = (gcnew System::Windows::Forms::PictureBox());
			this->label282 = (gcnew System::Windows::Forms::Label());
			this->label283 = (gcnew System::Windows::Forms::Label());
			this->label284 = (gcnew System::Windows::Forms::Label());
			this->label285 = (gcnew System::Windows::Forms::Label());
			this->label286 = (gcnew System::Windows::Forms::Label());
			this->label287 = (gcnew System::Windows::Forms::Label());
			this->label288 = (gcnew System::Windows::Forms::Label());
			this->label289 = (gcnew System::Windows::Forms::Label());
			this->PB_MAP_chart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->RADAR_VIEW = (gcnew System::Windows::Forms::TabPage());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->T_VR_Noise = (gcnew System::Windows::Forms::TextBox());
			this->label248 = (gcnew System::Windows::Forms::Label());
			this->T_HR_Noise = (gcnew System::Windows::Forms::TextBox());
			this->label250 = (gcnew System::Windows::Forms::Label());
			this->T_VL_Noise = (gcnew System::Windows::Forms::TextBox());
			this->T_HL_Noise = (gcnew System::Windows::Forms::TextBox());
			this->label254 = (gcnew System::Windows::Forms::Label());
			this->label255 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_AOA_H_5 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox86 = (gcnew System::Windows::Forms::GroupBox());
			this->F_POL_Target_selector = (gcnew System::Windows::Forms::NumericUpDown());
			this->label243 = (gcnew System::Windows::Forms::Label());
			this->label242 = (gcnew System::Windows::Forms::Label());
			this->POL_Copy = (gcnew System::Windows::Forms::TextBox());
			this->Polarization_Box = (gcnew System::Windows::Forms::PictureBox());
			this->B_TGT_AOA_V_5 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->B_TGT_VR_SNR_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_HR_SNR_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_VR_SNR_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_VL_SNR_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_VR_SNR_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_HR_SNR_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_VR_SNR_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_HL_SNR_4 = (gcnew System::Windows::Forms::TextBox());
			this->label249 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_HR_SNR_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_VL_SNR_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_HR_SNR_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_RELIABILITY_5 = (gcnew System::Windows::Forms::TextBox());
			this->label247 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_VL_SNR_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_HL_SNR_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_VL_SNR_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_V_5 = (gcnew System::Windows::Forms::TextBox());
			this->label246 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_HL_SNR_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_P_5 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_HL_SNR_1 = (gcnew System::Windows::Forms::TextBox());
			this->label245 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_D_5 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_R_5 = (gcnew System::Windows::Forms::TextBox());
			this->label157 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_RELIABILITY_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_V_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_P_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_D_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_R_4 = (gcnew System::Windows::Forms::TextBox());
			this->label156 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_RELIABILITY_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_RELIABILITY_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_RELIABILITY_1 = (gcnew System::Windows::Forms::TextBox());
			this->label151 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_V_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_P_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_D_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_R_3 = (gcnew System::Windows::Forms::TextBox());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_V_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_P_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_D_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_R_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_V_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_P_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_D_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_R_1 = (gcnew System::Windows::Forms::TextBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_POL_L_5 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_POL_R_5 = (gcnew System::Windows::Forms::TextBox());
			this->B_RADAR_PLOT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label152 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_POL_R_1 = (gcnew System::Windows::Forms::TextBox());
			this->label153 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_POL_L_1 = (gcnew System::Windows::Forms::TextBox());
			this->label154 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_AOA_V_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_AOA_H_4 = (gcnew System::Windows::Forms::TextBox());
			this->label155 = (gcnew System::Windows::Forms::Label());
			this->B_TGT_AOA_V_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_AOA_H_1 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_POL_L_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_POL_R_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_POL_R_4 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_POL_L_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_AOA_V_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_AOA_H_2 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_POL_R_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_POL_L_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_AOA_V_3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TGT_AOA_H_3 = (gcnew System::Windows::Forms::TextBox());
			this->Flash = (gcnew System::Windows::Forms::TabPage());
			this->B_RESET_ARC = (gcnew System::Windows::Forms::Button());
			this->B_MAIN_config = (gcnew System::Windows::Forms::Button());
			this->B_FLASH_WRITE_TO_FILE = (gcnew System::Windows::Forms::Button());
			this->B_FLASH_READ_FROM_FILE = (gcnew System::Windows::Forms::Button());
			this->B_FLASH_RETRIVE = (gcnew System::Windows::Forms::Button());
			this->B_FLASH_WRITE = (gcnew System::Windows::Forms::Button());
			this->B_FLASH_READ = (gcnew System::Windows::Forms::Button());
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->B_CALIBRATOR_CALIBRATE = (gcnew System::Windows::Forms::Button());
			this->B_PROBE_CALIBRATE = (gcnew System::Windows::Forms::Button());
			this->B_PROBE_RESET = (gcnew System::Windows::Forms::Button());
			this->label177 = (gcnew System::Windows::Forms::Label());
			this->label176 = (gcnew System::Windows::Forms::Label());
			this->label175 = (gcnew System::Windows::Forms::Label());
			this->B_CALIBRATOR_RESET = (gcnew System::Windows::Forms::Button());
			this->label171 = (gcnew System::Windows::Forms::Label());
			this->label170 = (gcnew System::Windows::Forms::Label());
			this->label118 = (gcnew System::Windows::Forms::Label());
			this->label117 = (gcnew System::Windows::Forms::Label());
			this->label174 = (gcnew System::Windows::Forms::Label());
			this->label173 = (gcnew System::Windows::Forms::Label());
			this->label172 = (gcnew System::Windows::Forms::Label());
			this->label136 = (gcnew System::Windows::Forms::Label());
			this->label137 = (gcnew System::Windows::Forms::Label());
			this->label165 = (gcnew System::Windows::Forms::Label());
			this->label169 = (gcnew System::Windows::Forms::Label());
			this->B_CALIBRATOR_RV_Q = (gcnew System::Windows::Forms::TextBox());
			this->B_CALIBRATOR_RH_Q = (gcnew System::Windows::Forms::TextBox());
			this->B_CALIBRATOR_LH_Q = (gcnew System::Windows::Forms::TextBox());
			this->B_CALIBRATOR_LV_Q = (gcnew System::Windows::Forms::TextBox());
			this->B_CALIBRATOR_RV_I = (gcnew System::Windows::Forms::TextBox());
			this->B_CALIBRATOR_RH_I = (gcnew System::Windows::Forms::TextBox());
			this->B_CALIBRATOR_LH_I = (gcnew System::Windows::Forms::TextBox());
			this->B_CALIBRATOR_LV_I = (gcnew System::Windows::Forms::TextBox());
			this->label145 = (gcnew System::Windows::Forms::Label());
			this->label144 = (gcnew System::Windows::Forms::Label());
			this->label143 = (gcnew System::Windows::Forms::Label());
			this->label142 = (gcnew System::Windows::Forms::Label());
			this->label141 = (gcnew System::Windows::Forms::Label());
			this->label140 = (gcnew System::Windows::Forms::Label());
			this->label139 = (gcnew System::Windows::Forms::Label());
			this->label138 = (gcnew System::Windows::Forms::Label());
			this->B_CORRECTION_RV_Q = (gcnew System::Windows::Forms::TextBox());
			this->B_CORRECTION_RH_Q = (gcnew System::Windows::Forms::TextBox());
			this->B_CORRECTION_LH_Q = (gcnew System::Windows::Forms::TextBox());
			this->B_CORRECTION_LV_Q = (gcnew System::Windows::Forms::TextBox());
			this->B_CORRECTION_RV_I = (gcnew System::Windows::Forms::TextBox());
			this->B_CORRECTION_RH_I = (gcnew System::Windows::Forms::TextBox());
			this->B_CORRECTION_LH_I = (gcnew System::Windows::Forms::TextBox());
			this->B_CORRECTION_LV_I = (gcnew System::Windows::Forms::TextBox());
			this->B_CALIBRATOR_TGT_END = (gcnew System::Windows::Forms::TextBox());
			this->B_CALIBRATOR_TGT_START = (gcnew System::Windows::Forms::TextBox());
			this->B_PROBE_CALIBRATE_TGT_START = (gcnew System::Windows::Forms::TextBox());
			this->B_PROBE_CALIBRATE_TGT_END = (gcnew System::Windows::Forms::TextBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->F_Target_detection_2nd_threshold = (gcnew System::Windows::Forms::NumericUpDown());
			this->label240 = (gcnew System::Windows::Forms::Label());
			this->B_MAX_VELOCITY_MS = (gcnew System::Windows::Forms::TextBox());
			this->label228 = (gcnew System::Windows::Forms::Label());
			this->F_MINIMUM_RANGE_METER = (gcnew System::Windows::Forms::NumericUpDown());
			this->label210 = (gcnew System::Windows::Forms::Label());
			this->label115 = (gcnew System::Windows::Forms::Label());
			this->F_BATCH_DURATION = (gcnew System::Windows::Forms::TextBox());
			this->F_AGC_threshold = (gcnew System::Windows::Forms::NumericUpDown());
			this->label109 = (gcnew System::Windows::Forms::Label());
			this->F_RANGE_DECIMATION = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_Target_detection_1st_threshold = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_RANGE_meter = (gcnew System::Windows::Forms::NumericUpDown());
			this->label160 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->F_MAX_VELOCITY = (gcnew System::Windows::Forms::NumericUpDown());
			this->label159 = (gcnew System::Windows::Forms::Label());
			this->F_OFFSET_sample = (gcnew System::Windows::Forms::NumericUpDown());
			this->label101 = (gcnew System::Windows::Forms::Label());
			this->label97 = (gcnew System::Windows::Forms::Label());
			this->F_Number_of_buffers = (gcnew System::Windows::Forms::NumericUpDown());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label98 = (gcnew System::Windows::Forms::Label());
			this->F_TxRx_control_MODE = (gcnew System::Windows::Forms::ListBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->F_PROBE_TEST_gain = (gcnew System::Windows::Forms::NumericUpDown());
			this->label103 = (gcnew System::Windows::Forms::Label());
			this->F_PROBE_TEST_profile = (gcnew System::Windows::Forms::NumericUpDown());
			this->label102 = (gcnew System::Windows::Forms::Label());
			this->F_SYSTEM_ID = (gcnew System::Windows::Forms::NumericUpDown());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->F_RF2_ON = (gcnew System::Windows::Forms::CheckBox());
			this->label100 = (gcnew System::Windows::Forms::Label());
			this->F_TX_LO_TR = (gcnew System::Windows::Forms::CheckBox());
			this->panel13 = (gcnew System::Windows::Forms::Panel());
			this->F_IF_SELECT_PROBE_B = (gcnew System::Windows::Forms::RadioButton());
			this->F_IF_SELECT_PROBE_A = (gcnew System::Windows::Forms::RadioButton());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->F_IF_SELECT_TX3_B = (gcnew System::Windows::Forms::RadioButton());
			this->F_IF_SELECT_TX3_A = (gcnew System::Windows::Forms::RadioButton());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->F_PROBE_SELECT_SAMPLE = (gcnew System::Windows::Forms::RadioButton());
			this->F_PROBE_SELECT_ANT = (gcnew System::Windows::Forms::RadioButton());
			this->label146 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->F_IF_SELECT_TX2_B = (gcnew System::Windows::Forms::RadioButton());
			this->F_IF_SELECT_TX2_A = (gcnew System::Windows::Forms::RadioButton());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->F_IF_SELECT_TX1_B = (gcnew System::Windows::Forms::RadioButton());
			this->F_IF_SELECT_TX1_A = (gcnew System::Windows::Forms::RadioButton());
			this->F_TX1_ON = (gcnew System::Windows::Forms::CheckBox());
			this->F_PROBE_ON = (gcnew System::Windows::Forms::CheckBox());
			this->F_TX3_ON = (gcnew System::Windows::Forms::CheckBox());
			this->label99 = (gcnew System::Windows::Forms::Label());
			this->F_TX2_ON = (gcnew System::Windows::Forms::CheckBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->F_ATTN_RX4 = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_IO_UPDATE_ON = (gcnew System::Windows::Forms::CheckBox());
			this->F_Profile_AD9910B = (gcnew System::Windows::Forms::NumericUpDown());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->F_Profile_AD9910A = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_FIFO_length = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_chip_length_AD9910A = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_Buffer_length = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_ATTN_RX3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_chip_length_AD9910B = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_IO_UPDATE_rate = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_ATTN_RX2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_AD9910_Set_aux_dac_B = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_AD9910_Set_aux_dac_A = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_ATTN_RX1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->F_ATTN_TX3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->F_ATTN_TX2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->F_ATTN_TX1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->label135 = (gcnew System::Windows::Forms::Label());
			this->label121 = (gcnew System::Windows::Forms::Label());
			this->F_CALIBRATOR_TGT_START = (gcnew System::Windows::Forms::NumericUpDown());
			this->label119 = (gcnew System::Windows::Forms::Label());
			this->F_CALIBRATOR_TGT_END = (gcnew System::Windows::Forms::NumericUpDown());
			this->label120 = (gcnew System::Windows::Forms::Label());
			this->F_PROBE_CALIBRATE_TGT_START = (gcnew System::Windows::Forms::NumericUpDown());
			this->label104 = (gcnew System::Windows::Forms::Label());
			this->F_PROBE_CALIBRATE_TGT_END = (gcnew System::Windows::Forms::NumericUpDown());
			this->label105 = (gcnew System::Windows::Forms::Label());
			this->Debug = (gcnew System::Windows::Forms::TabPage());
			this->B_PROBE_TEST = (gcnew System::Windows::Forms::Button());
			this->B_SNAPSHOT = (gcnew System::Windows::Forms::Button());
			this->label193 = (gcnew System::Windows::Forms::Label());
			this->label192 = (gcnew System::Windows::Forms::Label());
			this->label191 = (gcnew System::Windows::Forms::Label());
			this->label190 = (gcnew System::Windows::Forms::Label());
			this->label188 = (gcnew System::Windows::Forms::Label());
			this->label189 = (gcnew System::Windows::Forms::Label());
			this->label185 = (gcnew System::Windows::Forms::Label());
			this->label187 = (gcnew System::Windows::Forms::Label());
			this->label183 = (gcnew System::Windows::Forms::Label());
			this->label184 = (gcnew System::Windows::Forms::Label());
			this->label186 = (gcnew System::Windows::Forms::Label());
			this->label182 = (gcnew System::Windows::Forms::Label());
			this->label181 = (gcnew System::Windows::Forms::Label());
			this->label180 = (gcnew System::Windows::Forms::Label());
			this->label179 = (gcnew System::Windows::Forms::Label());
			this->label178 = (gcnew System::Windows::Forms::Label());
			this->B_PROBE_TEST_PLOT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->Mainenance = (gcnew System::Windows::Forms::TabPage());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->G_Upload_RF_MCU = (gcnew System::Windows::Forms::Button());
			this->B_RF_MCU_Browse = (gcnew System::Windows::Forms::Button());
			this->B_Out_RF_MCU = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->B_RF_MCU_Version = (gcnew System::Windows::Forms::TextBox());
			this->L_BUL_status_RF_MCU = (gcnew System::Windows::Forms::Label());
			this->B_BUL_status_RF_MCU = (gcnew System::Windows::Forms::TextBox());
			this->CHAB_BUL_Selector = (gcnew System::Windows::Forms::ComboBox());
			this->G_Upload_MCU = (gcnew System::Windows::Forms::Button());
			this->G_Upload_CHAB = (gcnew System::Windows::Forms::Button());
			this->G_Upload_DET = (gcnew System::Windows::Forms::Button());
			this->G_Upload_OMR = (gcnew System::Windows::Forms::Button());
			this->B_MCU_Browse = (gcnew System::Windows::Forms::Button());
			this->B_CHAB_Browse = (gcnew System::Windows::Forms::Button());
			this->B_Out_MCU = (gcnew System::Windows::Forms::TextBox());
			this->B_Out_CHAB = (gcnew System::Windows::Forms::TextBox());
			this->label107 = (gcnew System::Windows::Forms::Label());
			this->label106 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->B_DET_Browse = (gcnew System::Windows::Forms::Button());
			this->B_Out_DET = (gcnew System::Windows::Forms::TextBox());
			this->L_BUL_status_MCU = (gcnew System::Windows::Forms::Label());
			this->B_BUL_status_OMR = (gcnew System::Windows::Forms::TextBox());
			this->B_BUL_status_DET = (gcnew System::Windows::Forms::TextBox());
			this->B_BUL_status_MCU = (gcnew System::Windows::Forms::TextBox());
			this->B_label1 = (gcnew System::Windows::Forms::Label());
			this->L_BUL_status_OMR = (gcnew System::Windows::Forms::Label());
			this->L_BUL_status_CHB = (gcnew System::Windows::Forms::Label());
			this->B_OMR_Browse = (gcnew System::Windows::Forms::Button());
			this->L_BUL_status_DET = (gcnew System::Windows::Forms::Label());
			this->B_BUL_status_CHB = (gcnew System::Windows::Forms::TextBox());
			this->B_BUL_status_CHA = (gcnew System::Windows::Forms::TextBox());
			this->B_ResetAfterUpload = (gcnew System::Windows::Forms::CheckBox());
			this->B_Out_OMR = (gcnew System::Windows::Forms::TextBox());
			this->L_BUL_status_CHA = (gcnew System::Windows::Forms::Label());
			this->LAB_Experiments = (gcnew System::Windows::Forms::TabPage());
			this->B_CALIBRATOR_DATA = (gcnew System::Windows::Forms::GroupBox());
			this->label280 = (gcnew System::Windows::Forms::Label());
			this->B_LAB_SNR = (gcnew System::Windows::Forms::TextBox());
			this->label281 = (gcnew System::Windows::Forms::Label());
			this->B_LAB_CALIBRATOR_START = (gcnew System::Windows::Forms::Button());
			this->label266 = (gcnew System::Windows::Forms::Label());
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE = (gcnew System::Windows::Forms::Button());
			this->label277 = (gcnew System::Windows::Forms::Label());
			this->B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE = (gcnew System::Windows::Forms::TextBox());
			this->B_LAB_TOTAL_CYCLES = (gcnew System::Windows::Forms::TextBox());
			this->label276 = (gcnew System::Windows::Forms::Label());
			this->label275 = (gcnew System::Windows::Forms::Label());
			this->B_LAB_CYCLE = (gcnew System::Windows::Forms::TextBox());
			this->B_LAB_DOPPLER = (gcnew System::Windows::Forms::TextBox());
			this->label273 = (gcnew System::Windows::Forms::Label());
			this->label267 = (gcnew System::Windows::Forms::Label());
			this->B_ROTATOR_DATA = (gcnew System::Windows::Forms::GroupBox());
			this->label294 = (gcnew System::Windows::Forms::Label());
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE = (gcnew System::Windows::Forms::Button());
			this->B_LAB_ROTATOR_DATA_FILE_TO_SAVE = (gcnew System::Windows::Forms::TextBox());
			this->B_ELEVATION_RESOLUTION = (gcnew System::Windows::Forms::TextBox());
			this->label293 = (gcnew System::Windows::Forms::Label());
			this->B_AZIMUTH_RESOLUTION = (gcnew System::Windows::Forms::TextBox());
			this->label292 = (gcnew System::Windows::Forms::Label());
			this->B_CURRENT_ELEVATION = (gcnew System::Windows::Forms::TextBox());
			this->label291 = (gcnew System::Windows::Forms::Label());
			this->B_CURRENT_AZIMUTH = (gcnew System::Windows::Forms::TextBox());
			this->B_LAB_ELEVATION = (gcnew System::Windows::Forms::NumericUpDown());
			this->label290 = (gcnew System::Windows::Forms::Label());
			this->B_ROTATOR_COM_PORT = (gcnew System::Windows::Forms::ComboBox());
			this->B_COM = (gcnew System::Windows::Forms::Label());
			this->B_LAB_AZIMUTH = (gcnew System::Windows::Forms::NumericUpDown());
			this->lbl_azimuth = (gcnew System::Windows::Forms::Label());
			this->B_AZIMUTH = (gcnew System::Windows::Forms::Label());
			this->label251 = (gcnew System::Windows::Forms::Label());
			this->B_SCREEN_WIDTH_OF_VIEWER = (gcnew System::Windows::Forms::TrackBar());
			this->label263 = (gcnew System::Windows::Forms::Label());
			this->B_RF_TEMP = (gcnew System::Windows::Forms::TextBox());
			this->B_HMC830_PLL = (gcnew System::Windows::Forms::TextBox());
			this->L_RF_BOARD_TEMP = (gcnew System::Windows::Forms::Label());
			this->L_HMC830_PLL = (gcnew System::Windows::Forms::Label());
			this->B_RF_MCU_TEMP = (gcnew System::Windows::Forms::TextBox());
			this->L_RF_MCU_TEMP = (gcnew System::Windows::Forms::Label());
			this->A_SCOPE_VIEW = (gcnew System::Windows::Forms::TabPage());
			this->label158 = (gcnew System::Windows::Forms::Label());
			this->B_A_SCOPE_DOPPLER = (gcnew System::Windows::Forms::TextBox());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->RB_BARKER_PULSE = (gcnew System::Windows::Forms::RadioButton());
			this->RB_SINGLE_PULSE = (gcnew System::Windows::Forms::RadioButton());
			this->B_SATURATION_V_LEFT = (gcnew System::Windows::Forms::PictureBox());
			this->B_SATURATION_V_RIGHT = (gcnew System::Windows::Forms::PictureBox());
			this->B_SATURATION_H_RIGHT = (gcnew System::Windows::Forms::PictureBox());
			this->B_SATURATION_H_LEFT = (gcnew System::Windows::Forms::PictureBox());
			this->B_SCOPE_V_RIGHT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->B_SCOPE_V_LEFT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->B_SCOPE_H_RIGHT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->B_SCOPE_H_LEFT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->W_DATA_RECORDING = (gcnew System::Windows::Forms::Button());
			this->W_START_WORK_CIRC = (gcnew System::Windows::Forms::Button());
			this->label147 = (gcnew System::Windows::Forms::Label());
			this->B_IO_UPDATE_rate = (gcnew System::Windows::Forms::TextBox());
			this->B_AD9910_Set_aux_dac_B = (gcnew System::Windows::Forms::TextBox());
			this->B_chip_length_AD9910B = (gcnew System::Windows::Forms::TextBox());
			this->B_Profile_AD9910B = (gcnew System::Windows::Forms::TextBox());
			this->B_AD9910_Set_aux_dac_A = (gcnew System::Windows::Forms::TextBox());
			this->B_chip_length_AD9910A = (gcnew System::Windows::Forms::TextBox());
			this->B_Profile_AD9910A = (gcnew System::Windows::Forms::TextBox());
			this->label129 = (gcnew System::Windows::Forms::Label());
			this->label130 = (gcnew System::Windows::Forms::Label());
			this->label131 = (gcnew System::Windows::Forms::Label());
			this->label132 = (gcnew System::Windows::Forms::Label());
			this->label133 = (gcnew System::Windows::Forms::Label());
			this->label134 = (gcnew System::Windows::Forms::Label());
			this->B_SelectLogFile_Of_Calibrator = (gcnew System::Windows::Forms::OpenFileDialog());
			this->B_RANGE_meter = (gcnew System::Windows::Forms::TextBox());
			this->label78 = (gcnew System::Windows::Forms::Label());
			this->B_OFFSET_sample = (gcnew System::Windows::Forms::TextBox());
			this->label76 = (gcnew System::Windows::Forms::Label());
			this->B_FIFO_length = (gcnew System::Windows::Forms::TextBox());
			this->B_Buffer_length = (gcnew System::Windows::Forms::TextBox());
			this->B_Number_of_buffers = (gcnew System::Windows::Forms::TextBox());
			this->label111 = (gcnew System::Windows::Forms::Label());
			this->label112 = (gcnew System::Windows::Forms::Label());
			this->label113 = (gcnew System::Windows::Forms::Label());
			this->B_GROUP_RF = (gcnew System::Windows::Forms::GroupBox());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->B_RF2_ON = (gcnew System::Windows::Forms::TextBox());
			this->label149 = (gcnew System::Windows::Forms::Label());
			this->label148 = (gcnew System::Windows::Forms::Label());
			this->B_TxRx_control_MODE = (gcnew System::Windows::Forms::TextBox());
			this->B_SYSTEM_ID = (gcnew System::Windows::Forms::TextBox());
			this->B_ANT_SAMPLE_SELECT = (gcnew System::Windows::Forms::TextBox());
			this->B_IF_SELECT_PROBE = (gcnew System::Windows::Forms::TextBox());
			this->B_IF_SELECT_TX3 = (gcnew System::Windows::Forms::TextBox());
			this->B_IF_SELECT_TX2 = (gcnew System::Windows::Forms::TextBox());
			this->B_IF_SELECT_TX1 = (gcnew System::Windows::Forms::TextBox());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->B_IO_UPDATE_ON = (gcnew System::Windows::Forms::TextBox());
			this->B_TX_ON3 = (gcnew System::Windows::Forms::TextBox());
			this->B_TX_LO_TR = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->B_SAMPLE_ON_OFF = (gcnew System::Windows::Forms::TextBox());
			this->B_TX_ON2 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->B_TX_ON1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->B_ATTN_RX4 = (gcnew System::Windows::Forms::TextBox());
			this->B_ATTN_RX3 = (gcnew System::Windows::Forms::TextBox());
			this->B_ATTN_RX2 = (gcnew System::Windows::Forms::TextBox());
			this->B_ATTN_RX1 = (gcnew System::Windows::Forms::TextBox());
			this->B_ATTN_TX3 = (gcnew System::Windows::Forms::TextBox());
			this->B_ATTN_TX2 = (gcnew System::Windows::Forms::TextBox());
			this->B_ATTN_TX1 = (gcnew System::Windows::Forms::TextBox());
			this->label116 = (gcnew System::Windows::Forms::Label());
			this->label122 = (gcnew System::Windows::Forms::Label());
			this->label123 = (gcnew System::Windows::Forms::Label());
			this->label124 = (gcnew System::Windows::Forms::Label());
			this->label125 = (gcnew System::Windows::Forms::Label());
			this->label126 = (gcnew System::Windows::Forms::Label());
			this->label127 = (gcnew System::Windows::Forms::Label());
			this->label128 = (gcnew System::Windows::Forms::Label());
			this->B_RANGE_DECIMATION = (gcnew System::Windows::Forms::TextBox());
			this->label162 = (gcnew System::Windows::Forms::Label());
			this->B_MAX_VELOCITY = (gcnew System::Windows::Forms::TextBox());
			this->label161 = (gcnew System::Windows::Forms::Label());
			this->label150 = (gcnew System::Windows::Forms::Label());
			this->B_Target_detection_1st_threshold = (gcnew System::Windows::Forms::TextBox());
			this->B_GROUP_ALGORITHMS = (gcnew System::Windows::Forms::GroupBox());
			this->label241 = (gcnew System::Windows::Forms::Label());
			this->B_Target_detection_2nd_threshold = (gcnew System::Windows::Forms::TextBox());
			this->B_BATCH_DURATION = (gcnew System::Windows::Forms::TextBox());
			this->B_AGC_threshold = (gcnew System::Windows::Forms::TextBox());
			this->label110 = (gcnew System::Windows::Forms::Label());
			this->label114 = (gcnew System::Windows::Forms::Label());
			this->B_GROUP_STATE_MACHINES = (gcnew System::Windows::Forms::GroupBox());
			this->label211 = (gcnew System::Windows::Forms::Label());
			this->B_CHB_WORK_STATE = (gcnew System::Windows::Forms::TextBox());
			this->B_DET_INITIALIZATION_STATE = (gcnew System::Windows::Forms::TextBox());
			this->label168 = (gcnew System::Windows::Forms::Label());
			this->label167 = (gcnew System::Windows::Forms::Label());
			this->B_DET_FIRST_DETECTION_STATE = (gcnew System::Windows::Forms::TextBox());
			this->label166 = (gcnew System::Windows::Forms::Label());
			this->B_DET_CALIBRATE_STATE = (gcnew System::Windows::Forms::TextBox());
			this->label164 = (gcnew System::Windows::Forms::Label());
			this->label163 = (gcnew System::Windows::Forms::Label());
			this->B_CHA_WORK_STATE = (gcnew System::Windows::Forms::TextBox());
			this->B_folderBrowser_BUL = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->B_fileBrowser_TOM = (gcnew System::Windows::Forms::OpenFileDialog());
			this->toolTipHR = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTipVR = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTipHL = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTipVL = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->L_OMR_STATUS = (gcnew System::Windows::Forms::Label());
			this->L_MCU_STATUS = (gcnew System::Windows::Forms::Label());
			this->L_CHB_STATUS = (gcnew System::Windows::Forms::Label());
			this->L_CHA_STATUS = (gcnew System::Windows::Forms::Label());
			this->L_DET_STATUS = (gcnew System::Windows::Forms::Label());
			this->L_LMK01000 = (gcnew System::Windows::Forms::Label());
			this->L_LMK04828 = (gcnew System::Windows::Forms::Label());
			this->L_FPGA_B = (gcnew System::Windows::Forms::Label());
			this->L_FPGA_A = (gcnew System::Windows::Forms::Label());
			this->L_AD6655_B = (gcnew System::Windows::Forms::Label());
			this->L_AD6655_A = (gcnew System::Windows::Forms::Label());
			this->B_DEBUG_COUNT = (gcnew System::Windows::Forms::TextBox());
			this->B_PERIPHERALS_LMK04828 = (gcnew System::Windows::Forms::TextBox());
			this->B_PERIPHERALS_LMK01000 = (gcnew System::Windows::Forms::TextBox());
			this->B_OMR_STATUS = (gcnew System::Windows::Forms::TextBox());
			this->L_UCD9222_DET_internal = (gcnew System::Windows::Forms::Label());
			this->B_DET_STATUS = (gcnew System::Windows::Forms::TextBox());
			this->L_UCD9222_DET_external = (gcnew System::Windows::Forms::Label());
			this->B_CHA_STATUS = (gcnew System::Windows::Forms::TextBox());
			this->L_UCD9222_CHA_external = (gcnew System::Windows::Forms::Label());
			this->B_CHB_STATUS = (gcnew System::Windows::Forms::TextBox());
			this->B_MCU_STATUS = (gcnew System::Windows::Forms::TextBox());
			this->B_PERIPHERALS_AD6655_A = (gcnew System::Windows::Forms::TextBox());
			this->B_PERIPHERALS_AD6655_B = (gcnew System::Windows::Forms::TextBox());
			this->B_MCU_TEMP = (gcnew System::Windows::Forms::TextBox());
			this->B_PERIPHERALS_FPGA_A = (gcnew System::Windows::Forms::TextBox());
			this->B_PERIPHERALS_FPGA_B = (gcnew System::Windows::Forms::TextBox());
			this->B_UCD9222_DET_temperature_internal = (gcnew System::Windows::Forms::TextBox());
			this->L_Counter = (gcnew System::Windows::Forms::Label());
			this->L_UCD9222_CHA_internal = (gcnew System::Windows::Forms::Label());
			this->B_UCD9222_CHA_temperature_internal = (gcnew System::Windows::Forms::TextBox());
			this->L_AD9910_B = (gcnew System::Windows::Forms::Label());
			this->L_AD9910_A = (gcnew System::Windows::Forms::Label());
			this->B_UCD9222_CHA_temperature_external = (gcnew System::Windows::Forms::TextBox());
			this->B_PERIPHERALS_AD9910_A = (gcnew System::Windows::Forms::TextBox());
			this->B_PERIPHERALS_AD9910_B = (gcnew System::Windows::Forms::TextBox());
			this->L_MCU_TEMP = (gcnew System::Windows::Forms::Label());
			this->B_GROUP_STATUS = (gcnew System::Windows::Forms::GroupBox());
			this->B_RF_MCU_STATUS = (gcnew System::Windows::Forms::TextBox());
			this->L_RF_MCU_STATUS = (gcnew System::Windows::Forms::Label());
			this->B_UCD9222_DET_temperature_external = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->B_Navigation_Status = (gcnew System::Windows::Forms::TextBox());
			this->label244 = (gcnew System::Windows::Forms::Label());
			this->B_BROWSE_DIR = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->TOOL_TIP_START = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->TOOL_TIP_STOP = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->TOOL_TIP_START_RECORD = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->LOAD_MAP_TOOL_TIP = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->RE_FLIGHT_TOOL_TIP = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->B_SelectLogFile_Of_Rotator = (gcnew System::Windows::Forms::OpenFileDialog());
			this->B_MAX_ERROR_RANGE = (gcnew System::Windows::Forms::NumericUpDown());
			this->label270 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->B_GROUP_FREES->SuspendLayout();
			this->B_GROUP_SENSOR->SuspendLayout();
			this->B_tabControl->SuspendLayout();
			this->MAP_VIEW->SuspendLayout();
			this->B_VISIBLE_OBSTACLES->SuspendLayout();
			this->B_MAP_PANEL->SuspendLayout();
			this->REAL_TIME_TOOL_STRIP->SuspendLayout();
			this->RDM_VIEW->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_Color_Map))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RDM_V_R))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RDM_V_L))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RDM_H_R))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RDM_H_L))->BeginInit();
			this->SINGLE_RDM_VIEW->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_RDM_COLOR_MAP))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_RDM))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_MAP_chart))->BeginInit();
			this->RADAR_VIEW->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox86->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_POL_Target_selector))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Polarization_Box))->BeginInit();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RADAR_PLOT))->BeginInit();
			this->Flash->SuspendLayout();
			this->groupBox11->SuspendLayout();
			this->groupBox7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Target_detection_2nd_threshold))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_MINIMUM_RANGE_METER))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_AGC_threshold))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_RANGE_DECIMATION))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Target_detection_1st_threshold))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_RANGE_meter))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_MAX_VELOCITY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_OFFSET_sample))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Number_of_buffers))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_PROBE_TEST_gain))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_PROBE_TEST_profile))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_SYSTEM_ID))->BeginInit();
			this->groupBox6->SuspendLayout();
			this->panel13->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_RX4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Profile_AD9910B))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Profile_AD9910A))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_FIFO_length))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_chip_length_AD9910A))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Buffer_length))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_RX3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_chip_length_AD9910B))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_IO_UPDATE_rate))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_RX2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_AD9910_Set_aux_dac_B))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_AD9910_Set_aux_dac_A))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_RX1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_TX3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_TX2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_TX1))->BeginInit();
			this->groupBox10->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_CALIBRATOR_TGT_START))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_CALIBRATOR_TGT_END))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_PROBE_CALIBRATE_TGT_START))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_PROBE_CALIBRATE_TGT_END))->BeginInit();
			this->Debug->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_PROBE_TEST_PLOT))->BeginInit();
			this->Mainenance->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->LAB_Experiments->SuspendLayout();
			this->B_CALIBRATOR_DATA->SuspendLayout();
			this->B_ROTATOR_DATA->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_LAB_ELEVATION))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_LAB_AZIMUTH))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCREEN_WIDTH_OF_VIEWER))->BeginInit();
			this->A_SCOPE_VIEW->SuspendLayout();
			this->panel7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SATURATION_V_LEFT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SATURATION_V_RIGHT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SATURATION_H_RIGHT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SATURATION_H_LEFT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_V_RIGHT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_V_LEFT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_H_RIGHT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_H_LEFT))->BeginInit();
			this->B_GROUP_RF->SuspendLayout();
			this->B_GROUP_ALGORITHMS->SuspendLayout();
			this->B_GROUP_STATE_MACHINES->SuspendLayout();
			this->B_GROUP_STATUS->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_MAX_ERROR_RANGE))->BeginInit();
			this->SuspendLayout();
			// 
			// B_OMR_VERSION
			// 
			this->B_OMR_VERSION->Location = System::Drawing::Point(80, 201);
			this->B_OMR_VERSION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_OMR_VERSION->Name = L"B_OMR_VERSION";
			this->B_OMR_VERSION->ReadOnly = true;
			this->B_OMR_VERSION->Size = System::Drawing::Size(53, 20);
			this->B_OMR_VERSION->TabIndex = 0;
			this->B_OMR_VERSION->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_DET_VERSION
			// 
			this->B_DET_VERSION->Location = System::Drawing::Point(210, 201);
			this->B_DET_VERSION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DET_VERSION->Name = L"B_DET_VERSION";
			this->B_DET_VERSION->ReadOnly = true;
			this->B_DET_VERSION->Size = System::Drawing::Size(53, 20);
			this->B_DET_VERSION->TabIndex = 0;
			this->B_DET_VERSION->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->ForeColor = System::Drawing::Color::White;
			this->label48->Location = System::Drawing::Point(527, 204);
			this->label48->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(72, 13);
			this->label48->TabIndex = 15;
			this->label48->Text = L"MCU Version:";
			// 
			// B_label10
			// 
			this->B_label10->AutoSize = true;
			this->B_label10->ForeColor = System::Drawing::Color::White;
			this->B_label10->Location = System::Drawing::Point(4, 204);
			this->B_label10->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->B_label10->Name = L"B_label10";
			this->B_label10->Size = System::Drawing::Size(73, 13);
			this->B_label10->TabIndex = 9;
			this->B_label10->Text = L"OMR Version:";
			// 
			// B_MCU_VERSION
			// 
			this->B_MCU_VERSION->Location = System::Drawing::Point(599, 201);
			this->B_MCU_VERSION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_MCU_VERSION->Name = L"B_MCU_VERSION";
			this->B_MCU_VERSION->ReadOnly = true;
			this->B_MCU_VERSION->Size = System::Drawing::Size(53, 20);
			this->B_MCU_VERSION->TabIndex = 14;
			this->B_MCU_VERSION->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_label11
			// 
			this->B_label11->AutoSize = true;
			this->B_label11->ForeColor = System::Drawing::Color::White;
			this->B_label11->Location = System::Drawing::Point(139, 204);
			this->B_label11->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->B_label11->Name = L"B_label11";
			this->B_label11->Size = System::Drawing::Size(70, 13);
			this->B_label11->TabIndex = 1;
			this->B_label11->Text = L"DET Version:";
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->ForeColor = System::Drawing::Color::White;
			this->label47->Location = System::Drawing::Point(395, 204);
			this->label47->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(70, 13);
			this->label47->TabIndex = 13;
			this->label47->Text = L"CHB Version:";
			// 
			// B_CHA_VERSION
			// 
			this->B_CHA_VERSION->Location = System::Drawing::Point(338, 201);
			this->B_CHA_VERSION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CHA_VERSION->Name = L"B_CHA_VERSION";
			this->B_CHA_VERSION->ReadOnly = true;
			this->B_CHA_VERSION->Size = System::Drawing::Size(53, 20);
			this->B_CHA_VERSION->TabIndex = 10;
			this->B_CHA_VERSION->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CHB_VERSION
			// 
			this->B_CHB_VERSION->Location = System::Drawing::Point(466, 201);
			this->B_CHB_VERSION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CHB_VERSION->Name = L"B_CHB_VERSION";
			this->B_CHB_VERSION->ReadOnly = true;
			this->B_CHB_VERSION->Size = System::Drawing::Size(53, 20);
			this->B_CHB_VERSION->TabIndex = 12;
			this->B_CHB_VERSION->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->ForeColor = System::Drawing::Color::White;
			this->label46->Location = System::Drawing::Point(267, 204);
			this->label46->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(70, 13);
			this->label46->TabIndex = 11;
			this->label46->Text = L"CHA Version:";
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->groupBox1->Controls->Add(this->label73);
			this->groupBox1->Controls->Add(this->B_MATLAB_script);
			this->groupBox1->Controls->Add(this->B_SNAPSHOT_TYPE);
			this->groupBox1->Controls->Add(this->label64);
			this->groupBox1->Controls->Add(this->B_LOG_FOLDER);
			this->groupBox1->Controls->Add(this->B_LOG_FOLDER_BROWSE);
			this->groupBox1->Controls->Add(this->label66);
			this->groupBox1->ForeColor = System::Drawing::Color::White;
			this->groupBox1->Location = System::Drawing::Point(15, 6);
			this->groupBox1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox1->Size = System::Drawing::Size(628, 157);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// label73
			// 
			this->label73->AutoSize = true;
			this->label73->BackColor = System::Drawing::Color::Transparent;
			this->label73->ForeColor = System::Drawing::Color::White;
			this->label73->Location = System::Drawing::Point(262, 43);
			this->label73->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label73->Name = L"label73";
			this->label73->Size = System::Drawing::Size(78, 13);
			this->label73->TabIndex = 156;
			this->label73->Text = L"Snapshot type:";
			// 
			// B_MATLAB_script
			// 
			this->B_MATLAB_script->FormattingEnabled = true;
			this->B_MATLAB_script->Location = System::Drawing::Point(62, 43);
			this->B_MATLAB_script->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_MATLAB_script->Name = L"B_MATLAB_script";
			this->B_MATLAB_script->Size = System::Drawing::Size(200, 108);
			this->B_MATLAB_script->TabIndex = 81;
			this->B_MATLAB_script->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::B_MATLAB_script_SelectedIndexChanged);
			// 
			// B_SNAPSHOT_TYPE
			// 
			this->B_SNAPSHOT_TYPE->FormattingEnabled = true;
			this->B_SNAPSHOT_TYPE->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				L"0\tSNAPSHOT_CPI", L"1\tSNAPSHOT_PRE_FFT",
					L"2\tSNAPSHOT_RDM"
			});
			this->B_SNAPSHOT_TYPE->Location = System::Drawing::Point(346, 40);
			this->B_SNAPSHOT_TYPE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SNAPSHOT_TYPE->Name = L"B_SNAPSHOT_TYPE";
			this->B_SNAPSHOT_TYPE->Size = System::Drawing::Size(276, 108);
			this->B_SNAPSHOT_TYPE->TabIndex = 155;
			this->B_SNAPSHOT_TYPE->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::B_SNAPSHOT_TYPE_SelectedIndexChanged);
			// 
			// label64
			// 
			this->label64->AutoSize = true;
			this->label64->BackColor = System::Drawing::Color::Transparent;
			this->label64->ForeColor = System::Drawing::Color::White;
			this->label64->Location = System::Drawing::Point(20, 48);
			this->label64->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label64->Name = L"label64";
			this->label64->Size = System::Drawing::Size(42, 13);
			this->label64->TabIndex = 80;
			this->label64->Text = L"Scripts:";
			// 
			// B_LOG_FOLDER
			// 
			this->B_LOG_FOLDER->Location = System::Drawing::Point(62, 14);
			this->B_LOG_FOLDER->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LOG_FOLDER->Name = L"B_LOG_FOLDER";
			this->B_LOG_FOLDER->Size = System::Drawing::Size(486, 20);
			this->B_LOG_FOLDER->TabIndex = 4;
			this->B_LOG_FOLDER->TextChanged += gcnew System::EventHandler(this, &MyForm::B_LOG_FOLDER_TextChanged);
			// 
			// B_LOG_FOLDER_BROWSE
			// 
			this->B_LOG_FOLDER_BROWSE->ForeColor = System::Drawing::SystemColors::Desktop;
			this->B_LOG_FOLDER_BROWSE->Location = System::Drawing::Point(550, 13);
			this->B_LOG_FOLDER_BROWSE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LOG_FOLDER_BROWSE->Name = L"B_LOG_FOLDER_BROWSE";
			this->B_LOG_FOLDER_BROWSE->Size = System::Drawing::Size(74, 23);
			this->B_LOG_FOLDER_BROWSE->TabIndex = 5;
			this->B_LOG_FOLDER_BROWSE->Text = L"Browse...";
			this->B_LOG_FOLDER_BROWSE->UseVisualStyleBackColor = true;
			this->B_LOG_FOLDER_BROWSE->Click += gcnew System::EventHandler(this, &MyForm::B_LOG_FOLDER_BROWSE_Click);
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->BackColor = System::Drawing::Color::Transparent;
			this->label66->ForeColor = System::Drawing::Color::White;
			this->label66->Location = System::Drawing::Point(4, 17);
			this->label66->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(57, 13);
			this->label66->TabIndex = 6;
			this->label66->Text = L"Log folder:";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->ForeColor = System::Drawing::Color::White;
			this->label38->Location = System::Drawing::Point(36, 28);
			this->label38->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(31, 13);
			this->label38->TabIndex = 136;
			this->label38->Text = L"Brain";
			// 
			// B_DET_BRAIN_STATE
			// 
			this->B_DET_BRAIN_STATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_BRAIN_STATE->Location = System::Drawing::Point(67, 23);
			this->B_DET_BRAIN_STATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DET_BRAIN_STATE->Name = L"B_DET_BRAIN_STATE";
			this->B_DET_BRAIN_STATE->ReadOnly = true;
			this->B_DET_BRAIN_STATE->Size = System::Drawing::Size(45, 20);
			this->B_DET_BRAIN_STATE->TabIndex = 135;
			this->B_DET_BRAIN_STATE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// L_ACQUISITION
			// 
			this->L_ACQUISITION->AutoSize = true;
			this->L_ACQUISITION->ForeColor = System::Drawing::Color::White;
			this->L_ACQUISITION->Location = System::Drawing::Point(9, 68);
			this->L_ACQUISITION->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_ACQUISITION->Name = L"L_ACQUISITION";
			this->L_ACQUISITION->Size = System::Drawing::Size(58, 13);
			this->L_ACQUISITION->TabIndex = 134;
			this->L_ACQUISITION->Text = L"Acquisition";
			// 
			// B_DET_ACQUISITION_STATE
			// 
			this->B_DET_ACQUISITION_STATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_ACQUISITION_STATE->Location = System::Drawing::Point(67, 65);
			this->B_DET_ACQUISITION_STATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DET_ACQUISITION_STATE->Name = L"B_DET_ACQUISITION_STATE";
			this->B_DET_ACQUISITION_STATE->ReadOnly = true;
			this->B_DET_ACQUISITION_STATE->Size = System::Drawing::Size(45, 20);
			this->B_DET_ACQUISITION_STATE->TabIndex = 133;
			this->B_DET_ACQUISITION_STATE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// L_WORK
			// 
			this->L_WORK->AutoSize = true;
			this->L_WORK->ForeColor = System::Drawing::Color::White;
			this->L_WORK->Location = System::Drawing::Point(35, 48);
			this->L_WORK->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_WORK->Name = L"L_WORK";
			this->L_WORK->Size = System::Drawing::Size(33, 13);
			this->L_WORK->TabIndex = 132;
			this->L_WORK->Text = L"Work";
			// 
			// B_DET_WORK_STATE
			// 
			this->B_DET_WORK_STATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_WORK_STATE->Location = System::Drawing::Point(67, 44);
			this->B_DET_WORK_STATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DET_WORK_STATE->Name = L"B_DET_WORK_STATE";
			this->B_DET_WORK_STATE->ReadOnly = true;
			this->B_DET_WORK_STATE->Size = System::Drawing::Size(45, 20);
			this->B_DET_WORK_STATE->TabIndex = 130;
			this->B_DET_WORK_STATE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_ANGULAR_RATE_Z
			// 
			this->B_SENSOR_ANGULAR_RATE_Z->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ANGULAR_RATE_Z->Location = System::Drawing::Point(43, 630);
			this->B_SENSOR_ANGULAR_RATE_Z->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ANGULAR_RATE_Z->Name = L"B_SENSOR_ANGULAR_RATE_Z";
			this->B_SENSOR_ANGULAR_RATE_Z->ReadOnly = true;
			this->B_SENSOR_ANGULAR_RATE_Z->Size = System::Drawing::Size(34, 20);
			this->B_SENSOR_ANGULAR_RATE_Z->TabIndex = 107;
			this->B_SENSOR_ANGULAR_RATE_Z->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->ForeColor = System::Drawing::Color::White;
			this->label65->Location = System::Drawing::Point(25, 633);
			this->label65->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(17, 13);
			this->label65->TabIndex = 112;
			this->label65->Text = L"Z:";
			// 
			// label68
			// 
			this->label68->AutoSize = true;
			this->label68->ForeColor = System::Drawing::Color::White;
			this->label68->Location = System::Drawing::Point(10, 176);
			this->label68->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(35, 13);
			this->label68->TabIndex = 79;
			this->label68->Text = L"YAW:";
			// 
			// label69
			// 
			this->label69->AutoSize = true;
			this->label69->ForeColor = System::Drawing::Color::White;
			this->label69->Location = System::Drawing::Point(2, 201);
			this->label69->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label69->Name = L"label69";
			this->label69->Size = System::Drawing::Size(42, 13);
			this->label69->TabIndex = 81;
			this->label69->Text = L"PITCH:";
			// 
			// B_SENSOR_ACCELERATION_Z
			// 
			this->B_SENSOR_ACCELERATION_Z->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ACCELERATION_Z->Location = System::Drawing::Point(43, 536);
			this->B_SENSOR_ACCELERATION_Z->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ACCELERATION_Z->Name = L"B_SENSOR_ACCELERATION_Z";
			this->B_SENSOR_ACCELERATION_Z->ReadOnly = true;
			this->B_SENSOR_ACCELERATION_Z->Size = System::Drawing::Size(36, 20);
			this->B_SENSOR_ACCELERATION_Z->TabIndex = 99;
			this->B_SENSOR_ACCELERATION_Z->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_ACCELERATION_Y
			// 
			this->B_SENSOR_ACCELERATION_Y->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ACCELERATION_Y->Location = System::Drawing::Point(43, 514);
			this->B_SENSOR_ACCELERATION_Y->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ACCELERATION_Y->Name = L"B_SENSOR_ACCELERATION_Y";
			this->B_SENSOR_ACCELERATION_Y->ReadOnly = true;
			this->B_SENSOR_ACCELERATION_Y->Size = System::Drawing::Size(36, 20);
			this->B_SENSOR_ACCELERATION_Y->TabIndex = 97;
			this->B_SENSOR_ACCELERATION_Y->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_ACCELERATION_X
			// 
			this->B_SENSOR_ACCELERATION_X->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ACCELERATION_X->Location = System::Drawing::Point(43, 492);
			this->B_SENSOR_ACCELERATION_X->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ACCELERATION_X->Name = L"B_SENSOR_ACCELERATION_X";
			this->B_SENSOR_ACCELERATION_X->ReadOnly = true;
			this->B_SENSOR_ACCELERATION_X->Size = System::Drawing::Size(36, 20);
			this->B_SENSOR_ACCELERATION_X->TabIndex = 96;
			this->B_SENSOR_ACCELERATION_X->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_VELOCITY_Z
			// 
			this->B_SENSOR_VELOCITY_Z->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_VELOCITY_Z->Location = System::Drawing::Point(43, 316);
			this->B_SENSOR_VELOCITY_Z->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_VELOCITY_Z->Name = L"B_SENSOR_VELOCITY_Z";
			this->B_SENSOR_VELOCITY_Z->ReadOnly = true;
			this->B_SENSOR_VELOCITY_Z->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_VELOCITY_Z->TabIndex = 95;
			this->B_SENSOR_VELOCITY_Z->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_VELOCITY_Y
			// 
			this->B_SENSOR_VELOCITY_Y->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_VELOCITY_Y->Location = System::Drawing::Point(43, 294);
			this->B_SENSOR_VELOCITY_Y->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_VELOCITY_Y->Name = L"B_SENSOR_VELOCITY_Y";
			this->B_SENSOR_VELOCITY_Y->ReadOnly = true;
			this->B_SENSOR_VELOCITY_Y->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_VELOCITY_Y->TabIndex = 93;
			this->B_SENSOR_VELOCITY_Y->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_VELOCITY_X
			// 
			this->B_SENSOR_VELOCITY_X->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_VELOCITY_X->Location = System::Drawing::Point(43, 272);
			this->B_SENSOR_VELOCITY_X->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_VELOCITY_X->Name = L"B_SENSOR_VELOCITY_X";
			this->B_SENSOR_VELOCITY_X->ReadOnly = true;
			this->B_SENSOR_VELOCITY_X->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_VELOCITY_X->TabIndex = 91;
			this->B_SENSOR_VELOCITY_X->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_ALTITUDE
			// 
			this->B_SENSOR_ALTITUDE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ALTITUDE->Location = System::Drawing::Point(41, 416);
			this->B_SENSOR_ALTITUDE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ALTITUDE->Name = L"B_SENSOR_ALTITUDE";
			this->B_SENSOR_ALTITUDE->ReadOnly = true;
			this->B_SENSOR_ALTITUDE->Size = System::Drawing::Size(70, 20);
			this->B_SENSOR_ALTITUDE->TabIndex = 89;
			this->B_SENSOR_ALTITUDE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_LONGITUDE
			// 
			this->B_SENSOR_LONGITUDE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_LONGITUDE->Location = System::Drawing::Point(41, 394);
			this->B_SENSOR_LONGITUDE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_LONGITUDE->Name = L"B_SENSOR_LONGITUDE";
			this->B_SENSOR_LONGITUDE->ReadOnly = true;
			this->B_SENSOR_LONGITUDE->Size = System::Drawing::Size(70, 20);
			this->B_SENSOR_LONGITUDE->TabIndex = 87;
			this->B_SENSOR_LONGITUDE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_LATITUDE
			// 
			this->B_SENSOR_LATITUDE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_LATITUDE->Location = System::Drawing::Point(41, 372);
			this->B_SENSOR_LATITUDE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_LATITUDE->Name = L"B_SENSOR_LATITUDE";
			this->B_SENSOR_LATITUDE->ReadOnly = true;
			this->B_SENSOR_LATITUDE->Size = System::Drawing::Size(70, 20);
			this->B_SENSOR_LATITUDE->TabIndex = 85;
			this->B_SENSOR_LATITUDE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_ANGULAR_RATE_Y
			// 
			this->B_SENSOR_ANGULAR_RATE_Y->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ANGULAR_RATE_Y->Location = System::Drawing::Point(43, 608);
			this->B_SENSOR_ANGULAR_RATE_Y->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ANGULAR_RATE_Y->Name = L"B_SENSOR_ANGULAR_RATE_Y";
			this->B_SENSOR_ANGULAR_RATE_Y->ReadOnly = true;
			this->B_SENSOR_ANGULAR_RATE_Y->Size = System::Drawing::Size(34, 20);
			this->B_SENSOR_ANGULAR_RATE_Y->TabIndex = 104;
			this->B_SENSOR_ANGULAR_RATE_Y->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_INS_ROLL
			// 
			this->B_SENSOR_INS_ROLL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_INS_ROLL->Location = System::Drawing::Point(43, 107);
			this->B_SENSOR_INS_ROLL->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_INS_ROLL->Name = L"B_SENSOR_INS_ROLL";
			this->B_SENSOR_INS_ROLL->ReadOnly = true;
			this->B_SENSOR_INS_ROLL->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_INS_ROLL->TabIndex = 83;
			this->B_SENSOR_INS_ROLL->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_ANGULAR_RATE_X
			// 
			this->B_SENSOR_ANGULAR_RATE_X->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ANGULAR_RATE_X->Location = System::Drawing::Point(43, 586);
			this->B_SENSOR_ANGULAR_RATE_X->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ANGULAR_RATE_X->Name = L"B_SENSOR_ANGULAR_RATE_X";
			this->B_SENSOR_ANGULAR_RATE_X->ReadOnly = true;
			this->B_SENSOR_ANGULAR_RATE_X->Size = System::Drawing::Size(34, 20);
			this->B_SENSOR_ANGULAR_RATE_X->TabIndex = 101;
			this->B_SENSOR_ANGULAR_RATE_X->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_INS_PITCH
			// 
			this->B_SENSOR_INS_PITCH->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_INS_PITCH->Location = System::Drawing::Point(43, 85);
			this->B_SENSOR_INS_PITCH->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_INS_PITCH->Name = L"B_SENSOR_INS_PITCH";
			this->B_SENSOR_INS_PITCH->ReadOnly = true;
			this->B_SENSOR_INS_PITCH->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_INS_PITCH->TabIndex = 82;
			this->B_SENSOR_INS_PITCH->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_INS_YAW
			// 
			this->B_SENSOR_INS_YAW->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_INS_YAW->Location = System::Drawing::Point(43, 63);
			this->B_SENSOR_INS_YAW->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_INS_YAW->Name = L"B_SENSOR_INS_YAW";
			this->B_SENSOR_INS_YAW->ReadOnly = true;
			this->B_SENSOR_INS_YAW->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_INS_YAW->TabIndex = 80;
			this->B_SENSOR_INS_YAW->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label1003
			// 
			this->label1003->AutoSize = true;
			this->label1003->ForeColor = System::Drawing::Color::White;
			this->label1003->Location = System::Drawing::Point(19, 318);
			this->label1003->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1003->Name = L"label1003";
			this->label1003->Size = System::Drawing::Size(25, 13);
			this->label1003->TabIndex = 106;
			this->label1003->Text = L"V z:";
			// 
			// label1002
			// 
			this->label1002->AutoSize = true;
			this->label1002->ForeColor = System::Drawing::Color::White;
			this->label1002->Location = System::Drawing::Point(25, 497);
			this->label1002->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1002->Name = L"label1002";
			this->label1002->Size = System::Drawing::Size(17, 13);
			this->label1002->TabIndex = 105;
			this->label1002->Text = L"X:";
			// 
			// label1001
			// 
			this->label1001->AutoSize = true;
			this->label1001->ForeColor = System::Drawing::Color::White;
			this->label1001->Location = System::Drawing::Point(25, 518);
			this->label1001->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1001->Name = L"label1001";
			this->label1001->Size = System::Drawing::Size(17, 13);
			this->label1001->TabIndex = 103;
			this->label1001->Text = L"Y:";
			// 
			// lable10
			// 
			this->lable10->AutoSize = true;
			this->lable10->ForeColor = System::Drawing::Color::White;
			this->lable10->Location = System::Drawing::Point(25, 538);
			this->lable10->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lable10->Name = L"lable10";
			this->lable10->Size = System::Drawing::Size(17, 13);
			this->lable10->TabIndex = 102;
			this->lable10->Text = L"Z:";
			// 
			// label74
			// 
			this->label74->AutoSize = true;
			this->label74->ForeColor = System::Drawing::Color::White;
			this->label74->Location = System::Drawing::Point(25, 593);
			this->label74->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label74->Name = L"label74";
			this->label74->Size = System::Drawing::Size(17, 13);
			this->label74->TabIndex = 100;
			this->label74->Text = L"X:";
			// 
			// label75
			// 
			this->label75->AutoSize = true;
			this->label75->ForeColor = System::Drawing::Color::White;
			this->label75->Location = System::Drawing::Point(25, 613);
			this->label75->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label75->Name = L"label75";
			this->label75->Size = System::Drawing::Size(17, 13);
			this->label75->TabIndex = 98;
			this->label75->Text = L"Y:";
			// 
			// label1006
			// 
			this->label1006->AutoSize = true;
			this->label1006->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1006->ForeColor = System::Drawing::Color::White;
			this->label1006->Location = System::Drawing::Point(7, 395);
			this->label1006->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1006->Name = L"label1006";
			this->label1006->Size = System::Drawing::Size(34, 12);
			this->label1006->TabIndex = 94;
			this->label1006->Text = L"LONG:";
			// 
			// label77
			// 
			this->label77->AutoSize = true;
			this->label77->ForeColor = System::Drawing::Color::White;
			this->label77->Location = System::Drawing::Point(11, 418);
			this->label77->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label77->Name = L"label77";
			this->label77->Size = System::Drawing::Size(30, 13);
			this->label77->TabIndex = 92;
			this->label77->Text = L"ALT:";
			// 
			// label1005
			// 
			this->label1005->AutoSize = true;
			this->label1005->ForeColor = System::Drawing::Color::White;
			this->label1005->Location = System::Drawing::Point(18, 275);
			this->label1005->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1005->Name = L"label1005";
			this->label1005->Size = System::Drawing::Size(25, 13);
			this->label1005->TabIndex = 90;
			this->label1005->Text = L"V x:";
			// 
			// label1004
			// 
			this->label1004->AutoSize = true;
			this->label1004->ForeColor = System::Drawing::Color::White;
			this->label1004->Location = System::Drawing::Point(19, 297);
			this->label1004->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1004->Name = L"label1004";
			this->label1004->Size = System::Drawing::Size(25, 13);
			this->label1004->TabIndex = 88;
			this->label1004->Text = L"V y:";
			// 
			// label80
			// 
			this->label80->AutoSize = true;
			this->label80->ForeColor = System::Drawing::Color::White;
			this->label80->Location = System::Drawing::Point(7, 219);
			this->label80->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label80->Name = L"label80";
			this->label80->Size = System::Drawing::Size(38, 13);
			this->label80->TabIndex = 86;
			this->label80->Text = L"ROLL:";
			// 
			// label81
			// 
			this->label81->AutoSize = true;
			this->label81->ForeColor = System::Drawing::Color::White;
			this->label81->Location = System::Drawing::Point(11, 372);
			this->label81->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label81->Name = L"label81";
			this->label81->Size = System::Drawing::Size(30, 13);
			this->label81->TabIndex = 84;
			this->label81->Text = L"LAT:";
			// 
			// timer_DSP_messages
			// 
			this->timer_DSP_messages->Tick += gcnew System::EventHandler(this, &MyForm::timer_DSP_messages_Tick);
			// 
			// B_System_Health_Status
			// 
			this->B_System_Health_Status->BackColor = System::Drawing::Color::Red;
			this->B_System_Health_Status->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->B_System_Health_Status->Location = System::Drawing::Point(66, 639);
			this->B_System_Health_Status->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_System_Health_Status->Name = L"B_System_Health_Status";
			this->B_System_Health_Status->Size = System::Drawing::Size(78, 13);
			this->B_System_Health_Status->TabIndex = 204;
			this->B_System_Health_Status->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label71
			// 
			this->label71->AutoSize = true;
			this->label71->ForeColor = System::Drawing::Color::Black;
			this->label71->Location = System::Drawing::Point(66, 625);
			this->label71->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(78, 13);
			this->label71->TabIndex = 17;
			this->label71->Text = L"System Health:";
			// 
			// B_Ethernet_Status
			// 
			this->B_Ethernet_Status->BackColor = System::Drawing::Color::Red;
			this->B_Ethernet_Status->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->B_Ethernet_Status->Location = System::Drawing::Point(4, 639);
			this->B_Ethernet_Status->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Ethernet_Status->Name = L"B_Ethernet_Status";
			this->B_Ethernet_Status->Size = System::Drawing::Size(51, 13);
			this->B_Ethernet_Status->TabIndex = 16;
			this->B_Ethernet_Status->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->ForeColor = System::Drawing::Color::Black;
			this->label54->Location = System::Drawing::Point(4, 625);
			this->label54->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(50, 13);
			this->label54->TabIndex = 3;
			this->label54->Text = L"Ethernet:";
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->ForeColor = System::Drawing::Color::Black;
			this->label50->Location = System::Drawing::Point(5, 674);
			this->label50->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(37, 13);
			this->label50->TabIndex = 1;
			this->label50->Text = L"Status";
			// 
			// B_message
			// 
			this->B_message->BackColor = System::Drawing::Color::White;
			this->B_message->ForeColor = System::Drawing::Color::Black;
			this->B_message->Location = System::Drawing::Point(44, 670);
			this->B_message->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_message->Name = L"B_message";
			this->B_message->ReadOnly = true;
			this->B_message->Size = System::Drawing::Size(765, 20);
			this->B_message->TabIndex = 0;
			// 
			// B_GROUP_FREES
			// 
			this->B_GROUP_FREES->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->B_GROUP_FREES->Controls->Add(this->label67);
			this->B_GROUP_FREES->Controls->Add(this->label63);
			this->B_GROUP_FREES->Controls->Add(this->label62);
			this->B_GROUP_FREES->Controls->Add(this->label61);
			this->B_GROUP_FREES->Controls->Add(this->label56);
			this->B_GROUP_FREES->Controls->Add(this->label51);
			this->B_GROUP_FREES->Controls->Add(this->label57);
			this->B_GROUP_FREES->Controls->Add(this->label42);
			this->B_GROUP_FREES->Controls->Add(this->label58);
			this->B_GROUP_FREES->Controls->Add(this->label52);
			this->B_GROUP_FREES->Controls->Add(this->label59);
			this->B_GROUP_FREES->Controls->Add(this->label12);
			this->B_GROUP_FREES->Controls->Add(this->label53);
			this->B_GROUP_FREES->Controls->Add(this->label43);
			this->B_GROUP_FREES->Controls->Add(this->label55);
			this->B_GROUP_FREES->Controls->Add(this->label44);
			this->B_GROUP_FREES->Controls->Add(this->B_CHB_FREE_4);
			this->B_GROUP_FREES->Controls->Add(this->label49);
			this->B_GROUP_FREES->Controls->Add(this->label32);
			this->B_GROUP_FREES->Controls->Add(this->B_CHB_FREE_3);
			this->B_GROUP_FREES->Controls->Add(this->label40);
			this->B_GROUP_FREES->Controls->Add(this->B_CHB_FREE_2);
			this->B_GROUP_FREES->Controls->Add(this->label41);
			this->B_GROUP_FREES->Controls->Add(this->B_CHB_FREE_1);
			this->B_GROUP_FREES->Controls->Add(this->B_CHA_FREE_4);
			this->B_GROUP_FREES->Controls->Add(this->B_CHA_FREE_3);
			this->B_GROUP_FREES->Controls->Add(this->B_CHA_FREE_2);
			this->B_GROUP_FREES->Controls->Add(this->B_CHA_FREE_1);
			this->B_GROUP_FREES->Controls->Add(this->B_DET_FREE_4);
			this->B_GROUP_FREES->Controls->Add(this->B_DET_FREE_3);
			this->B_GROUP_FREES->Controls->Add(this->B_DET_FREE_2);
			this->B_GROUP_FREES->Controls->Add(this->B_DET_FREE_1);
			this->B_GROUP_FREES->Controls->Add(this->B_OMR_FREE_4);
			this->B_GROUP_FREES->Controls->Add(this->B_OMR_FREE_3);
			this->B_GROUP_FREES->Controls->Add(this->B_OMR_FREE_2);
			this->B_GROUP_FREES->Controls->Add(this->B_OMR_FREE_1);
			this->B_GROUP_FREES->ForeColor = System::Drawing::Color::White;
			this->B_GROUP_FREES->Location = System::Drawing::Point(8, 2);
			this->B_GROUP_FREES->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_FREES->Name = L"B_GROUP_FREES";
			this->B_GROUP_FREES->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_FREES->Size = System::Drawing::Size(127, 448);
			this->B_GROUP_FREES->TabIndex = 12;
			this->B_GROUP_FREES->TabStop = false;
			this->B_GROUP_FREES->Text = L"Free variables (debug)";
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->ForeColor = System::Drawing::Color::White;
			this->label67->Location = System::Drawing::Point(68, 317);
			this->label67->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(29, 13);
			this->label67->TabIndex = 155;
			this->label67->Text = L"CHB";
			// 
			// label63
			// 
			this->label63->AutoSize = true;
			this->label63->ForeColor = System::Drawing::Color::White;
			this->label63->Location = System::Drawing::Point(68, 215);
			this->label63->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(29, 13);
			this->label63->TabIndex = 155;
			this->label63->Text = L"CHA";
			// 
			// label62
			// 
			this->label62->AutoSize = true;
			this->label62->ForeColor = System::Drawing::Color::White;
			this->label62->Location = System::Drawing::Point(68, 117);
			this->label62->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(29, 13);
			this->label62->TabIndex = 155;
			this->label62->Text = L"DET";
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->ForeColor = System::Drawing::Color::White;
			this->label61->Location = System::Drawing::Point(67, 16);
			this->label61->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(32, 13);
			this->label61->TabIndex = 155;
			this->label61->Text = L"OMR";
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->ForeColor = System::Drawing::Color::White;
			this->label56->Location = System::Drawing::Point(4, 396);
			this->label56->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(40, 13);
			this->label56->TabIndex = 157;
			this->label56->Text = L"Free 4:";
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->ForeColor = System::Drawing::Color::White;
			this->label51->Location = System::Drawing::Point(4, 295);
			this->label51->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(40, 13);
			this->label51->TabIndex = 157;
			this->label51->Text = L"Free 4:";
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->ForeColor = System::Drawing::Color::White;
			this->label57->Location = System::Drawing::Point(4, 376);
			this->label57->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(40, 13);
			this->label57->TabIndex = 156;
			this->label57->Text = L"Free 3:";
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->ForeColor = System::Drawing::Color::White;
			this->label42->Location = System::Drawing::Point(4, 194);
			this->label42->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(40, 13);
			this->label42->TabIndex = 157;
			this->label42->Text = L"Free 4:";
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->ForeColor = System::Drawing::Color::White;
			this->label58->Location = System::Drawing::Point(4, 356);
			this->label58->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(40, 13);
			this->label58->TabIndex = 155;
			this->label58->Text = L"Free 2:";
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->ForeColor = System::Drawing::Color::White;
			this->label52->Location = System::Drawing::Point(4, 275);
			this->label52->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(40, 13);
			this->label52->TabIndex = 156;
			this->label52->Text = L"Free 3:";
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->ForeColor = System::Drawing::Color::White;
			this->label59->Location = System::Drawing::Point(4, 335);
			this->label59->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(40, 13);
			this->label59->TabIndex = 154;
			this->label59->Text = L"Free 1:";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(4, 96);
			this->label12->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(40, 13);
			this->label12->TabIndex = 157;
			this->label12->Text = L"Free 4:";
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->ForeColor = System::Drawing::Color::White;
			this->label53->Location = System::Drawing::Point(4, 254);
			this->label53->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(40, 13);
			this->label53->TabIndex = 155;
			this->label53->Text = L"Free 2:";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->ForeColor = System::Drawing::Color::White;
			this->label43->Location = System::Drawing::Point(4, 174);
			this->label43->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(40, 13);
			this->label43->TabIndex = 156;
			this->label43->Text = L"Free 3:";
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->ForeColor = System::Drawing::Color::White;
			this->label55->Location = System::Drawing::Point(4, 236);
			this->label55->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(40, 13);
			this->label55->TabIndex = 154;
			this->label55->Text = L"Free 1:";
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->ForeColor = System::Drawing::Color::White;
			this->label44->Location = System::Drawing::Point(4, 153);
			this->label44->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(40, 13);
			this->label44->TabIndex = 155;
			this->label44->Text = L"Free 2:";
			// 
			// B_CHB_FREE_4
			// 
			this->B_CHB_FREE_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHB_FREE_4->Location = System::Drawing::Point(51, 391);
			this->B_CHB_FREE_4->Name = L"B_CHB_FREE_4";
			this->B_CHB_FREE_4->ReadOnly = true;
			this->B_CHB_FREE_4->Size = System::Drawing::Size(66, 20);
			this->B_CHB_FREE_4->TabIndex = 146;
			this->B_CHB_FREE_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->ForeColor = System::Drawing::Color::White;
			this->label49->Location = System::Drawing::Point(4, 135);
			this->label49->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(40, 13);
			this->label49->TabIndex = 154;
			this->label49->Text = L"Free 1:";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->ForeColor = System::Drawing::Color::White;
			this->label32->Location = System::Drawing::Point(4, 75);
			this->label32->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(40, 13);
			this->label32->TabIndex = 156;
			this->label32->Text = L"Free 3:";
			// 
			// B_CHB_FREE_3
			// 
			this->B_CHB_FREE_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHB_FREE_3->Location = System::Drawing::Point(51, 371);
			this->B_CHB_FREE_3->Name = L"B_CHB_FREE_3";
			this->B_CHB_FREE_3->ReadOnly = true;
			this->B_CHB_FREE_3->Size = System::Drawing::Size(66, 20);
			this->B_CHB_FREE_3->TabIndex = 145;
			this->B_CHB_FREE_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->ForeColor = System::Drawing::Color::White;
			this->label40->Location = System::Drawing::Point(4, 57);
			this->label40->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(40, 13);
			this->label40->TabIndex = 155;
			this->label40->Text = L"Free 2:";
			// 
			// B_CHB_FREE_2
			// 
			this->B_CHB_FREE_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHB_FREE_2->Location = System::Drawing::Point(51, 352);
			this->B_CHB_FREE_2->Name = L"B_CHB_FREE_2";
			this->B_CHB_FREE_2->ReadOnly = true;
			this->B_CHB_FREE_2->Size = System::Drawing::Size(66, 20);
			this->B_CHB_FREE_2->TabIndex = 142;
			this->B_CHB_FREE_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->ForeColor = System::Drawing::Color::White;
			this->label41->Location = System::Drawing::Point(4, 36);
			this->label41->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(40, 13);
			this->label41->TabIndex = 154;
			this->label41->Text = L"Free 1:";
			// 
			// B_CHB_FREE_1
			// 
			this->B_CHB_FREE_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHB_FREE_1->Location = System::Drawing::Point(51, 332);
			this->B_CHB_FREE_1->Name = L"B_CHB_FREE_1";
			this->B_CHB_FREE_1->ReadOnly = true;
			this->B_CHB_FREE_1->Size = System::Drawing::Size(66, 20);
			this->B_CHB_FREE_1->TabIndex = 141;
			this->B_CHB_FREE_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CHA_FREE_4
			// 
			this->B_CHA_FREE_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHA_FREE_4->Location = System::Drawing::Point(51, 292);
			this->B_CHA_FREE_4->Name = L"B_CHA_FREE_4";
			this->B_CHA_FREE_4->ReadOnly = true;
			this->B_CHA_FREE_4->Size = System::Drawing::Size(66, 20);
			this->B_CHA_FREE_4->TabIndex = 138;
			this->B_CHA_FREE_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CHA_FREE_3
			// 
			this->B_CHA_FREE_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHA_FREE_3->Location = System::Drawing::Point(51, 272);
			this->B_CHA_FREE_3->Name = L"B_CHA_FREE_3";
			this->B_CHA_FREE_3->ReadOnly = true;
			this->B_CHA_FREE_3->Size = System::Drawing::Size(66, 20);
			this->B_CHA_FREE_3->TabIndex = 137;
			this->B_CHA_FREE_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CHA_FREE_2
			// 
			this->B_CHA_FREE_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHA_FREE_2->Location = System::Drawing::Point(51, 252);
			this->B_CHA_FREE_2->Name = L"B_CHA_FREE_2";
			this->B_CHA_FREE_2->ReadOnly = true;
			this->B_CHA_FREE_2->Size = System::Drawing::Size(66, 20);
			this->B_CHA_FREE_2->TabIndex = 134;
			this->B_CHA_FREE_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CHA_FREE_1
			// 
			this->B_CHA_FREE_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHA_FREE_1->Location = System::Drawing::Point(51, 232);
			this->B_CHA_FREE_1->Name = L"B_CHA_FREE_1";
			this->B_CHA_FREE_1->ReadOnly = true;
			this->B_CHA_FREE_1->Size = System::Drawing::Size(66, 20);
			this->B_CHA_FREE_1->TabIndex = 133;
			this->B_CHA_FREE_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_DET_FREE_4
			// 
			this->B_DET_FREE_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_FREE_4->Location = System::Drawing::Point(51, 190);
			this->B_DET_FREE_4->Name = L"B_DET_FREE_4";
			this->B_DET_FREE_4->ReadOnly = true;
			this->B_DET_FREE_4->Size = System::Drawing::Size(66, 20);
			this->B_DET_FREE_4->TabIndex = 91;
			this->B_DET_FREE_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_DET_FREE_3
			// 
			this->B_DET_FREE_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_FREE_3->Location = System::Drawing::Point(51, 172);
			this->B_DET_FREE_3->Name = L"B_DET_FREE_3";
			this->B_DET_FREE_3->ReadOnly = true;
			this->B_DET_FREE_3->Size = System::Drawing::Size(66, 20);
			this->B_DET_FREE_3->TabIndex = 90;
			this->B_DET_FREE_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_DET_FREE_2
			// 
			this->B_DET_FREE_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_FREE_2->Location = System::Drawing::Point(51, 152);
			this->B_DET_FREE_2->Name = L"B_DET_FREE_2";
			this->B_DET_FREE_2->ReadOnly = true;
			this->B_DET_FREE_2->Size = System::Drawing::Size(66, 20);
			this->B_DET_FREE_2->TabIndex = 89;
			this->B_DET_FREE_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_DET_FREE_1
			// 
			this->B_DET_FREE_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_FREE_1->Location = System::Drawing::Point(51, 132);
			this->B_DET_FREE_1->Name = L"B_DET_FREE_1";
			this->B_DET_FREE_1->ReadOnly = true;
			this->B_DET_FREE_1->Size = System::Drawing::Size(66, 20);
			this->B_DET_FREE_1->TabIndex = 88;
			this->B_DET_FREE_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_OMR_FREE_4
			// 
			this->B_OMR_FREE_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_OMR_FREE_4->Location = System::Drawing::Point(51, 92);
			this->B_OMR_FREE_4->Name = L"B_OMR_FREE_4";
			this->B_OMR_FREE_4->ReadOnly = true;
			this->B_OMR_FREE_4->Size = System::Drawing::Size(66, 20);
			this->B_OMR_FREE_4->TabIndex = 83;
			this->B_OMR_FREE_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_OMR_FREE_3
			// 
			this->B_OMR_FREE_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_OMR_FREE_3->Location = System::Drawing::Point(51, 72);
			this->B_OMR_FREE_3->Name = L"B_OMR_FREE_3";
			this->B_OMR_FREE_3->ReadOnly = true;
			this->B_OMR_FREE_3->Size = System::Drawing::Size(66, 20);
			this->B_OMR_FREE_3->TabIndex = 82;
			this->B_OMR_FREE_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_OMR_FREE_2
			// 
			this->B_OMR_FREE_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_OMR_FREE_2->Location = System::Drawing::Point(51, 52);
			this->B_OMR_FREE_2->Name = L"B_OMR_FREE_2";
			this->B_OMR_FREE_2->ReadOnly = true;
			this->B_OMR_FREE_2->Size = System::Drawing::Size(66, 20);
			this->B_OMR_FREE_2->TabIndex = 81;
			this->B_OMR_FREE_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_OMR_FREE_1
			// 
			this->B_OMR_FREE_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_OMR_FREE_1->Location = System::Drawing::Point(51, 32);
			this->B_OMR_FREE_1->Name = L"B_OMR_FREE_1";
			this->B_OMR_FREE_1->ReadOnly = true;
			this->B_OMR_FREE_1->Size = System::Drawing::Size(66, 20);
			this->B_OMR_FREE_1->TabIndex = 80;
			this->B_OMR_FREE_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// G_STOP_WORK
			// 
			this->G_STOP_WORK->BackColor = System::Drawing::Color::DarkGray;
			this->G_STOP_WORK->FlatAppearance->BorderSize = 0;
			this->G_STOP_WORK->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->G_STOP_WORK->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->G_STOP_WORK->ForeColor = System::Drawing::Color::Black;
			this->G_STOP_WORK->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"G_STOP_WORK.Image")));
			this->G_STOP_WORK->Location = System::Drawing::Point(370, 627);
			this->G_STOP_WORK->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->G_STOP_WORK->Name = L"G_STOP_WORK";
			this->G_STOP_WORK->Size = System::Drawing::Size(50, 38);
			this->G_STOP_WORK->TabIndex = 128;
			this->TOOL_TIP_STOP->SetToolTip(this->G_STOP_WORK, L"Please click \"Stop\" for work mode");
			this->G_STOP_WORK->UseVisualStyleBackColor = false;
			this->G_STOP_WORK->Click += gcnew System::EventHandler(this, &MyForm::G_STOP_WORK_Click);
			// 
			// B_SelectLOGfolder
			// 
			this->B_SelectLOGfolder->RootFolder = System::Environment::SpecialFolder::MyDocuments;
			// 
			// B_GROUP_SENSOR
			// 
			this->B_GROUP_SENSOR->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->B_GROUP_SENSOR->Controls->Add(this->label108);
			this->B_GROUP_SENSOR->Controls->Add(this->label93);
			this->B_GROUP_SENSOR->Controls->Add(this->label94);
			this->B_GROUP_SENSOR->Controls->Add(this->label95);
			this->B_GROUP_SENSOR->Controls->Add(this->label96);
			this->B_GROUP_SENSOR->Controls->Add(this->label92);
			this->B_GROUP_SENSOR->Controls->Add(this->label91);
			this->B_GROUP_SENSOR->Controls->Add(this->label90);
			this->B_GROUP_SENSOR->Controls->Add(this->label89);
			this->B_GROUP_SENSOR->Controls->Add(this->label85);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_INS_sd);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ATT_YAW);
			this->B_GROUP_SENSOR->Controls->Add(this->label86);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ATT_PITCH);
			this->B_GROUP_SENSOR->Controls->Add(this->label87);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ATT_ROLL);
			this->B_GROUP_SENSOR->Controls->Add(this->label88);
			this->B_GROUP_SENSOR->Controls->Add(this->label84);
			this->B_GROUP_SENSOR->Controls->Add(this->label83);
			this->B_GROUP_SENSOR->Controls->Add(this->label82);
			this->B_GROUP_SENSOR->Controls->Add(this->label79);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_VelUncertainty);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_PosUncertainty);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_AttUncertainty);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_TIME);
			this->B_GROUP_SENSOR->Controls->Add(this->label13);
			this->B_GROUP_SENSOR->Controls->Add(this->label10);
			this->B_GROUP_SENSOR->Controls->Add(this->label9);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ANGULAR_RATE_Z);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ACCELERATION_X);
			this->B_GROUP_SENSOR->Controls->Add(this->label1003);
			this->B_GROUP_SENSOR->Controls->Add(this->label65);
			this->B_GROUP_SENSOR->Controls->Add(this->label1002);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_INS_YAW);
			this->B_GROUP_SENSOR->Controls->Add(this->label68);
			this->B_GROUP_SENSOR->Controls->Add(this->label1001);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_INS_PITCH);
			this->B_GROUP_SENSOR->Controls->Add(this->label69);
			this->B_GROUP_SENSOR->Controls->Add(this->lable10);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ANGULAR_RATE_X);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ACCELERATION_Z);
			this->B_GROUP_SENSOR->Controls->Add(this->label74);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_INS_ROLL);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ACCELERATION_Y);
			this->B_GROUP_SENSOR->Controls->Add(this->label75);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ANGULAR_RATE_Y);
			this->B_GROUP_SENSOR->Controls->Add(this->label1006);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_ALTITUDE);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_LATITUDE);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_VELOCITY_Z);
			this->B_GROUP_SENSOR->Controls->Add(this->label77);
			this->B_GROUP_SENSOR->Controls->Add(this->label81);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_LONGITUDE);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_VELOCITY_Y);
			this->B_GROUP_SENSOR->Controls->Add(this->label1005);
			this->B_GROUP_SENSOR->Controls->Add(this->label80);
			this->B_GROUP_SENSOR->Controls->Add(this->label1004);
			this->B_GROUP_SENSOR->Controls->Add(this->B_SENSOR_VELOCITY_X);
			this->B_GROUP_SENSOR->ForeColor = System::Drawing::Color::White;
			this->B_GROUP_SENSOR->Location = System::Drawing::Point(-1, 3);
			this->B_GROUP_SENSOR->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_SENSOR->Name = L"B_GROUP_SENSOR";
			this->B_GROUP_SENSOR->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_SENSOR->Size = System::Drawing::Size(118, 660);
			this->B_GROUP_SENSOR->TabIndex = 9;
			this->B_GROUP_SENSOR->TabStop = false;
			this->B_GROUP_SENSOR->Text = L"Sensors";
			// 
			// label108
			// 
			this->label108->AutoSize = true;
			this->label108->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label108->ForeColor = System::Drawing::Color::White;
			this->label108->Location = System::Drawing::Point(80, 17);
			this->label108->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label108->Name = L"label108";
			this->label108->Size = System::Drawing::Size(32, 13);
			this->label108->TabIndex = 146;
			this->label108->Text = L"[Sec]";
			// 
			// label93
			// 
			this->label93->AutoSize = true;
			this->label93->ForeColor = System::Drawing::Color::White;
			this->label93->Location = System::Drawing::Point(85, 198);
			this->label93->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label93->Name = L"label93";
			this->label93->Size = System::Drawing::Size(31, 13);
			this->label93->TabIndex = 145;
			this->label93->Text = L"[deg]";
			// 
			// label94
			// 
			this->label94->AutoSize = true;
			this->label94->ForeColor = System::Drawing::Color::White;
			this->label94->Location = System::Drawing::Point(85, 220);
			this->label94->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label94->Name = L"label94";
			this->label94->Size = System::Drawing::Size(31, 13);
			this->label94->TabIndex = 144;
			this->label94->Text = L"[deg]";
			// 
			// label95
			// 
			this->label95->AutoSize = true;
			this->label95->ForeColor = System::Drawing::Color::White;
			this->label95->Location = System::Drawing::Point(85, 242);
			this->label95->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label95->Name = L"label95";
			this->label95->Size = System::Drawing::Size(31, 13);
			this->label95->TabIndex = 143;
			this->label95->Text = L"[deg]";
			// 
			// label96
			// 
			this->label96->AutoSize = true;
			this->label96->ForeColor = System::Drawing::Color::White;
			this->label96->Location = System::Drawing::Point(85, 175);
			this->label96->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label96->Name = L"label96";
			this->label96->Size = System::Drawing::Size(31, 13);
			this->label96->TabIndex = 142;
			this->label96->Text = L"[deg]";
			// 
			// label92
			// 
			this->label92->AutoSize = true;
			this->label92->ForeColor = System::Drawing::Color::White;
			this->label92->Location = System::Drawing::Point(85, 88);
			this->label92->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label92->Name = L"label92";
			this->label92->Size = System::Drawing::Size(31, 13);
			this->label92->TabIndex = 141;
			this->label92->Text = L"[deg]";
			// 
			// label91
			// 
			this->label91->AutoSize = true;
			this->label91->ForeColor = System::Drawing::Color::White;
			this->label91->Location = System::Drawing::Point(85, 110);
			this->label91->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label91->Name = L"label91";
			this->label91->Size = System::Drawing::Size(31, 13);
			this->label91->TabIndex = 140;
			this->label91->Text = L"[deg]";
			// 
			// label90
			// 
			this->label90->AutoSize = true;
			this->label90->ForeColor = System::Drawing::Color::White;
			this->label90->Location = System::Drawing::Point(85, 131);
			this->label90->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label90->Name = L"label90";
			this->label90->Size = System::Drawing::Size(31, 13);
			this->label90->TabIndex = 139;
			this->label90->Text = L"[deg]";
			// 
			// label89
			// 
			this->label89->AutoSize = true;
			this->label89->ForeColor = System::Drawing::Color::White;
			this->label89->Location = System::Drawing::Point(85, 66);
			this->label89->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label89->Name = L"label89";
			this->label89->Size = System::Drawing::Size(31, 13);
			this->label89->TabIndex = 138;
			this->label89->Text = L"[deg]";
			// 
			// label85
			// 
			this->label85->AutoSize = true;
			this->label85->ForeColor = System::Drawing::Color::White;
			this->label85->Location = System::Drawing::Point(18, 131);
			this->label85->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label85->Name = L"label85";
			this->label85->Size = System::Drawing::Size(24, 13);
			this->label85->TabIndex = 136;
			this->label85->Text = L"s.d.";
			// 
			// B_SENSOR_INS_sd
			// 
			this->B_SENSOR_INS_sd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_INS_sd->Location = System::Drawing::Point(43, 129);
			this->B_SENSOR_INS_sd->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_INS_sd->Name = L"B_SENSOR_INS_sd";
			this->B_SENSOR_INS_sd->ReadOnly = true;
			this->B_SENSOR_INS_sd->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_INS_sd->TabIndex = 135;
			this->B_SENSOR_INS_sd->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_ATT_YAW
			// 
			this->B_SENSOR_ATT_YAW->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ATT_YAW->Location = System::Drawing::Point(43, 173);
			this->B_SENSOR_ATT_YAW->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ATT_YAW->Name = L"B_SENSOR_ATT_YAW";
			this->B_SENSOR_ATT_YAW->ReadOnly = true;
			this->B_SENSOR_ATT_YAW->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_ATT_YAW->TabIndex = 130;
			this->B_SENSOR_ATT_YAW->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label86
			// 
			this->label86->AutoSize = true;
			this->label86->ForeColor = System::Drawing::Color::White;
			this->label86->Location = System::Drawing::Point(8, 67);
			this->label86->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label86->Name = L"label86";
			this->label86->Size = System::Drawing::Size(35, 13);
			this->label86->TabIndex = 129;
			this->label86->Text = L"YAW:";
			// 
			// B_SENSOR_ATT_PITCH
			// 
			this->B_SENSOR_ATT_PITCH->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ATT_PITCH->Location = System::Drawing::Point(43, 195);
			this->B_SENSOR_ATT_PITCH->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ATT_PITCH->Name = L"B_SENSOR_ATT_PITCH";
			this->B_SENSOR_ATT_PITCH->ReadOnly = true;
			this->B_SENSOR_ATT_PITCH->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_ATT_PITCH->TabIndex = 132;
			this->B_SENSOR_ATT_PITCH->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label87
			// 
			this->label87->AutoSize = true;
			this->label87->ForeColor = System::Drawing::Color::White;
			this->label87->Location = System::Drawing::Point(4, 89);
			this->label87->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label87->Name = L"label87";
			this->label87->Size = System::Drawing::Size(39, 13);
			this->label87->TabIndex = 131;
			this->label87->Text = L"PITCH";
			// 
			// B_SENSOR_ATT_ROLL
			// 
			this->B_SENSOR_ATT_ROLL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_ATT_ROLL->Location = System::Drawing::Point(43, 217);
			this->B_SENSOR_ATT_ROLL->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_ATT_ROLL->Name = L"B_SENSOR_ATT_ROLL";
			this->B_SENSOR_ATT_ROLL->ReadOnly = true;
			this->B_SENSOR_ATT_ROLL->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_ATT_ROLL->TabIndex = 133;
			this->B_SENSOR_ATT_ROLL->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label88
			// 
			this->label88->AutoSize = true;
			this->label88->ForeColor = System::Drawing::Color::White;
			this->label88->Location = System::Drawing::Point(5, 110);
			this->label88->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label88->Name = L"label88";
			this->label88->Size = System::Drawing::Size(38, 13);
			this->label88->TabIndex = 134;
			this->label88->Text = L"ROLL:";
			// 
			// label84
			// 
			this->label84->AutoSize = true;
			this->label84->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label84->ForeColor = System::Drawing::Color::White;
			this->label84->Location = System::Drawing::Point(8, 39);
			this->label84->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label84->Name = L"label84";
			this->label84->Size = System::Drawing::Size(81, 16);
			this->label84->TabIndex = 128;
			this->label84->Text = L"Self Attitude:";
			// 
			// label83
			// 
			this->label83->AutoSize = true;
			this->label83->ForeColor = System::Drawing::Color::White;
			this->label83->Location = System::Drawing::Point(18, 241);
			this->label83->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label83->Name = L"label83";
			this->label83->Size = System::Drawing::Size(24, 13);
			this->label83->TabIndex = 127;
			this->label83->Text = L"s.d.";
			// 
			// label82
			// 
			this->label82->AutoSize = true;
			this->label82->ForeColor = System::Drawing::Color::White;
			this->label82->Location = System::Drawing::Point(17, 440);
			this->label82->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label82->Name = L"label82";
			this->label82->Size = System::Drawing::Size(24, 13);
			this->label82->TabIndex = 126;
			this->label82->Text = L"s.d.";
			// 
			// label79
			// 
			this->label79->AutoSize = true;
			this->label79->ForeColor = System::Drawing::Color::White;
			this->label79->Location = System::Drawing::Point(19, 340);
			this->label79->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label79->Name = L"label79";
			this->label79->Size = System::Drawing::Size(24, 13);
			this->label79->TabIndex = 125;
			this->label79->Text = L"s.d.";
			// 
			// B_SENSOR_VelUncertainty
			// 
			this->B_SENSOR_VelUncertainty->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_VelUncertainty->Location = System::Drawing::Point(43, 338);
			this->B_SENSOR_VelUncertainty->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_VelUncertainty->Name = L"B_SENSOR_VelUncertainty";
			this->B_SENSOR_VelUncertainty->ReadOnly = true;
			this->B_SENSOR_VelUncertainty->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_VelUncertainty->TabIndex = 124;
			this->B_SENSOR_VelUncertainty->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_PosUncertainty
			// 
			this->B_SENSOR_PosUncertainty->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_PosUncertainty->Location = System::Drawing::Point(41, 438);
			this->B_SENSOR_PosUncertainty->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_PosUncertainty->Name = L"B_SENSOR_PosUncertainty";
			this->B_SENSOR_PosUncertainty->ReadOnly = true;
			this->B_SENSOR_PosUncertainty->Size = System::Drawing::Size(70, 20);
			this->B_SENSOR_PosUncertainty->TabIndex = 123;
			this->B_SENSOR_PosUncertainty->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_AttUncertainty
			// 
			this->B_SENSOR_AttUncertainty->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_AttUncertainty->Location = System::Drawing::Point(43, 239);
			this->B_SENSOR_AttUncertainty->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_AttUncertainty->Name = L"B_SENSOR_AttUncertainty";
			this->B_SENSOR_AttUncertainty->ReadOnly = true;
			this->B_SENSOR_AttUncertainty->Size = System::Drawing::Size(42, 20);
			this->B_SENSOR_AttUncertainty->TabIndex = 122;
			this->B_SENSOR_AttUncertainty->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_TIME
			// 
			this->B_SENSOR_TIME->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SENSOR_TIME->Location = System::Drawing::Point(8, 14);
			this->B_SENSOR_TIME->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_TIME->Name = L"B_SENSOR_TIME";
			this->B_SENSOR_TIME->ReadOnly = true;
			this->B_SENSOR_TIME->Size = System::Drawing::Size(70, 20);
			this->B_SENSOR_TIME->TabIndex = 121;
			this->B_SENSOR_TIME->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(5, 157);
			this->label13->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(94, 16);
			this->label13->TabIndex = 117;
			this->label13->Text = L"Inertial Attitude";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(43, 471);
			this->label10->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(34, 16);
			this->label10->TabIndex = 114;
			this->label10->Text = L"Acc:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(44, 564);
			this->label9->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(35, 16);
			this->label9->TabIndex = 113;
			this->label9->Text = L"Ang:";
			// 
			// B_SENSOR_CONFIG
			// 
			this->B_SENSOR_CONFIG->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_SENSOR_CONFIG->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_SENSOR_CONFIG->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold));
			this->B_SENSOR_CONFIG->ForeColor = System::Drawing::Color::Black;
			this->B_SENSOR_CONFIG->Location = System::Drawing::Point(256, 466);
			this->B_SENSOR_CONFIG->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SENSOR_CONFIG->Name = L"B_SENSOR_CONFIG";
			this->B_SENSOR_CONFIG->Size = System::Drawing::Size(124, 38);
			this->B_SENSOR_CONFIG->TabIndex = 118;
			this->B_SENSOR_CONFIG->Text = L"Reset Sensor";
			this->B_SENSOR_CONFIG->UseVisualStyleBackColor = false;
			this->B_SENSOR_CONFIG->Click += gcnew System::EventHandler(this, &MyForm::B_SENSOR_CONFIG_Click);
			// 
			// B_tabControl
			// 
			this->B_tabControl->Controls->Add(this->MAP_VIEW);
			this->B_tabControl->Controls->Add(this->RDM_VIEW);
			this->B_tabControl->Controls->Add(this->SINGLE_RDM_VIEW);
			this->B_tabControl->Controls->Add(this->RADAR_VIEW);
			this->B_tabControl->Controls->Add(this->Flash);
			this->B_tabControl->Controls->Add(this->Debug);
			this->B_tabControl->Controls->Add(this->Mainenance);
			this->B_tabControl->Controls->Add(this->LAB_Experiments);
			this->B_tabControl->Location = System::Drawing::Point(-1, 1);
			this->B_tabControl->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_tabControl->Name = L"B_tabControl";
			this->B_tabControl->SelectedIndex = 0;
			this->B_tabControl->Size = System::Drawing::Size(836, 616);
			this->B_tabControl->TabIndex = 14;
			this->B_tabControl->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::B_tabControl_SelectedIndexChanged);
			this->B_tabControl->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::B_MAP_PANEL_KeyDown);
			// 
			// MAP_VIEW
			// 
			this->MAP_VIEW->Controls->Add(this->label264);
			this->MAP_VIEW->Controls->Add(this->B_MAP_PANEL);
			this->MAP_VIEW->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->MAP_VIEW->Location = System::Drawing::Point(4, 22);
			this->MAP_VIEW->Name = L"MAP_VIEW";
			this->MAP_VIEW->Size = System::Drawing::Size(828, 590);
			this->MAP_VIEW->TabIndex = 6;
			this->MAP_VIEW->Text = L"MAP";
			this->MAP_VIEW->UseVisualStyleBackColor = true;
			// 
			// B_VISIBLE_OBSTACLES
			// 
			this->B_VISIBLE_OBSTACLES->BackColor = System::Drawing::Color::DarkGray;
			this->B_VISIBLE_OBSTACLES->Controls->Add(this->B_TRAJECTORIES);
			this->B_VISIBLE_OBSTACLES->Controls->Add(this->B_DETECTIONS);
			this->B_VISIBLE_OBSTACLES->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->B_VISIBLE_OBSTACLES->ForeColor = System::Drawing::Color::Black;
			this->B_VISIBLE_OBSTACLES->Location = System::Drawing::Point(692, 59);
			this->B_VISIBLE_OBSTACLES->Name = L"B_VISIBLE_OBSTACLES";
			this->B_VISIBLE_OBSTACLES->Size = System::Drawing::Size(120, 76);
			this->B_VISIBLE_OBSTACLES->TabIndex = 218;
			this->B_VISIBLE_OBSTACLES->TabStop = false;
			this->B_VISIBLE_OBSTACLES->Text = L"Visible Obstacles";
			// 
			// B_TRAJECTORIES
			// 
			this->B_TRAJECTORIES->AutoSize = true;
			this->B_TRAJECTORIES->BackColor = System::Drawing::Color::DarkGray;
			this->B_TRAJECTORIES->Checked = true;
			this->B_TRAJECTORIES->CheckState = System::Windows::Forms::CheckState::Checked;
			this->B_TRAJECTORIES->ForeColor = System::Drawing::Color::Black;
			this->B_TRAJECTORIES->Location = System::Drawing::Point(27, 46);
			this->B_TRAJECTORIES->Name = L"B_TRAJECTORIES";
			this->B_TRAJECTORIES->Size = System::Drawing::Size(87, 17);
			this->B_TRAJECTORIES->TabIndex = 1;
			this->B_TRAJECTORIES->Text = L"Trajecctories";
			this->B_TRAJECTORIES->UseVisualStyleBackColor = false;
			this->B_TRAJECTORIES->CheckedChanged += gcnew System::EventHandler(this, &MyForm::B_TRAJECTORIES_CheckedChanged);
			// 
			// B_DETECTIONS
			// 
			this->B_DETECTIONS->AutoSize = true;
			this->B_DETECTIONS->BackColor = System::Drawing::Color::DarkGray;
			this->B_DETECTIONS->Checked = true;
			this->B_DETECTIONS->CheckState = System::Windows::Forms::CheckState::Checked;
			this->B_DETECTIONS->ForeColor = System::Drawing::Color::Black;
			this->B_DETECTIONS->Location = System::Drawing::Point(27, 23);
			this->B_DETECTIONS->Name = L"B_DETECTIONS";
			this->B_DETECTIONS->Size = System::Drawing::Size(77, 17);
			this->B_DETECTIONS->TabIndex = 0;
			this->B_DETECTIONS->Text = L"Detections";
			this->B_DETECTIONS->UseVisualStyleBackColor = false;
			this->B_DETECTIONS->CheckedChanged += gcnew System::EventHandler(this, &MyForm::B_DETECTIONS_CheckedChanged);
			// 
			// B_LOAD_MAP
			// 
			this->B_LOAD_MAP->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_LOAD_MAP->FlatAppearance->BorderSize = 0;
			this->B_LOAD_MAP->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->B_LOAD_MAP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_LOAD_MAP->ForeColor = System::Drawing::Color::Black;
			this->B_LOAD_MAP->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_LOAD_MAP.Image")));
			this->B_LOAD_MAP->Location = System::Drawing::Point(744, 14);
			this->B_LOAD_MAP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LOAD_MAP->Name = L"B_LOAD_MAP";
			this->B_LOAD_MAP->Size = System::Drawing::Size(68, 35);
			this->B_LOAD_MAP->TabIndex = 214;
			this->LOAD_MAP_TOOL_TIP->SetToolTip(this->B_LOAD_MAP, L"Load Map");
			this->B_LOAD_MAP->UseVisualStyleBackColor = false;
			this->B_LOAD_MAP->Click += gcnew System::EventHandler(this, &MyForm::B_LOAD_MAP_Click);
			// 
			// B_RE_FLIGHT
			// 
			this->B_RE_FLIGHT->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_RE_FLIGHT->FlatAppearance->BorderSize = 0;
			this->B_RE_FLIGHT->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->B_RE_FLIGHT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_RE_FLIGHT->ForeColor = System::Drawing::Color::Black;
			this->B_RE_FLIGHT->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_RE_FLIGHT.Image")));
			this->B_RE_FLIGHT->Location = System::Drawing::Point(684, 10);
			this->B_RE_FLIGHT->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RE_FLIGHT->Name = L"B_RE_FLIGHT";
			this->B_RE_FLIGHT->Size = System::Drawing::Size(56, 41);
			this->B_RE_FLIGHT->TabIndex = 213;
			this->RE_FLIGHT_TOOL_TIP->SetToolTip(this->B_RE_FLIGHT, L"Re Flight");
			this->B_RE_FLIGHT->UseVisualStyleBackColor = false;
			this->B_RE_FLIGHT->Click += gcnew System::EventHandler(this, &MyForm::B_RE_FLIGHT_Click);
			// 
			// label264
			// 
			this->label264->AutoSize = true;
			this->label264->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label264->Location = System::Drawing::Point(2157, 553);
			this->label264->Name = L"label264";
			this->label264->Size = System::Drawing::Size(81, 15);
			this->label264->TabIndex = 208;
			this->label264->Text = L"Screen width:";
			// 
			// B_MAP_PANEL
			// 
			this->B_MAP_PANEL->BackColor = System::Drawing::Color::DarkGray;
			this->B_MAP_PANEL->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_MAP_PANEL->Controls->Add(this->B_LOAD_MAP);
			this->B_MAP_PANEL->Controls->Add(this->B_RE_FLIGHT);
			this->B_MAP_PANEL->Controls->Add(this->B_VISIBLE_OBSTACLES);
			this->B_MAP_PANEL->Controls->Add(this->REAL_TIME_TOOL_STRIP);
			this->B_MAP_PANEL->Controls->Add(this->panel5);
			this->B_MAP_PANEL->Controls->Add(this->B_SCALE_VIEWER);
			this->B_MAP_PANEL->Controls->Add(this->label265);
			this->B_MAP_PANEL->ForeColor = System::Drawing::Color::Black;
			this->B_MAP_PANEL->Location = System::Drawing::Point(1, 4);
			this->B_MAP_PANEL->MaximumSize = System::Drawing::Size(825, 600);
			this->B_MAP_PANEL->MinimumSize = System::Drawing::Size(825, 600);
			this->B_MAP_PANEL->Name = L"B_MAP_PANEL";
			this->B_MAP_PANEL->Size = System::Drawing::Size(825, 600);
			this->B_MAP_PANEL->TabIndex = 128;
			this->B_MAP_PANEL->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::B_MAP_PANEL_Paint);
			this->B_MAP_PANEL->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::B_MAP_PANEL_MouseDown);
			this->B_MAP_PANEL->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::B_MAP_PANEL_MouseMove);
			this->B_MAP_PANEL->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::B_MAP_PANEL_MouseWheel);
			// 
			// REAL_TIME_TOOL_STRIP
			// 
			this->REAL_TIME_TOOL_STRIP->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->REAL_TIME_TOOL_STRIP->Dock = System::Windows::Forms::DockStyle::None;
			this->REAL_TIME_TOOL_STRIP->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->REAL_TIME_TOOL_STRIP->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
				this->B_REAL_TIME_TOOL_EDIT,
					this->B_CALCULATE_DISTANCE, this->toolStripSeparator2, this->B_ZOOM_IN, this->B_ZOOM_OUT, this->toolStripSeparator1, this->B_RESET_SETTING,
					this->B_CLEAR_MAP
			});
			this->REAL_TIME_TOOL_STRIP->Location = System::Drawing::Point(0, 0);
			this->REAL_TIME_TOOL_STRIP->Name = L"REAL_TIME_TOOL_STRIP";
			this->REAL_TIME_TOOL_STRIP->Size = System::Drawing::Size(153, 25);
			this->REAL_TIME_TOOL_STRIP->TabIndex = 217;
			// 
			// B_REAL_TIME_TOOL_EDIT
			// 
			this->B_REAL_TIME_TOOL_EDIT->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_REAL_TIME_TOOL_EDIT->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_REAL_TIME_TOOL_EDIT.Image")));
			this->B_REAL_TIME_TOOL_EDIT->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_REAL_TIME_TOOL_EDIT->Name = L"B_REAL_TIME_TOOL_EDIT";
			this->B_REAL_TIME_TOOL_EDIT->Size = System::Drawing::Size(23, 22);
			this->B_REAL_TIME_TOOL_EDIT->ToolTipText = L"Edit";
			this->B_REAL_TIME_TOOL_EDIT->Click += gcnew System::EventHandler(this, &MyForm::B_REAL_TIME_TOOL_EDIT_Click);
			// 
			// B_CALCULATE_DISTANCE
			// 
			this->B_CALCULATE_DISTANCE->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_CALCULATE_DISTANCE->Enabled = false;
			this->B_CALCULATE_DISTANCE->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_CALCULATE_DISTANCE.Image")));
			this->B_CALCULATE_DISTANCE->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_CALCULATE_DISTANCE->Name = L"B_CALCULATE_DISTANCE";
			this->B_CALCULATE_DISTANCE->Size = System::Drawing::Size(23, 22);
			this->B_CALCULATE_DISTANCE->ToolTipText = L"Calculate Distance";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
			// 
			// B_ZOOM_IN
			// 
			this->B_ZOOM_IN->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_ZOOM_IN->Enabled = false;
			this->B_ZOOM_IN->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_ZOOM_IN.Image")));
			this->B_ZOOM_IN->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_ZOOM_IN->Name = L"B_ZOOM_IN";
			this->B_ZOOM_IN->Size = System::Drawing::Size(23, 22);
			this->B_ZOOM_IN->Text = L"B_ZOOM_IN";
			this->B_ZOOM_IN->Click += gcnew System::EventHandler(this, &MyForm::B_ZOOM_IN_Click);
			// 
			// B_ZOOM_OUT
			// 
			this->B_ZOOM_OUT->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_ZOOM_OUT->Enabled = false;
			this->B_ZOOM_OUT->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_ZOOM_OUT.Image")));
			this->B_ZOOM_OUT->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_ZOOM_OUT->Name = L"B_ZOOM_OUT";
			this->B_ZOOM_OUT->Size = System::Drawing::Size(23, 22);
			this->B_ZOOM_OUT->Text = L"B_ZOOM_OUT";
			this->B_ZOOM_OUT->Click += gcnew System::EventHandler(this, &MyForm::B_ZOOM_OUT_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
			// 
			// B_RESET_SETTING
			// 
			this->B_RESET_SETTING->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_RESET_SETTING->Enabled = false;
			this->B_RESET_SETTING->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_RESET_SETTING.Image")));
			this->B_RESET_SETTING->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_RESET_SETTING->Name = L"B_RESET_SETTING";
			this->B_RESET_SETTING->Size = System::Drawing::Size(23, 22);
			this->B_RESET_SETTING->ToolTipText = L"Reset setting of system";
			// 
			// B_CLEAR_MAP
			// 
			this->B_CLEAR_MAP->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_CLEAR_MAP->Enabled = false;
			this->B_CLEAR_MAP->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_CLEAR_MAP.Image")));
			this->B_CLEAR_MAP->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_CLEAR_MAP->Name = L"B_CLEAR_MAP";
			this->B_CLEAR_MAP->Size = System::Drawing::Size(23, 22);
			this->B_CLEAR_MAP->ToolTipText = L"Clear Data";
			// 
			// panel5
			// 
			this->panel5->BackColor = System::Drawing::Color::White;
			this->panel5->ForeColor = System::Drawing::Color::White;
			this->panel5->Location = System::Drawing::Point(8, 551);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(60, 4);
			this->panel5->TabIndex = 213;
			// 
			// B_SCALE_VIEWER
			// 
			this->B_SCALE_VIEWER->AutoSize = true;
			this->B_SCALE_VIEWER->ForeColor = System::Drawing::Color::Black;
			this->B_SCALE_VIEWER->Location = System::Drawing::Point(15, 558);
			this->B_SCALE_VIEWER->Name = L"B_SCALE_VIEWER";
			this->B_SCALE_VIEWER->Size = System::Drawing::Size(25, 13);
			this->B_SCALE_VIEWER->TabIndex = 211;
			this->B_SCALE_VIEWER->Text = L"500";
			this->B_SCALE_VIEWER->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label265
			// 
			this->label265->AutoSize = true;
			this->label265->BackColor = System::Drawing::Color::DarkGray;
			this->label265->ForeColor = System::Drawing::Color::Black;
			this->label265->Location = System::Drawing::Point(50, 558);
			this->label265->Name = L"label265";
			this->label265->Size = System::Drawing::Size(15, 13);
			this->label265->TabIndex = 212;
			this->label265->Text = L"m";
			// 
			// RDM_VIEW
			// 
			this->RDM_VIEW->BackColor = System::Drawing::Color::Black;
			this->RDM_VIEW->Controls->Add(this->label238);
			this->RDM_VIEW->Controls->Add(this->label237);
			this->RDM_VIEW->Controls->Add(this->B_Color_Map);
			this->RDM_VIEW->Controls->Add(this->groupBox81);
			this->RDM_VIEW->Controls->Add(this->groupBox80);
			this->RDM_VIEW->Controls->Add(this->groupBox79);
			this->RDM_VIEW->Controls->Add(this->groupBox71);
			this->RDM_VIEW->Controls->Add(this->Range37);
			this->RDM_VIEW->Controls->Add(this->groupBox72);
			this->RDM_VIEW->Controls->Add(this->Range36);
			this->RDM_VIEW->Controls->Add(this->groupBox73);
			this->RDM_VIEW->Controls->Add(this->Range35);
			this->RDM_VIEW->Controls->Add(this->groupBox74);
			this->RDM_VIEW->Controls->Add(this->Range34);
			this->RDM_VIEW->Controls->Add(this->groupBox75);
			this->RDM_VIEW->Controls->Add(this->Range33);
			this->RDM_VIEW->Controls->Add(this->groupBox76);
			this->RDM_VIEW->Controls->Add(this->Range32);
			this->RDM_VIEW->Controls->Add(this->groupBox77);
			this->RDM_VIEW->Controls->Add(this->Range31);
			this->RDM_VIEW->Controls->Add(this->groupBox78);
			this->RDM_VIEW->Controls->Add(this->groupBox63);
			this->RDM_VIEW->Controls->Add(this->Range17);
			this->RDM_VIEW->Controls->Add(this->groupBox64);
			this->RDM_VIEW->Controls->Add(this->Range16);
			this->RDM_VIEW->Controls->Add(this->groupBox65);
			this->RDM_VIEW->Controls->Add(this->Range15);
			this->RDM_VIEW->Controls->Add(this->groupBox66);
			this->RDM_VIEW->Controls->Add(this->Range14);
			this->RDM_VIEW->Controls->Add(this->groupBox67);
			this->RDM_VIEW->Controls->Add(this->Range13);
			this->RDM_VIEW->Controls->Add(this->groupBox68);
			this->RDM_VIEW->Controls->Add(this->Range12);
			this->RDM_VIEW->Controls->Add(this->groupBox69);
			this->RDM_VIEW->Controls->Add(this->Range11);
			this->RDM_VIEW->Controls->Add(this->groupBox70);
			this->RDM_VIEW->Controls->Add(this->groupBox55);
			this->RDM_VIEW->Controls->Add(this->Range47);
			this->RDM_VIEW->Controls->Add(this->groupBox56);
			this->RDM_VIEW->Controls->Add(this->Range46);
			this->RDM_VIEW->Controls->Add(this->groupBox57);
			this->RDM_VIEW->Controls->Add(this->Range45);
			this->RDM_VIEW->Controls->Add(this->groupBox58);
			this->RDM_VIEW->Controls->Add(this->Range44);
			this->RDM_VIEW->Controls->Add(this->groupBox59);
			this->RDM_VIEW->Controls->Add(this->Range43);
			this->RDM_VIEW->Controls->Add(this->groupBox60);
			this->RDM_VIEW->Controls->Add(this->Range42);
			this->RDM_VIEW->Controls->Add(this->groupBox61);
			this->RDM_VIEW->Controls->Add(this->Range41);
			this->RDM_VIEW->Controls->Add(this->groupBox62);
			this->RDM_VIEW->Controls->Add(this->groupBox46);
			this->RDM_VIEW->Controls->Add(this->groupBox47);
			this->RDM_VIEW->Controls->Add(this->Velocity31);
			this->RDM_VIEW->Controls->Add(this->groupBox48);
			this->RDM_VIEW->Controls->Add(this->Velocity32);
			this->RDM_VIEW->Controls->Add(this->groupBox49);
			this->RDM_VIEW->Controls->Add(this->Velocity33);
			this->RDM_VIEW->Controls->Add(this->groupBox50);
			this->RDM_VIEW->Controls->Add(this->groupBox51);
			this->RDM_VIEW->Controls->Add(this->Velocity36);
			this->RDM_VIEW->Controls->Add(this->groupBox52);
			this->RDM_VIEW->Controls->Add(this->Velocity35);
			this->RDM_VIEW->Controls->Add(this->groupBox53);
			this->RDM_VIEW->Controls->Add(this->Velocity34);
			this->RDM_VIEW->Controls->Add(this->groupBox54);
			this->RDM_VIEW->Controls->Add(this->groupBox37);
			this->RDM_VIEW->Controls->Add(this->groupBox38);
			this->RDM_VIEW->Controls->Add(this->Velocity11);
			this->RDM_VIEW->Controls->Add(this->groupBox39);
			this->RDM_VIEW->Controls->Add(this->Velocity12);
			this->RDM_VIEW->Controls->Add(this->groupBox40);
			this->RDM_VIEW->Controls->Add(this->Velocity13);
			this->RDM_VIEW->Controls->Add(this->groupBox41);
			this->RDM_VIEW->Controls->Add(this->groupBox42);
			this->RDM_VIEW->Controls->Add(this->Velocity16);
			this->RDM_VIEW->Controls->Add(this->groupBox43);
			this->RDM_VIEW->Controls->Add(this->Velocity15);
			this->RDM_VIEW->Controls->Add(this->groupBox44);
			this->RDM_VIEW->Controls->Add(this->Velocity14);
			this->RDM_VIEW->Controls->Add(this->groupBox45);
			this->RDM_VIEW->Controls->Add(this->groupBox28);
			this->RDM_VIEW->Controls->Add(this->groupBox29);
			this->RDM_VIEW->Controls->Add(this->Velocity41);
			this->RDM_VIEW->Controls->Add(this->groupBox30);
			this->RDM_VIEW->Controls->Add(this->Velocity42);
			this->RDM_VIEW->Controls->Add(this->groupBox31);
			this->RDM_VIEW->Controls->Add(this->Velocity43);
			this->RDM_VIEW->Controls->Add(this->groupBox32);
			this->RDM_VIEW->Controls->Add(this->groupBox33);
			this->RDM_VIEW->Controls->Add(this->Velocity46);
			this->RDM_VIEW->Controls->Add(this->groupBox34);
			this->RDM_VIEW->Controls->Add(this->Velocity45);
			this->RDM_VIEW->Controls->Add(this->groupBox35);
			this->RDM_VIEW->Controls->Add(this->Velocity44);
			this->RDM_VIEW->Controls->Add(this->groupBox36);
			this->RDM_VIEW->Controls->Add(this->groupBox27);
			this->RDM_VIEW->Controls->Add(this->groupBox26);
			this->RDM_VIEW->Controls->Add(this->Velocity21);
			this->RDM_VIEW->Controls->Add(this->groupBox25);
			this->RDM_VIEW->Controls->Add(this->Velocity22);
			this->RDM_VIEW->Controls->Add(this->groupBox24);
			this->RDM_VIEW->Controls->Add(this->Velocity23);
			this->RDM_VIEW->Controls->Add(this->groupBox23);
			this->RDM_VIEW->Controls->Add(this->groupBox22);
			this->RDM_VIEW->Controls->Add(this->Velocity26);
			this->RDM_VIEW->Controls->Add(this->groupBox21);
			this->RDM_VIEW->Controls->Add(this->Velocity25);
			this->RDM_VIEW->Controls->Add(this->groupBox20);
			this->RDM_VIEW->Controls->Add(this->Velocity24);
			this->RDM_VIEW->Controls->Add(this->groupBox19);
			this->RDM_VIEW->Controls->Add(this->groupBox18);
			this->RDM_VIEW->Controls->Add(this->groupBox17);
			this->RDM_VIEW->Controls->Add(this->Range27);
			this->RDM_VIEW->Controls->Add(this->groupBox16);
			this->RDM_VIEW->Controls->Add(this->Range26);
			this->RDM_VIEW->Controls->Add(this->groupBox15);
			this->RDM_VIEW->Controls->Add(this->Range25);
			this->RDM_VIEW->Controls->Add(this->groupBox14);
			this->RDM_VIEW->Controls->Add(this->Range24);
			this->RDM_VIEW->Controls->Add(this->groupBox13);
			this->RDM_VIEW->Controls->Add(this->Range23);
			this->RDM_VIEW->Controls->Add(this->groupBox12);
			this->RDM_VIEW->Controls->Add(this->Range22);
			this->RDM_VIEW->Controls->Add(this->groupBox8);
			this->RDM_VIEW->Controls->Add(this->Range21);
			this->RDM_VIEW->Controls->Add(this->groupBox4);
			this->RDM_VIEW->Controls->Add(this->label209);
			this->RDM_VIEW->Controls->Add(this->label208);
			this->RDM_VIEW->Controls->Add(this->label207);
			this->RDM_VIEW->Controls->Add(this->label206);
			this->RDM_VIEW->Controls->Add(this->Velocity_min_3);
			this->RDM_VIEW->Controls->Add(this->Velocity_min_1);
			this->RDM_VIEW->Controls->Add(this->Velocity_min_2);
			this->RDM_VIEW->Controls->Add(this->Velocity_min_4);
			this->RDM_VIEW->Controls->Add(this->Velocity_max_3);
			this->RDM_VIEW->Controls->Add(this->Velocity_max_4);
			this->RDM_VIEW->Controls->Add(this->Velocity_max_2);
			this->RDM_VIEW->Controls->Add(this->Velocity_max_1);
			this->RDM_VIEW->Controls->Add(this->Range_max_4);
			this->RDM_VIEW->Controls->Add(this->Range_max_3);
			this->RDM_VIEW->Controls->Add(this->Range_max_2);
			this->RDM_VIEW->Controls->Add(this->Range_max_1);
			this->RDM_VIEW->Controls->Add(this->label205);
			this->RDM_VIEW->Controls->Add(this->label204);
			this->RDM_VIEW->Controls->Add(this->label203);
			this->RDM_VIEW->Controls->Add(this->label202);
			this->RDM_VIEW->Controls->Add(this->label201);
			this->RDM_VIEW->Controls->Add(this->label200);
			this->RDM_VIEW->Controls->Add(this->label199);
			this->RDM_VIEW->Controls->Add(this->label198);
			this->RDM_VIEW->Controls->Add(this->label197);
			this->RDM_VIEW->Controls->Add(this->label196);
			this->RDM_VIEW->Controls->Add(this->label195);
			this->RDM_VIEW->Controls->Add(this->label194);
			this->RDM_VIEW->Controls->Add(this->B_RDM_V_R);
			this->RDM_VIEW->Controls->Add(this->B_RDM_V_L);
			this->RDM_VIEW->Controls->Add(this->B_RDM_H_R);
			this->RDM_VIEW->Controls->Add(this->B_RDM_H_L);
			this->RDM_VIEW->Controls->Add(this->label213);
			this->RDM_VIEW->Controls->Add(this->groupBox82);
			this->RDM_VIEW->Controls->Add(this->label214);
			this->RDM_VIEW->Controls->Add(this->label212);
			this->RDM_VIEW->Controls->Add(this->label215);
			this->RDM_VIEW->Controls->Add(this->label216);
			this->RDM_VIEW->Controls->Add(this->groupBox83);
			this->RDM_VIEW->Controls->Add(this->label217);
			this->RDM_VIEW->Controls->Add(this->label218);
			this->RDM_VIEW->Controls->Add(this->label219);
			this->RDM_VIEW->Controls->Add(this->label220);
			this->RDM_VIEW->Controls->Add(this->groupBox84);
			this->RDM_VIEW->Controls->Add(this->label221);
			this->RDM_VIEW->Controls->Add(this->label222);
			this->RDM_VIEW->Controls->Add(this->label223);
			this->RDM_VIEW->Controls->Add(this->label224);
			this->RDM_VIEW->Controls->Add(this->groupBox85);
			this->RDM_VIEW->Controls->Add(this->label225);
			this->RDM_VIEW->Controls->Add(this->label226);
			this->RDM_VIEW->Controls->Add(this->label227);
			this->RDM_VIEW->Controls->Add(this->label230);
			this->RDM_VIEW->Controls->Add(this->label229);
			this->RDM_VIEW->Controls->Add(this->label231);
			this->RDM_VIEW->Controls->Add(this->label232);
			this->RDM_VIEW->Controls->Add(this->label233);
			this->RDM_VIEW->Controls->Add(this->label234);
			this->RDM_VIEW->Controls->Add(this->label235);
			this->RDM_VIEW->Controls->Add(this->label236);
			this->RDM_VIEW->Controls->Add(this->label239);
			this->RDM_VIEW->Location = System::Drawing::Point(4, 22);
			this->RDM_VIEW->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->RDM_VIEW->Name = L"RDM_VIEW";
			this->RDM_VIEW->Size = System::Drawing::Size(828, 590);
			this->RDM_VIEW->TabIndex = 5;
			this->RDM_VIEW->Text = L"RDM";
			// 
			// label238
			// 
			this->label238->AutoSize = true;
			this->label238->ForeColor = System::Drawing::Color::White;
			this->label238->Location = System::Drawing::Point(814, 42);
			this->label238->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label238->Name = L"label238";
			this->label238->Size = System::Drawing::Size(14, 13);
			this->label238->TabIndex = 197;
			this->label238->Text = L"C";
			// 
			// label237
			// 
			this->label237->AutoSize = true;
			this->label237->ForeColor = System::Drawing::Color::White;
			this->label237->Location = System::Drawing::Point(788, 40);
			this->label237->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label237->Name = L"label237";
			this->label237->Size = System::Drawing::Size(26, 13);
			this->label237->TabIndex = 196;
			this->label237->Text = L"[dB]";
			// 
			// B_Color_Map
			// 
			this->B_Color_Map->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_Color_Map->Location = System::Drawing::Point(811, 59);
			this->B_Color_Map->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Color_Map->Name = L"B_Color_Map";
			this->B_Color_Map->Size = System::Drawing::Size(18, 133);
			this->B_Color_Map->TabIndex = 187;
			this->B_Color_Map->TabStop = false;
			// 
			// groupBox81
			// 
			this->groupBox81->BackColor = System::Drawing::Color::White;
			this->groupBox81->Location = System::Drawing::Point(785, 555);
			this->groupBox81->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox81->Name = L"groupBox81";
			this->groupBox81->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox81->Size = System::Drawing::Size(2, 20);
			this->groupBox81->TabIndex = 161;
			this->groupBox81->TabStop = false;
			this->groupBox81->Text = L"groupBox81";
			// 
			// groupBox80
			// 
			this->groupBox80->BackColor = System::Drawing::Color::White;
			this->groupBox80->Location = System::Drawing::Point(389, 555);
			this->groupBox80->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox80->Name = L"groupBox80";
			this->groupBox80->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox80->Size = System::Drawing::Size(2, 20);
			this->groupBox80->TabIndex = 160;
			this->groupBox80->TabStop = false;
			this->groupBox80->Text = L"groupBox80";
			// 
			// groupBox79
			// 
			this->groupBox79->BackColor = System::Drawing::Color::White;
			this->groupBox79->Location = System::Drawing::Point(389, 260);
			this->groupBox79->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox79->Name = L"groupBox79";
			this->groupBox79->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox79->Size = System::Drawing::Size(2, 20);
			this->groupBox79->TabIndex = 159;
			this->groupBox79->TabStop = false;
			this->groupBox79->Text = L"groupBox79";
			// 
			// groupBox71
			// 
			this->groupBox71->BackColor = System::Drawing::Color::White;
			this->groupBox71->Location = System::Drawing::Point(350, 555);
			this->groupBox71->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox71->Name = L"groupBox71";
			this->groupBox71->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox71->Size = System::Drawing::Size(2, 20);
			this->groupBox71->TabIndex = 157;
			this->groupBox71->TabStop = false;
			this->groupBox71->Text = L"groupBox71";
			// 
			// Range37
			// 
			this->Range37->AutoSize = true;
			this->Range37->ForeColor = System::Drawing::Color::White;
			this->Range37->Location = System::Drawing::Point(343, 573);
			this->Range37->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range37->Name = L"Range37";
			this->Range37->Size = System::Drawing::Size(10, 13);
			this->Range37->TabIndex = 158;
			this->Range37->Text = L"-";
			// 
			// groupBox72
			// 
			this->groupBox72->BackColor = System::Drawing::Color::White;
			this->groupBox72->Location = System::Drawing::Point(311, 555);
			this->groupBox72->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox72->Name = L"groupBox72";
			this->groupBox72->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox72->Size = System::Drawing::Size(2, 20);
			this->groupBox72->TabIndex = 155;
			this->groupBox72->TabStop = false;
			this->groupBox72->Text = L"groupBox72";
			// 
			// Range36
			// 
			this->Range36->AutoSize = true;
			this->Range36->ForeColor = System::Drawing::Color::White;
			this->Range36->Location = System::Drawing::Point(302, 573);
			this->Range36->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range36->Name = L"Range36";
			this->Range36->Size = System::Drawing::Size(10, 13);
			this->Range36->TabIndex = 156;
			this->Range36->Text = L"-";
			// 
			// groupBox73
			// 
			this->groupBox73->BackColor = System::Drawing::Color::White;
			this->groupBox73->Location = System::Drawing::Point(271, 555);
			this->groupBox73->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox73->Name = L"groupBox73";
			this->groupBox73->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox73->Size = System::Drawing::Size(2, 20);
			this->groupBox73->TabIndex = 153;
			this->groupBox73->TabStop = false;
			this->groupBox73->Text = L"groupBox73";
			// 
			// Range35
			// 
			this->Range35->AutoSize = true;
			this->Range35->ForeColor = System::Drawing::Color::White;
			this->Range35->Location = System::Drawing::Point(262, 573);
			this->Range35->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range35->Name = L"Range35";
			this->Range35->Size = System::Drawing::Size(10, 13);
			this->Range35->TabIndex = 154;
			this->Range35->Text = L"-";
			// 
			// groupBox74
			// 
			this->groupBox74->BackColor = System::Drawing::Color::White;
			this->groupBox74->Location = System::Drawing::Point(230, 555);
			this->groupBox74->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox74->Name = L"groupBox74";
			this->groupBox74->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox74->Size = System::Drawing::Size(2, 20);
			this->groupBox74->TabIndex = 151;
			this->groupBox74->TabStop = false;
			this->groupBox74->Text = L"groupBox74";
			// 
			// Range34
			// 
			this->Range34->AutoSize = true;
			this->Range34->ForeColor = System::Drawing::Color::White;
			this->Range34->Location = System::Drawing::Point(222, 573);
			this->Range34->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range34->Name = L"Range34";
			this->Range34->Size = System::Drawing::Size(10, 13);
			this->Range34->TabIndex = 152;
			this->Range34->Text = L"-";
			// 
			// groupBox75
			// 
			this->groupBox75->BackColor = System::Drawing::Color::White;
			this->groupBox75->Location = System::Drawing::Point(191, 555);
			this->groupBox75->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox75->Name = L"groupBox75";
			this->groupBox75->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox75->Size = System::Drawing::Size(2, 20);
			this->groupBox75->TabIndex = 149;
			this->groupBox75->TabStop = false;
			this->groupBox75->Text = L"groupBox75";
			// 
			// Range33
			// 
			this->Range33->AutoSize = true;
			this->Range33->ForeColor = System::Drawing::Color::White;
			this->Range33->Location = System::Drawing::Point(182, 573);
			this->Range33->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range33->Name = L"Range33";
			this->Range33->Size = System::Drawing::Size(10, 13);
			this->Range33->TabIndex = 150;
			this->Range33->Text = L"-";
			// 
			// groupBox76
			// 
			this->groupBox76->BackColor = System::Drawing::Color::White;
			this->groupBox76->Location = System::Drawing::Point(151, 555);
			this->groupBox76->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox76->Name = L"groupBox76";
			this->groupBox76->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox76->Size = System::Drawing::Size(2, 20);
			this->groupBox76->TabIndex = 147;
			this->groupBox76->TabStop = false;
			this->groupBox76->Text = L"groupBox76";
			// 
			// Range32
			// 
			this->Range32->AutoSize = true;
			this->Range32->ForeColor = System::Drawing::Color::White;
			this->Range32->Location = System::Drawing::Point(142, 573);
			this->Range32->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range32->Name = L"Range32";
			this->Range32->Size = System::Drawing::Size(10, 13);
			this->Range32->TabIndex = 148;
			this->Range32->Text = L"-";
			// 
			// groupBox77
			// 
			this->groupBox77->BackColor = System::Drawing::Color::White;
			this->groupBox77->Location = System::Drawing::Point(110, 555);
			this->groupBox77->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox77->Name = L"groupBox77";
			this->groupBox77->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox77->Size = System::Drawing::Size(2, 20);
			this->groupBox77->TabIndex = 146;
			this->groupBox77->TabStop = false;
			this->groupBox77->Text = L"groupBox77";
			// 
			// Range31
			// 
			this->Range31->AutoSize = true;
			this->Range31->ForeColor = System::Drawing::Color::White;
			this->Range31->Location = System::Drawing::Point(103, 573);
			this->Range31->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range31->Name = L"Range31";
			this->Range31->Size = System::Drawing::Size(10, 13);
			this->Range31->TabIndex = 145;
			this->Range31->Text = L"-";
			// 
			// groupBox78
			// 
			this->groupBox78->BackColor = System::Drawing::Color::White;
			this->groupBox78->Location = System::Drawing::Point(71, 555);
			this->groupBox78->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox78->Name = L"groupBox78";
			this->groupBox78->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox78->Size = System::Drawing::Size(2, 20);
			this->groupBox78->TabIndex = 144;
			this->groupBox78->TabStop = false;
			this->groupBox78->Text = L"groupBox78";
			// 
			// groupBox63
			// 
			this->groupBox63->BackColor = System::Drawing::Color::White;
			this->groupBox63->Location = System::Drawing::Point(350, 261);
			this->groupBox63->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox63->Name = L"groupBox63";
			this->groupBox63->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox63->Size = System::Drawing::Size(2, 20);
			this->groupBox63->TabIndex = 142;
			this->groupBox63->TabStop = false;
			this->groupBox63->Text = L"groupBox63";
			// 
			// Range17
			// 
			this->Range17->AutoSize = true;
			this->Range17->ForeColor = System::Drawing::Color::White;
			this->Range17->Location = System::Drawing::Point(343, 279);
			this->Range17->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range17->Name = L"Range17";
			this->Range17->Size = System::Drawing::Size(10, 13);
			this->Range17->TabIndex = 143;
			this->Range17->Text = L"-";
			// 
			// groupBox64
			// 
			this->groupBox64->BackColor = System::Drawing::Color::White;
			this->groupBox64->Location = System::Drawing::Point(311, 261);
			this->groupBox64->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox64->Name = L"groupBox64";
			this->groupBox64->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox64->Size = System::Drawing::Size(2, 20);
			this->groupBox64->TabIndex = 140;
			this->groupBox64->TabStop = false;
			this->groupBox64->Text = L"groupBox64";
			// 
			// Range16
			// 
			this->Range16->AutoSize = true;
			this->Range16->ForeColor = System::Drawing::Color::White;
			this->Range16->Location = System::Drawing::Point(302, 279);
			this->Range16->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range16->Name = L"Range16";
			this->Range16->Size = System::Drawing::Size(10, 13);
			this->Range16->TabIndex = 141;
			this->Range16->Text = L"-";
			// 
			// groupBox65
			// 
			this->groupBox65->BackColor = System::Drawing::Color::White;
			this->groupBox65->Location = System::Drawing::Point(271, 261);
			this->groupBox65->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox65->Name = L"groupBox65";
			this->groupBox65->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox65->Size = System::Drawing::Size(2, 20);
			this->groupBox65->TabIndex = 138;
			this->groupBox65->TabStop = false;
			this->groupBox65->Text = L"groupBox65";
			// 
			// Range15
			// 
			this->Range15->AutoSize = true;
			this->Range15->ForeColor = System::Drawing::Color::White;
			this->Range15->Location = System::Drawing::Point(263, 279);
			this->Range15->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range15->Name = L"Range15";
			this->Range15->Size = System::Drawing::Size(10, 13);
			this->Range15->TabIndex = 139;
			this->Range15->Text = L"-";
			// 
			// groupBox66
			// 
			this->groupBox66->BackColor = System::Drawing::Color::White;
			this->groupBox66->Location = System::Drawing::Point(230, 261);
			this->groupBox66->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox66->Name = L"groupBox66";
			this->groupBox66->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox66->Size = System::Drawing::Size(2, 20);
			this->groupBox66->TabIndex = 136;
			this->groupBox66->TabStop = false;
			this->groupBox66->Text = L"groupBox66";
			// 
			// Range14
			// 
			this->Range14->AutoSize = true;
			this->Range14->ForeColor = System::Drawing::Color::White;
			this->Range14->Location = System::Drawing::Point(222, 279);
			this->Range14->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range14->Name = L"Range14";
			this->Range14->Size = System::Drawing::Size(10, 13);
			this->Range14->TabIndex = 137;
			this->Range14->Text = L"-";
			// 
			// groupBox67
			// 
			this->groupBox67->BackColor = System::Drawing::Color::White;
			this->groupBox67->Location = System::Drawing::Point(191, 261);
			this->groupBox67->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox67->Name = L"groupBox67";
			this->groupBox67->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox67->Size = System::Drawing::Size(2, 20);
			this->groupBox67->TabIndex = 134;
			this->groupBox67->TabStop = false;
			this->groupBox67->Text = L"groupBox67";
			// 
			// Range13
			// 
			this->Range13->AutoSize = true;
			this->Range13->ForeColor = System::Drawing::Color::White;
			this->Range13->Location = System::Drawing::Point(182, 279);
			this->Range13->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range13->Name = L"Range13";
			this->Range13->Size = System::Drawing::Size(10, 13);
			this->Range13->TabIndex = 135;
			this->Range13->Text = L"-";
			// 
			// groupBox68
			// 
			this->groupBox68->BackColor = System::Drawing::Color::White;
			this->groupBox68->Location = System::Drawing::Point(151, 261);
			this->groupBox68->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox68->Name = L"groupBox68";
			this->groupBox68->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox68->Size = System::Drawing::Size(2, 20);
			this->groupBox68->TabIndex = 132;
			this->groupBox68->TabStop = false;
			this->groupBox68->Text = L"groupBox68";
			// 
			// Range12
			// 
			this->Range12->AutoSize = true;
			this->Range12->ForeColor = System::Drawing::Color::White;
			this->Range12->Location = System::Drawing::Point(143, 279);
			this->Range12->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range12->Name = L"Range12";
			this->Range12->Size = System::Drawing::Size(10, 13);
			this->Range12->TabIndex = 133;
			this->Range12->Text = L"-";
			// 
			// groupBox69
			// 
			this->groupBox69->BackColor = System::Drawing::Color::White;
			this->groupBox69->Location = System::Drawing::Point(110, 261);
			this->groupBox69->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox69->Name = L"groupBox69";
			this->groupBox69->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox69->Size = System::Drawing::Size(2, 20);
			this->groupBox69->TabIndex = 131;
			this->groupBox69->TabStop = false;
			this->groupBox69->Text = L"groupBox69";
			// 
			// Range11
			// 
			this->Range11->AutoSize = true;
			this->Range11->ForeColor = System::Drawing::Color::White;
			this->Range11->Location = System::Drawing::Point(102, 279);
			this->Range11->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range11->Name = L"Range11";
			this->Range11->Size = System::Drawing::Size(10, 13);
			this->Range11->TabIndex = 130;
			this->Range11->Text = L"-";
			// 
			// groupBox70
			// 
			this->groupBox70->BackColor = System::Drawing::Color::White;
			this->groupBox70->Location = System::Drawing::Point(71, 261);
			this->groupBox70->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox70->Name = L"groupBox70";
			this->groupBox70->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox70->Size = System::Drawing::Size(2, 20);
			this->groupBox70->TabIndex = 129;
			this->groupBox70->TabStop = false;
			this->groupBox70->Text = L"groupBox70";
			// 
			// groupBox55
			// 
			this->groupBox55->BackColor = System::Drawing::Color::White;
			this->groupBox55->Location = System::Drawing::Point(746, 555);
			this->groupBox55->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox55->Name = L"groupBox55";
			this->groupBox55->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox55->Size = System::Drawing::Size(2, 20);
			this->groupBox55->TabIndex = 127;
			this->groupBox55->TabStop = false;
			this->groupBox55->Text = L"groupBox55";
			// 
			// Range47
			// 
			this->Range47->AutoSize = true;
			this->Range47->ForeColor = System::Drawing::Color::White;
			this->Range47->Location = System::Drawing::Point(739, 573);
			this->Range47->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range47->Name = L"Range47";
			this->Range47->Size = System::Drawing::Size(10, 13);
			this->Range47->TabIndex = 128;
			this->Range47->Text = L"-";
			// 
			// groupBox56
			// 
			this->groupBox56->BackColor = System::Drawing::Color::White;
			this->groupBox56->Location = System::Drawing::Point(707, 555);
			this->groupBox56->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox56->Name = L"groupBox56";
			this->groupBox56->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox56->Size = System::Drawing::Size(2, 20);
			this->groupBox56->TabIndex = 125;
			this->groupBox56->TabStop = false;
			this->groupBox56->Text = L"groupBox56";
			// 
			// Range46
			// 
			this->Range46->AutoSize = true;
			this->Range46->ForeColor = System::Drawing::Color::White;
			this->Range46->Location = System::Drawing::Point(700, 573);
			this->Range46->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range46->Name = L"Range46";
			this->Range46->Size = System::Drawing::Size(10, 13);
			this->Range46->TabIndex = 126;
			this->Range46->Text = L"-";
			// 
			// groupBox57
			// 
			this->groupBox57->BackColor = System::Drawing::Color::White;
			this->groupBox57->Location = System::Drawing::Point(667, 555);
			this->groupBox57->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox57->Name = L"groupBox57";
			this->groupBox57->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox57->Size = System::Drawing::Size(2, 20);
			this->groupBox57->TabIndex = 123;
			this->groupBox57->TabStop = false;
			this->groupBox57->Text = L"groupBox57";
			// 
			// Range45
			// 
			this->Range45->AutoSize = true;
			this->Range45->ForeColor = System::Drawing::Color::White;
			this->Range45->Location = System::Drawing::Point(659, 573);
			this->Range45->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range45->Name = L"Range45";
			this->Range45->Size = System::Drawing::Size(10, 13);
			this->Range45->TabIndex = 124;
			this->Range45->Text = L"-";
			// 
			// groupBox58
			// 
			this->groupBox58->BackColor = System::Drawing::Color::White;
			this->groupBox58->Location = System::Drawing::Point(626, 555);
			this->groupBox58->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox58->Name = L"groupBox58";
			this->groupBox58->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox58->Size = System::Drawing::Size(2, 20);
			this->groupBox58->TabIndex = 121;
			this->groupBox58->TabStop = false;
			this->groupBox58->Text = L"groupBox58";
			// 
			// Range44
			// 
			this->Range44->AutoSize = true;
			this->Range44->ForeColor = System::Drawing::Color::White;
			this->Range44->Location = System::Drawing::Point(619, 573);
			this->Range44->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range44->Name = L"Range44";
			this->Range44->Size = System::Drawing::Size(10, 13);
			this->Range44->TabIndex = 122;
			this->Range44->Text = L"-";
			// 
			// groupBox59
			// 
			this->groupBox59->BackColor = System::Drawing::Color::White;
			this->groupBox59->Location = System::Drawing::Point(587, 555);
			this->groupBox59->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox59->Name = L"groupBox59";
			this->groupBox59->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox59->Size = System::Drawing::Size(2, 20);
			this->groupBox59->TabIndex = 119;
			this->groupBox59->TabStop = false;
			this->groupBox59->Text = L"groupBox59";
			// 
			// Range43
			// 
			this->Range43->AutoSize = true;
			this->Range43->ForeColor = System::Drawing::Color::White;
			this->Range43->Location = System::Drawing::Point(578, 573);
			this->Range43->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range43->Name = L"Range43";
			this->Range43->Size = System::Drawing::Size(10, 13);
			this->Range43->TabIndex = 120;
			this->Range43->Text = L"-";
			// 
			// groupBox60
			// 
			this->groupBox60->BackColor = System::Drawing::Color::White;
			this->groupBox60->Location = System::Drawing::Point(547, 555);
			this->groupBox60->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox60->Name = L"groupBox60";
			this->groupBox60->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox60->Size = System::Drawing::Size(2, 20);
			this->groupBox60->TabIndex = 117;
			this->groupBox60->TabStop = false;
			this->groupBox60->Text = L"groupBox60";
			// 
			// Range42
			// 
			this->Range42->AutoSize = true;
			this->Range42->ForeColor = System::Drawing::Color::White;
			this->Range42->Location = System::Drawing::Point(539, 573);
			this->Range42->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range42->Name = L"Range42";
			this->Range42->Size = System::Drawing::Size(10, 13);
			this->Range42->TabIndex = 118;
			this->Range42->Text = L"-";
			// 
			// groupBox61
			// 
			this->groupBox61->BackColor = System::Drawing::Color::White;
			this->groupBox61->Location = System::Drawing::Point(506, 555);
			this->groupBox61->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox61->Name = L"groupBox61";
			this->groupBox61->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox61->Size = System::Drawing::Size(2, 20);
			this->groupBox61->TabIndex = 116;
			this->groupBox61->TabStop = false;
			this->groupBox61->Text = L"groupBox61";
			// 
			// Range41
			// 
			this->Range41->AutoSize = true;
			this->Range41->ForeColor = System::Drawing::Color::White;
			this->Range41->Location = System::Drawing::Point(498, 573);
			this->Range41->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range41->Name = L"Range41";
			this->Range41->Size = System::Drawing::Size(10, 13);
			this->Range41->TabIndex = 115;
			this->Range41->Text = L"-";
			// 
			// groupBox62
			// 
			this->groupBox62->BackColor = System::Drawing::Color::White;
			this->groupBox62->Location = System::Drawing::Point(467, 555);
			this->groupBox62->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox62->Name = L"groupBox62";
			this->groupBox62->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox62->Size = System::Drawing::Size(2, 20);
			this->groupBox62->TabIndex = 114;
			this->groupBox62->TabStop = false;
			this->groupBox62->Text = L"groupBox62";
			// 
			// groupBox46
			// 
			this->groupBox46->BackColor = System::Drawing::Color::White;
			this->groupBox46->Location = System::Drawing::Point(62, 311);
			this->groupBox46->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox46->Name = L"groupBox46";
			this->groupBox46->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox46->Size = System::Drawing::Size(20, 1);
			this->groupBox46->TabIndex = 113;
			this->groupBox46->TabStop = false;
			this->groupBox46->Text = L"groupBox46";
			// 
			// groupBox47
			// 
			this->groupBox47->BackColor = System::Drawing::Color::White;
			this->groupBox47->Location = System::Drawing::Point(62, 342);
			this->groupBox47->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox47->Name = L"groupBox47";
			this->groupBox47->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox47->Size = System::Drawing::Size(20, 1);
			this->groupBox47->TabIndex = 112;
			this->groupBox47->TabStop = false;
			this->groupBox47->Text = L"groupBox47";
			// 
			// Velocity31
			// 
			this->Velocity31->AutoSize = true;
			this->Velocity31->ForeColor = System::Drawing::Color::White;
			this->Velocity31->Location = System::Drawing::Point(34, 337);
			this->Velocity31->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity31->Name = L"Velocity31";
			this->Velocity31->Size = System::Drawing::Size(10, 13);
			this->Velocity31->TabIndex = 111;
			this->Velocity31->Text = L"-";
			// 
			// groupBox48
			// 
			this->groupBox48->BackColor = System::Drawing::Color::White;
			this->groupBox48->Location = System::Drawing::Point(62, 374);
			this->groupBox48->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox48->Name = L"groupBox48";
			this->groupBox48->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox48->Size = System::Drawing::Size(20, 1);
			this->groupBox48->TabIndex = 110;
			this->groupBox48->TabStop = false;
			this->groupBox48->Text = L"groupBox48";
			// 
			// Velocity32
			// 
			this->Velocity32->AutoSize = true;
			this->Velocity32->ForeColor = System::Drawing::Color::White;
			this->Velocity32->Location = System::Drawing::Point(34, 368);
			this->Velocity32->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity32->Name = L"Velocity32";
			this->Velocity32->Size = System::Drawing::Size(10, 13);
			this->Velocity32->TabIndex = 109;
			this->Velocity32->Text = L"-";
			// 
			// groupBox49
			// 
			this->groupBox49->BackColor = System::Drawing::Color::White;
			this->groupBox49->Location = System::Drawing::Point(62, 406);
			this->groupBox49->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox49->Name = L"groupBox49";
			this->groupBox49->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox49->Size = System::Drawing::Size(20, 1);
			this->groupBox49->TabIndex = 108;
			this->groupBox49->TabStop = false;
			this->groupBox49->Text = L"groupBox49";
			// 
			// Velocity33
			// 
			this->Velocity33->AutoSize = true;
			this->Velocity33->ForeColor = System::Drawing::Color::White;
			this->Velocity33->Location = System::Drawing::Point(34, 400);
			this->Velocity33->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity33->Name = L"Velocity33";
			this->Velocity33->Size = System::Drawing::Size(10, 13);
			this->Velocity33->TabIndex = 107;
			this->Velocity33->Text = L"-";
			// 
			// groupBox50
			// 
			this->groupBox50->BackColor = System::Drawing::Color::White;
			this->groupBox50->Location = System::Drawing::Point(62, 563);
			this->groupBox50->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox50->Name = L"groupBox50";
			this->groupBox50->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox50->Size = System::Drawing::Size(20, 1);
			this->groupBox50->TabIndex = 106;
			this->groupBox50->TabStop = false;
			this->groupBox50->Text = L"groupBox50";
			// 
			// groupBox51
			// 
			this->groupBox51->BackColor = System::Drawing::Color::White;
			this->groupBox51->Location = System::Drawing::Point(62, 534);
			this->groupBox51->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox51->Name = L"groupBox51";
			this->groupBox51->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox51->Size = System::Drawing::Size(20, 1);
			this->groupBox51->TabIndex = 105;
			this->groupBox51->TabStop = false;
			this->groupBox51->Text = L"groupBox51";
			// 
			// Velocity36
			// 
			this->Velocity36->AutoSize = true;
			this->Velocity36->ForeColor = System::Drawing::Color::White;
			this->Velocity36->Location = System::Drawing::Point(34, 529);
			this->Velocity36->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity36->Name = L"Velocity36";
			this->Velocity36->Size = System::Drawing::Size(10, 13);
			this->Velocity36->TabIndex = 104;
			this->Velocity36->Text = L"-";
			// 
			// groupBox52
			// 
			this->groupBox52->BackColor = System::Drawing::Color::White;
			this->groupBox52->Location = System::Drawing::Point(62, 503);
			this->groupBox52->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox52->Name = L"groupBox52";
			this->groupBox52->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox52->Size = System::Drawing::Size(20, 1);
			this->groupBox52->TabIndex = 103;
			this->groupBox52->TabStop = false;
			this->groupBox52->Text = L"groupBox52";
			// 
			// Velocity35
			// 
			this->Velocity35->AutoSize = true;
			this->Velocity35->ForeColor = System::Drawing::Color::White;
			this->Velocity35->Location = System::Drawing::Point(34, 495);
			this->Velocity35->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity35->Name = L"Velocity35";
			this->Velocity35->Size = System::Drawing::Size(10, 13);
			this->Velocity35->TabIndex = 102;
			this->Velocity35->Text = L"-";
			// 
			// groupBox53
			// 
			this->groupBox53->BackColor = System::Drawing::Color::White;
			this->groupBox53->Location = System::Drawing::Point(62, 469);
			this->groupBox53->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox53->Name = L"groupBox53";
			this->groupBox53->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox53->Size = System::Drawing::Size(20, 1);
			this->groupBox53->TabIndex = 101;
			this->groupBox53->TabStop = false;
			this->groupBox53->Text = L"groupBox53";
			// 
			// Velocity34
			// 
			this->Velocity34->AutoSize = true;
			this->Velocity34->ForeColor = System::Drawing::Color::White;
			this->Velocity34->Location = System::Drawing::Point(34, 464);
			this->Velocity34->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity34->Name = L"Velocity34";
			this->Velocity34->Size = System::Drawing::Size(10, 13);
			this->Velocity34->TabIndex = 100;
			this->Velocity34->Text = L"-";
			// 
			// groupBox54
			// 
			this->groupBox54->BackColor = System::Drawing::Color::White;
			this->groupBox54->Location = System::Drawing::Point(62, 438);
			this->groupBox54->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox54->Name = L"groupBox54";
			this->groupBox54->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox54->Size = System::Drawing::Size(20, 1);
			this->groupBox54->TabIndex = 99;
			this->groupBox54->TabStop = false;
			this->groupBox54->Text = L"groupBox54";
			// 
			// groupBox37
			// 
			this->groupBox37->BackColor = System::Drawing::Color::White;
			this->groupBox37->Location = System::Drawing::Point(61, 16);
			this->groupBox37->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox37->Name = L"groupBox37";
			this->groupBox37->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox37->Size = System::Drawing::Size(20, 1);
			this->groupBox37->TabIndex = 98;
			this->groupBox37->TabStop = false;
			this->groupBox37->Text = L"groupBox37";
			// 
			// groupBox38
			// 
			this->groupBox38->BackColor = System::Drawing::Color::White;
			this->groupBox38->Location = System::Drawing::Point(61, 48);
			this->groupBox38->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox38->Name = L"groupBox38";
			this->groupBox38->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox38->Size = System::Drawing::Size(20, 1);
			this->groupBox38->TabIndex = 97;
			this->groupBox38->TabStop = false;
			this->groupBox38->Text = L"groupBox38";
			// 
			// Velocity11
			// 
			this->Velocity11->AutoSize = true;
			this->Velocity11->ForeColor = System::Drawing::Color::White;
			this->Velocity11->Location = System::Drawing::Point(32, 42);
			this->Velocity11->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity11->Name = L"Velocity11";
			this->Velocity11->Size = System::Drawing::Size(10, 13);
			this->Velocity11->TabIndex = 96;
			this->Velocity11->Text = L"-";
			// 
			// groupBox39
			// 
			this->groupBox39->BackColor = System::Drawing::Color::White;
			this->groupBox39->Location = System::Drawing::Point(61, 79);
			this->groupBox39->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox39->Name = L"groupBox39";
			this->groupBox39->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox39->Size = System::Drawing::Size(20, 1);
			this->groupBox39->TabIndex = 95;
			this->groupBox39->TabStop = false;
			this->groupBox39->Text = L"groupBox39";
			// 
			// Velocity12
			// 
			this->Velocity12->AutoSize = true;
			this->Velocity12->ForeColor = System::Drawing::Color::White;
			this->Velocity12->Location = System::Drawing::Point(32, 74);
			this->Velocity12->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity12->Name = L"Velocity12";
			this->Velocity12->Size = System::Drawing::Size(10, 13);
			this->Velocity12->TabIndex = 94;
			this->Velocity12->Text = L"-";
			// 
			// groupBox40
			// 
			this->groupBox40->BackColor = System::Drawing::Color::White;
			this->groupBox40->Location = System::Drawing::Point(61, 113);
			this->groupBox40->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox40->Name = L"groupBox40";
			this->groupBox40->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox40->Size = System::Drawing::Size(20, 1);
			this->groupBox40->TabIndex = 93;
			this->groupBox40->TabStop = false;
			this->groupBox40->Text = L"groupBox40";
			// 
			// Velocity13
			// 
			this->Velocity13->AutoSize = true;
			this->Velocity13->ForeColor = System::Drawing::Color::White;
			this->Velocity13->Location = System::Drawing::Point(32, 105);
			this->Velocity13->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity13->Name = L"Velocity13";
			this->Velocity13->Size = System::Drawing::Size(10, 13);
			this->Velocity13->TabIndex = 92;
			this->Velocity13->Text = L"-";
			// 
			// groupBox41
			// 
			this->groupBox41->BackColor = System::Drawing::Color::White;
			this->groupBox41->Location = System::Drawing::Point(61, 270);
			this->groupBox41->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox41->Name = L"groupBox41";
			this->groupBox41->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox41->Size = System::Drawing::Size(20, 1);
			this->groupBox41->TabIndex = 91;
			this->groupBox41->TabStop = false;
			this->groupBox41->Text = L"groupBox41";
			// 
			// groupBox42
			// 
			this->groupBox42->BackColor = System::Drawing::Color::White;
			this->groupBox42->Location = System::Drawing::Point(61, 240);
			this->groupBox42->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox42->Name = L"groupBox42";
			this->groupBox42->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox42->Size = System::Drawing::Size(20, 1);
			this->groupBox42->TabIndex = 90;
			this->groupBox42->TabStop = false;
			this->groupBox42->Text = L"groupBox42";
			// 
			// Velocity16
			// 
			this->Velocity16->AutoSize = true;
			this->Velocity16->ForeColor = System::Drawing::Color::White;
			this->Velocity16->Location = System::Drawing::Point(32, 234);
			this->Velocity16->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity16->Name = L"Velocity16";
			this->Velocity16->Size = System::Drawing::Size(10, 13);
			this->Velocity16->TabIndex = 89;
			this->Velocity16->Text = L"-";
			// 
			// groupBox43
			// 
			this->groupBox43->BackColor = System::Drawing::Color::White;
			this->groupBox43->Location = System::Drawing::Point(61, 208);
			this->groupBox43->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox43->Name = L"groupBox43";
			this->groupBox43->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox43->Size = System::Drawing::Size(20, 1);
			this->groupBox43->TabIndex = 88;
			this->groupBox43->TabStop = false;
			this->groupBox43->Text = L"groupBox43";
			// 
			// Velocity15
			// 
			this->Velocity15->AutoSize = true;
			this->Velocity15->ForeColor = System::Drawing::Color::White;
			this->Velocity15->Location = System::Drawing::Point(32, 202);
			this->Velocity15->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity15->Name = L"Velocity15";
			this->Velocity15->Size = System::Drawing::Size(10, 13);
			this->Velocity15->TabIndex = 87;
			this->Velocity15->Text = L"-";
			// 
			// groupBox44
			// 
			this->groupBox44->BackColor = System::Drawing::Color::White;
			this->groupBox44->Location = System::Drawing::Point(61, 176);
			this->groupBox44->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox44->Name = L"groupBox44";
			this->groupBox44->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox44->Size = System::Drawing::Size(20, 1);
			this->groupBox44->TabIndex = 86;
			this->groupBox44->TabStop = false;
			this->groupBox44->Text = L"groupBox44";
			// 
			// Velocity14
			// 
			this->Velocity14->AutoSize = true;
			this->Velocity14->ForeColor = System::Drawing::Color::White;
			this->Velocity14->Location = System::Drawing::Point(32, 170);
			this->Velocity14->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity14->Name = L"Velocity14";
			this->Velocity14->Size = System::Drawing::Size(10, 13);
			this->Velocity14->TabIndex = 85;
			this->Velocity14->Text = L"-";
			// 
			// groupBox45
			// 
			this->groupBox45->BackColor = System::Drawing::Color::White;
			this->groupBox45->Location = System::Drawing::Point(61, 144);
			this->groupBox45->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox45->Name = L"groupBox45";
			this->groupBox45->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox45->Size = System::Drawing::Size(20, 1);
			this->groupBox45->TabIndex = 84;
			this->groupBox45->TabStop = false;
			this->groupBox45->Text = L"groupBox45";
			// 
			// groupBox28
			// 
			this->groupBox28->BackColor = System::Drawing::Color::White;
			this->groupBox28->Location = System::Drawing::Point(458, 311);
			this->groupBox28->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox28->Name = L"groupBox28";
			this->groupBox28->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox28->Size = System::Drawing::Size(20, 1);
			this->groupBox28->TabIndex = 83;
			this->groupBox28->TabStop = false;
			this->groupBox28->Text = L"groupBox28";
			// 
			// groupBox29
			// 
			this->groupBox29->BackColor = System::Drawing::Color::White;
			this->groupBox29->Location = System::Drawing::Point(458, 342);
			this->groupBox29->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox29->Name = L"groupBox29";
			this->groupBox29->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox29->Size = System::Drawing::Size(20, 1);
			this->groupBox29->TabIndex = 82;
			this->groupBox29->TabStop = false;
			this->groupBox29->Text = L"groupBox29";
			// 
			// Velocity41
			// 
			this->Velocity41->AutoSize = true;
			this->Velocity41->ForeColor = System::Drawing::Color::White;
			this->Velocity41->Location = System::Drawing::Point(430, 337);
			this->Velocity41->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity41->Name = L"Velocity41";
			this->Velocity41->Size = System::Drawing::Size(10, 13);
			this->Velocity41->TabIndex = 81;
			this->Velocity41->Text = L"-";
			// 
			// groupBox30
			// 
			this->groupBox30->BackColor = System::Drawing::Color::White;
			this->groupBox30->Location = System::Drawing::Point(458, 374);
			this->groupBox30->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox30->Name = L"groupBox30";
			this->groupBox30->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox30->Size = System::Drawing::Size(20, 1);
			this->groupBox30->TabIndex = 80;
			this->groupBox30->TabStop = false;
			this->groupBox30->Text = L"groupBox30";
			// 
			// Velocity42
			// 
			this->Velocity42->AutoSize = true;
			this->Velocity42->ForeColor = System::Drawing::Color::White;
			this->Velocity42->Location = System::Drawing::Point(430, 368);
			this->Velocity42->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity42->Name = L"Velocity42";
			this->Velocity42->Size = System::Drawing::Size(10, 13);
			this->Velocity42->TabIndex = 79;
			this->Velocity42->Text = L"-";
			// 
			// groupBox31
			// 
			this->groupBox31->BackColor = System::Drawing::Color::White;
			this->groupBox31->Location = System::Drawing::Point(458, 406);
			this->groupBox31->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox31->Name = L"groupBox31";
			this->groupBox31->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox31->Size = System::Drawing::Size(20, 1);
			this->groupBox31->TabIndex = 78;
			this->groupBox31->TabStop = false;
			this->groupBox31->Text = L"groupBox31";
			// 
			// Velocity43
			// 
			this->Velocity43->AutoSize = true;
			this->Velocity43->ForeColor = System::Drawing::Color::White;
			this->Velocity43->Location = System::Drawing::Point(430, 400);
			this->Velocity43->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity43->Name = L"Velocity43";
			this->Velocity43->Size = System::Drawing::Size(10, 13);
			this->Velocity43->TabIndex = 77;
			this->Velocity43->Text = L"-";
			// 
			// groupBox32
			// 
			this->groupBox32->BackColor = System::Drawing::Color::White;
			this->groupBox32->Location = System::Drawing::Point(458, 563);
			this->groupBox32->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox32->Name = L"groupBox32";
			this->groupBox32->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox32->Size = System::Drawing::Size(20, 1);
			this->groupBox32->TabIndex = 76;
			this->groupBox32->TabStop = false;
			this->groupBox32->Text = L"groupBox32";
			// 
			// groupBox33
			// 
			this->groupBox33->BackColor = System::Drawing::Color::White;
			this->groupBox33->Location = System::Drawing::Point(458, 534);
			this->groupBox33->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox33->Name = L"groupBox33";
			this->groupBox33->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox33->Size = System::Drawing::Size(20, 1);
			this->groupBox33->TabIndex = 75;
			this->groupBox33->TabStop = false;
			this->groupBox33->Text = L"groupBox33";
			// 
			// Velocity46
			// 
			this->Velocity46->AutoSize = true;
			this->Velocity46->ForeColor = System::Drawing::Color::White;
			this->Velocity46->Location = System::Drawing::Point(430, 529);
			this->Velocity46->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity46->Name = L"Velocity46";
			this->Velocity46->Size = System::Drawing::Size(10, 13);
			this->Velocity46->TabIndex = 74;
			this->Velocity46->Text = L"-";
			// 
			// groupBox34
			// 
			this->groupBox34->BackColor = System::Drawing::Color::White;
			this->groupBox34->Location = System::Drawing::Point(458, 503);
			this->groupBox34->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox34->Name = L"groupBox34";
			this->groupBox34->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox34->Size = System::Drawing::Size(20, 1);
			this->groupBox34->TabIndex = 73;
			this->groupBox34->TabStop = false;
			this->groupBox34->Text = L"groupBox34";
			// 
			// Velocity45
			// 
			this->Velocity45->AutoSize = true;
			this->Velocity45->ForeColor = System::Drawing::Color::White;
			this->Velocity45->Location = System::Drawing::Point(430, 495);
			this->Velocity45->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity45->Name = L"Velocity45";
			this->Velocity45->Size = System::Drawing::Size(10, 13);
			this->Velocity45->TabIndex = 72;
			this->Velocity45->Text = L"-";
			// 
			// groupBox35
			// 
			this->groupBox35->BackColor = System::Drawing::Color::White;
			this->groupBox35->Location = System::Drawing::Point(458, 469);
			this->groupBox35->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox35->Name = L"groupBox35";
			this->groupBox35->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox35->Size = System::Drawing::Size(20, 1);
			this->groupBox35->TabIndex = 71;
			this->groupBox35->TabStop = false;
			this->groupBox35->Text = L"groupBox35";
			// 
			// Velocity44
			// 
			this->Velocity44->AutoSize = true;
			this->Velocity44->ForeColor = System::Drawing::Color::White;
			this->Velocity44->Location = System::Drawing::Point(430, 464);
			this->Velocity44->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity44->Name = L"Velocity44";
			this->Velocity44->Size = System::Drawing::Size(10, 13);
			this->Velocity44->TabIndex = 70;
			this->Velocity44->Text = L"-";
			// 
			// groupBox36
			// 
			this->groupBox36->BackColor = System::Drawing::Color::White;
			this->groupBox36->Location = System::Drawing::Point(458, 438);
			this->groupBox36->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox36->Name = L"groupBox36";
			this->groupBox36->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox36->Size = System::Drawing::Size(20, 1);
			this->groupBox36->TabIndex = 69;
			this->groupBox36->TabStop = false;
			this->groupBox36->Text = L"groupBox36";
			// 
			// groupBox27
			// 
			this->groupBox27->BackColor = System::Drawing::Color::White;
			this->groupBox27->Location = System::Drawing::Point(458, 16);
			this->groupBox27->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox27->Name = L"groupBox27";
			this->groupBox27->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox27->Size = System::Drawing::Size(20, 1);
			this->groupBox27->TabIndex = 68;
			this->groupBox27->TabStop = false;
			this->groupBox27->Text = L"groupBox27";
			// 
			// groupBox26
			// 
			this->groupBox26->BackColor = System::Drawing::Color::White;
			this->groupBox26->Location = System::Drawing::Point(458, 48);
			this->groupBox26->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox26->Name = L"groupBox26";
			this->groupBox26->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox26->Size = System::Drawing::Size(20, 1);
			this->groupBox26->TabIndex = 66;
			this->groupBox26->TabStop = false;
			this->groupBox26->Text = L"groupBox26";
			// 
			// Velocity21
			// 
			this->Velocity21->AutoSize = true;
			this->Velocity21->ForeColor = System::Drawing::Color::White;
			this->Velocity21->Location = System::Drawing::Point(430, 42);
			this->Velocity21->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity21->Name = L"Velocity21";
			this->Velocity21->Size = System::Drawing::Size(10, 13);
			this->Velocity21->TabIndex = 65;
			this->Velocity21->Text = L"-";
			// 
			// groupBox25
			// 
			this->groupBox25->BackColor = System::Drawing::Color::White;
			this->groupBox25->Location = System::Drawing::Point(458, 79);
			this->groupBox25->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox25->Name = L"groupBox25";
			this->groupBox25->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox25->Size = System::Drawing::Size(20, 1);
			this->groupBox25->TabIndex = 64;
			this->groupBox25->TabStop = false;
			this->groupBox25->Text = L"groupBox25";
			// 
			// Velocity22
			// 
			this->Velocity22->AutoSize = true;
			this->Velocity22->ForeColor = System::Drawing::Color::White;
			this->Velocity22->Location = System::Drawing::Point(430, 74);
			this->Velocity22->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity22->Name = L"Velocity22";
			this->Velocity22->Size = System::Drawing::Size(10, 13);
			this->Velocity22->TabIndex = 63;
			this->Velocity22->Text = L"-";
			// 
			// groupBox24
			// 
			this->groupBox24->BackColor = System::Drawing::Color::White;
			this->groupBox24->Location = System::Drawing::Point(458, 113);
			this->groupBox24->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox24->Name = L"groupBox24";
			this->groupBox24->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox24->Size = System::Drawing::Size(20, 1);
			this->groupBox24->TabIndex = 62;
			this->groupBox24->TabStop = false;
			this->groupBox24->Text = L"groupBox24";
			// 
			// Velocity23
			// 
			this->Velocity23->AutoSize = true;
			this->Velocity23->ForeColor = System::Drawing::Color::White;
			this->Velocity23->Location = System::Drawing::Point(430, 105);
			this->Velocity23->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity23->Name = L"Velocity23";
			this->Velocity23->Size = System::Drawing::Size(10, 13);
			this->Velocity23->TabIndex = 61;
			this->Velocity23->Text = L"-";
			// 
			// groupBox23
			// 
			this->groupBox23->BackColor = System::Drawing::Color::White;
			this->groupBox23->Location = System::Drawing::Point(458, 270);
			this->groupBox23->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox23->Name = L"groupBox23";
			this->groupBox23->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox23->Size = System::Drawing::Size(20, 1);
			this->groupBox23->TabIndex = 60;
			this->groupBox23->TabStop = false;
			this->groupBox23->Text = L"groupBox23";
			// 
			// groupBox22
			// 
			this->groupBox22->BackColor = System::Drawing::Color::White;
			this->groupBox22->Location = System::Drawing::Point(458, 240);
			this->groupBox22->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox22->Name = L"groupBox22";
			this->groupBox22->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox22->Size = System::Drawing::Size(20, 1);
			this->groupBox22->TabIndex = 58;
			this->groupBox22->TabStop = false;
			this->groupBox22->Text = L"groupBox22";
			// 
			// Velocity26
			// 
			this->Velocity26->AutoSize = true;
			this->Velocity26->ForeColor = System::Drawing::Color::White;
			this->Velocity26->Location = System::Drawing::Point(430, 234);
			this->Velocity26->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity26->Name = L"Velocity26";
			this->Velocity26->Size = System::Drawing::Size(10, 13);
			this->Velocity26->TabIndex = 57;
			this->Velocity26->Text = L"-";
			// 
			// groupBox21
			// 
			this->groupBox21->BackColor = System::Drawing::Color::White;
			this->groupBox21->Location = System::Drawing::Point(458, 208);
			this->groupBox21->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox21->Name = L"groupBox21";
			this->groupBox21->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox21->Size = System::Drawing::Size(20, 1);
			this->groupBox21->TabIndex = 56;
			this->groupBox21->TabStop = false;
			this->groupBox21->Text = L"groupBox21";
			// 
			// Velocity25
			// 
			this->Velocity25->AutoSize = true;
			this->Velocity25->ForeColor = System::Drawing::Color::White;
			this->Velocity25->Location = System::Drawing::Point(430, 202);
			this->Velocity25->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity25->Name = L"Velocity25";
			this->Velocity25->Size = System::Drawing::Size(10, 13);
			this->Velocity25->TabIndex = 55;
			this->Velocity25->Text = L"-";
			// 
			// groupBox20
			// 
			this->groupBox20->BackColor = System::Drawing::Color::White;
			this->groupBox20->Location = System::Drawing::Point(458, 176);
			this->groupBox20->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox20->Name = L"groupBox20";
			this->groupBox20->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox20->Size = System::Drawing::Size(20, 1);
			this->groupBox20->TabIndex = 54;
			this->groupBox20->TabStop = false;
			this->groupBox20->Text = L"groupBox20";
			// 
			// Velocity24
			// 
			this->Velocity24->AutoSize = true;
			this->Velocity24->ForeColor = System::Drawing::Color::White;
			this->Velocity24->Location = System::Drawing::Point(430, 170);
			this->Velocity24->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity24->Name = L"Velocity24";
			this->Velocity24->Size = System::Drawing::Size(10, 13);
			this->Velocity24->TabIndex = 53;
			this->Velocity24->Text = L"-";
			// 
			// groupBox19
			// 
			this->groupBox19->BackColor = System::Drawing::Color::White;
			this->groupBox19->Location = System::Drawing::Point(458, 144);
			this->groupBox19->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox19->Name = L"groupBox19";
			this->groupBox19->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox19->Size = System::Drawing::Size(20, 1);
			this->groupBox19->TabIndex = 52;
			this->groupBox19->TabStop = false;
			this->groupBox19->Text = L"groupBox19";
			// 
			// groupBox18
			// 
			this->groupBox18->BackColor = System::Drawing::Color::White;
			this->groupBox18->Location = System::Drawing::Point(786, 260);
			this->groupBox18->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox18->Name = L"groupBox18";
			this->groupBox18->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox18->Size = System::Drawing::Size(2, 20);
			this->groupBox18->TabIndex = 51;
			this->groupBox18->TabStop = false;
			this->groupBox18->Text = L"groupBox18";
			// 
			// groupBox17
			// 
			this->groupBox17->BackColor = System::Drawing::Color::White;
			this->groupBox17->Location = System::Drawing::Point(748, 260);
			this->groupBox17->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox17->Name = L"groupBox17";
			this->groupBox17->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox17->Size = System::Drawing::Size(2, 20);
			this->groupBox17->TabIndex = 49;
			this->groupBox17->TabStop = false;
			this->groupBox17->Text = L"groupBox17";
			// 
			// Range27
			// 
			this->Range27->AutoSize = true;
			this->Range27->ForeColor = System::Drawing::Color::White;
			this->Range27->Location = System::Drawing::Point(740, 277);
			this->Range27->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range27->Name = L"Range27";
			this->Range27->Size = System::Drawing::Size(10, 13);
			this->Range27->TabIndex = 50;
			this->Range27->Text = L"-";
			// 
			// groupBox16
			// 
			this->groupBox16->BackColor = System::Drawing::Color::White;
			this->groupBox16->Location = System::Drawing::Point(708, 260);
			this->groupBox16->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox16->Name = L"groupBox16";
			this->groupBox16->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox16->Size = System::Drawing::Size(2, 20);
			this->groupBox16->TabIndex = 47;
			this->groupBox16->TabStop = false;
			this->groupBox16->Text = L"groupBox16";
			// 
			// Range26
			// 
			this->Range26->AutoSize = true;
			this->Range26->ForeColor = System::Drawing::Color::White;
			this->Range26->Location = System::Drawing::Point(698, 277);
			this->Range26->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range26->Name = L"Range26";
			this->Range26->Size = System::Drawing::Size(10, 13);
			this->Range26->TabIndex = 48;
			this->Range26->Text = L"-";
			// 
			// groupBox15
			// 
			this->groupBox15->BackColor = System::Drawing::Color::White;
			this->groupBox15->Location = System::Drawing::Point(668, 260);
			this->groupBox15->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox15->Name = L"groupBox15";
			this->groupBox15->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox15->Size = System::Drawing::Size(2, 20);
			this->groupBox15->TabIndex = 45;
			this->groupBox15->TabStop = false;
			this->groupBox15->Text = L"groupBox15";
			// 
			// Range25
			// 
			this->Range25->AutoSize = true;
			this->Range25->ForeColor = System::Drawing::Color::White;
			this->Range25->Location = System::Drawing::Point(659, 277);
			this->Range25->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range25->Name = L"Range25";
			this->Range25->Size = System::Drawing::Size(10, 13);
			this->Range25->TabIndex = 46;
			this->Range25->Text = L"-";
			// 
			// groupBox14
			// 
			this->groupBox14->BackColor = System::Drawing::Color::White;
			this->groupBox14->Location = System::Drawing::Point(628, 260);
			this->groupBox14->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox14->Name = L"groupBox14";
			this->groupBox14->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox14->Size = System::Drawing::Size(2, 20);
			this->groupBox14->TabIndex = 43;
			this->groupBox14->TabStop = false;
			this->groupBox14->Text = L"groupBox14";
			// 
			// Range24
			// 
			this->Range24->AutoSize = true;
			this->Range24->ForeColor = System::Drawing::Color::White;
			this->Range24->Location = System::Drawing::Point(619, 277);
			this->Range24->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range24->Name = L"Range24";
			this->Range24->Size = System::Drawing::Size(10, 13);
			this->Range24->TabIndex = 44;
			this->Range24->Text = L"-";
			// 
			// groupBox13
			// 
			this->groupBox13->BackColor = System::Drawing::Color::White;
			this->groupBox13->Location = System::Drawing::Point(588, 260);
			this->groupBox13->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox13->Name = L"groupBox13";
			this->groupBox13->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox13->Size = System::Drawing::Size(2, 20);
			this->groupBox13->TabIndex = 41;
			this->groupBox13->TabStop = false;
			this->groupBox13->Text = L"groupBox13";
			// 
			// Range23
			// 
			this->Range23->AutoSize = true;
			this->Range23->ForeColor = System::Drawing::Color::White;
			this->Range23->Location = System::Drawing::Point(578, 277);
			this->Range23->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range23->Name = L"Range23";
			this->Range23->Size = System::Drawing::Size(10, 13);
			this->Range23->TabIndex = 42;
			this->Range23->Text = L"-";
			// 
			// groupBox12
			// 
			this->groupBox12->BackColor = System::Drawing::Color::White;
			this->groupBox12->Location = System::Drawing::Point(548, 260);
			this->groupBox12->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox12->Size = System::Drawing::Size(2, 20);
			this->groupBox12->TabIndex = 39;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"groupBox12";
			// 
			// Range22
			// 
			this->Range22->AutoSize = true;
			this->Range22->ForeColor = System::Drawing::Color::White;
			this->Range22->Location = System::Drawing::Point(540, 277);
			this->Range22->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range22->Name = L"Range22";
			this->Range22->Size = System::Drawing::Size(10, 13);
			this->Range22->TabIndex = 40;
			this->Range22->Text = L"-";
			// 
			// groupBox8
			// 
			this->groupBox8->BackColor = System::Drawing::Color::White;
			this->groupBox8->Location = System::Drawing::Point(508, 260);
			this->groupBox8->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox8->Size = System::Drawing::Size(2, 20);
			this->groupBox8->TabIndex = 38;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"groupBox8";
			// 
			// Range21
			// 
			this->Range21->AutoSize = true;
			this->Range21->ForeColor = System::Drawing::Color::White;
			this->Range21->Location = System::Drawing::Point(499, 277);
			this->Range21->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range21->Name = L"Range21";
			this->Range21->Size = System::Drawing::Size(10, 13);
			this->Range21->TabIndex = 37;
			this->Range21->Text = L"-";
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::White;
			this->groupBox4->Location = System::Drawing::Point(468, 260);
			this->groupBox4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox4->Size = System::Drawing::Size(2, 20);
			this->groupBox4->TabIndex = 36;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"groupBox4";
			// 
			// label209
			// 
			this->label209->AutoSize = true;
			this->label209->ForeColor = System::Drawing::Color::White;
			this->label209->Location = System::Drawing::Point(410, 573);
			this->label209->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label209->Name = L"label209";
			this->label209->Size = System::Drawing::Size(21, 13);
			this->label209->TabIndex = 35;
			this->label209->Text = L"[m]";
			// 
			// label208
			// 
			this->label208->AutoSize = true;
			this->label208->ForeColor = System::Drawing::Color::White;
			this->label208->Location = System::Drawing::Point(808, 573);
			this->label208->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label208->Name = L"label208";
			this->label208->Size = System::Drawing::Size(21, 13);
			this->label208->TabIndex = 34;
			this->label208->Text = L"[m]";
			// 
			// label207
			// 
			this->label207->AutoSize = true;
			this->label207->ForeColor = System::Drawing::Color::White;
			this->label207->Location = System::Drawing::Point(410, 279);
			this->label207->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label207->Name = L"label207";
			this->label207->Size = System::Drawing::Size(21, 13);
			this->label207->TabIndex = 33;
			this->label207->Text = L"[m]";
			// 
			// label206
			// 
			this->label206->AutoSize = true;
			this->label206->ForeColor = System::Drawing::Color::White;
			this->label206->Location = System::Drawing::Point(808, 279);
			this->label206->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label206->Name = L"label206";
			this->label206->Size = System::Drawing::Size(21, 13);
			this->label206->TabIndex = 32;
			this->label206->Text = L"[m]";
			// 
			// Velocity_min_3
			// 
			this->Velocity_min_3->AutoSize = true;
			this->Velocity_min_3->ForeColor = System::Drawing::Color::White;
			this->Velocity_min_3->Location = System::Drawing::Point(32, 558);
			this->Velocity_min_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity_min_3->Name = L"Velocity_min_3";
			this->Velocity_min_3->Size = System::Drawing::Size(23, 13);
			this->Velocity_min_3->TabIndex = 31;
			this->Velocity_min_3->Text = L"min";
			// 
			// Velocity_min_1
			// 
			this->Velocity_min_1->AutoSize = true;
			this->Velocity_min_1->ForeColor = System::Drawing::Color::White;
			this->Velocity_min_1->Location = System::Drawing::Point(32, 266);
			this->Velocity_min_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity_min_1->Name = L"Velocity_min_1";
			this->Velocity_min_1->Size = System::Drawing::Size(23, 13);
			this->Velocity_min_1->TabIndex = 30;
			this->Velocity_min_1->Text = L"min";
			// 
			// Velocity_min_2
			// 
			this->Velocity_min_2->AutoSize = true;
			this->Velocity_min_2->ForeColor = System::Drawing::Color::White;
			this->Velocity_min_2->Location = System::Drawing::Point(430, 266);
			this->Velocity_min_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity_min_2->Name = L"Velocity_min_2";
			this->Velocity_min_2->Size = System::Drawing::Size(23, 13);
			this->Velocity_min_2->TabIndex = 29;
			this->Velocity_min_2->Text = L"min";
			// 
			// Velocity_min_4
			// 
			this->Velocity_min_4->AutoSize = true;
			this->Velocity_min_4->ForeColor = System::Drawing::Color::White;
			this->Velocity_min_4->Location = System::Drawing::Point(430, 558);
			this->Velocity_min_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity_min_4->Name = L"Velocity_min_4";
			this->Velocity_min_4->Size = System::Drawing::Size(23, 13);
			this->Velocity_min_4->TabIndex = 28;
			this->Velocity_min_4->Text = L"min";
			// 
			// Velocity_max_3
			// 
			this->Velocity_max_3->AutoSize = true;
			this->Velocity_max_3->ForeColor = System::Drawing::Color::White;
			this->Velocity_max_3->Location = System::Drawing::Point(32, 303);
			this->Velocity_max_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity_max_3->Name = L"Velocity_max_3";
			this->Velocity_max_3->Size = System::Drawing::Size(26, 13);
			this->Velocity_max_3->TabIndex = 27;
			this->Velocity_max_3->Text = L"max";
			// 
			// Velocity_max_4
			// 
			this->Velocity_max_4->AutoSize = true;
			this->Velocity_max_4->ForeColor = System::Drawing::Color::White;
			this->Velocity_max_4->Location = System::Drawing::Point(430, 303);
			this->Velocity_max_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity_max_4->Name = L"Velocity_max_4";
			this->Velocity_max_4->Size = System::Drawing::Size(26, 13);
			this->Velocity_max_4->TabIndex = 26;
			this->Velocity_max_4->Text = L"max";
			// 
			// Velocity_max_2
			// 
			this->Velocity_max_2->AutoSize = true;
			this->Velocity_max_2->ForeColor = System::Drawing::Color::White;
			this->Velocity_max_2->Location = System::Drawing::Point(430, 10);
			this->Velocity_max_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity_max_2->Name = L"Velocity_max_2";
			this->Velocity_max_2->Size = System::Drawing::Size(26, 13);
			this->Velocity_max_2->TabIndex = 25;
			this->Velocity_max_2->Text = L"max";
			// 
			// Velocity_max_1
			// 
			this->Velocity_max_1->AutoSize = true;
			this->Velocity_max_1->ForeColor = System::Drawing::Color::White;
			this->Velocity_max_1->Location = System::Drawing::Point(32, 10);
			this->Velocity_max_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Velocity_max_1->Name = L"Velocity_max_1";
			this->Velocity_max_1->Size = System::Drawing::Size(26, 13);
			this->Velocity_max_1->TabIndex = 24;
			this->Velocity_max_1->Text = L"max";
			// 
			// Range_max_4
			// 
			this->Range_max_4->AutoSize = true;
			this->Range_max_4->ForeColor = System::Drawing::Color::White;
			this->Range_max_4->Location = System::Drawing::Point(775, 573);
			this->Range_max_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range_max_4->Name = L"Range_max_4";
			this->Range_max_4->Size = System::Drawing::Size(26, 13);
			this->Range_max_4->TabIndex = 23;
			this->Range_max_4->Text = L"max";
			// 
			// Range_max_3
			// 
			this->Range_max_3->AutoSize = true;
			this->Range_max_3->ForeColor = System::Drawing::Color::White;
			this->Range_max_3->Location = System::Drawing::Point(378, 573);
			this->Range_max_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range_max_3->Name = L"Range_max_3";
			this->Range_max_3->Size = System::Drawing::Size(26, 13);
			this->Range_max_3->TabIndex = 22;
			this->Range_max_3->Text = L"max";
			// 
			// Range_max_2
			// 
			this->Range_max_2->AutoSize = true;
			this->Range_max_2->ForeColor = System::Drawing::Color::White;
			this->Range_max_2->Location = System::Drawing::Point(776, 277);
			this->Range_max_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range_max_2->Name = L"Range_max_2";
			this->Range_max_2->Size = System::Drawing::Size(26, 13);
			this->Range_max_2->TabIndex = 21;
			this->Range_max_2->Text = L"max";
			// 
			// Range_max_1
			// 
			this->Range_max_1->AutoSize = true;
			this->Range_max_1->ForeColor = System::Drawing::Color::White;
			this->Range_max_1->Location = System::Drawing::Point(378, 279);
			this->Range_max_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Range_max_1->Name = L"Range_max_1";
			this->Range_max_1->Size = System::Drawing::Size(26, 13);
			this->Range_max_1->TabIndex = 20;
			this->Range_max_1->Text = L"max";
			// 
			// label205
			// 
			this->label205->AutoSize = true;
			this->label205->ForeColor = System::Drawing::Color::White;
			this->label205->Location = System::Drawing::Point(455, 573);
			this->label205->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label205->Name = L"label205";
			this->label205->Size = System::Drawing::Size(27, 13);
			this->label205->TabIndex = 19;
			this->label205->Text = L"R=0";
			// 
			// label204
			// 
			this->label204->AutoSize = true;
			this->label204->ForeColor = System::Drawing::Color::White;
			this->label204->Location = System::Drawing::Point(456, 277);
			this->label204->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label204->Name = L"label204";
			this->label204->Size = System::Drawing::Size(27, 13);
			this->label204->TabIndex = 18;
			this->label204->Text = L"R=0";
			// 
			// label203
			// 
			this->label203->AutoSize = true;
			this->label203->ForeColor = System::Drawing::Color::White;
			this->label203->Location = System::Drawing::Point(58, 572);
			this->label203->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label203->Name = L"label203";
			this->label203->Size = System::Drawing::Size(27, 13);
			this->label203->TabIndex = 17;
			this->label203->Text = L"R=0";
			// 
			// label202
			// 
			this->label202->AutoSize = true;
			this->label202->ForeColor = System::Drawing::Color::White;
			this->label202->Location = System::Drawing::Point(59, 279);
			this->label202->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label202->Name = L"label202";
			this->label202->Size = System::Drawing::Size(27, 13);
			this->label202->TabIndex = 16;
			this->label202->Text = L"R=0";
			// 
			// label201
			// 
			this->label201->AutoSize = true;
			this->label201->ForeColor = System::Drawing::Color::White;
			this->label201->Location = System::Drawing::Point(430, 433);
			this->label201->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label201->Name = L"label201";
			this->label201->Size = System::Drawing::Size(26, 13);
			this->label201->TabIndex = 15;
			this->label201->Text = L"V=0";
			// 
			// label200
			// 
			this->label200->AutoSize = true;
			this->label200->ForeColor = System::Drawing::Color::White;
			this->label200->Location = System::Drawing::Point(430, 139);
			this->label200->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label200->Name = L"label200";
			this->label200->Size = System::Drawing::Size(26, 13);
			this->label200->TabIndex = 14;
			this->label200->Text = L"V=0";
			// 
			// label199
			// 
			this->label199->AutoSize = true;
			this->label199->ForeColor = System::Drawing::Color::White;
			this->label199->Location = System::Drawing::Point(32, 139);
			this->label199->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label199->Name = L"label199";
			this->label199->Size = System::Drawing::Size(26, 13);
			this->label199->TabIndex = 13;
			this->label199->Text = L"V=0";
			// 
			// label198
			// 
			this->label198->AutoSize = true;
			this->label198->ForeColor = System::Drawing::Color::White;
			this->label198->Location = System::Drawing::Point(32, 433);
			this->label198->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label198->Name = L"label198";
			this->label198->Size = System::Drawing::Size(26, 13);
			this->label198->TabIndex = 12;
			this->label198->Text = L"V=0";
			// 
			// label197
			// 
			this->label197->AutoSize = true;
			this->label197->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label197->ForeColor = System::Drawing::Color::White;
			this->label197->Location = System::Drawing::Point(599, 0);
			this->label197->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label197->Name = L"label197";
			this->label197->Size = System::Drawing::Size(43, 13);
			this->label197->TabIndex = 11;
			this->label197->Text = L"Right H";
			// 
			// label196
			// 
			this->label196->AutoSize = true;
			this->label196->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label196->ForeColor = System::Drawing::Color::White;
			this->label196->Location = System::Drawing::Point(599, 295);
			this->label196->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label196->Name = L"label196";
			this->label196->Size = System::Drawing::Size(42, 13);
			this->label196->TabIndex = 10;
			this->label196->Text = L"Right V";
			// 
			// label195
			// 
			this->label195->AutoSize = true;
			this->label195->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label195->ForeColor = System::Drawing::Color::White;
			this->label195->Location = System::Drawing::Point(197, 295);
			this->label195->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label195->Name = L"label195";
			this->label195->Size = System::Drawing::Size(35, 13);
			this->label195->TabIndex = 9;
			this->label195->Text = L"Left V";
			// 
			// label194
			// 
			this->label194->AutoSize = true;
			this->label194->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label194->ForeColor = System::Drawing::Color::White;
			this->label194->Location = System::Drawing::Point(197, 0);
			this->label194->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label194->Name = L"label194";
			this->label194->Size = System::Drawing::Size(36, 13);
			this->label194->TabIndex = 8;
			this->label194->Text = L"Left H";
			// 
			// B_RDM_V_R
			// 
			this->B_RDM_V_R->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_RDM_V_R->Location = System::Drawing::Point(467, 311);
			this->B_RDM_V_R->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RDM_V_R->Name = L"B_RDM_V_R";
			this->B_RDM_V_R->Size = System::Drawing::Size(320, 255);
			this->B_RDM_V_R->TabIndex = 7;
			this->B_RDM_V_R->TabStop = false;
			this->B_RDM_V_R->Click += gcnew System::EventHandler(this, &MyForm::B_RDM_V_R_MouseClick);
			// 
			// B_RDM_V_L
			// 
			this->B_RDM_V_L->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_RDM_V_L->Location = System::Drawing::Point(71, 311);
			this->B_RDM_V_L->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RDM_V_L->Name = L"B_RDM_V_L";
			this->B_RDM_V_L->Size = System::Drawing::Size(320, 255);
			this->B_RDM_V_L->TabIndex = 6;
			this->B_RDM_V_L->TabStop = false;
			this->B_RDM_V_L->Click += gcnew System::EventHandler(this, &MyForm::B_RDM_V_L_MouseClick);
			// 
			// B_RDM_H_R
			// 
			this->B_RDM_H_R->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_RDM_H_R->Location = System::Drawing::Point(468, 16);
			this->B_RDM_H_R->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RDM_H_R->Name = L"B_RDM_H_R";
			this->B_RDM_H_R->Size = System::Drawing::Size(320, 255);
			this->B_RDM_H_R->TabIndex = 5;
			this->B_RDM_H_R->TabStop = false;
			this->B_RDM_H_R->Click += gcnew System::EventHandler(this, &MyForm::B_RDM_H_R_MouseClick);
			// 
			// B_RDM_H_L
			// 
			this->B_RDM_H_L->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_RDM_H_L->Location = System::Drawing::Point(71, 16);
			this->B_RDM_H_L->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RDM_H_L->Name = L"B_RDM_H_L";
			this->B_RDM_H_L->Size = System::Drawing::Size(320, 255);
			this->B_RDM_H_L->TabIndex = 4;
			this->B_RDM_H_L->TabStop = false;
			this->B_RDM_H_L->Click += gcnew System::EventHandler(this, &MyForm::B_RDM_H_L_MouseClick);
			// 
			// label213
			// 
			this->label213->AutoSize = true;
			this->label213->ForeColor = System::Drawing::Color::White;
			this->label213->Location = System::Drawing::Point(410, 130);
			this->label213->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label213->Name = L"label213";
			this->label213->Size = System::Drawing::Size(15, 13);
			this->label213->TabIndex = 168;
			this->label213->Text = L"m";
			// 
			// groupBox82
			// 
			this->groupBox82->BackColor = System::Drawing::Color::White;
			this->groupBox82->Location = System::Drawing::Point(413, 143);
			this->groupBox82->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox82->Name = L"groupBox82";
			this->groupBox82->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox82->Size = System::Drawing::Size(10, 1);
			this->groupBox82->TabIndex = 169;
			this->groupBox82->TabStop = false;
			this->groupBox82->Text = L"groupBox82";
			// 
			// label214
			// 
			this->label214->AutoSize = true;
			this->label214->ForeColor = System::Drawing::Color::White;
			this->label214->Location = System::Drawing::Point(412, 143);
			this->label214->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label214->Name = L"label214";
			this->label214->Size = System::Drawing::Size(12, 13);
			this->label214->TabIndex = 170;
			this->label214->Text = L"s";
			// 
			// label212
			// 
			this->label212->AutoSize = true;
			this->label212->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label212->ForeColor = System::Drawing::Color::White;
			this->label212->Location = System::Drawing::Point(398, 126);
			this->label212->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label212->Name = L"label212";
			this->label212->Size = System::Drawing::Size(22, 31);
			this->label212->TabIndex = 167;
			this->label212->Text = L"[";
			// 
			// label215
			// 
			this->label215->AutoSize = true;
			this->label215->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label215->ForeColor = System::Drawing::Color::White;
			this->label215->Location = System::Drawing::Point(418, 126);
			this->label215->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label215->Name = L"label215";
			this->label215->Size = System::Drawing::Size(22, 31);
			this->label215->TabIndex = 171;
			this->label215->Text = L"]";
			// 
			// label216
			// 
			this->label216->AutoSize = true;
			this->label216->ForeColor = System::Drawing::Color::White;
			this->label216->Location = System::Drawing::Point(410, 425);
			this->label216->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label216->Name = L"label216";
			this->label216->Size = System::Drawing::Size(15, 13);
			this->label216->TabIndex = 173;
			this->label216->Text = L"m";
			// 
			// groupBox83
			// 
			this->groupBox83->BackColor = System::Drawing::Color::White;
			this->groupBox83->Location = System::Drawing::Point(413, 438);
			this->groupBox83->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox83->Name = L"groupBox83";
			this->groupBox83->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox83->Size = System::Drawing::Size(10, 1);
			this->groupBox83->TabIndex = 174;
			this->groupBox83->TabStop = false;
			this->groupBox83->Text = L"groupBox83";
			// 
			// label217
			// 
			this->label217->AutoSize = true;
			this->label217->ForeColor = System::Drawing::Color::White;
			this->label217->Location = System::Drawing::Point(412, 438);
			this->label217->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label217->Name = L"label217";
			this->label217->Size = System::Drawing::Size(12, 13);
			this->label217->TabIndex = 175;
			this->label217->Text = L"s";
			// 
			// label218
			// 
			this->label218->AutoSize = true;
			this->label218->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label218->ForeColor = System::Drawing::Color::White;
			this->label218->Location = System::Drawing::Point(398, 420);
			this->label218->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label218->Name = L"label218";
			this->label218->Size = System::Drawing::Size(22, 31);
			this->label218->TabIndex = 172;
			this->label218->Text = L"[";
			// 
			// label219
			// 
			this->label219->AutoSize = true;
			this->label219->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label219->ForeColor = System::Drawing::Color::White;
			this->label219->Location = System::Drawing::Point(418, 420);
			this->label219->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label219->Name = L"label219";
			this->label219->Size = System::Drawing::Size(22, 31);
			this->label219->TabIndex = 176;
			this->label219->Text = L"]";
			// 
			// label220
			// 
			this->label220->AutoSize = true;
			this->label220->ForeColor = System::Drawing::Color::White;
			this->label220->Location = System::Drawing::Point(14, 129);
			this->label220->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label220->Name = L"label220";
			this->label220->Size = System::Drawing::Size(15, 13);
			this->label220->TabIndex = 178;
			this->label220->Text = L"m";
			// 
			// groupBox84
			// 
			this->groupBox84->BackColor = System::Drawing::Color::White;
			this->groupBox84->Location = System::Drawing::Point(16, 142);
			this->groupBox84->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox84->Name = L"groupBox84";
			this->groupBox84->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox84->Size = System::Drawing::Size(10, 1);
			this->groupBox84->TabIndex = 179;
			this->groupBox84->TabStop = false;
			this->groupBox84->Text = L"groupBox84";
			// 
			// label221
			// 
			this->label221->AutoSize = true;
			this->label221->ForeColor = System::Drawing::Color::White;
			this->label221->Location = System::Drawing::Point(14, 142);
			this->label221->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label221->Name = L"label221";
			this->label221->Size = System::Drawing::Size(12, 13);
			this->label221->TabIndex = 180;
			this->label221->Text = L"s";
			// 
			// label222
			// 
			this->label222->AutoSize = true;
			this->label222->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label222->ForeColor = System::Drawing::Color::White;
			this->label222->Location = System::Drawing::Point(1, 126);
			this->label222->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label222->Name = L"label222";
			this->label222->Size = System::Drawing::Size(22, 31);
			this->label222->TabIndex = 177;
			this->label222->Text = L"[";
			// 
			// label223
			// 
			this->label223->AutoSize = true;
			this->label223->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label223->ForeColor = System::Drawing::Color::White;
			this->label223->Location = System::Drawing::Point(20, 126);
			this->label223->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label223->Name = L"label223";
			this->label223->Size = System::Drawing::Size(22, 31);
			this->label223->TabIndex = 181;
			this->label223->Text = L"]";
			// 
			// label224
			// 
			this->label224->AutoSize = true;
			this->label224->ForeColor = System::Drawing::Color::White;
			this->label224->Location = System::Drawing::Point(14, 425);
			this->label224->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label224->Name = L"label224";
			this->label224->Size = System::Drawing::Size(15, 13);
			this->label224->TabIndex = 183;
			this->label224->Text = L"m";
			// 
			// groupBox85
			// 
			this->groupBox85->BackColor = System::Drawing::Color::White;
			this->groupBox85->Location = System::Drawing::Point(16, 438);
			this->groupBox85->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox85->Name = L"groupBox85";
			this->groupBox85->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox85->Size = System::Drawing::Size(10, 1);
			this->groupBox85->TabIndex = 184;
			this->groupBox85->TabStop = false;
			this->groupBox85->Text = L"groupBox85";
			// 
			// label225
			// 
			this->label225->AutoSize = true;
			this->label225->ForeColor = System::Drawing::Color::White;
			this->label225->Location = System::Drawing::Point(14, 438);
			this->label225->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label225->Name = L"label225";
			this->label225->Size = System::Drawing::Size(12, 13);
			this->label225->TabIndex = 185;
			this->label225->Text = L"s";
			// 
			// label226
			// 
			this->label226->AutoSize = true;
			this->label226->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label226->ForeColor = System::Drawing::Color::White;
			this->label226->Location = System::Drawing::Point(1, 420);
			this->label226->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label226->Name = L"label226";
			this->label226->Size = System::Drawing::Size(22, 31);
			this->label226->TabIndex = 182;
			this->label226->Text = L"[";
			// 
			// label227
			// 
			this->label227->AutoSize = true;
			this->label227->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label227->ForeColor = System::Drawing::Color::White;
			this->label227->Location = System::Drawing::Point(20, 420);
			this->label227->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label227->Name = L"label227";
			this->label227->Size = System::Drawing::Size(22, 31);
			this->label227->TabIndex = 186;
			this->label227->Text = L"]";
			// 
			// label230
			// 
			this->label230->AutoSize = true;
			this->label230->ForeColor = System::Drawing::Color::White;
			this->label230->Location = System::Drawing::Point(787, 185);
			this->label230->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label230->Name = L"label230";
			this->label230->Size = System::Drawing::Size(28, 13);
			this->label230->TabIndex = 189;
			this->label230->Text = L"<-80";
			// 
			// label229
			// 
			this->label229->AutoSize = true;
			this->label229->ForeColor = System::Drawing::Color::White;
			this->label229->Location = System::Drawing::Point(800, 53);
			this->label229->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label229->Name = L"label229";
			this->label229->Size = System::Drawing::Size(13, 13);
			this->label229->TabIndex = 188;
			this->label229->Text = L"0";
			// 
			// label231
			// 
			this->label231->AutoSize = true;
			this->label231->ForeColor = System::Drawing::Color::White;
			this->label231->Location = System::Drawing::Point(793, 74);
			this->label231->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label231->Name = L"label231";
			this->label231->Size = System::Drawing::Size(22, 13);
			this->label231->TabIndex = 190;
			this->label231->Text = L"-10";
			// 
			// label232
			// 
			this->label232->AutoSize = true;
			this->label232->ForeColor = System::Drawing::Color::White;
			this->label232->Location = System::Drawing::Point(793, 92);
			this->label232->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label232->Name = L"label232";
			this->label232->Size = System::Drawing::Size(22, 13);
			this->label232->TabIndex = 191;
			this->label232->Text = L"-20";
			// 
			// label233
			// 
			this->label233->AutoSize = true;
			this->label233->ForeColor = System::Drawing::Color::White;
			this->label233->Location = System::Drawing::Point(793, 111);
			this->label233->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label233->Name = L"label233";
			this->label233->Size = System::Drawing::Size(22, 13);
			this->label233->TabIndex = 192;
			this->label233->Text = L"-30";
			// 
			// label234
			// 
			this->label234->AutoSize = true;
			this->label234->ForeColor = System::Drawing::Color::White;
			this->label234->Location = System::Drawing::Point(793, 130);
			this->label234->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label234->Name = L"label234";
			this->label234->Size = System::Drawing::Size(22, 13);
			this->label234->TabIndex = 193;
			this->label234->Text = L"-40";
			// 
			// label235
			// 
			this->label235->AutoSize = true;
			this->label235->ForeColor = System::Drawing::Color::White;
			this->label235->Location = System::Drawing::Point(793, 149);
			this->label235->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label235->Name = L"label235";
			this->label235->Size = System::Drawing::Size(22, 13);
			this->label235->TabIndex = 194;
			this->label235->Text = L"-60";
			// 
			// label236
			// 
			this->label236->AutoSize = true;
			this->label236->ForeColor = System::Drawing::Color::White;
			this->label236->Location = System::Drawing::Point(793, 168);
			this->label236->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label236->Name = L"label236";
			this->label236->Size = System::Drawing::Size(22, 13);
			this->label236->TabIndex = 195;
			this->label236->Text = L"-70";
			// 
			// label239
			// 
			this->label239->AutoSize = true;
			this->label239->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label239->ForeColor = System::Drawing::Color::White;
			this->label239->Location = System::Drawing::Point(786, 27);
			this->label239->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label239->Name = L"label239";
			this->label239->Size = System::Drawing::Size(46, 13);
			this->label239->TabIndex = 198;
			this->label239->Text = L"Colorbar";
			// 
			// SINGLE_RDM_VIEW
			// 
			this->SINGLE_RDM_VIEW->BackColor = System::Drawing::Color::Black;
			this->SINGLE_RDM_VIEW->Controls->Add(this->Free_Flight_PB_MAP);
			this->SINGLE_RDM_VIEW->Controls->Add(this->Load_PB_MAP);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_MAP_location);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label262);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label261);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox113);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox112);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox111);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox110);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox109);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox108);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox107);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox106);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label260);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbox_select_RDM);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label253);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label256);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox105);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label257);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label258);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label259);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label252);
			this->SINGLE_RDM_VIEW->Controls->Add(this->PB_RDM_COLOR_MAP);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox87);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox88);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_velocity_6);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox89);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_velocity_5);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox90);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_velocity_4);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox91);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox92);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_velocity_1);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox93);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_velocity_2);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox94);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_velocity_3);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox95);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox96);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox97);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_range_7);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox98);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_range_6);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox99);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_range_5);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox100);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_range_4);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox101);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_range_3);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox102);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_range_2);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox103);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_range_1);
			this->SINGLE_RDM_VIEW->Controls->Add(this->groupBox104);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label269);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_velocity_min);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_velocity_max);
			this->SINGLE_RDM_VIEW->Controls->Add(this->lbl_range_max);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label274);
			this->SINGLE_RDM_VIEW->Controls->Add(this->Lbl_RDM);
			this->SINGLE_RDM_VIEW->Controls->Add(this->PB_RDM);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label282);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label283);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label284);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label285);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label286);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label287);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label288);
			this->SINGLE_RDM_VIEW->Controls->Add(this->label289);
			this->SINGLE_RDM_VIEW->Controls->Add(this->PB_MAP_chart);
			this->SINGLE_RDM_VIEW->Location = System::Drawing::Point(4, 22);
			this->SINGLE_RDM_VIEW->Name = L"SINGLE_RDM_VIEW";
			this->SINGLE_RDM_VIEW->Padding = System::Windows::Forms::Padding(3);
			this->SINGLE_RDM_VIEW->Size = System::Drawing::Size(828, 590);
			this->SINGLE_RDM_VIEW->TabIndex = 7;
			this->SINGLE_RDM_VIEW->Text = L"Operator";
			// 
			// Free_Flight_PB_MAP
			// 
			this->Free_Flight_PB_MAP->Enabled = false;
			this->Free_Flight_PB_MAP->ForeColor = System::Drawing::SystemColors::Desktop;
			this->Free_Flight_PB_MAP->Location = System::Drawing::Point(659, 464);
			this->Free_Flight_PB_MAP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->Free_Flight_PB_MAP->Name = L"Free_Flight_PB_MAP";
			this->Free_Flight_PB_MAP->Size = System::Drawing::Size(141, 23);
			this->Free_Flight_PB_MAP->TabIndex = 274;
			this->Free_Flight_PB_MAP->Text = L"Free Flight";
			this->Free_Flight_PB_MAP->UseVisualStyleBackColor = true;
			this->Free_Flight_PB_MAP->Click += gcnew System::EventHandler(this, &MyForm::Free_Flight_MAP_Click);
			// 
			// Load_PB_MAP
			// 
			this->Load_PB_MAP->ForeColor = System::Drawing::SystemColors::Desktop;
			this->Load_PB_MAP->Location = System::Drawing::Point(442, 464);
			this->Load_PB_MAP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->Load_PB_MAP->Name = L"Load_PB_MAP";
			this->Load_PB_MAP->Size = System::Drawing::Size(141, 23);
			this->Load_PB_MAP->TabIndex = 272;
			this->Load_PB_MAP->Text = L"Load Map";
			this->Load_PB_MAP->UseVisualStyleBackColor = true;
			this->Load_PB_MAP->Click += gcnew System::EventHandler(this, &MyForm::B_LOAD_MAP_Click);
			// 
			// lbl_MAP_location
			// 
			this->lbl_MAP_location->AutoSize = true;
			this->lbl_MAP_location->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl_MAP_location->ForeColor = System::Drawing::Color::White;
			this->lbl_MAP_location->Location = System::Drawing::Point(560, 86);
			this->lbl_MAP_location->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_MAP_location->Name = L"lbl_MAP_location";
			this->lbl_MAP_location->Size = System::Drawing::Size(0, 20);
			this->lbl_MAP_location->TabIndex = 271;
			this->lbl_MAP_location->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label262
			// 
			this->label262->AutoSize = true;
			this->label262->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label262->ForeColor = System::Drawing::Color::White;
			this->label262->Location = System::Drawing::Point(290, 440);
			this->label262->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label262->Name = L"label262";
			this->label262->Size = System::Drawing::Size(68, 13);
			this->label262->TabIndex = 268;
			this->label262->Text = L"RDM Select:";
			// 
			// label261
			// 
			this->label261->AutoSize = true;
			this->label261->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label261->ForeColor = System::Drawing::Color::White;
			this->label261->Location = System::Drawing::Point(71, 441);
			this->label261->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label261->Name = L"label261";
			this->label261->Size = System::Drawing::Size(49, 13);
			this->label261->TabIndex = 267;
			this->label261->Text = L"Colorbar:";
			// 
			// groupBox113
			// 
			this->groupBox113->BackColor = System::Drawing::Color::White;
			this->groupBox113->Location = System::Drawing::Point(169, 466);
			this->groupBox113->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox113->Name = L"groupBox113";
			this->groupBox113->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox113->Size = System::Drawing::Size(2, 10);
			this->groupBox113->TabIndex = 266;
			this->groupBox113->TabStop = false;
			this->groupBox113->Text = L"groupBox113";
			// 
			// groupBox112
			// 
			this->groupBox112->BackColor = System::Drawing::Color::White;
			this->groupBox112->Location = System::Drawing::Point(205, 466);
			this->groupBox112->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox112->Name = L"groupBox112";
			this->groupBox112->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox112->Size = System::Drawing::Size(2, 10);
			this->groupBox112->TabIndex = 266;
			this->groupBox112->TabStop = false;
			this->groupBox112->Text = L"groupBox112";
			// 
			// groupBox111
			// 
			this->groupBox111->BackColor = System::Drawing::Color::White;
			this->groupBox111->Location = System::Drawing::Point(131, 466);
			this->groupBox111->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox111->Name = L"groupBox111";
			this->groupBox111->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox111->Size = System::Drawing::Size(2, 10);
			this->groupBox111->TabIndex = 266;
			this->groupBox111->TabStop = false;
			this->groupBox111->Text = L"groupBox111";
			// 
			// groupBox110
			// 
			this->groupBox110->BackColor = System::Drawing::Color::White;
			this->groupBox110->Location = System::Drawing::Point(150, 466);
			this->groupBox110->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox110->Name = L"groupBox110";
			this->groupBox110->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox110->Size = System::Drawing::Size(2, 10);
			this->groupBox110->TabIndex = 266;
			this->groupBox110->TabStop = false;
			this->groupBox110->Text = L"groupBox110";
			// 
			// groupBox109
			// 
			this->groupBox109->BackColor = System::Drawing::Color::White;
			this->groupBox109->Location = System::Drawing::Point(188, 466);
			this->groupBox109->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox109->Name = L"groupBox109";
			this->groupBox109->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox109->Size = System::Drawing::Size(2, 10);
			this->groupBox109->TabIndex = 266;
			this->groupBox109->TabStop = false;
			this->groupBox109->Text = L"groupBox109";
			// 
			// groupBox108
			// 
			this->groupBox108->BackColor = System::Drawing::Color::White;
			this->groupBox108->Location = System::Drawing::Point(112, 466);
			this->groupBox108->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox108->Name = L"groupBox108";
			this->groupBox108->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox108->Size = System::Drawing::Size(2, 10);
			this->groupBox108->TabIndex = 266;
			this->groupBox108->TabStop = false;
			this->groupBox108->Text = L"groupBox108";
			// 
			// groupBox107
			// 
			this->groupBox107->BackColor = System::Drawing::Color::White;
			this->groupBox107->Location = System::Drawing::Point(93, 466);
			this->groupBox107->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox107->Name = L"groupBox107";
			this->groupBox107->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox107->Size = System::Drawing::Size(2, 10);
			this->groupBox107->TabIndex = 266;
			this->groupBox107->TabStop = false;
			this->groupBox107->Text = L"groupBox107";
			// 
			// groupBox106
			// 
			this->groupBox106->BackColor = System::Drawing::Color::White;
			this->groupBox106->Location = System::Drawing::Point(74, 466);
			this->groupBox106->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox106->Name = L"groupBox106";
			this->groupBox106->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox106->Size = System::Drawing::Size(2, 10);
			this->groupBox106->TabIndex = 265;
			this->groupBox106->TabStop = false;
			this->groupBox106->Text = L"groupBox106";
			// 
			// label260
			// 
			this->label260->AutoSize = true;
			this->label260->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label260->ForeColor = System::Drawing::Color::White;
			this->label260->Location = System::Drawing::Point(132, 105);
			this->label260->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label260->Name = L"label260";
			this->label260->Size = System::Drawing::Size(50, 20);
			this->label260->TabIndex = 264;
			this->label260->Text = L"RDM:";
			// 
			// lbox_select_RDM
			// 
			this->lbox_select_RDM->FormattingEnabled = true;
			this->lbox_select_RDM->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Left H", L"Left V", L"Right H", L"Right V" });
			this->lbox_select_RDM->Location = System::Drawing::Point(293, 453);
			this->lbox_select_RDM->Name = L"lbox_select_RDM";
			this->lbox_select_RDM->Size = System::Drawing::Size(64, 56);
			this->lbox_select_RDM->TabIndex = 263;
			this->lbox_select_RDM->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::lbox_select_RDM_SelectedIndexChanged);
			// 
			// label253
			// 
			this->label253->AutoSize = true;
			this->label253->ForeColor = System::Drawing::Color::White;
			this->label253->Location = System::Drawing::Point(26, 254);
			this->label253->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label253->Name = L"label253";
			this->label253->Size = System::Drawing::Size(26, 13);
			this->label253->TabIndex = 257;
			this->label253->Text = L"V=0";
			// 
			// label256
			// 
			this->label256->AutoSize = true;
			this->label256->ForeColor = System::Drawing::Color::White;
			this->label256->Location = System::Drawing::Point(7, 243);
			this->label256->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label256->Name = L"label256";
			this->label256->Size = System::Drawing::Size(15, 13);
			this->label256->TabIndex = 259;
			this->label256->Text = L"m";
			// 
			// groupBox105
			// 
			this->groupBox105->BackColor = System::Drawing::Color::White;
			this->groupBox105->Location = System::Drawing::Point(9, 256);
			this->groupBox105->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox105->Name = L"groupBox105";
			this->groupBox105->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox105->Size = System::Drawing::Size(10, 1);
			this->groupBox105->TabIndex = 260;
			this->groupBox105->TabStop = false;
			this->groupBox105->Text = L"groupBox105";
			// 
			// label257
			// 
			this->label257->AutoSize = true;
			this->label257->ForeColor = System::Drawing::Color::White;
			this->label257->Location = System::Drawing::Point(8, 256);
			this->label257->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label257->Name = L"label257";
			this->label257->Size = System::Drawing::Size(12, 13);
			this->label257->TabIndex = 261;
			this->label257->Text = L"s";
			// 
			// label258
			// 
			this->label258->AutoSize = true;
			this->label258->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label258->ForeColor = System::Drawing::Color::White;
			this->label258->Location = System::Drawing::Point(-6, 239);
			this->label258->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label258->Name = L"label258";
			this->label258->Size = System::Drawing::Size(22, 31);
			this->label258->TabIndex = 258;
			this->label258->Text = L"[";
			// 
			// label259
			// 
			this->label259->AutoSize = true;
			this->label259->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label259->ForeColor = System::Drawing::Color::White;
			this->label259->Location = System::Drawing::Point(14, 239);
			this->label259->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label259->Name = L"label259";
			this->label259->Size = System::Drawing::Size(22, 31);
			this->label259->TabIndex = 262;
			this->label259->Text = L"]";
			// 
			// label252
			// 
			this->label252->AutoSize = true;
			this->label252->ForeColor = System::Drawing::Color::White;
			this->label252->Location = System::Drawing::Point(222, 475);
			this->label252->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label252->Name = L"label252";
			this->label252->Size = System::Drawing::Size(26, 13);
			this->label252->TabIndex = 255;
			this->label252->Text = L"[dB]";
			// 
			// PB_RDM_COLOR_MAP
			// 
			this->PB_RDM_COLOR_MAP->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->PB_RDM_COLOR_MAP->Location = System::Drawing::Point(74, 455);
			this->PB_RDM_COLOR_MAP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->PB_RDM_COLOR_MAP->Name = L"PB_RDM_COLOR_MAP";
			this->PB_RDM_COLOR_MAP->Size = System::Drawing::Size(133, 18);
			this->PB_RDM_COLOR_MAP->TabIndex = 246;
			this->PB_RDM_COLOR_MAP->TabStop = false;
			// 
			// groupBox87
			// 
			this->groupBox87->BackColor = System::Drawing::Color::White;
			this->groupBox87->Location = System::Drawing::Point(59, 133);
			this->groupBox87->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox87->Name = L"groupBox87";
			this->groupBox87->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox87->Size = System::Drawing::Size(20, 1);
			this->groupBox87->TabIndex = 240;
			this->groupBox87->TabStop = false;
			this->groupBox87->Text = L"groupBox87";
			// 
			// groupBox88
			// 
			this->groupBox88->BackColor = System::Drawing::Color::White;
			this->groupBox88->Location = System::Drawing::Point(59, 165);
			this->groupBox88->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox88->Name = L"groupBox88";
			this->groupBox88->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox88->Size = System::Drawing::Size(20, 1);
			this->groupBox88->TabIndex = 239;
			this->groupBox88->TabStop = false;
			this->groupBox88->Text = L"groupBox88";
			// 
			// lbl_velocity_6
			// 
			this->lbl_velocity_6->AutoSize = true;
			this->lbl_velocity_6->ForeColor = System::Drawing::Color::White;
			this->lbl_velocity_6->Location = System::Drawing::Point(31, 157);
			this->lbl_velocity_6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_velocity_6->Name = L"lbl_velocity_6";
			this->lbl_velocity_6->Size = System::Drawing::Size(10, 13);
			this->lbl_velocity_6->TabIndex = 238;
			this->lbl_velocity_6->Text = L"-";
			// 
			// groupBox89
			// 
			this->groupBox89->BackColor = System::Drawing::Color::White;
			this->groupBox89->Location = System::Drawing::Point(59, 196);
			this->groupBox89->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox89->Name = L"groupBox89";
			this->groupBox89->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox89->Size = System::Drawing::Size(20, 1);
			this->groupBox89->TabIndex = 237;
			this->groupBox89->TabStop = false;
			this->groupBox89->Text = L"groupBox89";
			// 
			// lbl_velocity_5
			// 
			this->lbl_velocity_5->AutoSize = true;
			this->lbl_velocity_5->ForeColor = System::Drawing::Color::White;
			this->lbl_velocity_5->Location = System::Drawing::Point(31, 189);
			this->lbl_velocity_5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_velocity_5->Name = L"lbl_velocity_5";
			this->lbl_velocity_5->Size = System::Drawing::Size(10, 13);
			this->lbl_velocity_5->TabIndex = 236;
			this->lbl_velocity_5->Text = L"-";
			// 
			// groupBox90
			// 
			this->groupBox90->BackColor = System::Drawing::Color::White;
			this->groupBox90->Location = System::Drawing::Point(59, 230);
			this->groupBox90->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox90->Name = L"groupBox90";
			this->groupBox90->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox90->Size = System::Drawing::Size(20, 1);
			this->groupBox90->TabIndex = 235;
			this->groupBox90->TabStop = false;
			this->groupBox90->Text = L"groupBox90";
			// 
			// lbl_velocity_4
			// 
			this->lbl_velocity_4->AutoSize = true;
			this->lbl_velocity_4->ForeColor = System::Drawing::Color::White;
			this->lbl_velocity_4->Location = System::Drawing::Point(31, 223);
			this->lbl_velocity_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_velocity_4->Name = L"lbl_velocity_4";
			this->lbl_velocity_4->Size = System::Drawing::Size(10, 13);
			this->lbl_velocity_4->TabIndex = 234;
			this->lbl_velocity_4->Text = L"-";
			// 
			// groupBox91
			// 
			this->groupBox91->BackColor = System::Drawing::Color::White;
			this->groupBox91->Location = System::Drawing::Point(59, 387);
			this->groupBox91->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox91->Name = L"groupBox91";
			this->groupBox91->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox91->Size = System::Drawing::Size(20, 1);
			this->groupBox91->TabIndex = 233;
			this->groupBox91->TabStop = false;
			this->groupBox91->Text = L"groupBox91";
			// 
			// groupBox92
			// 
			this->groupBox92->BackColor = System::Drawing::Color::White;
			this->groupBox92->Location = System::Drawing::Point(59, 357);
			this->groupBox92->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox92->Name = L"groupBox92";
			this->groupBox92->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox92->Size = System::Drawing::Size(20, 1);
			this->groupBox92->TabIndex = 232;
			this->groupBox92->TabStop = false;
			this->groupBox92->Text = L"groupBox92";
			// 
			// lbl_velocity_1
			// 
			this->lbl_velocity_1->AutoSize = true;
			this->lbl_velocity_1->ForeColor = System::Drawing::Color::White;
			this->lbl_velocity_1->Location = System::Drawing::Point(31, 350);
			this->lbl_velocity_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_velocity_1->Name = L"lbl_velocity_1";
			this->lbl_velocity_1->Size = System::Drawing::Size(10, 13);
			this->lbl_velocity_1->TabIndex = 231;
			this->lbl_velocity_1->Text = L"-";
			// 
			// groupBox93
			// 
			this->groupBox93->BackColor = System::Drawing::Color::White;
			this->groupBox93->Location = System::Drawing::Point(59, 325);
			this->groupBox93->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox93->Name = L"groupBox93";
			this->groupBox93->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox93->Size = System::Drawing::Size(20, 1);
			this->groupBox93->TabIndex = 230;
			this->groupBox93->TabStop = false;
			this->groupBox93->Text = L"groupBox93";
			// 
			// lbl_velocity_2
			// 
			this->lbl_velocity_2->AutoSize = true;
			this->lbl_velocity_2->ForeColor = System::Drawing::Color::White;
			this->lbl_velocity_2->Location = System::Drawing::Point(31, 317);
			this->lbl_velocity_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_velocity_2->Name = L"lbl_velocity_2";
			this->lbl_velocity_2->Size = System::Drawing::Size(10, 13);
			this->lbl_velocity_2->TabIndex = 229;
			this->lbl_velocity_2->Text = L"-";
			// 
			// groupBox94
			// 
			this->groupBox94->BackColor = System::Drawing::Color::White;
			this->groupBox94->Location = System::Drawing::Point(59, 293);
			this->groupBox94->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox94->Name = L"groupBox94";
			this->groupBox94->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox94->Size = System::Drawing::Size(20, 1);
			this->groupBox94->TabIndex = 228;
			this->groupBox94->TabStop = false;
			this->groupBox94->Text = L"groupBox94";
			// 
			// lbl_velocity_3
			// 
			this->lbl_velocity_3->AutoSize = true;
			this->lbl_velocity_3->ForeColor = System::Drawing::Color::White;
			this->lbl_velocity_3->Location = System::Drawing::Point(31, 285);
			this->lbl_velocity_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_velocity_3->Name = L"lbl_velocity_3";
			this->lbl_velocity_3->Size = System::Drawing::Size(10, 13);
			this->lbl_velocity_3->TabIndex = 227;
			this->lbl_velocity_3->Text = L"-";
			// 
			// groupBox95
			// 
			this->groupBox95->BackColor = System::Drawing::Color::White;
			this->groupBox95->Location = System::Drawing::Point(59, 261);
			this->groupBox95->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox95->Name = L"groupBox95";
			this->groupBox95->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox95->Size = System::Drawing::Size(20, 1);
			this->groupBox95->TabIndex = 226;
			this->groupBox95->TabStop = false;
			this->groupBox95->Text = L"groupBox95";
			// 
			// groupBox96
			// 
			this->groupBox96->BackColor = System::Drawing::Color::White;
			this->groupBox96->Location = System::Drawing::Point(387, 377);
			this->groupBox96->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox96->Name = L"groupBox96";
			this->groupBox96->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox96->Size = System::Drawing::Size(2, 20);
			this->groupBox96->TabIndex = 225;
			this->groupBox96->TabStop = false;
			this->groupBox96->Text = L"groupBox96";
			// 
			// groupBox97
			// 
			this->groupBox97->BackColor = System::Drawing::Color::White;
			this->groupBox97->Location = System::Drawing::Point(348, 377);
			this->groupBox97->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox97->Name = L"groupBox97";
			this->groupBox97->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox97->Size = System::Drawing::Size(2, 20);
			this->groupBox97->TabIndex = 223;
			this->groupBox97->TabStop = false;
			this->groupBox97->Text = L"groupBox97";
			// 
			// lbl_range_7
			// 
			this->lbl_range_7->AutoSize = true;
			this->lbl_range_7->ForeColor = System::Drawing::Color::White;
			this->lbl_range_7->Location = System::Drawing::Point(340, 394);
			this->lbl_range_7->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_range_7->Name = L"lbl_range_7";
			this->lbl_range_7->Size = System::Drawing::Size(10, 13);
			this->lbl_range_7->TabIndex = 224;
			this->lbl_range_7->Text = L"-";
			// 
			// groupBox98
			// 
			this->groupBox98->BackColor = System::Drawing::Color::White;
			this->groupBox98->Location = System::Drawing::Point(309, 377);
			this->groupBox98->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox98->Name = L"groupBox98";
			this->groupBox98->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox98->Size = System::Drawing::Size(2, 20);
			this->groupBox98->TabIndex = 221;
			this->groupBox98->TabStop = false;
			this->groupBox98->Text = L"groupBox98";
			// 
			// lbl_range_6
			// 
			this->lbl_range_6->AutoSize = true;
			this->lbl_range_6->ForeColor = System::Drawing::Color::White;
			this->lbl_range_6->Location = System::Drawing::Point(301, 394);
			this->lbl_range_6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_range_6->Name = L"lbl_range_6";
			this->lbl_range_6->Size = System::Drawing::Size(10, 13);
			this->lbl_range_6->TabIndex = 222;
			this->lbl_range_6->Text = L"-";
			// 
			// groupBox99
			// 
			this->groupBox99->BackColor = System::Drawing::Color::White;
			this->groupBox99->Location = System::Drawing::Point(269, 377);
			this->groupBox99->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox99->Name = L"groupBox99";
			this->groupBox99->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox99->Size = System::Drawing::Size(2, 20);
			this->groupBox99->TabIndex = 219;
			this->groupBox99->TabStop = false;
			this->groupBox99->Text = L"groupBox99";
			// 
			// lbl_range_5
			// 
			this->lbl_range_5->AutoSize = true;
			this->lbl_range_5->ForeColor = System::Drawing::Color::White;
			this->lbl_range_5->Location = System::Drawing::Point(261, 394);
			this->lbl_range_5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_range_5->Name = L"lbl_range_5";
			this->lbl_range_5->Size = System::Drawing::Size(10, 13);
			this->lbl_range_5->TabIndex = 220;
			this->lbl_range_5->Text = L"-";
			// 
			// groupBox100
			// 
			this->groupBox100->BackColor = System::Drawing::Color::White;
			this->groupBox100->Location = System::Drawing::Point(228, 377);
			this->groupBox100->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox100->Name = L"groupBox100";
			this->groupBox100->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox100->Size = System::Drawing::Size(2, 20);
			this->groupBox100->TabIndex = 217;
			this->groupBox100->TabStop = false;
			this->groupBox100->Text = L"groupBox100";
			// 
			// lbl_range_4
			// 
			this->lbl_range_4->AutoSize = true;
			this->lbl_range_4->ForeColor = System::Drawing::Color::White;
			this->lbl_range_4->Location = System::Drawing::Point(220, 394);
			this->lbl_range_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_range_4->Name = L"lbl_range_4";
			this->lbl_range_4->Size = System::Drawing::Size(10, 13);
			this->lbl_range_4->TabIndex = 218;
			this->lbl_range_4->Text = L"-";
			// 
			// groupBox101
			// 
			this->groupBox101->BackColor = System::Drawing::Color::White;
			this->groupBox101->Location = System::Drawing::Point(189, 377);
			this->groupBox101->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox101->Name = L"groupBox101";
			this->groupBox101->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox101->Size = System::Drawing::Size(2, 20);
			this->groupBox101->TabIndex = 215;
			this->groupBox101->TabStop = false;
			this->groupBox101->Text = L"groupBox101";
			// 
			// lbl_range_3
			// 
			this->lbl_range_3->AutoSize = true;
			this->lbl_range_3->ForeColor = System::Drawing::Color::White;
			this->lbl_range_3->Location = System::Drawing::Point(181, 394);
			this->lbl_range_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_range_3->Name = L"lbl_range_3";
			this->lbl_range_3->Size = System::Drawing::Size(10, 13);
			this->lbl_range_3->TabIndex = 216;
			this->lbl_range_3->Text = L"-";
			// 
			// groupBox102
			// 
			this->groupBox102->BackColor = System::Drawing::Color::White;
			this->groupBox102->Location = System::Drawing::Point(149, 377);
			this->groupBox102->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox102->Name = L"groupBox102";
			this->groupBox102->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox102->Size = System::Drawing::Size(2, 20);
			this->groupBox102->TabIndex = 213;
			this->groupBox102->TabStop = false;
			this->groupBox102->Text = L"groupBox102";
			// 
			// lbl_range_2
			// 
			this->lbl_range_2->AutoSize = true;
			this->lbl_range_2->ForeColor = System::Drawing::Color::White;
			this->lbl_range_2->Location = System::Drawing::Point(141, 394);
			this->lbl_range_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_range_2->Name = L"lbl_range_2";
			this->lbl_range_2->Size = System::Drawing::Size(10, 13);
			this->lbl_range_2->TabIndex = 214;
			this->lbl_range_2->Text = L"-";
			// 
			// groupBox103
			// 
			this->groupBox103->BackColor = System::Drawing::Color::White;
			this->groupBox103->Location = System::Drawing::Point(108, 377);
			this->groupBox103->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox103->Name = L"groupBox103";
			this->groupBox103->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox103->Size = System::Drawing::Size(2, 20);
			this->groupBox103->TabIndex = 212;
			this->groupBox103->TabStop = false;
			this->groupBox103->Text = L"groupBox103";
			// 
			// lbl_range_1
			// 
			this->lbl_range_1->AutoSize = true;
			this->lbl_range_1->ForeColor = System::Drawing::Color::White;
			this->lbl_range_1->Location = System::Drawing::Point(100, 394);
			this->lbl_range_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_range_1->Name = L"lbl_range_1";
			this->lbl_range_1->Size = System::Drawing::Size(10, 13);
			this->lbl_range_1->TabIndex = 211;
			this->lbl_range_1->Text = L"-";
			// 
			// groupBox104
			// 
			this->groupBox104->BackColor = System::Drawing::Color::White;
			this->groupBox104->Location = System::Drawing::Point(69, 377);
			this->groupBox104->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox104->Name = L"groupBox104";
			this->groupBox104->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox104->Size = System::Drawing::Size(2, 20);
			this->groupBox104->TabIndex = 210;
			this->groupBox104->TabStop = false;
			this->groupBox104->Text = L"groupBox104";
			// 
			// label269
			// 
			this->label269->AutoSize = true;
			this->label269->ForeColor = System::Drawing::Color::White;
			this->label269->Location = System::Drawing::Point(379, 405);
			this->label269->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label269->Name = L"label269";
			this->label269->Size = System::Drawing::Size(21, 13);
			this->label269->TabIndex = 208;
			this->label269->Text = L"[m]";
			// 
			// lbl_velocity_min
			// 
			this->lbl_velocity_min->AutoSize = true;
			this->lbl_velocity_min->ForeColor = System::Drawing::Color::White;
			this->lbl_velocity_min->Location = System::Drawing::Point(31, 383);
			this->lbl_velocity_min->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_velocity_min->Name = L"lbl_velocity_min";
			this->lbl_velocity_min->Size = System::Drawing::Size(23, 13);
			this->lbl_velocity_min->TabIndex = 207;
			this->lbl_velocity_min->Text = L"min";
			// 
			// lbl_velocity_max
			// 
			this->lbl_velocity_max->AutoSize = true;
			this->lbl_velocity_max->ForeColor = System::Drawing::Color::White;
			this->lbl_velocity_max->Location = System::Drawing::Point(31, 126);
			this->lbl_velocity_max->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_velocity_max->Name = L"lbl_velocity_max";
			this->lbl_velocity_max->Size = System::Drawing::Size(26, 13);
			this->lbl_velocity_max->TabIndex = 206;
			this->lbl_velocity_max->Text = L"max";
			// 
			// lbl_range_max
			// 
			this->lbl_range_max->AutoSize = true;
			this->lbl_range_max->ForeColor = System::Drawing::Color::White;
			this->lbl_range_max->Location = System::Drawing::Point(377, 394);
			this->lbl_range_max->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_range_max->Name = L"lbl_range_max";
			this->lbl_range_max->Size = System::Drawing::Size(26, 13);
			this->lbl_range_max->TabIndex = 205;
			this->lbl_range_max->Text = L"max";
			// 
			// label274
			// 
			this->label274->AutoSize = true;
			this->label274->ForeColor = System::Drawing::Color::White;
			this->label274->Location = System::Drawing::Point(57, 394);
			this->label274->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label274->Name = L"label274";
			this->label274->Size = System::Drawing::Size(27, 13);
			this->label274->TabIndex = 203;
			this->label274->Text = L"R=0";
			// 
			// Lbl_RDM
			// 
			this->Lbl_RDM->AutoSize = true;
			this->Lbl_RDM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Lbl_RDM->ForeColor = System::Drawing::Color::White;
			this->Lbl_RDM->Location = System::Drawing::Point(182, 105);
			this->Lbl_RDM->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Lbl_RDM->Name = L"Lbl_RDM";
			this->Lbl_RDM->Size = System::Drawing::Size(0, 20);
			this->Lbl_RDM->TabIndex = 201;
			// 
			// PB_RDM
			// 
			this->PB_RDM->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->PB_RDM->Location = System::Drawing::Point(69, 133);
			this->PB_RDM->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->PB_RDM->Name = L"PB_RDM";
			this->PB_RDM->Size = System::Drawing::Size(320, 255);
			this->PB_RDM->TabIndex = 199;
			this->PB_RDM->TabStop = false;
			// 
			// label282
			// 
			this->label282->AutoSize = true;
			this->label282->ForeColor = System::Drawing::Color::White;
			this->label282->Location = System::Drawing::Point(198, 475);
			this->label282->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label282->Name = L"label282";
			this->label282->Size = System::Drawing::Size(28, 13);
			this->label282->TabIndex = 248;
			this->label282->Text = L"<-80";
			// 
			// label283
			// 
			this->label283->AutoSize = true;
			this->label283->ForeColor = System::Drawing::Color::White;
			this->label283->Location = System::Drawing::Point(68, 475);
			this->label283->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label283->Name = L"label283";
			this->label283->Size = System::Drawing::Size(13, 13);
			this->label283->TabIndex = 247;
			this->label283->Text = L"0";
			// 
			// label284
			// 
			this->label284->AutoSize = true;
			this->label284->ForeColor = System::Drawing::Color::White;
			this->label284->Location = System::Drawing::Point(79, 475);
			this->label284->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label284->Name = L"label284";
			this->label284->Size = System::Drawing::Size(22, 13);
			this->label284->TabIndex = 249;
			this->label284->Text = L"-10";
			// 
			// label285
			// 
			this->label285->AutoSize = true;
			this->label285->ForeColor = System::Drawing::Color::White;
			this->label285->Location = System::Drawing::Point(101, 475);
			this->label285->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label285->Name = L"label285";
			this->label285->Size = System::Drawing::Size(22, 13);
			this->label285->TabIndex = 250;
			this->label285->Text = L"-20";
			// 
			// label286
			// 
			this->label286->AutoSize = true;
			this->label286->ForeColor = System::Drawing::Color::White;
			this->label286->Location = System::Drawing::Point(121, 475);
			this->label286->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label286->Name = L"label286";
			this->label286->Size = System::Drawing::Size(22, 13);
			this->label286->TabIndex = 251;
			this->label286->Text = L"-30";
			// 
			// label287
			// 
			this->label287->AutoSize = true;
			this->label287->ForeColor = System::Drawing::Color::White;
			this->label287->Location = System::Drawing::Point(140, 475);
			this->label287->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label287->Name = L"label287";
			this->label287->Size = System::Drawing::Size(22, 13);
			this->label287->TabIndex = 252;
			this->label287->Text = L"-40";
			// 
			// label288
			// 
			this->label288->AutoSize = true;
			this->label288->ForeColor = System::Drawing::Color::White;
			this->label288->Location = System::Drawing::Point(159, 475);
			this->label288->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label288->Name = L"label288";
			this->label288->Size = System::Drawing::Size(22, 13);
			this->label288->TabIndex = 253;
			this->label288->Text = L"-60";
			// 
			// label289
			// 
			this->label289->AutoSize = true;
			this->label289->ForeColor = System::Drawing::Color::White;
			this->label289->Location = System::Drawing::Point(179, 475);
			this->label289->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label289->Name = L"label289";
			this->label289->Size = System::Drawing::Size(22, 13);
			this->label289->TabIndex = 254;
			this->label289->Text = L"-70";
			// 
			// PB_MAP_chart
			// 
			this->PB_MAP_chart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->PB_MAP_chart->BackColor = System::Drawing::Color::Black;
			chartArea11->AlignmentOrientation = static_cast<System::Windows::Forms::DataVisualization::Charting::AreaAlignmentOrientations>((System::Windows::Forms::DataVisualization::Charting::AreaAlignmentOrientations::Vertical | System::Windows::Forms::DataVisualization::Charting::AreaAlignmentOrientations::Horizontal));
			chartArea11->AxisX->Crossing = 1.7976931348623157E+308;
			chartArea11->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea11->AxisX->InterlacedColor = System::Drawing::Color::White;
			chartArea11->AxisX->Interval = 1000;
			chartArea11->AxisX->IsMarksNextToAxis = false;
			chartArea11->AxisX->LabelStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6));
			chartArea11->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea11->AxisX->LineColor = System::Drawing::Color::Silver;
			chartArea11->AxisX->MajorGrid->LineColor = System::Drawing::Color::Silver;
			chartArea11->AxisX->MajorTickMark->Enabled = false;
			chartArea11->AxisX->Maximum = 4000;
			chartArea11->AxisX->Minimum = 0;
			chartArea11->AxisX->StripLines->Add(stripLine3);
			chartArea11->AxisY->Crossing = 1.7976931348623157E+308;
			chartArea11->AxisY->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea11->AxisY->Interval = 1000;
			chartArea11->AxisY->IsMarksNextToAxis = false;
			chartArea11->AxisY->LabelStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6));
			chartArea11->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea11->AxisY->LineColor = System::Drawing::Color::Silver;
			chartArea11->AxisY->MajorGrid->LineColor = System::Drawing::Color::Silver;
			chartArea11->AxisY->MajorTickMark->Enabled = false;
			chartArea11->AxisY->Maximum = 4000;
			chartArea11->AxisY->Minimum = 0;
			chartArea11->AxisY->StripLines->Add(stripLine4);
			chartArea11->BackColor = System::Drawing::Color::White;
			chartArea11->BorderColor = System::Drawing::Color::White;
			chartArea11->Name = L"ChartArea1";
			chartArea11->Position->Auto = false;
			chartArea11->Position->Height = 95;
			chartArea11->Position->Width = 95;
			chartArea11->Position->X = 5;
			this->PB_MAP_chart->ChartAreas->Add(chartArea11);
			legend8->Enabled = false;
			legend8->Name = L"Legend1";
			this->PB_MAP_chart->Legends->Add(legend8);
			this->PB_MAP_chart->Location = System::Drawing::Point(380, 105);
			this->PB_MAP_chart->Margin = System::Windows::Forms::Padding(0);
			this->PB_MAP_chart->Name = L"PB_MAP_chart";
			series28->BorderWidth = 3;
			series28->ChartArea = L"ChartArea1";
			series28->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series28->Color = System::Drawing::Color::Blue;
			series28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			series28->IsVisibleInLegend = false;
			series28->Legend = L"Legend1";
			series28->MarkerColor = System::Drawing::Color::Blue;
			series28->MarkerSize = 10;
			series28->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Cross;
			series28->Name = L"targets_wires";
			series29->BorderWidth = 3;
			series29->ChartArea = L"ChartArea1";
			series29->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series29->Color = System::Drawing::Color::Blue;
			series29->IsVisibleInLegend = false;
			series29->LabelAngle = 90;
			series29->Legend = L"Legend1";
			series29->MarkerColor = System::Drawing::Color::Magenta;
			series29->MarkerSize = 7;
			series29->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series29->Name = L"targets_pylons";
			this->PB_MAP_chart->Series->Add(series28);
			this->PB_MAP_chart->Series->Add(series29);
			this->PB_MAP_chart->Size = System::Drawing::Size(445, 362);
			this->PB_MAP_chart->TabIndex = 270;
			this->PB_MAP_chart->Text = L"chart1";
			// 
			// RADAR_VIEW
			// 
			this->RADAR_VIEW->BackColor = System::Drawing::Color::Black;
			this->RADAR_VIEW->Controls->Add(this->groupBox3);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_H_5);
			this->RADAR_VIEW->Controls->Add(this->groupBox86);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_V_5);
			this->RADAR_VIEW->Controls->Add(this->groupBox5);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_L_5);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_R_5);
			this->RADAR_VIEW->Controls->Add(this->B_RADAR_PLOT);
			this->RADAR_VIEW->Controls->Add(this->label152);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_R_1);
			this->RADAR_VIEW->Controls->Add(this->label153);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_L_1);
			this->RADAR_VIEW->Controls->Add(this->label154);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_V_1);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_H_4);
			this->RADAR_VIEW->Controls->Add(this->label155);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_V_4);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_H_1);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_L_4);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_R_2);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_R_4);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_L_2);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_V_2);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_H_2);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_R_3);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_POL_L_3);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_V_3);
			this->RADAR_VIEW->Controls->Add(this->B_TGT_AOA_H_3);
			this->RADAR_VIEW->Location = System::Drawing::Point(4, 22);
			this->RADAR_VIEW->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->RADAR_VIEW->Name = L"RADAR_VIEW";
			this->RADAR_VIEW->Size = System::Drawing::Size(828, 590);
			this->RADAR_VIEW->TabIndex = 4;
			this->RADAR_VIEW->Text = L"PPI Scope";
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::Transparent;
			this->groupBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->groupBox3->Controls->Add(this->textBox2);
			this->groupBox3->Controls->Add(this->T_VR_Noise);
			this->groupBox3->Controls->Add(this->label248);
			this->groupBox3->Controls->Add(this->T_HR_Noise);
			this->groupBox3->Controls->Add(this->label250);
			this->groupBox3->Controls->Add(this->T_VL_Noise);
			this->groupBox3->Controls->Add(this->T_HL_Noise);
			this->groupBox3->Controls->Add(this->label254);
			this->groupBox3->Controls->Add(this->label255);
			this->groupBox3->ForeColor = System::Drawing::Color::White;
			this->groupBox3->Location = System::Drawing::Point(352, 526);
			this->groupBox3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox3->Size = System::Drawing::Size(287, 66);
			this->groupBox3->TabIndex = 179;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"RDM Noise level [dB]";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->textBox2->Location = System::Drawing::Point(338, 212);
			this->textBox2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(66, 20);
			this->textBox2->TabIndex = 174;
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->textBox2->Visible = false;
			// 
			// T_VR_Noise
			// 
			this->T_VR_Noise->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->T_VR_Noise->Location = System::Drawing::Point(216, 32);
			this->T_VR_Noise->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->T_VR_Noise->Name = L"T_VR_Noise";
			this->T_VR_Noise->ReadOnly = true;
			this->T_VR_Noise->Size = System::Drawing::Size(66, 20);
			this->T_VR_Noise->TabIndex = 160;
			this->T_VR_Noise->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label248
			// 
			this->label248->AutoSize = true;
			this->label248->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label248->ForeColor = System::Drawing::Color::White;
			this->label248->Location = System::Drawing::Point(239, 12);
			this->label248->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label248->Name = L"label248";
			this->label248->Size = System::Drawing::Size(26, 15);
			this->label248->TabIndex = 159;
			this->label248->Text = L"VR:";
			// 
			// T_HR_Noise
			// 
			this->T_HR_Noise->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->T_HR_Noise->Location = System::Drawing::Point(146, 32);
			this->T_HR_Noise->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->T_HR_Noise->Name = L"T_HR_Noise";
			this->T_HR_Noise->ReadOnly = true;
			this->T_HR_Noise->Size = System::Drawing::Size(66, 20);
			this->T_HR_Noise->TabIndex = 135;
			this->T_HR_Noise->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label250
			// 
			this->label250->AutoSize = true;
			this->label250->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label250->ForeColor = System::Drawing::Color::White;
			this->label250->Location = System::Drawing::Point(166, 12);
			this->label250->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label250->Name = L"label250";
			this->label250->Size = System::Drawing::Size(28, 15);
			this->label250->TabIndex = 134;
			this->label250->Text = L"HR:";
			// 
			// T_VL_Noise
			// 
			this->T_VL_Noise->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->T_VL_Noise->Location = System::Drawing::Point(76, 32);
			this->T_VL_Noise->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->T_VL_Noise->Name = L"T_VL_Noise";
			this->T_VL_Noise->ReadOnly = true;
			this->T_VL_Noise->Size = System::Drawing::Size(66, 20);
			this->T_VL_Noise->TabIndex = 130;
			this->T_VL_Noise->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// T_HL_Noise
			// 
			this->T_HL_Noise->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->T_HL_Noise->Location = System::Drawing::Point(6, 32);
			this->T_HL_Noise->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->T_HL_Noise->Name = L"T_HL_Noise";
			this->T_HL_Noise->ReadOnly = true;
			this->T_HL_Noise->Size = System::Drawing::Size(66, 20);
			this->T_HL_Noise->TabIndex = 126;
			this->T_HL_Noise->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label254
			// 
			this->label254->AutoSize = true;
			this->label254->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label254->ForeColor = System::Drawing::Color::White;
			this->label254->Location = System::Drawing::Point(98, 12);
			this->label254->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label254->Name = L"label254";
			this->label254->Size = System::Drawing::Size(24, 15);
			this->label254->TabIndex = 122;
			this->label254->Text = L"VL:";
			// 
			// label255
			// 
			this->label255->AutoSize = true;
			this->label255->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label255->ForeColor = System::Drawing::Color::White;
			this->label255->Location = System::Drawing::Point(26, 12);
			this->label255->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label255->Name = L"label255";
			this->label255->Size = System::Drawing::Size(26, 15);
			this->label255->TabIndex = 121;
			this->label255->Text = L"HL:";
			// 
			// B_TGT_AOA_H_5
			// 
			this->B_TGT_AOA_H_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_H_5->Location = System::Drawing::Point(751, 497);
			this->B_TGT_AOA_H_5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_H_5->Name = L"B_TGT_AOA_H_5";
			this->B_TGT_AOA_H_5->ReadOnly = true;
			this->B_TGT_AOA_H_5->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_H_5->TabIndex = 178;
			this->B_TGT_AOA_H_5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_H_5->Visible = false;
			// 
			// groupBox86
			// 
			this->groupBox86->Controls->Add(this->F_POL_Target_selector);
			this->groupBox86->Controls->Add(this->label243);
			this->groupBox86->Controls->Add(this->label242);
			this->groupBox86->Controls->Add(this->POL_Copy);
			this->groupBox86->Controls->Add(this->Polarization_Box);
			this->groupBox86->ForeColor = System::Drawing::Color::White;
			this->groupBox86->Location = System::Drawing::Point(8, 3);
			this->groupBox86->Name = L"groupBox86";
			this->groupBox86->Size = System::Drawing::Size(223, 277);
			this->groupBox86->TabIndex = 15;
			this->groupBox86->TabStop = false;
			this->groupBox86->Text = L"Polarization";
			// 
			// F_POL_Target_selector
			// 
			this->F_POL_Target_selector->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_POL_Target_selector->Location = System::Drawing::Point(10, 244);
			this->F_POL_Target_selector->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_POL_Target_selector->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			this->F_POL_Target_selector->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->F_POL_Target_selector->Name = L"F_POL_Target_selector";
			this->F_POL_Target_selector->Size = System::Drawing::Size(63, 26);
			this->F_POL_Target_selector->TabIndex = 181;
			this->F_POL_Target_selector->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_POL_Target_selector->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// label243
			// 
			this->label243->AutoSize = true;
			this->label243->ForeColor = System::Drawing::Color::White;
			this->label243->Location = System::Drawing::Point(4, 227);
			this->label243->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label243->Name = L"label243";
			this->label243->Size = System::Drawing::Size(71, 13);
			this->label243->TabIndex = 180;
			this->label243->Text = L"Target Select";
			// 
			// label242
			// 
			this->label242->AutoSize = true;
			this->label242->ForeColor = System::Drawing::Color::White;
			this->label242->Location = System::Drawing::Point(79, 229);
			this->label242->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label242->Name = L"label242";
			this->label242->Size = System::Drawing::Size(55, 13);
			this->label242->TabIndex = 179;
			this->label242->Text = L"POL [deg]";
			// 
			// POL_Copy
			// 
			this->POL_Copy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->POL_Copy->Location = System::Drawing::Point(82, 245);
			this->POL_Copy->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->POL_Copy->Name = L"POL_Copy";
			this->POL_Copy->ReadOnly = true;
			this->POL_Copy->Size = System::Drawing::Size(66, 20);
			this->POL_Copy->TabIndex = 129;
			this->POL_Copy->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// Polarization_Box
			// 
			this->Polarization_Box->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Polarization_Box->Location = System::Drawing::Point(12, 19);
			this->Polarization_Box->Name = L"Polarization_Box";
			this->Polarization_Box->Size = System::Drawing::Size(200, 200);
			this->Polarization_Box->TabIndex = 0;
			this->Polarization_Box->TabStop = false;
			// 
			// B_TGT_AOA_V_5
			// 
			this->B_TGT_AOA_V_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_V_5->Location = System::Drawing::Point(751, 519);
			this->B_TGT_AOA_V_5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_V_5->Name = L"B_TGT_AOA_V_5";
			this->B_TGT_AOA_V_5->ReadOnly = true;
			this->B_TGT_AOA_V_5->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_V_5->TabIndex = 177;
			this->B_TGT_AOA_V_5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_V_5->Visible = false;
			// 
			// groupBox5
			// 
			this->groupBox5->BackColor = System::Drawing::Color::Transparent;
			this->groupBox5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->groupBox5->Controls->Add(this->B_TGT_VR_SNR_4);
			this->groupBox5->Controls->Add(this->B_TGT_HR_SNR_4);
			this->groupBox5->Controls->Add(this->B_TGT_VR_SNR_3);
			this->groupBox5->Controls->Add(this->B_TGT_VL_SNR_4);
			this->groupBox5->Controls->Add(this->B_TGT_VR_SNR_2);
			this->groupBox5->Controls->Add(this->B_TGT_HR_SNR_3);
			this->groupBox5->Controls->Add(this->B_TGT_VR_SNR_1);
			this->groupBox5->Controls->Add(this->B_TGT_HL_SNR_4);
			this->groupBox5->Controls->Add(this->label249);
			this->groupBox5->Controls->Add(this->B_TGT_HR_SNR_2);
			this->groupBox5->Controls->Add(this->B_TGT_VL_SNR_3);
			this->groupBox5->Controls->Add(this->B_TGT_HR_SNR_1);
			this->groupBox5->Controls->Add(this->B_TGT_RELIABILITY_5);
			this->groupBox5->Controls->Add(this->label247);
			this->groupBox5->Controls->Add(this->B_TGT_VL_SNR_2);
			this->groupBox5->Controls->Add(this->B_TGT_HL_SNR_3);
			this->groupBox5->Controls->Add(this->B_TGT_VL_SNR_1);
			this->groupBox5->Controls->Add(this->B_TGT_V_5);
			this->groupBox5->Controls->Add(this->label246);
			this->groupBox5->Controls->Add(this->B_TGT_HL_SNR_2);
			this->groupBox5->Controls->Add(this->B_TGT_P_5);
			this->groupBox5->Controls->Add(this->B_TGT_HL_SNR_1);
			this->groupBox5->Controls->Add(this->label245);
			this->groupBox5->Controls->Add(this->B_TGT_D_5);
			this->groupBox5->Controls->Add(this->B_TGT_R_5);
			this->groupBox5->Controls->Add(this->label157);
			this->groupBox5->Controls->Add(this->B_TGT_RELIABILITY_4);
			this->groupBox5->Controls->Add(this->B_TGT_V_4);
			this->groupBox5->Controls->Add(this->B_TGT_P_4);
			this->groupBox5->Controls->Add(this->B_TGT_D_4);
			this->groupBox5->Controls->Add(this->B_TGT_R_4);
			this->groupBox5->Controls->Add(this->label156);
			this->groupBox5->Controls->Add(this->B_TGT_RELIABILITY_3);
			this->groupBox5->Controls->Add(this->B_TGT_RELIABILITY_2);
			this->groupBox5->Controls->Add(this->B_TGT_RELIABILITY_1);
			this->groupBox5->Controls->Add(this->label151);
			this->groupBox5->Controls->Add(this->B_TGT_V_3);
			this->groupBox5->Controls->Add(this->B_TGT_P_3);
			this->groupBox5->Controls->Add(this->B_TGT_D_3);
			this->groupBox5->Controls->Add(this->B_TGT_R_3);
			this->groupBox5->Controls->Add(this->label37);
			this->groupBox5->Controls->Add(this->B_TGT_V_2);
			this->groupBox5->Controls->Add(this->B_TGT_P_2);
			this->groupBox5->Controls->Add(this->B_TGT_D_2);
			this->groupBox5->Controls->Add(this->B_TGT_R_2);
			this->groupBox5->Controls->Add(this->B_TGT_V_1);
			this->groupBox5->Controls->Add(this->B_TGT_P_1);
			this->groupBox5->Controls->Add(this->B_TGT_D_1);
			this->groupBox5->Controls->Add(this->B_TGT_R_1);
			this->groupBox5->Controls->Add(this->label36);
			this->groupBox5->Controls->Add(this->label35);
			this->groupBox5->Controls->Add(this->label34);
			this->groupBox5->Controls->Add(this->label33);
			this->groupBox5->Controls->Add(this->label23);
			this->groupBox5->Controls->Add(this->label4);
			this->groupBox5->ForeColor = System::Drawing::Color::White;
			this->groupBox5->Location = System::Drawing::Point(0, 320);
			this->groupBox5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox5->Size = System::Drawing::Size(340, 275);
			this->groupBox5->TabIndex = 14;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Targets";
			// 
			// B_TGT_VR_SNR_4
			// 
			this->B_TGT_VR_SNR_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_VR_SNR_4->Location = System::Drawing::Point(268, 218);
			this->B_TGT_VR_SNR_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_VR_SNR_4->Name = L"B_TGT_VR_SNR_4";
			this->B_TGT_VR_SNR_4->ReadOnly = true;
			this->B_TGT_VR_SNR_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_VR_SNR_4->TabIndex = 188;
			this->B_TGT_VR_SNR_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_HR_SNR_4
			// 
			this->B_TGT_HR_SNR_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_HR_SNR_4->Location = System::Drawing::Point(268, 193);
			this->B_TGT_HR_SNR_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_HR_SNR_4->Name = L"B_TGT_HR_SNR_4";
			this->B_TGT_HR_SNR_4->ReadOnly = true;
			this->B_TGT_HR_SNR_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_HR_SNR_4->TabIndex = 188;
			this->B_TGT_HR_SNR_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_VR_SNR_3
			// 
			this->B_TGT_VR_SNR_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_VR_SNR_3->Location = System::Drawing::Point(198, 218);
			this->B_TGT_VR_SNR_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_VR_SNR_3->Name = L"B_TGT_VR_SNR_3";
			this->B_TGT_VR_SNR_3->ReadOnly = true;
			this->B_TGT_VR_SNR_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_VR_SNR_3->TabIndex = 187;
			this->B_TGT_VR_SNR_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_VL_SNR_4
			// 
			this->B_TGT_VL_SNR_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_VL_SNR_4->Location = System::Drawing::Point(268, 168);
			this->B_TGT_VL_SNR_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_VL_SNR_4->Name = L"B_TGT_VL_SNR_4";
			this->B_TGT_VL_SNR_4->ReadOnly = true;
			this->B_TGT_VL_SNR_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_VL_SNR_4->TabIndex = 188;
			this->B_TGT_VL_SNR_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_VR_SNR_2
			// 
			this->B_TGT_VR_SNR_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_VR_SNR_2->Location = System::Drawing::Point(128, 218);
			this->B_TGT_VR_SNR_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_VR_SNR_2->Name = L"B_TGT_VR_SNR_2";
			this->B_TGT_VR_SNR_2->ReadOnly = true;
			this->B_TGT_VR_SNR_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_VR_SNR_2->TabIndex = 186;
			this->B_TGT_VR_SNR_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_HR_SNR_3
			// 
			this->B_TGT_HR_SNR_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_HR_SNR_3->Location = System::Drawing::Point(198, 193);
			this->B_TGT_HR_SNR_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_HR_SNR_3->Name = L"B_TGT_HR_SNR_3";
			this->B_TGT_HR_SNR_3->ReadOnly = true;
			this->B_TGT_HR_SNR_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_HR_SNR_3->TabIndex = 187;
			this->B_TGT_HR_SNR_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_VR_SNR_1
			// 
			this->B_TGT_VR_SNR_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_VR_SNR_1->Location = System::Drawing::Point(58, 218);
			this->B_TGT_VR_SNR_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_VR_SNR_1->Name = L"B_TGT_VR_SNR_1";
			this->B_TGT_VR_SNR_1->ReadOnly = true;
			this->B_TGT_VR_SNR_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_VR_SNR_1->TabIndex = 185;
			this->B_TGT_VR_SNR_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_HL_SNR_4
			// 
			this->B_TGT_HL_SNR_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_HL_SNR_4->Location = System::Drawing::Point(268, 141);
			this->B_TGT_HL_SNR_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_HL_SNR_4->Name = L"B_TGT_HL_SNR_4";
			this->B_TGT_HL_SNR_4->ReadOnly = true;
			this->B_TGT_HL_SNR_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_HL_SNR_4->TabIndex = 183;
			this->B_TGT_HL_SNR_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label249
			// 
			this->label249->AutoSize = true;
			this->label249->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label249->ForeColor = System::Drawing::Color::White;
			this->label249->Location = System::Drawing::Point(1, 221);
			this->label249->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label249->Name = L"label249";
			this->label249->Size = System::Drawing::Size(60, 12);
			this->label249->TabIndex = 184;
			this->label249->Text = L"SNR VR [dB]";
			// 
			// B_TGT_HR_SNR_2
			// 
			this->B_TGT_HR_SNR_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_HR_SNR_2->Location = System::Drawing::Point(128, 193);
			this->B_TGT_HR_SNR_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_HR_SNR_2->Name = L"B_TGT_HR_SNR_2";
			this->B_TGT_HR_SNR_2->ReadOnly = true;
			this->B_TGT_HR_SNR_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_HR_SNR_2->TabIndex = 186;
			this->B_TGT_HR_SNR_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_VL_SNR_3
			// 
			this->B_TGT_VL_SNR_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_VL_SNR_3->Location = System::Drawing::Point(198, 168);
			this->B_TGT_VL_SNR_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_VL_SNR_3->Name = L"B_TGT_VL_SNR_3";
			this->B_TGT_VL_SNR_3->ReadOnly = true;
			this->B_TGT_VL_SNR_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_VL_SNR_3->TabIndex = 187;
			this->B_TGT_VL_SNR_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_HR_SNR_1
			// 
			this->B_TGT_HR_SNR_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_HR_SNR_1->Location = System::Drawing::Point(58, 193);
			this->B_TGT_HR_SNR_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_HR_SNR_1->Name = L"B_TGT_HR_SNR_1";
			this->B_TGT_HR_SNR_1->ReadOnly = true;
			this->B_TGT_HR_SNR_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_HR_SNR_1->TabIndex = 185;
			this->B_TGT_HR_SNR_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_RELIABILITY_5
			// 
			this->B_TGT_RELIABILITY_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_RELIABILITY_5->Location = System::Drawing::Point(338, 212);
			this->B_TGT_RELIABILITY_5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_RELIABILITY_5->Name = L"B_TGT_RELIABILITY_5";
			this->B_TGT_RELIABILITY_5->ReadOnly = true;
			this->B_TGT_RELIABILITY_5->Size = System::Drawing::Size(66, 20);
			this->B_TGT_RELIABILITY_5->TabIndex = 174;
			this->B_TGT_RELIABILITY_5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_RELIABILITY_5->Visible = false;
			// 
			// label247
			// 
			this->label247->AutoSize = true;
			this->label247->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label247->ForeColor = System::Drawing::Color::White;
			this->label247->Location = System::Drawing::Point(1, 196);
			this->label247->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label247->Name = L"label247";
			this->label247->Size = System::Drawing::Size(60, 12);
			this->label247->TabIndex = 184;
			this->label247->Text = L"SNR HR [dB]";
			// 
			// B_TGT_VL_SNR_2
			// 
			this->B_TGT_VL_SNR_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_VL_SNR_2->Location = System::Drawing::Point(128, 168);
			this->B_TGT_VL_SNR_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_VL_SNR_2->Name = L"B_TGT_VL_SNR_2";
			this->B_TGT_VL_SNR_2->ReadOnly = true;
			this->B_TGT_VL_SNR_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_VL_SNR_2->TabIndex = 186;
			this->B_TGT_VL_SNR_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_HL_SNR_3
			// 
			this->B_TGT_HL_SNR_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_HL_SNR_3->Location = System::Drawing::Point(198, 141);
			this->B_TGT_HL_SNR_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_HL_SNR_3->Name = L"B_TGT_HL_SNR_3";
			this->B_TGT_HL_SNR_3->ReadOnly = true;
			this->B_TGT_HL_SNR_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_HL_SNR_3->TabIndex = 182;
			this->B_TGT_HL_SNR_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_VL_SNR_1
			// 
			this->B_TGT_VL_SNR_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_VL_SNR_1->Location = System::Drawing::Point(58, 168);
			this->B_TGT_VL_SNR_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_VL_SNR_1->Name = L"B_TGT_VL_SNR_1";
			this->B_TGT_VL_SNR_1->ReadOnly = true;
			this->B_TGT_VL_SNR_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_VL_SNR_1->TabIndex = 185;
			this->B_TGT_VL_SNR_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_V_5
			// 
			this->B_TGT_V_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_V_5->Location = System::Drawing::Point(338, 92);
			this->B_TGT_V_5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_V_5->Name = L"B_TGT_V_5";
			this->B_TGT_V_5->ReadOnly = true;
			this->B_TGT_V_5->Size = System::Drawing::Size(66, 20);
			this->B_TGT_V_5->TabIndex = 173;
			this->B_TGT_V_5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_V_5->Visible = false;
			// 
			// label246
			// 
			this->label246->AutoSize = true;
			this->label246->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label246->ForeColor = System::Drawing::Color::White;
			this->label246->Location = System::Drawing::Point(3, 171);
			this->label246->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label246->Name = L"label246";
			this->label246->Size = System::Drawing::Size(58, 12);
			this->label246->TabIndex = 184;
			this->label246->Text = L"SNR VL [dB]";
			// 
			// B_TGT_HL_SNR_2
			// 
			this->B_TGT_HL_SNR_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_HL_SNR_2->Location = System::Drawing::Point(128, 141);
			this->B_TGT_HL_SNR_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_HL_SNR_2->Name = L"B_TGT_HL_SNR_2";
			this->B_TGT_HL_SNR_2->ReadOnly = true;
			this->B_TGT_HL_SNR_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_HL_SNR_2->TabIndex = 181;
			this->B_TGT_HL_SNR_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_P_5
			// 
			this->B_TGT_P_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_P_5->Location = System::Drawing::Point(338, 71);
			this->B_TGT_P_5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_P_5->Name = L"B_TGT_P_5";
			this->B_TGT_P_5->ReadOnly = true;
			this->B_TGT_P_5->Size = System::Drawing::Size(66, 20);
			this->B_TGT_P_5->TabIndex = 172;
			this->B_TGT_P_5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_P_5->Visible = false;
			// 
			// B_TGT_HL_SNR_1
			// 
			this->B_TGT_HL_SNR_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_HL_SNR_1->Location = System::Drawing::Point(58, 141);
			this->B_TGT_HL_SNR_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_HL_SNR_1->Name = L"B_TGT_HL_SNR_1";
			this->B_TGT_HL_SNR_1->ReadOnly = true;
			this->B_TGT_HL_SNR_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_HL_SNR_1->TabIndex = 180;
			this->B_TGT_HL_SNR_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label245
			// 
			this->label245->AutoSize = true;
			this->label245->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label245->ForeColor = System::Drawing::Color::White;
			this->label245->Location = System::Drawing::Point(2, 145);
			this->label245->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label245->Name = L"label245";
			this->label245->Size = System::Drawing::Size(58, 12);
			this->label245->TabIndex = 179;
			this->label245->Text = L"SNR HL [dB]";
			// 
			// B_TGT_D_5
			// 
			this->B_TGT_D_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_D_5->Location = System::Drawing::Point(338, 51);
			this->B_TGT_D_5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_D_5->Name = L"B_TGT_D_5";
			this->B_TGT_D_5->ReadOnly = true;
			this->B_TGT_D_5->Size = System::Drawing::Size(66, 20);
			this->B_TGT_D_5->TabIndex = 171;
			this->B_TGT_D_5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_D_5->Visible = false;
			// 
			// B_TGT_R_5
			// 
			this->B_TGT_R_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_R_5->Location = System::Drawing::Point(338, 30);
			this->B_TGT_R_5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_R_5->Name = L"B_TGT_R_5";
			this->B_TGT_R_5->ReadOnly = true;
			this->B_TGT_R_5->Size = System::Drawing::Size(66, 20);
			this->B_TGT_R_5->TabIndex = 170;
			this->B_TGT_R_5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_R_5->Visible = false;
			// 
			// label157
			// 
			this->label157->AutoSize = true;
			this->label157->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label157->ForeColor = System::Drawing::Color::White;
			this->label157->Location = System::Drawing::Point(344, 9);
			this->label157->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label157->Name = L"label157";
			this->label157->Size = System::Drawing::Size(55, 15);
			this->label157->TabIndex = 169;
			this->label157->Text = L"Target 5:";
			this->label157->Visible = false;
			// 
			// B_TGT_RELIABILITY_4
			// 
			this->B_TGT_RELIABILITY_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_RELIABILITY_4->Location = System::Drawing::Point(268, 242);
			this->B_TGT_RELIABILITY_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_RELIABILITY_4->Name = L"B_TGT_RELIABILITY_4";
			this->B_TGT_RELIABILITY_4->ReadOnly = true;
			this->B_TGT_RELIABILITY_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_RELIABILITY_4->TabIndex = 164;
			this->B_TGT_RELIABILITY_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_V_4
			// 
			this->B_TGT_V_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_V_4->Location = System::Drawing::Point(268, 114);
			this->B_TGT_V_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_V_4->Name = L"B_TGT_V_4";
			this->B_TGT_V_4->ReadOnly = true;
			this->B_TGT_V_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_V_4->TabIndex = 163;
			this->B_TGT_V_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_P_4
			// 
			this->B_TGT_P_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_P_4->Location = System::Drawing::Point(268, 86);
			this->B_TGT_P_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_P_4->Name = L"B_TGT_P_4";
			this->B_TGT_P_4->ReadOnly = true;
			this->B_TGT_P_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_P_4->TabIndex = 162;
			this->B_TGT_P_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_D_4
			// 
			this->B_TGT_D_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_D_4->Location = System::Drawing::Point(268, 58);
			this->B_TGT_D_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_D_4->Name = L"B_TGT_D_4";
			this->B_TGT_D_4->ReadOnly = true;
			this->B_TGT_D_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_D_4->TabIndex = 161;
			this->B_TGT_D_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_R_4
			// 
			this->B_TGT_R_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_R_4->Location = System::Drawing::Point(268, 30);
			this->B_TGT_R_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_R_4->Name = L"B_TGT_R_4";
			this->B_TGT_R_4->ReadOnly = true;
			this->B_TGT_R_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_R_4->TabIndex = 160;
			this->B_TGT_R_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label156
			// 
			this->label156->AutoSize = true;
			this->label156->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label156->ForeColor = System::Drawing::Color::White;
			this->label156->Location = System::Drawing::Point(275, 9);
			this->label156->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label156->Name = L"label156";
			this->label156->Size = System::Drawing::Size(55, 15);
			this->label156->TabIndex = 159;
			this->label156->Text = L"Target 4:";
			// 
			// B_TGT_RELIABILITY_3
			// 
			this->B_TGT_RELIABILITY_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_RELIABILITY_3->Location = System::Drawing::Point(198, 242);
			this->B_TGT_RELIABILITY_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_RELIABILITY_3->Name = L"B_TGT_RELIABILITY_3";
			this->B_TGT_RELIABILITY_3->ReadOnly = true;
			this->B_TGT_RELIABILITY_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_RELIABILITY_3->TabIndex = 154;
			this->B_TGT_RELIABILITY_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_RELIABILITY_2
			// 
			this->B_TGT_RELIABILITY_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_RELIABILITY_2->Location = System::Drawing::Point(128, 242);
			this->B_TGT_RELIABILITY_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_RELIABILITY_2->Name = L"B_TGT_RELIABILITY_2";
			this->B_TGT_RELIABILITY_2->ReadOnly = true;
			this->B_TGT_RELIABILITY_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_RELIABILITY_2->TabIndex = 149;
			this->B_TGT_RELIABILITY_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_RELIABILITY_1
			// 
			this->B_TGT_RELIABILITY_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_RELIABILITY_1->Location = System::Drawing::Point(58, 242);
			this->B_TGT_RELIABILITY_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_RELIABILITY_1->Name = L"B_TGT_RELIABILITY_1";
			this->B_TGT_RELIABILITY_1->ReadOnly = true;
			this->B_TGT_RELIABILITY_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_RELIABILITY_1->TabIndex = 140;
			this->B_TGT_RELIABILITY_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label151
			// 
			this->label151->AutoSize = true;
			this->label151->ForeColor = System::Drawing::Color::White;
			this->label151->Location = System::Drawing::Point(3, 244);
			this->label151->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label151->Name = L"label151";
			this->label151->Size = System::Drawing::Size(51, 13);
			this->label151->TabIndex = 139;
			this->label151->Text = L"Reliability";
			// 
			// B_TGT_V_3
			// 
			this->B_TGT_V_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_V_3->Location = System::Drawing::Point(198, 114);
			this->B_TGT_V_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_V_3->Name = L"B_TGT_V_3";
			this->B_TGT_V_3->ReadOnly = true;
			this->B_TGT_V_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_V_3->TabIndex = 138;
			this->B_TGT_V_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_P_3
			// 
			this->B_TGT_P_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_P_3->Location = System::Drawing::Point(198, 86);
			this->B_TGT_P_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_P_3->Name = L"B_TGT_P_3";
			this->B_TGT_P_3->ReadOnly = true;
			this->B_TGT_P_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_P_3->TabIndex = 137;
			this->B_TGT_P_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_D_3
			// 
			this->B_TGT_D_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_D_3->Location = System::Drawing::Point(198, 58);
			this->B_TGT_D_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_D_3->Name = L"B_TGT_D_3";
			this->B_TGT_D_3->ReadOnly = true;
			this->B_TGT_D_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_D_3->TabIndex = 136;
			this->B_TGT_D_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_R_3
			// 
			this->B_TGT_R_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_R_3->Location = System::Drawing::Point(198, 30);
			this->B_TGT_R_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_R_3->Name = L"B_TGT_R_3";
			this->B_TGT_R_3->ReadOnly = true;
			this->B_TGT_R_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_R_3->TabIndex = 135;
			this->B_TGT_R_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label37->ForeColor = System::Drawing::Color::White;
			this->label37->Location = System::Drawing::Point(205, 9);
			this->label37->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(55, 15);
			this->label37->TabIndex = 134;
			this->label37->Text = L"Target 3:";
			// 
			// B_TGT_V_2
			// 
			this->B_TGT_V_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_V_2->Location = System::Drawing::Point(128, 114);
			this->B_TGT_V_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_V_2->Name = L"B_TGT_V_2";
			this->B_TGT_V_2->ReadOnly = true;
			this->B_TGT_V_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_V_2->TabIndex = 133;
			this->B_TGT_V_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_P_2
			// 
			this->B_TGT_P_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_P_2->Location = System::Drawing::Point(128, 86);
			this->B_TGT_P_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_P_2->Name = L"B_TGT_P_2";
			this->B_TGT_P_2->ReadOnly = true;
			this->B_TGT_P_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_P_2->TabIndex = 132;
			this->B_TGT_P_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_D_2
			// 
			this->B_TGT_D_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_D_2->Location = System::Drawing::Point(128, 58);
			this->B_TGT_D_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_D_2->Name = L"B_TGT_D_2";
			this->B_TGT_D_2->ReadOnly = true;
			this->B_TGT_D_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_D_2->TabIndex = 131;
			this->B_TGT_D_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_R_2
			// 
			this->B_TGT_R_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_R_2->Location = System::Drawing::Point(128, 30);
			this->B_TGT_R_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_R_2->Name = L"B_TGT_R_2";
			this->B_TGT_R_2->ReadOnly = true;
			this->B_TGT_R_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_R_2->TabIndex = 130;
			this->B_TGT_R_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_V_1
			// 
			this->B_TGT_V_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_V_1->Location = System::Drawing::Point(58, 114);
			this->B_TGT_V_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_V_1->Name = L"B_TGT_V_1";
			this->B_TGT_V_1->ReadOnly = true;
			this->B_TGT_V_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_V_1->TabIndex = 129;
			this->B_TGT_V_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_P_1
			// 
			this->B_TGT_P_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_P_1->Location = System::Drawing::Point(58, 86);
			this->B_TGT_P_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_P_1->Name = L"B_TGT_P_1";
			this->B_TGT_P_1->ReadOnly = true;
			this->B_TGT_P_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_P_1->TabIndex = 128;
			this->B_TGT_P_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_D_1
			// 
			this->B_TGT_D_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_D_1->Location = System::Drawing::Point(58, 58);
			this->B_TGT_D_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_D_1->Name = L"B_TGT_D_1";
			this->B_TGT_D_1->ReadOnly = true;
			this->B_TGT_D_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_D_1->TabIndex = 127;
			this->B_TGT_D_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TGT_R_1
			// 
			this->B_TGT_R_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_R_1->Location = System::Drawing::Point(58, 30);
			this->B_TGT_R_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_R_1->Name = L"B_TGT_R_1";
			this->B_TGT_R_1->ReadOnly = true;
			this->B_TGT_R_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_R_1->TabIndex = 126;
			this->B_TGT_R_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->ForeColor = System::Drawing::Color::White;
			this->label36->Location = System::Drawing::Point(7, 116);
			this->label36->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(52, 13);
			this->label36->TabIndex = 125;
			this->label36->Text = L"Vel. [m/s]";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->ForeColor = System::Drawing::Color::White;
			this->label35->Location = System::Drawing::Point(0, 30);
			this->label35->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(56, 13);
			this->label35->TabIndex = 124;
			this->label35->Text = L"Range [m]";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->ForeColor = System::Drawing::Color::White;
			this->label34->Location = System::Drawing::Point(4, 86);
			this->label34->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(55, 13);
			this->label34->TabIndex = 123;
			this->label34->Text = L"POL [deg]";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label33->ForeColor = System::Drawing::Color::White;
			this->label33->Location = System::Drawing::Point(133, 9);
			this->label33->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(55, 15);
			this->label33->TabIndex = 122;
			this->label33->Text = L"Target 2:";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->ForeColor = System::Drawing::Color::White;
			this->label23->Location = System::Drawing::Point(62, 9);
			this->label23->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(55, 15);
			this->label23->TabIndex = 121;
			this->label23->Text = L"Target 1:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(0, 59);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(57, 13);
			this->label4->TabIndex = 120;
			this->label4->Text = L"DOA [deg]";
			// 
			// B_TGT_POL_L_5
			// 
			this->B_TGT_POL_L_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_L_5->Location = System::Drawing::Point(751, 543);
			this->B_TGT_POL_L_5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_L_5->Name = L"B_TGT_POL_L_5";
			this->B_TGT_POL_L_5->ReadOnly = true;
			this->B_TGT_POL_L_5->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_L_5->TabIndex = 176;
			this->B_TGT_POL_L_5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_L_5->Visible = false;
			// 
			// B_TGT_POL_R_5
			// 
			this->B_TGT_POL_R_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_R_5->Location = System::Drawing::Point(751, 563);
			this->B_TGT_POL_R_5->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_R_5->Name = L"B_TGT_POL_R_5";
			this->B_TGT_POL_R_5->ReadOnly = true;
			this->B_TGT_POL_R_5->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_R_5->TabIndex = 175;
			this->B_TGT_POL_R_5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_R_5->Visible = false;
			// 
			// B_RADAR_PLOT
			// 
			this->B_RADAR_PLOT->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->B_RADAR_PLOT->BackColor = System::Drawing::Color::Black;
			chartArea12->AlignmentOrientation = System::Windows::Forms::DataVisualization::Charting::AreaAlignmentOrientations::Horizontal;
			chartArea12->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea12->AxisX->IsMarksNextToAxis = false;
			chartArea12->AxisX->LabelStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			chartArea12->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea12->AxisX->LineColor = System::Drawing::Color::White;
			chartArea12->AxisX->LineWidth = 2;
			chartArea12->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea12->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea12->AxisX->Maximum = 180;
			chartArea12->AxisX->Minimum = -180;
			chartArea12->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea12->AxisY->Interval = 250;
			chartArea12->AxisY->IsLabelAutoFit = false;
			chartArea12->AxisY->LabelStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea12->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea12->AxisY->LineColor = System::Drawing::Color::White;
			chartArea12->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea12->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea12->AxisY->Maximum = 1000;
			chartArea12->AxisY->Minimum = 0;
			chartArea12->AxisY->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea12->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea12->BackColor = System::Drawing::Color::Black;
			chartArea12->Name = L"ChartArea1";
			chartArea12->Position->Auto = false;
			chartArea12->Position->Height = 95;
			chartArea12->Position->Width = 95;
			chartArea12->Position->X = 5;
			this->B_RADAR_PLOT->ChartAreas->Add(chartArea12);
			legend9->Enabled = false;
			legend9->Name = L"Legend1";
			this->B_RADAR_PLOT->Legends->Add(legend9);
			this->B_RADAR_PLOT->Location = System::Drawing::Point(278, 1);
			this->B_RADAR_PLOT->Margin = System::Windows::Forms::Padding(0);
			this->B_RADAR_PLOT->Name = L"B_RADAR_PLOT";
			series30->BorderWidth = 3;
			series30->ChartArea = L"ChartArea1";
			series30->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Polar;
			series30->Color = System::Drawing::Color::Yellow;
			series30->CustomProperties = L"EmptyPointValue=Zero";
			series30->IsVisibleInLegend = false;
			series30->LabelAngle = 90;
			series30->Legend = L"Legend1";
			series30->MarkerColor = System::Drawing::Color::Red;
			series30->Name = L"Wires";
			this->B_RADAR_PLOT->Series->Add(series30);
			this->B_RADAR_PLOT->Size = System::Drawing::Size(552, 537);
			this->B_RADAR_PLOT->TabIndex = 0;
			this->B_RADAR_PLOT->Text = L"chart1";
			// 
			// label152
			// 
			this->label152->AutoSize = true;
			this->label152->ForeColor = System::Drawing::Color::White;
			this->label152->Location = System::Drawing::Point(419, 568);
			this->label152->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label152->Name = L"label152";
			this->label152->Size = System::Drawing::Size(39, 13);
			this->label152->TabIndex = 141;
			this->label152->Text = L"POL R";
			this->label152->Visible = false;
			// 
			// B_TGT_POL_R_1
			// 
			this->B_TGT_POL_R_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_R_1->Location = System::Drawing::Point(471, 563);
			this->B_TGT_POL_R_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_R_1->Name = L"B_TGT_POL_R_1";
			this->B_TGT_POL_R_1->ReadOnly = true;
			this->B_TGT_POL_R_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_R_1->TabIndex = 142;
			this->B_TGT_POL_R_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_R_1->Visible = false;
			// 
			// label153
			// 
			this->label153->AutoSize = true;
			this->label153->ForeColor = System::Drawing::Color::White;
			this->label153->Location = System::Drawing::Point(419, 547);
			this->label153->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label153->Name = L"label153";
			this->label153->Size = System::Drawing::Size(37, 13);
			this->label153->TabIndex = 143;
			this->label153->Text = L"POL L";
			this->label153->Visible = false;
			// 
			// B_TGT_POL_L_1
			// 
			this->B_TGT_POL_L_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_L_1->Location = System::Drawing::Point(471, 543);
			this->B_TGT_POL_L_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_L_1->Name = L"B_TGT_POL_L_1";
			this->B_TGT_POL_L_1->ReadOnly = true;
			this->B_TGT_POL_L_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_L_1->TabIndex = 144;
			this->B_TGT_POL_L_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_L_1->Visible = false;
			// 
			// label154
			// 
			this->label154->AutoSize = true;
			this->label154->ForeColor = System::Drawing::Color::White;
			this->label154->Location = System::Drawing::Point(419, 521);
			this->label154->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label154->Name = L"label154";
			this->label154->Size = System::Drawing::Size(37, 13);
			this->label154->TabIndex = 145;
			this->label154->Text = L"AoA V";
			this->label154->Visible = false;
			// 
			// B_TGT_AOA_V_1
			// 
			this->B_TGT_AOA_V_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_V_1->Location = System::Drawing::Point(471, 519);
			this->B_TGT_AOA_V_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_V_1->Name = L"B_TGT_AOA_V_1";
			this->B_TGT_AOA_V_1->ReadOnly = true;
			this->B_TGT_AOA_V_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_V_1->TabIndex = 146;
			this->B_TGT_AOA_V_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_V_1->Visible = false;
			// 
			// B_TGT_AOA_H_4
			// 
			this->B_TGT_AOA_H_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_H_4->Location = System::Drawing::Point(682, 497);
			this->B_TGT_AOA_H_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_H_4->Name = L"B_TGT_AOA_H_4";
			this->B_TGT_AOA_H_4->ReadOnly = true;
			this->B_TGT_AOA_H_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_H_4->TabIndex = 168;
			this->B_TGT_AOA_H_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_H_4->Visible = false;
			// 
			// label155
			// 
			this->label155->AutoSize = true;
			this->label155->ForeColor = System::Drawing::Color::White;
			this->label155->Location = System::Drawing::Point(419, 501);
			this->label155->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label155->Name = L"label155";
			this->label155->Size = System::Drawing::Size(38, 13);
			this->label155->TabIndex = 147;
			this->label155->Text = L"AoA H";
			this->label155->Visible = false;
			// 
			// B_TGT_AOA_V_4
			// 
			this->B_TGT_AOA_V_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_V_4->Location = System::Drawing::Point(682, 519);
			this->B_TGT_AOA_V_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_V_4->Name = L"B_TGT_AOA_V_4";
			this->B_TGT_AOA_V_4->ReadOnly = true;
			this->B_TGT_AOA_V_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_V_4->TabIndex = 167;
			this->B_TGT_AOA_V_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_V_4->Visible = false;
			// 
			// B_TGT_AOA_H_1
			// 
			this->B_TGT_AOA_H_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_H_1->Location = System::Drawing::Point(471, 497);
			this->B_TGT_AOA_H_1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_H_1->Name = L"B_TGT_AOA_H_1";
			this->B_TGT_AOA_H_1->ReadOnly = true;
			this->B_TGT_AOA_H_1->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_H_1->TabIndex = 148;
			this->B_TGT_AOA_H_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_H_1->Visible = false;
			// 
			// B_TGT_POL_L_4
			// 
			this->B_TGT_POL_L_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_L_4->Location = System::Drawing::Point(682, 543);
			this->B_TGT_POL_L_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_L_4->Name = L"B_TGT_POL_L_4";
			this->B_TGT_POL_L_4->ReadOnly = true;
			this->B_TGT_POL_L_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_L_4->TabIndex = 166;
			this->B_TGT_POL_L_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_L_4->Visible = false;
			// 
			// B_TGT_POL_R_2
			// 
			this->B_TGT_POL_R_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_R_2->Location = System::Drawing::Point(541, 563);
			this->B_TGT_POL_R_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_R_2->Name = L"B_TGT_POL_R_2";
			this->B_TGT_POL_R_2->ReadOnly = true;
			this->B_TGT_POL_R_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_R_2->TabIndex = 150;
			this->B_TGT_POL_R_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_R_2->Visible = false;
			// 
			// B_TGT_POL_R_4
			// 
			this->B_TGT_POL_R_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_R_4->Location = System::Drawing::Point(682, 563);
			this->B_TGT_POL_R_4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_R_4->Name = L"B_TGT_POL_R_4";
			this->B_TGT_POL_R_4->ReadOnly = true;
			this->B_TGT_POL_R_4->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_R_4->TabIndex = 165;
			this->B_TGT_POL_R_4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_R_4->Visible = false;
			// 
			// B_TGT_POL_L_2
			// 
			this->B_TGT_POL_L_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_L_2->Location = System::Drawing::Point(541, 543);
			this->B_TGT_POL_L_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_L_2->Name = L"B_TGT_POL_L_2";
			this->B_TGT_POL_L_2->ReadOnly = true;
			this->B_TGT_POL_L_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_L_2->TabIndex = 151;
			this->B_TGT_POL_L_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_L_2->Visible = false;
			// 
			// B_TGT_AOA_V_2
			// 
			this->B_TGT_AOA_V_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_V_2->Location = System::Drawing::Point(541, 519);
			this->B_TGT_AOA_V_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_V_2->Name = L"B_TGT_AOA_V_2";
			this->B_TGT_AOA_V_2->ReadOnly = true;
			this->B_TGT_AOA_V_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_V_2->TabIndex = 152;
			this->B_TGT_AOA_V_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_V_2->Visible = false;
			// 
			// B_TGT_AOA_H_2
			// 
			this->B_TGT_AOA_H_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_H_2->Location = System::Drawing::Point(541, 497);
			this->B_TGT_AOA_H_2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_H_2->Name = L"B_TGT_AOA_H_2";
			this->B_TGT_AOA_H_2->ReadOnly = true;
			this->B_TGT_AOA_H_2->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_H_2->TabIndex = 153;
			this->B_TGT_AOA_H_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_H_2->Visible = false;
			// 
			// B_TGT_POL_R_3
			// 
			this->B_TGT_POL_R_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_R_3->Location = System::Drawing::Point(612, 563);
			this->B_TGT_POL_R_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_R_3->Name = L"B_TGT_POL_R_3";
			this->B_TGT_POL_R_3->ReadOnly = true;
			this->B_TGT_POL_R_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_R_3->TabIndex = 155;
			this->B_TGT_POL_R_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_R_3->Visible = false;
			// 
			// B_TGT_POL_L_3
			// 
			this->B_TGT_POL_L_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_POL_L_3->Location = System::Drawing::Point(612, 543);
			this->B_TGT_POL_L_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_POL_L_3->Name = L"B_TGT_POL_L_3";
			this->B_TGT_POL_L_3->ReadOnly = true;
			this->B_TGT_POL_L_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_POL_L_3->TabIndex = 156;
			this->B_TGT_POL_L_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_POL_L_3->Visible = false;
			// 
			// B_TGT_AOA_V_3
			// 
			this->B_TGT_AOA_V_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_V_3->Location = System::Drawing::Point(612, 519);
			this->B_TGT_AOA_V_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_V_3->Name = L"B_TGT_AOA_V_3";
			this->B_TGT_AOA_V_3->ReadOnly = true;
			this->B_TGT_AOA_V_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_V_3->TabIndex = 157;
			this->B_TGT_AOA_V_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_V_3->Visible = false;
			// 
			// B_TGT_AOA_H_3
			// 
			this->B_TGT_AOA_H_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TGT_AOA_H_3->Location = System::Drawing::Point(612, 497);
			this->B_TGT_AOA_H_3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TGT_AOA_H_3->Name = L"B_TGT_AOA_H_3";
			this->B_TGT_AOA_H_3->ReadOnly = true;
			this->B_TGT_AOA_H_3->Size = System::Drawing::Size(66, 20);
			this->B_TGT_AOA_H_3->TabIndex = 158;
			this->B_TGT_AOA_H_3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_TGT_AOA_H_3->Visible = false;
			// 
			// Flash
			// 
			this->Flash->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->Flash->Controls->Add(this->B_RESET_ARC);
			this->Flash->Controls->Add(this->B_MAIN_config);
			this->Flash->Controls->Add(this->B_FLASH_WRITE_TO_FILE);
			this->Flash->Controls->Add(this->B_FLASH_READ_FROM_FILE);
			this->Flash->Controls->Add(this->B_FLASH_RETRIVE);
			this->Flash->Controls->Add(this->B_FLASH_WRITE);
			this->Flash->Controls->Add(this->B_FLASH_READ);
			this->Flash->Controls->Add(this->groupBox11);
			this->Flash->Controls->Add(this->groupBox7);
			this->Flash->Controls->Add(this->label98);
			this->Flash->Controls->Add(this->F_TxRx_control_MODE);
			this->Flash->Controls->Add(this->groupBox2);
			this->Flash->Controls->Add(this->F_SYSTEM_ID);
			this->Flash->Controls->Add(this->label72);
			this->Flash->Controls->Add(this->B_SENSOR_CONFIG);
			this->Flash->Controls->Add(this->groupBox6);
			this->Flash->Controls->Add(this->groupBox10);
			this->Flash->ForeColor = System::Drawing::Color::White;
			this->Flash->Location = System::Drawing::Point(4, 22);
			this->Flash->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->Flash->Name = L"Flash";
			this->Flash->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->Flash->Size = System::Drawing::Size(828, 590);
			this->Flash->TabIndex = 1;
			this->Flash->Text = L"Configuration";
			this->Flash->Click += gcnew System::EventHandler(this, &MyForm::Flash_Click);
			// 
			// B_RESET_ARC
			// 
			this->B_RESET_ARC->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_RESET_ARC->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_RESET_ARC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold));
			this->B_RESET_ARC->ForeColor = System::Drawing::Color::Black;
			this->B_RESET_ARC->Location = System::Drawing::Point(256, 519);
			this->B_RESET_ARC->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RESET_ARC->Name = L"B_RESET_ARC";
			this->B_RESET_ARC->Size = System::Drawing::Size(124, 38);
			this->B_RESET_ARC->TabIndex = 171;
			this->B_RESET_ARC->Text = L"Reset ARC";
			this->B_RESET_ARC->UseVisualStyleBackColor = false;
			this->B_RESET_ARC->Click += gcnew System::EventHandler(this, &MyForm::B_RESET_ARC_Click);
			// 
			// B_MAIN_config
			// 
			this->B_MAIN_config->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_MAIN_config->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_MAIN_config->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_MAIN_config->ForeColor = System::Drawing::Color::Black;
			this->B_MAIN_config->Location = System::Drawing::Point(421, 525);
			this->B_MAIN_config->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_MAIN_config->Name = L"B_MAIN_config";
			this->B_MAIN_config->Size = System::Drawing::Size(173, 53);
			this->B_MAIN_config->TabIndex = 29;
			this->B_MAIN_config->Text = L"CONFIGURE";
			this->B_MAIN_config->UseVisualStyleBackColor = false;
			this->B_MAIN_config->Click += gcnew System::EventHandler(this, &MyForm::B_MAIN_config_Click);
			// 
			// B_FLASH_WRITE_TO_FILE
			// 
			this->B_FLASH_WRITE_TO_FILE->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_FLASH_WRITE_TO_FILE->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_FLASH_WRITE_TO_FILE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_FLASH_WRITE_TO_FILE->ForeColor = System::Drawing::Color::Black;
			this->B_FLASH_WRITE_TO_FILE->Location = System::Drawing::Point(256, 201);
			this->B_FLASH_WRITE_TO_FILE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_FLASH_WRITE_TO_FILE->Name = L"B_FLASH_WRITE_TO_FILE";
			this->B_FLASH_WRITE_TO_FILE->Size = System::Drawing::Size(124, 38);
			this->B_FLASH_WRITE_TO_FILE->TabIndex = 29;
			this->B_FLASH_WRITE_TO_FILE->Text = L"Save to FILE";
			this->B_FLASH_WRITE_TO_FILE->UseVisualStyleBackColor = false;
			this->B_FLASH_WRITE_TO_FILE->Click += gcnew System::EventHandler(this, &MyForm::B_FLASH_WRITE_TO_FILE_Click);
			// 
			// B_FLASH_READ_FROM_FILE
			// 
			this->B_FLASH_READ_FROM_FILE->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_FLASH_READ_FROM_FILE->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_FLASH_READ_FROM_FILE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_FLASH_READ_FROM_FILE->ForeColor = System::Drawing::Color::Black;
			this->B_FLASH_READ_FROM_FILE->Location = System::Drawing::Point(256, 254);
			this->B_FLASH_READ_FROM_FILE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_FLASH_READ_FROM_FILE->Name = L"B_FLASH_READ_FROM_FILE";
			this->B_FLASH_READ_FROM_FILE->Size = System::Drawing::Size(124, 38);
			this->B_FLASH_READ_FROM_FILE->TabIndex = 29;
			this->B_FLASH_READ_FROM_FILE->Text = L"Read from FILE";
			this->B_FLASH_READ_FROM_FILE->UseVisualStyleBackColor = false;
			this->B_FLASH_READ_FROM_FILE->Click += gcnew System::EventHandler(this, &MyForm::B_FLASH_READ_FROM_FILE_Click);
			// 
			// B_FLASH_RETRIVE
			// 
			this->B_FLASH_RETRIVE->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_FLASH_RETRIVE->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_FLASH_RETRIVE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_FLASH_RETRIVE->ForeColor = System::Drawing::Color::Black;
			this->B_FLASH_RETRIVE->Location = System::Drawing::Point(256, 413);
			this->B_FLASH_RETRIVE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_FLASH_RETRIVE->Name = L"B_FLASH_RETRIVE";
			this->B_FLASH_RETRIVE->Size = System::Drawing::Size(124, 38);
			this->B_FLASH_RETRIVE->TabIndex = 29;
			this->B_FLASH_RETRIVE->Text = L"Retrive from status";
			this->B_FLASH_RETRIVE->UseVisualStyleBackColor = false;
			this->B_FLASH_RETRIVE->Click += gcnew System::EventHandler(this, &MyForm::B_FLASH_RETRIVE_Click);
			// 
			// B_FLASH_WRITE
			// 
			this->B_FLASH_WRITE->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_FLASH_WRITE->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_FLASH_WRITE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_FLASH_WRITE->ForeColor = System::Drawing::Color::Black;
			this->B_FLASH_WRITE->Location = System::Drawing::Point(256, 307);
			this->B_FLASH_WRITE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_FLASH_WRITE->Name = L"B_FLASH_WRITE";
			this->B_FLASH_WRITE->Size = System::Drawing::Size(124, 38);
			this->B_FLASH_WRITE->TabIndex = 29;
			this->B_FLASH_WRITE->Text = L"  Write to    FLASH";
			this->B_FLASH_WRITE->UseVisualStyleBackColor = false;
			this->B_FLASH_WRITE->Click += gcnew System::EventHandler(this, &MyForm::B_FLASH_WRITE_Click);
			// 
			// B_FLASH_READ
			// 
			this->B_FLASH_READ->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_FLASH_READ->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_FLASH_READ->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_FLASH_READ->ForeColor = System::Drawing::Color::Black;
			this->B_FLASH_READ->Location = System::Drawing::Point(256, 360);
			this->B_FLASH_READ->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_FLASH_READ->Name = L"B_FLASH_READ";
			this->B_FLASH_READ->Size = System::Drawing::Size(124, 38);
			this->B_FLASH_READ->TabIndex = 29;
			this->B_FLASH_READ->Text = L"Read from FLASH";
			this->B_FLASH_READ->UseVisualStyleBackColor = false;
			this->B_FLASH_READ->Click += gcnew System::EventHandler(this, &MyForm::B_FLASH_READ_Click);
			// 
			// groupBox11
			// 
			this->groupBox11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_CALIBRATE);
			this->groupBox11->Controls->Add(this->B_PROBE_CALIBRATE);
			this->groupBox11->Controls->Add(this->B_PROBE_RESET);
			this->groupBox11->Controls->Add(this->label177);
			this->groupBox11->Controls->Add(this->label176);
			this->groupBox11->Controls->Add(this->label175);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_RESET);
			this->groupBox11->Controls->Add(this->label171);
			this->groupBox11->Controls->Add(this->label170);
			this->groupBox11->Controls->Add(this->label118);
			this->groupBox11->Controls->Add(this->label117);
			this->groupBox11->Controls->Add(this->label174);
			this->groupBox11->Controls->Add(this->label173);
			this->groupBox11->Controls->Add(this->label172);
			this->groupBox11->Controls->Add(this->label136);
			this->groupBox11->Controls->Add(this->label137);
			this->groupBox11->Controls->Add(this->label165);
			this->groupBox11->Controls->Add(this->label169);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_RV_Q);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_RH_Q);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_LH_Q);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_LV_Q);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_RV_I);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_RH_I);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_LH_I);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_LV_I);
			this->groupBox11->Controls->Add(this->label145);
			this->groupBox11->Controls->Add(this->label144);
			this->groupBox11->Controls->Add(this->label143);
			this->groupBox11->Controls->Add(this->label142);
			this->groupBox11->Controls->Add(this->label141);
			this->groupBox11->Controls->Add(this->label140);
			this->groupBox11->Controls->Add(this->label139);
			this->groupBox11->Controls->Add(this->label138);
			this->groupBox11->Controls->Add(this->B_CORRECTION_RV_Q);
			this->groupBox11->Controls->Add(this->B_CORRECTION_RH_Q);
			this->groupBox11->Controls->Add(this->B_CORRECTION_LH_Q);
			this->groupBox11->Controls->Add(this->B_CORRECTION_LV_Q);
			this->groupBox11->Controls->Add(this->B_CORRECTION_RV_I);
			this->groupBox11->Controls->Add(this->B_CORRECTION_RH_I);
			this->groupBox11->Controls->Add(this->B_CORRECTION_LH_I);
			this->groupBox11->Controls->Add(this->B_CORRECTION_LV_I);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_TGT_END);
			this->groupBox11->Controls->Add(this->B_CALIBRATOR_TGT_START);
			this->groupBox11->Controls->Add(this->B_PROBE_CALIBRATE_TGT_START);
			this->groupBox11->Controls->Add(this->B_PROBE_CALIBRATE_TGT_END);
			this->groupBox11->ForeColor = System::Drawing::Color::White;
			this->groupBox11->Location = System::Drawing::Point(625, 6);
			this->groupBox11->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox11->Size = System::Drawing::Size(192, 573);
			this->groupBox11->TabIndex = 169;
			this->groupBox11->TabStop = false;
			this->groupBox11->Text = L"Calibration";
			// 
			// B_CALIBRATOR_CALIBRATE
			// 
			this->B_CALIBRATOR_CALIBRATE->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_CALIBRATOR_CALIBRATE->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_CALIBRATOR_CALIBRATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold));
			this->B_CALIBRATOR_CALIBRATE->ForeColor = System::Drawing::Color::Black;
			this->B_CALIBRATOR_CALIBRATE->Location = System::Drawing::Point(39, 453);
			this->B_CALIBRATOR_CALIBRATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_CALIBRATE->Name = L"B_CALIBRATOR_CALIBRATE";
			this->B_CALIBRATOR_CALIBRATE->Size = System::Drawing::Size(137, 45);
			this->B_CALIBRATOR_CALIBRATE->TabIndex = 154;
			this->B_CALIBRATOR_CALIBRATE->Text = L"Calibrate";
			this->B_CALIBRATOR_CALIBRATE->UseVisualStyleBackColor = false;
			this->B_CALIBRATOR_CALIBRATE->Click += gcnew System::EventHandler(this, &MyForm::B_CALIBRATOR_CALIBRATE_Click);
			// 
			// B_PROBE_CALIBRATE
			// 
			this->B_PROBE_CALIBRATE->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_PROBE_CALIBRATE->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_PROBE_CALIBRATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold));
			this->B_PROBE_CALIBRATE->ForeColor = System::Drawing::Color::Black;
			this->B_PROBE_CALIBRATE->Location = System::Drawing::Point(39, 333);
			this->B_PROBE_CALIBRATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PROBE_CALIBRATE->Name = L"B_PROBE_CALIBRATE";
			this->B_PROBE_CALIBRATE->Size = System::Drawing::Size(137, 45);
			this->B_PROBE_CALIBRATE->TabIndex = 156;
			this->B_PROBE_CALIBRATE->Text = L"Probe calibrate";
			this->B_PROBE_CALIBRATE->UseVisualStyleBackColor = false;
			this->B_PROBE_CALIBRATE->Click += gcnew System::EventHandler(this, &MyForm::B_PROBE_CALIBRATE_Click);
			// 
			// B_PROBE_RESET
			// 
			this->B_PROBE_RESET->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_PROBE_RESET->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_PROBE_RESET->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold));
			this->B_PROBE_RESET->ForeColor = System::Drawing::Color::Black;
			this->B_PROBE_RESET->Location = System::Drawing::Point(39, 393);
			this->B_PROBE_RESET->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PROBE_RESET->Name = L"B_PROBE_RESET";
			this->B_PROBE_RESET->Size = System::Drawing::Size(137, 45);
			this->B_PROBE_RESET->TabIndex = 156;
			this->B_PROBE_RESET->Text = L"Reset Probe \r\nCalibration";
			this->B_PROBE_RESET->UseVisualStyleBackColor = false;
			this->B_PROBE_RESET->Click += gcnew System::EventHandler(this, &MyForm::B_PROBE_RESET_Click);
			// 
			// label177
			// 
			this->label177->AutoSize = true;
			this->label177->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label177->ForeColor = System::Drawing::Color::White;
			this->label177->Location = System::Drawing::Point(103, 37);
			this->label177->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label177->Name = L"label177";
			this->label177->Size = System::Drawing::Size(18, 13);
			this->label177->TabIndex = 177;
			this->label177->Text = L"+ j";
			// 
			// label176
			// 
			this->label176->AutoSize = true;
			this->label176->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label176->ForeColor = System::Drawing::Color::White;
			this->label176->Location = System::Drawing::Point(103, 58);
			this->label176->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label176->Name = L"label176";
			this->label176->Size = System::Drawing::Size(18, 13);
			this->label176->TabIndex = 176;
			this->label176->Text = L"+ j";
			// 
			// label175
			// 
			this->label175->AutoSize = true;
			this->label175->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label175->ForeColor = System::Drawing::Color::White;
			this->label175->Location = System::Drawing::Point(103, 76);
			this->label175->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label175->Name = L"label175";
			this->label175->Size = System::Drawing::Size(18, 13);
			this->label175->TabIndex = 175;
			this->label175->Text = L"+ j";
			// 
			// B_CALIBRATOR_RESET
			// 
			this->B_CALIBRATOR_RESET->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_CALIBRATOR_RESET->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_CALIBRATOR_RESET->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold));
			this->B_CALIBRATOR_RESET->ForeColor = System::Drawing::Color::Black;
			this->B_CALIBRATOR_RESET->Location = System::Drawing::Point(39, 513);
			this->B_CALIBRATOR_RESET->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_RESET->Name = L"B_CALIBRATOR_RESET";
			this->B_CALIBRATOR_RESET->Size = System::Drawing::Size(137, 45);
			this->B_CALIBRATOR_RESET->TabIndex = 156;
			this->B_CALIBRATOR_RESET->Text = L"Reset Calibration";
			this->B_CALIBRATOR_RESET->UseVisualStyleBackColor = false;
			this->B_CALIBRATOR_RESET->Click += gcnew System::EventHandler(this, &MyForm::B_CALIBRATOR_RESET_Click);
			// 
			// label171
			// 
			this->label171->AutoSize = true;
			this->label171->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label171->ForeColor = System::Drawing::Color::White;
			this->label171->Location = System::Drawing::Point(103, 97);
			this->label171->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label171->Name = L"label171";
			this->label171->Size = System::Drawing::Size(18, 13);
			this->label171->TabIndex = 174;
			this->label171->Text = L"+ j";
			// 
			// label170
			// 
			this->label170->AutoSize = true;
			this->label170->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label170->ForeColor = System::Drawing::Color::White;
			this->label170->Location = System::Drawing::Point(103, 195);
			this->label170->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label170->Name = L"label170";
			this->label170->Size = System::Drawing::Size(18, 13);
			this->label170->TabIndex = 173;
			this->label170->Text = L"+ j";
			// 
			// label118
			// 
			this->label118->AutoSize = true;
			this->label118->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label118->ForeColor = System::Drawing::Color::White;
			this->label118->Location = System::Drawing::Point(103, 175);
			this->label118->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label118->Name = L"label118";
			this->label118->Size = System::Drawing::Size(18, 13);
			this->label118->TabIndex = 172;
			this->label118->Text = L"+ j";
			// 
			// label117
			// 
			this->label117->AutoSize = true;
			this->label117->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label117->ForeColor = System::Drawing::Color::White;
			this->label117->Location = System::Drawing::Point(103, 155);
			this->label117->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label117->Name = L"label117";
			this->label117->Size = System::Drawing::Size(18, 13);
			this->label117->TabIndex = 171;
			this->label117->Text = L"+ j";
			// 
			// label174
			// 
			this->label174->AutoSize = true;
			this->label174->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label174->ForeColor = System::Drawing::Color::White;
			this->label174->Location = System::Drawing::Point(103, 135);
			this->label174->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label174->Name = L"label174";
			this->label174->Size = System::Drawing::Size(18, 13);
			this->label174->TabIndex = 170;
			this->label174->Text = L"+ j";
			// 
			// label173
			// 
			this->label173->AutoSize = true;
			this->label173->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label173->ForeColor = System::Drawing::Color::White;
			this->label173->Location = System::Drawing::Point(39, 115);
			this->label173->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label173->Name = L"label173";
			this->label173->Size = System::Drawing::Size(131, 13);
			this->label173->TabIndex = 169;
			this->label173->Text = L"Target clibration (complex)";
			// 
			// label172
			// 
			this->label172->AutoSize = true;
			this->label172->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label172->ForeColor = System::Drawing::Color::White;
			this->label172->Location = System::Drawing::Point(44, 16);
			this->label172->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label172->Name = L"label172";
			this->label172->Size = System::Drawing::Size(121, 13);
			this->label172->TabIndex = 168;
			this->label172->Text = L"Rx_correction (complex)";
			// 
			// label136
			// 
			this->label136->AutoSize = true;
			this->label136->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label136->ForeColor = System::Drawing::Color::White;
			this->label136->Location = System::Drawing::Point(23, 155);
			this->label136->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label136->Name = L"label136";
			this->label136->Size = System::Drawing::Size(23, 13);
			this->label136->TabIndex = 167;
			this->label136->Text = L"L-V";
			// 
			// label137
			// 
			this->label137->AutoSize = true;
			this->label137->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label137->ForeColor = System::Drawing::Color::White;
			this->label137->Location = System::Drawing::Point(20, 175);
			this->label137->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label137->Name = L"label137";
			this->label137->Size = System::Drawing::Size(26, 13);
			this->label137->TabIndex = 166;
			this->label137->Text = L"R-H";
			// 
			// label165
			// 
			this->label165->AutoSize = true;
			this->label165->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label165->ForeColor = System::Drawing::Color::White;
			this->label165->Location = System::Drawing::Point(22, 135);
			this->label165->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label165->Name = L"label165";
			this->label165->Size = System::Drawing::Size(24, 13);
			this->label165->TabIndex = 165;
			this->label165->Text = L"L-H";
			// 
			// label169
			// 
			this->label169->AutoSize = true;
			this->label169->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label169->ForeColor = System::Drawing::Color::White;
			this->label169->Location = System::Drawing::Point(21, 197);
			this->label169->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label169->Name = L"label169";
			this->label169->Size = System::Drawing::Size(25, 13);
			this->label169->TabIndex = 164;
			this->label169->Text = L"R-V";
			// 
			// B_CALIBRATOR_RV_Q
			// 
			this->B_CALIBRATOR_RV_Q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_RV_Q->Location = System::Drawing::Point(122, 193);
			this->B_CALIBRATOR_RV_Q->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_RV_Q->Name = L"B_CALIBRATOR_RV_Q";
			this->B_CALIBRATOR_RV_Q->ReadOnly = true;
			this->B_CALIBRATOR_RV_Q->Size = System::Drawing::Size(54, 20);
			this->B_CALIBRATOR_RV_Q->TabIndex = 161;
			this->B_CALIBRATOR_RV_Q->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CALIBRATOR_RH_Q
			// 
			this->B_CALIBRATOR_RH_Q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_RH_Q->Location = System::Drawing::Point(122, 172);
			this->B_CALIBRATOR_RH_Q->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_RH_Q->Name = L"B_CALIBRATOR_RH_Q";
			this->B_CALIBRATOR_RH_Q->ReadOnly = true;
			this->B_CALIBRATOR_RH_Q->Size = System::Drawing::Size(54, 20);
			this->B_CALIBRATOR_RH_Q->TabIndex = 160;
			this->B_CALIBRATOR_RH_Q->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CALIBRATOR_LH_Q
			// 
			this->B_CALIBRATOR_LH_Q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_LH_Q->Location = System::Drawing::Point(122, 132);
			this->B_CALIBRATOR_LH_Q->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_LH_Q->Name = L"B_CALIBRATOR_LH_Q";
			this->B_CALIBRATOR_LH_Q->ReadOnly = true;
			this->B_CALIBRATOR_LH_Q->Size = System::Drawing::Size(54, 20);
			this->B_CALIBRATOR_LH_Q->TabIndex = 158;
			this->B_CALIBRATOR_LH_Q->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CALIBRATOR_LV_Q
			// 
			this->B_CALIBRATOR_LV_Q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_LV_Q->Location = System::Drawing::Point(122, 152);
			this->B_CALIBRATOR_LV_Q->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_LV_Q->Name = L"B_CALIBRATOR_LV_Q";
			this->B_CALIBRATOR_LV_Q->ReadOnly = true;
			this->B_CALIBRATOR_LV_Q->Size = System::Drawing::Size(54, 20);
			this->B_CALIBRATOR_LV_Q->TabIndex = 159;
			this->B_CALIBRATOR_LV_Q->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CALIBRATOR_RV_I
			// 
			this->B_CALIBRATOR_RV_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_RV_I->Location = System::Drawing::Point(47, 193);
			this->B_CALIBRATOR_RV_I->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_RV_I->Name = L"B_CALIBRATOR_RV_I";
			this->B_CALIBRATOR_RV_I->ReadOnly = true;
			this->B_CALIBRATOR_RV_I->Size = System::Drawing::Size(54, 20);
			this->B_CALIBRATOR_RV_I->TabIndex = 157;
			this->B_CALIBRATOR_RV_I->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CALIBRATOR_RH_I
			// 
			this->B_CALIBRATOR_RH_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_RH_I->Location = System::Drawing::Point(47, 172);
			this->B_CALIBRATOR_RH_I->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_RH_I->Name = L"B_CALIBRATOR_RH_I";
			this->B_CALIBRATOR_RH_I->ReadOnly = true;
			this->B_CALIBRATOR_RH_I->Size = System::Drawing::Size(54, 20);
			this->B_CALIBRATOR_RH_I->TabIndex = 156;
			this->B_CALIBRATOR_RH_I->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CALIBRATOR_LH_I
			// 
			this->B_CALIBRATOR_LH_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_LH_I->Location = System::Drawing::Point(47, 132);
			this->B_CALIBRATOR_LH_I->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_LH_I->Name = L"B_CALIBRATOR_LH_I";
			this->B_CALIBRATOR_LH_I->ReadOnly = true;
			this->B_CALIBRATOR_LH_I->Size = System::Drawing::Size(54, 20);
			this->B_CALIBRATOR_LH_I->TabIndex = 154;
			this->B_CALIBRATOR_LH_I->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CALIBRATOR_LV_I
			// 
			this->B_CALIBRATOR_LV_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_LV_I->Location = System::Drawing::Point(47, 152);
			this->B_CALIBRATOR_LV_I->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_LV_I->Name = L"B_CALIBRATOR_LV_I";
			this->B_CALIBRATOR_LV_I->ReadOnly = true;
			this->B_CALIBRATOR_LV_I->Size = System::Drawing::Size(54, 20);
			this->B_CALIBRATOR_LV_I->TabIndex = 155;
			this->B_CALIBRATOR_LV_I->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label145
			// 
			this->label145->AutoSize = true;
			this->label145->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label145->ForeColor = System::Drawing::Color::White;
			this->label145->Location = System::Drawing::Point(25, 287);
			this->label145->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label145->Name = L"label145";
			this->label145->Size = System::Drawing::Size(108, 13);
			this->label145->TabIndex = 153;
			this->label145->Text = L"Calibrator end sample";
			// 
			// label144
			// 
			this->label144->AutoSize = true;
			this->label144->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label144->ForeColor = System::Drawing::Color::White;
			this->label144->Location = System::Drawing::Point(23, 267);
			this->label144->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label144->Name = L"label144";
			this->label144->Size = System::Drawing::Size(110, 13);
			this->label144->TabIndex = 152;
			this->label144->Text = L"Calibrator start sample";
			// 
			// label143
			// 
			this->label143->AutoSize = true;
			this->label143->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label143->ForeColor = System::Drawing::Color::White;
			this->label143->Location = System::Drawing::Point(41, 246);
			this->label143->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label143->Name = L"label143";
			this->label143->Size = System::Drawing::Size(92, 13);
			this->label143->TabIndex = 151;
			this->label143->Text = L"Probe end sample";
			// 
			// label142
			// 
			this->label142->AutoSize = true;
			this->label142->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label142->ForeColor = System::Drawing::Color::White;
			this->label142->Location = System::Drawing::Point(39, 228);
			this->label142->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label142->Name = L"label142";
			this->label142->Size = System::Drawing::Size(94, 13);
			this->label142->TabIndex = 150;
			this->label142->Text = L"Probe start sample";
			// 
			// label141
			// 
			this->label141->AutoSize = true;
			this->label141->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label141->ForeColor = System::Drawing::Color::White;
			this->label141->Location = System::Drawing::Point(23, 58);
			this->label141->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label141->Name = L"label141";
			this->label141->Size = System::Drawing::Size(23, 13);
			this->label141->TabIndex = 149;
			this->label141->Text = L"L-V";
			// 
			// label140
			// 
			this->label140->AutoSize = true;
			this->label140->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label140->ForeColor = System::Drawing::Color::White;
			this->label140->Location = System::Drawing::Point(20, 76);
			this->label140->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label140->Name = L"label140";
			this->label140->Size = System::Drawing::Size(26, 13);
			this->label140->TabIndex = 148;
			this->label140->Text = L"R-H";
			// 
			// label139
			// 
			this->label139->AutoSize = true;
			this->label139->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label139->ForeColor = System::Drawing::Color::White;
			this->label139->Location = System::Drawing::Point(22, 37);
			this->label139->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label139->Name = L"label139";
			this->label139->Size = System::Drawing::Size(24, 13);
			this->label139->TabIndex = 147;
			this->label139->Text = L"L-H";
			// 
			// label138
			// 
			this->label138->AutoSize = true;
			this->label138->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label138->ForeColor = System::Drawing::Color::White;
			this->label138->Location = System::Drawing::Point(21, 99);
			this->label138->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label138->Name = L"label138";
			this->label138->Size = System::Drawing::Size(25, 13);
			this->label138->TabIndex = 146;
			this->label138->Text = L"R-V";
			// 
			// B_CORRECTION_RV_Q
			// 
			this->B_CORRECTION_RV_Q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CORRECTION_RV_Q->Location = System::Drawing::Point(122, 94);
			this->B_CORRECTION_RV_Q->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CORRECTION_RV_Q->Name = L"B_CORRECTION_RV_Q";
			this->B_CORRECTION_RV_Q->ReadOnly = true;
			this->B_CORRECTION_RV_Q->Size = System::Drawing::Size(54, 20);
			this->B_CORRECTION_RV_Q->TabIndex = 141;
			this->B_CORRECTION_RV_Q->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CORRECTION_RH_Q
			// 
			this->B_CORRECTION_RH_Q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CORRECTION_RH_Q->Location = System::Drawing::Point(122, 73);
			this->B_CORRECTION_RH_Q->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CORRECTION_RH_Q->Name = L"B_CORRECTION_RH_Q";
			this->B_CORRECTION_RH_Q->ReadOnly = true;
			this->B_CORRECTION_RH_Q->Size = System::Drawing::Size(54, 20);
			this->B_CORRECTION_RH_Q->TabIndex = 140;
			this->B_CORRECTION_RH_Q->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CORRECTION_LH_Q
			// 
			this->B_CORRECTION_LH_Q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CORRECTION_LH_Q->Location = System::Drawing::Point(122, 34);
			this->B_CORRECTION_LH_Q->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CORRECTION_LH_Q->Name = L"B_CORRECTION_LH_Q";
			this->B_CORRECTION_LH_Q->ReadOnly = true;
			this->B_CORRECTION_LH_Q->Size = System::Drawing::Size(54, 20);
			this->B_CORRECTION_LH_Q->TabIndex = 138;
			this->B_CORRECTION_LH_Q->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CORRECTION_LV_Q
			// 
			this->B_CORRECTION_LV_Q->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CORRECTION_LV_Q->Location = System::Drawing::Point(122, 55);
			this->B_CORRECTION_LV_Q->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CORRECTION_LV_Q->Name = L"B_CORRECTION_LV_Q";
			this->B_CORRECTION_LV_Q->ReadOnly = true;
			this->B_CORRECTION_LV_Q->Size = System::Drawing::Size(54, 20);
			this->B_CORRECTION_LV_Q->TabIndex = 139;
			this->B_CORRECTION_LV_Q->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CORRECTION_RV_I
			// 
			this->B_CORRECTION_RV_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CORRECTION_RV_I->Location = System::Drawing::Point(47, 94);
			this->B_CORRECTION_RV_I->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CORRECTION_RV_I->Name = L"B_CORRECTION_RV_I";
			this->B_CORRECTION_RV_I->ReadOnly = true;
			this->B_CORRECTION_RV_I->Size = System::Drawing::Size(54, 20);
			this->B_CORRECTION_RV_I->TabIndex = 137;
			this->B_CORRECTION_RV_I->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CORRECTION_RH_I
			// 
			this->B_CORRECTION_RH_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CORRECTION_RH_I->Location = System::Drawing::Point(47, 73);
			this->B_CORRECTION_RH_I->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CORRECTION_RH_I->Name = L"B_CORRECTION_RH_I";
			this->B_CORRECTION_RH_I->ReadOnly = true;
			this->B_CORRECTION_RH_I->Size = System::Drawing::Size(54, 20);
			this->B_CORRECTION_RH_I->TabIndex = 136;
			this->B_CORRECTION_RH_I->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CORRECTION_LH_I
			// 
			this->B_CORRECTION_LH_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CORRECTION_LH_I->Location = System::Drawing::Point(47, 34);
			this->B_CORRECTION_LH_I->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CORRECTION_LH_I->Name = L"B_CORRECTION_LH_I";
			this->B_CORRECTION_LH_I->ReadOnly = true;
			this->B_CORRECTION_LH_I->Size = System::Drawing::Size(54, 20);
			this->B_CORRECTION_LH_I->TabIndex = 134;
			this->B_CORRECTION_LH_I->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CORRECTION_LV_I
			// 
			this->B_CORRECTION_LV_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CORRECTION_LV_I->Location = System::Drawing::Point(47, 55);
			this->B_CORRECTION_LV_I->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CORRECTION_LV_I->Name = L"B_CORRECTION_LV_I";
			this->B_CORRECTION_LV_I->ReadOnly = true;
			this->B_CORRECTION_LV_I->Size = System::Drawing::Size(54, 20);
			this->B_CORRECTION_LV_I->TabIndex = 135;
			this->B_CORRECTION_LV_I->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CALIBRATOR_TGT_END
			// 
			this->B_CALIBRATOR_TGT_END->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_TGT_END->Location = System::Drawing::Point(136, 284);
			this->B_CALIBRATOR_TGT_END->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_TGT_END->Name = L"B_CALIBRATOR_TGT_END";
			this->B_CALIBRATOR_TGT_END->ReadOnly = true;
			this->B_CALIBRATOR_TGT_END->Size = System::Drawing::Size(41, 20);
			this->B_CALIBRATOR_TGT_END->TabIndex = 133;
			this->B_CALIBRATOR_TGT_END->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_CALIBRATOR_TGT_START
			// 
			this->B_CALIBRATOR_TGT_START->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CALIBRATOR_TGT_START->Location = System::Drawing::Point(136, 264);
			this->B_CALIBRATOR_TGT_START->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CALIBRATOR_TGT_START->Name = L"B_CALIBRATOR_TGT_START";
			this->B_CALIBRATOR_TGT_START->ReadOnly = true;
			this->B_CALIBRATOR_TGT_START->Size = System::Drawing::Size(41, 20);
			this->B_CALIBRATOR_TGT_START->TabIndex = 132;
			this->B_CALIBRATOR_TGT_START->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_PROBE_CALIBRATE_TGT_START
			// 
			this->B_PROBE_CALIBRATE_TGT_START->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PROBE_CALIBRATE_TGT_START->Location = System::Drawing::Point(136, 223);
			this->B_PROBE_CALIBRATE_TGT_START->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PROBE_CALIBRATE_TGT_START->Name = L"B_PROBE_CALIBRATE_TGT_START";
			this->B_PROBE_CALIBRATE_TGT_START->ReadOnly = true;
			this->B_PROBE_CALIBRATE_TGT_START->Size = System::Drawing::Size(41, 20);
			this->B_PROBE_CALIBRATE_TGT_START->TabIndex = 130;
			this->B_PROBE_CALIBRATE_TGT_START->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_PROBE_CALIBRATE_TGT_END
			// 
			this->B_PROBE_CALIBRATE_TGT_END->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PROBE_CALIBRATE_TGT_END->Location = System::Drawing::Point(136, 244);
			this->B_PROBE_CALIBRATE_TGT_END->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PROBE_CALIBRATE_TGT_END->Name = L"B_PROBE_CALIBRATE_TGT_END";
			this->B_PROBE_CALIBRATE_TGT_END->ReadOnly = true;
			this->B_PROBE_CALIBRATE_TGT_END->Size = System::Drawing::Size(41, 20);
			this->B_PROBE_CALIBRATE_TGT_END->TabIndex = 131;
			this->B_PROBE_CALIBRATE_TGT_END->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->B_MAX_ERROR_RANGE);
			this->groupBox7->Controls->Add(this->label270);
			this->groupBox7->Controls->Add(this->F_Target_detection_2nd_threshold);
			this->groupBox7->Controls->Add(this->label240);
			this->groupBox7->Controls->Add(this->B_MAX_VELOCITY_MS);
			this->groupBox7->Controls->Add(this->label228);
			this->groupBox7->Controls->Add(this->F_MINIMUM_RANGE_METER);
			this->groupBox7->Controls->Add(this->label210);
			this->groupBox7->Controls->Add(this->label115);
			this->groupBox7->Controls->Add(this->F_BATCH_DURATION);
			this->groupBox7->Controls->Add(this->F_AGC_threshold);
			this->groupBox7->Controls->Add(this->label109);
			this->groupBox7->Controls->Add(this->F_RANGE_DECIMATION);
			this->groupBox7->Controls->Add(this->F_Target_detection_1st_threshold);
			this->groupBox7->Controls->Add(this->F_RANGE_meter);
			this->groupBox7->Controls->Add(this->label160);
			this->groupBox7->Controls->Add(this->label39);
			this->groupBox7->Controls->Add(this->F_MAX_VELOCITY);
			this->groupBox7->Controls->Add(this->label159);
			this->groupBox7->Controls->Add(this->F_OFFSET_sample);
			this->groupBox7->Controls->Add(this->label101);
			this->groupBox7->Controls->Add(this->label97);
			this->groupBox7->Controls->Add(this->F_Number_of_buffers);
			this->groupBox7->Controls->Add(this->label24);
			this->groupBox7->ForeColor = System::Drawing::Color::White;
			this->groupBox7->Location = System::Drawing::Point(402, 195);
			this->groupBox7->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox7->Size = System::Drawing::Size(207, 309);
			this->groupBox7->TabIndex = 167;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Digital control";
			// 
			// F_Target_detection_2nd_threshold
			// 
			this->F_Target_detection_2nd_threshold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_Target_detection_2nd_threshold->Location = System::Drawing::Point(114, 43);
			this->F_Target_detection_2nd_threshold->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_Target_detection_2nd_threshold->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32767, 0, 0, 0 });
			this->F_Target_detection_2nd_threshold->Name = L"F_Target_detection_2nd_threshold";
			this->F_Target_detection_2nd_threshold->Size = System::Drawing::Size(78, 20);
			this->F_Target_detection_2nd_threshold->TabIndex = 169;
			this->F_Target_detection_2nd_threshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_Target_detection_2nd_threshold->ValueChanged += gcnew System::EventHandler(this, &MyForm::Target_detection_2nd_threshold_ValueChanged);
			// 
			// label240
			// 
			this->label240->AutoSize = true;
			this->label240->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label240->ForeColor = System::Drawing::Color::White;
			this->label240->Location = System::Drawing::Point(2, 46);
			this->label240->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label240->Name = L"label240";
			this->label240->Size = System::Drawing::Size(113, 13);
			this->label240->TabIndex = 170;
			this->label240->Text = L"2nd detector threshold";
			// 
			// B_MAX_VELOCITY_MS
			// 
			this->B_MAX_VELOCITY_MS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_MAX_VELOCITY_MS->Location = System::Drawing::Point(115, 249);
			this->B_MAX_VELOCITY_MS->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_MAX_VELOCITY_MS->Name = L"B_MAX_VELOCITY_MS";
			this->B_MAX_VELOCITY_MS->ReadOnly = true;
			this->B_MAX_VELOCITY_MS->Size = System::Drawing::Size(45, 20);
			this->B_MAX_VELOCITY_MS->TabIndex = 169;
			this->B_MAX_VELOCITY_MS->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label228
			// 
			this->label228->AutoSize = true;
			this->label228->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label228->ForeColor = System::Drawing::Color::White;
			this->label228->Location = System::Drawing::Point(30, 67);
			this->label228->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label228->Name = L"label228";
			this->label228->Size = System::Drawing::Size(81, 13);
			this->label228->TabIndex = 169;
			this->label228->Text = L"max vel. [Buff#]";
			// 
			// F_MINIMUM_RANGE_METER
			// 
			this->F_MINIMUM_RANGE_METER->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_MINIMUM_RANGE_METER->Location = System::Drawing::Point(114, 228);
			this->F_MINIMUM_RANGE_METER->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_MINIMUM_RANGE_METER->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, 0 });
			this->F_MINIMUM_RANGE_METER->Name = L"F_MINIMUM_RANGE_METER";
			this->F_MINIMUM_RANGE_METER->Size = System::Drawing::Size(78, 20);
			this->F_MINIMUM_RANGE_METER->TabIndex = 177;
			this->F_MINIMUM_RANGE_METER->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_MINIMUM_RANGE_METER->Visible = false;
			this->F_MINIMUM_RANGE_METER->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_MINIMUM_RANGE_METER_ValueChanged);
			// 
			// label210
			// 
			this->label210->AutoSize = true;
			this->label210->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label210->ForeColor = System::Drawing::Color::White;
			this->label210->Location = System::Drawing::Point(17, 231);
			this->label210->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label210->Name = L"label210";
			this->label210->Size = System::Drawing::Size(95, 13);
			this->label210->TabIndex = 176;
			this->label210->Text = L"Minimum range [m]";
			this->label210->Visible = false;
			// 
			// label115
			// 
			this->label115->AutoSize = true;
			this->label115->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label115->ForeColor = System::Drawing::Color::White;
			this->label115->Location = System::Drawing::Point(36, 171);
			this->label115->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label115->Name = L"label115";
			this->label115->Size = System::Drawing::Size(76, 13);
			this->label115->TabIndex = 175;
			this->label115->Text = L"Batch duration";
			// 
			// F_BATCH_DURATION
			// 
			this->F_BATCH_DURATION->Location = System::Drawing::Point(114, 169);
			this->F_BATCH_DURATION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_BATCH_DURATION->Name = L"F_BATCH_DURATION";
			this->F_BATCH_DURATION->ReadOnly = true;
			this->F_BATCH_DURATION->Size = System::Drawing::Size(78, 20);
			this->F_BATCH_DURATION->TabIndex = 171;
			this->F_BATCH_DURATION->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// F_AGC_threshold
			// 
			this->F_AGC_threshold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_AGC_threshold->Location = System::Drawing::Point(114, 207);
			this->F_AGC_threshold->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_AGC_threshold->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32767, 0, 0, 0 });
			this->F_AGC_threshold->Name = L"F_AGC_threshold";
			this->F_AGC_threshold->Size = System::Drawing::Size(78, 20);
			this->F_AGC_threshold->TabIndex = 170;
			this->F_AGC_threshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_AGC_threshold->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->F_AGC_threshold->Visible = false;
			this->F_AGC_threshold->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_AGC_threshold_ValueChanged);
			// 
			// label109
			// 
			this->label109->AutoSize = true;
			this->label109->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label109->ForeColor = System::Drawing::Color::White;
			this->label109->Location = System::Drawing::Point(37, 210);
			this->label109->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label109->Name = L"label109";
			this->label109->Size = System::Drawing::Size(75, 13);
			this->label109->TabIndex = 169;
			this->label109->Text = L"AGC threshold";
			this->label109->Visible = false;
			// 
			// F_RANGE_DECIMATION
			// 
			this->F_RANGE_DECIMATION->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_RANGE_DECIMATION->Location = System::Drawing::Point(114, 85);
			this->F_RANGE_DECIMATION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_RANGE_DECIMATION->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3000, 0, 0, 0 });
			this->F_RANGE_DECIMATION->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->F_RANGE_DECIMATION->Name = L"F_RANGE_DECIMATION";
			this->F_RANGE_DECIMATION->Size = System::Drawing::Size(78, 20);
			this->F_RANGE_DECIMATION->TabIndex = 168;
			this->F_RANGE_DECIMATION->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_RANGE_DECIMATION->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->F_RANGE_DECIMATION->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_RANGE_DECIMATION_ValueChanged);
			// 
			// F_Target_detection_1st_threshold
			// 
			this->F_Target_detection_1st_threshold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_Target_detection_1st_threshold->Location = System::Drawing::Point(114, 22);
			this->F_Target_detection_1st_threshold->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_Target_detection_1st_threshold->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32767, 0, 0, 0 });
			this->F_Target_detection_1st_threshold->Name = L"F_Target_detection_1st_threshold";
			this->F_Target_detection_1st_threshold->Size = System::Drawing::Size(78, 20);
			this->F_Target_detection_1st_threshold->TabIndex = 165;
			this->F_Target_detection_1st_threshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_Target_detection_1st_threshold->ValueChanged += gcnew System::EventHandler(this, &MyForm::Target_detection_1st_threshold_ValueChanged);
			// 
			// F_RANGE_meter
			// 
			this->F_RANGE_meter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_RANGE_meter->Location = System::Drawing::Point(114, 127);
			this->F_RANGE_meter->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_RANGE_meter->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3000, 0, 0, 0 });
			this->F_RANGE_meter->Name = L"F_RANGE_meter";
			this->F_RANGE_meter->Size = System::Drawing::Size(78, 20);
			this->F_RANGE_meter->TabIndex = 166;
			this->F_RANGE_meter->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_RANGE_meter->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_RANGE_meter_ValueChanged);
			// 
			// label160
			// 
			this->label160->AutoSize = true;
			this->label160->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label160->ForeColor = System::Drawing::Color::White;
			this->label160->Location = System::Drawing::Point(19, 87);
			this->label160->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label160->Name = L"label160";
			this->label160->Size = System::Drawing::Size(93, 13);
			this->label160->TabIndex = 167;
			this->label160->Text = L"Range decimation";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label39->ForeColor = System::Drawing::Color::White;
			this->label39->Location = System::Drawing::Point(2, 25);
			this->label39->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(109, 13);
			this->label39->TabIndex = 166;
			this->label39->Text = L"1st detector threshold";
			// 
			// F_MAX_VELOCITY
			// 
			this->F_MAX_VELOCITY->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_MAX_VELOCITY->Location = System::Drawing::Point(114, 64);
			this->F_MAX_VELOCITY->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_MAX_VELOCITY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3000, 0, 0, 0 });
			this->F_MAX_VELOCITY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->F_MAX_VELOCITY->Name = L"F_MAX_VELOCITY";
			this->F_MAX_VELOCITY->Size = System::Drawing::Size(78, 20);
			this->F_MAX_VELOCITY->TabIndex = 168;
			this->F_MAX_VELOCITY->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_MAX_VELOCITY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->F_MAX_VELOCITY->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_MAX_VELOCITY_ValueChanged);
			// 
			// label159
			// 
			this->label159->AutoSize = true;
			this->label159->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label159->ForeColor = System::Drawing::Color::White;
			this->label159->Location = System::Drawing::Point(28, 253);
			this->label159->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label159->Name = L"label159";
			this->label159->Size = System::Drawing::Size(87, 13);
			this->label159->TabIndex = 167;
			this->label159->Text = L"max vel. [m/Sec]";
			// 
			// F_OFFSET_sample
			// 
			this->F_OFFSET_sample->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_OFFSET_sample->Location = System::Drawing::Point(114, 106);
			this->F_OFFSET_sample->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_OFFSET_sample->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->F_OFFSET_sample->Name = L"F_OFFSET_sample";
			this->F_OFFSET_sample->Size = System::Drawing::Size(78, 20);
			this->F_OFFSET_sample->TabIndex = 165;
			this->F_OFFSET_sample->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_OFFSET_sample->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_OFFSET_sample_ValueChanged);
			// 
			// label101
			// 
			this->label101->AutoSize = true;
			this->label101->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label101->ForeColor = System::Drawing::Color::White;
			this->label101->Location = System::Drawing::Point(49, 109);
			this->label101->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label101->Name = L"label101";
			this->label101->Size = System::Drawing::Size(63, 13);
			this->label101->TabIndex = 162;
			this->label101->Text = L"Offset [smp]";
			// 
			// label97
			// 
			this->label97->AutoSize = true;
			this->label97->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label97->ForeColor = System::Drawing::Color::White;
			this->label97->Location = System::Drawing::Point(56, 128);
			this->label97->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label97->Name = L"label97";
			this->label97->Size = System::Drawing::Size(56, 13);
			this->label97->TabIndex = 164;
			this->label97->Text = L"Range [m]";
			// 
			// F_Number_of_buffers
			// 
			this->F_Number_of_buffers->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_Number_of_buffers->Location = System::Drawing::Point(114, 148);
			this->F_Number_of_buffers->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_Number_of_buffers->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->F_Number_of_buffers->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->F_Number_of_buffers->Name = L"F_Number_of_buffers";
			this->F_Number_of_buffers->Size = System::Drawing::Size(78, 20);
			this->F_Number_of_buffers->TabIndex = 51;
			this->F_Number_of_buffers->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_Number_of_buffers->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->F_Number_of_buffers->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_Number_of_buffers_ValueChanged);
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->ForeColor = System::Drawing::Color::White;
			this->label24->Location = System::Drawing::Point(50, 150);
			this->label24->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(61, 13);
			this->label24->TabIndex = 18;
			this->label24->Text = L"# of buffers";
			// 
			// label98
			// 
			this->label98->AutoSize = true;
			this->label98->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label98->ForeColor = System::Drawing::Color::White;
			this->label98->Location = System::Drawing::Point(253, 6);
			this->label98->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label98->Name = L"label98";
			this->label98->Size = System::Drawing::Size(144, 20);
			this->label98->TabIndex = 164;
			this->label98->Text = L"Tx/Rx control mode";
			// 
			// F_TxRx_control_MODE
			// 
			this->F_TxRx_control_MODE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_TxRx_control_MODE->FormattingEnabled = true;
			this->F_TxRx_control_MODE->ItemHeight = 16;
			this->F_TxRx_control_MODE->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"WORK", L"PROBE", L"CALIBRATOR" });
			this->F_TxRx_control_MODE->Location = System::Drawing::Point(257, 29);
			this->F_TxRx_control_MODE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_TxRx_control_MODE->Name = L"F_TxRx_control_MODE";
			this->F_TxRx_control_MODE->Size = System::Drawing::Size(100, 52);
			this->F_TxRx_control_MODE->TabIndex = 163;
			this->F_TxRx_control_MODE->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::F_TxRx_control_MODE_SelectedIndexChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->groupBox2->Controls->Add(this->F_PROBE_TEST_gain);
			this->groupBox2->Controls->Add(this->label103);
			this->groupBox2->Controls->Add(this->F_PROBE_TEST_profile);
			this->groupBox2->Controls->Add(this->label102);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->groupBox2->ForeColor = System::Drawing::Color::White;
			this->groupBox2->Location = System::Drawing::Point(257, 93);
			this->groupBox2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox2->Size = System::Drawing::Size(136, 90);
			this->groupBox2->TabIndex = 162;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"PROBE test";
			this->groupBox2->Visible = false;
			// 
			// F_PROBE_TEST_gain
			// 
			this->F_PROBE_TEST_gain->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_PROBE_TEST_gain->Location = System::Drawing::Point(54, 52);
			this->F_PROBE_TEST_gain->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_PROBE_TEST_gain->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
			this->F_PROBE_TEST_gain->Name = L"F_PROBE_TEST_gain";
			this->F_PROBE_TEST_gain->Size = System::Drawing::Size(68, 20);
			this->F_PROBE_TEST_gain->TabIndex = 62;
			this->F_PROBE_TEST_gain->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_PROBE_TEST_gain->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_PROBE_TEST_gain_ValueChanged);
			// 
			// label103
			// 
			this->label103->AutoSize = true;
			this->label103->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label103->ForeColor = System::Drawing::Color::White;
			this->label103->Location = System::Drawing::Point(14, 53);
			this->label103->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label103->Name = L"label103";
			this->label103->Size = System::Drawing::Size(29, 13);
			this->label103->TabIndex = 61;
			this->label103->Text = L"Gain";
			// 
			// F_PROBE_TEST_profile
			// 
			this->F_PROBE_TEST_profile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_PROBE_TEST_profile->Location = System::Drawing::Point(54, 25);
			this->F_PROBE_TEST_profile->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_PROBE_TEST_profile->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
			this->F_PROBE_TEST_profile->Name = L"F_PROBE_TEST_profile";
			this->F_PROBE_TEST_profile->Size = System::Drawing::Size(68, 20);
			this->F_PROBE_TEST_profile->TabIndex = 60;
			this->F_PROBE_TEST_profile->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_PROBE_TEST_profile->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_PROBE_TEST_profile_ValueChanged);
			// 
			// label102
			// 
			this->label102->AutoSize = true;
			this->label102->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label102->ForeColor = System::Drawing::Color::White;
			this->label102->Location = System::Drawing::Point(4, 26);
			this->label102->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label102->Name = L"label102";
			this->label102->Size = System::Drawing::Size(36, 13);
			this->label102->TabIndex = 59;
			this->label102->Text = L"Profile";
			// 
			// F_SYSTEM_ID
			// 
			this->F_SYSTEM_ID->Cursor = System::Windows::Forms::Cursors::AppStarting;
			this->F_SYSTEM_ID->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_SYSTEM_ID->Location = System::Drawing::Point(109, 8);
			this->F_SYSTEM_ID->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_SYSTEM_ID->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			this->F_SYSTEM_ID->Name = L"F_SYSTEM_ID";
			this->F_SYSTEM_ID->Size = System::Drawing::Size(100, 26);
			this->F_SYSTEM_ID->TabIndex = 161;
			this->F_SYSTEM_ID->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_SYSTEM_ID->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_SYSTEM_ID_ValueChanged);
			// 
			// label72
			// 
			this->label72->AutoSize = true;
			this->label72->Cursor = System::Windows::Forms::Cursors::AppStarting;
			this->label72->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label72->ForeColor = System::Drawing::Color::White;
			this->label72->Location = System::Drawing::Point(22, 10);
			this->label72->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(87, 20);
			this->label72->TabIndex = 160;
			this->label72->Text = L"System ID:";
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->groupBox6->Controls->Add(this->F_RF2_ON);
			this->groupBox6->Controls->Add(this->label100);
			this->groupBox6->Controls->Add(this->F_TX_LO_TR);
			this->groupBox6->Controls->Add(this->panel13);
			this->groupBox6->Controls->Add(this->panel3);
			this->groupBox6->Controls->Add(this->panel4);
			this->groupBox6->Controls->Add(this->label146);
			this->groupBox6->Controls->Add(this->panel2);
			this->groupBox6->Controls->Add(this->label2);
			this->groupBox6->Controls->Add(this->panel1);
			this->groupBox6->Controls->Add(this->F_TX1_ON);
			this->groupBox6->Controls->Add(this->F_PROBE_ON);
			this->groupBox6->Controls->Add(this->F_TX3_ON);
			this->groupBox6->Controls->Add(this->label99);
			this->groupBox6->Controls->Add(this->F_TX2_ON);
			this->groupBox6->Controls->Add(this->label28);
			this->groupBox6->Controls->Add(this->label26);
			this->groupBox6->Controls->Add(this->F_ATTN_RX4);
			this->groupBox6->Controls->Add(this->F_IO_UPDATE_ON);
			this->groupBox6->Controls->Add(this->F_Profile_AD9910B);
			this->groupBox6->Controls->Add(this->label25);
			this->groupBox6->Controls->Add(this->F_Profile_AD9910A);
			this->groupBox6->Controls->Add(this->F_FIFO_length);
			this->groupBox6->Controls->Add(this->F_chip_length_AD9910A);
			this->groupBox6->Controls->Add(this->F_Buffer_length);
			this->groupBox6->Controls->Add(this->F_ATTN_RX3);
			this->groupBox6->Controls->Add(this->F_chip_length_AD9910B);
			this->groupBox6->Controls->Add(this->F_IO_UPDATE_rate);
			this->groupBox6->Controls->Add(this->F_ATTN_RX2);
			this->groupBox6->Controls->Add(this->F_AD9910_Set_aux_dac_B);
			this->groupBox6->Controls->Add(this->F_AD9910_Set_aux_dac_A);
			this->groupBox6->Controls->Add(this->F_ATTN_RX1);
			this->groupBox6->Controls->Add(this->label1);
			this->groupBox6->Controls->Add(this->label22);
			this->groupBox6->Controls->Add(this->label8);
			this->groupBox6->Controls->Add(this->F_ATTN_TX3);
			this->groupBox6->Controls->Add(this->F_ATTN_TX2);
			this->groupBox6->Controls->Add(this->label3);
			this->groupBox6->Controls->Add(this->F_ATTN_TX1);
			this->groupBox6->Controls->Add(this->label16);
			this->groupBox6->Controls->Add(this->label17);
			this->groupBox6->Controls->Add(this->label15);
			this->groupBox6->Controls->Add(this->label18);
			this->groupBox6->Controls->Add(this->label21);
			this->groupBox6->Controls->Add(this->label20);
			this->groupBox6->Controls->Add(this->label19);
			this->groupBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox6->ForeColor = System::Drawing::Color::White;
			this->groupBox6->Location = System::Drawing::Point(5, 33);
			this->groupBox6->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox6->Size = System::Drawing::Size(238, 546);
			this->groupBox6->TabIndex = 159;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Tx/Rx control";
			// 
			// F_RF2_ON
			// 
			this->F_RF2_ON->AutoSize = true;
			this->F_RF2_ON->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_RF2_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_RF2_ON->ForeColor = System::Drawing::Color::White;
			this->F_RF2_ON->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_RF2_ON->Location = System::Drawing::Point(54, 432);
			this->F_RF2_ON->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_RF2_ON->Name = L"F_RF2_ON";
			this->F_RF2_ON->Size = System::Drawing::Size(59, 24);
			this->F_RF2_ON->TabIndex = 171;
			this->F_RF2_ON->Text = L"RF2";
			this->F_RF2_ON->UseVisualStyleBackColor = true;
			this->F_RF2_ON->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_RF2_ON_CheckedChanged);
			// 
			// label100
			// 
			this->label100->AutoSize = true;
			this->label100->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label100->ForeColor = System::Drawing::Color::White;
			this->label100->Location = System::Drawing::Point(17, 474);
			this->label100->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label100->Name = L"label100";
			this->label100->Size = System::Drawing::Size(87, 20);
			this->label100->TabIndex = 165;
			this->label100->Text = L"continuous";
			this->label100->Visible = false;
			// 
			// F_TX_LO_TR
			// 
			this->F_TX_LO_TR->AutoSize = true;
			this->F_TX_LO_TR->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX_LO_TR->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_TX_LO_TR->ForeColor = System::Drawing::Color::White;
			this->F_TX_LO_TR->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX_LO_TR->Location = System::Drawing::Point(60, 406);
			this->F_TX_LO_TR->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_TX_LO_TR->Name = L"F_TX_LO_TR";
			this->F_TX_LO_TR->Size = System::Drawing::Size(53, 24);
			this->F_TX_LO_TR->TabIndex = 39;
			this->F_TX_LO_TR->Text = L"T/R";
			this->F_TX_LO_TR->UseVisualStyleBackColor = true;
			this->F_TX_LO_TR->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_TX_LO_TR_CheckedChanged);
			// 
			// panel13
			// 
			this->panel13->Controls->Add(this->F_IF_SELECT_PROBE_B);
			this->panel13->Controls->Add(this->F_IF_SELECT_PROBE_A);
			this->panel13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel13->Location = System::Drawing::Point(136, 368);
			this->panel13->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->panel13->Name = L"panel13";
			this->panel13->Size = System::Drawing::Size(90, 33);
			this->panel13->TabIndex = 70;
			// 
			// F_IF_SELECT_PROBE_B
			// 
			this->F_IF_SELECT_PROBE_B->AutoSize = true;
			this->F_IF_SELECT_PROBE_B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_IF_SELECT_PROBE_B->ForeColor = System::Drawing::Color::White;
			this->F_IF_SELECT_PROBE_B->Location = System::Drawing::Point(50, 3);
			this->F_IF_SELECT_PROBE_B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IF_SELECT_PROBE_B->Name = L"F_IF_SELECT_PROBE_B";
			this->F_IF_SELECT_PROBE_B->Size = System::Drawing::Size(38, 24);
			this->F_IF_SELECT_PROBE_B->TabIndex = 61;
			this->F_IF_SELECT_PROBE_B->TabStop = true;
			this->F_IF_SELECT_PROBE_B->Text = L"B";
			this->F_IF_SELECT_PROBE_B->UseVisualStyleBackColor = true;
			// 
			// F_IF_SELECT_PROBE_A
			// 
			this->F_IF_SELECT_PROBE_A->AutoSize = true;
			this->F_IF_SELECT_PROBE_A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_IF_SELECT_PROBE_A->ForeColor = System::Drawing::Color::White;
			this->F_IF_SELECT_PROBE_A->Location = System::Drawing::Point(8, 3);
			this->F_IF_SELECT_PROBE_A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IF_SELECT_PROBE_A->Name = L"F_IF_SELECT_PROBE_A";
			this->F_IF_SELECT_PROBE_A->Size = System::Drawing::Size(38, 24);
			this->F_IF_SELECT_PROBE_A->TabIndex = 60;
			this->F_IF_SELECT_PROBE_A->TabStop = true;
			this->F_IF_SELECT_PROBE_A->Text = L"A";
			this->F_IF_SELECT_PROBE_A->UseVisualStyleBackColor = true;
			this->F_IF_SELECT_PROBE_A->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_IF_SELECT_PROBE_A_CheckedChanged);
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->F_IF_SELECT_TX3_B);
			this->panel3->Controls->Add(this->F_IF_SELECT_TX3_A);
			this->panel3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel3->Location = System::Drawing::Point(136, 334);
			this->panel3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(90, 33);
			this->panel3->TabIndex = 64;
			// 
			// F_IF_SELECT_TX3_B
			// 
			this->F_IF_SELECT_TX3_B->AutoSize = true;
			this->F_IF_SELECT_TX3_B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_IF_SELECT_TX3_B->ForeColor = System::Drawing::Color::White;
			this->F_IF_SELECT_TX3_B->Location = System::Drawing::Point(50, 6);
			this->F_IF_SELECT_TX3_B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IF_SELECT_TX3_B->Name = L"F_IF_SELECT_TX3_B";
			this->F_IF_SELECT_TX3_B->Size = System::Drawing::Size(38, 24);
			this->F_IF_SELECT_TX3_B->TabIndex = 61;
			this->F_IF_SELECT_TX3_B->TabStop = true;
			this->F_IF_SELECT_TX3_B->Text = L"B";
			this->F_IF_SELECT_TX3_B->UseVisualStyleBackColor = true;
			// 
			// F_IF_SELECT_TX3_A
			// 
			this->F_IF_SELECT_TX3_A->AutoSize = true;
			this->F_IF_SELECT_TX3_A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_IF_SELECT_TX3_A->ForeColor = System::Drawing::Color::White;
			this->F_IF_SELECT_TX3_A->Location = System::Drawing::Point(8, 7);
			this->F_IF_SELECT_TX3_A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IF_SELECT_TX3_A->Name = L"F_IF_SELECT_TX3_A";
			this->F_IF_SELECT_TX3_A->Size = System::Drawing::Size(38, 24);
			this->F_IF_SELECT_TX3_A->TabIndex = 60;
			this->F_IF_SELECT_TX3_A->TabStop = true;
			this->F_IF_SELECT_TX3_A->Text = L"A";
			this->F_IF_SELECT_TX3_A->UseVisualStyleBackColor = true;
			this->F_IF_SELECT_TX3_A->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_IF_SELECT_TX3_A_CheckedChanged);
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->F_PROBE_SELECT_SAMPLE);
			this->panel4->Controls->Add(this->F_PROBE_SELECT_ANT);
			this->panel4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel4->Location = System::Drawing::Point(136, 402);
			this->panel4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(90, 64);
			this->panel4->TabIndex = 66;
			// 
			// F_PROBE_SELECT_SAMPLE
			// 
			this->F_PROBE_SELECT_SAMPLE->AutoSize = true;
			this->F_PROBE_SELECT_SAMPLE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_PROBE_SELECT_SAMPLE->ForeColor = System::Drawing::Color::White;
			this->F_PROBE_SELECT_SAMPLE->Location = System::Drawing::Point(8, 7);
			this->F_PROBE_SELECT_SAMPLE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_PROBE_SELECT_SAMPLE->Name = L"F_PROBE_SELECT_SAMPLE";
			this->F_PROBE_SELECT_SAMPLE->Size = System::Drawing::Size(56, 24);
			this->F_PROBE_SELECT_SAMPLE->TabIndex = 61;
			this->F_PROBE_SELECT_SAMPLE->TabStop = true;
			this->F_PROBE_SELECT_SAMPLE->Text = L"Ant.";
			this->F_PROBE_SELECT_SAMPLE->UseVisualStyleBackColor = true;
			// 
			// F_PROBE_SELECT_ANT
			// 
			this->F_PROBE_SELECT_ANT->AutoSize = true;
			this->F_PROBE_SELECT_ANT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_PROBE_SELECT_ANT->ForeColor = System::Drawing::Color::White;
			this->F_PROBE_SELECT_ANT->Location = System::Drawing::Point(8, 37);
			this->F_PROBE_SELECT_ANT->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_PROBE_SELECT_ANT->Name = L"F_PROBE_SELECT_ANT";
			this->F_PROBE_SELECT_ANT->Size = System::Drawing::Size(81, 24);
			this->F_PROBE_SELECT_ANT->TabIndex = 60;
			this->F_PROBE_SELECT_ANT->TabStop = true;
			this->F_PROBE_SELECT_ANT->Text = L"Sample";
			this->F_PROBE_SELECT_ANT->UseVisualStyleBackColor = true;
			this->F_PROBE_SELECT_ANT->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_PROBE_SELECT_ANT_CheckedChanged);
			// 
			// label146
			// 
			this->label146->AutoSize = true;
			this->label146->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label146->ForeColor = System::Drawing::Color::White;
			this->label146->Location = System::Drawing::Point(173, 124);
			this->label146->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label146->Name = L"label146";
			this->label146->Size = System::Drawing::Size(45, 20);
			this->label146->TabIndex = 71;
			this->label146->Text = L"[kHz]";
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->F_IF_SELECT_TX2_B);
			this->panel2->Controls->Add(this->F_IF_SELECT_TX2_A);
			this->panel2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel2->Location = System::Drawing::Point(136, 308);
			this->panel2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(88, 35);
			this->panel2->TabIndex = 63;
			// 
			// F_IF_SELECT_TX2_B
			// 
			this->F_IF_SELECT_TX2_B->AutoSize = true;
			this->F_IF_SELECT_TX2_B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_IF_SELECT_TX2_B->ForeColor = System::Drawing::Color::White;
			this->F_IF_SELECT_TX2_B->Location = System::Drawing::Point(50, 1);
			this->F_IF_SELECT_TX2_B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IF_SELECT_TX2_B->Name = L"F_IF_SELECT_TX2_B";
			this->F_IF_SELECT_TX2_B->Size = System::Drawing::Size(38, 24);
			this->F_IF_SELECT_TX2_B->TabIndex = 61;
			this->F_IF_SELECT_TX2_B->TabStop = true;
			this->F_IF_SELECT_TX2_B->Text = L"B";
			this->F_IF_SELECT_TX2_B->UseVisualStyleBackColor = true;
			// 
			// F_IF_SELECT_TX2_A
			// 
			this->F_IF_SELECT_TX2_A->AutoSize = true;
			this->F_IF_SELECT_TX2_A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_IF_SELECT_TX2_A->ForeColor = System::Drawing::Color::White;
			this->F_IF_SELECT_TX2_A->Location = System::Drawing::Point(8, 1);
			this->F_IF_SELECT_TX2_A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IF_SELECT_TX2_A->Name = L"F_IF_SELECT_TX2_A";
			this->F_IF_SELECT_TX2_A->Size = System::Drawing::Size(38, 24);
			this->F_IF_SELECT_TX2_A->TabIndex = 60;
			this->F_IF_SELECT_TX2_A->TabStop = true;
			this->F_IF_SELECT_TX2_A->Text = L"A";
			this->F_IF_SELECT_TX2_A->UseVisualStyleBackColor = true;
			this->F_IF_SELECT_TX2_A->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_IF_SELECT_TX2_A_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(170, 16);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(52, 20);
			this->label2->TabIndex = 70;
			this->label2->Text = L"CH-B:";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->F_IF_SELECT_TX1_B);
			this->panel1->Controls->Add(this->F_IF_SELECT_TX1_A);
			this->panel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel1->Location = System::Drawing::Point(136, 274);
			this->panel1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(90, 32);
			this->panel1->TabIndex = 62;
			// 
			// F_IF_SELECT_TX1_B
			// 
			this->F_IF_SELECT_TX1_B->AutoSize = true;
			this->F_IF_SELECT_TX1_B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_IF_SELECT_TX1_B->ForeColor = System::Drawing::Color::White;
			this->F_IF_SELECT_TX1_B->Location = System::Drawing::Point(49, 4);
			this->F_IF_SELECT_TX1_B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IF_SELECT_TX1_B->Name = L"F_IF_SELECT_TX1_B";
			this->F_IF_SELECT_TX1_B->Size = System::Drawing::Size(38, 24);
			this->F_IF_SELECT_TX1_B->TabIndex = 61;
			this->F_IF_SELECT_TX1_B->TabStop = true;
			this->F_IF_SELECT_TX1_B->Text = L"B";
			this->F_IF_SELECT_TX1_B->UseVisualStyleBackColor = true;
			// 
			// F_IF_SELECT_TX1_A
			// 
			this->F_IF_SELECT_TX1_A->AutoSize = true;
			this->F_IF_SELECT_TX1_A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_IF_SELECT_TX1_A->ForeColor = System::Drawing::Color::White;
			this->F_IF_SELECT_TX1_A->Location = System::Drawing::Point(8, 4);
			this->F_IF_SELECT_TX1_A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IF_SELECT_TX1_A->Name = L"F_IF_SELECT_TX1_A";
			this->F_IF_SELECT_TX1_A->Size = System::Drawing::Size(38, 24);
			this->F_IF_SELECT_TX1_A->TabIndex = 60;
			this->F_IF_SELECT_TX1_A->TabStop = true;
			this->F_IF_SELECT_TX1_A->Text = L"A";
			this->F_IF_SELECT_TX1_A->UseVisualStyleBackColor = true;
			this->F_IF_SELECT_TX1_A->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_IF_SELECT_TX1_A_CheckedChanged);
			// 
			// F_TX1_ON
			// 
			this->F_TX1_ON->AutoSize = true;
			this->F_TX1_ON->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX1_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_TX1_ON->ForeColor = System::Drawing::Color::White;
			this->F_TX1_ON->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX1_ON->Location = System::Drawing::Point(30, 277);
			this->F_TX1_ON->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_TX1_ON->Name = L"F_TX1_ON";
			this->F_TX1_ON->Size = System::Drawing::Size(82, 24);
			this->F_TX1_ON->TabIndex = 36;
			this->F_TX1_ON->Text = L"TX1 (V)";
			this->F_TX1_ON->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX1_ON->UseVisualStyleBackColor = true;
			this->F_TX1_ON->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_TX1_ON_CheckedChanged);
			// 
			// F_PROBE_ON
			// 
			this->F_PROBE_ON->AutoSize = true;
			this->F_PROBE_ON->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_PROBE_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_PROBE_ON->ForeColor = System::Drawing::Color::White;
			this->F_PROBE_ON->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_PROBE_ON->Location = System::Drawing::Point(42, 373);
			this->F_PROBE_ON->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_PROBE_ON->Name = L"F_PROBE_ON";
			this->F_PROBE_ON->Size = System::Drawing::Size(70, 24);
			this->F_PROBE_ON->TabIndex = 40;
			this->F_PROBE_ON->Text = L"Probe";
			this->F_PROBE_ON->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_PROBE_ON->UseVisualStyleBackColor = true;
			this->F_PROBE_ON->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_PROBE_ON_CheckedChanged);
			// 
			// F_TX3_ON
			// 
			this->F_TX3_ON->AutoSize = true;
			this->F_TX3_ON->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX3_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_TX3_ON->ForeColor = System::Drawing::Color::White;
			this->F_TX3_ON->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX3_ON->Location = System::Drawing::Point(30, 339);
			this->F_TX3_ON->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_TX3_ON->Name = L"F_TX3_ON";
			this->F_TX3_ON->Size = System::Drawing::Size(82, 24);
			this->F_TX3_ON->TabIndex = 37;
			this->F_TX3_ON->Text = L"TX3 (C)";
			this->F_TX3_ON->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX3_ON->UseVisualStyleBackColor = true;
			this->F_TX3_ON->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_TX3_ON_CheckedChanged);
			// 
			// label99
			// 
			this->label99->AutoSize = true;
			this->label99->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label99->ForeColor = System::Drawing::Color::White;
			this->label99->Location = System::Drawing::Point(10, 155);
			this->label99->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label99->Name = L"label99";
			this->label99->Size = System::Drawing::Size(79, 20);
			this->label99->TabIndex = 68;
			this->label99->Text = L"Gain [dB]:";
			// 
			// F_TX2_ON
			// 
			this->F_TX2_ON->AutoSize = true;
			this->F_TX2_ON->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX2_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_TX2_ON->ForeColor = System::Drawing::Color::White;
			this->F_TX2_ON->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX2_ON->Location = System::Drawing::Point(29, 311);
			this->F_TX2_ON->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_TX2_ON->Name = L"F_TX2_ON";
			this->F_TX2_ON->Size = System::Drawing::Size(83, 24);
			this->F_TX2_ON->TabIndex = 38;
			this->F_TX2_ON->Text = L"TX2 (H)";
			this->F_TX2_ON->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_TX2_ON->UseVisualStyleBackColor = true;
			this->F_TX2_ON->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_TX2_ON_CheckedChanged);
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label28->ForeColor = System::Drawing::Color::White;
			this->label28->Location = System::Drawing::Point(113, 14);
			this->label28->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(52, 20);
			this->label28->TabIndex = 69;
			this->label28->Text = L"CH-A:";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->ForeColor = System::Drawing::Color::White;
			this->label26->Location = System::Drawing::Point(14, 447);
			this->label26->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(94, 20);
			this->label26->TabIndex = 16;
			this->label26->Text = L"FIFO length";
			this->label26->Visible = false;
			// 
			// F_ATTN_RX4
			// 
			this->F_ATTN_RX4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_ATTN_RX4->Location = System::Drawing::Point(176, 241);
			this->F_ATTN_RX4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_ATTN_RX4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->F_ATTN_RX4->Name = L"F_ATTN_RX4";
			this->F_ATTN_RX4->Size = System::Drawing::Size(42, 26);
			this->F_ATTN_RX4->TabIndex = 48;
			this->F_ATTN_RX4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_ATTN_RX4->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_ATTN_RX4_ValueChanged);
			// 
			// F_IO_UPDATE_ON
			// 
			this->F_IO_UPDATE_ON->AutoSize = true;
			this->F_IO_UPDATE_ON->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->F_IO_UPDATE_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_IO_UPDATE_ON->ForeColor = System::Drawing::Color::White;
			this->F_IO_UPDATE_ON->Location = System::Drawing::Point(12, 474);
			this->F_IO_UPDATE_ON->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IO_UPDATE_ON->Name = L"F_IO_UPDATE_ON";
			this->F_IO_UPDATE_ON->Size = System::Drawing::Size(104, 24);
			this->F_IO_UPDATE_ON->TabIndex = 54;
			this->F_IO_UPDATE_ON->Text = L"IO_update";
			this->F_IO_UPDATE_ON->UseVisualStyleBackColor = true;
			this->F_IO_UPDATE_ON->Visible = false;
			this->F_IO_UPDATE_ON->CheckedChanged += gcnew System::EventHandler(this, &MyForm::F_IO_UPDATE_ON_CheckedChanged);
			// 
			// F_Profile_AD9910B
			// 
			this->F_Profile_AD9910B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_Profile_AD9910B->Location = System::Drawing::Point(173, 38);
			this->F_Profile_AD9910B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_Profile_AD9910B->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
			this->F_Profile_AD9910B->Name = L"F_Profile_AD9910B";
			this->F_Profile_AD9910B->Size = System::Drawing::Size(44, 26);
			this->F_Profile_AD9910B->TabIndex = 59;
			this->F_Profile_AD9910B->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_Profile_AD9910B->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_Profile_AD9910B_ValueChanged);
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label25->ForeColor = System::Drawing::Color::White;
			this->label25->Location = System::Drawing::Point(17, 509);
			this->label25->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(101, 20);
			this->label25->TabIndex = 17;
			this->label25->Text = L"Buffer length";
			// 
			// F_Profile_AD9910A
			// 
			this->F_Profile_AD9910A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_Profile_AD9910A->Location = System::Drawing::Point(115, 38);
			this->F_Profile_AD9910A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_Profile_AD9910A->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
			this->F_Profile_AD9910A->Name = L"F_Profile_AD9910A";
			this->F_Profile_AD9910A->Size = System::Drawing::Size(47, 26);
			this->F_Profile_AD9910A->TabIndex = 58;
			this->F_Profile_AD9910A->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_Profile_AD9910A->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_Profile_AD9910A_ValueChanged);
			// 
			// F_FIFO_length
			// 
			this->F_FIFO_length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_FIFO_length->Location = System::Drawing::Point(21, 447);
			this->F_FIFO_length->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_FIFO_length->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->F_FIFO_length->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, System::Int32::MinValue });
			this->F_FIFO_length->Name = L"F_FIFO_length";
			this->F_FIFO_length->Size = System::Drawing::Size(58, 26);
			this->F_FIFO_length->TabIndex = 53;
			this->F_FIFO_length->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_FIFO_length->Visible = false;
			this->F_FIFO_length->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_FIFO_length_ValueChanged);
			// 
			// F_chip_length_AD9910A
			// 
			this->F_chip_length_AD9910A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_chip_length_AD9910A->Location = System::Drawing::Point(115, 66);
			this->F_chip_length_AD9910A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_chip_length_AD9910A->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->F_chip_length_AD9910A->Name = L"F_chip_length_AD9910A";
			this->F_chip_length_AD9910A->Size = System::Drawing::Size(47, 26);
			this->F_chip_length_AD9910A->TabIndex = 57;
			this->F_chip_length_AD9910A->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_chip_length_AD9910A->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_chip_length_AD9910A_ValueChanged);
			// 
			// F_Buffer_length
			// 
			this->F_Buffer_length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_Buffer_length->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->F_Buffer_length->Location = System::Drawing::Point(161, 506);
			this->F_Buffer_length->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_Buffer_length->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			this->F_Buffer_length->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->F_Buffer_length->Name = L"F_Buffer_length";
			this->F_Buffer_length->Size = System::Drawing::Size(58, 26);
			this->F_Buffer_length->TabIndex = 52;
			this->F_Buffer_length->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_Buffer_length->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->F_Buffer_length->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_Buffer_length_ValueChanged);
			// 
			// F_ATTN_RX3
			// 
			this->F_ATTN_RX3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_ATTN_RX3->Location = System::Drawing::Point(176, 212);
			this->F_ATTN_RX3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_ATTN_RX3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->F_ATTN_RX3->Name = L"F_ATTN_RX3";
			this->F_ATTN_RX3->Size = System::Drawing::Size(42, 26);
			this->F_ATTN_RX3->TabIndex = 47;
			this->F_ATTN_RX3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_ATTN_RX3->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_ATTN_RX3_ValueChanged);
			// 
			// F_chip_length_AD9910B
			// 
			this->F_chip_length_AD9910B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_chip_length_AD9910B->Location = System::Drawing::Point(173, 66);
			this->F_chip_length_AD9910B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_chip_length_AD9910B->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->F_chip_length_AD9910B->Name = L"F_chip_length_AD9910B";
			this->F_chip_length_AD9910B->Size = System::Drawing::Size(44, 26);
			this->F_chip_length_AD9910B->TabIndex = 56;
			this->F_chip_length_AD9910B->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_chip_length_AD9910B->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_chip_length_AD9910B_ValueChanged);
			// 
			// F_IO_UPDATE_rate
			// 
			this->F_IO_UPDATE_rate->DecimalPlaces = 3;
			this->F_IO_UPDATE_rate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_IO_UPDATE_rate->Location = System::Drawing::Point(115, 126);
			this->F_IO_UPDATE_rate->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_IO_UPDATE_rate->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 155, 0, 0, 0 });
			this->F_IO_UPDATE_rate->Name = L"F_IO_UPDATE_rate";
			this->F_IO_UPDATE_rate->Size = System::Drawing::Size(47, 17);
			this->F_IO_UPDATE_rate->TabIndex = 55;
			this->F_IO_UPDATE_rate->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_IO_UPDATE_rate->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_IO_UPDATE_rate_ValueChanged);
			// 
			// F_ATTN_RX2
			// 
			this->F_ATTN_RX2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_ATTN_RX2->Location = System::Drawing::Point(176, 185);
			this->F_ATTN_RX2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_ATTN_RX2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->F_ATTN_RX2->Name = L"F_ATTN_RX2";
			this->F_ATTN_RX2->Size = System::Drawing::Size(42, 26);
			this->F_ATTN_RX2->TabIndex = 46;
			this->F_ATTN_RX2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_ATTN_RX2->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_ATTN_RX2_ValueChanged);
			// 
			// F_AD9910_Set_aux_dac_B
			// 
			this->F_AD9910_Set_aux_dac_B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_AD9910_Set_aux_dac_B->Location = System::Drawing::Point(173, 94);
			this->F_AD9910_Set_aux_dac_B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_AD9910_Set_aux_dac_B->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
			this->F_AD9910_Set_aux_dac_B->Name = L"F_AD9910_Set_aux_dac_B";
			this->F_AD9910_Set_aux_dac_B->Size = System::Drawing::Size(44, 26);
			this->F_AD9910_Set_aux_dac_B->TabIndex = 50;
			this->F_AD9910_Set_aux_dac_B->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_AD9910_Set_aux_dac_B->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_AD9910_Set_aux_dac_B_ValueChanged);
			// 
			// F_AD9910_Set_aux_dac_A
			// 
			this->F_AD9910_Set_aux_dac_A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_AD9910_Set_aux_dac_A->Location = System::Drawing::Point(115, 94);
			this->F_AD9910_Set_aux_dac_A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_AD9910_Set_aux_dac_A->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
			this->F_AD9910_Set_aux_dac_A->Name = L"F_AD9910_Set_aux_dac_A";
			this->F_AD9910_Set_aux_dac_A->Size = System::Drawing::Size(47, 26);
			this->F_AD9910_Set_aux_dac_A->TabIndex = 49;
			this->F_AD9910_Set_aux_dac_A->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_AD9910_Set_aux_dac_A->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_AD9910_Set_aux_dac_A_ValueChanged);
			// 
			// F_ATTN_RX1
			// 
			this->F_ATTN_RX1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_ATTN_RX1->Location = System::Drawing::Point(176, 157);
			this->F_ATTN_RX1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_ATTN_RX1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->F_ATTN_RX1->Name = L"F_ATTN_RX1";
			this->F_ATTN_RX1->Size = System::Drawing::Size(42, 26);
			this->F_ATTN_RX1->TabIndex = 45;
			this->F_ATTN_RX1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_ATTN_RX1->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_ATTN_RX1_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(59, 39);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Profile";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->ForeColor = System::Drawing::Color::White;
			this->label22->Location = System::Drawing::Point(70, 95);
			this->label22->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(43, 20);
			this->label22->TabIndex = 20;
			this->label22->Text = L"Gain";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(71, 124);
			this->label8->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(41, 20);
			this->label8->TabIndex = 4;
			this->label8->Text = L"PRF";
			// 
			// F_ATTN_TX3
			// 
			this->F_ATTN_TX3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_ATTN_TX3->Location = System::Drawing::Point(74, 240);
			this->F_ATTN_TX3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_ATTN_TX3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->F_ATTN_TX3->Name = L"F_ATTN_TX3";
			this->F_ATTN_TX3->Size = System::Drawing::Size(42, 26);
			this->F_ATTN_TX3->TabIndex = 44;
			this->F_ATTN_TX3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_ATTN_TX3->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_ATTN_TX3_ValueChanged);
			// 
			// F_ATTN_TX2
			// 
			this->F_ATTN_TX2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_ATTN_TX2->Location = System::Drawing::Point(74, 212);
			this->F_ATTN_TX2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_ATTN_TX2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->F_ATTN_TX2->Name = L"F_ATTN_TX2";
			this->F_ATTN_TX2->Size = System::Drawing::Size(42, 26);
			this->F_ATTN_TX2->TabIndex = 43;
			this->F_ATTN_TX2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_ATTN_TX2->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_ATTN_TX2_ValueChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(71, 68);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 20);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Chip";
			// 
			// F_ATTN_TX1
			// 
			this->F_ATTN_TX1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->F_ATTN_TX1->Location = System::Drawing::Point(74, 183);
			this->F_ATTN_TX1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_ATTN_TX1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->F_ATTN_TX1->Name = L"F_ATTN_TX1";
			this->F_ATTN_TX1->Size = System::Drawing::Size(42, 26);
			this->F_ATTN_TX1->TabIndex = 42;
			this->F_ATTN_TX1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_ATTN_TX1->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_ATTN_TX1_ValueChanged);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->ForeColor = System::Drawing::Color::White;
			this->label16->Location = System::Drawing::Point(35, 215);
			this->label16->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(38, 20);
			this->label16->TabIndex = 8;
			this->label16->Text = L"TX2";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->ForeColor = System::Drawing::Color::White;
			this->label17->Location = System::Drawing::Point(35, 243);
			this->label17->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(38, 20);
			this->label17->TabIndex = 25;
			this->label17->Text = L"TX3";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->Location = System::Drawing::Point(35, 186);
			this->label15->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(38, 20);
			this->label15->TabIndex = 9;
			this->label15->Text = L"TX1";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->ForeColor = System::Drawing::Color::White;
			this->label18->Location = System::Drawing::Point(137, 160);
			this->label18->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(41, 20);
			this->label18->TabIndex = 24;
			this->label18->Text = L"RX1";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->ForeColor = System::Drawing::Color::White;
			this->label21->Location = System::Drawing::Point(137, 244);
			this->label21->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(41, 20);
			this->label21->TabIndex = 21;
			this->label21->Text = L"RX4";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->ForeColor = System::Drawing::Color::White;
			this->label20->Location = System::Drawing::Point(137, 217);
			this->label20->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(41, 20);
			this->label20->TabIndex = 22;
			this->label20->Text = L"RX3";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->ForeColor = System::Drawing::Color::White;
			this->label19->Location = System::Drawing::Point(137, 186);
			this->label19->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(41, 20);
			this->label19->TabIndex = 23;
			this->label19->Text = L"RX2";
			// 
			// groupBox10
			// 
			this->groupBox10->Controls->Add(this->label135);
			this->groupBox10->Controls->Add(this->label121);
			this->groupBox10->Controls->Add(this->F_CALIBRATOR_TGT_START);
			this->groupBox10->Controls->Add(this->label119);
			this->groupBox10->Controls->Add(this->F_CALIBRATOR_TGT_END);
			this->groupBox10->Controls->Add(this->label120);
			this->groupBox10->Controls->Add(this->F_PROBE_CALIBRATE_TGT_START);
			this->groupBox10->Controls->Add(this->label104);
			this->groupBox10->Controls->Add(this->F_PROBE_CALIBRATE_TGT_END);
			this->groupBox10->Controls->Add(this->label105);
			this->groupBox10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->groupBox10->ForeColor = System::Drawing::Color::White;
			this->groupBox10->Location = System::Drawing::Point(402, 6);
			this->groupBox10->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox10->Size = System::Drawing::Size(207, 177);
			this->groupBox10->TabIndex = 156;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"Calibration Configuration";
			// 
			// label135
			// 
			this->label135->AutoSize = true;
			this->label135->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label135->ForeColor = System::Drawing::Color::White;
			this->label135->Location = System::Drawing::Point(111, 99);
			this->label135->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label135->Name = L"label135";
			this->label135->Size = System::Drawing::Size(54, 13);
			this->label135->TabIndex = 59;
			this->label135->Text = L"Calibrator:";
			// 
			// label121
			// 
			this->label121->AutoSize = true;
			this->label121->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label121->ForeColor = System::Drawing::Color::White;
			this->label121->Location = System::Drawing::Point(111, 15);
			this->label121->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label121->Name = L"label121";
			this->label121->Size = System::Drawing::Size(38, 13);
			this->label121->TabIndex = 58;
			this->label121->Text = L"Probe:";
			// 
			// F_CALIBRATOR_TGT_START
			// 
			this->F_CALIBRATOR_TGT_START->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_CALIBRATOR_TGT_START->Location = System::Drawing::Point(115, 118);
			this->F_CALIBRATOR_TGT_START->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_CALIBRATOR_TGT_START->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->F_CALIBRATOR_TGT_START->Name = L"F_CALIBRATOR_TGT_START";
			this->F_CALIBRATOR_TGT_START->Size = System::Drawing::Size(55, 20);
			this->F_CALIBRATOR_TGT_START->TabIndex = 54;
			this->F_CALIBRATOR_TGT_START->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_CALIBRATOR_TGT_START->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_CALIBRATOR_TGT_START_ValueChanged);
			// 
			// label119
			// 
			this->label119->AutoSize = true;
			this->label119->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label119->ForeColor = System::Drawing::Color::White;
			this->label119->Location = System::Drawing::Point(33, 123);
			this->label119->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label119->Name = L"label119";
			this->label119->Size = System::Drawing::Size(79, 13);
			this->label119->TabIndex = 56;
			this->label119->Text = L"START sample";
			// 
			// F_CALIBRATOR_TGT_END
			// 
			this->F_CALIBRATOR_TGT_END->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_CALIBRATOR_TGT_END->Location = System::Drawing::Point(115, 149);
			this->F_CALIBRATOR_TGT_END->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_CALIBRATOR_TGT_END->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->F_CALIBRATOR_TGT_END->Name = L"F_CALIBRATOR_TGT_END";
			this->F_CALIBRATOR_TGT_END->Size = System::Drawing::Size(55, 20);
			this->F_CALIBRATOR_TGT_END->TabIndex = 55;
			this->F_CALIBRATOR_TGT_END->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_CALIBRATOR_TGT_END->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_CALIBRATOR_TGT_END_ValueChanged);
			// 
			// label120
			// 
			this->label120->AutoSize = true;
			this->label120->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label120->ForeColor = System::Drawing::Color::White;
			this->label120->Location = System::Drawing::Point(45, 150);
			this->label120->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label120->Name = L"label120";
			this->label120->Size = System::Drawing::Size(66, 13);
			this->label120->TabIndex = 57;
			this->label120->Text = L"END sample";
			// 
			// F_PROBE_CALIBRATE_TGT_START
			// 
			this->F_PROBE_CALIBRATE_TGT_START->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_PROBE_CALIBRATE_TGT_START->Location = System::Drawing::Point(115, 34);
			this->F_PROBE_CALIBRATE_TGT_START->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_PROBE_CALIBRATE_TGT_START->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->F_PROBE_CALIBRATE_TGT_START->Name = L"F_PROBE_CALIBRATE_TGT_START";
			this->F_PROBE_CALIBRATE_TGT_START->Size = System::Drawing::Size(55, 20);
			this->F_PROBE_CALIBRATE_TGT_START->TabIndex = 0;
			this->F_PROBE_CALIBRATE_TGT_START->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_PROBE_CALIBRATE_TGT_START->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_PROBE_CALIBRATE_TGT_START_ValueChanged);
			// 
			// label104
			// 
			this->label104->AutoSize = true;
			this->label104->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label104->ForeColor = System::Drawing::Color::White;
			this->label104->Location = System::Drawing::Point(33, 39);
			this->label104->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label104->Name = L"label104";
			this->label104->Size = System::Drawing::Size(79, 13);
			this->label104->TabIndex = 52;
			this->label104->Text = L"START sample";
			// 
			// F_PROBE_CALIBRATE_TGT_END
			// 
			this->F_PROBE_CALIBRATE_TGT_END->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->F_PROBE_CALIBRATE_TGT_END->Location = System::Drawing::Point(115, 63);
			this->F_PROBE_CALIBRATE_TGT_END->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->F_PROBE_CALIBRATE_TGT_END->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->F_PROBE_CALIBRATE_TGT_END->Name = L"F_PROBE_CALIBRATE_TGT_END";
			this->F_PROBE_CALIBRATE_TGT_END->Size = System::Drawing::Size(55, 20);
			this->F_PROBE_CALIBRATE_TGT_END->TabIndex = 1;
			this->F_PROBE_CALIBRATE_TGT_END->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->F_PROBE_CALIBRATE_TGT_END->ValueChanged += gcnew System::EventHandler(this, &MyForm::F_PROBE_CALIBRATE_TGT_END_ValueChanged);
			// 
			// label105
			// 
			this->label105->AutoSize = true;
			this->label105->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label105->ForeColor = System::Drawing::Color::White;
			this->label105->Location = System::Drawing::Point(45, 66);
			this->label105->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label105->Name = L"label105";
			this->label105->Size = System::Drawing::Size(66, 13);
			this->label105->TabIndex = 53;
			this->label105->Text = L"END sample";
			// 
			// Debug
			// 
			this->Debug->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->Debug->Controls->Add(this->B_PROBE_TEST);
			this->Debug->Controls->Add(this->B_SNAPSHOT);
			this->Debug->Controls->Add(this->label193);
			this->Debug->Controls->Add(this->label192);
			this->Debug->Controls->Add(this->label191);
			this->Debug->Controls->Add(this->label190);
			this->Debug->Controls->Add(this->label188);
			this->Debug->Controls->Add(this->label189);
			this->Debug->Controls->Add(this->label185);
			this->Debug->Controls->Add(this->label187);
			this->Debug->Controls->Add(this->label183);
			this->Debug->Controls->Add(this->label184);
			this->Debug->Controls->Add(this->label186);
			this->Debug->Controls->Add(this->label182);
			this->Debug->Controls->Add(this->label181);
			this->Debug->Controls->Add(this->label180);
			this->Debug->Controls->Add(this->label179);
			this->Debug->Controls->Add(this->label178);
			this->Debug->Controls->Add(this->B_PROBE_TEST_PLOT);
			this->Debug->Controls->Add(this->groupBox1);
			this->Debug->ForeColor = System::Drawing::Color::White;
			this->Debug->Location = System::Drawing::Point(4, 22);
			this->Debug->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->Debug->Name = L"Debug";
			this->Debug->Size = System::Drawing::Size(828, 590);
			this->Debug->TabIndex = 2;
			this->Debug->Text = L"Data Visualization";
			// 
			// B_PROBE_TEST
			// 
			this->B_PROBE_TEST->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_PROBE_TEST->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_PROBE_TEST->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_PROBE_TEST->ForeColor = System::Drawing::Color::Black;
			this->B_PROBE_TEST->Location = System::Drawing::Point(666, 12);
			this->B_PROBE_TEST->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PROBE_TEST->Name = L"B_PROBE_TEST";
			this->B_PROBE_TEST->Size = System::Drawing::Size(140, 36);
			this->B_PROBE_TEST->TabIndex = 152;
			this->B_PROBE_TEST->Text = L"PROBE TEST";
			this->B_PROBE_TEST->UseVisualStyleBackColor = false;
			this->B_PROBE_TEST->Click += gcnew System::EventHandler(this, &MyForm::B_PROBE_TEST_Click);
			// 
			// B_SNAPSHOT
			// 
			this->B_SNAPSHOT->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(181)), static_cast<System::Int32>(static_cast<System::Byte>(181)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_SNAPSHOT->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->B_SNAPSHOT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_SNAPSHOT->ForeColor = System::Drawing::Color::Black;
			this->B_SNAPSHOT->Location = System::Drawing::Point(667, 67);
			this->B_SNAPSHOT->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SNAPSHOT->Name = L"B_SNAPSHOT";
			this->B_SNAPSHOT->Size = System::Drawing::Size(139, 36);
			this->B_SNAPSHOT->TabIndex = 30;
			this->B_SNAPSHOT->Text = L"SNAPSHOT";
			this->B_SNAPSHOT->UseVisualStyleBackColor = false;
			this->B_SNAPSHOT->Click += gcnew System::EventHandler(this, &MyForm::B_SNAPSHOT_Click);
			// 
			// label193
			// 
			this->label193->AutoSize = true;
			this->label193->Location = System::Drawing::Point(406, 453);
			this->label193->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label193->Name = L"label193";
			this->label193->Size = System::Drawing::Size(42, 13);
			this->label193->TabIndex = 180;
			this->label193->Text = L"Right V";
			// 
			// label192
			// 
			this->label192->AutoSize = true;
			this->label192->Location = System::Drawing::Point(405, 257);
			this->label192->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label192->Name = L"label192";
			this->label192->Size = System::Drawing::Size(43, 13);
			this->label192->TabIndex = 179;
			this->label192->Text = L"Right H";
			// 
			// label191
			// 
			this->label191->AutoSize = true;
			this->label191->Location = System::Drawing::Point(12, 453);
			this->label191->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label191->Name = L"label191";
			this->label191->Size = System::Drawing::Size(35, 13);
			this->label191->TabIndex = 178;
			this->label191->Text = L"Left V";
			// 
			// label190
			// 
			this->label190->AutoSize = true;
			this->label190->Location = System::Drawing::Point(19, 257);
			this->label190->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label190->Name = L"label190";
			this->label190->Size = System::Drawing::Size(36, 13);
			this->label190->TabIndex = 177;
			this->label190->Text = L"Left H";
			// 
			// label188
			// 
			this->label188->AutoSize = true;
			this->label188->BackColor = System::Drawing::Color::White;
			this->label188->Font = (gcnew System::Drawing::Font(L"Miriam Fixed", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(177)));
			this->label188->ForeColor = System::Drawing::Color::Red;
			this->label188->Location = System::Drawing::Point(357, 401);
			this->label188->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label188->Name = L"label188";
			this->label188->Size = System::Drawing::Size(21, 19);
			this->label188->TabIndex = 176;
			this->label188->Text = L"Q";
			// 
			// label189
			// 
			this->label189->AutoSize = true;
			this->label189->BackColor = System::Drawing::Color::White;
			this->label189->Font = (gcnew System::Drawing::Font(L"Miriam Fixed", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(177)));
			this->label189->ForeColor = System::Drawing::Color::Blue;
			this->label189->Location = System::Drawing::Point(332, 403);
			this->label189->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label189->Name = L"label189";
			this->label189->Size = System::Drawing::Size(21, 19);
			this->label189->TabIndex = 175;
			this->label189->Text = L"I";
			// 
			// label185
			// 
			this->label185->AutoSize = true;
			this->label185->BackColor = System::Drawing::Color::White;
			this->label185->Font = (gcnew System::Drawing::Font(L"Miriam Fixed", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(177)));
			this->label185->ForeColor = System::Drawing::Color::Red;
			this->label185->Location = System::Drawing::Point(756, 401);
			this->label185->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label185->Name = L"label185";
			this->label185->Size = System::Drawing::Size(21, 19);
			this->label185->TabIndex = 174;
			this->label185->Text = L"Q";
			// 
			// label187
			// 
			this->label187->AutoSize = true;
			this->label187->BackColor = System::Drawing::Color::White;
			this->label187->Font = (gcnew System::Drawing::Font(L"Miriam Fixed", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(177)));
			this->label187->ForeColor = System::Drawing::Color::Blue;
			this->label187->Location = System::Drawing::Point(731, 402);
			this->label187->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label187->Name = L"label187";
			this->label187->Size = System::Drawing::Size(21, 19);
			this->label187->TabIndex = 173;
			this->label187->Text = L"I";
			// 
			// label183
			// 
			this->label183->AutoSize = true;
			this->label183->BackColor = System::Drawing::Color::White;
			this->label183->Font = (gcnew System::Drawing::Font(L"Miriam Fixed", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(177)));
			this->label183->ForeColor = System::Drawing::Color::Red;
			this->label183->Location = System::Drawing::Point(357, 204);
			this->label183->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label183->Name = L"label183";
			this->label183->Size = System::Drawing::Size(21, 19);
			this->label183->TabIndex = 172;
			this->label183->Text = L"Q";
			// 
			// label184
			// 
			this->label184->AutoSize = true;
			this->label184->BackColor = System::Drawing::Color::White;
			this->label184->Font = (gcnew System::Drawing::Font(L"Miriam Fixed", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(177)));
			this->label184->ForeColor = System::Drawing::Color::Blue;
			this->label184->Location = System::Drawing::Point(332, 205);
			this->label184->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label184->Name = L"label184";
			this->label184->Size = System::Drawing::Size(21, 19);
			this->label184->TabIndex = 171;
			this->label184->Text = L"I";
			// 
			// label186
			// 
			this->label186->AutoSize = true;
			this->label186->BackColor = System::Drawing::Color::White;
			this->label186->Font = (gcnew System::Drawing::Font(L"Miriam Fixed", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(177)));
			this->label186->ForeColor = System::Drawing::Color::Red;
			this->label186->Location = System::Drawing::Point(756, 204);
			this->label186->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label186->Name = L"label186";
			this->label186->Size = System::Drawing::Size(21, 19);
			this->label186->TabIndex = 170;
			this->label186->Text = L"Q";
			// 
			// label182
			// 
			this->label182->AutoSize = true;
			this->label182->BackColor = System::Drawing::Color::White;
			this->label182->Font = (gcnew System::Drawing::Font(L"Miriam Fixed", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(177)));
			this->label182->ForeColor = System::Drawing::Color::Blue;
			this->label182->Location = System::Drawing::Point(731, 205);
			this->label182->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label182->Name = L"label182";
			this->label182->Size = System::Drawing::Size(21, 19);
			this->label182->TabIndex = 166;
			this->label182->Text = L"I";
			// 
			// label181
			// 
			this->label181->AutoSize = true;
			this->label181->Location = System::Drawing::Point(616, 565);
			this->label181->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label181->Name = L"label181";
			this->label181->Size = System::Drawing::Size(51, 13);
			this->label181->TabIndex = 165;
			this->label181->Text = L"[samples]";
			// 
			// label180
			// 
			this->label180->AutoSize = true;
			this->label180->Location = System::Drawing::Point(226, 565);
			this->label180->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label180->Name = L"label180";
			this->label180->Size = System::Drawing::Size(51, 13);
			this->label180->TabIndex = 164;
			this->label180->Text = L"[samples]";
			// 
			// label179
			// 
			this->label179->AutoSize = true;
			this->label179->Location = System::Drawing::Point(616, 364);
			this->label179->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label179->Name = L"label179";
			this->label179->Size = System::Drawing::Size(51, 13);
			this->label179->TabIndex = 163;
			this->label179->Text = L"[samples]";
			// 
			// label178
			// 
			this->label178->AutoSize = true;
			this->label178->Location = System::Drawing::Point(226, 364);
			this->label178->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label178->Name = L"label178";
			this->label178->Size = System::Drawing::Size(51, 13);
			this->label178->TabIndex = 162;
			this->label178->Text = L"[samples]";
			// 
			// B_PROBE_TEST_PLOT
			// 
			this->B_PROBE_TEST_PLOT->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(86)));
			chartArea13->AxisX->Interval = 200;
			chartArea13->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea13->AxisX->Maximum = 1024;
			chartArea13->AxisX->Minimum = 0;
			chartArea13->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea13->AxisY->Interval = 0.5;
			chartArea13->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea13->AxisY->Maximum = 1;
			chartArea13->AxisY->Minimum = -1;
			chartArea13->IsSameFontSizeForAllAxes = true;
			chartArea13->Name = L"Left_H";
			chartArea14->AxisX->Interval = 200;
			chartArea14->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea14->AxisX->Maximum = 1024;
			chartArea14->AxisX->Minimum = 0;
			chartArea14->AxisY->Interval = 0.5;
			chartArea14->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea14->AxisY->Maximum = 1;
			chartArea14->AxisY->Minimum = -1;
			chartArea14->Name = L"Left_V";
			chartArea15->AxisX->Interval = 200;
			chartArea15->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea15->AxisX->Maximum = 1024;
			chartArea15->AxisX->Minimum = 0;
			chartArea15->AxisY->Interval = 0.5;
			chartArea15->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea15->AxisY->Maximum = 1;
			chartArea15->AxisY->Minimum = -1;
			chartArea15->Name = L"Right_H";
			chartArea16->AxisX->Interval = 200;
			chartArea16->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea16->AxisX->Maximum = 1024;
			chartArea16->AxisX->Minimum = 0;
			chartArea16->AxisY->Interval = 0.5;
			chartArea16->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea16->AxisY->Maximum = 1;
			chartArea16->AxisY->Minimum = -1;
			chartArea16->Name = L"Right_V";
			this->B_PROBE_TEST_PLOT->ChartAreas->Add(chartArea13);
			this->B_PROBE_TEST_PLOT->ChartAreas->Add(chartArea14);
			this->B_PROBE_TEST_PLOT->ChartAreas->Add(chartArea15);
			this->B_PROBE_TEST_PLOT->ChartAreas->Add(chartArea16);
			legend10->Enabled = false;
			legend10->Name = L"Legend1";
			this->B_PROBE_TEST_PLOT->Legends->Add(legend10);
			this->B_PROBE_TEST_PLOT->Location = System::Drawing::Point(8, 172);
			this->B_PROBE_TEST_PLOT->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PROBE_TEST_PLOT->Name = L"B_PROBE_TEST_PLOT";
			series31->BorderWidth = 2;
			series31->ChartArea = L"Left_H";
			series31->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series31->Color = System::Drawing::Color::Blue;
			series31->Label = L"I";
			series31->Legend = L"Legend1";
			series31->LegendText = L"I";
			series31->Name = L"LH_I";
			series32->BorderWidth = 2;
			series32->ChartArea = L"Left_H";
			series32->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series32->Color = System::Drawing::Color::Red;
			series32->Label = L"Q";
			series32->Legend = L"Legend1";
			series32->LegendText = L"Q";
			series32->Name = L"LH_Q";
			series33->BorderWidth = 2;
			series33->ChartArea = L"Left_V";
			series33->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series33->Color = System::Drawing::Color::Blue;
			series33->Label = L"I";
			series33->Legend = L"Legend1";
			series33->LegendText = L"I";
			series33->Name = L"LV_I";
			series34->BorderWidth = 2;
			series34->ChartArea = L"Left_V";
			series34->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series34->Color = System::Drawing::Color::Red;
			series34->Legend = L"Legend1";
			series34->LegendText = L"Q";
			series34->Name = L"LV_Q";
			series35->BorderWidth = 2;
			series35->ChartArea = L"Right_H";
			series35->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series35->Color = System::Drawing::Color::Blue;
			series35->Legend = L"Legend1";
			series35->LegendText = L"I";
			series35->Name = L"RH_I";
			series36->BorderWidth = 2;
			series36->ChartArea = L"Right_H";
			series36->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series36->Color = System::Drawing::Color::Red;
			series36->Legend = L"Legend1";
			series36->LegendText = L"Q";
			series36->Name = L"RH_Q";
			series37->BorderWidth = 2;
			series37->ChartArea = L"Right_V";
			series37->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series37->Color = System::Drawing::Color::Blue;
			series37->Legend = L"Legend1";
			series37->LegendText = L"I";
			series37->Name = L"RV_I";
			series38->BorderWidth = 2;
			series38->ChartArea = L"Right_V";
			series38->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series38->Color = System::Drawing::Color::Red;
			series38->Legend = L"Legend1";
			series38->LegendText = L"Q";
			series38->Name = L"RV_Q";
			series38->Points->Add(dataPoint2);
			this->B_PROBE_TEST_PLOT->Series->Add(series31);
			this->B_PROBE_TEST_PLOT->Series->Add(series32);
			this->B_PROBE_TEST_PLOT->Series->Add(series33);
			this->B_PROBE_TEST_PLOT->Series->Add(series34);
			this->B_PROBE_TEST_PLOT->Series->Add(series35);
			this->B_PROBE_TEST_PLOT->Series->Add(series36);
			this->B_PROBE_TEST_PLOT->Series->Add(series37);
			this->B_PROBE_TEST_PLOT->Series->Add(series38);
			this->B_PROBE_TEST_PLOT->Size = System::Drawing::Size(818, 409);
			this->B_PROBE_TEST_PLOT->TabIndex = 155;
			this->B_PROBE_TEST_PLOT->Text = L"chart1";
			// 
			// Mainenance
			// 
			this->Mainenance->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->Mainenance->Controls->Add(this->groupBox9);
			this->Mainenance->Location = System::Drawing::Point(4, 22);
			this->Mainenance->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->Mainenance->Name = L"Mainenance";
			this->Mainenance->Size = System::Drawing::Size(828, 590);
			this->Mainenance->TabIndex = 3;
			this->Mainenance->Text = L"Maintenance";
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->G_Upload_RF_MCU);
			this->groupBox9->Controls->Add(this->B_RF_MCU_Browse);
			this->groupBox9->Controls->Add(this->B_Out_RF_MCU);
			this->groupBox9->Controls->Add(this->label27);
			this->groupBox9->Controls->Add(this->label14);
			this->groupBox9->Controls->Add(this->B_RF_MCU_Version);
			this->groupBox9->Controls->Add(this->L_BUL_status_RF_MCU);
			this->groupBox9->Controls->Add(this->B_BUL_status_RF_MCU);
			this->groupBox9->Controls->Add(this->CHAB_BUL_Selector);
			this->groupBox9->Controls->Add(this->G_Upload_MCU);
			this->groupBox9->Controls->Add(this->B_OMR_VERSION);
			this->groupBox9->Controls->Add(this->G_Upload_CHAB);
			this->groupBox9->Controls->Add(this->B_DET_VERSION);
			this->groupBox9->Controls->Add(this->G_Upload_DET);
			this->groupBox9->Controls->Add(this->label48);
			this->groupBox9->Controls->Add(this->G_Upload_OMR);
			this->groupBox9->Controls->Add(this->B_MCU_Browse);
			this->groupBox9->Controls->Add(this->B_label10);
			this->groupBox9->Controls->Add(this->B_CHAB_Browse);
			this->groupBox9->Controls->Add(this->B_Out_MCU);
			this->groupBox9->Controls->Add(this->B_MCU_VERSION);
			this->groupBox9->Controls->Add(this->B_Out_CHAB);
			this->groupBox9->Controls->Add(this->B_label11);
			this->groupBox9->Controls->Add(this->label107);
			this->groupBox9->Controls->Add(this->label46);
			this->groupBox9->Controls->Add(this->label106);
			this->groupBox9->Controls->Add(this->label47);
			this->groupBox9->Controls->Add(this->label11);
			this->groupBox9->Controls->Add(this->B_CHB_VERSION);
			this->groupBox9->Controls->Add(this->B_DET_Browse);
			this->groupBox9->Controls->Add(this->B_CHA_VERSION);
			this->groupBox9->Controls->Add(this->B_Out_DET);
			this->groupBox9->Controls->Add(this->L_BUL_status_MCU);
			this->groupBox9->Controls->Add(this->B_BUL_status_OMR);
			this->groupBox9->Controls->Add(this->B_BUL_status_DET);
			this->groupBox9->Controls->Add(this->B_BUL_status_MCU);
			this->groupBox9->Controls->Add(this->B_label1);
			this->groupBox9->Controls->Add(this->L_BUL_status_OMR);
			this->groupBox9->Controls->Add(this->L_BUL_status_CHB);
			this->groupBox9->Controls->Add(this->B_OMR_Browse);
			this->groupBox9->Controls->Add(this->L_BUL_status_DET);
			this->groupBox9->Controls->Add(this->B_BUL_status_CHB);
			this->groupBox9->Controls->Add(this->B_BUL_status_CHA);
			this->groupBox9->Controls->Add(this->B_ResetAfterUpload);
			this->groupBox9->Controls->Add(this->B_Out_OMR);
			this->groupBox9->Controls->Add(this->L_BUL_status_CHA);
			this->groupBox9->ForeColor = System::Drawing::Color::White;
			this->groupBox9->Location = System::Drawing::Point(6, 13);
			this->groupBox9->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->groupBox9->Size = System::Drawing::Size(811, 240);
			this->groupBox9->TabIndex = 121;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"Software Version";
			// 
			// G_Upload_RF_MCU
			// 
			this->G_Upload_RF_MCU->ForeColor = System::Drawing::SystemColors::Desktop;
			this->G_Upload_RF_MCU->Location = System::Drawing::Point(600, 114);
			this->G_Upload_RF_MCU->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->G_Upload_RF_MCU->Name = L"G_Upload_RF_MCU";
			this->G_Upload_RF_MCU->Size = System::Drawing::Size(74, 23);
			this->G_Upload_RF_MCU->TabIndex = 137;
			this->G_Upload_RF_MCU->Text = L"Upload";
			this->G_Upload_RF_MCU->UseVisualStyleBackColor = true;
			// 
			// B_RF_MCU_Browse
			// 
			this->B_RF_MCU_Browse->ForeColor = System::Drawing::SystemColors::Desktop;
			this->B_RF_MCU_Browse->Location = System::Drawing::Point(522, 114);
			this->B_RF_MCU_Browse->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RF_MCU_Browse->Name = L"B_RF_MCU_Browse";
			this->B_RF_MCU_Browse->Size = System::Drawing::Size(74, 23);
			this->B_RF_MCU_Browse->TabIndex = 136;
			this->B_RF_MCU_Browse->Text = L"Browse...";
			this->B_RF_MCU_Browse->UseVisualStyleBackColor = true;
			// 
			// B_Out_RF_MCU
			// 
			this->B_Out_RF_MCU->Location = System::Drawing::Point(99, 116);
			this->B_Out_RF_MCU->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Out_RF_MCU->Name = L"B_Out_RF_MCU";
			this->B_Out_RF_MCU->Size = System::Drawing::Size(421, 20);
			this->B_Out_RF_MCU->TabIndex = 135;
			this->B_Out_RF_MCU->TextChanged += gcnew System::EventHandler(this, &MyForm::B_Out_RF_MCU_TextChanged);
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->BackColor = System::Drawing::Color::Transparent;
			this->label27->ForeColor = System::Drawing::Color::White;
			this->label27->Location = System::Drawing::Point(10, 120);
			this->label27->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(48, 13);
			this->label27->TabIndex = 134;
			this->label27->Text = L"RF MCU";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(658, 204);
			this->label14->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(89, 13);
			this->label14->TabIndex = 131;
			this->label14->Text = L"RF MCU Version:";
			// 
			// B_RF_MCU_Version
			// 
			this->B_RF_MCU_Version->Location = System::Drawing::Point(749, 201);
			this->B_RF_MCU_Version->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RF_MCU_Version->Name = L"B_RF_MCU_Version";
			this->B_RF_MCU_Version->ReadOnly = true;
			this->B_RF_MCU_Version->Size = System::Drawing::Size(53, 20);
			this->B_RF_MCU_Version->TabIndex = 130;
			this->B_RF_MCU_Version->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// L_BUL_status_RF_MCU
			// 
			this->L_BUL_status_RF_MCU->AutoSize = true;
			this->L_BUL_status_RF_MCU->ForeColor = System::Drawing::Color::White;
			this->L_BUL_status_RF_MCU->Location = System::Drawing::Point(659, 178);
			this->L_BUL_status_RF_MCU->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_BUL_status_RF_MCU->Name = L"L_BUL_status_RF_MCU";
			this->L_BUL_status_RF_MCU->Size = System::Drawing::Size(88, 13);
			this->L_BUL_status_RF_MCU->TabIndex = 133;
			this->L_BUL_status_RF_MCU->Text = L"Upload RF MCU:";
			// 
			// B_BUL_status_RF_MCU
			// 
			this->B_BUL_status_RF_MCU->Location = System::Drawing::Point(749, 173);
			this->B_BUL_status_RF_MCU->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_BUL_status_RF_MCU->Name = L"B_BUL_status_RF_MCU";
			this->B_BUL_status_RF_MCU->ReadOnly = true;
			this->B_BUL_status_RF_MCU->Size = System::Drawing::Size(53, 20);
			this->B_BUL_status_RF_MCU->TabIndex = 132;
			// 
			// CHAB_BUL_Selector
			// 
			this->CHAB_BUL_Selector->FormattingEnabled = true;
			this->CHAB_BUL_Selector->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Both", L"CHA", L"CHB" });
			this->CHAB_BUL_Selector->Location = System::Drawing::Point(51, 64);
			this->CHAB_BUL_Selector->Name = L"CHAB_BUL_Selector";
			this->CHAB_BUL_Selector->Size = System::Drawing::Size(44, 21);
			this->CHAB_BUL_Selector->TabIndex = 49;
			// 
			// G_Upload_MCU
			// 
			this->G_Upload_MCU->ForeColor = System::Drawing::SystemColors::Desktop;
			this->G_Upload_MCU->Location = System::Drawing::Point(601, 89);
			this->G_Upload_MCU->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->G_Upload_MCU->Name = L"G_Upload_MCU";
			this->G_Upload_MCU->Size = System::Drawing::Size(74, 23);
			this->G_Upload_MCU->TabIndex = 47;
			this->G_Upload_MCU->Text = L"Upload";
			this->G_Upload_MCU->UseVisualStyleBackColor = true;
			this->G_Upload_MCU->Click += gcnew System::EventHandler(this, &MyForm::G_Upload_MCU_Click);
			// 
			// G_Upload_CHAB
			// 
			this->G_Upload_CHAB->ForeColor = System::Drawing::SystemColors::Desktop;
			this->G_Upload_CHAB->Location = System::Drawing::Point(601, 64);
			this->G_Upload_CHAB->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->G_Upload_CHAB->Name = L"G_Upload_CHAB";
			this->G_Upload_CHAB->Size = System::Drawing::Size(74, 23);
			this->G_Upload_CHAB->TabIndex = 46;
			this->G_Upload_CHAB->Text = L"Upload";
			this->G_Upload_CHAB->UseVisualStyleBackColor = true;
			this->G_Upload_CHAB->Click += gcnew System::EventHandler(this, &MyForm::G_Upload_CHAB_Click);
			// 
			// G_Upload_DET
			// 
			this->G_Upload_DET->ForeColor = System::Drawing::SystemColors::Desktop;
			this->G_Upload_DET->Location = System::Drawing::Point(601, 39);
			this->G_Upload_DET->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->G_Upload_DET->Name = L"G_Upload_DET";
			this->G_Upload_DET->Size = System::Drawing::Size(74, 23);
			this->G_Upload_DET->TabIndex = 45;
			this->G_Upload_DET->Text = L"Upload";
			this->G_Upload_DET->UseVisualStyleBackColor = true;
			this->G_Upload_DET->Click += gcnew System::EventHandler(this, &MyForm::G_Upload_DET_Click);
			// 
			// G_Upload_OMR
			// 
			this->G_Upload_OMR->ForeColor = System::Drawing::SystemColors::Desktop;
			this->G_Upload_OMR->Location = System::Drawing::Point(601, 14);
			this->G_Upload_OMR->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->G_Upload_OMR->Name = L"G_Upload_OMR";
			this->G_Upload_OMR->Size = System::Drawing::Size(74, 23);
			this->G_Upload_OMR->TabIndex = 44;
			this->G_Upload_OMR->Text = L"Upload";
			this->G_Upload_OMR->UseVisualStyleBackColor = true;
			this->G_Upload_OMR->Click += gcnew System::EventHandler(this, &MyForm::G_Upload_OMR_Click);
			// 
			// B_MCU_Browse
			// 
			this->B_MCU_Browse->ForeColor = System::Drawing::SystemColors::Desktop;
			this->B_MCU_Browse->Location = System::Drawing::Point(523, 89);
			this->B_MCU_Browse->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_MCU_Browse->Name = L"B_MCU_Browse";
			this->B_MCU_Browse->Size = System::Drawing::Size(74, 23);
			this->B_MCU_Browse->TabIndex = 43;
			this->B_MCU_Browse->Text = L"Browse...";
			this->B_MCU_Browse->UseVisualStyleBackColor = true;
			this->B_MCU_Browse->Click += gcnew System::EventHandler(this, &MyForm::B_MCU_Browse_Click);
			// 
			// B_CHAB_Browse
			// 
			this->B_CHAB_Browse->ForeColor = System::Drawing::SystemColors::Desktop;
			this->B_CHAB_Browse->Location = System::Drawing::Point(523, 64);
			this->B_CHAB_Browse->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CHAB_Browse->Name = L"B_CHAB_Browse";
			this->B_CHAB_Browse->Size = System::Drawing::Size(74, 23);
			this->B_CHAB_Browse->TabIndex = 42;
			this->B_CHAB_Browse->Text = L"Browse...";
			this->B_CHAB_Browse->UseVisualStyleBackColor = true;
			this->B_CHAB_Browse->Click += gcnew System::EventHandler(this, &MyForm::B_CHAB_Browse_Click);
			// 
			// B_Out_MCU
			// 
			this->B_Out_MCU->Location = System::Drawing::Point(99, 91);
			this->B_Out_MCU->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Out_MCU->Name = L"B_Out_MCU";
			this->B_Out_MCU->Size = System::Drawing::Size(420, 20);
			this->B_Out_MCU->TabIndex = 37;
			this->B_Out_MCU->TextChanged += gcnew System::EventHandler(this, &MyForm::B_Out_MCU_TextChanged);
			// 
			// B_Out_CHAB
			// 
			this->B_Out_CHAB->Location = System::Drawing::Point(99, 66);
			this->B_Out_CHAB->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Out_CHAB->Name = L"B_Out_CHAB";
			this->B_Out_CHAB->Size = System::Drawing::Size(420, 20);
			this->B_Out_CHAB->TabIndex = 36;
			this->B_Out_CHAB->TextChanged += gcnew System::EventHandler(this, &MyForm::B_Out_CHAB_TextChanged);
			// 
			// label107
			// 
			this->label107->AutoSize = true;
			this->label107->BackColor = System::Drawing::Color::Transparent;
			this->label107->ForeColor = System::Drawing::Color::White;
			this->label107->Location = System::Drawing::Point(13, 95);
			this->label107->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label107->Name = L"label107";
			this->label107->Size = System::Drawing::Size(31, 13);
			this->label107->TabIndex = 31;
			this->label107->Text = L"MCU";
			// 
			// label106
			// 
			this->label106->AutoSize = true;
			this->label106->BackColor = System::Drawing::Color::Transparent;
			this->label106->ForeColor = System::Drawing::Color::White;
			this->label106->Location = System::Drawing::Point(13, 70);
			this->label106->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label106->Name = L"label106";
			this->label106->Size = System::Drawing::Size(36, 13);
			this->label106->TabIndex = 30;
			this->label106->Text = L"CHAB";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(13, 45);
			this->label11->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(29, 13);
			this->label11->TabIndex = 29;
			this->label11->Text = L"DET";
			// 
			// B_DET_Browse
			// 
			this->B_DET_Browse->ForeColor = System::Drawing::SystemColors::Desktop;
			this->B_DET_Browse->Location = System::Drawing::Point(523, 39);
			this->B_DET_Browse->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DET_Browse->Name = L"B_DET_Browse";
			this->B_DET_Browse->Size = System::Drawing::Size(74, 23);
			this->B_DET_Browse->TabIndex = 28;
			this->B_DET_Browse->Text = L"Browse...";
			this->B_DET_Browse->UseVisualStyleBackColor = true;
			this->B_DET_Browse->Click += gcnew System::EventHandler(this, &MyForm::B_DET_Browse_Click);
			// 
			// B_Out_DET
			// 
			this->B_Out_DET->Location = System::Drawing::Point(99, 41);
			this->B_Out_DET->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Out_DET->Name = L"B_Out_DET";
			this->B_Out_DET->Size = System::Drawing::Size(420, 20);
			this->B_Out_DET->TabIndex = 26;
			this->B_Out_DET->TextChanged += gcnew System::EventHandler(this, &MyForm::B_Out_DET_TextChanged);
			// 
			// L_BUL_status_MCU
			// 
			this->L_BUL_status_MCU->AutoSize = true;
			this->L_BUL_status_MCU->ForeColor = System::Drawing::Color::White;
			this->L_BUL_status_MCU->Location = System::Drawing::Point(527, 178);
			this->L_BUL_status_MCU->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_BUL_status_MCU->Name = L"L_BUL_status_MCU";
			this->L_BUL_status_MCU->Size = System::Drawing::Size(71, 13);
			this->L_BUL_status_MCU->TabIndex = 25;
			this->L_BUL_status_MCU->Text = L"Upload MCU:";
			// 
			// B_BUL_status_OMR
			// 
			this->B_BUL_status_OMR->Location = System::Drawing::Point(80, 173);
			this->B_BUL_status_OMR->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_BUL_status_OMR->Name = L"B_BUL_status_OMR";
			this->B_BUL_status_OMR->ReadOnly = true;
			this->B_BUL_status_OMR->Size = System::Drawing::Size(53, 20);
			this->B_BUL_status_OMR->TabIndex = 17;
			// 
			// B_BUL_status_DET
			// 
			this->B_BUL_status_DET->Location = System::Drawing::Point(210, 173);
			this->B_BUL_status_DET->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_BUL_status_DET->Name = L"B_BUL_status_DET";
			this->B_BUL_status_DET->ReadOnly = true;
			this->B_BUL_status_DET->Size = System::Drawing::Size(53, 20);
			this->B_BUL_status_DET->TabIndex = 16;
			// 
			// B_BUL_status_MCU
			// 
			this->B_BUL_status_MCU->Location = System::Drawing::Point(599, 173);
			this->B_BUL_status_MCU->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_BUL_status_MCU->Name = L"B_BUL_status_MCU";
			this->B_BUL_status_MCU->ReadOnly = true;
			this->B_BUL_status_MCU->Size = System::Drawing::Size(53, 20);
			this->B_BUL_status_MCU->TabIndex = 24;
			// 
			// B_label1
			// 
			this->B_label1->AutoSize = true;
			this->B_label1->BackColor = System::Drawing::Color::Transparent;
			this->B_label1->ForeColor = System::Drawing::Color::White;
			this->B_label1->Location = System::Drawing::Point(13, 20);
			this->B_label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->B_label1->Name = L"B_label1";
			this->B_label1->Size = System::Drawing::Size(32, 13);
			this->B_label1->TabIndex = 3;
			this->B_label1->Text = L"OMR";
			// 
			// L_BUL_status_OMR
			// 
			this->L_BUL_status_OMR->AutoSize = true;
			this->L_BUL_status_OMR->ForeColor = System::Drawing::Color::White;
			this->L_BUL_status_OMR->Location = System::Drawing::Point(4, 178);
			this->L_BUL_status_OMR->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_BUL_status_OMR->Name = L"L_BUL_status_OMR";
			this->L_BUL_status_OMR->Size = System::Drawing::Size(72, 13);
			this->L_BUL_status_OMR->TabIndex = 19;
			this->L_BUL_status_OMR->Text = L"Upload OMR:";
			// 
			// L_BUL_status_CHB
			// 
			this->L_BUL_status_CHB->AutoSize = true;
			this->L_BUL_status_CHB->ForeColor = System::Drawing::Color::White;
			this->L_BUL_status_CHB->Location = System::Drawing::Point(397, 178);
			this->L_BUL_status_CHB->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_BUL_status_CHB->Name = L"L_BUL_status_CHB";
			this->L_BUL_status_CHB->Size = System::Drawing::Size(69, 13);
			this->L_BUL_status_CHB->TabIndex = 23;
			this->L_BUL_status_CHB->Text = L"Upload CHB:";
			// 
			// B_OMR_Browse
			// 
			this->B_OMR_Browse->ForeColor = System::Drawing::SystemColors::Desktop;
			this->B_OMR_Browse->Location = System::Drawing::Point(523, 14);
			this->B_OMR_Browse->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_OMR_Browse->Name = L"B_OMR_Browse";
			this->B_OMR_Browse->Size = System::Drawing::Size(74, 23);
			this->B_OMR_Browse->TabIndex = 1;
			this->B_OMR_Browse->Text = L"Browse...";
			this->B_OMR_Browse->UseVisualStyleBackColor = true;
			this->B_OMR_Browse->Click += gcnew System::EventHandler(this, &MyForm::B_OMR_Browse_Click);
			// 
			// L_BUL_status_DET
			// 
			this->L_BUL_status_DET->AutoSize = true;
			this->L_BUL_status_DET->ForeColor = System::Drawing::Color::White;
			this->L_BUL_status_DET->Location = System::Drawing::Point(140, 178);
			this->L_BUL_status_DET->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_BUL_status_DET->Name = L"L_BUL_status_DET";
			this->L_BUL_status_DET->Size = System::Drawing::Size(69, 13);
			this->L_BUL_status_DET->TabIndex = 18;
			this->L_BUL_status_DET->Text = L"Upload DET:";
			// 
			// B_BUL_status_CHB
			// 
			this->B_BUL_status_CHB->Location = System::Drawing::Point(467, 173);
			this->B_BUL_status_CHB->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_BUL_status_CHB->Name = L"B_BUL_status_CHB";
			this->B_BUL_status_CHB->ReadOnly = true;
			this->B_BUL_status_CHB->Size = System::Drawing::Size(53, 20);
			this->B_BUL_status_CHB->TabIndex = 22;
			// 
			// B_BUL_status_CHA
			// 
			this->B_BUL_status_CHA->Location = System::Drawing::Point(338, 173);
			this->B_BUL_status_CHA->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_BUL_status_CHA->Name = L"B_BUL_status_CHA";
			this->B_BUL_status_CHA->ReadOnly = true;
			this->B_BUL_status_CHA->Size = System::Drawing::Size(53, 20);
			this->B_BUL_status_CHA->TabIndex = 20;
			// 
			// B_ResetAfterUpload
			// 
			this->B_ResetAfterUpload->AutoSize = true;
			this->B_ResetAfterUpload->BackColor = System::Drawing::Color::Transparent;
			this->B_ResetAfterUpload->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->B_ResetAfterUpload->Checked = true;
			this->B_ResetAfterUpload->CheckState = System::Windows::Forms::CheckState::Checked;
			this->B_ResetAfterUpload->ForeColor = System::Drawing::Color::White;
			this->B_ResetAfterUpload->Location = System::Drawing::Point(16, 145);
			this->B_ResetAfterUpload->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_ResetAfterUpload->Name = L"B_ResetAfterUpload";
			this->B_ResetAfterUpload->Size = System::Drawing::Size(118, 17);
			this->B_ResetAfterUpload->TabIndex = 7;
			this->B_ResetAfterUpload->Text = L"Reset after Upload:";
			this->B_ResetAfterUpload->UseVisualStyleBackColor = false;
			this->B_ResetAfterUpload->Visible = false;
			// 
			// B_Out_OMR
			// 
			this->B_Out_OMR->Location = System::Drawing::Point(99, 16);
			this->B_Out_OMR->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Out_OMR->Name = L"B_Out_OMR";
			this->B_Out_OMR->Size = System::Drawing::Size(420, 20);
			this->B_Out_OMR->TabIndex = 0;
			this->B_Out_OMR->TextChanged += gcnew System::EventHandler(this, &MyForm::B_Out_OMR_TextChanged);
			// 
			// L_BUL_status_CHA
			// 
			this->L_BUL_status_CHA->AutoSize = true;
			this->L_BUL_status_CHA->ForeColor = System::Drawing::Color::White;
			this->L_BUL_status_CHA->Location = System::Drawing::Point(269, 178);
			this->L_BUL_status_CHA->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_BUL_status_CHA->Name = L"L_BUL_status_CHA";
			this->L_BUL_status_CHA->Size = System::Drawing::Size(69, 13);
			this->L_BUL_status_CHA->TabIndex = 21;
			this->L_BUL_status_CHA->Text = L"Upload CHA:";
			// 
			// LAB_Experiments
			// 
			this->LAB_Experiments->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->LAB_Experiments->Controls->Add(this->B_CALIBRATOR_DATA);
			this->LAB_Experiments->Controls->Add(this->B_ROTATOR_DATA);
			this->LAB_Experiments->ForeColor = System::Drawing::Color::White;
			this->LAB_Experiments->Location = System::Drawing::Point(4, 22);
			this->LAB_Experiments->Name = L"LAB_Experiments";
			this->LAB_Experiments->Padding = System::Windows::Forms::Padding(3);
			this->LAB_Experiments->Size = System::Drawing::Size(828, 590);
			this->LAB_Experiments->TabIndex = 8;
			this->LAB_Experiments->Text = L"LAB Experiments";
			// 
			// B_CALIBRATOR_DATA
			// 
			this->B_CALIBRATOR_DATA->Controls->Add(this->label280);
			this->B_CALIBRATOR_DATA->Controls->Add(this->B_LAB_SNR);
			this->B_CALIBRATOR_DATA->Controls->Add(this->label281);
			this->B_CALIBRATOR_DATA->Controls->Add(this->B_LAB_CALIBRATOR_START);
			this->B_CALIBRATOR_DATA->Controls->Add(this->label266);
			this->B_CALIBRATOR_DATA->Controls->Add(this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE);
			this->B_CALIBRATOR_DATA->Controls->Add(this->label277);
			this->B_CALIBRATOR_DATA->Controls->Add(this->B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE);
			this->B_CALIBRATOR_DATA->Controls->Add(this->B_LAB_TOTAL_CYCLES);
			this->B_CALIBRATOR_DATA->Controls->Add(this->label276);
			this->B_CALIBRATOR_DATA->Controls->Add(this->label275);
			this->B_CALIBRATOR_DATA->Controls->Add(this->B_LAB_CYCLE);
			this->B_CALIBRATOR_DATA->Controls->Add(this->B_LAB_DOPPLER);
			this->B_CALIBRATOR_DATA->Controls->Add(this->label273);
			this->B_CALIBRATOR_DATA->Controls->Add(this->label267);
			this->B_CALIBRATOR_DATA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_CALIBRATOR_DATA->Location = System::Drawing::Point(9, 29);
			this->B_CALIBRATOR_DATA->Name = L"B_CALIBRATOR_DATA";
			this->B_CALIBRATOR_DATA->Size = System::Drawing::Size(797, 164);
			this->B_CALIBRATOR_DATA->TabIndex = 212;
			this->B_CALIBRATOR_DATA->TabStop = false;
			this->B_CALIBRATOR_DATA->Text = L"Calibrator";
			// 
			// label280
			// 
			this->label280->AutoSize = true;
			this->label280->BackColor = System::Drawing::Color::Transparent;
			this->label280->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label280->ForeColor = System::Drawing::Color::Black;
			this->label280->Location = System::Drawing::Point(463, 92);
			this->label280->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label280->Name = L"label280";
			this->label280->Size = System::Drawing::Size(25, 17);
			this->label280->TabIndex = 222;
			this->label280->Text = L"dB";
			// 
			// B_LAB_SNR
			// 
			this->B_LAB_SNR->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_LAB_SNR->Location = System::Drawing::Point(340, 89);
			this->B_LAB_SNR->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LAB_SNR->Name = L"B_LAB_SNR";
			this->B_LAB_SNR->Size = System::Drawing::Size(117, 23);
			this->B_LAB_SNR->TabIndex = 221;
			this->B_LAB_SNR->Text = L"0";
			// 
			// label281
			// 
			this->label281->AutoSize = true;
			this->label281->BackColor = System::Drawing::Color::Transparent;
			this->label281->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label281->ForeColor = System::Drawing::Color::Black;
			this->label281->Location = System::Drawing::Point(297, 92);
			this->label281->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label281->Name = L"label281";
			this->label281->Size = System::Drawing::Size(41, 17);
			this->label281->TabIndex = 220;
			this->label281->Text = L"SNR:";
			// 
			// B_LAB_CALIBRATOR_START
			// 
			this->B_LAB_CALIBRATOR_START->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(218)),
				static_cast<System::Int32>(static_cast<System::Byte>(218)), static_cast<System::Int32>(static_cast<System::Byte>(212)));
			this->B_LAB_CALIBRATOR_START->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->B_LAB_CALIBRATOR_START->ForeColor = System::Drawing::Color::Black;
			this->B_LAB_CALIBRATOR_START->Location = System::Drawing::Point(534, 100);
			this->B_LAB_CALIBRATOR_START->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LAB_CALIBRATOR_START->Name = L"B_LAB_CALIBRATOR_START";
			this->B_LAB_CALIBRATOR_START->Size = System::Drawing::Size(116, 39);
			this->B_LAB_CALIBRATOR_START->TabIndex = 219;
			this->B_LAB_CALIBRATOR_START->Text = L"START";
			this->B_LAB_CALIBRATOR_START->UseVisualStyleBackColor = false;
			// 
			// label266
			// 
			this->label266->AutoSize = true;
			this->label266->BackColor = System::Drawing::Color::Transparent;
			this->label266->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label266->ForeColor = System::Drawing::Color::Black;
			this->label266->Location = System::Drawing::Point(23, 35);
			this->label266->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label266->Name = L"label266";
			this->label266->Size = System::Drawing::Size(90, 17);
			this->label266->TabIndex = 6;
			this->label266->Text = L"Protocol File:";
			// 
			// B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE
			// 
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE->ForeColor = System::Drawing::SystemColors::Desktop;
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE->Location = System::Drawing::Point(692, 32);
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE->Name = L"B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE";
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE->Size = System::Drawing::Size(74, 23);
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE->TabIndex = 5;
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE->Text = L"Browse...";
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE->UseVisualStyleBackColor = true;
			this->B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE->Click += gcnew System::EventHandler(this, &MyForm::B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE_Click);
			// 
			// label277
			// 
			this->label277->AutoSize = true;
			this->label277->BackColor = System::Drawing::Color::Transparent;
			this->label277->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label277->ForeColor = System::Drawing::Color::Black;
			this->label277->Location = System::Drawing::Point(411, 128);
			this->label277->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label277->Name = L"label277";
			this->label277->Size = System::Drawing::Size(49, 17);
			this->label277->TabIndex = 218;
			this->label277->Text = L"Cycles";
			// 
			// B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE
			// 
			this->B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE->Location = System::Drawing::Point(119, 32);
			this->B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE->Name = L"B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE";
			this->B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE->Size = System::Drawing::Size(567, 23);
			this->B_LAB_CALIBRATOR_DATA_FILE_TO_SAVE->TabIndex = 4;
			// 
			// B_LAB_TOTAL_CYCLES
			// 
			this->B_LAB_TOTAL_CYCLES->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_LAB_TOTAL_CYCLES->Location = System::Drawing::Point(289, 125);
			this->B_LAB_TOTAL_CYCLES->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LAB_TOTAL_CYCLES->Name = L"B_LAB_TOTAL_CYCLES";
			this->B_LAB_TOTAL_CYCLES->Size = System::Drawing::Size(117, 23);
			this->B_LAB_TOTAL_CYCLES->TabIndex = 217;
			this->B_LAB_TOTAL_CYCLES->Text = L"0";
			// 
			// label276
			// 
			this->label276->AutoSize = true;
			this->label276->BackColor = System::Drawing::Color::Transparent;
			this->label276->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label276->ForeColor = System::Drawing::Color::Black;
			this->label276->Location = System::Drawing::Point(237, 128);
			this->label276->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label276->Name = L"label276";
			this->label276->Size = System::Drawing::Size(47, 17);
			this->label276->TabIndex = 216;
			this->label276->Text = L"Out of";
			// 
			// label275
			// 
			this->label275->AutoSize = true;
			this->label275->BackColor = System::Drawing::Color::Transparent;
			this->label275->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label275->ForeColor = System::Drawing::Color::Black;
			this->label275->Location = System::Drawing::Point(211, 92);
			this->label275->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label275->Name = L"label275";
			this->label275->Size = System::Drawing::Size(25, 17);
			this->label275->TabIndex = 215;
			this->label275->Text = L"Hz";
			// 
			// B_LAB_CYCLE
			// 
			this->B_LAB_CYCLE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_LAB_CYCLE->Location = System::Drawing::Point(91, 125);
			this->B_LAB_CYCLE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LAB_CYCLE->Name = L"B_LAB_CYCLE";
			this->B_LAB_CYCLE->Size = System::Drawing::Size(117, 23);
			this->B_LAB_CYCLE->TabIndex = 214;
			this->B_LAB_CYCLE->Text = L"0";
			// 
			// B_LAB_DOPPLER
			// 
			this->B_LAB_DOPPLER->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_LAB_DOPPLER->Location = System::Drawing::Point(93, 89);
			this->B_LAB_DOPPLER->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LAB_DOPPLER->Name = L"B_LAB_DOPPLER";
			this->B_LAB_DOPPLER->Size = System::Drawing::Size(117, 23);
			this->B_LAB_DOPPLER->TabIndex = 213;
			this->B_LAB_DOPPLER->Text = L"0";
			// 
			// label273
			// 
			this->label273->AutoSize = true;
			this->label273->BackColor = System::Drawing::Color::Transparent;
			this->label273->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label273->ForeColor = System::Drawing::Color::Black;
			this->label273->Location = System::Drawing::Point(41, 128);
			this->label273->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label273->Name = L"label273";
			this->label273->Size = System::Drawing::Size(46, 17);
			this->label273->TabIndex = 212;
			this->label273->Text = L"Cycle:";
			// 
			// label267
			// 
			this->label267->AutoSize = true;
			this->label267->BackColor = System::Drawing::Color::Transparent;
			this->label267->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label267->ForeColor = System::Drawing::Color::Black;
			this->label267->Location = System::Drawing::Point(25, 92);
			this->label267->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label267->Name = L"label267";
			this->label267->Size = System::Drawing::Size(62, 17);
			this->label267->TabIndex = 211;
			this->label267->Text = L"Doppler:";
			// 
			// B_ROTATOR_DATA
			// 
			this->B_ROTATOR_DATA->Controls->Add(this->label294);
			this->B_ROTATOR_DATA->Controls->Add(this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE);
			this->B_ROTATOR_DATA->Controls->Add(this->B_LAB_ROTATOR_DATA_FILE_TO_SAVE);
			this->B_ROTATOR_DATA->Controls->Add(this->B_ELEVATION_RESOLUTION);
			this->B_ROTATOR_DATA->Controls->Add(this->label293);
			this->B_ROTATOR_DATA->Controls->Add(this->B_AZIMUTH_RESOLUTION);
			this->B_ROTATOR_DATA->Controls->Add(this->label292);
			this->B_ROTATOR_DATA->Controls->Add(this->B_CURRENT_ELEVATION);
			this->B_ROTATOR_DATA->Controls->Add(this->label291);
			this->B_ROTATOR_DATA->Controls->Add(this->B_CURRENT_AZIMUTH);
			this->B_ROTATOR_DATA->Controls->Add(this->B_LAB_ELEVATION);
			this->B_ROTATOR_DATA->Controls->Add(this->label290);
			this->B_ROTATOR_DATA->Controls->Add(this->B_ROTATOR_COM_PORT);
			this->B_ROTATOR_DATA->Controls->Add(this->B_COM);
			this->B_ROTATOR_DATA->Controls->Add(this->B_LAB_AZIMUTH);
			this->B_ROTATOR_DATA->Controls->Add(this->lbl_azimuth);
			this->B_ROTATOR_DATA->Controls->Add(this->B_AZIMUTH);
			this->B_ROTATOR_DATA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_ROTATOR_DATA->ForeColor = System::Drawing::Color::Black;
			this->B_ROTATOR_DATA->Location = System::Drawing::Point(9, 203);
			this->B_ROTATOR_DATA->Name = L"B_ROTATOR_DATA";
			this->B_ROTATOR_DATA->Size = System::Drawing::Size(797, 185);
			this->B_ROTATOR_DATA->TabIndex = 211;
			this->B_ROTATOR_DATA->TabStop = false;
			this->B_ROTATOR_DATA->Text = L"Rotator";
			// 
			// label294
			// 
			this->label294->AutoSize = true;
			this->label294->BackColor = System::Drawing::Color::Transparent;
			this->label294->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label294->ForeColor = System::Drawing::Color::Black;
			this->label294->Location = System::Drawing::Point(23, 31);
			this->label294->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label294->Name = L"label294";
			this->label294->Size = System::Drawing::Size(90, 17);
			this->label294->TabIndex = 25;
			this->label294->Text = L"Protocol File:";
			// 
			// B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE
			// 
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE->ForeColor = System::Drawing::SystemColors::Desktop;
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE->Location = System::Drawing::Point(692, 28);
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE->Name = L"B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE";
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE->Size = System::Drawing::Size(74, 23);
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE->TabIndex = 24;
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE->Text = L"Browse...";
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE->UseVisualStyleBackColor = true;
			this->B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE->Click += gcnew System::EventHandler(this, &MyForm::B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE_Click);
			// 
			// B_LAB_ROTATOR_DATA_FILE_TO_SAVE
			// 
			this->B_LAB_ROTATOR_DATA_FILE_TO_SAVE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->B_LAB_ROTATOR_DATA_FILE_TO_SAVE->Location = System::Drawing::Point(119, 28);
			this->B_LAB_ROTATOR_DATA_FILE_TO_SAVE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LAB_ROTATOR_DATA_FILE_TO_SAVE->Name = L"B_LAB_ROTATOR_DATA_FILE_TO_SAVE";
			this->B_LAB_ROTATOR_DATA_FILE_TO_SAVE->Size = System::Drawing::Size(567, 23);
			this->B_LAB_ROTATOR_DATA_FILE_TO_SAVE->TabIndex = 23;
			// 
			// B_ELEVATION_RESOLUTION
			// 
			this->B_ELEVATION_RESOLUTION->Location = System::Drawing::Point(622, 107);
			this->B_ELEVATION_RESOLUTION->Name = L"B_ELEVATION_RESOLUTION";
			this->B_ELEVATION_RESOLUTION->Size = System::Drawing::Size(100, 23);
			this->B_ELEVATION_RESOLUTION->TabIndex = 22;
			this->B_ELEVATION_RESOLUTION->Text = L"0";
			// 
			// label293
			// 
			this->label293->AutoSize = true;
			this->label293->BackColor = System::Drawing::Color::Transparent;
			this->label293->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label293->ForeColor = System::Drawing::Color::Black;
			this->label293->Location = System::Drawing::Point(481, 110);
			this->label293->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label293->Name = L"label293";
			this->label293->Size = System::Drawing::Size(136, 17);
			this->label293->TabIndex = 21;
			this->label293->Text = L"Elevation resolution:";
			// 
			// B_AZIMUTH_RESOLUTION
			// 
			this->B_AZIMUTH_RESOLUTION->Location = System::Drawing::Point(622, 80);
			this->B_AZIMUTH_RESOLUTION->Name = L"B_AZIMUTH_RESOLUTION";
			this->B_AZIMUTH_RESOLUTION->Size = System::Drawing::Size(100, 23);
			this->B_AZIMUTH_RESOLUTION->TabIndex = 20;
			this->B_AZIMUTH_RESOLUTION->Text = L"0";
			// 
			// label292
			// 
			this->label292->AutoSize = true;
			this->label292->BackColor = System::Drawing::Color::Transparent;
			this->label292->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label292->ForeColor = System::Drawing::Color::Black;
			this->label292->Location = System::Drawing::Point(489, 83);
			this->label292->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label292->Name = L"label292";
			this->label292->Size = System::Drawing::Size(128, 17);
			this->label292->TabIndex = 19;
			this->label292->Text = L"Azimuth resolution:";
			// 
			// B_CURRENT_ELEVATION
			// 
			this->B_CURRENT_ELEVATION->Location = System::Drawing::Point(343, 107);
			this->B_CURRENT_ELEVATION->Name = L"B_CURRENT_ELEVATION";
			this->B_CURRENT_ELEVATION->Size = System::Drawing::Size(100, 23);
			this->B_CURRENT_ELEVATION->TabIndex = 18;
			this->B_CURRENT_ELEVATION->Text = L"0";
			// 
			// label291
			// 
			this->label291->AutoSize = true;
			this->label291->BackColor = System::Drawing::Color::Transparent;
			this->label291->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label291->ForeColor = System::Drawing::Color::Black;
			this->label291->Location = System::Drawing::Point(217, 110);
			this->label291->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label291->Name = L"label291";
			this->label291->Size = System::Drawing::Size(121, 17);
			this->label291->TabIndex = 17;
			this->label291->Text = L"Current Elevation:";
			// 
			// B_CURRENT_AZIMUTH
			// 
			this->B_CURRENT_AZIMUTH->Location = System::Drawing::Point(343, 80);
			this->B_CURRENT_AZIMUTH->Name = L"B_CURRENT_AZIMUTH";
			this->B_CURRENT_AZIMUTH->Size = System::Drawing::Size(100, 23);
			this->B_CURRENT_AZIMUTH->TabIndex = 16;
			this->B_CURRENT_AZIMUTH->Text = L"0";
			// 
			// B_LAB_ELEVATION
			// 
			this->B_LAB_ELEVATION->DecimalPlaces = 2;
			this->B_LAB_ELEVATION->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 131072 });
			this->B_LAB_ELEVATION->Location = System::Drawing::Point(93, 107);
			this->B_LAB_ELEVATION->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, 0 });
			this->B_LAB_ELEVATION->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, System::Int32::MinValue });
			this->B_LAB_ELEVATION->Name = L"B_LAB_ELEVATION";
			this->B_LAB_ELEVATION->Size = System::Drawing::Size(79, 23);
			this->B_LAB_ELEVATION->TabIndex = 20;
			this->B_LAB_ELEVATION->Click += gcnew System::EventHandler(this, &MyForm::B_LAB_ELEVATION_MIN_ValueChanged);
			// 
			// label290
			// 
			this->label290->AutoSize = true;
			this->label290->BackColor = System::Drawing::Color::Transparent;
			this->label290->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label290->ForeColor = System::Drawing::Color::Black;
			this->label290->Location = System::Drawing::Point(17, 110);
			this->label290->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label290->Name = L"label290";
			this->label290->Size = System::Drawing::Size(70, 17);
			this->label290->TabIndex = 14;
			this->label290->Text = L"Elevation:";
			// 
			// B_ROTATOR_COM_PORT
			// 
			this->B_ROTATOR_COM_PORT->FormattingEnabled = true;
			this->B_ROTATOR_COM_PORT->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"COM1", L"COM2", L"COM3", L"COM4", L"COM5",
					L"COM6", L"COM7", L"COM8", L"COM9", L"COM10"
			});
			this->B_ROTATOR_COM_PORT->Location = System::Drawing::Point(93, 147);
			this->B_ROTATOR_COM_PORT->Name = L"B_ROTATOR_COM_PORT";
			this->B_ROTATOR_COM_PORT->Size = System::Drawing::Size(79, 24);
			this->B_ROTATOR_COM_PORT->TabIndex = 13;
			this->B_ROTATOR_COM_PORT->Text = L"COM1";
			this->B_ROTATOR_COM_PORT->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::B_ROTATOR_COM_PORT_SelectedIndexChanged);
			// 
			// B_COM
			// 
			this->B_COM->AutoSize = true;
			this->B_COM->BackColor = System::Drawing::Color::Transparent;
			this->B_COM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_COM->ForeColor = System::Drawing::Color::Black;
			this->B_COM->Location = System::Drawing::Point(44, 151);
			this->B_COM->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->B_COM->Name = L"B_COM";
			this->B_COM->Size = System::Drawing::Size(43, 17);
			this->B_COM->TabIndex = 12;
			this->B_COM->Text = L"COM:";
			// 
			// B_LAB_AZIMUTH
			// 
			this->B_LAB_AZIMUTH->DecimalPlaces = 2;
			this->B_LAB_AZIMUTH->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 131072 });
			this->B_LAB_AZIMUTH->Location = System::Drawing::Point(93, 80);
			this->B_LAB_AZIMUTH->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, 0 });
			this->B_LAB_AZIMUTH->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, System::Int32::MinValue });
			this->B_LAB_AZIMUTH->Name = L"B_LAB_AZIMUTH";
			this->B_LAB_AZIMUTH->Size = System::Drawing::Size(79, 23);
			this->B_LAB_AZIMUTH->TabIndex = 19;
			this->B_LAB_AZIMUTH->Click += gcnew System::EventHandler(this, &MyForm::B_LAB_AZIMUTH_MIN_ValueChanged);
			// 
			// lbl_azimuth
			// 
			this->lbl_azimuth->AutoSize = true;
			this->lbl_azimuth->BackColor = System::Drawing::Color::Transparent;
			this->lbl_azimuth->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl_azimuth->ForeColor = System::Drawing::Color::Black;
			this->lbl_azimuth->Location = System::Drawing::Point(225, 83);
			this->lbl_azimuth->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lbl_azimuth->Name = L"lbl_azimuth";
			this->lbl_azimuth->Size = System::Drawing::Size(113, 17);
			this->lbl_azimuth->TabIndex = 9;
			this->lbl_azimuth->Text = L"Current Azimuth:";
			// 
			// B_AZIMUTH
			// 
			this->B_AZIMUTH->AutoSize = true;
			this->B_AZIMUTH->BackColor = System::Drawing::Color::Transparent;
			this->B_AZIMUTH->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_AZIMUTH->ForeColor = System::Drawing::Color::Black;
			this->B_AZIMUTH->Location = System::Drawing::Point(25, 83);
			this->B_AZIMUTH->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->B_AZIMUTH->Name = L"B_AZIMUTH";
			this->B_AZIMUTH->Size = System::Drawing::Size(62, 17);
			this->B_AZIMUTH->TabIndex = 8;
			this->B_AZIMUTH->Text = L"Azimuth:";
			// 
			// label251
			// 
			this->label251->AutoSize = true;
			this->label251->ForeColor = System::Drawing::Color::Black;
			this->label251->Location = System::Drawing::Point(796, 635);
			this->label251->Name = L"label251";
			this->label251->Size = System::Drawing::Size(36, 13);
			this->label251->TabIndex = 210;
			this->label251->Text = L"30 km";
			// 
			// B_SCREEN_WIDTH_OF_VIEWER
			// 
			this->B_SCREEN_WIDTH_OF_VIEWER->BackColor = System::Drawing::Color::DarkGray;
			this->B_SCREEN_WIDTH_OF_VIEWER->Location = System::Drawing::Point(681, 623);
			this->B_SCREEN_WIDTH_OF_VIEWER->Maximum = 30;
			this->B_SCREEN_WIDTH_OF_VIEWER->Minimum = 1;
			this->B_SCREEN_WIDTH_OF_VIEWER->Name = L"B_SCREEN_WIDTH_OF_VIEWER";
			this->B_SCREEN_WIDTH_OF_VIEWER->Size = System::Drawing::Size(118, 45);
			this->B_SCREEN_WIDTH_OF_VIEWER->TabIndex = 207;
			this->B_SCREEN_WIDTH_OF_VIEWER->Value = 15;
			this->B_SCREEN_WIDTH_OF_VIEWER->Scroll += gcnew System::EventHandler(this, &MyForm::B_SCREEN_WIDTH_OF_VIEWER_Scroll);
			// 
			// label263
			// 
			this->label263->AutoSize = true;
			this->label263->ForeColor = System::Drawing::Color::Black;
			this->label263->Location = System::Drawing::Point(645, 634);
			this->label263->Name = L"label263";
			this->label263->Size = System::Drawing::Size(30, 13);
			this->label263->TabIndex = 209;
			this->label263->Text = L"1 km";
			// 
			// B_RF_TEMP
			// 
			this->B_RF_TEMP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_RF_TEMP->Location = System::Drawing::Point(77, 506);
			this->B_RF_TEMP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RF_TEMP->Name = L"B_RF_TEMP";
			this->B_RF_TEMP->ReadOnly = true;
			this->B_RF_TEMP->Size = System::Drawing::Size(50, 20);
			this->B_RF_TEMP->TabIndex = 71;
			this->B_RF_TEMP->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_HMC830_PLL
			// 
			this->B_HMC830_PLL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_HMC830_PLL->Location = System::Drawing::Point(77, 176);
			this->B_HMC830_PLL->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_HMC830_PLL->Name = L"B_HMC830_PLL";
			this->B_HMC830_PLL->ReadOnly = true;
			this->B_HMC830_PLL->Size = System::Drawing::Size(50, 20);
			this->B_HMC830_PLL->TabIndex = 74;
			// 
			// L_RF_BOARD_TEMP
			// 
			this->L_RF_BOARD_TEMP->AutoSize = true;
			this->L_RF_BOARD_TEMP->ForeColor = System::Drawing::Color::White;
			this->L_RF_BOARD_TEMP->Location = System::Drawing::Point(8, 507);
			this->L_RF_BOARD_TEMP->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_RF_BOARD_TEMP->Name = L"L_RF_BOARD_TEMP";
			this->L_RF_BOARD_TEMP->Size = System::Drawing::Size(51, 13);
			this->L_RF_BOARD_TEMP->TabIndex = 72;
			this->L_RF_BOARD_TEMP->Text = L"Temp RF";
			// 
			// L_HMC830_PLL
			// 
			this->L_HMC830_PLL->AutoSize = true;
			this->L_HMC830_PLL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->L_HMC830_PLL->ForeColor = System::Drawing::Color::White;
			this->L_HMC830_PLL->Location = System::Drawing::Point(8, 179);
			this->L_HMC830_PLL->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_HMC830_PLL->Name = L"L_HMC830_PLL";
			this->L_HMC830_PLL->Size = System::Drawing::Size(64, 12);
			this->L_HMC830_PLL->TabIndex = 73;
			this->L_HMC830_PLL->Text = L"HMC830_PLL";
			// 
			// B_RF_MCU_TEMP
			// 
			this->B_RF_MCU_TEMP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_RF_MCU_TEMP->Location = System::Drawing::Point(77, 484);
			this->B_RF_MCU_TEMP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RF_MCU_TEMP->Name = L"B_RF_MCU_TEMP";
			this->B_RF_MCU_TEMP->ReadOnly = true;
			this->B_RF_MCU_TEMP->Size = System::Drawing::Size(50, 20);
			this->B_RF_MCU_TEMP->TabIndex = 69;
			this->B_RF_MCU_TEMP->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// L_RF_MCU_TEMP
			// 
			this->L_RF_MCU_TEMP->AutoSize = true;
			this->L_RF_MCU_TEMP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->L_RF_MCU_TEMP->ForeColor = System::Drawing::Color::White;
			this->L_RF_MCU_TEMP->Location = System::Drawing::Point(8, 486);
			this->L_RF_MCU_TEMP->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_RF_MCU_TEMP->Name = L"L_RF_MCU_TEMP";
			this->L_RF_MCU_TEMP->Size = System::Drawing::Size(68, 12);
			this->L_RF_MCU_TEMP->TabIndex = 70;
			this->L_RF_MCU_TEMP->Text = L"Temp RF MCU";
			// 
			// A_SCOPE_VIEW
			// 
			this->A_SCOPE_VIEW->BackColor = System::Drawing::Color::Black;
			this->A_SCOPE_VIEW->Controls->Add(this->label158);
			this->A_SCOPE_VIEW->Controls->Add(this->B_A_SCOPE_DOPPLER);
			this->A_SCOPE_VIEW->Controls->Add(this->panel7);
			this->A_SCOPE_VIEW->Controls->Add(this->B_SATURATION_V_LEFT);
			this->A_SCOPE_VIEW->Controls->Add(this->B_SATURATION_V_RIGHT);
			this->A_SCOPE_VIEW->Controls->Add(this->B_SATURATION_H_RIGHT);
			this->A_SCOPE_VIEW->Controls->Add(this->B_SATURATION_H_LEFT);
			this->A_SCOPE_VIEW->Controls->Add(this->B_SCOPE_V_RIGHT);
			this->A_SCOPE_VIEW->Controls->Add(this->B_SCOPE_V_LEFT);
			this->A_SCOPE_VIEW->Controls->Add(this->B_SCOPE_H_RIGHT);
			this->A_SCOPE_VIEW->Controls->Add(this->B_SCOPE_H_LEFT);
			this->A_SCOPE_VIEW->ForeColor = System::Drawing::Color::White;
			this->A_SCOPE_VIEW->Location = System::Drawing::Point(4, 22);
			this->A_SCOPE_VIEW->Name = L"A_SCOPE_VIEW";
			this->A_SCOPE_VIEW->Padding = System::Windows::Forms::Padding(3);
			this->A_SCOPE_VIEW->Size = System::Drawing::Size(829, 588);
			this->A_SCOPE_VIEW->TabIndex = 0;
			this->A_SCOPE_VIEW->Text = L"A-Scope";
			// 
			// label158
			// 
			this->label158->AutoSize = true;
			this->label158->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label158->ForeColor = System::Drawing::Color::White;
			this->label158->Location = System::Drawing::Point(342, 11);
			this->label158->Name = L"label158";
			this->label158->Size = System::Drawing::Size(44, 13);
			this->label158->TabIndex = 205;
			this->label158->Text = L"Doppler";
			// 
			// B_A_SCOPE_DOPPLER
			// 
			this->B_A_SCOPE_DOPPLER->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_A_SCOPE_DOPPLER->Location = System::Drawing::Point(392, 8);
			this->B_A_SCOPE_DOPPLER->Name = L"B_A_SCOPE_DOPPLER";
			this->B_A_SCOPE_DOPPLER->ReadOnly = true;
			this->B_A_SCOPE_DOPPLER->Size = System::Drawing::Size(69, 20);
			this->B_A_SCOPE_DOPPLER->TabIndex = 204;
			this->B_A_SCOPE_DOPPLER->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// panel7
			// 
			this->panel7->Controls->Add(this->RB_BARKER_PULSE);
			this->panel7->Controls->Add(this->RB_SINGLE_PULSE);
			this->panel7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel7->Location = System::Drawing::Point(6, 247);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(95, 55);
			this->panel7->TabIndex = 203;
			// 
			// RB_BARKER_PULSE
			// 
			this->RB_BARKER_PULSE->AutoSize = true;
			this->RB_BARKER_PULSE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RB_BARKER_PULSE->ForeColor = System::Drawing::Color::White;
			this->RB_BARKER_PULSE->Location = System::Drawing::Point(3, 28);
			this->RB_BARKER_PULSE->Name = L"RB_BARKER_PULSE";
			this->RB_BARKER_PULSE->Size = System::Drawing::Size(74, 24);
			this->RB_BARKER_PULSE->TabIndex = 61;
			this->RB_BARKER_PULSE->TabStop = true;
			this->RB_BARKER_PULSE->Text = L"Barker";
			this->RB_BARKER_PULSE->UseVisualStyleBackColor = true;
			// 
			// RB_SINGLE_PULSE
			// 
			this->RB_SINGLE_PULSE->AutoSize = true;
			this->RB_SINGLE_PULSE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RB_SINGLE_PULSE->ForeColor = System::Drawing::Color::White;
			this->RB_SINGLE_PULSE->Location = System::Drawing::Point(3, 1);
			this->RB_SINGLE_PULSE->Name = L"RB_SINGLE_PULSE";
			this->RB_SINGLE_PULSE->Size = System::Drawing::Size(71, 24);
			this->RB_SINGLE_PULSE->TabIndex = 60;
			this->RB_SINGLE_PULSE->TabStop = true;
			this->RB_SINGLE_PULSE->Text = L"Single";
			this->RB_SINGLE_PULSE->UseVisualStyleBackColor = true;
			// 
			// B_SATURATION_V_LEFT
			// 
			this->B_SATURATION_V_LEFT->BackColor = System::Drawing::Color::Transparent;
			this->B_SATURATION_V_LEFT->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_SATURATION_V_LEFT->Location = System::Drawing::Point(149, 278);
			this->B_SATURATION_V_LEFT->Name = L"B_SATURATION_V_LEFT";
			this->B_SATURATION_V_LEFT->Size = System::Drawing::Size(21, 20);
			this->B_SATURATION_V_LEFT->TabIndex = 201;
			this->B_SATURATION_V_LEFT->TabStop = false;
			// 
			// B_SATURATION_V_RIGHT
			// 
			this->B_SATURATION_V_RIGHT->BackColor = System::Drawing::Color::Transparent;
			this->B_SATURATION_V_RIGHT->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_SATURATION_V_RIGHT->Location = System::Drawing::Point(549, 278);
			this->B_SATURATION_V_RIGHT->Name = L"B_SATURATION_V_RIGHT";
			this->B_SATURATION_V_RIGHT->Size = System::Drawing::Size(21, 20);
			this->B_SATURATION_V_RIGHT->TabIndex = 200;
			this->B_SATURATION_V_RIGHT->TabStop = false;
			// 
			// B_SATURATION_H_RIGHT
			// 
			this->B_SATURATION_H_RIGHT->BackColor = System::Drawing::Color::Transparent;
			this->B_SATURATION_H_RIGHT->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_SATURATION_H_RIGHT->Location = System::Drawing::Point(549, 13);
			this->B_SATURATION_H_RIGHT->Name = L"B_SATURATION_H_RIGHT";
			this->B_SATURATION_H_RIGHT->Size = System::Drawing::Size(21, 20);
			this->B_SATURATION_H_RIGHT->TabIndex = 199;
			this->B_SATURATION_H_RIGHT->TabStop = false;
			// 
			// B_SATURATION_H_LEFT
			// 
			this->B_SATURATION_H_LEFT->BackColor = System::Drawing::Color::Transparent;
			this->B_SATURATION_H_LEFT->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B_SATURATION_H_LEFT->Location = System::Drawing::Point(149, 13);
			this->B_SATURATION_H_LEFT->Name = L"B_SATURATION_H_LEFT";
			this->B_SATURATION_H_LEFT->Size = System::Drawing::Size(21, 20);
			this->B_SATURATION_H_LEFT->TabIndex = 198;
			this->B_SATURATION_H_LEFT->TabStop = false;
			// 
			// B_SCOPE_V_RIGHT
			// 
			this->B_SCOPE_V_RIGHT->BackColor = System::Drawing::Color::Black;
			chartArea17->AxisX->Interval = 100;
			chartArea17->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea17->AxisX->LineColor = System::Drawing::Color::White;
			chartArea17->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea17->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea17->AxisX->Maximum = 1000;
			chartArea17->AxisX->Minimum = 0;
			chartArea17->AxisX->Title = L"Range [m]";
			chartArea17->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea17->AxisY->Interval = 10;
			chartArea17->AxisY->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea17->AxisY->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea17->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea17->AxisY->LineColor = System::Drawing::Color::White;
			chartArea17->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea17->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea17->AxisY->Maximum = 0;
			chartArea17->AxisY->Minimum = -80;
			chartArea17->AxisY->Title = L"Amplitude [dB]";
			chartArea17->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea17->BackColor = System::Drawing::Color::Black;
			chartArea17->Name = L"ChartArea1";
			this->B_SCOPE_V_RIGHT->ChartAreas->Add(chartArea17);
			legend11->Enabled = false;
			legend11->Name = L"Legend1";
			this->B_SCOPE_V_RIGHT->Legends->Add(legend11);
			this->B_SCOPE_V_RIGHT->Location = System::Drawing::Point(399, 270);
			this->B_SCOPE_V_RIGHT->Name = L"B_SCOPE_V_RIGHT";
			series39->BorderWidth = 2;
			series39->ChartArea = L"ChartArea1";
			series39->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series39->Color = System::Drawing::Color::Lime;
			series39->Legend = L"Legend1";
			series39->Name = L"Single1";
			series40->BorderWidth = 2;
			series40->ChartArea = L"ChartArea1";
			series40->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series40->Color = System::Drawing::Color::Yellow;
			series40->Legend = L"Legend1";
			series40->Name = L"Average1";
			series41->BorderWidth = 2;
			series41->ChartArea = L"ChartArea1";
			series41->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series41->Color = System::Drawing::Color::Red;
			series41->Legend = L"Legend1";
			series41->Name = L"Single2";
			series42->BorderWidth = 2;
			series42->ChartArea = L"ChartArea1";
			series42->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series42->Color = System::Drawing::Color::Aqua;
			series42->Legend = L"Legend1";
			series42->Name = L"Average2";
			this->B_SCOPE_V_RIGHT->Series->Add(series39);
			this->B_SCOPE_V_RIGHT->Series->Add(series40);
			this->B_SCOPE_V_RIGHT->Series->Add(series41);
			this->B_SCOPE_V_RIGHT->Series->Add(series42);
			this->B_SCOPE_V_RIGHT->Size = System::Drawing::Size(418, 262);
			this->B_SCOPE_V_RIGHT->TabIndex = 151;
			this->B_SCOPE_V_RIGHT->Text = L"H - left";
			title5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			title5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			title5->Name = L"Title1";
			title5->Text = L"V - right";
			this->B_SCOPE_V_RIGHT->Titles->Add(title5);
			// 
			// B_SCOPE_V_LEFT
			// 
			this->B_SCOPE_V_LEFT->BackColor = System::Drawing::Color::Black;
			chartArea18->AxisX->Interval = 100;
			chartArea18->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea18->AxisX->LineColor = System::Drawing::Color::White;
			chartArea18->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea18->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea18->AxisX->Maximum = 1000;
			chartArea18->AxisX->Minimum = 0;
			chartArea18->AxisX->Title = L"Range [m]";
			chartArea18->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea18->AxisY->Interval = 10;
			chartArea18->AxisY->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea18->AxisY->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea18->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea18->AxisY->LineColor = System::Drawing::Color::White;
			chartArea18->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea18->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea18->AxisY->Maximum = 0;
			chartArea18->AxisY->Minimum = -80;
			chartArea18->AxisY->Title = L"Amplitude [dB]";
			chartArea18->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea18->BackColor = System::Drawing::Color::Black;
			chartArea18->Name = L"ChartArea1";
			this->B_SCOPE_V_LEFT->ChartAreas->Add(chartArea18);
			legend12->Enabled = false;
			legend12->Name = L"Legend1";
			this->B_SCOPE_V_LEFT->Legends->Add(legend12);
			this->B_SCOPE_V_LEFT->Location = System::Drawing::Point(-5, 270);
			this->B_SCOPE_V_LEFT->Name = L"B_SCOPE_V_LEFT";
			series43->BorderWidth = 2;
			series43->ChartArea = L"ChartArea1";
			series43->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series43->Color = System::Drawing::Color::Lime;
			series43->Legend = L"Legend1";
			series43->Name = L"Single1";
			series44->BorderWidth = 2;
			series44->ChartArea = L"ChartArea1";
			series44->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series44->Color = System::Drawing::Color::Yellow;
			series44->Legend = L"Legend1";
			series44->Name = L"Average1";
			series45->BorderWidth = 2;
			series45->ChartArea = L"ChartArea1";
			series45->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series45->Color = System::Drawing::Color::Red;
			series45->Legend = L"Legend1";
			series45->Name = L"Single2";
			series46->BorderWidth = 2;
			series46->ChartArea = L"ChartArea1";
			series46->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series46->Color = System::Drawing::Color::Aqua;
			series46->Legend = L"Legend1";
			series46->Name = L"Average2";
			this->B_SCOPE_V_LEFT->Series->Add(series43);
			this->B_SCOPE_V_LEFT->Series->Add(series44);
			this->B_SCOPE_V_LEFT->Series->Add(series45);
			this->B_SCOPE_V_LEFT->Series->Add(series46);
			this->B_SCOPE_V_LEFT->Size = System::Drawing::Size(418, 262);
			this->B_SCOPE_V_LEFT->TabIndex = 150;
			this->B_SCOPE_V_LEFT->Text = L"H - left";
			title6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			title6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			title6->Name = L"Title1";
			title6->Text = L"V - left";
			this->B_SCOPE_V_LEFT->Titles->Add(title6);
			// 
			// B_SCOPE_H_RIGHT
			// 
			this->B_SCOPE_H_RIGHT->BackColor = System::Drawing::Color::Black;
			chartArea19->AxisX->Interval = 100;
			chartArea19->AxisX->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea19->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea19->AxisX->LineColor = System::Drawing::Color::White;
			chartArea19->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea19->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea19->AxisX->Maximum = 1000;
			chartArea19->AxisX->Minimum = 0;
			chartArea19->AxisX->Title = L"Range [m]";
			chartArea19->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea19->AxisY->Interval = 10;
			chartArea19->AxisY->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea19->AxisY->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea19->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea19->AxisY->LineColor = System::Drawing::Color::White;
			chartArea19->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea19->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea19->AxisY->Maximum = 0;
			chartArea19->AxisY->Minimum = -80;
			chartArea19->AxisY->Title = L"Amplitude [dB]";
			chartArea19->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea19->BackColor = System::Drawing::Color::Black;
			chartArea19->Name = L"ChartArea1";
			this->B_SCOPE_H_RIGHT->ChartAreas->Add(chartArea19);
			legend13->Enabled = false;
			legend13->Name = L"Legend1";
			this->B_SCOPE_H_RIGHT->Legends->Add(legend13);
			this->B_SCOPE_H_RIGHT->Location = System::Drawing::Point(399, 5);
			this->B_SCOPE_H_RIGHT->Name = L"B_SCOPE_H_RIGHT";
			series47->BorderWidth = 2;
			series47->ChartArea = L"ChartArea1";
			series47->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series47->Color = System::Drawing::Color::Lime;
			series47->Legend = L"Legend1";
			series47->Name = L"Single1";
			series48->BorderWidth = 2;
			series48->ChartArea = L"ChartArea1";
			series48->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series48->Color = System::Drawing::Color::Yellow;
			series48->Legend = L"Legend1";
			series48->Name = L"Average1";
			series49->BorderWidth = 2;
			series49->ChartArea = L"ChartArea1";
			series49->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series49->Color = System::Drawing::Color::Red;
			series49->Legend = L"Legend1";
			series49->Name = L"Single2";
			series50->BorderWidth = 2;
			series50->ChartArea = L"ChartArea1";
			series50->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series50->Color = System::Drawing::Color::Aqua;
			series50->Legend = L"Legend1";
			series50->Name = L"Average2";
			this->B_SCOPE_H_RIGHT->Series->Add(series47);
			this->B_SCOPE_H_RIGHT->Series->Add(series48);
			this->B_SCOPE_H_RIGHT->Series->Add(series49);
			this->B_SCOPE_H_RIGHT->Series->Add(series50);
			this->B_SCOPE_H_RIGHT->Size = System::Drawing::Size(418, 263);
			this->B_SCOPE_H_RIGHT->TabIndex = 149;
			this->B_SCOPE_H_RIGHT->Text = L"H - left";
			title7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			title7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			title7->Name = L"Title1";
			title7->Text = L"H - right";
			this->B_SCOPE_H_RIGHT->Titles->Add(title7);
			// 
			// B_SCOPE_H_LEFT
			// 
			this->B_SCOPE_H_LEFT->BackColor = System::Drawing::Color::Black;
			chartArea20->AxisX->Interval = 100;
			chartArea20->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea20->AxisX->LineColor = System::Drawing::Color::White;
			chartArea20->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea20->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea20->AxisX->Maximum = 1000;
			chartArea20->AxisX->Minimum = 0;
			chartArea20->AxisX->ScaleBreakStyle->LineColor = System::Drawing::Color::White;
			chartArea20->AxisX->Title = L"Range [m]";
			chartArea20->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea20->AxisY->Interval = 10;
			chartArea20->AxisY->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea20->AxisY->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea20->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea20->AxisY->LineColor = System::Drawing::Color::White;
			chartArea20->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea20->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea20->AxisY->Maximum = 0;
			chartArea20->AxisY->MaximumAutoSize = 80;
			chartArea20->AxisY->Minimum = -80;
			chartArea20->AxisY->ScaleBreakStyle->LineColor = System::Drawing::Color::White;
			chartArea20->AxisY->Title = L"Amplitude [dB]";
			chartArea20->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea20->BackColor = System::Drawing::Color::Black;
			chartArea20->BackGradientStyle = System::Windows::Forms::DataVisualization::Charting::GradientStyle::LeftRight;
			chartArea20->BackHatchStyle = System::Windows::Forms::DataVisualization::Charting::ChartHatchStyle::BackwardDiagonal;
			chartArea20->BackImageTransparentColor = System::Drawing::Color::Black;
			chartArea20->BackSecondaryColor = System::Drawing::Color::Black;
			chartArea20->BorderColor = System::Drawing::Color::White;
			chartArea20->Name = L"ChartArea1";
			this->B_SCOPE_H_LEFT->ChartAreas->Add(chartArea20);
			legend14->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			legend14->Enabled = false;
			legend14->LegendStyle = System::Windows::Forms::DataVisualization::Charting::LegendStyle::Row;
			legend14->Name = L"Legend1";
			this->B_SCOPE_H_LEFT->Legends->Add(legend14);
			this->B_SCOPE_H_LEFT->Location = System::Drawing::Point(-5, 6);
			this->B_SCOPE_H_LEFT->Name = L"B_SCOPE_H_LEFT";
			series51->BorderWidth = 2;
			series51->ChartArea = L"ChartArea1";
			series51->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series51->Color = System::Drawing::Color::Lime;
			series51->Legend = L"Legend1";
			series51->MarkerBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			series51->Name = L"Single1";
			series51->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series52->BorderWidth = 2;
			series52->ChartArea = L"ChartArea1";
			series52->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series52->Color = System::Drawing::Color::Yellow;
			series52->Legend = L"Legend1";
			series52->MarkerBorderColor = System::Drawing::Color::Red;
			series52->Name = L"Average1";
			series52->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series53->BorderWidth = 2;
			series53->ChartArea = L"ChartArea1";
			series53->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series53->Color = System::Drawing::Color::Red;
			series53->Legend = L"Legend1";
			series53->Name = L"Single2";
			series54->BorderWidth = 2;
			series54->ChartArea = L"ChartArea1";
			series54->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series54->Color = System::Drawing::Color::Aqua;
			series54->Legend = L"Legend1";
			series54->Name = L"Average2";
			this->B_SCOPE_H_LEFT->Series->Add(series51);
			this->B_SCOPE_H_LEFT->Series->Add(series52);
			this->B_SCOPE_H_LEFT->Series->Add(series53);
			this->B_SCOPE_H_LEFT->Series->Add(series54);
			this->B_SCOPE_H_LEFT->Size = System::Drawing::Size(418, 262);
			this->B_SCOPE_H_LEFT->TabIndex = 148;
			this->B_SCOPE_H_LEFT->Text = L"H - left";
			title8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			title8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			title8->Name = L"Title1";
			title8->Text = L"H - left";
			this->B_SCOPE_H_LEFT->Titles->Add(title8);
			// 
			// W_DATA_RECORDING
			// 
			this->W_DATA_RECORDING->BackColor = System::Drawing::Color::DarkGray;
			this->W_DATA_RECORDING->Enabled = false;
			this->W_DATA_RECORDING->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->W_DATA_RECORDING->FlatAppearance->BorderSize = 0;
			this->W_DATA_RECORDING->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->W_DATA_RECORDING->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->W_DATA_RECORDING->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->W_DATA_RECORDING->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->W_DATA_RECORDING->ForeColor = System::Drawing::Color::Black;
			this->W_DATA_RECORDING->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"W_DATA_RECORDING.Image")));
			this->W_DATA_RECORDING->Location = System::Drawing::Point(445, 627);
			this->W_DATA_RECORDING->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->W_DATA_RECORDING->Name = L"W_DATA_RECORDING";
			this->W_DATA_RECORDING->Size = System::Drawing::Size(50, 38);
			this->W_DATA_RECORDING->TabIndex = 137;
			this->TOOL_TIP_START_RECORD->SetToolTip(this->W_DATA_RECORDING, L"Please click \"Start Record\" for record the new data");
			this->W_DATA_RECORDING->UseVisualStyleBackColor = false;
			this->W_DATA_RECORDING->Click += gcnew System::EventHandler(this, &MyForm::W_RECORDING_START_Click);
			// 
			// W_START_WORK_CIRC
			// 
			this->W_START_WORK_CIRC->BackColor = System::Drawing::Color::DarkGray;
			this->W_START_WORK_CIRC->FlatAppearance->BorderSize = 0;
			this->W_START_WORK_CIRC->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->W_START_WORK_CIRC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->W_START_WORK_CIRC->ForeColor = System::Drawing::Color::Black;
			this->W_START_WORK_CIRC->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"W_START_WORK_CIRC.Image")));
			this->W_START_WORK_CIRC->Location = System::Drawing::Point(295, 627);
			this->W_START_WORK_CIRC->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->W_START_WORK_CIRC->Name = L"W_START_WORK_CIRC";
			this->W_START_WORK_CIRC->Size = System::Drawing::Size(50, 38);
			this->W_START_WORK_CIRC->TabIndex = 138;
			this->TOOL_TIP_START->SetToolTip(this->W_START_WORK_CIRC, L"Please click \"Start\" for work mode");
			this->W_START_WORK_CIRC->UseVisualStyleBackColor = false;
			this->W_START_WORK_CIRC->Click += gcnew System::EventHandler(this, &MyForm::G_START_WORK_CIRC_Click);
			// 
			// label147
			// 
			this->label147->AutoSize = true;
			this->label147->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label147->ForeColor = System::Drawing::Color::White;
			this->label147->Location = System::Drawing::Point(110, 138);
			this->label147->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label147->Name = L"label147";
			this->label147->Size = System::Drawing::Size(32, 13);
			this->label147->TabIndex = 165;
			this->label147->Text = L"[kHz]";
			// 
			// B_IO_UPDATE_rate
			// 
			this->B_IO_UPDATE_rate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_IO_UPDATE_rate->Location = System::Drawing::Point(73, 137);
			this->B_IO_UPDATE_rate->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_IO_UPDATE_rate->Name = L"B_IO_UPDATE_rate";
			this->B_IO_UPDATE_rate->ReadOnly = true;
			this->B_IO_UPDATE_rate->Size = System::Drawing::Size(30, 17);
			this->B_IO_UPDATE_rate->TabIndex = 77;
			this->B_IO_UPDATE_rate->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_AD9910_Set_aux_dac_B
			// 
			this->B_AD9910_Set_aux_dac_B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_AD9910_Set_aux_dac_B->Location = System::Drawing::Point(112, 116);
			this->B_AD9910_Set_aux_dac_B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_AD9910_Set_aux_dac_B->Name = L"B_AD9910_Set_aux_dac_B";
			this->B_AD9910_Set_aux_dac_B->ReadOnly = true;
			this->B_AD9910_Set_aux_dac_B->Size = System::Drawing::Size(30, 20);
			this->B_AD9910_Set_aux_dac_B->TabIndex = 76;
			this->B_AD9910_Set_aux_dac_B->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_chip_length_AD9910B
			// 
			this->B_chip_length_AD9910B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_chip_length_AD9910B->Location = System::Drawing::Point(112, 95);
			this->B_chip_length_AD9910B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_chip_length_AD9910B->Name = L"B_chip_length_AD9910B";
			this->B_chip_length_AD9910B->ReadOnly = true;
			this->B_chip_length_AD9910B->Size = System::Drawing::Size(30, 20);
			this->B_chip_length_AD9910B->TabIndex = 75;
			this->B_chip_length_AD9910B->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_Profile_AD9910B
			// 
			this->B_Profile_AD9910B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_Profile_AD9910B->Location = System::Drawing::Point(112, 74);
			this->B_Profile_AD9910B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Profile_AD9910B->Name = L"B_Profile_AD9910B";
			this->B_Profile_AD9910B->ReadOnly = true;
			this->B_Profile_AD9910B->Size = System::Drawing::Size(30, 20);
			this->B_Profile_AD9910B->TabIndex = 74;
			this->B_Profile_AD9910B->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_AD9910_Set_aux_dac_A
			// 
			this->B_AD9910_Set_aux_dac_A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_AD9910_Set_aux_dac_A->Location = System::Drawing::Point(73, 116);
			this->B_AD9910_Set_aux_dac_A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_AD9910_Set_aux_dac_A->Name = L"B_AD9910_Set_aux_dac_A";
			this->B_AD9910_Set_aux_dac_A->ReadOnly = true;
			this->B_AD9910_Set_aux_dac_A->Size = System::Drawing::Size(30, 20);
			this->B_AD9910_Set_aux_dac_A->TabIndex = 73;
			this->B_AD9910_Set_aux_dac_A->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_chip_length_AD9910A
			// 
			this->B_chip_length_AD9910A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_chip_length_AD9910A->Location = System::Drawing::Point(73, 95);
			this->B_chip_length_AD9910A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_chip_length_AD9910A->Name = L"B_chip_length_AD9910A";
			this->B_chip_length_AD9910A->ReadOnly = true;
			this->B_chip_length_AD9910A->Size = System::Drawing::Size(30, 20);
			this->B_chip_length_AD9910A->TabIndex = 72;
			this->B_chip_length_AD9910A->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_Profile_AD9910A
			// 
			this->B_Profile_AD9910A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_Profile_AD9910A->Location = System::Drawing::Point(73, 74);
			this->B_Profile_AD9910A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Profile_AD9910A->Name = L"B_Profile_AD9910A";
			this->B_Profile_AD9910A->ReadOnly = true;
			this->B_Profile_AD9910A->Size = System::Drawing::Size(30, 20);
			this->B_Profile_AD9910A->TabIndex = 71;
			this->B_Profile_AD9910A->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label129
			// 
			this->label129->AutoSize = true;
			this->label129->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label129->ForeColor = System::Drawing::Color::White;
			this->label129->Location = System::Drawing::Point(124, 56);
			this->label129->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label129->Name = L"label129";
			this->label129->Size = System::Drawing::Size(18, 15);
			this->label129->TabIndex = 70;
			this->label129->Text = L"B:";
			// 
			// label130
			// 
			this->label130->AutoSize = true;
			this->label130->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label130->ForeColor = System::Drawing::Color::White;
			this->label130->Location = System::Drawing::Point(79, 56);
			this->label130->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label130->Name = L"label130";
			this->label130->Size = System::Drawing::Size(17, 15);
			this->label130->TabIndex = 69;
			this->label130->Text = L"A:";
			// 
			// label131
			// 
			this->label131->AutoSize = true;
			this->label131->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label131->ForeColor = System::Drawing::Color::White;
			this->label131->Location = System::Drawing::Point(38, 79);
			this->label131->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label131->Name = L"label131";
			this->label131->Size = System::Drawing::Size(36, 13);
			this->label131->TabIndex = 0;
			this->label131->Text = L"Profile";
			// 
			// label132
			// 
			this->label132->AutoSize = true;
			this->label132->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label132->ForeColor = System::Drawing::Color::White;
			this->label132->Location = System::Drawing::Point(44, 119);
			this->label132->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label132->Name = L"label132";
			this->label132->Size = System::Drawing::Size(29, 13);
			this->label132->TabIndex = 20;
			this->label132->Text = L"Gain";
			// 
			// label133
			// 
			this->label133->AutoSize = true;
			this->label133->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label133->ForeColor = System::Drawing::Color::White;
			this->label133->Location = System::Drawing::Point(44, 138);
			this->label133->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label133->Name = L"label133";
			this->label133->Size = System::Drawing::Size(28, 13);
			this->label133->TabIndex = 4;
			this->label133->Text = L"PRF";
			// 
			// label134
			// 
			this->label134->AutoSize = true;
			this->label134->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label134->ForeColor = System::Drawing::Color::White;
			this->label134->Location = System::Drawing::Point(43, 99);
			this->label134->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label134->Name = L"label134";
			this->label134->Size = System::Drawing::Size(28, 13);
			this->label134->TabIndex = 3;
			this->label134->Text = L"Chip";
			// 
			// B_SelectLogFile_Of_Calibrator
			// 
			this->B_SelectLogFile_Of_Calibrator->FileName = L"Select LOG file of calibrator";
			this->B_SelectLogFile_Of_Calibrator->Filter = L"Log files (*.bin)|*.bin|All files (*.*)|*.*";
			this->B_SelectLogFile_Of_Calibrator->Title = L"Select LOG file of calibrator";
			// 
			// B_RANGE_meter
			// 
			this->B_RANGE_meter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_RANGE_meter->Location = System::Drawing::Point(96, 68);
			this->B_RANGE_meter->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RANGE_meter->Name = L"B_RANGE_meter";
			this->B_RANGE_meter->ReadOnly = true;
			this->B_RANGE_meter->Size = System::Drawing::Size(54, 20);
			this->B_RANGE_meter->TabIndex = 86;
			this->B_RANGE_meter->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label78
			// 
			this->label78->AutoSize = true;
			this->label78->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label78->ForeColor = System::Drawing::Color::White;
			this->label78->Location = System::Drawing::Point(14, 69);
			this->label78->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label78->Name = L"label78";
			this->label78->Size = System::Drawing::Size(56, 13);
			this->label78->TabIndex = 85;
			this->label78->Text = L"Range [m]";
			// 
			// B_OFFSET_sample
			// 
			this->B_OFFSET_sample->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_OFFSET_sample->Location = System::Drawing::Point(96, 46);
			this->B_OFFSET_sample->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_OFFSET_sample->Name = L"B_OFFSET_sample";
			this->B_OFFSET_sample->ReadOnly = true;
			this->B_OFFSET_sample->Size = System::Drawing::Size(54, 20);
			this->B_OFFSET_sample->TabIndex = 84;
			this->B_OFFSET_sample->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label76
			// 
			this->label76->AutoSize = true;
			this->label76->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label76->ForeColor = System::Drawing::Color::White;
			this->label76->Location = System::Drawing::Point(14, 48);
			this->label76->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label76->Name = L"label76";
			this->label76->Size = System::Drawing::Size(71, 13);
			this->label76->TabIndex = 83;
			this->label76->Text = L"Offset sample";
			// 
			// B_FIFO_length
			// 
			this->B_FIFO_length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_FIFO_length->Location = System::Drawing::Point(88, 399);
			this->B_FIFO_length->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_FIFO_length->Name = L"B_FIFO_length";
			this->B_FIFO_length->ReadOnly = true;
			this->B_FIFO_length->Size = System::Drawing::Size(54, 20);
			this->B_FIFO_length->TabIndex = 82;
			this->B_FIFO_length->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_Buffer_length
			// 
			this->B_Buffer_length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_Buffer_length->Location = System::Drawing::Point(88, 378);
			this->B_Buffer_length->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Buffer_length->Name = L"B_Buffer_length";
			this->B_Buffer_length->ReadOnly = true;
			this->B_Buffer_length->Size = System::Drawing::Size(54, 20);
			this->B_Buffer_length->TabIndex = 81;
			this->B_Buffer_length->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_Number_of_buffers
			// 
			this->B_Number_of_buffers->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_Number_of_buffers->Location = System::Drawing::Point(96, 24);
			this->B_Number_of_buffers->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Number_of_buffers->Name = L"B_Number_of_buffers";
			this->B_Number_of_buffers->ReadOnly = true;
			this->B_Number_of_buffers->Size = System::Drawing::Size(54, 20);
			this->B_Number_of_buffers->TabIndex = 80;
			this->B_Number_of_buffers->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label111
			// 
			this->label111->AutoSize = true;
			this->label111->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label111->ForeColor = System::Drawing::Color::White;
			this->label111->Location = System::Drawing::Point(14, 27);
			this->label111->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label111->Name = L"label111";
			this->label111->Size = System::Drawing::Size(61, 13);
			this->label111->TabIndex = 18;
			this->label111->Text = L"# of buffers";
			// 
			// label112
			// 
			this->label112->AutoSize = true;
			this->label112->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label112->ForeColor = System::Drawing::Color::White;
			this->label112->Location = System::Drawing::Point(14, 401);
			this->label112->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label112->Name = L"label112";
			this->label112->Size = System::Drawing::Size(62, 13);
			this->label112->TabIndex = 16;
			this->label112->Text = L"FIFO length";
			// 
			// label113
			// 
			this->label113->AutoSize = true;
			this->label113->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label113->ForeColor = System::Drawing::Color::White;
			this->label113->Location = System::Drawing::Point(14, 381);
			this->label113->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label113->Name = L"label113";
			this->label113->Size = System::Drawing::Size(67, 13);
			this->label113->TabIndex = 17;
			this->label113->Text = L"Buffer length";
			// 
			// B_GROUP_RF
			// 
			this->B_GROUP_RF->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->B_GROUP_RF->Controls->Add(this->label45);
			this->B_GROUP_RF->Controls->Add(this->B_RF2_ON);
			this->B_GROUP_RF->Controls->Add(this->label149);
			this->B_GROUP_RF->Controls->Add(this->label148);
			this->B_GROUP_RF->Controls->Add(this->B_TxRx_control_MODE);
			this->B_GROUP_RF->Controls->Add(this->B_SYSTEM_ID);
			this->B_GROUP_RF->Controls->Add(this->label147);
			this->B_GROUP_RF->Controls->Add(this->B_IO_UPDATE_rate);
			this->B_GROUP_RF->Controls->Add(this->B_ANT_SAMPLE_SELECT);
			this->B_GROUP_RF->Controls->Add(this->B_AD9910_Set_aux_dac_B);
			this->B_GROUP_RF->Controls->Add(this->B_chip_length_AD9910B);
			this->B_GROUP_RF->Controls->Add(this->B_IF_SELECT_PROBE);
			this->B_GROUP_RF->Controls->Add(this->B_Profile_AD9910B);
			this->B_GROUP_RF->Controls->Add(this->B_AD9910_Set_aux_dac_A);
			this->B_GROUP_RF->Controls->Add(this->B_chip_length_AD9910A);
			this->B_GROUP_RF->Controls->Add(this->B_IF_SELECT_TX3);
			this->B_GROUP_RF->Controls->Add(this->B_Profile_AD9910A);
			this->B_GROUP_RF->Controls->Add(this->label129);
			this->B_GROUP_RF->Controls->Add(this->B_IF_SELECT_TX2);
			this->B_GROUP_RF->Controls->Add(this->label130);
			this->B_GROUP_RF->Controls->Add(this->B_FIFO_length);
			this->B_GROUP_RF->Controls->Add(this->label131);
			this->B_GROUP_RF->Controls->Add(this->B_IF_SELECT_TX1);
			this->B_GROUP_RF->Controls->Add(this->label132);
			this->B_GROUP_RF->Controls->Add(this->B_Buffer_length);
			this->B_GROUP_RF->Controls->Add(this->label133);
			this->B_GROUP_RF->Controls->Add(this->label31);
			this->B_GROUP_RF->Controls->Add(this->label134);
			this->B_GROUP_RF->Controls->Add(this->label30);
			this->B_GROUP_RF->Controls->Add(this->label112);
			this->B_GROUP_RF->Controls->Add(this->label29);
			this->B_GROUP_RF->Controls->Add(this->label113);
			this->B_GROUP_RF->Controls->Add(this->B_IO_UPDATE_ON);
			this->B_GROUP_RF->Controls->Add(this->B_TX_ON3);
			this->B_GROUP_RF->Controls->Add(this->B_TX_LO_TR);
			this->B_GROUP_RF->Controls->Add(this->label7);
			this->B_GROUP_RF->Controls->Add(this->B_SAMPLE_ON_OFF);
			this->B_GROUP_RF->Controls->Add(this->B_TX_ON2);
			this->B_GROUP_RF->Controls->Add(this->label6);
			this->B_GROUP_RF->Controls->Add(this->B_TX_ON1);
			this->B_GROUP_RF->Controls->Add(this->label5);
			this->B_GROUP_RF->Controls->Add(this->B_ATTN_RX4);
			this->B_GROUP_RF->Controls->Add(this->B_ATTN_RX3);
			this->B_GROUP_RF->Controls->Add(this->B_ATTN_RX2);
			this->B_GROUP_RF->Controls->Add(this->B_ATTN_RX1);
			this->B_GROUP_RF->Controls->Add(this->B_ATTN_TX3);
			this->B_GROUP_RF->Controls->Add(this->B_ATTN_TX2);
			this->B_GROUP_RF->Controls->Add(this->B_ATTN_TX1);
			this->B_GROUP_RF->Controls->Add(this->label116);
			this->B_GROUP_RF->Controls->Add(this->label122);
			this->B_GROUP_RF->Controls->Add(this->label123);
			this->B_GROUP_RF->Controls->Add(this->label124);
			this->B_GROUP_RF->Controls->Add(this->label125);
			this->B_GROUP_RF->Controls->Add(this->label126);
			this->B_GROUP_RF->Controls->Add(this->label127);
			this->B_GROUP_RF->Controls->Add(this->label128);
			this->B_GROUP_RF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_GROUP_RF->ForeColor = System::Drawing::Color::White;
			this->B_GROUP_RF->Location = System::Drawing::Point(121, 3);
			this->B_GROUP_RF->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_RF->Name = L"B_GROUP_RF";
			this->B_GROUP_RF->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_RF->Size = System::Drawing::Size(159, 422);
			this->B_GROUP_RF->TabIndex = 128;
			this->B_GROUP_RF->TabStop = false;
			this->B_GROUP_RF->Text = L"Tx/Rx control status";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label45->ForeColor = System::Drawing::Color::White;
			this->label45->Location = System::Drawing::Point(14, 338);
			this->label45->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(27, 13);
			this->label45->TabIndex = 172;
			this->label45->Text = L"RF2";
			// 
			// B_RF2_ON
			// 
			this->B_RF2_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_RF2_ON->Location = System::Drawing::Point(45, 335);
			this->B_RF2_ON->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RF2_ON->Name = L"B_RF2_ON";
			this->B_RF2_ON->ReadOnly = true;
			this->B_RF2_ON->Size = System::Drawing::Size(30, 20);
			this->B_RF2_ON->TabIndex = 171;
			this->B_RF2_ON->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label149
			// 
			this->label149->AutoSize = true;
			this->label149->Cursor = System::Windows::Forms::Cursors::AppStarting;
			this->label149->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label149->ForeColor = System::Drawing::Color::Yellow;
			this->label149->Location = System::Drawing::Point(14, 40);
			this->label149->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label149->Name = L"label149";
			this->label149->Size = System::Drawing::Size(38, 13);
			this->label149->TabIndex = 168;
			this->label149->Text = L"Mode";
			// 
			// label148
			// 
			this->label148->AutoSize = true;
			this->label148->Cursor = System::Windows::Forms::Cursors::AppStarting;
			this->label148->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label148->ForeColor = System::Drawing::Color::Yellow;
			this->label148->Location = System::Drawing::Point(14, 22);
			this->label148->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label148->Name = L"label148";
			this->label148->Size = System::Drawing::Size(64, 13);
			this->label148->TabIndex = 167;
			this->label148->Text = L"System ID";
			// 
			// B_TxRx_control_MODE
			// 
			this->B_TxRx_control_MODE->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->B_TxRx_control_MODE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->B_TxRx_control_MODE->Location = System::Drawing::Point(56, 38);
			this->B_TxRx_control_MODE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TxRx_control_MODE->Name = L"B_TxRx_control_MODE";
			this->B_TxRx_control_MODE->ReadOnly = true;
			this->B_TxRx_control_MODE->Size = System::Drawing::Size(86, 20);
			this->B_TxRx_control_MODE->TabIndex = 166;
			this->B_TxRx_control_MODE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SYSTEM_ID
			// 
			this->B_SYSTEM_ID->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->B_SYSTEM_ID->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SYSTEM_ID->Location = System::Drawing::Point(82, 16);
			this->B_SYSTEM_ID->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SYSTEM_ID->Name = L"B_SYSTEM_ID";
			this->B_SYSTEM_ID->ReadOnly = true;
			this->B_SYSTEM_ID->Size = System::Drawing::Size(60, 20);
			this->B_SYSTEM_ID->TabIndex = 165;
			this->B_SYSTEM_ID->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_ANT_SAMPLE_SELECT
			// 
			this->B_ANT_SAMPLE_SELECT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_ANT_SAMPLE_SELECT->Location = System::Drawing::Point(48, 312);
			this->B_ANT_SAMPLE_SELECT->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_ANT_SAMPLE_SELECT->Name = L"B_ANT_SAMPLE_SELECT";
			this->B_ANT_SAMPLE_SELECT->ReadOnly = true;
			this->B_ANT_SAMPLE_SELECT->Size = System::Drawing::Size(26, 20);
			this->B_ANT_SAMPLE_SELECT->TabIndex = 156;
			this->B_ANT_SAMPLE_SELECT->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_IF_SELECT_PROBE
			// 
			this->B_IF_SELECT_PROBE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_IF_SELECT_PROBE->Location = System::Drawing::Point(112, 312);
			this->B_IF_SELECT_PROBE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_IF_SELECT_PROBE->Name = L"B_IF_SELECT_PROBE";
			this->B_IF_SELECT_PROBE->ReadOnly = true;
			this->B_IF_SELECT_PROBE->Size = System::Drawing::Size(30, 20);
			this->B_IF_SELECT_PROBE->TabIndex = 155;
			this->B_IF_SELECT_PROBE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_IF_SELECT_TX3
			// 
			this->B_IF_SELECT_TX3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_IF_SELECT_TX3->Location = System::Drawing::Point(112, 290);
			this->B_IF_SELECT_TX3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_IF_SELECT_TX3->Name = L"B_IF_SELECT_TX3";
			this->B_IF_SELECT_TX3->ReadOnly = true;
			this->B_IF_SELECT_TX3->Size = System::Drawing::Size(30, 20);
			this->B_IF_SELECT_TX3->TabIndex = 154;
			this->B_IF_SELECT_TX3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_IF_SELECT_TX2
			// 
			this->B_IF_SELECT_TX2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_IF_SELECT_TX2->Location = System::Drawing::Point(112, 268);
			this->B_IF_SELECT_TX2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_IF_SELECT_TX2->Name = L"B_IF_SELECT_TX2";
			this->B_IF_SELECT_TX2->ReadOnly = true;
			this->B_IF_SELECT_TX2->Size = System::Drawing::Size(30, 20);
			this->B_IF_SELECT_TX2->TabIndex = 153;
			this->B_IF_SELECT_TX2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_IF_SELECT_TX1
			// 
			this->B_IF_SELECT_TX1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_IF_SELECT_TX1->Location = System::Drawing::Point(112, 246);
			this->B_IF_SELECT_TX1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_IF_SELECT_TX1->Name = L"B_IF_SELECT_TX1";
			this->B_IF_SELECT_TX1->ReadOnly = true;
			this->B_IF_SELECT_TX1->Size = System::Drawing::Size(30, 20);
			this->B_IF_SELECT_TX1->TabIndex = 152;
			this->B_IF_SELECT_TX1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label31->ForeColor = System::Drawing::Color::White;
			this->label31->Location = System::Drawing::Point(80, 338);
			this->label31->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(27, 13);
			this->label31->TabIndex = 151;
			this->label31->Text = L"T/R";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label30->ForeColor = System::Drawing::Color::White;
			this->label30->Location = System::Drawing::Point(76, 360);
			this->label30->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(32, 13);
			this->label30->TabIndex = 150;
			this->label30->Text = L"Cont.";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label29->ForeColor = System::Drawing::Color::White;
			this->label29->Location = System::Drawing::Point(14, 313);
			this->label29->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(35, 13);
			this->label29->TabIndex = 149;
			this->label29->Text = L"Probe";
			// 
			// B_IO_UPDATE_ON
			// 
			this->B_IO_UPDATE_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_IO_UPDATE_ON->Location = System::Drawing::Point(112, 356);
			this->B_IO_UPDATE_ON->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_IO_UPDATE_ON->Name = L"B_IO_UPDATE_ON";
			this->B_IO_UPDATE_ON->ReadOnly = true;
			this->B_IO_UPDATE_ON->Size = System::Drawing::Size(30, 20);
			this->B_IO_UPDATE_ON->TabIndex = 148;
			this->B_IO_UPDATE_ON->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TX_ON3
			// 
			this->B_TX_ON3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TX_ON3->Location = System::Drawing::Point(77, 290);
			this->B_TX_ON3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TX_ON3->Name = L"B_TX_ON3";
			this->B_TX_ON3->ReadOnly = true;
			this->B_TX_ON3->Size = System::Drawing::Size(30, 20);
			this->B_TX_ON3->TabIndex = 85;
			this->B_TX_ON3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TX_LO_TR
			// 
			this->B_TX_LO_TR->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TX_LO_TR->Location = System::Drawing::Point(112, 334);
			this->B_TX_LO_TR->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TX_LO_TR->Name = L"B_TX_LO_TR";
			this->B_TX_LO_TR->ReadOnly = true;
			this->B_TX_LO_TR->Size = System::Drawing::Size(30, 20);
			this->B_TX_LO_TR->TabIndex = 147;
			this->B_TX_LO_TR->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(14, 291);
			this->label7->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(43, 13);
			this->label7->TabIndex = 86;
			this->label7->Text = L"TX3 (C)";
			// 
			// B_SAMPLE_ON_OFF
			// 
			this->B_SAMPLE_ON_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_SAMPLE_ON_OFF->Location = System::Drawing::Point(77, 312);
			this->B_SAMPLE_ON_OFF->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_SAMPLE_ON_OFF->Name = L"B_SAMPLE_ON_OFF";
			this->B_SAMPLE_ON_OFF->ReadOnly = true;
			this->B_SAMPLE_ON_OFF->Size = System::Drawing::Size(30, 20);
			this->B_SAMPLE_ON_OFF->TabIndex = 146;
			this->B_SAMPLE_ON_OFF->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_TX_ON2
			// 
			this->B_TX_ON2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TX_ON2->Location = System::Drawing::Point(77, 268);
			this->B_TX_ON2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TX_ON2->Name = L"B_TX_ON2";
			this->B_TX_ON2->ReadOnly = true;
			this->B_TX_ON2->Size = System::Drawing::Size(30, 20);
			this->B_TX_ON2->TabIndex = 84;
			this->B_TX_ON2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(14, 272);
			this->label6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(50, 13);
			this->label6->TabIndex = 85;
			this->label6->Text = L"TX2 (H)  ";
			// 
			// B_TX_ON1
			// 
			this->B_TX_ON1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_TX_ON1->Location = System::Drawing::Point(77, 246);
			this->B_TX_ON1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_TX_ON1->Name = L"B_TX_ON1";
			this->B_TX_ON1->ReadOnly = true;
			this->B_TX_ON1->Size = System::Drawing::Size(30, 20);
			this->B_TX_ON1->TabIndex = 83;
			this->B_TX_ON1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(14, 252);
			this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(49, 13);
			this->label5->TabIndex = 84;
			this->label5->Text = L"TX1 (V)  ";
			// 
			// B_ATTN_RX4
			// 
			this->B_ATTN_RX4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_ATTN_RX4->Location = System::Drawing::Point(112, 222);
			this->B_ATTN_RX4->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_ATTN_RX4->Name = L"B_ATTN_RX4";
			this->B_ATTN_RX4->ReadOnly = true;
			this->B_ATTN_RX4->Size = System::Drawing::Size(30, 20);
			this->B_ATTN_RX4->TabIndex = 83;
			this->B_ATTN_RX4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_ATTN_RX3
			// 
			this->B_ATTN_RX3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_ATTN_RX3->Location = System::Drawing::Point(112, 200);
			this->B_ATTN_RX3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_ATTN_RX3->Name = L"B_ATTN_RX3";
			this->B_ATTN_RX3->ReadOnly = true;
			this->B_ATTN_RX3->Size = System::Drawing::Size(30, 20);
			this->B_ATTN_RX3->TabIndex = 82;
			this->B_ATTN_RX3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_ATTN_RX2
			// 
			this->B_ATTN_RX2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_ATTN_RX2->Location = System::Drawing::Point(112, 178);
			this->B_ATTN_RX2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_ATTN_RX2->Name = L"B_ATTN_RX2";
			this->B_ATTN_RX2->ReadOnly = true;
			this->B_ATTN_RX2->Size = System::Drawing::Size(30, 20);
			this->B_ATTN_RX2->TabIndex = 81;
			this->B_ATTN_RX2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_ATTN_RX1
			// 
			this->B_ATTN_RX1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_ATTN_RX1->Location = System::Drawing::Point(112, 157);
			this->B_ATTN_RX1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_ATTN_RX1->Name = L"B_ATTN_RX1";
			this->B_ATTN_RX1->ReadOnly = true;
			this->B_ATTN_RX1->Size = System::Drawing::Size(30, 20);
			this->B_ATTN_RX1->TabIndex = 80;
			this->B_ATTN_RX1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_ATTN_TX3
			// 
			this->B_ATTN_TX3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_ATTN_TX3->Location = System::Drawing::Point(44, 222);
			this->B_ATTN_TX3->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_ATTN_TX3->Name = L"B_ATTN_TX3";
			this->B_ATTN_TX3->ReadOnly = true;
			this->B_ATTN_TX3->Size = System::Drawing::Size(30, 20);
			this->B_ATTN_TX3->TabIndex = 79;
			this->B_ATTN_TX3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_ATTN_TX2
			// 
			this->B_ATTN_TX2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_ATTN_TX2->Location = System::Drawing::Point(44, 200);
			this->B_ATTN_TX2->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_ATTN_TX2->Name = L"B_ATTN_TX2";
			this->B_ATTN_TX2->ReadOnly = true;
			this->B_ATTN_TX2->Size = System::Drawing::Size(30, 20);
			this->B_ATTN_TX2->TabIndex = 78;
			this->B_ATTN_TX2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_ATTN_TX1
			// 
			this->B_ATTN_TX1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_ATTN_TX1->Location = System::Drawing::Point(44, 178);
			this->B_ATTN_TX1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_ATTN_TX1->Name = L"B_ATTN_TX1";
			this->B_ATTN_TX1->ReadOnly = true;
			this->B_ATTN_TX1->Size = System::Drawing::Size(30, 20);
			this->B_ATTN_TX1->TabIndex = 77;
			this->B_ATTN_TX1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label116
			// 
			this->label116->AutoSize = true;
			this->label116->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label116->ForeColor = System::Drawing::Color::White;
			this->label116->Location = System::Drawing::Point(23, 160);
			this->label116->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label116->Name = L"label116";
			this->label116->Size = System::Drawing::Size(60, 15);
			this->label116->TabIndex = 68;
			this->label116->Text = L"Gain [dB]:";
			// 
			// label122
			// 
			this->label122->AutoSize = true;
			this->label122->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label122->ForeColor = System::Drawing::Color::White;
			this->label122->Location = System::Drawing::Point(14, 223);
			this->label122->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label122->Name = L"label122";
			this->label122->Size = System::Drawing::Size(27, 13);
			this->label122->TabIndex = 25;
			this->label122->Text = L"TX3";
			// 
			// label123
			// 
			this->label123->AutoSize = true;
			this->label123->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label123->ForeColor = System::Drawing::Color::White;
			this->label123->Location = System::Drawing::Point(79, 162);
			this->label123->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label123->Name = L"label123";
			this->label123->Size = System::Drawing::Size(28, 13);
			this->label123->TabIndex = 24;
			this->label123->Text = L"RX1";
			// 
			// label124
			// 
			this->label124->AutoSize = true;
			this->label124->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label124->ForeColor = System::Drawing::Color::White;
			this->label124->Location = System::Drawing::Point(79, 183);
			this->label124->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label124->Name = L"label124";
			this->label124->Size = System::Drawing::Size(28, 13);
			this->label124->TabIndex = 23;
			this->label124->Text = L"RX2";
			// 
			// label125
			// 
			this->label125->AutoSize = true;
			this->label125->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label125->ForeColor = System::Drawing::Color::White;
			this->label125->Location = System::Drawing::Point(79, 204);
			this->label125->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label125->Name = L"label125";
			this->label125->Size = System::Drawing::Size(28, 13);
			this->label125->TabIndex = 22;
			this->label125->Text = L"RX3";
			// 
			// label126
			// 
			this->label126->AutoSize = true;
			this->label126->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label126->ForeColor = System::Drawing::Color::White;
			this->label126->Location = System::Drawing::Point(79, 224);
			this->label126->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label126->Name = L"label126";
			this->label126->Size = System::Drawing::Size(28, 13);
			this->label126->TabIndex = 21;
			this->label126->Text = L"RX4";
			// 
			// label127
			// 
			this->label127->AutoSize = true;
			this->label127->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label127->ForeColor = System::Drawing::Color::White;
			this->label127->Location = System::Drawing::Point(14, 183);
			this->label127->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label127->Name = L"label127";
			this->label127->Size = System::Drawing::Size(27, 13);
			this->label127->TabIndex = 9;
			this->label127->Text = L"TX1";
			// 
			// label128
			// 
			this->label128->AutoSize = true;
			this->label128->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label128->ForeColor = System::Drawing::Color::White;
			this->label128->Location = System::Drawing::Point(14, 203);
			this->label128->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label128->Name = L"label128";
			this->label128->Size = System::Drawing::Size(27, 13);
			this->label128->TabIndex = 8;
			this->label128->Text = L"TX2";
			// 
			// B_RANGE_DECIMATION
			// 
			this->B_RANGE_DECIMATION->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_RANGE_DECIMATION->Location = System::Drawing::Point(96, 178);
			this->B_RANGE_DECIMATION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RANGE_DECIMATION->Name = L"B_RANGE_DECIMATION";
			this->B_RANGE_DECIMATION->ReadOnly = true;
			this->B_RANGE_DECIMATION->Size = System::Drawing::Size(54, 20);
			this->B_RANGE_DECIMATION->TabIndex = 170;
			this->B_RANGE_DECIMATION->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label162
			// 
			this->label162->AutoSize = true;
			this->label162->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label162->ForeColor = System::Drawing::Color::White;
			this->label162->Location = System::Drawing::Point(14, 181);
			this->label162->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label162->Name = L"label162";
			this->label162->Size = System::Drawing::Size(60, 13);
			this->label162->TabIndex = 169;
			this->label162->Text = L"Range dec";
			// 
			// B_MAX_VELOCITY
			// 
			this->B_MAX_VELOCITY->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_MAX_VELOCITY->Location = System::Drawing::Point(96, 156);
			this->B_MAX_VELOCITY->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_MAX_VELOCITY->Name = L"B_MAX_VELOCITY";
			this->B_MAX_VELOCITY->ReadOnly = true;
			this->B_MAX_VELOCITY->Size = System::Drawing::Size(54, 20);
			this->B_MAX_VELOCITY->TabIndex = 157;
			this->B_MAX_VELOCITY->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label161
			// 
			this->label161->AutoSize = true;
			this->label161->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label161->ForeColor = System::Drawing::Color::White;
			this->label161->Location = System::Drawing::Point(14, 159);
			this->label161->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label161->Name = L"label161";
			this->label161->Size = System::Drawing::Size(81, 13);
			this->label161->TabIndex = 156;
			this->label161->Text = L"max vel. [Buff#]";
			// 
			// label150
			// 
			this->label150->AutoSize = true;
			this->label150->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label150->ForeColor = System::Drawing::Color::White;
			this->label150->Location = System::Drawing::Point(14, 113);
			this->label150->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label150->Name = L"label150";
			this->label150->Size = System::Drawing::Size(63, 13);
			this->label150->TabIndex = 155;
			this->label150->Text = L"Threshold 1";
			// 
			// B_Target_detection_1st_threshold
			// 
			this->B_Target_detection_1st_threshold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_Target_detection_1st_threshold->Location = System::Drawing::Point(96, 112);
			this->B_Target_detection_1st_threshold->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Target_detection_1st_threshold->Name = L"B_Target_detection_1st_threshold";
			this->B_Target_detection_1st_threshold->ReadOnly = true;
			this->B_Target_detection_1st_threshold->Size = System::Drawing::Size(54, 20);
			this->B_Target_detection_1st_threshold->TabIndex = 154;
			this->B_Target_detection_1st_threshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_GROUP_ALGORITHMS
			// 
			this->B_GROUP_ALGORITHMS->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->B_GROUP_ALGORITHMS->Controls->Add(this->label241);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->B_Target_detection_2nd_threshold);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->B_BATCH_DURATION);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->B_AGC_threshold);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->label110);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->B_RANGE_DECIMATION);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->B_Target_detection_1st_threshold);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->label162);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->B_MAX_VELOCITY);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->B_RANGE_meter);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->label161);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->B_OFFSET_sample);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->label76);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->label78);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->B_Number_of_buffers);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->label111);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->label114);
			this->B_GROUP_ALGORITHMS->Controls->Add(this->label150);
			this->B_GROUP_ALGORITHMS->ForeColor = System::Drawing::Color::White;
			this->B_GROUP_ALGORITHMS->Location = System::Drawing::Point(121, 427);
			this->B_GROUP_ALGORITHMS->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_ALGORITHMS->Name = L"B_GROUP_ALGORITHMS";
			this->B_GROUP_ALGORITHMS->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_ALGORITHMS->Size = System::Drawing::Size(158, 236);
			this->B_GROUP_ALGORITHMS->TabIndex = 168;
			this->B_GROUP_ALGORITHMS->TabStop = false;
			this->B_GROUP_ALGORITHMS->Text = L"Digital control status";
			// 
			// label241
			// 
			this->label241->AutoSize = true;
			this->label241->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label241->ForeColor = System::Drawing::Color::White;
			this->label241->Location = System::Drawing::Point(14, 135);
			this->label241->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label241->Name = L"label241";
			this->label241->Size = System::Drawing::Size(63, 13);
			this->label241->TabIndex = 176;
			this->label241->Text = L"Threshold 2";
			// 
			// B_Target_detection_2nd_threshold
			// 
			this->B_Target_detection_2nd_threshold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_Target_detection_2nd_threshold->Location = System::Drawing::Point(96, 134);
			this->B_Target_detection_2nd_threshold->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Target_detection_2nd_threshold->Name = L"B_Target_detection_2nd_threshold";
			this->B_Target_detection_2nd_threshold->ReadOnly = true;
			this->B_Target_detection_2nd_threshold->Size = System::Drawing::Size(54, 20);
			this->B_Target_detection_2nd_threshold->TabIndex = 175;
			this->B_Target_detection_2nd_threshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_BATCH_DURATION
			// 
			this->B_BATCH_DURATION->Location = System::Drawing::Point(96, 90);
			this->B_BATCH_DURATION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_BATCH_DURATION->Name = L"B_BATCH_DURATION";
			this->B_BATCH_DURATION->ReadOnly = true;
			this->B_BATCH_DURATION->Size = System::Drawing::Size(54, 20);
			this->B_BATCH_DURATION->TabIndex = 173;
			this->B_BATCH_DURATION->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_AGC_threshold
			// 
			this->B_AGC_threshold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_AGC_threshold->Location = System::Drawing::Point(96, 200);
			this->B_AGC_threshold->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_AGC_threshold->Name = L"B_AGC_threshold";
			this->B_AGC_threshold->ReadOnly = true;
			this->B_AGC_threshold->Size = System::Drawing::Size(54, 20);
			this->B_AGC_threshold->TabIndex = 172;
			this->B_AGC_threshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->B_AGC_threshold->Visible = false;
			// 
			// label110
			// 
			this->label110->AutoSize = true;
			this->label110->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label110->ForeColor = System::Drawing::Color::White;
			this->label110->Location = System::Drawing::Point(14, 205);
			this->label110->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label110->Name = L"label110";
			this->label110->Size = System::Drawing::Size(75, 13);
			this->label110->TabIndex = 171;
			this->label110->Text = L"AGC threshold";
			this->label110->Visible = false;
			// 
			// label114
			// 
			this->label114->AutoSize = true;
			this->label114->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label114->ForeColor = System::Drawing::Color::White;
			this->label114->Location = System::Drawing::Point(14, 91);
			this->label114->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label114->Name = L"label114";
			this->label114->Size = System::Drawing::Size(76, 13);
			this->label114->TabIndex = 174;
			this->label114->Text = L"Batch duration";
			// 
			// B_GROUP_STATE_MACHINES
			// 
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->label211);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->B_CHB_WORK_STATE);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->B_DET_INITIALIZATION_STATE);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->label168);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->label167);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->B_DET_FIRST_DETECTION_STATE);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->label166);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->B_DET_CALIBRATE_STATE);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->label164);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->label163);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->B_CHA_WORK_STATE);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->label38);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->B_DET_BRAIN_STATE);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->B_DET_WORK_STATE);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->L_ACQUISITION);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->B_DET_ACQUISITION_STATE);
			this->B_GROUP_STATE_MACHINES->Controls->Add(this->L_WORK);
			this->B_GROUP_STATE_MACHINES->ForeColor = System::Drawing::Color::White;
			this->B_GROUP_STATE_MACHINES->Location = System::Drawing::Point(8, 456);
			this->B_GROUP_STATE_MACHINES->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_STATE_MACHINES->Name = L"B_GROUP_STATE_MACHINES";
			this->B_GROUP_STATE_MACHINES->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_STATE_MACHINES->Size = System::Drawing::Size(125, 197);
			this->B_GROUP_STATE_MACHINES->TabIndex = 203;
			this->B_GROUP_STATE_MACHINES->TabStop = false;
			this->B_GROUP_STATE_MACHINES->Text = L"DSPs State machines";
			// 
			// label211
			// 
			this->label211->AutoSize = true;
			this->label211->ForeColor = System::Drawing::Color::White;
			this->label211->Location = System::Drawing::Point(6, 128);
			this->label211->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label211->Name = L"label211";
			this->label211->Size = System::Drawing::Size(61, 13);
			this->label211->TabIndex = 189;
			this->label211->Text = L"Initialization";
			// 
			// B_CHB_WORK_STATE
			// 
			this->B_CHB_WORK_STATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHB_WORK_STATE->Location = System::Drawing::Point(70, 171);
			this->B_CHB_WORK_STATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CHB_WORK_STATE->Name = L"B_CHB_WORK_STATE";
			this->B_CHB_WORK_STATE->ReadOnly = true;
			this->B_CHB_WORK_STATE->Size = System::Drawing::Size(45, 20);
			this->B_CHB_WORK_STATE->TabIndex = 147;
			this->B_CHB_WORK_STATE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_DET_INITIALIZATION_STATE
			// 
			this->B_DET_INITIALIZATION_STATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_INITIALIZATION_STATE->Location = System::Drawing::Point(67, 128);
			this->B_DET_INITIALIZATION_STATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DET_INITIALIZATION_STATE->Name = L"B_DET_INITIALIZATION_STATE";
			this->B_DET_INITIALIZATION_STATE->ReadOnly = true;
			this->B_DET_INITIALIZATION_STATE->Size = System::Drawing::Size(45, 20);
			this->B_DET_INITIALIZATION_STATE->TabIndex = 188;
			this->B_DET_INITIALIZATION_STATE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label168
			// 
			this->label168->AutoSize = true;
			this->label168->ForeColor = System::Drawing::Color::White;
			this->label168->Location = System::Drawing::Point(6, 16);
			this->label168->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label168->Name = L"label168";
			this->label168->Size = System::Drawing::Size(29, 13);
			this->label168->TabIndex = 146;
			this->label168->Text = L"DET";
			// 
			// label167
			// 
			this->label167->AutoSize = true;
			this->label167->ForeColor = System::Drawing::Color::White;
			this->label167->Location = System::Drawing::Point(4, 107);
			this->label167->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label167->Name = L"label167";
			this->label167->Size = System::Drawing::Size(63, 13);
			this->label167->TabIndex = 145;
			this->label167->Text = L"1st detector";
			// 
			// B_DET_FIRST_DETECTION_STATE
			// 
			this->B_DET_FIRST_DETECTION_STATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_FIRST_DETECTION_STATE->Location = System::Drawing::Point(67, 107);
			this->B_DET_FIRST_DETECTION_STATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DET_FIRST_DETECTION_STATE->Name = L"B_DET_FIRST_DETECTION_STATE";
			this->B_DET_FIRST_DETECTION_STATE->ReadOnly = true;
			this->B_DET_FIRST_DETECTION_STATE->Size = System::Drawing::Size(45, 20);
			this->B_DET_FIRST_DETECTION_STATE->TabIndex = 144;
			this->B_DET_FIRST_DETECTION_STATE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label166
			// 
			this->label166->AutoSize = true;
			this->label166->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->label166->ForeColor = System::Drawing::Color::White;
			this->label166->Location = System::Drawing::Point(19, 89);
			this->label166->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label166->Name = L"label166";
			this->label166->Size = System::Drawing::Size(48, 13);
			this->label166->TabIndex = 143;
			this->label166->Text = L"Calibrate";
			// 
			// B_DET_CALIBRATE_STATE
			// 
			this->B_DET_CALIBRATE_STATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_CALIBRATE_STATE->Location = System::Drawing::Point(67, 86);
			this->B_DET_CALIBRATE_STATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DET_CALIBRATE_STATE->Name = L"B_DET_CALIBRATE_STATE";
			this->B_DET_CALIBRATE_STATE->ReadOnly = true;
			this->B_DET_CALIBRATE_STATE->Size = System::Drawing::Size(45, 20);
			this->B_DET_CALIBRATE_STATE->TabIndex = 142;
			this->B_DET_CALIBRATE_STATE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label164
			// 
			this->label164->AutoSize = true;
			this->label164->ForeColor = System::Drawing::Color::White;
			this->label164->Location = System::Drawing::Point(14, 155);
			this->label164->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label164->Name = L"label164";
			this->label164->Size = System::Drawing::Size(36, 13);
			this->label164->TabIndex = 139;
			this->label164->Text = L"CHAB";
			// 
			// label163
			// 
			this->label163->AutoSize = true;
			this->label163->ForeColor = System::Drawing::Color::White;
			this->label163->Location = System::Drawing::Point(76, 155);
			this->label163->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label163->Name = L"label163";
			this->label163->Size = System::Drawing::Size(33, 13);
			this->label163->TabIndex = 138;
			this->label163->Text = L"Work";
			// 
			// B_CHA_WORK_STATE
			// 
			this->B_CHA_WORK_STATE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHA_WORK_STATE->Location = System::Drawing::Point(12, 171);
			this->B_CHA_WORK_STATE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CHA_WORK_STATE->Name = L"B_CHA_WORK_STATE";
			this->B_CHA_WORK_STATE->ReadOnly = true;
			this->B_CHA_WORK_STATE->Size = System::Drawing::Size(45, 20);
			this->B_CHA_WORK_STATE->TabIndex = 137;
			this->B_CHA_WORK_STATE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// toolTipHR
			// 
			this->toolTipHR->IsBalloon = true;
			// 
			// toolTipVR
			// 
			this->toolTipVR->IsBalloon = true;
			// 
			// toolTipHL
			// 
			this->toolTipHL->IsBalloon = true;
			// 
			// toolTipVL
			// 
			this->toolTipVL->IsBalloon = true;
			// 
			// L_OMR_STATUS
			// 
			this->L_OMR_STATUS->AutoSize = true;
			this->L_OMR_STATUS->ForeColor = System::Drawing::Color::White;
			this->L_OMR_STATUS->Location = System::Drawing::Point(8, 47);
			this->L_OMR_STATUS->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_OMR_STATUS->Name = L"L_OMR_STATUS";
			this->L_OMR_STATUS->Size = System::Drawing::Size(32, 13);
			this->L_OMR_STATUS->TabIndex = 21;
			this->L_OMR_STATUS->Text = L"OMR";
			// 
			// L_MCU_STATUS
			// 
			this->L_MCU_STATUS->AutoSize = true;
			this->L_MCU_STATUS->ForeColor = System::Drawing::Color::White;
			this->L_MCU_STATUS->Location = System::Drawing::Point(8, 135);
			this->L_MCU_STATUS->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_MCU_STATUS->Name = L"L_MCU_STATUS";
			this->L_MCU_STATUS->Size = System::Drawing::Size(31, 13);
			this->L_MCU_STATUS->TabIndex = 25;
			this->L_MCU_STATUS->Text = L"MCU";
			// 
			// L_CHB_STATUS
			// 
			this->L_CHB_STATUS->AutoSize = true;
			this->L_CHB_STATUS->ForeColor = System::Drawing::Color::White;
			this->L_CHB_STATUS->Location = System::Drawing::Point(8, 113);
			this->L_CHB_STATUS->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_CHB_STATUS->Name = L"L_CHB_STATUS";
			this->L_CHB_STATUS->Size = System::Drawing::Size(29, 13);
			this->L_CHB_STATUS->TabIndex = 27;
			this->L_CHB_STATUS->Text = L"CHB";
			// 
			// L_CHA_STATUS
			// 
			this->L_CHA_STATUS->AutoSize = true;
			this->L_CHA_STATUS->ForeColor = System::Drawing::Color::White;
			this->L_CHA_STATUS->Location = System::Drawing::Point(8, 91);
			this->L_CHA_STATUS->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_CHA_STATUS->Name = L"L_CHA_STATUS";
			this->L_CHA_STATUS->Size = System::Drawing::Size(29, 13);
			this->L_CHA_STATUS->TabIndex = 29;
			this->L_CHA_STATUS->Text = L"CHA";
			// 
			// L_DET_STATUS
			// 
			this->L_DET_STATUS->AutoSize = true;
			this->L_DET_STATUS->ForeColor = System::Drawing::Color::White;
			this->L_DET_STATUS->Location = System::Drawing::Point(8, 69);
			this->L_DET_STATUS->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_DET_STATUS->Name = L"L_DET_STATUS";
			this->L_DET_STATUS->Size = System::Drawing::Size(29, 13);
			this->L_DET_STATUS->TabIndex = 31;
			this->L_DET_STATUS->Text = L"DET";
			// 
			// L_LMK01000
			// 
			this->L_LMK01000->AutoSize = true;
			this->L_LMK01000->ForeColor = System::Drawing::Color::White;
			this->L_LMK01000->Location = System::Drawing::Point(8, 310);
			this->L_LMK01000->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_LMK01000->Name = L"L_LMK01000";
			this->L_LMK01000->Size = System::Drawing::Size(59, 13);
			this->L_LMK01000->TabIndex = 35;
			this->L_LMK01000->Text = L"LMK01000";
			// 
			// L_LMK04828
			// 
			this->L_LMK04828->AutoSize = true;
			this->L_LMK04828->ForeColor = System::Drawing::Color::White;
			this->L_LMK04828->Location = System::Drawing::Point(8, 288);
			this->L_LMK04828->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_LMK04828->Name = L"L_LMK04828";
			this->L_LMK04828->Size = System::Drawing::Size(59, 13);
			this->L_LMK04828->TabIndex = 37;
			this->L_LMK04828->Text = L"LMK04828";
			// 
			// L_FPGA_B
			// 
			this->L_FPGA_B->AutoSize = true;
			this->L_FPGA_B->ForeColor = System::Drawing::Color::White;
			this->L_FPGA_B->Location = System::Drawing::Point(8, 266);
			this->L_FPGA_B->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_FPGA_B->Name = L"L_FPGA_B";
			this->L_FPGA_B->Size = System::Drawing::Size(48, 13);
			this->L_FPGA_B->TabIndex = 39;
			this->L_FPGA_B->Text = L"FPGA_B";
			// 
			// L_FPGA_A
			// 
			this->L_FPGA_A->AutoSize = true;
			this->L_FPGA_A->ForeColor = System::Drawing::Color::White;
			this->L_FPGA_A->Location = System::Drawing::Point(8, 244);
			this->L_FPGA_A->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_FPGA_A->Name = L"L_FPGA_A";
			this->L_FPGA_A->Size = System::Drawing::Size(48, 13);
			this->L_FPGA_A->TabIndex = 40;
			this->L_FPGA_A->Text = L"FPGA_A";
			// 
			// L_AD6655_B
			// 
			this->L_AD6655_B->AutoSize = true;
			this->L_AD6655_B->ForeColor = System::Drawing::Color::White;
			this->L_AD6655_B->Location = System::Drawing::Point(8, 222);
			this->L_AD6655_B->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_AD6655_B->Name = L"L_AD6655_B";
			this->L_AD6655_B->Size = System::Drawing::Size(59, 13);
			this->L_AD6655_B->TabIndex = 42;
			this->L_AD6655_B->Text = L"AD6655_B";
			// 
			// L_AD6655_A
			// 
			this->L_AD6655_A->AccessibleDescription = L"";
			this->L_AD6655_A->AutoSize = true;
			this->L_AD6655_A->ForeColor = System::Drawing::Color::White;
			this->L_AD6655_A->Location = System::Drawing::Point(8, 200);
			this->L_AD6655_A->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_AD6655_A->Name = L"L_AD6655_A";
			this->L_AD6655_A->Size = System::Drawing::Size(59, 13);
			this->L_AD6655_A->TabIndex = 43;
			this->L_AD6655_A->Text = L"AD6655_A";
			// 
			// B_DEBUG_COUNT
			// 
			this->B_DEBUG_COUNT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DEBUG_COUNT->Location = System::Drawing::Point(77, 22);
			this->B_DEBUG_COUNT->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DEBUG_COUNT->Name = L"B_DEBUG_COUNT";
			this->B_DEBUG_COUNT->ReadOnly = true;
			this->B_DEBUG_COUNT->Size = System::Drawing::Size(50, 20);
			this->B_DEBUG_COUNT->TabIndex = 17;
			this->B_DEBUG_COUNT->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_PERIPHERALS_LMK04828
			// 
			this->B_PERIPHERALS_LMK04828->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PERIPHERALS_LMK04828->Location = System::Drawing::Point(77, 286);
			this->B_PERIPHERALS_LMK04828->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PERIPHERALS_LMK04828->Name = L"B_PERIPHERALS_LMK04828";
			this->B_PERIPHERALS_LMK04828->ReadOnly = true;
			this->B_PERIPHERALS_LMK04828->Size = System::Drawing::Size(50, 20);
			this->B_PERIPHERALS_LMK04828->TabIndex = 38;
			// 
			// B_PERIPHERALS_LMK01000
			// 
			this->B_PERIPHERALS_LMK01000->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PERIPHERALS_LMK01000->Location = System::Drawing::Point(77, 308);
			this->B_PERIPHERALS_LMK01000->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PERIPHERALS_LMK01000->Name = L"B_PERIPHERALS_LMK01000";
			this->B_PERIPHERALS_LMK01000->ReadOnly = true;
			this->B_PERIPHERALS_LMK01000->Size = System::Drawing::Size(50, 20);
			this->B_PERIPHERALS_LMK01000->TabIndex = 41;
			// 
			// B_OMR_STATUS
			// 
			this->B_OMR_STATUS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_OMR_STATUS->Location = System::Drawing::Point(77, 44);
			this->B_OMR_STATUS->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_OMR_STATUS->Name = L"B_OMR_STATUS";
			this->B_OMR_STATUS->ReadOnly = true;
			this->B_OMR_STATUS->Size = System::Drawing::Size(50, 20);
			this->B_OMR_STATUS->TabIndex = 22;
			// 
			// L_UCD9222_DET_internal
			// 
			this->L_UCD9222_DET_internal->AutoSize = true;
			this->L_UCD9222_DET_internal->ForeColor = System::Drawing::Color::White;
			this->L_UCD9222_DET_internal->Location = System::Drawing::Point(8, 398);
			this->L_UCD9222_DET_internal->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_UCD9222_DET_internal->Name = L"L_UCD9222_DET_internal";
			this->L_UCD9222_DET_internal->Size = System::Drawing::Size(51, 13);
			this->L_UCD9222_DET_internal->TabIndex = 58;
			this->L_UCD9222_DET_internal->Text = L"Temp U1";
			// 
			// B_DET_STATUS
			// 
			this->B_DET_STATUS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_DET_STATUS->Location = System::Drawing::Point(77, 66);
			this->B_DET_STATUS->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_DET_STATUS->Name = L"B_DET_STATUS";
			this->B_DET_STATUS->ReadOnly = true;
			this->B_DET_STATUS->Size = System::Drawing::Size(50, 20);
			this->B_DET_STATUS->TabIndex = 24;
			// 
			// L_UCD9222_DET_external
			// 
			this->L_UCD9222_DET_external->AutoSize = true;
			this->L_UCD9222_DET_external->ForeColor = System::Drawing::Color::White;
			this->L_UCD9222_DET_external->Location = System::Drawing::Point(8, 442);
			this->L_UCD9222_DET_external->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_UCD9222_DET_external->Name = L"L_UCD9222_DET_external";
			this->L_UCD9222_DET_external->Size = System::Drawing::Size(50, 13);
			this->L_UCD9222_DET_external->TabIndex = 56;
			this->L_UCD9222_DET_external->Text = L"Temp B1";
			// 
			// B_CHA_STATUS
			// 
			this->B_CHA_STATUS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHA_STATUS->Location = System::Drawing::Point(77, 88);
			this->B_CHA_STATUS->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CHA_STATUS->Name = L"B_CHA_STATUS";
			this->B_CHA_STATUS->ReadOnly = true;
			this->B_CHA_STATUS->Size = System::Drawing::Size(50, 20);
			this->B_CHA_STATUS->TabIndex = 26;
			// 
			// L_UCD9222_CHA_external
			// 
			this->L_UCD9222_CHA_external->AutoSize = true;
			this->L_UCD9222_CHA_external->ForeColor = System::Drawing::Color::White;
			this->L_UCD9222_CHA_external->Location = System::Drawing::Point(8, 464);
			this->L_UCD9222_CHA_external->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_UCD9222_CHA_external->Name = L"L_UCD9222_CHA_external";
			this->L_UCD9222_CHA_external->Size = System::Drawing::Size(50, 13);
			this->L_UCD9222_CHA_external->TabIndex = 64;
			this->L_UCD9222_CHA_external->Text = L"Temp B2";
			// 
			// B_CHB_STATUS
			// 
			this->B_CHB_STATUS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_CHB_STATUS->Location = System::Drawing::Point(77, 110);
			this->B_CHB_STATUS->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_CHB_STATUS->Name = L"B_CHB_STATUS";
			this->B_CHB_STATUS->ReadOnly = true;
			this->B_CHB_STATUS->Size = System::Drawing::Size(50, 20);
			this->B_CHB_STATUS->TabIndex = 28;
			// 
			// B_MCU_STATUS
			// 
			this->B_MCU_STATUS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_MCU_STATUS->Location = System::Drawing::Point(77, 132);
			this->B_MCU_STATUS->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_MCU_STATUS->Name = L"B_MCU_STATUS";
			this->B_MCU_STATUS->ReadOnly = true;
			this->B_MCU_STATUS->Size = System::Drawing::Size(50, 20);
			this->B_MCU_STATUS->TabIndex = 30;
			// 
			// B_PERIPHERALS_AD6655_A
			// 
			this->B_PERIPHERALS_AD6655_A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PERIPHERALS_AD6655_A->Location = System::Drawing::Point(77, 198);
			this->B_PERIPHERALS_AD6655_A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PERIPHERALS_AD6655_A->Name = L"B_PERIPHERALS_AD6655_A";
			this->B_PERIPHERALS_AD6655_A->ReadOnly = true;
			this->B_PERIPHERALS_AD6655_A->Size = System::Drawing::Size(50, 20);
			this->B_PERIPHERALS_AD6655_A->TabIndex = 32;
			// 
			// B_PERIPHERALS_AD6655_B
			// 
			this->B_PERIPHERALS_AD6655_B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PERIPHERALS_AD6655_B->Location = System::Drawing::Point(77, 220);
			this->B_PERIPHERALS_AD6655_B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PERIPHERALS_AD6655_B->Name = L"B_PERIPHERALS_AD6655_B";
			this->B_PERIPHERALS_AD6655_B->ReadOnly = true;
			this->B_PERIPHERALS_AD6655_B->Size = System::Drawing::Size(50, 20);
			this->B_PERIPHERALS_AD6655_B->TabIndex = 33;
			// 
			// B_MCU_TEMP
			// 
			this->B_MCU_TEMP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_MCU_TEMP->Location = System::Drawing::Point(77, 374);
			this->B_MCU_TEMP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_MCU_TEMP->Name = L"B_MCU_TEMP";
			this->B_MCU_TEMP->ReadOnly = true;
			this->B_MCU_TEMP->Size = System::Drawing::Size(50, 20);
			this->B_MCU_TEMP->TabIndex = 52;
			this->B_MCU_TEMP->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_PERIPHERALS_FPGA_A
			// 
			this->B_PERIPHERALS_FPGA_A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PERIPHERALS_FPGA_A->Location = System::Drawing::Point(77, 242);
			this->B_PERIPHERALS_FPGA_A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PERIPHERALS_FPGA_A->Name = L"B_PERIPHERALS_FPGA_A";
			this->B_PERIPHERALS_FPGA_A->ReadOnly = true;
			this->B_PERIPHERALS_FPGA_A->Size = System::Drawing::Size(50, 20);
			this->B_PERIPHERALS_FPGA_A->TabIndex = 34;
			// 
			// B_PERIPHERALS_FPGA_B
			// 
			this->B_PERIPHERALS_FPGA_B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PERIPHERALS_FPGA_B->Location = System::Drawing::Point(77, 264);
			this->B_PERIPHERALS_FPGA_B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PERIPHERALS_FPGA_B->Name = L"B_PERIPHERALS_FPGA_B";
			this->B_PERIPHERALS_FPGA_B->ReadOnly = true;
			this->B_PERIPHERALS_FPGA_B->Size = System::Drawing::Size(50, 20);
			this->B_PERIPHERALS_FPGA_B->TabIndex = 36;
			// 
			// B_UCD9222_DET_temperature_internal
			// 
			this->B_UCD9222_DET_temperature_internal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_UCD9222_DET_temperature_internal->Location = System::Drawing::Point(77, 396);
			this->B_UCD9222_DET_temperature_internal->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_UCD9222_DET_temperature_internal->Name = L"B_UCD9222_DET_temperature_internal";
			this->B_UCD9222_DET_temperature_internal->ReadOnly = true;
			this->B_UCD9222_DET_temperature_internal->Size = System::Drawing::Size(50, 20);
			this->B_UCD9222_DET_temperature_internal->TabIndex = 55;
			this->B_UCD9222_DET_temperature_internal->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// L_Counter
			// 
			this->L_Counter->AutoSize = true;
			this->L_Counter->ForeColor = System::Drawing::Color::White;
			this->L_Counter->Location = System::Drawing::Point(8, 25);
			this->L_Counter->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_Counter->Name = L"L_Counter";
			this->L_Counter->Size = System::Drawing::Size(44, 13);
			this->L_Counter->TabIndex = 16;
			this->L_Counter->Text = L"Counter";
			// 
			// L_UCD9222_CHA_internal
			// 
			this->L_UCD9222_CHA_internal->AutoSize = true;
			this->L_UCD9222_CHA_internal->ForeColor = System::Drawing::Color::White;
			this->L_UCD9222_CHA_internal->Location = System::Drawing::Point(8, 420);
			this->L_UCD9222_CHA_internal->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_UCD9222_CHA_internal->Name = L"L_UCD9222_CHA_internal";
			this->L_UCD9222_CHA_internal->Size = System::Drawing::Size(51, 13);
			this->L_UCD9222_CHA_internal->TabIndex = 66;
			this->L_UCD9222_CHA_internal->Text = L"Temp U2";
			// 
			// B_UCD9222_CHA_temperature_internal
			// 
			this->B_UCD9222_CHA_temperature_internal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_UCD9222_CHA_temperature_internal->Location = System::Drawing::Point(77, 418);
			this->B_UCD9222_CHA_temperature_internal->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_UCD9222_CHA_temperature_internal->Name = L"B_UCD9222_CHA_temperature_internal";
			this->B_UCD9222_CHA_temperature_internal->ReadOnly = true;
			this->B_UCD9222_CHA_temperature_internal->Size = System::Drawing::Size(50, 20);
			this->B_UCD9222_CHA_temperature_internal->TabIndex = 59;
			this->B_UCD9222_CHA_temperature_internal->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// L_AD9910_B
			// 
			this->L_AD9910_B->AutoSize = true;
			this->L_AD9910_B->ForeColor = System::Drawing::Color::White;
			this->L_AD9910_B->Location = System::Drawing::Point(8, 354);
			this->L_AD9910_B->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_AD9910_B->Name = L"L_AD9910_B";
			this->L_AD9910_B->Size = System::Drawing::Size(59, 13);
			this->L_AD9910_B->TabIndex = 49;
			this->L_AD9910_B->Text = L"AD9910_B";
			// 
			// L_AD9910_A
			// 
			this->L_AD9910_A->AutoSize = true;
			this->L_AD9910_A->ForeColor = System::Drawing::Color::White;
			this->L_AD9910_A->Location = System::Drawing::Point(8, 332);
			this->L_AD9910_A->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_AD9910_A->Name = L"L_AD9910_A";
			this->L_AD9910_A->Size = System::Drawing::Size(59, 13);
			this->L_AD9910_A->TabIndex = 50;
			this->L_AD9910_A->Text = L"AD9910_A";
			// 
			// B_UCD9222_CHA_temperature_external
			// 
			this->B_UCD9222_CHA_temperature_external->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_UCD9222_CHA_temperature_external->Location = System::Drawing::Point(77, 462);
			this->B_UCD9222_CHA_temperature_external->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_UCD9222_CHA_temperature_external->Name = L"B_UCD9222_CHA_temperature_external";
			this->B_UCD9222_CHA_temperature_external->ReadOnly = true;
			this->B_UCD9222_CHA_temperature_external->Size = System::Drawing::Size(50, 20);
			this->B_UCD9222_CHA_temperature_external->TabIndex = 61;
			this->B_UCD9222_CHA_temperature_external->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_PERIPHERALS_AD9910_A
			// 
			this->B_PERIPHERALS_AD9910_A->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PERIPHERALS_AD9910_A->Location = System::Drawing::Point(77, 330);
			this->B_PERIPHERALS_AD9910_A->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PERIPHERALS_AD9910_A->Name = L"B_PERIPHERALS_AD9910_A";
			this->B_PERIPHERALS_AD9910_A->ReadOnly = true;
			this->B_PERIPHERALS_AD9910_A->Size = System::Drawing::Size(50, 20);
			this->B_PERIPHERALS_AD9910_A->TabIndex = 44;
			// 
			// B_PERIPHERALS_AD9910_B
			// 
			this->B_PERIPHERALS_AD9910_B->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_PERIPHERALS_AD9910_B->Location = System::Drawing::Point(77, 352);
			this->B_PERIPHERALS_AD9910_B->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PERIPHERALS_AD9910_B->Name = L"B_PERIPHERALS_AD9910_B";
			this->B_PERIPHERALS_AD9910_B->ReadOnly = true;
			this->B_PERIPHERALS_AD9910_B->Size = System::Drawing::Size(50, 20);
			this->B_PERIPHERALS_AD9910_B->TabIndex = 46;
			// 
			// L_MCU_TEMP
			// 
			this->L_MCU_TEMP->AutoSize = true;
			this->L_MCU_TEMP->ForeColor = System::Drawing::Color::White;
			this->L_MCU_TEMP->Location = System::Drawing::Point(8, 376);
			this->L_MCU_TEMP->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_MCU_TEMP->Name = L"L_MCU_TEMP";
			this->L_MCU_TEMP->Size = System::Drawing::Size(61, 13);
			this->L_MCU_TEMP->TabIndex = 51;
			this->L_MCU_TEMP->Text = L"Temp MCU";
			// 
			// B_GROUP_STATUS
			// 
			this->B_GROUP_STATUS->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->B_GROUP_STATUS->Controls->Add(this->L_RF_MCU_TEMP);
			this->B_GROUP_STATUS->Controls->Add(this->L_MCU_TEMP);
			this->B_GROUP_STATUS->Controls->Add(this->B_RF_MCU_TEMP);
			this->B_GROUP_STATUS->Controls->Add(this->L_RF_BOARD_TEMP);
			this->B_GROUP_STATUS->Controls->Add(this->B_RF_TEMP);
			this->B_GROUP_STATUS->Controls->Add(this->B_HMC830_PLL);
			this->B_GROUP_STATUS->Controls->Add(this->L_HMC830_PLL);
			this->B_GROUP_STATUS->Controls->Add(this->B_PERIPHERALS_AD9910_B);
			this->B_GROUP_STATUS->Controls->Add(this->B_PERIPHERALS_AD9910_A);
			this->B_GROUP_STATUS->Controls->Add(this->B_UCD9222_CHA_temperature_external);
			this->B_GROUP_STATUS->Controls->Add(this->L_AD9910_A);
			this->B_GROUP_STATUS->Controls->Add(this->L_AD9910_B);
			this->B_GROUP_STATUS->Controls->Add(this->B_UCD9222_CHA_temperature_internal);
			this->B_GROUP_STATUS->Controls->Add(this->L_UCD9222_CHA_internal);
			this->B_GROUP_STATUS->Controls->Add(this->L_Counter);
			this->B_GROUP_STATUS->Controls->Add(this->B_RF_MCU_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->L_RF_MCU_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->B_UCD9222_DET_temperature_external);
			this->B_GROUP_STATUS->Controls->Add(this->B_UCD9222_DET_temperature_internal);
			this->B_GROUP_STATUS->Controls->Add(this->B_PERIPHERALS_FPGA_B);
			this->B_GROUP_STATUS->Controls->Add(this->B_PERIPHERALS_FPGA_A);
			this->B_GROUP_STATUS->Controls->Add(this->B_MCU_TEMP);
			this->B_GROUP_STATUS->Controls->Add(this->B_PERIPHERALS_AD6655_B);
			this->B_GROUP_STATUS->Controls->Add(this->B_PERIPHERALS_AD6655_A);
			this->B_GROUP_STATUS->Controls->Add(this->B_MCU_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->B_CHB_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->L_UCD9222_CHA_external);
			this->B_GROUP_STATUS->Controls->Add(this->B_CHA_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->L_UCD9222_DET_external);
			this->B_GROUP_STATUS->Controls->Add(this->B_DET_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->L_UCD9222_DET_internal);
			this->B_GROUP_STATUS->Controls->Add(this->B_OMR_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->B_PERIPHERALS_LMK01000);
			this->B_GROUP_STATUS->Controls->Add(this->B_PERIPHERALS_LMK04828);
			this->B_GROUP_STATUS->Controls->Add(this->B_DEBUG_COUNT);
			this->B_GROUP_STATUS->Controls->Add(this->L_AD6655_A);
			this->B_GROUP_STATUS->Controls->Add(this->L_AD6655_B);
			this->B_GROUP_STATUS->Controls->Add(this->L_FPGA_A);
			this->B_GROUP_STATUS->Controls->Add(this->L_FPGA_B);
			this->B_GROUP_STATUS->Controls->Add(this->L_LMK04828);
			this->B_GROUP_STATUS->Controls->Add(this->L_LMK01000);
			this->B_GROUP_STATUS->Controls->Add(this->L_DET_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->L_CHA_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->L_CHB_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->L_MCU_STATUS);
			this->B_GROUP_STATUS->Controls->Add(this->L_OMR_STATUS);
			this->B_GROUP_STATUS->ForeColor = System::Drawing::Color::White;
			this->B_GROUP_STATUS->Location = System::Drawing::Point(141, 2);
			this->B_GROUP_STATUS->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_STATUS->Name = L"B_GROUP_STATUS";
			this->B_GROUP_STATUS->Padding = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_GROUP_STATUS->Size = System::Drawing::Size(134, 556);
			this->B_GROUP_STATUS->TabIndex = 10;
			this->B_GROUP_STATUS->TabStop = false;
			this->B_GROUP_STATUS->Text = L"Status";
			// 
			// B_RF_MCU_STATUS
			// 
			this->B_RF_MCU_STATUS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_RF_MCU_STATUS->Location = System::Drawing::Point(77, 154);
			this->B_RF_MCU_STATUS->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RF_MCU_STATUS->Name = L"B_RF_MCU_STATUS";
			this->B_RF_MCU_STATUS->ReadOnly = true;
			this->B_RF_MCU_STATUS->Size = System::Drawing::Size(50, 20);
			this->B_RF_MCU_STATUS->TabIndex = 68;
			// 
			// L_RF_MCU_STATUS
			// 
			this->L_RF_MCU_STATUS->AutoSize = true;
			this->L_RF_MCU_STATUS->ForeColor = System::Drawing::Color::White;
			this->L_RF_MCU_STATUS->Location = System::Drawing::Point(8, 157);
			this->L_RF_MCU_STATUS->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->L_RF_MCU_STATUS->Name = L"L_RF_MCU_STATUS";
			this->L_RF_MCU_STATUS->Size = System::Drawing::Size(48, 13);
			this->L_RF_MCU_STATUS->TabIndex = 67;
			this->L_RF_MCU_STATUS->Text = L"RF MCU";
			// 
			// B_UCD9222_DET_temperature_external
			// 
			this->B_UCD9222_DET_temperature_external->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->B_UCD9222_DET_temperature_external->Location = System::Drawing::Point(77, 440);
			this->B_UCD9222_DET_temperature_external->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_UCD9222_DET_temperature_external->Name = L"B_UCD9222_DET_temperature_external";
			this->B_UCD9222_DET_temperature_external->ReadOnly = true;
			this->B_UCD9222_DET_temperature_external->Size = System::Drawing::Size(50, 20);
			this->B_UCD9222_DET_temperature_external->TabIndex = 57;
			this->B_UCD9222_DET_temperature_external->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(836, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(288, 690);
			this->tabControl1->TabIndex = 204;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->tabPage1->Controls->Add(this->B_GROUP_SENSOR);
			this->tabPage1->Controls->Add(this->B_GROUP_ALGORITHMS);
			this->tabPage1->Controls->Add(this->B_GROUP_RF);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(280, 664);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Operational";
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(91)), static_cast<System::Int32>(static_cast<System::Byte>(91)),
				static_cast<System::Int32>(static_cast<System::Byte>(86)));
			this->tabPage2->Controls->Add(this->B_GROUP_STATE_MACHINES);
			this->tabPage2->Controls->Add(this->B_GROUP_STATUS);
			this->tabPage2->Controls->Add(this->B_GROUP_FREES);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(280, 664);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Debug";
			// 
			// B_Navigation_Status
			// 
			this->B_Navigation_Status->BackColor = System::Drawing::Color::Red;
			this->B_Navigation_Status->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->B_Navigation_Status->Location = System::Drawing::Point(154, 639);
			this->B_Navigation_Status->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_Navigation_Status->Name = L"B_Navigation_Status";
			this->B_Navigation_Status->Size = System::Drawing::Size(61, 13);
			this->B_Navigation_Status->TabIndex = 206;
			this->B_Navigation_Status->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label244
			// 
			this->label244->AutoSize = true;
			this->label244->ForeColor = System::Drawing::Color::Black;
			this->label244->Location = System::Drawing::Point(157, 625);
			this->label244->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label244->Name = L"label244";
			this->label244->Size = System::Drawing::Size(61, 13);
			this->label244->TabIndex = 205;
			this->label244->Text = L"Navigation:";
			// 
			// B_BROWSE_DIR
			// 
			this->B_BROWSE_DIR->RootFolder = System::Environment::SpecialFolder::MyDocuments;
			// 
			// B_SelectLogFile_Of_Rotator
			// 
			this->B_SelectLogFile_Of_Rotator->FileName = L"Select LOG file of rotator";
			this->B_SelectLogFile_Of_Rotator->Filter = L"Log files (*.bin)|*.bin|All files (*.*)|*.*";
			this->B_SelectLogFile_Of_Rotator->Title = L"Select LOG file of rotator";
			// 
			// B_MAX_ERROR_RANGE
			// 
			this->B_MAX_ERROR_RANGE->Location = System::Drawing::Point(116, 275);
			this->B_MAX_ERROR_RANGE->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->B_MAX_ERROR_RANGE->Name = L"B_MAX_ERROR_RANGE";
			this->B_MAX_ERROR_RANGE->Size = System::Drawing::Size(76, 20);
			this->B_MAX_ERROR_RANGE->TabIndex = 178;
			this->B_MAX_ERROR_RANGE->ValueChanged += gcnew System::EventHandler(this, &MyForm::B_MAX_ERROR_RANGE_ValueChanged);
			// 
			// label270
			// 
			this->label270->AutoSize = true;
			this->label270->Location = System::Drawing::Point(17, 277);
			this->label270->Name = L"label270";
			this->label270->Size = System::Drawing::Size(98, 13);
			this->label270->TabIndex = 179;
			this->label270->Text = L"Max error range [m]";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkGray;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1122, 692);
			this->Controls->Add(this->B_Navigation_Status);
			this->Controls->Add(this->label251);
			this->Controls->Add(this->label244);
			this->Controls->Add(this->B_SCREEN_WIDTH_OF_VIEWER);
			this->Controls->Add(this->label263);
			this->Controls->Add(this->label50);
			this->Controls->Add(this->B_message);
			this->Controls->Add(this->B_System_Health_Status);
			this->Controls->Add(this->label71);
			this->Controls->Add(this->G_STOP_WORK);
			this->Controls->Add(this->B_Ethernet_Status);
			this->Controls->Add(this->W_START_WORK_CIRC);
			this->Controls->Add(this->label54);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->B_tabControl);
			this->Controls->Add(this->W_DATA_RECORDING);
			this->ForeColor = System::Drawing::Color::Black;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->MaximumSize = System::Drawing::Size(1138, 731);
			this->MinimumSize = System::Drawing::Size(1138, 726);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"ARC1 monitor V3.0";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->B_GROUP_FREES->ResumeLayout(false);
			this->B_GROUP_FREES->PerformLayout();
			this->B_GROUP_SENSOR->ResumeLayout(false);
			this->B_GROUP_SENSOR->PerformLayout();
			this->B_tabControl->ResumeLayout(false);
			this->MAP_VIEW->ResumeLayout(false);
			this->MAP_VIEW->PerformLayout();
			this->B_VISIBLE_OBSTACLES->ResumeLayout(false);
			this->B_VISIBLE_OBSTACLES->PerformLayout();
			this->B_MAP_PANEL->ResumeLayout(false);
			this->B_MAP_PANEL->PerformLayout();
			this->REAL_TIME_TOOL_STRIP->ResumeLayout(false);
			this->REAL_TIME_TOOL_STRIP->PerformLayout();
			this->RDM_VIEW->ResumeLayout(false);
			this->RDM_VIEW->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_Color_Map))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RDM_V_R))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RDM_V_L))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RDM_H_R))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RDM_H_L))->EndInit();
			this->SINGLE_RDM_VIEW->ResumeLayout(false);
			this->SINGLE_RDM_VIEW->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_RDM_COLOR_MAP))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_RDM))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_MAP_chart))->EndInit();
			this->RADAR_VIEW->ResumeLayout(false);
			this->RADAR_VIEW->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox86->ResumeLayout(false);
			this->groupBox86->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_POL_Target_selector))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Polarization_Box))->EndInit();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_RADAR_PLOT))->EndInit();
			this->Flash->ResumeLayout(false);
			this->Flash->PerformLayout();
			this->groupBox11->ResumeLayout(false);
			this->groupBox11->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Target_detection_2nd_threshold))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_MINIMUM_RANGE_METER))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_AGC_threshold))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_RANGE_DECIMATION))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Target_detection_1st_threshold))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_RANGE_meter))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_MAX_VELOCITY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_OFFSET_sample))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Number_of_buffers))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_PROBE_TEST_gain))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_PROBE_TEST_profile))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_SYSTEM_ID))->EndInit();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->panel13->ResumeLayout(false);
			this->panel13->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_RX4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Profile_AD9910B))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Profile_AD9910A))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_FIFO_length))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_chip_length_AD9910A))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_Buffer_length))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_RX3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_chip_length_AD9910B))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_IO_UPDATE_rate))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_RX2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_AD9910_Set_aux_dac_B))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_AD9910_Set_aux_dac_A))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_RX1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_TX3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_TX2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_ATTN_TX1))->EndInit();
			this->groupBox10->ResumeLayout(false);
			this->groupBox10->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_CALIBRATOR_TGT_START))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_CALIBRATOR_TGT_END))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_PROBE_CALIBRATE_TGT_START))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->F_PROBE_CALIBRATE_TGT_END))->EndInit();
			this->Debug->ResumeLayout(false);
			this->Debug->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_PROBE_TEST_PLOT))->EndInit();
			this->Mainenance->ResumeLayout(false);
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->LAB_Experiments->ResumeLayout(false);
			this->B_CALIBRATOR_DATA->ResumeLayout(false);
			this->B_CALIBRATOR_DATA->PerformLayout();
			this->B_ROTATOR_DATA->ResumeLayout(false);
			this->B_ROTATOR_DATA->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_LAB_ELEVATION))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_LAB_AZIMUTH))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCREEN_WIDTH_OF_VIEWER))->EndInit();
			this->A_SCOPE_VIEW->ResumeLayout(false);
			this->A_SCOPE_VIEW->PerformLayout();
			this->panel7->ResumeLayout(false);
			this->panel7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SATURATION_V_LEFT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SATURATION_V_RIGHT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SATURATION_H_RIGHT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SATURATION_H_LEFT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_V_RIGHT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_V_LEFT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_H_RIGHT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_H_LEFT))->EndInit();
			this->B_GROUP_RF->ResumeLayout(false);
			this->B_GROUP_RF->PerformLayout();
			this->B_GROUP_ALGORITHMS->ResumeLayout(false);
			this->B_GROUP_ALGORITHMS->PerformLayout();
			this->B_GROUP_STATE_MACHINES->ResumeLayout(false);
			this->B_GROUP_STATE_MACHINES->PerformLayout();
			this->B_GROUP_STATUS->ResumeLayout(false);
			this->B_GROUP_STATUS->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_MAX_ERROR_RANGE))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		#pragma endregion

		#pragma region To Fix
		private:
		C_Radar_Viewer					Radar_Viewer;
		C_GUI_Status^					GUI_Status;
		C_SYSTEM_status^				System_Status;

		C_Lab_Calibrator				Lab_Calibrator;
		T_TARGETS_data*					TARGETS_data;
		bool							target_updated;
		
		C_Lab_ROT2PROG					Lab_ROT2PROG;
		bool							my_Ignore_Evens;
		//-----------------------------------
		//	The Real Time Thread of the class according to UML
		//-----------------------------------
		Real_Time_Thread				real_time_thread;
		T_BUL_config*					BUL_config;
	
		double							correction1I;
		double*							RDM_P;
		int								Temp_valid;

		String^							Path;
		Bitmap^							image;
		//--------------end------------------
	/*	Thread^							thread_PC_messaging;
		Thread^							thread_PC_recording;	*/

		fstream							*data_recording_file_handle;
		int								range_correction;

		int								local_authentication;
		int								local_data_authentication;
		int								timer_counter = TIMER_INTERVAL * 2;
		
		float							margin = (float)0.005;

		clock_t							for_debug_timer_1;
		clock_t							for_debug_timer_2;
		clock_t							for_debug_timer_3;

		clock_t							for_debug_timer_4;
		clock_t							for_debug_timer_5;
		clock_t							for_debug_timer_6;

		//clock_t							for_debug_timer_of_plot_radar_to_screen;
		//-----------------------------------
		//  Matlab variables
		//-----------------------------------
		Engine							*Matlab_engine;
		// -----------------------------------
		//  Display
		//------------------------------------
		Scope^							scope;
		// -----------------------------------
		//  Methods
		//------------------------------------
		private:
		void		My_Message(String^ message_string);
		//String^		GOOD_FAULT(UINT32_T integerValue);
		String^		GOOD_FAULT(uint32_t integerValue);
		Color		BUL_COLOR(int BUL_status_message);
		//Color		BG_COLOR(UINT32_T integerValue);
		Color		BG_COLOR(uint32_t integerValue);
		String^		int2BULStatusMessages(int BUL_status_message);

		void		MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		void		B_MAIN_config_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_SENSOR_CONFIG_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_OMR_Browse_Click(System::Object^  sender, System::EventArgs^  e);
		void        B_RESET_ARC_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_DET_Browse_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_CHAB_Browse_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_MCU_Browse_Click(System::Object^  sender, System::EventArgs^  e);

		void		G_Upload_OMR_Click(System::Object^  sender, System::EventArgs^  e);
		void		G_Upload_DET_Click(System::Object^  sender, System::EventArgs^  e);
		void		G_Upload_CHAB_Click(System::Object^  sender, System::EventArgs^  e);
		void		G_Upload_MCU_Click(System::Object^  sender, System::EventArgs^  e);

		void		B_LOG_FOLDER_BROWSE_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_SNAPSHOT_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_PROBE_TEST_Click(System::Object^  sender, System::EventArgs^  e);

		void		B_CALIBRATOR_CALIBRATE_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_PROBE_CALIBRATE_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_PROBE_RESET_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_CALIBRATOR_RESET_Click(System::Object^  sender, System::EventArgs^  e);

		void		W_RECORDING_START_Click(System::Object^  sender, System::EventArgs^  e);
		void		G_START_WORK_CIRC_Click(System::Object^  sender, System::EventArgs^  e);
		void		G_START_WORK_HV_Click(System::Object^  sender, System::EventArgs^  e);
		void		G_STOP_WORK_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_FLASH_WRITE_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_FLASH_READ_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_FLASH_WRITE_TO_FILE_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_FLASH_READ_FROM_FILE_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_FLASH_RETRIVE_Click(System::Object^  sender, System::EventArgs^  e);
		void		F_RF2_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		// ------------------------------------------------------------------------
		//				The Real Time Thread of the class according to UML
		//-------------------------------------------------------------------------
		void		timer_DSP_messages_Tick(System::Object^  sender, System::EventArgs^  e);

		void		Update_Sensor_Controls();
		void		Update_Debug_Tab_Controls();
		void		Update_Work_Tab_Controls();
		void		Update_Maintenance_Tab_Controls();
		void		Update_Status_Controls();
		void		Update_Status_ARC_Controls();
		void		Update_Status_TxRx_Controls(T_TxRx_control* TxRx_control);	
		void		Update_BUL_Controls();

		void		Etherent_status_state_machine();
		void		System_Health_status();

		void		Targets_Update_Controls(T_TARGETS_data* pTARGETS_data);
		void		Save_experiment_data_file(char*	directory_path);
		void		Open_aux_view(E_LEGEND_MODE legend_mode);

		void		plot_A_SCOPE(double *Samples_buffer, int buffer_size_doubles, int start_range, int end_range, int step_range);
		void		Plot_RDM(Byte* pBuffer_short, T_TARGETS_data* pTARGETS_data);
		void		Targets_Sort_by_Reliability(T_TARGETS_data* pTARGETS_data);
		void		Plot_probe_test(int16_t* pbuffer);

		int			Data_recording_start();
		int			Data_recording_stop();
		
		int			create_experiment_folder(char* experiment_path);
		//int			Process_Snapshot(int16_t* pBuffer_short);
		int			Process_Snapshot();
		int			Process_obstacles_map(char* pBuffer);

		void		Flash_Display_fields_to_Screen();
		void		Flash_TxRx_fields_to_Screen(T_TxRx_control* TxRx_control);

		dp_cplx		IQ_correction(int16_t* I1, int16_t* Q1, dp_cplx correction);
		dp_cplx		complex_division(dp_cplx x, dp_cplx y);

		private: System::Void Flash_Click(System::Object^  sender, System::EventArgs^  e) {}
		private: System::Void lbox_select_RDM_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {}

		 void		B_MAP_PANEL_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
		#pragma endregion 

		#pragma region GUI Methods
		private:
		//-----------------------------------------------------------
		//			DEBUG controls
		//-----------------------------------------------------------
		void		B_SNAPSHOT_TYPE_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_MATLAB_script_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_LOG_FOLDER_TextChanged(System::Object^  sender, System::EventArgs^  e);
		//-----------------------------------------------------------
		//			FLASH controls
		//-----------------------------------------------------------
		void		F_IF_SELECT_TX1_A_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_IF_SELECT_TX2_A_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_IF_SELECT_TX3_A_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_IF_SELECT_PROBE_A_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_TX1_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_TX2_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_TX3_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_PROBE_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_TX_LO_TR_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_PROBE_SELECT_ANT_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_IO_UPDATE_ON_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_ATTN_TX1_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_ATTN_TX2_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_ATTN_TX3_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_ATTN_RX1_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_ATTN_RX2_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_ATTN_RX3_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_ATTN_RX4_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_Profile_AD9910A_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_Profile_AD9910B_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_chip_length_AD9910A_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_chip_length_AD9910B_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_AD9910_Set_aux_dac_A_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_AD9910_Set_aux_dac_B_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_IO_UPDATE_rate_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_Number_of_buffers_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_AGC_threshold_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_Buffer_length_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_FIFO_length_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_OFFSET_sample_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_RANGE_meter_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_SYSTEM_ID_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_PROBE_CALIBRATE_TGT_START_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_PROBE_CALIBRATE_TGT_END_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_CALIBRATOR_TGT_START_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_CALIBRATOR_TGT_END_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_PROBE_TEST_profile_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_PROBE_TEST_gain_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_TxRx_control_MODE_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		void		Target_detection_1st_threshold_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		Target_detection_2nd_threshold_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_MAX_VELOCITY_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_RANGE_DECIMATION_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		F_MINIMUM_RANGE_METER_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		Free_Flight_MAP_Click(System::Object^  sender, System::EventArgs^  e);
		//-----------------------------------------------------------
		//			MAINTENANCE controls
		//-----------------------------------------------------------
		void		B_ResetAfterUpload_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_Out_OMR_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_Out_DET_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_Out_CHAB_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_Out_MCU_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_Out_RF_MCU_TextChanged(System::Object^  sender, System::EventArgs^  e);
		//-----------------------------------------------------------
		//			WORK controls
		//-----------------------------------------------------------
		void		B_RDM_H_R_MouseClick(System::Object^  sender, System::EventArgs^  e);
		void		B_RDM_V_R_MouseClick(System::Object^  sender, System::EventArgs^  e);
		void		B_RDM_H_L_MouseClick(System::Object^  sender, System::EventArgs^  e);
		void		B_RDM_V_L_MouseClick(System::Object^  sender, System::EventArgs^  e);
		void		B_tabControl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_AUX_VIEW_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		//-----------------------------------------------------------
		//			MAP Tab control Function
		//-----------------------------------------------------------
		int			mouse_x, mouse_y;
		//
		// Functions for Mouse
		//
		void		B_MAP_PANEL_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^ e);
		void		B_MAP_PANEL_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^ e);
		void		B_MAP_PANEL_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		//
		// Functions for Keyboard
		//
		void		B_MAP_PANEL_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^ e);

		void		B_SCREEN_WIDTH_OF_VIEWER_Scroll(System::Object^ sender, System::EventArgs^ e);
		void		B_ZOOM_IN_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_ZOOM_OUT_Click(System::Object^  sender, System::EventArgs^  e);
		//
		//	Load Map
		//
		void		B_LOAD_MAP_Click(System::Object^  sender, System::EventArgs^  e);
		//
		//	Review Flight
		//
		void		B_RE_FLIGHT_Click(System::Object^  sender, System::EventArgs^  e);
		//
		//	Detection Algorithm
		//
		void		B_MAX_ERROR_RANGE_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_WIRE_SEGMENT_LENGTH_METER_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		//
		// Visible Obstacles
		//
		void		B_DETECTIONS_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_TRAJECTORIES_CheckedChanged(System::Object^  sender, System::EventArgs^  e);


		void		B_REAL_TIME_TOOL_EDIT_Click(System::Object^  sender, System::EventArgs^  e);
		//-----------------------------------------------------------
		//			LAB Experiments Tab control Function
		//-----------------------------------------------------------
		//
		//	Calibrator function
		//		
		void		B_LAB_CALIBRATOR_BROWSE_DATA_FILE_TO_SAVE_Click(System::Object^  sender, System::EventArgs^  e);
		void		B_LAB_CALIBRATOR_START_Click(System::Object^  sender, System::EventArgs^  e);
		//
		//	Rotator function
		//
		void		B_LAB_ROTATOR_BROWSE_DATA_FILE_TO_SAVE_Click(System::Object^  sender, System::EventArgs^  e);

		void		B_LAB_AZIMUTH_MIN_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_LAB_ELEVATION_MIN_ValueChanged(System::Object^  sender, System::EventArgs^  e); 
		void		B_ROTATOR_TIMER_Tick(System::Object^  sender, System::EventArgs^  e);
		void		B_ROTATOR_COM_PORT_VisibleChanged(System::Object^  sender, System::EventArgs^  e);
		void		B_ROTATOR_COM_PORT_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		#pragma endregion
};
}