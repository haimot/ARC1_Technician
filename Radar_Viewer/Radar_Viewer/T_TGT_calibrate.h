#ifndef T_TGT_CALIBRATE_H
#define T_TGT_CALIBRATE_H

#include <cstdint>
//-----------------------------------------
//  T_TGT_calibrate
//-----------------------------------------
typedef struct T_TGT_calibrate
{
	_Uint32t		Probe_start_sample;
	_Uint32t		Probe_end_sample;

	_Uint32t		Calibrator_start_sample;
	_Uint32t		Calibrator_end_sample;
} T_TGT_calibrate;
#endif