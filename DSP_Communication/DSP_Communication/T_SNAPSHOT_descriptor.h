#ifndef T_SNAPSHOT_DESCRIPTOR_H
#define T_SNAPSHOT_DESCRIPTOR_H

#include <iostream>

//-----------------------------------------
//		Enum:		Snapshot
//-----------------------------------------

typedef enum
{
	SNAPSHOT_CPI = 0,
	SNAPSHOT_PRE_FFT,
	SNAPSHOT_RDM,
	SNAPSHOT_PROBE_TEST
} E_SNAPSHOT_type;
//-----------------------------------------
//		Struct:		T_SNAPSHOT_descriptor
//-----------------------------------------
typedef struct T_SNAPSHOT_descriptor
{
	E_SNAPSHOT_type		SNAPSHOT_type;
	_Uint32t			SNAPSHOT_number_of_samples;
} T_SNAPSHOT_descriptor;
#endif