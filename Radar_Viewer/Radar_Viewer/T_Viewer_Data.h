#ifndef T_Viewer_DATA_H
#define T_Viewer_DATA_H

#define MAX_STRING_LENGTH				512

//-----------------------------------------
//		Struct:		T_Viewer_Data
//-----------------------------------------
typedef struct T_Viewer_Data
{
	double GPS_latitude;
	double GPS_longitude;
	double Meter_Per_Pixel;
	int Screen_Width_meter;
	char OBSTACLES_file_name[MAX_STRING_LENGTH];
	char EXPERIMENT_directory[MAX_STRING_LENGTH];
	char DETECTIONS_folder[MAX_STRING_LENGTH];
} T_Viewer_Data;

#endif

