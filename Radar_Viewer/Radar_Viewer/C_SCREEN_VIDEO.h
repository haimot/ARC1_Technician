#ifndef  C_SCREEN_VIDEO_H
#define  C_SCREEN_VIDEO_H

//	C_SCREEN_VIDEO
//	Alon Slapak
//	9.9.2015
//---------------------------------------
//		Using OPENCV for video capture
//---------------------------------------
//	0. Download 'OpenCV for Windows' from http://opencv.org/downloads.html. Should be the fle: 'opencv-2.4.9.exe'
//	1.	Install the 'opencv-2.4.9.exe' file. Extract to c:\
//	2.	Configure Windows:
//		a. My Computer > Properties > Advanced System Settings > Environment Variables > New and add new system variable:
//			Name: OPENCV_DIR
//			Value: C : \opencv\build\ (or other path that you like)
//		b. My Computer > Properties > Advanced System Settings > Environment Variables... > System variables > select Path
//			and press Edit button and add:
//			;%OPENCV_DIR%\x86\vc12\bin
//	3.	Configure Visual Studio Project:
//		a. In left tree menu select Configuration Properties > C/C++ > General > Additional Include Directories > Add:
//			$(OPENCV_DIR)\include 
//		b. In left tree menu select Configuration Properties > Linker > General > Additional Library Directories > Add:
//			$(OPENCV_DIR)\x86\vc12\lib 
//		c.  In left tree menu select Configuration Properties > Linker > Input > Additional Dependencies > select Edit
//			and add below lib files:
/*
opencv_calib3d249d.lib
opencv_contrib249d.lib
opencv_core249d.lib
opencv_features2d249d.lib
opencv_flann249d.lib
opencv_gpu249d.lib
opencv_highgui249d.lib
opencv_imgproc249d.lib
opencv_legacy249d.lib
opencv_ml249d.lib
opencv_nonfree249d.lib
opencv_objdetect249d.lib
opencv_ocl249d.lib
opencv_photo249d.lib
opencv_stitching249d.lib
opencv_superres249d.lib
opencv_ts249d.lib
opencv_video249d.lib
opencv_videostab249d.lib
*/
//	Comments:
//		1.	realease version, simple remove the 'd' after the version number (249)
//		2.	pdb warning: ignore. See: http://answers.opencv.org/question/23556/pdb-was-not-found-link-with-no-debug-info/
//				don't worry too much about it. indeed, the pdb's are not supplied with the prebuild libs. (that would blow up the download to gigabytes). 
//				you still can debug your own code, you just can't peek into the opencv libs while debugging.
//				if you still need them, rebuild the libs from src(cmake), this will generate the pdbs as well
//		3. If youi have warnings, such as ''fopen': This function or variable may be unsafe. 
//			Consider using fopen_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.":
//			This is not an error, it is a warning from your Microsoft compiler.
//			Select your project and click "Properties" in the context menu.
//			In the dialog, chose Configuration Properties->C / C++->Preprocessor
//			In the field PreprocessorDefinitions add; _CRT_SECURE_NO_WARNINGS to turn those warnings off.
//
//
//---------------------------------------
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"

using namespace System::Windows::Forms;
//-----------------------------------------
//		Class:	C_SCREEN_VIDEO
//-----------------------------------------
ref class C_SCREEN_VIDEO
{
	private:
	//------------------------------------
	//		Properties
	//------------------------------------
	CvCapture*				capture;
	IplImage*				frame;
	PictureBox^				picture_box;
	public:
	//------------------------------------
	//		Constructors/Destructor
	//------------------------------------
	C_SCREEN_VIDEO();
	~C_SCREEN_VIDEO();
	// --------------------------------------------------
	//  Set_Video_Panel  
	// 	Description:	set the pointer to the picture box 
	// 	Reference: 
	//  Input value:	pointer to a PictureBox PictureBox object
	//  Return Value: 
	// --------------------------------------------------
	void Set_Video_Panel(PictureBox^ picture_box_other);
	// --------------------------------------------------
	//  Clear_Video_Panel  
	// 	Description:	clear the picture box 
	// 	Reference: 
	//  Input value:	
	//  Return Value: 
	// --------------------------------------------------
	void Clear_Video_Panel();
	// --------------------------------------------------
	//  Set_Video_File  
	// 	Description:	Set the video file name to be displayed. 
	// 	Reference: 
	//  Input value:	pointer to a char string containing the video file name.
	//  Return Value: 
	// --------------------------------------------------
	void Set_Video_File(char* file_name_video_other);
	// --------------------------------------------------
	//  plot_frame_of_time  
	// 	Description:	plot the frame which with the given time index [Sec]
	//					From the begining of the viseo file.
	// 	Reference:		http://docs.opencv.org/modules/highgui/doc/reading_and_writing_images_and_video.html
	//  Input value:	time_stamp of the requested frame related to 
	//					the begining of the viso file which is 0:00 mSec
	//  Return Value: 
	// --------------------------------------------------
	void plot_frame_of_time(double time_index_SEC);
};
#endif

