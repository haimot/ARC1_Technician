#ifndef T_DISAPLAY_FIELDS_H
#define T_DISAPLAY_FIELDS_H

#include "T_DEBUG_fields.h"
#include "T_FLASH_fields.h"
#include "T_MAINTENANCE_fields.h"
#include <stdint.h>
//-----------------------------------------
//		Struct:		T_DISAPLAY_fields
//-----------------------------------------
typedef struct T_DISAPLAY_fields
{
	uint32_t					TAB_index;
	T_MAINTENANCE_fields		MAINTENANCE_fields;
	T_DEBUG_fields				DEBUG_fields;
	T_FLASH_fields				FLASH_fields;
} T_DISAPLAY_fields;
#endif