#ifndef C_UTM_COORDINATES_H
#define C_UTM_COORDINATES_H

#include "C_CartesianPoint.h"

//-----------------------------------------
//		Class:		C_Position
//----------------------------------------- 
public ref class C_UTM_Coordinates
{
	//-------------------------------------
	//				Fields 
	//-------------------------------------
	private:
	double latitude; //in degrees
	double longitude; //in degrees
	double altitude; //in degrees

	public:
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	C_UTM_Coordinates();
	//-------------------------------------
	//			Other Constructors in degrees
	//-------------------------------------
	C_UTM_Coordinates(double lat, double lon, double alt);
	//-------------------------------------
	//			Copy Constructor
	//-------------------------------------
	C_UTM_Coordinates(C_UTM_Coordinates % UTM_Coordinates_other);

	//-------------------------------------------
	//			Property: Latitude coordinate of UTM point in degrees
	//-------------------------------------------
	property double Latitude {double get(); void set(double latitude_other); }
//-------------------------------------------
//			Property: Longitude coordinate of UTM point in degrees
//-------------------------------------------
property double Longitude {double get(); void set(double longitude_other); }
//-------------------------------------------
//			Property: Altitude coordinate of UTM point in degrees
//-------------------------------------------
property double Altitude {double get(); void set(double altitude_other); }


#pragma region Methods
//------------------------------------------ -
//			methods
//-------------------------------------------
void Clear();
bool Is_Clear();
C_CartesianPoint Convert_UTM_To_ECEF();
void Convert_ECEF_To_UTM(C_CartesianPoint% ECEF_position);
C_UTM_Coordinates Line_point_projection(C_UTM_Coordinates point_1, C_UTM_Coordinates point_2);
#pragma endregion


#pragma region Operator Overloading
//-------------------------------------------
//			Operators
//-------------------------------------------
void operator=(double Number);
void operator=(C_UTM_Coordinates% UTM_Coordinates_other);
//-------------------------------------------
//	'-' operator between two UTM points returns the 
//	distance in cartesian NED coordinates
//-------------------------------------------
C_CartesianPoint operator-(C_UTM_Coordinates% UTM_Coordinates_other);
//-------------------------------------------
//	'+' operator between UTM point and NED offset
//	returns the new UTM point
//-------------------------------------------
C_UTM_Coordinates operator+(C_CartesianPoint% NED_offset);
//-------------------------------------------
//	'+' operator between two UTM points 
//	returns the new UTM point
//-------------------------------------------
C_UTM_Coordinates operator+(C_UTM_Coordinates% UTM_Coordinates_other);

#pragma endregion

};
#endif



