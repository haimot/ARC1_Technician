#ifndef T_SIMULATOR_DATA_H
#define T_SIMULATOR_DATA_H

#define MAX_STRING_LENGTH				512

//-----------------------------------------
//		Struct:		T_Simulator_Data
//-----------------------------------------
typedef struct T_Simulator_Data
{
	double GPS_latitude;
	double GPS_longitude;
	double Meter_Per_Pixel;
	int Screen_Width;
	char OBSTACLES_file_name[MAX_STRING_LENGTH];
	char EXPERIMENT_directory[MAX_STRING_LENGTH];
	char DETECTIONS_folder[MAX_STRING_LENGTH];
	char MAP_image_file[MAX_STRING_LENGTH];
} T_Simulator_Data;

#endif

