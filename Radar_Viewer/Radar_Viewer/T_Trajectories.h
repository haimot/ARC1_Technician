#ifndef _T_TRAJECTORIES__H
#define _T_TRAJECTORIES__H

#include "T_Trajectory.h"
#include "T_RecyclingFifo.h"
#include <stdint.h>

#define  MAX_TRAJEC_NR                 30 //MAX 255
//-------------------------------------------
//		Struct:		T_Trajectories_
//-------------------------------------------
typedef struct  T_Trajectories_
{
	T_Trajectory			trajectoriesData[MAX_TRAJEC_NR];	//TODO can be a tree
	uint32_t				trajectoriesNr;						//how many trajectories from MAX_TRAJEC_NR was realy used (also alive and dead), dive the maxNr of the arrey to check
	uint32_t				trajectoriesNrAlive;				//how much trajectories are alive
	uint32_t				frameNrAct;							//Nr of actual frame
	T_RecyclingFifo			recFifo;
} T_Trajectories;
#endif /* __MATCHMAKER_H */

