#pragma once
//---------------------------------------------------------
//
// MATLAB Engine (call MATLAB functions from C++):
//  http://www.mathworks.com/help/matlab/matlab_external/introducing-matlab-engine.html
// COmplile MATLAB engine application in the Microsoft Visual Studio
//	http://www.mathworks.com/matlabcentral/answers/100603-how-can-i-compile-a-matlab-engine-application-using-microsoft-visual-studio-9-0-or-10-0
//---------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <winsock2.h>			// Note, has to be *before* <msclr/...>. Alon. 7.10.2014
#include <Ws2tcpip.h>
#include <sstream>
#include <list>
#include "T_SENSOR_data.h"
#include "engine.h"
#include <stdint.h>

using	std::fstream;
using	std::ios;
using	std::string;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
//-----------------------------------------
//		MISC. parameters
//-----------------------------------------
#define GOOD						0
#define FAULT						1
#define MAX_STRING_LENGTH			512
#define MAX_RETRY_NUMBER			200	//100 Eran 16.7.15
//-----------------------------------------
//		DATA
//-----------------------------------------
#define TIME_RECORD_LENGTH			1024
#define	WORK_DATA_NUM_OF_RECORDS	4
#define	WORK_DATA_SIZE				TIME_RECORD_LENGTH * sizeof(double) * WORK_DATA_NUM_OF_RECORDS
#define PI							3.14159265358979323846
#define FFTC_ZERO_PADDING_MUL		2
//-----------------------------------------
//		FILES & FOLDERS
//-----------------------------------------
#define	FLASH_VALUES_FILE_NAME		"FLASH_VALUES.bin"
#define	BUL_IMAGE_FILE_NAME			"ARC1"			// remeber to change in the ARC1_CHAB.RMD file and ARC1_CHAB.map
#define	BUL_IMAGE_FILE_NAME_CORE0	"ARC1_CORE0"
#define	BUL_IMAGE_FILE_NAME_CORE1	"ARC1_CORE1"
#define	BUL_IMAGE_FILE_NAME_CORE2	"ARC1_CORE2"
#define	BUL_IMAGE_FILE_NAME_CORE3	"ARC1_CORE3"
#define	BUL_IMAGE_FILE_NAME_CORE4	"ARC1_CORE4"
#define	BUL_IMAGE_FILE_NAME_CORE5	"ARC1_CORE5"
#define	BUL_IMAGE_FILE_NAME_CORE6	"ARC1_CORE6"
#define	BUL_IMAGE_FILE_NAME_CORE7	"ARC1_CORE7"
#define	BUL_IMAGE_FILE_NAME_MCU		"ARC1_MCU_V2\\Debug\\ARC1_MCU_V2.txt"
#define BUL_NOR_FILES_PATH			"..\\NOR_FILES"
#define BUL_MAD_FILES_CHAB_PATH		"..\\MAD_FILES_CHAB"
#define BUL_MAD_FILES_DET_PATH		"..\\MAD_FILES_DET"
#define BUL_MAD_FILES_OMR_PATH		"..\\MAD_FILES_OMR"
#define BUL_NAND_FILES_PATH			"..\\NAND_FILES"
#define	MATLAB_SCRIPTS_NAME			"MATLAB_SCRIPTS.txt"
#define	MATLAB_SCRIPTS_PATH			"..\\MATLAB_SCRIPTS"
#define	DATA_RECORDING_FILE			"data_recording.bin"
#define	SNAPSHOT_SAMPLES_FILE		"snapshot_samples.bin"
#define	A_SCOPE_SAMPLES_FILE		"A_scope_samples.bin"
#define	EXPERIMENT_DATA_FILE		"LOG.txt"
#define EXPERIMENT_NUMBER_FILE		"expNum.txt"
//-----------------------------------------
//		Ethernet
//-----------------------------------------
#define ETHERNET_BUFFER_LENGTH		1024
#define ETHERNET_BUFFER_LENGTH		1024
#define ETHERNET_IP_ADDRESS			"192.168.2.100"
#define ETHERNET_MESSAGING_PORT		7
#define ETHERNET_RECORDING_PORT		8
#define	ETHERNET_TIME_OUT			10000					//[Micro-Seconds]
#define	ETHERNET_PING				12345

//-----------------------------------------
//		TIMER
//-----------------------------------------
#define	TIMER_INTERVAL				50		// [mSec] ( Eran 10.5.15 - changed from 500 )
//-----------------------------------------
//		Display A-Scope
//-----------------------------------------
#define	A_SCOPE_MIN_RANGE			130		// [m]
#define	A_SCOPE_MAX_RANGE			464		// [m]
#define	A_SCOPE_STEP_RANGE			3		// [m]
#define	METERS_PER_SAMPLE			3

typedef enum
{
	LEGEND_OFF = 0,
	LEGEND_CIRCULAR,
	LEGEND_HV
}	E_LEGEND_MODE;
//-----------------------------------------
//		Display RADAR view
//-----------------------------------------
#define MAX_NUMBER_OF_TARGETS		100
#define WIRE_FOV_DEGREES			40
#define SERIES_NAME					"Obstacle_"
//-----------------------------------------
//		E_POL_MODE
//-----------------------------------------
typedef enum 
{ 
	TX_OFF = 0, 
	POL_VERTICAL, 
	POL_HORIZONTAL, 
	POL_LINEAR, 
	POL_CIRCULAR 
} E_POL_MODE;

