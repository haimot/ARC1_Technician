#ifndef T_SYSTEM_CONTROL_1_H
#define T_SYSTEM_CONTROL_1_H

#include "T_TxRx_control.h"
#include "T_TGT_calibrate.h"
#include "T_PROBE_test.h"
#include "dp_cplx.h"
#include "T_DET_algorithms.h"

#include <stdint.h>
//-----------------------------------------
//		struct:		T_SYSTEM_control_1
//-----------------------------------------
typedef struct T_SYSTEM_control_1
{
	uint32_t 			System_ID;
	T_TxRx_control 		TxRx_control_PROBE;
	T_TxRx_control 		TxRx_control_CALIBRATOR;
	T_TxRx_control 		TxRx_control_WORK;
	T_TGT_calibrate		TGT_calibrate;
	T_PROBE_test		PROBE_test;
	dp_cplx				Rx_correction[4];
	dp_cplx				Calibrator_correction[4];
	T_DET_algorithms	DET_algorithms;
	dp_cplx				DC_claculation[14][4]; // Eran 19.11.15 ZP
	uint32_t			Enable_RF2_Support;	   // Enable RF2 communication ( 0 = NO, 1 = Yes )
} T_SYSTEM_control_1;
#endif