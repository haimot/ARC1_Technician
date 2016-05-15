//-----------------------------------------
//			Main_Thread.h 
//   Communication with GUI Status and System status
//	Haim Otachi	  12/01/2016
//----------------------------------------------------
#include "Main_Thread.h"


#pragma region Constructor / Destructor
// --------------------------------------------------
//  Real_Time_Thread - Default Constructor
//  Haim Otachi     12/01/2016
// 	Description:	the function initialize the any objects of the class with default parameters
// 	Reference: 
//  Return Value:	
// --------------------------------------------------
Main_Thread::Main_Thread()
{
	//-------------------------------------
	//	  create new object of the 'system_status' class
	//-------------------------------------
	system_status = gcnew C_SYSTEM_status;
	//-------------------------------------
	//	  create new object of the 'GUI_Status' class
	//-------------------------------------
	GUI_Status = gcnew C_GUI_Status;
	//-------------------------------------
	//	  create new object of the 'GUI' class
	//-------------------------------------
	GUI = gcnew MyForm;
}
// --------------------------------------------------
//  Real_Time_Thread - Destructor
//  Haim Otachi     12/01/2016
// 	Description:	the function delete the any objects of the class
// 	Reference: 
//  Return Value:	
// --------------------------------------------------
Main_Thread::~Main_Thread()
{
	//-------------------------------------
	//	  delete the 'system_status' object
	//-------------------------------------
	delete system_status;
	//-------------------------------------
	//	  delete the 'GUI_Status' object
	//-------------------------------------
	delete GUI_Status;
	//-------------------------------------
	//	  delete the 'GUI' object
	//-------------------------------------
	delete GUI;
}
#pragma endregion

#pragma region Public Methods
// --------------------------------------------------
//  Real_Time_Thread - Destructor
//  Haim Otachi     12/01/2016
// 	Description:	the function delete the any objects of the class
// 	Reference: 
//  Return Value:	
// --------------------------------------------------
void Main_Thread::Initialize(MyForm^ GUI_Other, C_SYSTEM_status^ system_status_other, C_GUI_Status^ GUI_Status_Other)
{
	system_status = system_status_other;
	GUI_Status = GUI_Status_Other;
	GUI = GUI_Other;
}
#pragma endregion