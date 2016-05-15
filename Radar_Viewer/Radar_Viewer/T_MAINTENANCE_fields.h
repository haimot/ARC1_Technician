#ifndef C_MAINTENANCE_FIELDS_H
#define C_MAINTENANCE_FIELDS_H
//-----------------------------------------
//		MISC. parameters
//-----------------------------------------
#define MAX_STRING_LENGTH			512
//-----------------------------------------
//		Struct:		T_MAINTENANCE_fields
//-----------------------------------------
typedef struct T_MAINTENANCE_fields
{
	int			reset_after_boot_upload;
	char		outFile_directory_OMR[MAX_STRING_LENGTH];
	char		outFile_directory_DET[MAX_STRING_LENGTH];
	char		outFile_directory_CHAB[MAX_STRING_LENGTH];
	char		outFile_directory_MCU[MAX_STRING_LENGTH];
	char		outFile_directory_RF_MCU[MAX_STRING_LENGTH];
} T_MAINTENANCE_fields;

#endif