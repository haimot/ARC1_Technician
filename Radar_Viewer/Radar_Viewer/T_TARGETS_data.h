#ifndef T_TARGETS_DATA_H
#define T_TARGETS_DATA_H

#include "T_PNI.h"
//-----------------------------------------
//            Display RADAR view
//-----------------------------------------
#define MAX_NUMBER_OF_TARGETS            100
//-----------------------------------------
//		Struct:	  T_TARGETS_data
//-----------------------------------------
typedef struct T_TARGETS_data
{
	double				Authentication;
	double				Targets_number;
	double				Noise_Level[4];
	T_PNI				Targets_array[MAX_NUMBER_OF_TARGETS];
} T_TARGETS_data;
#endif



