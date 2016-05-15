#ifndef T_DEBUG_FIELDS_H
#define T_DEBUG_FIELDS_H

#include "T_SNAPSHOT_descriptor.h"
//-----------------------------------------
//		MISC. parameters
//-----------------------------------------
#define MAX_STRING_LENGTH			512
//-----------------------------------------
//		Struct:		T_DEBUG_fields
//-----------------------------------------
typedef struct T_DEBUG_fields
{
	int					MATLAB_script_index;
	char				MATLAB_script[MAX_STRING_LENGTH];	// Haim Otachi 03/02/2016

	char				LOG_folder[MAX_STRING_LENGTH];
	E_SNAPSHOT_type		SNAPSHOT_type;
} T_DEBUG_fields;
#endif