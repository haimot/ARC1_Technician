#ifndef _T_TRAJECTORY__H
#define _T_TRAJECTORY__H

#include <stdint.h>

#define  PARAMETER_NR_STATE            5
#define  PARAMETER_NR_MES              5
//-------------------------------------------
//		Enum:		TrjType
//-------------------------------------------
typedef enum { DEBUGPYLON, DEBUGGROUND, DEBUGWIRE, PYLON00 } TrjType;
//-------------------------------------------
//		Enum:		BoolC
//-------------------------------------------
typedef enum { false_C, true_C} Bool_C;
//-------------------------------------------
//		Struct:		T_Trajectory_
//-------------------------------------------
typedef struct  T_Trajectory_
{
	int					trjNrInArray;
	int					trjNrGlobal;
	bool				isEmpty;											// true - is empty    , false - is not empty
	uint32_t			startFrame;											//time of the birth of this trajectory
	double				xEstVct[PARAMETER_NR_STATE];						//vector of estimation values
	double				pEstMtx[PARAMETER_NR_STATE][PARAMETER_NR_STATE];	//vector of Covariance Matrixes
	double				innovVect[PARAMETER_NR_MES];						//vector of innovation (prompted-fact)
	double				innovCovMtx[PARAMETER_NR_MES][PARAMETER_NR_MES];	//vector of Covariance Matrices
	double				sMtxInv[PARAMETER_NR_MES][PARAMETER_NR_MES];		// Covariance Matrices

	//double forgetting; // <- it's like downcouter that kills the Trajectory
	uint32_t			forgetEvent;										//counter of the frozen stutus events
	bool				isFrozen;											//vector one of two (0 - recived detection carently | 1 not recived )
	double				zkVect[PARAMETER_NR_MES];							//vector of mesurments
	TrjType				trjType;											//type of the trajectory (now one of three wire|pilon|ground )
	uint32_t			deathFrame;											//here 0 alive, >0 the frame nr, that trajectory was killed // here status Shai: status of (now one of three 0- killed| 1-alive )
	double				jacobyMtx[PARAMETER_NR_STATE][PARAMETER_NR_STATE];

	//   bool isPredictedDone;
	double				xEstVctPredicted[PARAMETER_NR_STATE];
	double				pEstMtxPredicted[PARAMETER_NR_STATE][PARAMETER_NR_STATE];
} T_Trajectory;
#endif