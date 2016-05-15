#ifndef T_BUL_CONFIG_H
#define T_BUL_CONFIG_H

#include <iostream>

//-----------------------------------------
//		T_BUL_config
//-----------------------------------------
typedef struct T_BUL_config
{
	_Uint32t				target_dsp;
	_Uint32t				image_size;
	_Uint32t				reset_after_upload;
} T_BUL_config;
#endif