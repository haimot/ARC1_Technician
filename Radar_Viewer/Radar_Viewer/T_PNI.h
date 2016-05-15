#ifndef T_PNI_H
#define T_PNI_H
//-----------------------------------------
//		Struct:		T_TARGET
//-----------------------------------------
#include <stdint.h>

typedef struct T_PNI
{
	uint32_t Range_index;
	uint32_t Doppler_index;
	uint32_t Gain[4];

	double Range;
	double Radial_velocity; // Radial_velocity = doppler
	double Azimuth_H;
	double Azimuth_V;
	double Polarization_ratio_L;
	double Polarization_ratio_R;
	double Elevation;
	double Target_reliability;
} T_PNI;
#endif