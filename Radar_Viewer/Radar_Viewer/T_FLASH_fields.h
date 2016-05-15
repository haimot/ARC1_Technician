#ifndef T_FLASH_FIELDS_H
#define T_FLASH_FIELDS_H

#include <stdint.h>
#include "T_TxRx_control.h"
#include "T_TGT_calibrate.h"
#include "T_PROBE_test.h"
#include "T_DET_algorithms.h"

//-----------------------------------------
//		Enum:		E_TxRx_MODE
//-----------------------------------------
typedef enum
{
	TxRx_MODE_WORK = 0,
	TxRx_MODE_PROBE,
	TxRx_MODE_CALIBRATOR
}	E_TxRx_MODE;
////-----------------------------------------
////		Enum:		E_FLASH_fields
////-----------------------------------------
//typedef enum
//{
//	//-----------------------------------------------------------
//	//			TxRx_control	controls
//	//-----------------------------------------------------------
//	PROFILE_AD9910A	= 1,						
//	PROFILE_AD9910B,							
//	CHIP_LENGTH_AD9910A,						
//	CHIP_LENGTH_AD9910B,						
//	SELECT_TX1,								
//	SELECT_TX2,								
//	SELECT_TX3,								
//    SELECT_PROBE,							
//    IO_UPDATE_rate,							
//    TX1_ON,									
//    TX2_ON,									
//    TX3_ON,									
//    PROBE_ON,								
//    TX_LO_TR,							
//	ANT_SAMPLE_SELECT,					
//    ATTN_TX1,								
//    ATTN_TX2,								
//    ATTN_TX3,								
//    ATTN_RX1,								
//    ATTN_RX2,								
//    ATTN_RX3,								
//    ATTN_RX4,								
//	AD9910_SET_AUX_DAC_A,					
//	AD9910_SET_AUX_DAC_B,					
//	BUFFER_LENGTH,							
//	FIFO_LENGTH,							
//	IO_UPDATE_ON,						
//	//-----------------------------------------------------------
//	//			DET_algorithms	controls
//	//-----------------------------------------------------------
//	OFFSET_SAMPLES,						
//	RANGE_SAMPLES,							
//	TARGET_DETECTION_1ST_THRESHOLD,			
//	TARGET_DETECTION_2ST_THRESHOLD,		
//	Range_DECIMATION,						
//	MINIMUM_RANGE_METER,						
//	//-----------------------------------------------------------
//	//			TGT_calibrate	controls
//	//-----------------------------------------------------------
//	PROBE_START_SAMPLE,						
//	PROBE_END_SAMPLE,						
//	CALIBRATOR_START_SAMPLE,					
//	CALIBRATOR_END_SAMPLE,					
//	//-----------------------------------------------------------
//	//			PROBE_test	controls
//	//-----------------------------------------------------------
//	PROBE_TEST_PROFILE,						
//	PROBE_TEST_GAIN							
//}E_FLASH_fields;
//-----------------------------------------
//		Struct:		T_FLASH_fields
//-----------------------------------------
typedef struct T_FLASH_fields
{
	E_TxRx_MODE			TxRx_MODE;
	uint32_t 			System_ID;
	T_TxRx_control		TxRx_control[3];
	T_TGT_calibrate		TGT_calibrate;
	T_PROBE_test		PROBE_test;
	T_DET_algorithms	DET_algorithms;
	uint32_t			Enable_RF2_Support;			// Enable RF2 communication ( 0 = NO, 1 = Yes )
} T_FLASH_fields;
#endif