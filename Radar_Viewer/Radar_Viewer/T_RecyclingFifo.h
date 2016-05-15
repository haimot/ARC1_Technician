#ifndef _T_RECYCLINGFIFO_H
#define _T_RECYCLINGFIFO_H

#include <stdint.h>

#define  MAX_TRAJEC_NR                 30 //MAX 255
//-------------------------------------------
//		Struct:		T_RecyclingFifo_
//-------------------------------------------
typedef struct  T_RecyclingFifo_
{
	uint32_t		queue[MAX_TRAJEC_NR];	//TODO can be a tree
	int				begin;					//how many trajectories from MAX_TRAJEC_NR was realy used (also alive and dead), dive the maxNr of the arrey to check
} T_RecyclingFifo;
#endif