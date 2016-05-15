//------------------------------------------------
//	Monitor interface
//	Alon Slapak	3/10/2014
//	Reference:
//		http://stackoverflow.com/questions/11130915/windows-form-clr-application-in-visual-studio-2012-rc
//		http://mcn-www.jwu.ac.jp/~yokamoto/openwww/vsg/VCpp2012FormApp/
//----------------------------------------------------
#include "main.h"
#include "MyForm.h"
#include "Recovery_Flight.h"
//#include "Loading_Page.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ARC1_Technician::MyForm myForm;        //NameOfProject::NameOfForm instanceOfForm;
	//ARC1_Technician::Recovery_Flight recovery_flight;
	//----------------------------------------
	//   Show on primary screen
	//----------------------------------------
	array<Screen^>^ sc;
	sc = Screen::AllScreens;
	//----------------------------------------
	//   'myForm' panel
	//----------------------------------------
	myForm.Left = sc[0]->Bounds.Left;
	myForm.Top = sc[0]->Bounds.Top;
	myForm.StartPosition = FormStartPosition::Manual;
	myForm.WindowState = FormWindowState::Normal;

	Application::Run(%myForm);
}