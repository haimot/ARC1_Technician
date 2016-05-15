#include "Loading_Page.h"
#include "Recovery_Flight.h"
#include <msclr\marshal.h>

using namespace msclr::interop;
namespace ARC1_Technician
{
	Loading_Page::Loading_Page()
	{
		InitializeComponent();
		
		////get picboxPB dimension
		//pbWIDTH = picboxPB->Width;
		//pbHEIGHT = picboxPB->Height;

		//pbUnit = pbWIDTH / 100.0;

		////pbComplete - This is equal to work completed in % [min = 0 max = 100]
		//pbComplete = 0;

		////create bitmap
		//bmp = gcnew Bitmap(pbWIDTH, pbHEIGHT);
		//
		//// start the 'timer' 
		//timer->Start();
	}

	Loading_Page::~Loading_Page()
	{
		if (components)
		{
			delete components;
		}

		//timer->Stop();
	}

	void Loading_Page::Loading_Page_Load(System::Object^  sender, System::EventArgs^  e)
	{
		if (backgroundWorker->IsBusy)
		{
			backgroundWorker->CancelAsync();
		}
		else
		{
			_inputParameter->Delay = 100;
			_inputParameter->Process = 1200;

			// Start the background worker (execute the background worker doWork())
			backgroundWorker->RunWorkerAsync();
		}
	}
	void Loading_Page::timer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		////graphics
		//g = Graphics::FromImage(bmp);

		////clear graphics
		//g->Clear(Color::LightSkyBlue);

		////draw progressbar
		//g->FillRectangle(Brushes::CornflowerBlue, Rectangle(0, 0, (int)(pbComplete * pbUnit), pbHEIGHT));

		////draw % complete
		//g->DrawString(gcnew String(pbComplete + "%"), gcnew System::Drawing::Font("Arial", pbHEIGHT / 2), Brushes::Black, PointF(pbWIDTH / 2 - pbHEIGHT, pbHEIGHT / 10));

		////load bitmap in picturebox picboxPB
		//picboxPB->Image = bmp;

		////update pbComplete
		////Note!
		////To keep things simple I am adding +1 to pbComplete every 50ms
		////You can change this as per your requirement :)
		//pbComplete++;
		//if (pbComplete > 100)
		//{
		//	//dispose
		//	//g->Dispose();
		//	timer->Stop();
		//}
	}
	void Loading_Page::simulateHeavyWork()
	{
		Threading::Thread::Sleep(100);
		//Recovery_Flight  recovery_flight;
	}


	void Loading_Page::backgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
	{
		//for (int i = 0; i < 100; i++)
		//{
		//	//simulateHeavyWork();
		//	backgroundWorker->ReportProgress(i);
		//}
		//Data_Parameter dp = dynamic_cast<Data_Parameter%>(*e->Argument);
		//int process = (dynamic_cast<Data_Parameter%>(*e->Argument)).Process;
		////int delay = (dynamic_cast<Data_Parameter%>(*e->Argument)).Delay;
		////int index = 1;
		//try
		//{
		//	//for (size_t i = 0; i < process; i++)
		//	//{
		//	//	if (!backgroundWorker->CancellationPending)
		//	//	{
		//	//		backgroundWorker->ReportProgress(index++ * 100 / process, String::Format("Process data {0}", i));
		//	//		Threading::Thread::Sleep(delay); // used to simulate length of operation

		//	//		Recovery_Flight  recovery_flight;
		//	//	}
		//	//}
		//}
		//catch (Exception^ ex)
		//{
		//	backgroundWorker->CancelAsync();
		//	MessageBox::Show(ex->Message, "Message", MessageBoxButtons::OK, MessageBoxIcon::Error);
		//}
	}
	void Loading_Page::backgroundWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
	{
		// this is updated from doWork. Its where GUI components are update
		// receives updates after 100 ms
		progress->Value = e->ProgressPercentage;
		LBL_PERCENT->Text = String::Format("Processing...{0}%", e->ProgressPercentage.ToString());
		progress->Update();
	}
	void Loading_Page::backgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
	{
		MessageBox::Show("Loading page has been completed.", "Messeage", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}

