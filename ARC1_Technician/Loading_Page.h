#pragma once

namespace ARC1_Technician 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	typedef struct Data_Parameter
	{
		int Process;
		int Delay;
	}Data_Parameter;

	/// <summary>
	/// Summary for Loading_Page
	/// </summary>
	public ref class Loading_Page : public System::Windows::Forms::Form
	{
		public:
			Loading_Page();

		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~Loading_Page();
		private: System::ComponentModel::IContainer^			components;
		protected:
		private: System::Windows::Forms::Timer^					timer;
		private: System::ComponentModel::BackgroundWorker^		backgroundWorker;
		private: System::Windows::Forms::Label^					LBL_PERCENT;
		private: System::Windows::Forms::ProgressBar^			progress;
		private: System::Windows::Forms::PictureBox^			picboxPB;
		
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
			this->picboxPB = (gcnew System::Windows::Forms::PictureBox());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->LBL_PERCENT = (gcnew System::Windows::Forms::Label());
			this->progress = (gcnew System::Windows::Forms::ProgressBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picboxPB))->BeginInit();
			this->SuspendLayout();
			// 
			// picboxPB
			// 
			this->picboxPB->Location = System::Drawing::Point(12, 97);
			this->picboxPB->Name = L"picboxPB";
			this->picboxPB->Size = System::Drawing::Size(470, 50);
			this->picboxPB->TabIndex = 0;
			this->picboxPB->TabStop = false;
			// 
			// timer
			// 
			this->timer->Interval = 50;
			this->timer->Tick += gcnew System::EventHandler(this, &Loading_Page::timer_Tick);
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->WorkerReportsProgress = true;
			this->backgroundWorker->WorkerSupportsCancellation = true;
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Loading_Page::backgroundWorker_DoWork);
			this->backgroundWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Loading_Page::backgroundWorker_ProgressChanged);
			this->backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Loading_Page::backgroundWorker_RunWorkerCompleted);
			// 
			// LBL_PERCENT
			// 
			this->LBL_PERCENT->AutoSize = true;
			this->LBL_PERCENT->Location = System::Drawing::Point(194, 9);
			this->LBL_PERCENT->Name = L"LBL_PERCENT";
			this->LBL_PERCENT->Size = System::Drawing::Size(94, 13);
			this->LBL_PERCENT->TabIndex = 1;
			this->LBL_PERCENT->Text = L"Processing .... 0% ";
			// 
			// progress
			// 
			this->progress->Location = System::Drawing::Point(13, 36);
			this->progress->Name = L"progress";
			this->progress->Size = System::Drawing::Size(469, 23);
			this->progress->TabIndex = 2;
			// 
			// Loading_Page
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(494, 157);
			this->Controls->Add(this->progress);
			this->Controls->Add(this->LBL_PERCENT);
			this->Controls->Add(this->picboxPB);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Loading_Page";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Loding page... please wait";
			this->Load += gcnew System::EventHandler(this, &Loading_Page::Loading_Page_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picboxPB))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		#pragma endregion

		private:
			//----------------------------------------------
			//				Fields
			//----------------------------------------------
			//pb = ProgressBar
			double				pbUnit;
			int					pbWIDTH, 
								pbHEIGHT, 
								pbComplete;

			Bitmap^				bmp;
			Graphics^			g;

			Data_Parameter*		_inputParameter;
			//----------------------------------------------
			//				Methods
			//----------------------------------------------
			void				Loading_Page_Load(System::Object^  sender, System::EventArgs^  e);
			void				timer_Tick(System::Object^  sender, System::EventArgs^  e);
			void				simulateHeavyWork();

			void				backgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
			void				backgroundWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
			void				backgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
	};
}
