#pragma once
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

#include "C_GUI_Status.h"
#include "C_Radar_Viewer.h"

namespace ARC1_Technician 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace msclr::interop;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Radar_Viewer;

	/// <summary>
	/// Summary for Recovery_Flight
	/// </summary>
	public ref class Recovery_Flight : public System::Windows::Forms::Form
	{
		public:
			Recovery_Flight();

		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~Recovery_Flight();
	
	protected:
	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::Label^  B_SCALE_RE_FLIGHT_VIEWER;
	private: System::Windows::Forms::Label^  label265;
	private: System::Windows::Forms::PictureBox^  B_MAP_RE_FLIGHT_VIDEO;
	private: System::Windows::Forms::GroupBox^  groupBox115;
	private: System::Windows::Forms::Button^  B_LOAD_RE_FLIGHT_DETECTION;
	private: System::Windows::Forms::TextBox^  B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER;
	private: System::Windows::Forms::GroupBox^  groupBox114;
	private: System::Windows::Forms::Button^  B_LOAD_MAP;
	private: System::Windows::Forms::TextBox^  B_FILE_TOM_Of_RE_FLIGHT;
	private: System::Windows::Forms::Button^  B_PLAY_RE_FLIGHT_VIEWER;
	private: System::Windows::Forms::Label^  label251;
	private: System::Windows::Forms::Label^  label263;

	private: System::Windows::Forms::TrackBar^  B_SCREEN_WIDTH_OF_VIEWER;
	private: System::Windows::Forms::Label^  label50;
	private: System::Windows::Forms::TextBox^  B_RE_FLIGHT_MESSAGE;
	private: System::Windows::Forms::OpenFileDialog^  B_fileBrowser_RE_FLIGHT_TOM;

	private: System::Windows::Forms::FolderBrowserDialog^  B_BROWSE_RE_FLIGHT_DIR;
	private: System::Windows::Forms::GroupBox^  groupBox9;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_ERROR_FUNCTION;

	private: System::Windows::Forms::Panel^  B_MAP_PANEL_RE_FLIGHT;





	private: System::Windows::Forms::Button^  B_STOP;
	private: System::Windows::Forms::ToolStrip^  VIEWER_TOOL_STRIP;




	private: System::Windows::Forms::ToolStripButton^  B_TOOL_EDIT;
	private: System::Windows::Forms::Timer^  Operations_Timer;
	private: System::Windows::Forms::Button^  B_STEP;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;

	private: System::Windows::Forms::ToolTip^  TOOL_TIP_PLAY;
	private: System::Windows::Forms::ToolTip^  TOOL_TIP_STOP;
	private: System::Windows::Forms::ToolStripButton^  B_ZOOM_IN;
	private: System::Windows::Forms::ToolStripButton^  B_ZOOM_OUT;
	private: System::Windows::Forms::ToolTip^  TOOL_TIP_STEP_BY_STEP;
	private: System::Windows::Forms::ToolTip^  TOOL_TIP_RESET_SETTING;
	private: System::Windows::Forms::ToolStripButton^  B_RESET_VIEWER;
	private: System::Windows::Forms::ToolStripButton^  B_CLEAR_VIEWER;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripButton^  B_CALCULATE_DISTANCE;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::GroupBox^  B_VISIBLE_OBSTACLES;

	private: System::Windows::Forms::CheckBox^  B_DETECTIONS;
	private: System::Windows::Forms::CheckBox^  B_TRAJECTORIES;










	private: System::ComponentModel::IContainer^  components;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


		#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Recovery_Flight::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->B_MAP_PANEL_RE_FLIGHT = (gcnew System::Windows::Forms::Panel());
			this->B_VISIBLE_OBSTACLES = (gcnew System::Windows::Forms::GroupBox());
			this->B_TRAJECTORIES = (gcnew System::Windows::Forms::CheckBox());
			this->B_DETECTIONS = (gcnew System::Windows::Forms::CheckBox());
			this->VIEWER_TOOL_STRIP = (gcnew System::Windows::Forms::ToolStrip());
			this->B_TOOL_EDIT = (gcnew System::Windows::Forms::ToolStripButton());
			this->B_CALCULATE_DISTANCE = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->B_ZOOM_IN = (gcnew System::Windows::Forms::ToolStripButton());
			this->B_ZOOM_OUT = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->B_RESET_VIEWER = (gcnew System::Windows::Forms::ToolStripButton());
			this->B_CLEAR_VIEWER = (gcnew System::Windows::Forms::ToolStripButton());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->B_SCALE_RE_FLIGHT_VIEWER = (gcnew System::Windows::Forms::Label());
			this->label265 = (gcnew System::Windows::Forms::Label());
			this->B_MAP_RE_FLIGHT_VIDEO = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox115 = (gcnew System::Windows::Forms::GroupBox());
			this->B_LOAD_RE_FLIGHT_DETECTION = (gcnew System::Windows::Forms::Button());
			this->B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER = (gcnew System::Windows::Forms::TextBox());
			this->groupBox114 = (gcnew System::Windows::Forms::GroupBox());
			this->B_LOAD_MAP = (gcnew System::Windows::Forms::Button());
			this->B_FILE_TOM_Of_RE_FLIGHT = (gcnew System::Windows::Forms::TextBox());
			this->B_PLAY_RE_FLIGHT_VIEWER = (gcnew System::Windows::Forms::Button());
			this->label251 = (gcnew System::Windows::Forms::Label());
			this->label263 = (gcnew System::Windows::Forms::Label());
			this->B_SCREEN_WIDTH_OF_VIEWER = (gcnew System::Windows::Forms::TrackBar());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->B_RE_FLIGHT_MESSAGE = (gcnew System::Windows::Forms::TextBox());
			this->B_fileBrowser_RE_FLIGHT_TOM = (gcnew System::Windows::Forms::OpenFileDialog());
			this->B_BROWSE_RE_FLIGHT_DIR = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->B_ERROR_FUNCTION = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->B_STOP = (gcnew System::Windows::Forms::Button());
			this->Operations_Timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->B_STEP = (gcnew System::Windows::Forms::Button());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->TOOL_TIP_PLAY = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->TOOL_TIP_STOP = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->TOOL_TIP_STEP_BY_STEP = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->TOOL_TIP_RESET_SETTING = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->B_MAP_PANEL_RE_FLIGHT->SuspendLayout();
			this->B_VISIBLE_OBSTACLES->SuspendLayout();
			this->VIEWER_TOOL_STRIP->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_MAP_RE_FLIGHT_VIDEO))->BeginInit();
			this->groupBox115->SuspendLayout();
			this->groupBox114->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCREEN_WIDTH_OF_VIEWER))->BeginInit();
			this->groupBox9->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_ERROR_FUNCTION))->BeginInit();
			this->SuspendLayout();
			// 
			// B_MAP_PANEL_RE_FLIGHT
			// 
			this->B_MAP_PANEL_RE_FLIGHT->BackColor = System::Drawing::Color::DarkGray;
			this->B_MAP_PANEL_RE_FLIGHT->Controls->Add(this->B_VISIBLE_OBSTACLES);
			this->B_MAP_PANEL_RE_FLIGHT->Controls->Add(this->VIEWER_TOOL_STRIP);
			this->B_MAP_PANEL_RE_FLIGHT->Controls->Add(this->panel5);
			this->B_MAP_PANEL_RE_FLIGHT->Controls->Add(this->B_SCALE_RE_FLIGHT_VIEWER);
			this->B_MAP_PANEL_RE_FLIGHT->Controls->Add(this->label265);
			this->B_MAP_PANEL_RE_FLIGHT->Dock = System::Windows::Forms::DockStyle::Top;
			this->B_MAP_PANEL_RE_FLIGHT->ForeColor = System::Drawing::Color::Black;
			this->B_MAP_PANEL_RE_FLIGHT->Location = System::Drawing::Point(0, 0);
			this->B_MAP_PANEL_RE_FLIGHT->MaximumSize = System::Drawing::Size(600, 600);
			this->B_MAP_PANEL_RE_FLIGHT->MinimumSize = System::Drawing::Size(600, 600);
			this->B_MAP_PANEL_RE_FLIGHT->Name = L"B_MAP_PANEL_RE_FLIGHT";
			this->B_MAP_PANEL_RE_FLIGHT->Size = System::Drawing::Size(600, 600);
			this->B_MAP_PANEL_RE_FLIGHT->TabIndex = 129;
			this->B_MAP_PANEL_RE_FLIGHT->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_Paint);
			this->B_MAP_PANEL_RE_FLIGHT->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseClick);
			this->B_MAP_PANEL_RE_FLIGHT->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseDown);
			this->B_MAP_PANEL_RE_FLIGHT->MouseLeave += gcnew System::EventHandler(this, &Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseLeave);
			this->B_MAP_PANEL_RE_FLIGHT->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseMove);
			this->B_MAP_PANEL_RE_FLIGHT->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Recovery_Flight::B_MAP_PANEL_RE_FLIGHT_MouseWheel);
			// 
			// B_VISIBLE_OBSTACLES
			// 
			this->B_VISIBLE_OBSTACLES->BackColor = System::Drawing::Color::DarkGray;
			this->B_VISIBLE_OBSTACLES->Controls->Add(this->B_TRAJECTORIES);
			this->B_VISIBLE_OBSTACLES->Controls->Add(this->B_DETECTIONS);
			this->B_VISIBLE_OBSTACLES->ForeColor = System::Drawing::Color::Black;
			this->B_VISIBLE_OBSTACLES->Location = System::Drawing::Point(476, 5);
			this->B_VISIBLE_OBSTACLES->Name = L"B_VISIBLE_OBSTACLES";
			this->B_VISIBLE_OBSTACLES->Size = System::Drawing::Size(120, 76);
			this->B_VISIBLE_OBSTACLES->TabIndex = 217;
			this->B_VISIBLE_OBSTACLES->TabStop = false;
			this->B_VISIBLE_OBSTACLES->Text = L"Visible Obstacles";
			// 
			// B_TRAJECTORIES
			// 
			this->B_TRAJECTORIES->AutoSize = true;
			this->B_TRAJECTORIES->Checked = true;
			this->B_TRAJECTORIES->CheckState = System::Windows::Forms::CheckState::Checked;
			this->B_TRAJECTORIES->ForeColor = System::Drawing::Color::Black;
			this->B_TRAJECTORIES->Location = System::Drawing::Point(27, 46);
			this->B_TRAJECTORIES->Name = L"B_TRAJECTORIES";
			this->B_TRAJECTORIES->Size = System::Drawing::Size(87, 17);
			this->B_TRAJECTORIES->TabIndex = 1;
			this->B_TRAJECTORIES->Text = L"Trajecctories";
			this->B_TRAJECTORIES->UseVisualStyleBackColor = true;
			this->B_TRAJECTORIES->CheckedChanged += gcnew System::EventHandler(this, &Recovery_Flight::B_TRAJECTORIES_CheckedChanged);
			// 
			// B_DETECTIONS
			// 
			this->B_DETECTIONS->AutoSize = true;
			this->B_DETECTIONS->Checked = true;
			this->B_DETECTIONS->CheckState = System::Windows::Forms::CheckState::Checked;
			this->B_DETECTIONS->ForeColor = System::Drawing::Color::Black;
			this->B_DETECTIONS->Location = System::Drawing::Point(27, 23);
			this->B_DETECTIONS->Name = L"B_DETECTIONS";
			this->B_DETECTIONS->Size = System::Drawing::Size(77, 17);
			this->B_DETECTIONS->TabIndex = 0;
			this->B_DETECTIONS->Text = L"Detections";
			this->B_DETECTIONS->UseVisualStyleBackColor = true;
			this->B_DETECTIONS->CheckedChanged += gcnew System::EventHandler(this, &Recovery_Flight::B_DETECTIONS_CheckedChanged);
			// 
			// VIEWER_TOOL_STRIP
			// 
			this->VIEWER_TOOL_STRIP->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->VIEWER_TOOL_STRIP->Dock = System::Windows::Forms::DockStyle::None;
			this->VIEWER_TOOL_STRIP->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->B_TOOL_EDIT,
					this->B_CALCULATE_DISTANCE, this->toolStripSeparator1, this->B_ZOOM_IN, this->B_ZOOM_OUT, this->toolStripSeparator2, this->toolStripButton2,
					this->B_RESET_VIEWER, this->B_CLEAR_VIEWER
			});
			this->VIEWER_TOOL_STRIP->Location = System::Drawing::Point(0, 0);
			this->VIEWER_TOOL_STRIP->Name = L"VIEWER_TOOL_STRIP";
			this->VIEWER_TOOL_STRIP->Size = System::Drawing::Size(162, 25);
			this->VIEWER_TOOL_STRIP->TabIndex = 216;
			// 
			// B_TOOL_EDIT
			// 
			this->B_TOOL_EDIT->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_TOOL_EDIT->Enabled = false;
			this->B_TOOL_EDIT->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_TOOL_EDIT.Image")));
			this->B_TOOL_EDIT->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_TOOL_EDIT->Name = L"B_TOOL_EDIT";
			this->B_TOOL_EDIT->Size = System::Drawing::Size(23, 22);
			this->B_TOOL_EDIT->ToolTipText = L"Edit";
			this->B_TOOL_EDIT->Click += gcnew System::EventHandler(this, &Recovery_Flight::B_TOOL_EDIT_Click);
			// 
			// B_CALCULATE_DISTANCE
			// 
			this->B_CALCULATE_DISTANCE->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_CALCULATE_DISTANCE->Enabled = false;
			this->B_CALCULATE_DISTANCE->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_CALCULATE_DISTANCE.Image")));
			this->B_CALCULATE_DISTANCE->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_CALCULATE_DISTANCE->Name = L"B_CALCULATE_DISTANCE";
			this->B_CALCULATE_DISTANCE->Size = System::Drawing::Size(23, 22);
			this->B_CALCULATE_DISTANCE->ToolTipText = L"Calculate Distance";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
			// 
			// B_ZOOM_IN
			// 
			this->B_ZOOM_IN->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_ZOOM_IN->Enabled = false;
			this->B_ZOOM_IN->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_ZOOM_IN.Image")));
			this->B_ZOOM_IN->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_ZOOM_IN->Name = L"B_ZOOM_IN";
			this->B_ZOOM_IN->Size = System::Drawing::Size(23, 22);
			this->B_ZOOM_IN->Text = L"B_ZOOM_IN";
			this->B_ZOOM_IN->Click += gcnew System::EventHandler(this, &Recovery_Flight::B_ZOOM_IN_Click);
			// 
			// B_ZOOM_OUT
			// 
			this->B_ZOOM_OUT->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_ZOOM_OUT->Enabled = false;
			this->B_ZOOM_OUT->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_ZOOM_OUT.Image")));
			this->B_ZOOM_OUT->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_ZOOM_OUT->Name = L"B_ZOOM_OUT";
			this->B_ZOOM_OUT->Size = System::Drawing::Size(23, 22);
			this->B_ZOOM_OUT->Text = L"B_ZOOM_OUT";
			this->B_ZOOM_OUT->Click += gcnew System::EventHandler(this, &Recovery_Flight::B_ZOOM_OUT_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton2->Enabled = false;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(23, 22);
			this->toolStripButton2->Text = L"toolStripButton2";
			this->toolStripButton2->Visible = false;
			// 
			// B_RESET_VIEWER
			// 
			this->B_RESET_VIEWER->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_RESET_VIEWER->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_RESET_VIEWER.Image")));
			this->B_RESET_VIEWER->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_RESET_VIEWER->Name = L"B_RESET_VIEWER";
			this->B_RESET_VIEWER->Size = System::Drawing::Size(23, 22);
			this->B_RESET_VIEWER->ToolTipText = L"Reset Viewer";
			this->B_RESET_VIEWER->Click += gcnew System::EventHandler(this, &Recovery_Flight::B_RESET_VIEWER_Click);
			// 
			// B_CLEAR_VIEWER
			// 
			this->B_CLEAR_VIEWER->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->B_CLEAR_VIEWER->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_CLEAR_VIEWER.Image")));
			this->B_CLEAR_VIEWER->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->B_CLEAR_VIEWER->Name = L"B_CLEAR_VIEWER";
			this->B_CLEAR_VIEWER->Size = System::Drawing::Size(23, 22);
			this->B_CLEAR_VIEWER->ToolTipText = L"Clear Viewer";
			// 
			// panel5
			// 
			this->panel5->BackColor = System::Drawing::Color::White;
			this->panel5->ForeColor = System::Drawing::Color::White;
			this->panel5->Location = System::Drawing::Point(19, 557);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(60, 4);
			this->panel5->TabIndex = 213;
			// 
			// B_SCALE_RE_FLIGHT_VIEWER
			// 
			this->B_SCALE_RE_FLIGHT_VIEWER->AutoSize = true;
			this->B_SCALE_RE_FLIGHT_VIEWER->BackColor = System::Drawing::Color::DarkGray;
			this->B_SCALE_RE_FLIGHT_VIEWER->ForeColor = System::Drawing::Color::Black;
			this->B_SCALE_RE_FLIGHT_VIEWER->Location = System::Drawing::Point(26, 568);
			this->B_SCALE_RE_FLIGHT_VIEWER->Name = L"B_SCALE_RE_FLIGHT_VIEWER";
			this->B_SCALE_RE_FLIGHT_VIEWER->Size = System::Drawing::Size(25, 13);
			this->B_SCALE_RE_FLIGHT_VIEWER->TabIndex = 211;
			this->B_SCALE_RE_FLIGHT_VIEWER->Text = L"500";
			this->B_SCALE_RE_FLIGHT_VIEWER->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label265
			// 
			this->label265->AutoSize = true;
			this->label265->BackColor = System::Drawing::Color::DarkGray;
			this->label265->ForeColor = System::Drawing::Color::Black;
			this->label265->Location = System::Drawing::Point(61, 568);
			this->label265->Name = L"label265";
			this->label265->Size = System::Drawing::Size(15, 13);
			this->label265->TabIndex = 212;
			this->label265->Text = L"m";
			// 
			// B_MAP_RE_FLIGHT_VIDEO
			// 
			this->B_MAP_RE_FLIGHT_VIDEO->BackColor = System::Drawing::Color::Black;
			this->B_MAP_RE_FLIGHT_VIDEO->Location = System::Drawing::Point(603, 143);
			this->B_MAP_RE_FLIGHT_VIDEO->Name = L"B_MAP_RE_FLIGHT_VIDEO";
			this->B_MAP_RE_FLIGHT_VIDEO->Size = System::Drawing::Size(624, 392);
			this->B_MAP_RE_FLIGHT_VIDEO->TabIndex = 131;
			this->B_MAP_RE_FLIGHT_VIDEO->TabStop = false;
			// 
			// groupBox115
			// 
			this->groupBox115->BackColor = System::Drawing::Color::DarkGray;
			this->groupBox115->Controls->Add(this->B_LOAD_RE_FLIGHT_DETECTION);
			this->groupBox115->Controls->Add(this->B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER);
			this->groupBox115->ForeColor = System::Drawing::Color::White;
			this->groupBox115->Location = System::Drawing::Point(606, 537);
			this->groupBox115->Name = L"groupBox115";
			this->groupBox115->Size = System::Drawing::Size(621, 46);
			this->groupBox115->TabIndex = 133;
			this->groupBox115->TabStop = false;
			this->groupBox115->Text = L"Detections:";
			// 
			// B_LOAD_RE_FLIGHT_DETECTION
			// 
			this->B_LOAD_RE_FLIGHT_DETECTION->ForeColor = System::Drawing::Color::Black;
			this->B_LOAD_RE_FLIGHT_DETECTION->Location = System::Drawing::Point(523, 11);
			this->B_LOAD_RE_FLIGHT_DETECTION->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LOAD_RE_FLIGHT_DETECTION->Name = L"B_LOAD_RE_FLIGHT_DETECTION";
			this->B_LOAD_RE_FLIGHT_DETECTION->Size = System::Drawing::Size(93, 27);
			this->B_LOAD_RE_FLIGHT_DETECTION->TabIndex = 11;
			this->B_LOAD_RE_FLIGHT_DETECTION->Text = L"Load Detection";
			this->B_LOAD_RE_FLIGHT_DETECTION->UseVisualStyleBackColor = true;
			this->B_LOAD_RE_FLIGHT_DETECTION->Click += gcnew System::EventHandler(this, &Recovery_Flight::B_LOAD_RE_FLIGHT_DETECTION_Click);
			// 
			// B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER
			// 
			this->B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER->Location = System::Drawing::Point(7, 15);
			this->B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER->Name = L"B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER";
			this->B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER->Size = System::Drawing::Size(511, 20);
			this->B_DETECTIONS_FOLDER_Of_RE_FLIGHT_VIEWER->TabIndex = 0;
			// 
			// groupBox114
			// 
			this->groupBox114->BackColor = System::Drawing::Color::DarkGray;
			this->groupBox114->Controls->Add(this->B_LOAD_MAP);
			this->groupBox114->Controls->Add(this->B_FILE_TOM_Of_RE_FLIGHT);
			this->groupBox114->ForeColor = System::Drawing::Color::White;
			this->groupBox114->Location = System::Drawing::Point(603, 589);
			this->groupBox114->Name = L"groupBox114";
			this->groupBox114->Size = System::Drawing::Size(624, 49);
			this->groupBox114->TabIndex = 132;
			this->groupBox114->TabStop = false;
			this->groupBox114->Text = L"True Obstacles-map (TOM):";
			// 
			// B_LOAD_MAP
			// 
			this->B_LOAD_MAP->ForeColor = System::Drawing::Color::Black;
			this->B_LOAD_MAP->Location = System::Drawing::Point(526, 14);
			this->B_LOAD_MAP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_LOAD_MAP->Name = L"B_LOAD_MAP";
			this->B_LOAD_MAP->Size = System::Drawing::Size(93, 27);
			this->B_LOAD_MAP->TabIndex = 10;
			this->B_LOAD_MAP->Text = L"Load Map";
			this->B_LOAD_MAP->UseVisualStyleBackColor = true;
			this->B_LOAD_MAP->Click += gcnew System::EventHandler(this, &Recovery_Flight::B_LOAD_MAP_Click);
			// 
			// B_FILE_TOM_Of_RE_FLIGHT
			// 
			this->B_FILE_TOM_Of_RE_FLIGHT->Location = System::Drawing::Point(6, 18);
			this->B_FILE_TOM_Of_RE_FLIGHT->Name = L"B_FILE_TOM_Of_RE_FLIGHT";
			this->B_FILE_TOM_Of_RE_FLIGHT->Size = System::Drawing::Size(515, 20);
			this->B_FILE_TOM_Of_RE_FLIGHT->TabIndex = 6;
			// 
			// B_PLAY_RE_FLIGHT_VIEWER
			// 
			this->B_PLAY_RE_FLIGHT_VIEWER->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_PLAY_RE_FLIGHT_VIEWER->FlatAppearance->BorderSize = 0;
			this->B_PLAY_RE_FLIGHT_VIEWER->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->B_PLAY_RE_FLIGHT_VIEWER->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->B_PLAY_RE_FLIGHT_VIEWER->ForeColor = System::Drawing::Color::Black;
			this->B_PLAY_RE_FLIGHT_VIEWER->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_PLAY_RE_FLIGHT_VIEWER.Image")));
			this->B_PLAY_RE_FLIGHT_VIEWER->Location = System::Drawing::Point(19, 602);
			this->B_PLAY_RE_FLIGHT_VIEWER->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_PLAY_RE_FLIGHT_VIEWER->Name = L"B_PLAY_RE_FLIGHT_VIEWER";
			this->B_PLAY_RE_FLIGHT_VIEWER->Size = System::Drawing::Size(44, 42);
			this->B_PLAY_RE_FLIGHT_VIEWER->TabIndex = 140;
			this->TOOL_TIP_PLAY->SetToolTip(this->B_PLAY_RE_FLIGHT_VIEWER, L"Play Viewer");
			this->B_PLAY_RE_FLIGHT_VIEWER->UseVisualStyleBackColor = false;
			this->B_PLAY_RE_FLIGHT_VIEWER->Click += gcnew System::EventHandler(this, &Recovery_Flight::B_PLAY_RE_FLIGHT_VIEWER_Click);
			// 
			// label251
			// 
			this->label251->AutoSize = true;
			this->label251->Location = System::Drawing::Point(538, 626);
			this->label251->Name = L"label251";
			this->label251->Size = System::Drawing::Size(36, 13);
			this->label251->TabIndex = 214;
			this->label251->Text = L"30 km";
			// 
			// label263
			// 
			this->label263->AutoSize = true;
			this->label263->Location = System::Drawing::Point(355, 626);
			this->label263->Name = L"label263";
			this->label263->Size = System::Drawing::Size(30, 13);
			this->label263->TabIndex = 213;
			this->label263->Text = L"1 km";
			// 
			// B_SCREEN_WIDTH_OF_VIEWER
			// 
			this->B_SCREEN_WIDTH_OF_VIEWER->Location = System::Drawing::Point(377, 609);
			this->B_SCREEN_WIDTH_OF_VIEWER->Maximum = 30;
			this->B_SCREEN_WIDTH_OF_VIEWER->Minimum = 1;
			this->B_SCREEN_WIDTH_OF_VIEWER->Name = L"B_SCREEN_WIDTH_OF_VIEWER";
			this->B_SCREEN_WIDTH_OF_VIEWER->Size = System::Drawing::Size(165, 45);
			this->B_SCREEN_WIDTH_OF_VIEWER->TabIndex = 211;
			this->B_SCREEN_WIDTH_OF_VIEWER->Value = 15;
			this->B_SCREEN_WIDTH_OF_VIEWER->Scroll += gcnew System::EventHandler(this, &Recovery_Flight::B_SCREEN_WIDTH_OF_RE_FLIGHT_VIEWER_Scroll);
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->ForeColor = System::Drawing::Color::Black;
			this->label50->Location = System::Drawing::Point(7, 672);
			this->label50->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(37, 13);
			this->label50->TabIndex = 216;
			this->label50->Text = L"Status";
			// 
			// B_RE_FLIGHT_MESSAGE
			// 
			this->B_RE_FLIGHT_MESSAGE->BackColor = System::Drawing::Color::White;
			this->B_RE_FLIGHT_MESSAGE->ForeColor = System::Drawing::Color::Black;
			this->B_RE_FLIGHT_MESSAGE->Location = System::Drawing::Point(45, 669);
			this->B_RE_FLIGHT_MESSAGE->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_RE_FLIGHT_MESSAGE->Name = L"B_RE_FLIGHT_MESSAGE";
			this->B_RE_FLIGHT_MESSAGE->ReadOnly = true;
			this->B_RE_FLIGHT_MESSAGE->Size = System::Drawing::Size(726, 20);
			this->B_RE_FLIGHT_MESSAGE->TabIndex = 215;
			// 
			// B_BROWSE_RE_FLIGHT_DIR
			// 
			this->B_BROWSE_RE_FLIGHT_DIR->RootFolder = System::Environment::SpecialFolder::MyDocuments;
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->B_ERROR_FUNCTION);
			this->groupBox9->ForeColor = System::Drawing::Color::White;
			this->groupBox9->Location = System::Drawing::Point(603, 2);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(624, 135);
			this->groupBox9->TabIndex = 218;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"Error function";
			// 
			// B_ERROR_FUNCTION
			// 
			this->B_ERROR_FUNCTION->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_ERROR_FUNCTION->BorderlineColor = System::Drawing::SystemColors::AppWorkspace;
			chartArea1->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea1->AxisX->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->Maximum = 600;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisX->Title = L"Step #";
			chartArea1->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea1->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea1->AxisY->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->Maximum = 1;
			chartArea1->AxisY->Minimum = 0;
			chartArea1->AxisY->Title = L"Normalized Error";
			chartArea1->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea1->AxisY2->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea1->AxisY2->Minimum = 0;
			chartArea1->BackColor = System::Drawing::Color::Black;
			chartArea1->BorderColor = System::Drawing::Color::White;
			chartArea1->Name = L"ChartArea1";
			this->B_ERROR_FUNCTION->ChartAreas->Add(chartArea1);
			this->B_ERROR_FUNCTION->Location = System::Drawing::Point(3, 19);
			this->B_ERROR_FUNCTION->Name = L"B_ERROR_FUNCTION";
			series1->BorderWidth = 2;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series1->Color = System::Drawing::Color::Yellow;
			series1->IsVisibleInLegend = false;
			series1->Name = L"error_function";
			this->B_ERROR_FUNCTION->Series->Add(series1);
			this->B_ERROR_FUNCTION->Size = System::Drawing::Size(613, 110);
			this->B_ERROR_FUNCTION->TabIndex = 28;
			this->B_ERROR_FUNCTION->Text = L"chart1";
			// 
			// B_STOP
			// 
			this->B_STOP->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_STOP->FlatAppearance->BorderSize = 0;
			this->B_STOP->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->B_STOP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_STOP->ForeColor = System::Drawing::Color::Black;
			this->B_STOP->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_STOP.Image")));
			this->B_STOP->Location = System::Drawing::Point(171, 605);
			this->B_STOP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_STOP->Name = L"B_STOP";
			this->B_STOP->Size = System::Drawing::Size(42, 36);
			this->B_STOP->TabIndex = 221;
			this->TOOL_TIP_STOP->SetToolTip(this->B_STOP, L"Stop Viewer");
			this->B_STOP->UseVisualStyleBackColor = false;
			this->B_STOP->Click += gcnew System::EventHandler(this, &Recovery_Flight::B_STOP_Click);
			// 
			// Operations_Timer
			// 
			this->Operations_Timer->Interval = 50;
			this->Operations_Timer->Tick += gcnew System::EventHandler(this, &Recovery_Flight::Operations_Timer_Tick);
			// 
			// B_STEP
			// 
			this->B_STEP->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)));
			this->B_STEP->FlatAppearance->BorderSize = 0;
			this->B_STEP->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->B_STEP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_STEP->ForeColor = System::Drawing::Color::Black;
			this->B_STEP->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"B_STEP.Image")));
			this->B_STEP->Location = System::Drawing::Point(81, 602);
			this->B_STEP->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->B_STEP->Name = L"B_STEP";
			this->B_STEP->Size = System::Drawing::Size(72, 42);
			this->B_STEP->TabIndex = 222;
			this->TOOL_TIP_STEP_BY_STEP->SetToolTip(this->B_STEP, L"Step by Step");
			this->B_STEP->UseVisualStyleBackColor = false;
			this->B_STEP->Click += gcnew System::EventHandler(this, &Recovery_Flight::B_STEP_Click);
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 22);
			this->toolStripButton1->ToolTipText = L"Edit";
			// 
			// Recovery_Flight
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkGray;
			this->ClientSize = System::Drawing::Size(1231, 692);
			this->Controls->Add(this->B_STEP);
			this->Controls->Add(this->B_STOP);
			this->Controls->Add(this->groupBox9);
			this->Controls->Add(this->label50);
			this->Controls->Add(this->B_RE_FLIGHT_MESSAGE);
			this->Controls->Add(this->label251);
			this->Controls->Add(this->label263);
			this->Controls->Add(this->B_SCREEN_WIDTH_OF_VIEWER);
			this->Controls->Add(this->B_PLAY_RE_FLIGHT_VIEWER);
			this->Controls->Add(this->groupBox115);
			this->Controls->Add(this->groupBox114);
			this->Controls->Add(this->B_MAP_RE_FLIGHT_VIDEO);
			this->Controls->Add(this->B_MAP_PANEL_RE_FLIGHT);
			this->Name = L"Recovery_Flight";
			this->Text = L"Recovery_Flight";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Recovery_Flight::Recovery_Flight_FormClosing);
			this->B_MAP_PANEL_RE_FLIGHT->ResumeLayout(false);
			this->B_MAP_PANEL_RE_FLIGHT->PerformLayout();
			this->B_VISIBLE_OBSTACLES->ResumeLayout(false);
			this->B_VISIBLE_OBSTACLES->PerformLayout();
			this->VIEWER_TOOL_STRIP->ResumeLayout(false);
			this->VIEWER_TOOL_STRIP->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_MAP_RE_FLIGHT_VIDEO))->EndInit();
			this->groupBox115->ResumeLayout(false);
			this->groupBox115->PerformLayout();
			this->groupBox114->ResumeLayout(false);
			this->groupBox114->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCREEN_WIDTH_OF_VIEWER))->EndInit();
			this->groupBox9->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_ERROR_FUNCTION))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		#pragma endregion


	//----------------------------------------------
	//				Variables
	//----------------------------------------------
	C_Radar_Viewer					Radar_Viewer;
	C_GUI_Status					GUI_Status;
	//
	//	0 - for play, 1- for pause, 2 - for stop
	//
	int								operation_mode;
	bool							flag;

	String^							Path;
	String^							returned_message;

	Bitmap^							image;
	//----------------------------------------------
	//				GUI Methods
	//----------------------------------------------
	private:
	void							My_Re_Flight_Message(String^ message_string);
	void							B_LOAD_MAP_Click(System::Object^  sender, System::EventArgs^  e);
	void							B_MAP_PANEL_RE_FLIGHT_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
	void							B_CLEAR_VIEWER_Click(System::Object^  sender, System::EventArgs^  e);
	void							Recovery_Flight_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);

	void							B_LOAD_RE_FLIGHT_DETECTION_Click(System::Object^  sender, System::EventArgs^  e);
	void							B_PLAY_RE_FLIGHT_VIEWER_Click(System::Object^  sender, System::EventArgs^  e);

	void							Operations_Timer_Tick(System::Object^  sender, System::EventArgs^  e);
	//-----------------------------------------------------------
	//			MAP Tab control Function
	//-----------------------------------------------------------
	int								mouse_x, mouse_y;
	void							B_MAP_PANEL_RE_FLIGHT_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	void							B_MAP_PANEL_RE_FLIGHT_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	void							B_MAP_PANEL_RE_FLIGHT_MouseLeave(System::Object^  sender, System::EventArgs^  e);
	void							B_MAP_PANEL_RE_FLIGHT_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	void							B_MAP_PANEL_RE_FLIGHT_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

	void							B_SCREEN_WIDTH_OF_RE_FLIGHT_VIEWER_Scroll(System::Object^  sender, System::EventArgs^  e);
	void							B_RESET_VIEWER_Click(System::Object^  sender, System::EventArgs^  e);

	void							B_ZOOM_IN_Click(System::Object^  sender, System::EventArgs^  e);
	void							B_ZOOM_OUT_Click(System::Object^  sender, System::EventArgs^  e);

	void							B_TOOL_EDIT_Click(System::Object^  sender, System::EventArgs^  e);

	void							B_STEP_Click(System::Object^  sender, System::EventArgs^  e);
	void							B_STOP_Click(System::Object^  sender, System::EventArgs^  e);

	void							B_DETECTIONS_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	void							B_TRAJECTORIES_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
};
}
