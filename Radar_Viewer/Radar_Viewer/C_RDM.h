#ifndef C_RDM_H
#define C_RDM_H

#include "T_TARGETS_data.h"
//#include "T_SYSTEM_control_0.h"
#include <stdint.h>

using namespace System::Drawing;
using namespace System::Windows::Forms;
//-----------------------------------------
//		Class:	C_RDM
//-----------------------------------------
public ref class C_RDM
{
	//-----------------------------------------
	//			Private Fields
	//-----------------------------------------
	private:		
	double*					RDM;
	double*					RDM_buffer_double;
	uint32_t				RDM_size_int16;
	
	//T_SYSTEM_control_0*		system_status;
	PictureBox^				RDM_View;

	public:
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------			
	C_RDM();
	//-------------------------------------
	//			Destructor
	//-------------------------------------
	~C_RDM();
	//-------------------------------------------
	//			Public Methods
	//-------------------------------------------
	void		Initialize(PictureBox^	RDM_View_Other);
	double		Update_RDM(Point% RDM_Point);
};
#endif