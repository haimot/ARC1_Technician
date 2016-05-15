#ifndef T_DET_ALGORITHMS_H
#define T_DET_ALGORITHMS_H

#include <stdint.h>
//-----------------------------------------
//  struct:		T_DET_algorithms
//-----------------------------------------
typedef struct T_DET_algorithms
{
	uint32_t			OFFSET_samples;
	uint32_t			RANGE_samples;
	uint32_t            Number_of_buffers;
	uint32_t			Number_of_RDMs;
	uint16_t			Target_detection_1st_threshold;
	uint16_t			Target_detection_2nd_threshold;	// Eran 23.6.15
	uint16_t			Maximal_doppler;
	uint16_t			Range_decimation;
	int16_t				AGC_threshold;
	//uint16_t			Minimum_range_meter;
} T_DET_algorithms;
#endif