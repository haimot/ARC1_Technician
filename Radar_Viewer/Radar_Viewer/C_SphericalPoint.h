#ifndef C_SPHERICAL_POINT_H
#define C_SPHERICAL_POINT_H

#include "C_CartesianPoint.h"

//-----------------------------------------
//		Class:		CartesianPoint
//-----------------------------------------

public ref class C_SphericalPoint
{
	//-----------------------------------------
	//				Fields 
	//-----------------------------------------
	private:
	double range; //in meters
	double azimuth; //in radians
	double phi; //in radians

	public:
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	C_SphericalPoint() {}
//-------------------------------------
//			Other Constructors
//-------------------------------------
C_SphericalPoint(double Range, double Azimuth);
//-------------------------------------
//			Copy Constructor
//-------------------------------------
C_SphericalPoint(C_SphericalPoint% other);

//-------------------------------------------
//			The Range of the point from specific reference point
//-------------------------------------------
property double Range {double get(); void set(double range_Other); }
//-------------------------------------------
//			The Angle created by this Range R
//-------------------------------------------
property double Azimuth {double get(); void set(double azimuth_Other); }
//-------------------------------------------
//			Phi coordinate of point
//-------------------------------------------
property double Phi {double get(); void set(double phi_Other); }
//-------------------------------------------
//			Get/Set The Spherical Point Coordinate
//-------------------------------------------
void set_Spherical_Point(double r_other, double Azimuth_other, double phi_other);

//-------------------------------------------
//				  Methods
//-------------------------------------------
C_CartesianPoint Convert_Spherical_To_Cartesian();
void Convert_Cartesian_To_Spherical(C_CartesianPoint% cartesian_point);

//-------------------------------------------
//				  Operator Overloading
//-------------------------------------------
void operator=(C_SphericalPoint% SphericalPoint_other);
void operator+=(C_SphericalPoint% SphericalPoint_other);
void operator-=(C_SphericalPoint% SphericalPoint_other);
void operator=(int& Number);

};
#endif  // of CARTESIANPOINT_H



