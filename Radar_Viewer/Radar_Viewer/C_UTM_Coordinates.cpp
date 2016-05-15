#include "C_UTM_Coordinates.h"
#include <math.h>


#define PI				3.14159265358979323846
#define	GOOD				0
#define FAULT				1
//-------------------------------------
// WGS84 ellipsoid constants 
//-------------------------------------
#define EQUATORIAL_RADIUS	6378137.0
#define POLAR_RADIUS		6356752.314
#define	FLATTENING_COEFF	0.003352810664747
#define ECCENTRICITY		8.1819190842622e-2  
#define	ECCENTRICITY_2ND	8.2094437949695676e-2

//-------------------------------------
//			Constructor
//-------------------------------------
C_UTM_Coordinates::C_UTM_Coordinates()
{
	latitude = 0;
	longitude = 0;
	altitude = 0;
}
//-------------------------------------
//			Other Constructors
//-------------------------------------
C_UTM_Coordinates::C_UTM_Coordinates(double lat, double lon, double alt) : latitude(lat), longitude(lon), altitude(alt)
{
}
//-------------------------------------
//			Copy Constructor
//-------------------------------------
C_UTM_Coordinates::C_UTM_Coordinates(C_UTM_Coordinates % UTM_Coordinates_other) :
latitude(UTM_Coordinates_other.latitude),
longitude(UTM_Coordinates_other.longitude),
altitude(UTM_Coordinates_other.altitude)
{
}


//-------------------------------------------
//			Property: Latitude coordinate of UTM point in degrees
//-------------------------------------------
double C_UTM_Coordinates::Latitude::get() { return latitude; }
void C_UTM_Coordinates::Latitude::set(double latitude_other) { latitude = latitude_other; }
//-------------------------------------------
//			Property: Longitude coordinate of UTM point in degrees
//-------------------------------------------
double C_UTM_Coordinates::Longitude::get() { return longitude; }
void C_UTM_Coordinates::Longitude::set(double longitude_other) { longitude = longitude_other; }
//-------------------------------------------
//			Property: Altitude coordinate of UTM point in degrees
//-------------------------------------------
double C_UTM_Coordinates::Altitude::get() { return altitude; }
void C_UTM_Coordinates::Altitude::set(double altitude_other) { altitude = altitude_other; }
// --------------------------------------------------
//  Clear
//  Alon Slapak		2.12.2015
// 	Description:	clear fields values to -1
//  Input Value:	
//  Return Value:  
// --------------------------------------------------
void C_UTM_Coordinates::Clear()
{
	latitude = 0;
	longitude = 0;
	altitude = 0;
}
// --------------------------------------------------
//  Is_Clear
//  Alon Slapak		2.12.2015
// 	Description:	check if values are cleard (0)
//  Input Value:	
//  Return Value:  
// --------------------------------------------------
bool C_UTM_Coordinates::Is_Clear()
{
	if ((latitude == 0) && (longitude == 0) && (altitude == 0))
	{
		return true;
}
else
{
	return false;
}
}

// --------------------------------------------------
//  Convert_UTM_To_ECEF
//  Haim Otachi 23.8.2015
// 	Description:	Convert latitude, longitude, and altitude in WGS84 to ECEF (Earth-centered Earth-fixed) X,Y,Z
//		latitude and longitude given in Degrees.
//		altitude should be given in meters
//		Given the Latitude, Longitude and Altitude in the Geodetic coordinate 
//		system, this subroutine computes the equivalent position x, y, z 
//		in the Geocentric coordinate system using the Helmert's formula.
//  Reference: see http://agamenon.tsc.uah.es/Asignaturas/it/rd/apuntes/RxControl_Manual.pdf
//     more references:
//	 Theoretical overvie: Section 2.3.2.1 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=0CCoQFjACahUKEwiN9puL-b7HAhWKwBQKHUWeCVc&url=http%3A%2F%2Fwww.springer.com%2Fcda%2Fcontent%2Fdocument%2Fcda_downloaddocument%2F9780857296344-c2.pdf%3FSGWID%3D0-0-45-1143141-p174116371&ei=sZnZVc3ZB4qBU8W8prgF&usg=AFQjCNEccSj6iWxvsA2_y-Ci0b_GOTNg-Q&sig2=JsvWGmL-5u5wsZZ8vG5WKg
//	 Functional description: page 42 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0CBwQFjAAahUKEwjZuIGJ-r7HAhXGPxQKHffKDg4&url=http%3A%2F%2Fwww.theatlas.org%2Findex.php%3Foption%3Dcom_phocadownload%26view%3Dcategory%26download%3D106%3Acoordinate-systems-functionality-description%26id%3D11%3Avol7-2007%26Itemid%3D77&ei=uJrZVdn8OMb_UPeVu3A&usg=AFQjCNEP66XtO2iqfiRgjRt3v1CCWQW0Xw&sig2=38xGVlDGF2lDVbSIrD52Fw 
//	 Also: https://en.wikipedia.org/wiki/Geographic_coordinate_conversion
//	Input Value:	
//  Return Value:  ECEF is C_CartesianPoint format (double x,y,z)
// --------------------------------------------------
C_CartesianPoint C_UTM_Coordinates::Convert_UTM_To_ECEF()
{
	C_CartesianPoint result;
	//-------------------------------------------
	// Conversion from degree into radians
	//-------------------------------------------
	double lat_RAD = latitude * (PI / 180.0);
	double lon_RAD = longitude * (PI / 180.0);
	//-------------------------------------------
	// Auxiliary from Helmert's formula
	//-------------------------------------------
	double rn = EQUATORIAL_RADIUS / sqrt(1 - ECCENTRICITY * ECCENTRICITY * sin(lat_RAD) * sin(lat_RAD));
	double Nc = rn * (1.0 - ECCENTRICITY * ECCENTRICITY);
	//-------------------------------------------
	// Calculate the ECEF X,Y,Z
	//-------------------------------------------
	double X = (rn + altitude)*cos(lat_RAD)*cos(lon_RAD);
	double Y = (rn + altitude)*cos(lat_RAD)*sin(lon_RAD);
	double Z = (Nc + altitude)*sin(lat_RAD);
	//-------------------------------------------
	// Substitute into ECEF cartesian structure
	//-------------------------------------------
	result.X = X;
	result.Y = Y;
	result.Z = Z;
	//-------------------------------------------
	// return ECEF cartesian structure
	//-------------------------------------------
	return result;
}
// --------------------------------------------------
//  Convert_ECEF_To_UTM
//  Haim Otachi 23.8.2015
// 	Description:	Convert ECEF (Earth-centered Earth-fixed) X,Y,Z in WGS84 to latitude, longitude, and altitude
//					latitude and longitude return in degrees.
//					altitude should be return in meters
//  Reference: see http://agamenon.tsc.uah.es/Asignaturas/it/rd/apuntes/RxControl_Manual.pdf
//     more references:
//	 Theoretical overvie https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=0CCoQFjACahUKEwiN9puL-b7HAhWKwBQKHUWeCVc&url=http%3A%2F%2Fwww.springer.com%2Fcda%2Fcontent%2Fdocument%2Fcda_downloaddocument%2F9780857296344-c2.pdf%3FSGWID%3D0-0-45-1143141-p174116371&ei=sZnZVc3ZB4qBU8W8prgF&usg=AFQjCNEccSj6iWxvsA2_y-Ci0b_GOTNg-Q&sig2=JsvWGmL-5u5wsZZ8vG5WKg
//	 Functional description: page 31 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0CBwQFjAAahUKEwjZuIGJ-r7HAhXGPxQKHffKDg4&url=http%3A%2F%2Fwww.theatlas.org%2Findex.php%3Foption%3Dcom_phocadownload%26view%3Dcategory%26download%3D106%3Acoordinate-systems-functionality-description%26id%3D11%3Avol7-2007%26Itemid%3D77&ei=uJrZVdn8OMb_UPeVu3A&usg=AFQjCNEP66XtO2iqfiRgjRt3v1CCWQW0Xw&sig2=38xGVlDGF2lDVbSIrD52Fw
//	 Also: https://en.wikipedia.org/wiki/Geographic_coordinate_conversion
//		see also:	Ward, H.R. 1973. Calculation of the factor km used in angle error equations.
//					Memo HRW - 250, Raytheon Co., Equipment Division,
//					Wayland, MA, May 7, 1973.
//	Input Value:	ECEF is C_CartesianPoint format (double x,y,z)
//  Return Value: 
// --------------------------------------------------
void C_UTM_Coordinates::Convert_ECEF_To_UTM(C_CartesianPoint% ECEF_position)
{
	//-----------------------------------------
	//		Ectract X,Y,Z from reference class
	//-----------------------------------------
	double X = ECEF_position.X;
	double Y = ECEF_position.Y;
	double Z = ECEF_position.Z;
	//-------------------------------------------
	// Auxiliary from Helmert's formula
	//-------------------------------------------
	double norm = sqrt(X*X + Y*Y);
	double theta = atan2(EQUATORIAL_RADIUS * Z, POLAR_RADIUS * norm);
	double E2 = pow(ECCENTRICITY, 2);
	double E2_2nd = pow(ECCENTRICITY_2ND, 2);

	//------------------------------------------------
	//		 Update UTM coordinate
	//------------------------------------------------
	double lat_RAD = atan2((Z + E2_2nd * POLAR_RADIUS * pow(sin(theta), 3)), norm - E2 * EQUATORIAL_RADIUS * pow(cos(theta), 3));
	double lon_RAD = atan2(Y, X);
	//------------------------------------------------
	//		 RAD -> Degs
	//------------------------------------------------
	latitude = lat_RAD / PI * 180;
	longitude = lon_RAD / PI * 180;
	altitude = norm / cos(lat_RAD) - EQUATORIAL_RADIUS / sqrt(1 - E2 * sin(lat_RAD) * sin(lat_RAD));
}
// --------------------------------------------------
//  operator=
//  Haim Otachi 23.8.2015
// 	Description:	= opeartor (assignment)
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value:  
// --------------------------------------------------
void C_UTM_Coordinates::operator=(C_UTM_Coordinates% UTM_Coordinates_other)
{
	latitude = UTM_Coordinates_other.latitude;
	longitude = UTM_Coordinates_other.longitude;
	altitude = UTM_Coordinates_other.altitude;
}
// --------------------------------------------------
//  operator=
//  Haim Otachi 23.8.2015
// 	Description:	= opeartor (assignment of a constant value)
// 	Reference: 
//	Input Value:	number
//  Return Value:  
// --------------------------------------------------
void C_UTM_Coordinates::operator=(double Number)
{
	latitude = Number;
	longitude = Number;
	altitude = Number;
}

// --------------------------------------------------
//  operator-
//  Alon Slapk	25.8.2015
// 	Description:	'-' operator between two UTM points returns the
//					distance in cartesian NED coordinates. Subtraction of two UTM 
//					points is done by translating to NED and then subtract in cartesian coordinates.
// 	Reference: This functino works as the Matlb function:
//			[xNorth, yEast, zDown] = geodetic2ned(LAT, LON, H, LAT0, LON0, H0, SPHEROID) 
//			which transforms point locations from geodetic coordinates
//			(LAT, LON, H) to local Cartesian coordinates(xNorth, yEast, zDown),
//			given a local coordinate system defined by the geodetic coordinates of
//			its origin(LAT0, LON0, H0).The geodetic coordinates refer to the
//			reference body specified by the spheroid object, SPHEROID.Ellipsoidal
//			heights H and H0 must be expressed in the same length unit as the
//			spheroid.Outputs xNorth, yEast, and zDown will be expressed in this
//			unit, also.The input latitude and longitude angles are in degrees by
//			default.
//	 Theoretical overvie: Section 2.3.2.2 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=0CCoQFjACahUKEwiN9puL-b7HAhWKwBQKHUWeCVc&url=http%3A%2F%2Fwww.springer.com%2Fcda%2Fcontent%2Fdocument%2Fcda_downloaddocument%2F9780857296344-c2.pdf%3FSGWID%3D0-0-45-1143141-p174116371&ei=sZnZVc3ZB4qBU8W8prgF&usg=AFQjCNEccSj6iWxvsA2_y-Ci0b_GOTNg-Q&sig2=JsvWGmL-5u5wsZZ8vG5WKg
//	 Functional description: page 31 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0CBwQFjAAahUKEwjZuIGJ-r7HAhXGPxQKHffKDg4&url=http%3A%2F%2Fwww.theatlas.org%2Findex.php%3Foption%3Dcom_phocadownload%26view%3Dcategory%26download%3D106%3Acoordinate-systems-functionality-description%26id%3D11%3Avol7-2007%26Itemid%3D77&ei=uJrZVdn8OMb_UPeVu3A&usg=AFQjCNEP66XtO2iqfiRgjRt3v1CCWQW0Xw&sig2=38xGVlDGF2lDVbSIrD52Fw
//	 Also: https://en.wikipedia.org/wiki/Geographic_coordinate_conversion
//	Input Value:	reference to other UTM class
//  Return Value:   Distance in cartesian coordinates
// --------------------------------------------------
C_CartesianPoint C_UTM_Coordinates::operator-(C_UTM_Coordinates% UTM_Coordinates_other)
{
	//--------------------------------------------------------
	// get reference Lat, Lon in degrees and alt
	//--------------------------------------------------------
	double ref_Lat = UTM_Coordinates_other.latitude * (PI / 180.0);
	double ref_Lon = UTM_Coordinates_other.longitude * (PI / 180.0);
	double ref_Alt = UTM_Coordinates_other.altitude;
	//--------------------------------------------------------
	//		(UTM point - reference point) UTM --> ECEF
	//--------------------------------------------------------
	C_CartesianPoint ECEF_offset;
	ECEF_offset = Convert_UTM_To_ECEF() - UTM_Coordinates_other.Convert_UTM_To_ECEF();
	double ECEF_x = ECEF_offset.X;
	double ECEF_y = ECEF_offset.Y;
	double ECEF_z = ECEF_offset.Z;
	//--------------------------------------------------------
	//		ECEF --> NED 
	//--------------------------------------------------------
	C_CartesianPoint NED_offset;
	NED_offset.X = -sin(ref_Lon) * ECEF_x + cos(ref_Lon) * ECEF_y;
	NED_offset.Y = -sin(ref_Lat)* cos(ref_Lon) * ECEF_x - sin(ref_Lat) * sin(ref_Lon) * ECEF_y + cos(ref_Lat) * ECEF_z;
	NED_offset.Z = cos(ref_Lat) * cos(ref_Lon) * ECEF_x + cos(ref_Lat) * sin(ref_Lon) * ECEF_y + sin(ref_Lat) * ECEF_z;

	return NED_offset;
}
// --------------------------------------------------
// operator+
//  Alon Slapk	26.8.2015
// 	Description:	'+' operator between UTM point and NED offset returns the new UTM point.
//					This is done by translating to NED and then adding in cartesian coordinates.
//					and then return to UTM.
// 	Reference:
//	 Theoretical overvie: Section 2.3.2.2 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=0CCoQFjACahUKEwiN9puL-b7HAhWKwBQKHUWeCVc&url=http%3A%2F%2Fwww.springer.com%2Fcda%2Fcontent%2Fdocument%2Fcda_downloaddocument%2F9780857296344-c2.pdf%3FSGWID%3D0-0-45-1143141-p174116371&ei=sZnZVc3ZB4qBU8W8prgF&usg=AFQjCNEccSj6iWxvsA2_y-Ci0b_GOTNg-Q&sig2=JsvWGmL-5u5wsZZ8vG5WKg
//	 Functional description: page 31 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0CBwQFjAAahUKEwjZuIGJ-r7HAhXGPxQKHffKDg4&url=http%3A%2F%2Fwww.theatlas.org%2Findex.php%3Foption%3Dcom_phocadownload%26view%3Dcategory%26download%3D106%3Acoordinate-systems-functionality-description%26id%3D11%3Avol7-2007%26Itemid%3D77&ei=uJrZVdn8OMb_UPeVu3A&usg=AFQjCNEP66XtO2iqfiRgjRt3v1CCWQW0Xw&sig2=38xGVlDGF2lDVbSIrD52Fw
//	 Also: https://en.wikipedia.org/wiki/Geographic_coordinate_conversion
//  Input value:	reference to a cartesian_offset
//  Return Value:	new UTM point
// --------------------------------------------------
C_UTM_Coordinates C_UTM_Coordinates::operator+(C_CartesianPoint% NED_offset)
{
	//--------------------------------------------------------
	// get reference Lat, Lon in degrees and alt
	//--------------------------------------------------------
	double ref_Lat = latitude * (PI / 180.0);
	double ref_Lon = longitude * (PI / 180.0);
	double ref_Alt = altitude;
	//--------------------------------------------------------
	//		NED --> ECEF
	//--------------------------------------------------------
	C_CartesianPoint ECEF_offset;
	ECEF_offset.X = -sin(ref_Lon) * NED_offset.X - sin(ref_Lat) * cos(ref_Lon) * NED_offset.Y + cos(ref_Lat) * cos(ref_Lon) * NED_offset.Z;
	ECEF_offset.Y = cos(ref_Lon) * NED_offset.X - sin(ref_Lat) * sin(ref_Lon) * NED_offset.Y + cos(ref_Lat) * sin(ref_Lon) * NED_offset.Z;
	ECEF_offset.Z = cos(ref_Lat) * NED_offset.Y + sin(ref_Lat) * NED_offset.Z;
	//--------------------------------------------------------
	//		(UTM point - reference point) UTM --> ECEF
	//--------------------------------------------------------
	C_CartesianPoint ECEF_Point;
	ECEF_Point = Convert_UTM_To_ECEF() + ECEF_offset;
	//--------------------------------------------------------
	//		ECEF --> UTM
	//--------------------------------------------------------
	C_UTM_Coordinates UTM_result;
	UTM_result.Convert_ECEF_To_UTM(ECEF_Point);
	return UTM_result;
}

//-------------------------------------------
//	'+' operator between two UTM points 
//	returns the new UTM point
//-------------------------------------------
C_UTM_Coordinates C_UTM_Coordinates::operator+(C_UTM_Coordinates% UTM_Coordinates_other)
{
	C_UTM_Coordinates UTM_result;

	UTM_result.latitude = latitude + UTM_Coordinates_other.latitude;
	UTM_result.longitude = longitude + UTM_Coordinates_other.longitude;
	UTM_result.altitude = altitude + UTM_Coordinates_other.altitude;

	return UTM_result;
}

C_UTM_Coordinates C_UTM_Coordinates::Line_point_projection(C_UTM_Coordinates point_1, C_UTM_Coordinates point_2)
{
	double t, x1, x2, y1, y2;
	C_UTM_Coordinates closest_point;

	x1 = (point_2.longitude - point_1.longitude);
	y1 = (point_2.latitude - point_1.latitude);
	x2 = (longitude - point_1.longitude);
	y2 = (latitude - point_1.latitude);
	t = (x1 * x2 + y1 * y2) / (x1 * x1 + y1 * y1);

	double newLon, newLat;

	newLon = point_1.longitude + t * (point_2.longitude - point_1.longitude);
	newLat = point_1.latitude + t * (point_2.latitude - point_1.latitude);

	closest_point.latitude = newLat;
	closest_point.longitude = newLon;

	return closest_point;
}




