#pragma once

namespace ARC1_Technician 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Display_Polar
	/// </summary>
	public ref class Display_Polar : public System::Windows::Forms::Form
	{
	public:
		Display_Polar(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Display_Polar()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  B_POLAR_CHART;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Display_Polar::typeid));
			this->B_POLAR_CHART = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_POLAR_CHART))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// B_POLAR_CHART
			// 
			this->B_POLAR_CHART->BackColor = System::Drawing::Color::Black;
			this->B_POLAR_CHART->BorderlineColor = System::Drawing::Color::Black;
			chartArea1->AxisX->InterlacedColor = System::Drawing::Color::White;
			chartArea1->AxisX->Interval = 10;
			chartArea1->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea1->AxisX->IntervalOffset = 40;
			chartArea1->AxisX->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->AxisX->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->AxisX->IsLabelAutoFit = false;
			chartArea1->AxisX->IsReversed = true;
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->LabelStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea1->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea1->AxisX->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->MajorGrid->Interval = 0;
			chartArea1->AxisX->MajorGrid->IntervalOffset = 0;
			chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->Maximum = 20;
			chartArea1->AxisX->Minimum = -60;
			chartArea1->AxisX->MinorGrid->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->MinorTickMark->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->ScaleBreakStyle->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->ScrollBar->BackColor = System::Drawing::Color::White;
			chartArea1->AxisX->ScrollBar->ButtonColor = System::Drawing::Color::White;
			chartArea1->AxisX->ScrollBar->LineColor = System::Drawing::Color::White;
			chartArea1->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea1->AxisY->IsLabelAutoFit = false;
			chartArea1->AxisY->LabelStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea1->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->MajorTickMark->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->Maximum = 1000;
			chartArea1->AxisY->Minimum = 0;
			chartArea1->AxisY->MinorGrid->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->MinorTickMark->LineColor = System::Drawing::Color::White;
			chartArea1->AxisY->ScaleBreakStyle->MaxNumberOfBreaks = 4;
			chartArea1->BackColor = System::Drawing::Color::Black;
			chartArea1->Name = L"ChartArea1";
			this->B_POLAR_CHART->ChartAreas->Add(chartArea1);
			legend1->BackColor = System::Drawing::Color::Black;
			legend1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			legend1->ForeColor = System::Drawing::Color::White;
			legend1->IsTextAutoFit = false;
			legend1->Name = L"Legend1";
			this->B_POLAR_CHART->Legends->Add(legend1);
			this->B_POLAR_CHART->Location = System::Drawing::Point(3, -1);
			this->B_POLAR_CHART->Name = L"B_POLAR_CHART";
			series1->BorderColor = System::Drawing::Color::White;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Polar;
			series1->Color = System::Drawing::Color::Yellow;
			series1->LabelForeColor = System::Drawing::Color::White;
			series1->Legend = L"Legend1";
			series1->MarkerBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			series1->MarkerColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			series1->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Square;
			series1->Name = L"Wires";
			this->B_POLAR_CHART->Series->Add(series1);
			this->B_POLAR_CHART->Size = System::Drawing::Size(878, 440);
			this->B_POLAR_CHART->TabIndex = 0;
			this->B_POLAR_CHART->Text = L"chart1";
			// 
			// chart1
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chart1->Legends->Add(legend2);
			this->chart1->Location = System::Drawing::Point(725, 235);
			this->chart1->Name = L"chart1";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Radar;
			series2->Legend = L"Legend1";
			series2->Name = L"Series1";
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(300, 300);
			this->chart1->TabIndex = 1;
			this->chart1->Text = L"chart1";
			// 
			// Display_Polar
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(1061, 601);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->B_POLAR_CHART);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Display_Polar";
			this->Text = L"Polar";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->B_POLAR_CHART))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
