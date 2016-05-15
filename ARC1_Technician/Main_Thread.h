#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H
//-----------------------------------------
//			Main_Thread.h 
//   Communication with GUI Status and System status
//-----------------------------------------
#include "C_SYSTEM_status.h"		// Communication with System Status
#include "C_GUI_Status.h"			// Communication with GUI Status
#include "MyForm.h"					// Communication with GUI 
//-----------------------------------------
//	using namespace:
//			1.	ARC1_Technician
//-----------------------------------------
using namespace ARC1_Technician;
//-----------------------------------------
//		ref class:	Main_Thread
//-----------------------------------------
public ref class Main_Thread
{
	//-----------------------------------------
	//			Private Fields
	//-----------------------------------------
	private:
		C_SYSTEM_status^				system_status;
		C_GUI_Status^					GUI_Status;
		MyForm^							GUI;
	//-----------------------------------------
	//			Constructor
	//-----------------------------------------
	public:							Main_Thread();
	//-----------------------------------------
	//			Destructor
	//-----------------------------------------
	public:							~Main_Thread();
	//-----------------------------------------
	//			Public Methods
	//-----------------------------------------	
	public:
		void							Initialize(MyForm^ GUI_Other, C_SYSTEM_status^ system_status_other, C_GUI_Status^ GUI_Status_Other);
		//void							Update_All();
};
#endif