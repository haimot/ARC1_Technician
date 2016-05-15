#ifndef T_DET_STATES_H
#define T_DET_STATES_H

#include <stdint.h>
//-----------------------------------------
//		Struct:		T_DET_STATES
//-----------------------------------------
typedef struct T_DET_STATES
{
	uint32_t		DET_BRAIN_STATE;
	uint32_t 		DET_ACQUISITION_STATE;
	uint32_t		DET_WORK_STATE;
	uint32_t		DET_CALIBRATE_STATE;
	uint32_t		DET_FIRST_DETECTION_STATE;
	uint32_t		CHAB_INITIALIZATION_STATE;
} T_DET_STATES;
#endif