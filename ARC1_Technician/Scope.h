#pragma once
#include "ARC1_Technician.h"
#include "C_DSP_Communication.h"
#include <math.h>
#include <stdio.h>


namespace ARC1_Technician 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Scope
	/// </summary>
	public ref class Scope : public System::Windows::Forms::Form
	{
		public:
			Scope(void);

		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~Scope();

		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_SCOPE_H_LEFT;
		protected:
		private: System::ComponentModel::IContainer^  components;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_SCOPE_H_RIGHT;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_SCOPE_V_LEFT;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_SCOPE_V_RIGHT;
		private: System::Windows::Forms::TextBox^  B_SENSOR_TIME;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::Panel^  panel1;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::Label^  label1006;
		private: System::Windows::Forms::TextBox^  B_SENSOR_ALTITUDE;
		private: System::Windows::Forms::TextBox^  B_SENSOR_LATITUDE;
		private: System::Windows::Forms::Label^  label77;
		private: System::Windows::Forms::Label^  label81;
		private: System::Windows::Forms::TextBox^  B_SENSOR_LONGITUDE;
		private: System::Windows::Forms::Panel^  B_LEGEND_2b;
		private: System::Windows::Forms::Panel^  B_LEGEND_2d;
		private: System::Windows::Forms::Label^  B_LEGEND_2a;
		private: System::Windows::Forms::Label^  B_LEGEND_2c;
		private: System::Windows::Forms::Label^  B_LEGEND_TX1;
		private: System::Windows::Forms::Label^  B_LEGEND_TX2;
		private: System::Windows::Forms::Panel^  panel2;
		protected:

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series11 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series12 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series13 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series14 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series15 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series16 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Scope::typeid));
			this->B_SCOPE_H_LEFT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->B_SCOPE_H_RIGHT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->B_SCOPE_V_LEFT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->B_SCOPE_V_RIGHT = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->B_SENSOR_TIME = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label1006 = (gcnew System::Windows::Forms::Label());
			this->B_SENSOR_ALTITUDE = (gcnew System::Windows::Forms::TextBox());
			this->B_SENSOR_LATITUDE = (gcnew System::Windows::Forms::TextBox());
			this->label77 = (gcnew System::Windows::Forms::Label());
			this->label81 = (gcnew System::Windows::Forms::Label());
			this->B_SENSOR_LONGITUDE = (gcnew System::Windows::Forms::TextBox());
			this->B_LEGEND_2b = (gcnew System::Windows::Forms::Panel());
			this->B_LEGEND_2d = (gcnew System::Windows::Forms::Panel());
			this->B_LEGEND_2a = (gcnew System::Windows::Forms::Label());
			this->B_LEGEND_2c = (gcnew System::Windows::Forms::Label());
			this->B_LEGEND_TX1 = (gcnew System::Windows::Forms::Label());
			this->B_LEGEND_TX2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_H_LEFT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_H_RIGHT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_V_LEFT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_V_RIGHT))->BeginInit();
			this->SuspendLayout();
			// 
			// B_SCOPE_H_LEFT
			// 
			this->B_SCOPE_H_LEFT->BackColor = System::Drawing::Color::Black;
			chartArea1->AxisX->Interval = 100;
			chartArea1->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea1->AxisX->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->Maximum = 1000;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisX->ScaleBreakStyle->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->Title = L"Range [m]";
			chartArea1->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea1->AxisY->Interval = 10;
			chartArea1->AxisY->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->AxisY->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea1->AxisY->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->Maximum = 0;
			chartArea1->AxisY->MaximumAutoSize = 80;
			chartArea1->AxisY->Minimum = -80;
			chartArea1->AxisY->ScaleBreakStyle->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->Title = L"Amplitude [dB]";
			chartArea1->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea1->BackColor = System::Drawing::Color::Black;
			chartArea1->BackGradientStyle = System::Windows::Forms::DataVisualization::Charting::GradientStyle::LeftRight;
			chartArea1->BackHatchStyle = System::Windows::Forms::DataVisualization::Charting::ChartHatchStyle::BackwardDiagonal;
			chartArea1->BackImageTransparentColor = System::Drawing::Color::Black;
			chartArea1->BackSecondaryColor = System::Drawing::Color::Black;
			chartArea1->BorderColor = System::Drawing::Color::White;
			chartArea1->Name = L"ChartArea1";
			this->B_SCOPE_H_LEFT->ChartAreas->Add(chartArea1);
			legend1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			legend1->Enabled = false;
			legend1->LegendStyle = System::Windows::Forms::DataVisualization::Charting::LegendStyle::Row;
			legend1->Name = L"Legend1";
			this->B_SCOPE_H_LEFT->Legends->Add(legend1);
			this->B_SCOPE_H_LEFT->Location = System::Drawing::Point(5, 12);
			this->B_SCOPE_H_LEFT->Name = L"B_SCOPE_H_LEFT";
			series1->BorderWidth = 2;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Color = System::Drawing::Color::Lime;
			series1->Legend = L"Legend1";
			series1->MarkerBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			series1->Name = L"Single1";
			series1->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series2->BorderWidth = 2;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Color = System::Drawing::Color::Yellow;
			series2->Legend = L"Legend1";
			series2->MarkerBorderColor = System::Drawing::Color::Red;
			series2->Name = L"Average1";
			series2->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series3->BorderWidth = 2;
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Color = System::Drawing::Color::Red;
			series3->Legend = L"Legend1";
			series3->Name = L"Single2";
			series4->BorderWidth = 2;
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Color = System::Drawing::Color::Aqua;
			series4->Legend = L"Legend1";
			series4->Name = L"Average2";
			this->B_SCOPE_H_LEFT->Series->Add(series1);
			this->B_SCOPE_H_LEFT->Series->Add(series2);
			this->B_SCOPE_H_LEFT->Series->Add(series3);
			this->B_SCOPE_H_LEFT->Series->Add(series4);
			this->B_SCOPE_H_LEFT->Size = System::Drawing::Size(493, 271);
			this->B_SCOPE_H_LEFT->TabIndex = 0;
			this->B_SCOPE_H_LEFT->Text = L"H - left";
			title1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			title1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			title1->Name = L"Title1";
			title1->Text = L"H - left";
			this->B_SCOPE_H_LEFT->Titles->Add(title1);
			// 
			// B_SCOPE_H_RIGHT
			// 
			this->B_SCOPE_H_RIGHT->BackColor = System::Drawing::Color::Black;
			chartArea2->AxisX->Interval = 100;
			chartArea2->AxisX->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea2->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea2->AxisX->LineColor = System::Drawing::Color::White;
			chartArea2->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea2->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea2->AxisX->Maximum = 1000;
			chartArea2->AxisX->Minimum = 0;
			chartArea2->AxisX->Title = L"Range [m]";
			chartArea2->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea2->AxisY->Interval = 10;
			chartArea2->AxisY->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea2->AxisY->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea2->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea2->AxisY->LineColor = System::Drawing::Color::White;
			chartArea2->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea2->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea2->AxisY->Maximum = 0;
			chartArea2->AxisY->Minimum = -80;
			chartArea2->AxisY->Title = L"Amplitude [dB]";
			chartArea2->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea2->BackColor = System::Drawing::Color::Black;
			chartArea2->Name = L"ChartArea1";
			this->B_SCOPE_H_RIGHT->ChartAreas->Add(chartArea2);
			legend2->Enabled = false;
			legend2->Name = L"Legend1";
			this->B_SCOPE_H_RIGHT->Legends->Add(legend2);
			this->B_SCOPE_H_RIGHT->Location = System::Drawing::Point(484, 12);
			this->B_SCOPE_H_RIGHT->Name = L"B_SCOPE_H_RIGHT";
			series5->BorderWidth = 2;
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series5->Color = System::Drawing::Color::Lime;
			series5->Legend = L"Legend1";
			series5->Name = L"Single1";
			series6->BorderWidth = 2;
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series6->Color = System::Drawing::Color::Yellow;
			series6->Legend = L"Legend1";
			series6->Name = L"Average1";
			series7->BorderWidth = 2;
			series7->ChartArea = L"ChartArea1";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series7->Color = System::Drawing::Color::Red;
			series7->Legend = L"Legend1";
			series7->Name = L"Single2";
			series8->BorderWidth = 2;
			series8->ChartArea = L"ChartArea1";
			series8->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series8->Color = System::Drawing::Color::Aqua;
			series8->Legend = L"Legend1";
			series8->Name = L"Average2";
			this->B_SCOPE_H_RIGHT->Series->Add(series5);
			this->B_SCOPE_H_RIGHT->Series->Add(series6);
			this->B_SCOPE_H_RIGHT->Series->Add(series7);
			this->B_SCOPE_H_RIGHT->Series->Add(series8);
			this->B_SCOPE_H_RIGHT->Size = System::Drawing::Size(493, 271);
			this->B_SCOPE_H_RIGHT->TabIndex = 1;
			this->B_SCOPE_H_RIGHT->Text = L"H - left";
			title2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			title2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			title2->Name = L"Title1";
			title2->Text = L"H - right";
			this->B_SCOPE_H_RIGHT->Titles->Add(title2);
			// 
			// B_SCOPE_V_LEFT
			// 
			this->B_SCOPE_V_LEFT->BackColor = System::Drawing::Color::Black;
			chartArea3->AxisX->Interval = 100;
			chartArea3->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea3->AxisX->LineColor = System::Drawing::Color::White;
			chartArea3->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea3->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea3->AxisX->Maximum = 1000;
			chartArea3->AxisX->Minimum = 0;
			chartArea3->AxisX->Title = L"Range [m]";
			chartArea3->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea3->AxisY->Interval = 10;
			chartArea3->AxisY->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea3->AxisY->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea3->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea3->AxisY->LineColor = System::Drawing::Color::White;
			chartArea3->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea3->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea3->AxisY->Maximum = 0;
			chartArea3->AxisY->Minimum = -80;
			chartArea3->AxisY->Title = L"Amplitude [dB]";
			chartArea3->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea3->BackColor = System::Drawing::Color::Black;
			chartArea3->Name = L"ChartArea1";
			this->B_SCOPE_V_LEFT->ChartAreas->Add(chartArea3);
			legend3->Enabled = false;
			legend3->Name = L"Legend1";
			this->B_SCOPE_V_LEFT->Legends->Add(legend3);
			this->B_SCOPE_V_LEFT->Location = System::Drawing::Point(5, 289);
			this->B_SCOPE_V_LEFT->Name = L"B_SCOPE_V_LEFT";
			series9->BorderWidth = 2;
			series9->ChartArea = L"ChartArea1";
			series9->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series9->Color = System::Drawing::Color::Lime;
			series9->Legend = L"Legend1";
			series9->Name = L"Single1";
			series10->BorderWidth = 2;
			series10->ChartArea = L"ChartArea1";
			series10->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series10->Color = System::Drawing::Color::Yellow;
			series10->Legend = L"Legend1";
			series10->Name = L"Average1";
			series11->BorderWidth = 2;
			series11->ChartArea = L"ChartArea1";
			series11->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series11->Color = System::Drawing::Color::Red;
			series11->Legend = L"Legend1";
			series11->Name = L"Single2";
			series12->BorderWidth = 2;
			series12->ChartArea = L"ChartArea1";
			series12->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series12->Color = System::Drawing::Color::Aqua;
			series12->Legend = L"Legend1";
			series12->Name = L"Average2";
			this->B_SCOPE_V_LEFT->Series->Add(series9);
			this->B_SCOPE_V_LEFT->Series->Add(series10);
			this->B_SCOPE_V_LEFT->Series->Add(series11);
			this->B_SCOPE_V_LEFT->Series->Add(series12);
			this->B_SCOPE_V_LEFT->Size = System::Drawing::Size(493, 271);
			this->B_SCOPE_V_LEFT->TabIndex = 2;
			this->B_SCOPE_V_LEFT->Text = L"H - left";
			title3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			title3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			title3->Name = L"Title1";
			title3->Text = L"V - left";
			this->B_SCOPE_V_LEFT->Titles->Add(title3);
			// 
			// B_SCOPE_V_RIGHT
			// 
			this->B_SCOPE_V_RIGHT->BackColor = System::Drawing::Color::Black;
			chartArea4->AxisX->Interval = 100;
			chartArea4->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea4->AxisX->LineColor = System::Drawing::Color::White;
			chartArea4->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea4->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea4->AxisX->Maximum = 1000;
			chartArea4->AxisX->Minimum = 0;
			chartArea4->AxisX->Title = L"Range [m]";
			chartArea4->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea4->AxisY->Interval = 10;
			chartArea4->AxisY->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea4->AxisY->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea4->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea4->AxisY->LineColor = System::Drawing::Color::White;
			chartArea4->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea4->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea4->AxisY->Maximum = 0;
			chartArea4->AxisY->Minimum = -80;
			chartArea4->AxisY->Title = L"Amplitude [dB]";
			chartArea4->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea4->BackColor = System::Drawing::Color::Black;
			chartArea4->Name = L"ChartArea1";
			this->B_SCOPE_V_RIGHT->ChartAreas->Add(chartArea4);
			legend4->Enabled = false;
			legend4->Name = L"Legend1";
			this->B_SCOPE_V_RIGHT->Legends->Add(legend4);
			this->B_SCOPE_V_RIGHT->Location = System::Drawing::Point(484, 289);
			this->B_SCOPE_V_RIGHT->Name = L"B_SCOPE_V_RIGHT";
			series13->BorderWidth = 2;
			series13->ChartArea = L"ChartArea1";
			series13->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series13->Color = System::Drawing::Color::Lime;
			series13->Legend = L"Legend1";
			series13->Name = L"Single1";
			series14->BorderWidth = 2;
			series14->ChartArea = L"ChartArea1";
			series14->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series14->Color = System::Drawing::Color::Yellow;
			series14->Legend = L"Legend1";
			series14->Name = L"Average1";
			series15->BorderWidth = 2;
			series15->ChartArea = L"ChartArea1";
			series15->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series15->Color = System::Drawing::Color::Red;
			series15->Legend = L"Legend1";
			series15->Name = L"Single2";
			series16->BorderWidth = 2;
			series16->ChartArea = L"ChartArea1";
			series16->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series16->Color = System::Drawing::Color::Aqua;
			series16->Legend = L"Legend1";
			series16->Name = L"Average2";
			this->B_SCOPE_V_RIGHT->Series->Add(series13);
			this->B_SCOPE_V_RIGHT->Series->Add(series14);
			this->B_SCOPE_V_RIGHT->Series->Add(series15);
			this->B_SCOPE_V_RIGHT->Series->Add(series16);
			this->B_SCOPE_V_RIGHT->Size = System::Drawing::Size(493, 271);
			this->B_SCOPE_V_RIGHT->TabIndex = 3;
			this->B_SCOPE_V_RIGHT->Text = L"H - left";
			title4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			title4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			title4->Name = L"Title1";
			title4->Text = L"V - right";
			this->B_SCOPE_V_RIGHT->Titles->Add(title4);
			// 
			// B_SENSOR_TIME
			// 
			this->B_SENSOR_TIME->BackColor = System::Drawing::Color::White;
			this->B_SENSOR_TIME->Enabled = false;
			this->B_SENSOR_TIME->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_SENSOR_TIME->ForeColor = System::Drawing::Color::Yellow;
			this->B_SENSOR_TIME->Location = System::Drawing::Point(1034, 66);
			this->B_SENSOR_TIME->Name = L"B_SENSOR_TIME";
			this->B_SENSOR_TIME->Size = System::Drawing::Size(96, 26);
			this->B_SENSOR_TIME->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Yellow;
			this->label1->Location = System::Drawing::Point(279, 555);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 25);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Average";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Lime;
			this->label2->Location = System::Drawing::Point(126, 555);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(72, 25);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Single";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(947, 69);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(87, 20);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Time [Sec]:";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Yellow;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->ForeColor = System::Drawing::Color::Blue;
			this->panel1->Location = System::Drawing::Point(367, 567);
			this->panel1->Margin = System::Windows::Forms::Padding(1);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(63, 5);
			this->panel1->TabIndex = 8;
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::Lime;
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->ForeColor = System::Drawing::Color::Black;
			this->panel2->Location = System::Drawing::Point(202, 568);
			this->panel2->Margin = System::Windows::Forms::Padding(1);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(63, 5);
			this->panel2->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(1069, 36);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(43, 20);
			this->label4->TabIndex = 10;
			this->label4->Text = L"GPS";
			// 
			// label1006
			// 
			this->label1006->AutoSize = true;
			this->label1006->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1006->ForeColor = System::Drawing::Color::White;
			this->label1006->Location = System::Drawing::Point(974, 137);
			this->label1006->Name = L"label1006";
			this->label1006->Size = System::Drawing::Size(58, 20);
			this->label1006->TabIndex = 100;
			this->label1006->Text = L"LONG:";
			// 
			// B_SENSOR_ALTITUDE
			// 
			this->B_SENSOR_ALTITUDE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_SENSOR_ALTITUDE->Location = System::Drawing::Point(1034, 168);
			this->B_SENSOR_ALTITUDE->Name = L"B_SENSOR_ALTITUDE";
			this->B_SENSOR_ALTITUDE->ReadOnly = true;
			this->B_SENSOR_ALTITUDE->Size = System::Drawing::Size(96, 26);
			this->B_SENSOR_ALTITUDE->TabIndex = 98;
			this->B_SENSOR_ALTITUDE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_SENSOR_LATITUDE
			// 
			this->B_SENSOR_LATITUDE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_SENSOR_LATITUDE->Location = System::Drawing::Point(1034, 100);
			this->B_SENSOR_LATITUDE->Name = L"B_SENSOR_LATITUDE";
			this->B_SENSOR_LATITUDE->ReadOnly = true;
			this->B_SENSOR_LATITUDE->Size = System::Drawing::Size(96, 26);
			this->B_SENSOR_LATITUDE->TabIndex = 96;
			this->B_SENSOR_LATITUDE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label77
			// 
			this->label77->AutoSize = true;
			this->label77->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label77->ForeColor = System::Drawing::Color::White;
			this->label77->Location = System::Drawing::Point(990, 171);
			this->label77->Name = L"label77";
			this->label77->Size = System::Drawing::Size(42, 20);
			this->label77->TabIndex = 99;
			this->label77->Text = L"ALT:";
			// 
			// label81
			// 
			this->label81->AutoSize = true;
			this->label81->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label81->ForeColor = System::Drawing::Color::White;
			this->label81->Location = System::Drawing::Point(990, 103);
			this->label81->Name = L"label81";
			this->label81->Size = System::Drawing::Size(42, 20);
			this->label81->TabIndex = 95;
			this->label81->Text = L"LAT:";
			// 
			// B_SENSOR_LONGITUDE
			// 
			this->B_SENSOR_LONGITUDE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_SENSOR_LONGITUDE->Location = System::Drawing::Point(1034, 134);
			this->B_SENSOR_LONGITUDE->Name = L"B_SENSOR_LONGITUDE";
			this->B_SENSOR_LONGITUDE->ReadOnly = true;
			this->B_SENSOR_LONGITUDE->Size = System::Drawing::Size(96, 26);
			this->B_SENSOR_LONGITUDE->TabIndex = 97;
			this->B_SENSOR_LONGITUDE->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// B_LEGEND_2b
			// 
			this->B_LEGEND_2b->BackColor = System::Drawing::Color::Red;
			this->B_LEGEND_2b->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->B_LEGEND_2b->ForeColor = System::Drawing::Color::Black;
			this->B_LEGEND_2b->Location = System::Drawing::Point(808, 567);
			this->B_LEGEND_2b->Margin = System::Windows::Forms::Padding(1);
			this->B_LEGEND_2b->Name = L"B_LEGEND_2b";
			this->B_LEGEND_2b->Size = System::Drawing::Size(63, 5);
			this->B_LEGEND_2b->TabIndex = 182;
			// 
			// B_LEGEND_2d
			// 
			this->B_LEGEND_2d->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->B_LEGEND_2d->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->B_LEGEND_2d->ForeColor = System::Drawing::Color::Blue;
			this->B_LEGEND_2d->Location = System::Drawing::Point(973, 566);
			this->B_LEGEND_2d->Margin = System::Windows::Forms::Padding(1);
			this->B_LEGEND_2d->Name = L"B_LEGEND_2d";
			this->B_LEGEND_2d->Size = System::Drawing::Size(63, 5);
			this->B_LEGEND_2d->TabIndex = 181;
			// 
			// B_LEGEND_2a
			// 
			this->B_LEGEND_2a->AutoSize = true;
			this->B_LEGEND_2a->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_LEGEND_2a->ForeColor = System::Drawing::Color::Red;
			this->B_LEGEND_2a->Location = System::Drawing::Point(732, 555);
			this->B_LEGEND_2a->Name = L"B_LEGEND_2a";
			this->B_LEGEND_2a->Size = System::Drawing::Size(72, 25);
			this->B_LEGEND_2a->TabIndex = 180;
			this->B_LEGEND_2a->Text = L"Single";
			// 
			// B_LEGEND_2c
			// 
			this->B_LEGEND_2c->AutoSize = true;
			this->B_LEGEND_2c->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_LEGEND_2c->ForeColor = System::Drawing::Color::Aqua;
			this->B_LEGEND_2c->Location = System::Drawing::Point(885, 554);
			this->B_LEGEND_2c->Name = L"B_LEGEND_2c";
			this->B_LEGEND_2c->Size = System::Drawing::Size(92, 25);
			this->B_LEGEND_2c->TabIndex = 179;
			this->B_LEGEND_2c->Text = L"Average";
			// 
			// B_LEGEND_TX1
			// 
			this->B_LEGEND_TX1->AutoSize = true;
			this->B_LEGEND_TX1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_LEGEND_TX1->ForeColor = System::Drawing::Color::White;
			this->B_LEGEND_TX1->Location = System::Drawing::Point(0, 553);
			this->B_LEGEND_TX1->Name = L"B_LEGEND_TX1";
			this->B_LEGEND_TX1->Size = System::Drawing::Size(125, 25);
			this->B_LEGEND_TX1->TabIndex = 183;
			this->B_LEGEND_TX1->Text = L"TX Circular:";
			// 
			// B_LEGEND_TX2
			// 
			this->B_LEGEND_TX2->AutoSize = true;
			this->B_LEGEND_TX2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->B_LEGEND_TX2->ForeColor = System::Drawing::Color::White;
			this->B_LEGEND_TX2->Location = System::Drawing::Point(633, 555);
			this->B_LEGEND_TX2->Name = L"B_LEGEND_TX2";
			this->B_LEGEND_TX2->Size = System::Drawing::Size(71, 25);
			this->B_LEGEND_TX2->TabIndex = 184;
			this->B_LEGEND_TX2->Text = L"TX  V:";
			// 
			// Scope
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(1136, 588);
			this->ControlBox = false;
			this->Controls->Add(this->B_LEGEND_TX2);
			this->Controls->Add(this->B_LEGEND_TX1);
			this->Controls->Add(this->B_LEGEND_2b);
			this->Controls->Add(this->B_LEGEND_2d);
			this->Controls->Add(this->B_LEGEND_2a);
			this->Controls->Add(this->B_LEGEND_2c);
			this->Controls->Add(this->label1006);
			this->Controls->Add(this->B_SENSOR_ALTITUDE);
			this->Controls->Add(this->B_SENSOR_LATITUDE);
			this->Controls->Add(this->label77);
			this->Controls->Add(this->label81);
			this->Controls->Add(this->B_SENSOR_LONGITUDE);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->B_SENSOR_TIME);
			this->Controls->Add(this->B_SCOPE_V_RIGHT);
			this->Controls->Add(this->B_SCOPE_V_LEFT);
			this->Controls->Add(this->B_SCOPE_H_RIGHT);
			this->Controls->Add(this->B_SCOPE_H_LEFT);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Scope";
			this->Text = L"A-Scope";
			this->Load += gcnew System::EventHandler(this, &Scope::Scope_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_H_LEFT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_H_RIGHT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_V_LEFT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_SCOPE_V_RIGHT))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		#pragma endregion

		public:
			void	Clear_data(void);
			void	plot_data_1a(double *Samples_buffer, int start_range, int end_range, int step_range);
			void	plot_data_1b(double *Samples_buffer, int start_range, int end_range, int step_range);
			void	plot_data_2a(double *Samples_buffer, int start_range, int end_range, int step_range);
			void	plot_data_2b(double *Samples_buffer, int start_range, int end_range, int step_range);
			void	show_GPS(String^ time, String^ latit, String^ longit, String^ altit);
			void	set_mode(E_LEGEND_MODE legend_mode);

			void	Scope_Load(System::Object^  sender, System::EventArgs^  e);

	};
}
