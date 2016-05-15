#include "C_SphericalPoint.h"
#include <cmath>

#define PI       3.14159265358979323846

//-------------------------------------
//			Other Constructors
//-------------------------------------
C_SphericalPoint::C_SphericalPoint(double Range, double Azimuth) : range(Range), azimuth(Azimuth), phi(PI / 2) {}
//-------------------------------------
//			Copy Constructor
//-------------------------------------
C_SphericalPoint::C_SphericalPoint(C_SphericalPoint% other) : range(other.range), azimuth(other.azimuth), phi(other.phi) {}


//-------------------------------------------
//			The Range of the point from specific reference point
//-------------------------------------------
double C_SphericalPoint::Range::get() { return range; }
void C_SphericalPoint::Range::set(double range_Other) { range = range_Other; }
//-------------------------------------------
//			The Angle created by this Range R
//-------------------------------------------
double C_SphericalPoint::Azimuth::get() { return azimuth; }
void C_SphericalPoint::Azimuth::set(double azimuth_Other) { azimuth = azimuth_Other; }
//-------------------------------------------
//			Phi coordinate of point
//-------------------------------------------
double C_SphericalPoint::Phi::get() { return phi; }
void C_SphericalPoint::Phi::set(double phi_other) { phi = PI / 2; }
//-------------------------------------------
//			Get/Set The Spherical Point Coordinate
//-------------------------------------------
void C_SphericalPoint::set_Spherical_Point(double r_other, double theta_other, double phi_other)
{
	Range = r_other;
	Azimuth = theta_other;
	phi = phi_other;
}


// --------------------------------------------------
//  operator+=
//  Haim Otachi 23.8.2015
// 	Description:	+= opeartor
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_SphericalPoint::operator+=(C_SphericalPoint% SphericalPoint_other)
{
	//-------------------------------------------
	//			New Point 
	//-------------------------------------------
	double NewX = range * cos(azimuth) + SphericalPoint_other.range * cos(SphericalPoint_other.azimuth);
	double NewY = range * sin(azimuth) + SphericalPoint_other.range * sin(SphericalPoint_other.azimuth);
	//-------------------------------------------
	//			Update the new data
	//------------------------------------------- 
	range = sqrt(pow(NewX, 2) + pow(NewY, 2));;
	azimuth = atan2(NewY, NewX);
}
// --------------------------------------------------
//  operator-=
//  Haim Otachi 23.8.2015
// 	Description:	-= opeartor 
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_SphericalPoint::operator-=(C_SphericalPoint% SphericalPoint_other)
{
	//-------------------------------------------
	//			New Point 
	//-------------------------------------------
	double NewX = range * cos(azimuth) - SphericalPoint_other.range * cos(SphericalPoint_other.azimuth);
	double NewY = range * sin(azimuth) - SphericalPoint_other.range * sin(SphericalPoint_other.azimuth);
	//-------------------------------------------
	//			Update the new data
	//------------------------------------------- 
	range = sqrt(pow(NewX, 2) + pow(NewY, 2));;
	azimuth = atan2(NewY, NewX);
}
// --------------------------------------------------
//  operator=
//  Haim Otachi 23.8.2015
// 	Description:	= opeartor   (assignment)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_SphericalPoint::operator=(C_SphericalPoint% SphericalPoint_other)
{
	range = SphericalPoint_other.range;
	azimuth = SphericalPoint_other.azimuth;
	phi = SphericalPoint_other.phi;
}

void C_SphericalPoint::operator=(int& Number)
{
	range = Number;
	azimuth = Number;
	phi = Number;
}

// --------------------------------------------------
//  Convert_Spherical_To_Cartesian
//  Haim Otachi 23.8.2015
// 	Description:	Convert Spherical Coordinate To Cartesian Coordinate
// 	Reference: 
//	Input Value:	constant integer
//  Return Value: 
// --------------------------------------------------
C_CartesianPoint C_SphericalPoint::Convert_Spherical_To_Cartesian()
{
	C_CartesianPoint CartesianPoint;
	//--------------------------------------------------------
	//	Calculate the  X, Y  and Z coordinates 
	//--------------------------------------------------------
	CartesianPoint.X = range * sin(phi) * cos(azimuth);
	CartesianPoint.Y = range * sin(phi) * sin(azimuth);
	CartesianPoint.Z = range * cos(phi);

	return CartesianPoint;
}
// --------------------------------------------------
//  Convert_Cartesian_To_Spherical
//  Alon Slapak 24.8.2015
// 	Description:	Convert Cartesian Coordinate To Spherical Coordinate
// 	Reference: 
//	Input Value:	constant integer
//  Return Value: 
// --------------------------------------------------
void C_SphericalPoint::Convert_Cartesian_To_Spherical(C_CartesianPoint% cartesian_point)
{
	range = sqrt(pow(cartesian_point.X, 2.0) + pow(cartesian_point.Y, 2.0) + pow(cartesian_point.Z, 2.0));
	azimuth = atan2(cartesian_point.Y, cartesian_point.X);
	phi = acos(cartesian_point.Z/ Range);
}




