#include "C_SCREEN_VIDEO.h"

using namespace System::Drawing;
//--------------------------------------------
// Declaring a fake structure to avoid C++/CLI linker warning
//http://stackoverflow.com/questions/7103679/c-visual-studio-2010-not-linking-native-static-library
//--------------------------------------------
struct CvCapture{};

// --------------------------------------------------
//  C_SCREEN_VIDEO  
//  Alon Slapak 7.9.2015
// 	Description:	Constructor
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
C_SCREEN_VIDEO::C_SCREEN_VIDEO()
{
	//------------------------------
	//		Insert default values
	//------------------------------
	capture = nullptr;
	frame = nullptr;
	picture_box = gcnew PictureBox();
}
// --------------------------------------------------
//  C_SCREEN_VIDEO  
//  Alon Slapak 8.9.2015
// 	Description:	Destructor
// 	Reference: 
//  Input value:
//  Return Value: 
// --------------------------------------------------
C_SCREEN_VIDEO::~C_SCREEN_VIDEO()
{
	pin_ptr<CvCapture*> p;
	p = &capture;
	cvReleaseCapture(p);
}

// --------------------------------------------------
//  Set_Video_Panel  
//  Alon Slapak 7.9.2015
// 	Description:	set the pointer to the picture box 
// 	Reference: 
//  Input value:	picture_box_other
//  Return Value: 
// --------------------------------------------------
void C_SCREEN_VIDEO::Set_Video_Panel(PictureBox^ picture_box_other)
{
	picture_box = picture_box_other;
	picture_box->SizeMode = PictureBoxSizeMode::StretchImage;
}
// --------------------------------------------------
//  Clear_Video_Panel  
// 	Description:	clear the picture box 
// 	Reference: 
//  Input value:	
//  Return Value: 
// --------------------------------------------------
void C_SCREEN_VIDEO::Clear_Video_Panel()
{
	delete picture_box->Image;
	picture_box->Image = nullptr;
}
// --------------------------------------------------
//  Set_Video_File  
//  Alon Slapak 7.9.2015
// 	Description:	Set the video file name to be displayed. 
// 	Reference: 
//  Input value:	pointer to a char string containing the video file name.
//  Return Value: 
// --------------------------------------------------
void C_SCREEN_VIDEO::Set_Video_File(char* file_name_video_other)
{
	capture = cvCaptureFromFile(file_name_video_other);
}

// --------------------------------------------------
//  plot_frame_of_time  
//  Alon Slapak 7.9.2015
// 	Description:	plot the frame which with the given time index [Sec]
//					From the begining of the viseo file.
// 	Reference:		http://docs.opencv.org/modules/highgui/doc/reading_and_writing_images_and_video.html
//  Input value:	time_stamp of the requested frame related to 
//					the begining of the viso file which is 0:00 mSec
//  Return Value: 
// --------------------------------------------------
void C_SCREEN_VIDEO::plot_frame_of_time(double time_index_SEC)
{
	//------------------------------------------
	//	Move the capture pointer to the requested frame using time index in mSec
	//------------------------------------------
	cvSetCaptureProperty(capture, CV_CAP_PROP_POS_MSEC, time_index_SEC * 1000);
	//------------------------------------------
	//	Capture frame from file
	//------------------------------------------
	frame = cvQueryFrame(capture);
	//------------------------------------------
	//
	//------------------------------------------
	if (frame != NULL)
	{
		picture_box->Image = gcnew Bitmap(frame->width, frame->height, frame->widthStep, Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) frame->imageData);
		picture_box->Refresh();
}
}




