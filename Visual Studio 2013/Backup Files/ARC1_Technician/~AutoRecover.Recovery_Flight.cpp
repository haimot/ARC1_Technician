#include "Recovery_Flight.h"
//-----------------------------------------
//		TIMER
//-----------------------------------------
#define		TIMER_INTERVAL				1		// [mSec]
//-----------------------------------------
//		Field of Initial data
//-----------------------------------------
#define		SHOW_DETECTIONS								6
#define     SHOW_TRAJECTORIES							7

//-----------------------------------------
//		Namespace:	ARC1_Technician
//-----------------------------------------
namespace ARC1_Technician
{
	// --------------------------------------------------
	//  Recovery_Flight
	//  Haim Otachi		04/01/2016
	// 	Description:	Constructor:
	//						1. init controls
	//						2. Malloc buffers
	//						3. Read initial values from files
	// 	Reference: 
	//	Input Value:	
	//  Return Value: 
	// --------------------------------------------------
	Recovery_Flight::Recovery_Flight()
	{
		InitializeComponent();
		returned_message = L"";
		//-----------------------------------------
		//	Read INITIAL DATA from file
		//-----------------------------------------
		if (GUI_Status.Read_Data_From_File() == true)
		{
			//-----------------------------------------
			//	Initialize the Radar Viewer
			//-----------------------------------------
			returned_message = Radar_Viewer.Initialize(B_MAP_PANEL_RE_FLIGHT, B_MAP_RE_FLIGHT_VIDEO, GUI_Status);
			My_Re_Flight_Message(returned_message);
		}	

		operation_mode = -1;
		flag = false;
		//-----------------------------------------
		//		Init GUI -  generator of flight simulator
		//-----------------------------------------	
		B_FILE_TOM_Of_RE_FLIGHT->Text = gcnew String(GUI_Status.Viewer_TOM_File_Name);
		B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER->Text = gcnew String(GUI_Status.DETECTIONS_Folder_Of_Viewer);
		//-----------------------------------------------
		//					Timer
		//-----------------------------------------------
		this->Operations_Timer->Interval	= TIMER_INTERVAL;
		this->Operations_Timer->Enabled		= true;

		this->B_DETECTIONS->Checked			= true;
		this->B_TRAJECTORIES->Checked		= true;
	}
	// --------------------------------------------------
	//  ~Recovery_Flight()
	//  Haim Otachi		04/01/2016
	// 	Description:	Destructor: Clean up any resources being used.
	// 	Reference: 
	//	Input Value:	
	//  Return Value: 
	// --------------------------------------------------
	Recovery_Flight::~Recovery_Flight()
	{
		if (components)
		{
			delete components;
		}
	}
	// --------------------------------------------------
	//  My_Message
	//  Haim Otachi		04/01/2016
	// 	Description:	Put message on the GUI
	// 	Reference: 
	//	Input Value:	Message string
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::My_Re_Flight_Message(String^ message_string)
	{
		B_RE_FLIGHT_MESSAGE->Text = message_string;
		B_RE_FLIGHT_MESSAGE->Refresh();
	}
	// --------------------------------------------------
	//  Load_map_Click
	//  Haim Otachi		04/01/2016
	// 	Description:	BROWSE for obstacle map file
	// 	Reference: 
	//	Input Value:	
	//  Return Value:	
	// --------------------------------------------------
	void Recovery_Flight::B_LOAD_MAP_Click(System::Object^  sender, System::EventArgs^  e)
	{
		char OBSTACLES_File_Name_Of_Map[MAX_STRING_LENGTH];
		// --------------------------------------------------
		//			ask for file name
		// --------------------------------------------------
		B_fileBrowser_RE_FLIGHT_TOM->ShowDialog();
		B_FILE_TOM_Of_RE_FLIGHT->Text = B_fileBrowser_RE_FLIGHT_TOM->FileName;
		// --------------------------------------------------
		//			Update Radat_Viewer with TOM file name
		// --------------------------------------------------
		marshal_context ^ context = gcnew marshal_context();
		sprintf_s(OBSTACLES_File_Name_Of_Map, context->marshal_as<const char*>(B_fileBrowser_RE_FLIGHT_TOM->FileName));
		GUI_Status.Viewer_TOM_File_Name = OBSTACLES_File_Name_Of_Map;
		// --------------------------------------------------
		//			Clear screen
		// --------------------------------------------------	
		Radar_Viewer.Clear_Screen();
		B_MAP_PANEL_RE_FLIGHT->Invalidate();
		//--------------------------------------
		//	Laod TOM and plot on screen
		//--------------------------------------
		if (Radar_Viewer.Load_TOM_From_File() == false)
		{
			My_Re_Flight_Message("TOM file is incorrect.");
			return;
		}
		double temp = (int)(GUI_Status.Screen_Width_Of_Viewer / 1000);
		B_SCREEN_WIDTH_OF_VIEWER->Value = (int)(GUI_Status.Screen_Width_Of_Viewer / 1000);
		double scale = (double)GUI_Status.Screen_Width_Of_Viewer / 10;

		B_SCALE_RE_FLIGHT_VIEWER->Text = scale.ToString();

		operation_mode = -1;
	}
	// --------------------------------------------------
	//  B_LOAD_DETCTIONS_Click  
	//	Haim Otachi		04/01/2016
	// 	Description:	Load Detections file  
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_LOAD_RE_FLIGHT_DETECTION_Click(System::Object^  sender, System::EventArgs^  e)
	{
		char DETECTIONS_folder_Of_Viewer[MAX_STRING_LENGTH];
		//--------------------------------------
		// Put value in ANALYSE_fields structure's field
		//--------------------------------------
		B_BROWSE_RE_FLIGHT_DIR->SelectedPath = B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER->Text;
		B_BROWSE_RE_FLIGHT_DIR->ShowDialog();
		B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER->Text = B_BROWSE_RE_FLIGHT_DIR->SelectedPath;
		//--------------------------------------
		// Update the GUI data struct
		//--------------------------------------		
		marshal_context ^ context = gcnew marshal_context();
		sprintf_s(DETECTIONS_folder_Of_Viewer, context->marshal_as<const char*>(B_BROWSE_RE_FLIGHT_DIR->SelectedPath));
		GUI_Status.DETECTIONS_Folder_Of_Viewer = DETECTIONS_folder_Of_Viewer;
		//--------------------------------------
		//	Update Radar_Viewer screen
		//--------------------------------------
		if (Radar_Viewer.Load_Detections_From_File() == false)
		{
			My_Re_Flight_Message("Detections file is incorrect.");
			return;
		}
		B_SCREEN_WIDTH_OF_VIEWER->Value = (int)(GUI_Status.Screen_Width_Of_Viewer / 1000);
		double scale = (double)GUI_Status.Screen_Width_Of_Viewer / 10;

		B_SCALE_RE_FLIGHT_VIEWER->Text = scale.ToString();
		My_Re_Flight_Message("Detections file was loaded. Ready to play.");

		operation_mode = -1;
	}
	// --------------------------------------------------
	//  B_PLAY_RE_FLIGHT_VIEWER_Click  
	//  Alon Slapak 8/6/2015
	// 	Description:	Play experiment file 
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_PLAY_RE_FLIGHT_VIEWER_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//---------------------------------------------------
		//	if 'Play' button is not pressed
		//---------------------------------------------------
		if (operation_mode != 0)
		{
			returned_message = L"";

			My_Re_Flight_Message("Start playing the results.");
			//---------------------------------------------------
			//			Prepare screen
			//---------------------------------------------------
			Radar_Viewer.Plot_TOM_On_Screen();
			// --------------------------------------------------
			//			Clear screen
			// --------------------------------------------------
			if (operation_mode != 1 && flag == false)
			{
				Radar_Viewer.Restart();
			}

			operation_mode = 0;
			flag = true;

			Path = "Media_Controls_Pause_icon_48_pixel.png";
			image = gcnew Bitmap(Path, true);
			B_PLAY_RE_FLIGHT_VIEWER->Image = image;
		}
		//--------------------------------
		//	if 'Play' button 
		//--------------------------------
		else if (operation_mode == 0)
		{
			//--------------------------------
			//	we update the system to 'Pause' case
			//--------------------------------
			operation_mode = 2;
			Path = "Media_Controls_Play_icon_48_pixel.png";
			image = gcnew Bitmap(Path, true);
			B_PLAY_RE_FLIGHT_VIEWER->Image = image;
		}
	}
	// --------------------------------------------------
	//  B_CLEAR_WIRE_Click  
	//  Haim Otachi		04/01/2016
	// 	Description:	Clear viewer screen
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_CLEAR_VIEWER_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//----------------------------
		//		Clear TOM and Radar_Route
		//----------------------------
		Radar_Viewer.Clear_Radar_Viewer();
		//----------------------------
		//		Clear GUI_Status
		//----------------------------
		GUI_Status.Viewer_TOM_File_Name = "Enter obstacles file name...............";
		GUI_Status.DETECTIONS_Folder_Of_Viewer = "Enter DETECTIONS folder...............";
		B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER->Text = gcnew String(GUI_Status.DETECTIONS_Folder_Of_Viewer);
		B_FILE_TOM_Of_RE_FLIGHT->Text = gcnew String(GUI_Status.Viewer_TOM_File_Name);
	}
	// --------------------------------------------------
	//  B_RESET_VIEWER_Click  
	//  Haim Otachi	04/01/2016
	// 	Description:	Reset the viewer scale and 
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_RESET_VIEWER_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (Radar_Viewer.Reset_Radar_Viewer() == false)
		{
			My_Re_Flight_Message("Dimensions error. Files cannot be displayed.");
		}
	}
	// --------------------------------------------------
	//  B_MAP_PANEL_RE_FLIGHT_Paint  
	//  Haim Otachi		04/01/2016
	// 	Description:	Plot TOM after Paint event
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		Radar_Viewer.Plot_TOM_On_Screen();
	}
	// --------------------------------------------------
	//  MyForm_FormClosing  
	// Haim Otachi		04/01/2016
	// 	Description:	Open file for serialization of GUI data
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::Recovery_Flight_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		//-----------------------------------------
		//	Read INITIAL DATA from file
		//-----------------------------------------
		GUI_Status.Save_Data_To_File();
	}

	#pragma region Mouse Operations: B_MAP_PANEL (MAP Tab control Function)
	// --------------------------------------------------
	//  B_MAP_PANEL_RE_FLIGHT_MouseClick  
	//  Alon Slapak 12/03/2016
	// 	Description:	Get wires from user using mouse
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		////-------------------------------------------------------
		////	LEFT: add WIRE
		////-------------------------------------------------------
		//if (e->Button == System::Windows::Forms::MouseButtons::Left)
		//{
		//	Radar_Viewer.Add_Wire(e->X, e->Y);
		//}
		////-------------------------------------------------------
		////	RIGHT: add Pylon
		////-------------------------------------------------------
		//if (e->Button == System::Windows::Forms::MouseButtons::Right)
		//{
		//	Radar_Viewer.Add_Pylon(e->X, e->Y);
		//}
	}
	// --------------------------------------------------
	//  B_MAP_PANEL_RE_FLIGHT_MouseLeave  
	//  Alon Slapak 12/03/2016
	// 	Description:	Get wires from user using mouse
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseLeave(System::Object^  sender, System::EventArgs^  e)
	{
		////-------------------------------------------------------
		////	delete the line from the panel ( from B_SIMULATOR_PANEL)
		////-------------------------------------------------------
		//Radar_Viewer.Erase_Line();
	}
	// --------------------------------------------------
	//  B_MAP_PANEL_MouseDown  
	//  Haim Otachi		28/12/2015
	// 	Description:	Take reference viewer position to serve for the mouse move function, so as to 
	//					move the viewer with the mouse.
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//-------------------------------------------------------
		//	LEFT: add WIRE
		//-------------------------------------------------------
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			mouse_x = e->X;
			mouse_y = e->Y;
		}
	}
	// --------------------------------------------------
	//  B_MAP_PANEL_MouseMove  
	//  Haim Otachi		28/12/2015
	// 	Description:	Move viewer when moving the mouse with left-button pressed
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		// -----------------------------------
		//			all other casses
		// -----------------------------------
		if (operation_mode != 4)
		{
			if (e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				Radar_Viewer.Offset_Viewer_Position(e->X - mouse_x, e->Y - mouse_y);
				mouse_x = e->X;
				mouse_y = e->Y;
				// --------------------------------------------------
				// Refresh screen with new scale
				// --------------------------------------------------
				B_MAP_PANEL_RE_FLIGHT->Invalidate();
				//-----------------------------------------
				//	Plot the obstacles to the screen
				//-----------------------------------------
				Radar_Viewer.Plot_TOM_On_Screen();
			}
		}
		// -----------------------------------
		//			'Edit' case
		// -----------------------------------
		else   // if operation_mode == 4
		{
			//-------------------------------------------------------
			//  The Mouse Move to the next point and plot to the screen the Pylon and wire the was created
			//-------------------------------------------------------
			Radar_Viewer.Mouse_Move(e->X, e->Y);
		}	
	}
	// --------------------------------------------------
	//  B_VIEWER_PANEL_MouseWheel  
	//  Haim Otachi		28/12/2015
	// 	Description:	Using the mouse wheel to change the scale of the viewer
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if ((e->Delta < 0) && (B_SCREEN_WIDTH_OF_VIEWER->Value > B_SCREEN_WIDTH_OF_VIEWER->Minimum))
		{
			B_SCREEN_WIDTH_OF_VIEWER->Value -= 1;
		}
		if ((e->Delta > 0) && (B_SCREEN_WIDTH_OF_VIEWER->Value < B_SCREEN_WIDTH_OF_VIEWER->Maximum))
		{
			B_SCREEN_WIDTH_OF_VIEWER->Value += 1;
		}
		// --------------------------------------------------
		// Calculate the new scale
		// --------------------------------------------------		
		double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
		Radar_Viewer.Set_Viewer_Scale(screen_width_meter);
		// --------------------------------------------------
		// Refresh screen with new scale
		// --------------------------------------------------
		B_MAP_PANEL_RE_FLIGHT->Invalidate();
		//-----------------------------------------
		//	Plot the current radar position (if exist - for 'real time case'),
		//	And the obstacles of 'TOM' to the screen
		//-----------------------------------------
		Radar_Viewer.Plot_TOM_On_Screen();
		//-----------------------------------------
		//	Update GUI controls
		//-----------------------------------------
		double scale = (double)GUI_Status.Screen_Width_Of_Viewer / 10;
		B_SCALE_RE_FLIGHT_VIEWER->Text = scale.ToString();
	}
	// --------------------------------------------------
	//  B_SCREEN_WIDTH_OF_VIEWER  
	//  Haim Otachi     11/10/2015
	// 	Description:	change radar screen width
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_SCREEN_WIDTH_OF_RE_FLIGHT_VIEWER_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		try
		{
			// --------------------------------------------------
			// Calculate the new scale
			// --------------------------------------------------		
			double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
			Radar_Viewer.Set_Viewer_Scale(screen_width_meter);
			// --------------------------------------------------
			// Refresh screen with new scale
			// --------------------------------------------------
			B_MAP_PANEL_RE_FLIGHT->Invalidate();
			//-----------------------------------------
			//	Plot the current radar position (if exist - for 'real time case'),
			//	And the obstacles of 'TOM' to the screen
			//-----------------------------------------
			Radar_Viewer.Plot_TOM_On_Screen();
			//-----------------------------------------
			//	Update GUI controls
			//-----------------------------------------
			double scale = (double)GUI_Status.Screen_Width_Of_Viewer / 10;
			B_SCALE_RE_FLIGHT_VIEWER->Text = scale.ToString();
		}
		catch (Exception^ Ex)
		{
			Ex->Message;
		}
	}
	// --------------------------------------------------
	//  B_ZOOM_IN_Click  
	//  Haim Otachi     09/03/2016
	// 	Description:	change radar screen width - ZOOM IN
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_ZOOM_IN_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (B_SCREEN_WIDTH_OF_VIEWER->Value > B_SCREEN_WIDTH_OF_VIEWER->Minimum)
		{
			B_SCREEN_WIDTH_OF_VIEWER->Value -= 1;
			// --------------------------------------------------
			// Calculate the new scale
			// --------------------------------------------------
			double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
			Radar_Viewer.Set_Step_Viewer_Scale(screen_width_meter);
			// --------------------------------------------------
			// Refresh screen with new scale
			// --------------------------------------------------
			B_MAP_PANEL_RE_FLIGHT->Invalidate();
			//-----------------------------------------
			//	Plot the obstacles to the screen
			//-----------------------------------------
			Radar_Viewer.Plot_TOM_On_Screen();
			//-----------------------------------------
			//	Update GUI controls
			//-----------------------------------------
			double scale = (double)GUI_Status.Screen_Width_Of_Viewer / 10;
			B_SCALE_RE_FLIGHT_VIEWER->Text = scale.ToString();
		}
	}
	// --------------------------------------------------
	//  B_ZOOM_OUT_Click  
	//  Haim Otachi     09/03/2016
	// 	Description:	change radar screen width - ZOOM OUT
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_ZOOM_OUT_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (B_SCREEN_WIDTH_OF_VIEWER->Value < B_SCREEN_WIDTH_OF_VIEWER->Maximum)
		{
			B_SCREEN_WIDTH_OF_VIEWER->Value += 1;
			// --------------------------------------------------
			// Calculate the new scale
			// --------------------------------------------------
			double screen_width_meter = (double)B_SCREEN_WIDTH_OF_VIEWER->Value * 1000;
			Radar_Viewer.Set_Step_Viewer_Scale(screen_width_meter);
			// --------------------------------------------------
			// Refresh screen with new scale
			// --------------------------------------------------
			B_MAP_PANEL_RE_FLIGHT->Invalidate();
			//-----------------------------------------
			//	Plot the obstacles to the screen
			//-----------------------------------------
			Radar_Viewer.Plot_TOM_On_Screen();
			//-----------------------------------------
			//	Update GUI controls
			//-----------------------------------------
			double scale = (double)GUI_Status.Screen_Width_Of_Viewer / 10;
			B_SCALE_RE_FLIGHT_VIEWER->Text = scale.ToString();
		}
	}
	#pragma endregion
	// --------------------------------------------------
	//  B_STOP_Click  
	// Haim Otachi		11/03/2016
	// 	Description:	???
	// 	Reference: 
	//  Input value:
	//  Return Value: 
	// --------------------------------------------------
	void Recovery_Flight::B_STOP_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//--------------------------------
		//	we update the system to 'Stop' case
		//--------------------------------
		operation_mode = 4;
	}

	void Recovery_Flight::B_TOOL_EDIT_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		//if (operation_mode != 4)
		//{
		//	Path = gcnew String("C:\\Users\\user\\Pictures\\images\\edit_validated_icon.png");
		//	// -----------------------------------
		//	//			'Edit' case
		//	// -----------------------------------
		//	operation_mode = 4;

		//	image = gcnew Bitmap(Path, true);
		//	B_TOOL_EDIT->Image = image;

		//	My_Re_Flight_Message("Edit case.");
		//}
		//else
		//{
		//	Path = gcnew String("C:\\Users\\user\\Pictures\\images\\Edit.png");
		//	// -----------------------------------
		//	//			'General' case
		//	// -----------------------------------
		//	operation_mode = -1;

		//	image = gcnew Bitmap(Path, true);
		//	B_TOOL_EDIT->Image = image;

		//	My_Re_Flight_Message("finished Edit case.");
		//}
	}

	void Recovery_Flight::Operations_Timer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		if (operation_mode != -1)
		{
			if (returned_message != L"done" && operation_mode != 4) // operation_mode = 4 - 'Stop' case
			{
				// -----------------------------------
				//			'Play' case
				// -----------------------------------
				if (operation_mode == 0)
				{
					returned_message = Radar_Viewer.Viewer_Step();
					My_Re_Flight_Message(returned_message);
				}
				// -----------------------------------
				//			'Step' case
				// -----------------------------------
				else if (operation_mode == 1)
				{
					returned_message = Radar_Viewer.Viewer_Step();
					My_Re_Flight_Message(returned_message);

					operation_mode = 3;
				}
				// -----------------------------------
				//			Stop 'Step' case
				// -----------------------------------
				else if (operation_mode == 3)
				{
					Path = gcnew String("Media_Controls_Play_icon_48_pixel.png");
					image = gcnew Bitmap(Path, true);
					B_PLAY_RE_FLIGHT_VIEWER->Image = image;

					My_Re_Flight_Message("Scenario 'Step' is done.");
				}
				// -----------------------------------
				//			'Pause' case
				// -----------------------------------
				else 
				{
					My_Re_Flight_Message(returned_message);
				}				
			}
			else if (returned_message == L"done")
			{
				Path = gcnew String("Media_Controls_Play_icon_48_pixel.png");
				image = gcnew Bitmap(Path, true);
				B_PLAY_RE_FLIGHT_VIEWER->Image = image;

				My_Re_Flight_Message("Scenario is done.");
			}
			// -----------------------------------
			//			'Stop' case
			// -----------------------------------
			else
			{
				Path = gcnew String("Media_Controls_Play_icon_48_pixel.png");
				image = gcnew Bitmap(Path, true);
				B_PLAY_RE_FLIGHT_VIEWER->Image = image;

				My_Re_Flight_Message("Viewer is stop.");
				// --------------------------------------------------
				//			Clear screen
				// --------------------------------------------------	
				Radar_Viewer.Restart();
				B_MAP_PANEL_RE_FLIGHT->Invalidate();
				// --------------------------------------------------
				//	 Refresh the data and change the 'returned_message' to 'done'
				// --------------------------------------------------
				returned_message = L"done";
				My_Re_Flight_Message(returned_message);
				//--------------------------------------
				//	Laod TOM and plot on screen
				//--------------------------------------
				if (Radar_Viewer.Load_TOM_From_File() == false)
				{
					My_Re_Flight_Message("TOM file is incorrect.");
					return;
				}

				operation_mode = -1;
			}
		}
	}

	void Recovery_Flight::B_STEP_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//--------------------------------
		//	we update the system to 'Step' case
		//--------------------------------
		operation_mode = 1;
		flag = true;
		returned_message = L"";
	}

	void Recovery_Flight::B_DETECTIONS_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		GUI_Status.Update(SHOW_DETE)
	}
	void Recovery_Flight::B_TRAJECTORIES_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{

	}
}
