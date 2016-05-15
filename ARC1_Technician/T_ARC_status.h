#ifndef T_ARC_STATUS_H
#define T_ARC_STATUS_H

#include "T_DET_STATES.h"
#include "T_CHAB_STATES.h"
#include <stdint.h>
//-----------------------------------------
//		SYSTEM STATUS
//		Enum:		E_BUL_status
//
//	Changes by:
//		Haim Otachi 10/01/2016:  Add structures from ARC1_Technician.h
//-----------------------------------------
typedef enum
{
	BUL_GOOD = 0,
	BUL_FAULT,
	BUL_READY,
	BUL_FLASHING,
	BUL_VERIFYING
} E_BUL_status;
//-----------------------------------------
//		Struct:		T_DISAPLAY_fields
//-----------------------------------------
typedef struct T_ARC_status
{
	uint32_t			DEBUG_COUNT;

	uint32_t 			STATUS_SYS;
	uint32_t 			STATUS_OMR;
	uint32_t 			STATUS_DET;
	uint32_t 			STATUS_CHA;
	uint32_t 			STATUS_CHB;
	uint32_t 			STATUS_MCU;
	uint32_t 			STATUS_RF_MCU;

	uint32_t 			SW_VERSION_OMR;
	uint32_t 			SW_VERSION_DET;
	uint32_t 			SW_VERSION_CHA;
	uint32_t 			SW_VERSION_CHB;
	uint32_t 			SW_VERSION_MCU;
	uint32_t 			SW_VERSION_RF_MCU;

	E_BUL_status		BUL_status_OMR;
	E_BUL_status		BUL_status_DET;
	E_BUL_status		BUL_status_CHA;
	E_BUL_status		BUL_status_CHB;
	E_BUL_status		BUL_status_MCU;
	E_BUL_status		BUL_status_RF_MCU;

	uint32_t			PERIPHERALS_AD6655_A;
	uint32_t			PERIPHERALS_AD6655_B;

	uint32_t 			PERIPHERALS_FPGA_A;
	uint32_t 			PERIPHERALS_FPGA_B;

	uint32_t			clib_grade;							// calibration grade: Noise_STD, SNR, Manitude, Phase

	uint32_t			DATA_VALID_CHA;
	uint32_t			DATA_VALID_CHB;

	uint32_t			DATA_SATURATED_CHA;
	uint32_t			DATA_SATURATED_CHB;

	uint32_t			DATA_SATURATED_H_LEFT;
	uint32_t			DATA_SATURATED_V_LEFT;

	uint32_t			DATA_SATURATED_H_RIGHT;
	uint32_t			DATA_SATURATED_V_RIGHT;

	uint32_t    		PERIPHERALS_LMK04828;
	uint32_t    		PERIPHERALS_LMK01000;

	uint32_t    		PERIPHERALS_AD9910_A;
	uint32_t    		PERIPHERALS_AD9910_B;

	uint32_t   			MCU_TEMPERATURE;

	uint32_t 			UCD9222_DET_temperature_internal;
	uint32_t 			UCD9222_DET_temperature_external;
	uint32_t 			UCD9222_CHA_temperature_internal;
	uint32_t 			UCD9222_CHA_temperature_external;

	uint32_t			HMC830_PLL;

	uint32_t			RF_MCU_temperature;
	uint32_t			RF_temperature;

	T_DET_STATES		DET_STATES_shadow;

	T_CHAB_STATES		CHA_STATES_shadow;
	T_CHAB_STATES		CHB_STATES_shadow;
} T_ARC_status;
#endif