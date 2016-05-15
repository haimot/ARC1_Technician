#ifndef T_SYSTEM_CONTROL_0_H
#define T_SYSTEM_CONTROL_0_H

#include "T_ARC_status.h"
#include "T_SENSOR_data.h"
#include "T_SYSTEM_control_1.h"
#include "T_DATA_download.h"
#include "T_DEBUG_frees.h"
//-----------------------------------------
//		Enum:		E_ETEHRNET_STATUS
//-----------------------------------------
typedef enum
{
	ETHERNET_GOOD = 0,
	ETHERNET_PHY,
	ETHERNET_OFF
}	E_ETEHRNET_STATUS;
//-----------------------------------------
//		struct:		T_SYSTEM_control_0
//-----------------------------------------
typedef struct T_SYSTEM_control_0
{
	//TODO: Add to struct T_System_Control
	T_ARC_status			ARC_status;
	T_SENSOR_data			SENSOR_data;
	T_SYSTEM_control_1		SYSTEM_control_shadow;
	T_DATA_download 		DATA_download;

	//TODO: creat new struct with this name: SystemDebgigFrees
	T_DEBUG_frees			CHA_DEBUG_frees;
	T_DEBUG_frees			CHB_DEBUG_frees;
	T_DEBUG_frees			DET_DEBUG_frees;
	T_DEBUG_frees			OMR_DEBUG_frees;
	T_DEBUG_frees			MCU_DEBUG_frees;
} T_SYSTEM_control_0;
#endif