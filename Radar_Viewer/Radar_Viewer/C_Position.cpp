//-----------------------------------------
//		This is the main DLL file.
//-----------------------------------------
#include "C_Position.h"
#include <math.h>

#define PI			3.14159265358979323846
//-----------------------------------------
//		Display
//-----------------------------------------
#define SCREEN_SIZE_X					600
#define SCREEN_SIZE_Y					600
//-----------------------------------------
//		Misc.
//-----------------------------------------
#define	GOOD							0
#define FAULT							1

namespace ROD_Position
{
	#pragma region Constructors
		//-------------------------------------
		//			Constructors
		//-------------------------------------
		C_Position::C_Position()
		{
			//-------------------------------------
			//			Screen position
			//-------------------------------------
			Screen_in_UTM_Position.Clear();
			Screen_in_UTM_North = 0;
			//-------------------------------------
			//			RADAR position
			//-------------------------------------
			Radar_in_UTM_Position.Clear();
			Radar_in_UTM_North = 0;
			//-------------------------------------
			//			Auxiliaries
			//-------------------------------------
			meter_per_pixel = 1;
		}
		C_Position::C_Position(double lat, double lon)
		{
			Object_in_UTM_position.Latitude = lat;
			Object_in_UTM_position.Longitude = lon;
			Object_in_UTM_position.Altitude = 0;
		}
		C_Position::C_Position(double x, double y, double z)
		{
			Object_in_Cartesian_Position.X = x;
			Object_in_Cartesian_Position.Y = y;
			Object_in_Cartesian_Position.Z = z;
		}
		C_Position::C_Position(C_UTM_Coordinates Screen_in_UTM_Position_other)
		{
			Screen_in_UTM_Position = Screen_in_UTM_Position_other;
		}
		C_Position::C_Position(C_UTM_Coordinates Screen_in_UTM_Position_other, C_UTM_Coordinates Radar_in_UTM_Position_other)
		{
			Screen_in_UTM_Position = Screen_in_UTM_Position_other;
			Radar_in_UTM_Position = Radar_in_UTM_Position_other;
		}
		C_Position::C_Position(C_CartesianPoint CartesianPoint_other)
		{
			Object_in_Cartesian_Position = CartesianPoint_other;
		}
		C_Position::C_Position(C_SphericalPoint SphericalPoint_other)
		{
			Object_in_Spherical_Position = SphericalPoint_other;
		}
		C_Position::C_Position(C_Point2DInt Point2DInt_other)
		{
			Object_in_Screen_Position = Point2DInt_other;
		}
		//-------------------------------------
		//			Copy Constructors
		//-------------------------------------
		C_Position::C_Position(C_Position% Position_other)
		{
			//-------------------------------------
			//			Object coordinates
			//-------------------------------------
			Object_in_UTM_position = Position_other.Object_in_UTM_position;
			Object_in_Cartesian_Position = Position_other.Object_in_Cartesian_Position;
			Object_in_Spherical_Position = Position_other.Object_in_Spherical_Position;
			Object_in_Screen_Position = Position_other.Object_in_Screen_Position;

			Object_in_NED_Position = Position_other.Object_in_NED_Position;
			//-------------------------------------
			//			Relative coordinates 
			//-------------------------------------
			Screen_in_UTM_Position = Position_other.Screen_in_UTM_Position;
			Screen_in_UTM_North = Position_other.Screen_in_UTM_North;

			Radar_in_UTM_Position = Position_other.Radar_in_UTM_Position;
			Radar_in_UTM_North = Position_other.Radar_in_UTM_North;

			meter_per_pixel = Position_other.meter_per_pixel;
		}
	#pragma endregion

	#pragma region Set And Get

	#pragma region Object coordinates
		//-------------------------------------------
		//			Get/Set Object coordinates: UTM Coordinate
		//-------------------------------------------
		C_UTM_Coordinates C_Position::get_Object_in_UTM_Position() { return Object_in_UTM_position; }
		void C_Position::set_Object_in_UTM_Position(double lat, double lon, double alt)
		{
			//-------------------------------------------
			// if screen is not initialized yet, initialize to Object to avoid 
			// error in UTM differences 
			// TODO: add clear and is_clear
			//-------------------------------------------
			if (Screen_in_UTM_Position.Is_Clear())
			{
				Screen_in_UTM_Position.Latitude = lat;
				Screen_in_UTM_Position.Longitude = lon;
				Screen_in_UTM_Position.Altitude = alt;
			}
			//-------------------------------------------
			//		Substitute the object
			//-------------------------------------------
			Object_in_UTM_position.Latitude = lat;
			Object_in_UTM_position.Longitude = lon;
			Object_in_UTM_position.Altitude = alt;

			Convert_UTM_To_NED();
			Convert_NED_To_ALL();
		}
		void C_Position::set_Object_in_UTM_Position(C_UTM_Coordinates% UTM_Coordinates_Other)
		{
			Object_in_UTM_position = UTM_Coordinates_Other;

			Convert_UTM_To_NED();
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set Object coordinates: Cartesian Point
		//-------------------------------------------
		C_CartesianPoint C_Position::get_Object_in_Cartesian_Position() { return Object_in_Cartesian_Position; }
		void C_Position::set_Object_in_Cartesian_Position(double x, double y, double z)
		{
			Object_in_Cartesian_Position.X = x;
			Object_in_Cartesian_Position.Y = y;
			Object_in_Cartesian_Position.Z = z;

			Convert_RADAR_Cartesian_To_NED();
			Convert_NED_To_ALL();
		}
		void C_Position::set_Object_in_Cartesian_Position(C_CartesianPoint% CartesianPoint_other)
		{
			Object_in_Cartesian_Position = CartesianPoint_other;

			Convert_RADAR_Cartesian_To_NED();
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set Object coordinates: Spherical Point
		//-------------------------------------------
		C_SphericalPoint C_Position::get_Object_in_Spherica_Position() { return Object_in_Spherical_Position; }
		void C_Position::set_Object_in_Spherica_Position(double Range, double Azimuth, double phi)
		{
			Object_in_Spherical_Position.Range = Range;
			Object_in_Spherical_Position.Azimuth = Azimuth;
			Object_in_Spherical_Position.Phi = phi;

			Convert_RADAR_Spherical_To_NED();
			Convert_NED_To_ALL();

		}
		void C_Position::set_Object_in_Spherica_Position(C_SphericalPoint% SphericalPoint_other)
		{
			Object_in_Spherical_Position = SphericalPoint_other;

			Convert_RADAR_Spherical_To_NED();
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set Object coordinates: Screen Coordinates
		//-------------------------------------------
		C_Point2DInt C_Position::get_Object_in_Screen_Position() { return Object_in_Screen_Position; }
		void C_Position::set_Object_in_Screen_Position(int screen_x, int screen_y)
		{
			Object_in_Screen_Position.Screen_X = screen_x;
			Object_in_Screen_Position.Screen_Y = screen_y;

			Convert_Screen_To_NED();
			Convert_NED_To_ALL();
		}

		void C_Position::set_Object_in_Screen_Position(C_Point2DInt% Screen_coordinates_other)
		{
			Object_in_Screen_Position = Screen_coordinates_other;

			Convert_Screen_To_NED();
			Convert_NED_To_ALL();
		}
	#pragma endregion

	#pragma region relative coordinates
		//-------------------------------------------
		//			Get/Set relative coordinates: Screen_in_UTM_Position
		//-------------------------------------------
		C_UTM_Coordinates C_Position::get_Screen_in_UTM_Position() { return Screen_in_UTM_Position; }
		void C_Position::set_Screen_in_UTM_Position(double Latitude, double Longitude)
		{
			C_UTM_Coordinates old_screen_utm_origin = Screen_in_UTM_Position;

			Screen_in_UTM_Position.Latitude = Latitude;
			Screen_in_UTM_Position.Longitude = Longitude;
			Screen_in_UTM_Position.Altitude = 0;

			Object_in_NED_Position -= Screen_in_UTM_Position - old_screen_utm_origin;
			Convert_NED_To_ALL();
		}
		void C_Position::set_Screen_in_UTM_Position(C_UTM_Coordinates% Screen_in_UTM_Position_other)
		{
			C_UTM_Coordinates old_screen_utm_origin = Screen_in_UTM_Position;
			Screen_in_UTM_Position = Screen_in_UTM_Position_other;
			Object_in_NED_Position -= Screen_in_UTM_Position - old_screen_utm_origin;
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set relative coordinates: Screen in UTM North
		//-------------------------------------------
		double C_Position::get_Screen_in_UTM_North() { return Screen_in_UTM_North; }
		void C_Position::set_Screen_in_UTM_North(double angle)
		{
			Screen_in_UTM_North = angle;
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set relative coordinates: Radar_in_UTM_Position
		//-------------------------------------------
		C_UTM_Coordinates C_Position::get_Radar_in_UTM_Position() { return Radar_in_UTM_Position; }
		void C_Position::set_Radar_in_UTM_Position(double Latitude, double Longitude, double Altitude)
		{
			Radar_in_UTM_Position.Latitude = Latitude;
			Radar_in_UTM_Position.Longitude = Longitude;
			Radar_in_UTM_Position.Altitude = Altitude;
			Convert_NED_To_ALL();
		}
		void C_Position::set_Radar_in_UTM_Position(C_UTM_Coordinates% Radar_in_UTM_Position_other)
		{
			Radar_in_UTM_Position = Radar_in_UTM_Position_other;
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set relative coordinates: Radar in UTM North
		//-------------------------------------------
		double C_Position::get_Radar_in_UTM_North() { return Radar_in_UTM_North; }
		void C_Position::set_Radar_in_UTM_North(double angle)
		{
			Radar_in_UTM_North = angle;
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set relative coordinates: Meters per pixel
		//-------------------------------------------
		double C_Position::get_Meter_Per_Pixel() { return meter_per_pixel; }
		void C_Position::set_Meter_Per_Pixel(double meter_per_pixel_other)
		{
			meter_per_pixel = meter_per_pixel_other;
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set Latitude of utm coordinate
		//-------------------------------------------
		double C_Position::Latitude::get() { return Object_in_UTM_position.Latitude; }
		void C_Position::Latitude::set(double Latitude_Other)
		{
			Object_in_UTM_position.Latitude = Latitude_Other;

			Convert_UTM_To_NED();
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set Longitude of utm coordinate
		//-------------------------------------------
		double C_Position::Longitude::get() { return Object_in_UTM_position.Longitude; }
		void C_Position::Longitude::set(double Longitude_Other)
		{
			Object_in_UTM_position.Longitude = Longitude_Other;

			Convert_UTM_To_NED();
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set altitude of utm coordinate
		//-------------------------------------------
		double C_Position::Altitude::get() { return Object_in_UTM_position.Altitude; }
		void C_Position::Altitude::set(double Altitude_Other)
		{
			Object_in_UTM_position.Altitude = Altitude_Other;

			Convert_UTM_To_NED();
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set X pixel of screen coordinate
		//-------------------------------------------
		int C_Position::Screen_X::get() { return Object_in_Screen_Position.Screen_X; }
		void C_Position::Screen_X::set(int Screen_X_Other)
		{
			Object_in_Screen_Position.Screen_X = Screen_X_Other;

			Convert_Screen_To_NED();
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set Y pixel of screen coordinate
		//-------------------------------------------
		int C_Position::Screen_Y::get() { return Object_in_Screen_Position.Screen_Y; }
		void C_Position::Screen_Y::set(int Screen_Y_Other)
		{
			Object_in_Screen_Position.Screen_Y = Screen_Y_Other;

			Convert_Screen_To_NED();
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set Range of Spherical Coordinates
		//-------------------------------------------
		double C_Position::Get_Range() { return Object_in_Spherical_Position.Range; }
		void C_Position::Set_Range(double Range_Other)
		{
			Object_in_Spherical_Position.Range = Range_Other;

			Convert_RADAR_Spherical_To_NED();
			Convert_NED_To_ALL();
		}
		//-------------------------------------------
		//			Get/Set Theta of Spherical Coordinates
		//-------------------------------------------
		double C_Position::Get_Azimuth() { return Object_in_Spherical_Position.Azimuth; }
		void C_Position::Set_Azimuth(double azimuth_Other)
		{
			Object_in_Spherical_Position.Azimuth = azimuth_Other;

			Convert_RADAR_Spherical_To_NED();
			Convert_NED_To_ALL();
		}
	#pragma endregion

	#pragma endregion

	#pragma region Methods
		// --------------------------------------------------
		//  Convert_UTM_To_NED
		//  Haim Otachi     17/08/2015
		// 	Description:	Convert from UTM coordinate (lat,lon,alt) to NED coordinate system (in cartesian unit) 
		//		The position vector transformation from the geodetic system to the ECEF coordinate
		//		system is an intermediate step in converting the GPS position measurement to the
		//		local NED coordinate system.
		// 	Reference:
		//	 Theoretical overvie: Section 2.3.2.2 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=0CCoQFjACahUKEwiN9puL-b7HAhWKwBQKHUWeCVc&url=http%3A%2F%2Fwww.springer.com%2Fcda%2Fcontent%2Fdocument%2Fcda_downloaddocument%2F9780857296344-c2.pdf%3FSGWID%3D0-0-45-1143141-p174116371&ei=sZnZVc3ZB4qBU8W8prgF&usg=AFQjCNEccSj6iWxvsA2_y-Ci0b_GOTNg-Q&sig2=JsvWGmL-5u5wsZZ8vG5WKg
		//	 Functional description: page 31 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0CBwQFjAAahUKEwjZuIGJ-r7HAhXGPxQKHffKDg4&url=http%3A%2F%2Fwww.theatlas.org%2Findex.php%3Foption%3Dcom_phocadownload%26view%3Dcategory%26download%3D106%3Acoordinate-systems-functionality-description%26id%3D11%3Avol7-2007%26Itemid%3D77&ei=uJrZVdn8OMb_UPeVu3A&usg=AFQjCNEP66XtO2iqfiRgjRt3v1CCWQW0Xw&sig2=38xGVlDGF2lDVbSIrD52Fw
		//	 Also: https://en.wikipedia.org/wiki/Geographic_coordinate_conversion
		//  Input value:	
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::Convert_UTM_To_NED()
		{
			Object_in_NED_Position = Object_in_UTM_position - Screen_in_UTM_Position;
		}
		// --------------------------------------------------
		//  Convert_Screen_To_NED  
		//  Alon Slapak     25.8.2015
		// 	Description:	Convert from screen coordinate (in pixel unit) to NED coordinate system (in cartesian unit)
		//                   ------- NED is a - Reference point of system -------
		// 	Reference:		
		//  Input value:	
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::Convert_Screen_To_NED()
		{
			//--------------------------------------------------------
			//	    Build temporary cartesian point from the screen (X,Y)
			//--------------------------------------------------------
			C_CartesianPoint CartesianPoint;
			CartesianPoint.X = Object_in_Screen_Position.Screen_X;
			CartesianPoint.Y = Object_in_Screen_Position.Screen_Y;
			//--------------------------------------------------------
			//	   Rotate according to the secreen north
			//--------------------------------------------------------
			CartesianPoint.Rotate_XY(-Screen_in_UTM_North);
			//--------------------------------------------------------
			//	   Scale by meter-per-pixel
			//--------------------------------------------------------
			CartesianPoint.Scale(meter_per_pixel, meter_per_pixel, 1);
			//--------------------------------------------------------
			//	    Update the Object_in_NED_Position with new values
			//--------------------------------------------------------
			Object_in_NED_Position = CartesianPoint;
		}
		// --------------------------------------------------
		//  Convert_RADAR_Cartesian_To_NED()
		//  Haim Otachi     17/08/2015
		// 	Description:	Convert from Radar cartesian coordinate system (in cartesian unit) to NED coordinate system (in cartesian unit) 
		//                   ------- NED is a - Reference point of system -------
		// 	Reference:		
		//  Input value:	
		//  Return Value:	The NED coordinate system
		// --------------------------------------------------
		void C_Position::Convert_RADAR_Cartesian_To_NED()
		{
			//--------------------------------------------------------
			//	    Build temporary cartesian point from the radar cartesian
			//--------------------------------------------------------
			C_CartesianPoint CartesianPoint = Object_in_Cartesian_Position;
			//--------------------------------------------------------
			//		Rotate
			//--------------------------------------------------------
			CartesianPoint.Rotate_XY(-Radar_in_UTM_North);
			//--------------------------------------------------------
			//		Translate
			//--------------------------------------------------------
			CartesianPoint += (Radar_in_UTM_Position - Screen_in_UTM_Position);
			//--------------------------------------------------------
			//	    Update the Object_in_NED_Position with new values
			//--------------------------------------------------------
			Object_in_NED_Position = CartesianPoint;
		}
		// --------------------------------------------------
		//  Convert_NED_To_Screen
		//  Haim Otachi     17/08/2015
		// 	Description:	Convert from Radar spherical coordinate system (Range,theta, phi) to NED coordinate system (in cartesian unit)
		//                  ------- NED is a - Reference point of system -------
		// 	Reference:		
		//  Input value:	
		//  Return Value:	The NED coordinate system
		// --------------------------------------------------
		void C_Position::Convert_RADAR_Spherical_To_NED()
		{
			//-------------------------------------------
			// Convert from RADAR_Spherical coordinates to RADAR Cartesian coordinate
			//-------------------------------------------
			Object_in_Cartesian_Position = Object_in_Spherical_Position.Convert_Spherical_To_Cartesian();
			//--------------------------------------------------------
			// Convert from RADAR Cartesian coordinate to NED coordinate
			//--------------------------------------------------------
			Convert_RADAR_Cartesian_To_NED();
		}
		// --------------------------------------------------
		//  Convert_NED_To_Screen
		//  Alon Slapak     25.8.2015
		// 	Description:	Convert from NED coordinate system (in cartesian unit) to screen coordinate (in pixel unit)
		//                  ------- NED is a - Reference point of system -------
		// 	Reference:		
		//  Input value:	
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::Convert_NED_To_Screen()
		{
			Object_in_Screen_Position.Screen_X = (int)Object_in_NED_Position.X;
			Object_in_Screen_Position.Screen_Y = (int)Object_in_NED_Position.Y;
			//--------------------------------------------------------
			//		 Rotate
			//--------------------------------------------------------
			Object_in_Screen_Position.Rotate(-Screen_in_UTM_North);
			//--------------------------------------------------------
			//		 Scale
			//--------------------------------------------------------
			Object_in_Screen_Position.Scale(1 / meter_per_pixel, 1 / meter_per_pixel);
		}
		// --------------------------------------------------
		//  Convert_NED_To_RADAR_Cartesian
		//  Alon Slapak     25.8.2015
		// 	Description:	Convert from NED coordinate system (in cartesian unit) to Radar cartesian coordinate system (in cartesian unit)
		//                   ------- NED is a - Reference point of system -------
		// 	Reference:		
		//  Input value:	
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::Convert_NED_To_RADAR_Cartesian()
		{
			Object_in_Cartesian_Position = Object_in_NED_Position;
			//--------------------------------------------------------
			//		Translate //xxx
			//--------------------------------------------------------
			Object_in_Cartesian_Position -= (Radar_in_UTM_Position - Screen_in_UTM_Position);
			//--------------------------------------------------------
			//		Rotate
			//--------------------------------------------------------
			Object_in_Cartesian_Position.Rotate_XY(Radar_in_UTM_North);
		}
		// --------------------------------------------------
		//  Convert_NED_To_Screen
		//  Haim Otachi     17/08/2015
		// 	Description:	Convert from NED coordinate system (in cartesian unit) to Radar spherical coordinate system (Range,theta, phi) 
		//                  ------- NED is a - Reference point of system -------
		// 	Reference:		
		//  Input value:	
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::Convert_NED_To_RADAR_Spherical()
		{
			//-------------------------------------------
			// Convert from NED coordinate to RADAR Cartesian coordinate
			//-------------------------------------------
			Convert_NED_To_RADAR_Cartesian();
			//-------------------------------------------
			// Convert from RADAR Cartesian coordinate to RADAR_Spherical coordinates
			//-------------------------------------------
			Object_in_Spherical_Position.Convert_Cartesian_To_Spherical(Object_in_Cartesian_Position);
		}
		// --------------------------------------------------
		//  Convert_NED_To_ALL
		//  Haim Otachi     17/08/2015
		// 	Description:	Convert from NED coordinate system (in cartesian unit) to all coordinate system
		//                  ------- NED is a - Reference point of system -------
		// 	Reference:		
		//  Input value:	
		//  Return Value:	The all coordinate system
		// --------------------------------------------------
		void C_Position::Convert_NED_To_ALL()
		{
			Convert_NED_To_UTM();
			Convert_NED_To_RADAR_Cartesian();
			Convert_NED_To_Screen();
			Convert_NED_To_RADAR_Spherical();
		}
		// --------------------------------------------------
		//  Convert_NED_TO_UTM
		//  Haim Otachi     17/08/2015
		// 	Description:	Convert from UTM Radar coordinate system (lat, lon, alt) to NED coordinate system (in cartesian unit)
		//                  This is just the inversion of the ECEF to NED transformation.
		// 	Reference:
		//	 Theoretical overvie: Section 2.3.2.2 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=0CCoQFjACahUKEwiN9puL-b7HAhWKwBQKHUWeCVc&url=http%3A%2F%2Fwww.springer.com%2Fcda%2Fcontent%2Fdocument%2Fcda_downloaddocument%2F9780857296344-c2.pdf%3FSGWID%3D0-0-45-1143141-p174116371&ei=sZnZVc3ZB4qBU8W8prgF&usg=AFQjCNEccSj6iWxvsA2_y-Ci0b_GOTNg-Q&sig2=JsvWGmL-5u5wsZZ8vG5WKg
		//	 Functional description: page 31 in https://www.google.co.il/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0CBwQFjAAahUKEwjZuIGJ-r7HAhXGPxQKHffKDg4&url=http%3A%2F%2Fwww.theatlas.org%2Findex.php%3Foption%3Dcom_phocadownload%26view%3Dcategory%26download%3D106%3Acoordinate-systems-functionality-description%26id%3D11%3Avol7-2007%26Itemid%3D77&ei=uJrZVdn8OMb_UPeVu3A&usg=AFQjCNEP66XtO2iqfiRgjRt3v1CCWQW0Xw&sig2=38xGVlDGF2lDVbSIrD52Fw
		//	 Also: https://en.wikipedia.org/wiki/Geographic_coordinate_conversion
		//  Input value:	
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::Convert_NED_To_UTM()
		{
			Object_in_UTM_position = Screen_in_UTM_Position + Object_in_NED_Position;
		}
		// --------------------------------------------------
		//  Line_point_projection
		//  Haim Otachi 02/09/2015
		// 	Description:	???? WRONG
		// 	Reference: 
		//	Input Value:	
		//  Return Value: 
		// --------------------------------------------------
		C_Position C_Position::Line_point_projection(C_Position point_1, C_Position point_2)
		{
			C_UTM_Coordinates line_point_projection = Object_in_UTM_position.Line_point_projection(point_1.Object_in_UTM_position, point_2.Object_in_UTM_position);
			C_Position result;
			result.meter_per_pixel = meter_per_pixel;
			result.Screen_in_UTM_Position = Screen_in_UTM_Position;
			result.set_Object_in_UTM_Position(line_point_projection);
			return result;
		}
		// --------------------------------------------------
		//  Line_angle
		//  Haim Otachi		26/10/2015
		// 	Description:	the function calculate the Line angle between 3 point relative to cartesian coordinates unit,
		//					and use in the function Line_angle of the C_Cartesian_Point class
		// 	Reference: 
		//	Input Value:	
		//  Return Value: 
		// --------------------------------------------------
		double C_Position::Line_angle(C_Position point_1, C_Position point_2) { return Object_in_Cartesian_Position.Line_angle(point_1.get_Object_in_Cartesian_Position(), point_2.get_Object_in_Cartesian_Position()); }
		// --------------------------------------------------
		//  Distance_To
		//  Haim Otachi 09/02/2015
		// 	Description:	
		// 	Reference: 
		//	Input Value:	
		//  Return Value: 
		// --------------------------------------------------
		double C_Position::Distance_To(C_Position Position_Other)
		{
			C_CartesianPoint difference_between_points = Object_in_NED_Position - Position_Other.Object_in_NED_Position;
			return difference_between_points.Norm();
		}
		// --------------------------------------------------
		//  Azimuth_To
		//  Haim Otachi 09/02/2015
		// 	Description:	
		// 	Reference: 
		//	Input Value:	
		//  Return Value: 
		// --------------------------------------------------
		double C_Position::Azimuth_To(C_Position Position_Other)
		{
			C_CartesianPoint difference_between_points = Object_in_NED_Position - Position_Other.Object_in_NED_Position;
			return atan2(difference_between_points.Y, difference_between_points.X);
		}
		// --------------------------------------------------
		//  Maximal_projected_distanc
		//  Haim Otachi 3/9/2015
		// 	Description:	calculate the maximal (delta x, delta y) between the 
		//					two classes.
		// 	Reference: 
		//	Input Value:	Reference to another class
		//  Return Value:   maximal (delta x, delta y)
		// --------------------------------------------------
		double C_Position::Maximal_projected_distanc(C_Position% Position_other)
		{
			// --------------------------------------------------
			//	  calculate delta_x and delta_y between two points 
			// --------------------------------------------------
			C_CartesianPoint cartesian_point = Object_in_UTM_position - Position_other.Object_in_UTM_position;
			// --------------------------------------------------
			//	  return the Maximal projected distanc
			// --------------------------------------------------
			return fmax(fabs(cartesian_point.X), fabs(cartesian_point.Y));
		}
		// --------------------------------------------------
		//  Calc_Left_Point_Of_Line
		//  Haim Otachi		01/11/2015
		// 	Description:	
		// 	Reference: 
		//	Input Value:	
		//  Return Value:   the left point in cartesian coordinate unit
		// --------------------------------------------------
		C_CartesianPoint C_Position::Calc_Left_Point_Of_Line()
		{
			C_CartesianPoint result;
			double delta_X = Object_in_Cartesian_Position.X - 1000;
			double delta_Y = Object_in_Cartesian_Position.Y - 1000;
			double delta_Z = Object_in_Cartesian_Position.Z - 1000;

			result.set_point2D(delta_X, delta_Y);
			result.Z = delta_Z;
			return result;
		}
		// --------------------------------------------------
		//  Calc_Right_Point_Of_Line
		//  Haim Otachi		01/11/2015
		// 	Description:	
		// 	Reference: 
		//	Input Value:	
		//  Return Value:   the right point in cartesian coordinate unit
		// --------------------------------------------------
		C_CartesianPoint C_Position::Calc_Right_Point_Of_Line()
		{
			C_CartesianPoint result;
			double delta_X = Object_in_Cartesian_Position.X + 1000;
			double delta_Y = Object_in_Cartesian_Position.Y + 1000;
			double delta_Z = Object_in_Cartesian_Position.Z + 1000;

			result.set_point2D(delta_X, delta_Y);
			result.Z = delta_Z;
			return result;
		}
		// -----------------------------------------------------------------
		//  Distance_between_Two_Phi   
		//  Haim Otachi		08/12/2015
		// 	Description:	Calculate distance between 2 pylons, such as, 
		//						•	First pylon - represented the first phi.
		//						•	Second pylon – represented the second phi.
		//					Definition:
		//						'Phi' – represented the range and azimuth of the target(pylon / wire), like :
		//										Phi = (range, azimuth)
		// 	Reference:		
		//  Input value:	pylon other
		//  Return Value:	The distacne between the 2 phi
		// -----------------------------------------------------------------
		double C_Position::Distance_between_Two_Phi(C_Position% pylon_other)
		{
			//-------------------------------------------
			//			range and range_hat
			//-------------------------------------------
			double range = pylon_other.Get_Range(); // r
			double range_hat = Object_in_Spherical_Position.Range; // r hat
			//-------------------------------------------
			//			theta and theta_hat
			//-------------------------------------------
			double theta = pylon_other.Get_Azimuth() - PI / 2; // theta
			double theta_hat = Object_in_Spherical_Position.Azimuth - PI / 2; // theta hat
			//-------------------------------------------
			//			range and range_Hat in squared
			//-------------------------------------------
			double Range = pow(range, 2); // r^2
			double Range_Hat = pow(range_hat, 2); // r_hat^2
			//-------------------------------------------
			//			delta of angles (theta and theta_Hat)
			//-------------------------------------------
			double delta_Angle = theta - theta_hat;
			double temp = 2 * range * range_hat * cos(delta_Angle);
			//-------------------------------------------
			//			calculate the distance
			//-------------------------------------------
			double distance = sqrt(Range + Range_Hat - temp);
			//-------------------------------------------
			//			return the distance between two pi
			//-------------------------------------------
			return distance;
		}
		// -----------------------------------------------------------------
		//  DeltaFunction 
		//  Haim Otachi		08/12/2015
		// 	Description:	
		// 	Reference:		
		//  Input value:	second pylon
		//  Return Value:	
		// -----------------------------------------------------------------
		double C_Position::DeltaFunction(C_Position% pylon_other, double DMax)
		{
			//-------------------------------------------
			//	we calculate the distance between 2 pylons
			//-------------------------------------------
			double distance = Distance_between_Two_Phi(pylon_other);
			//-------------------------------------------
			//	we return the delta function
			//-------------------------------------------
			return fmin(distance / DMax, 1);
		}
		// -----------------------------------------------------------------
		//  RnrFunction  
		//  Haim Otachi		08/12/2015
		// 	Description:	
		// 	Reference:		
		//  Input value:	
		//  Return Value:	
		// -----------------------------------------------------------------      
		double C_Position::RnrFunction(C_Position% pylon_other, double Cnr)
		{
			double part_1 = 0, part_2 = 0, part_3 = 0;
			double Rnr_Result_Function = 0;
			//-------------------------------------------
			//			Calculate distance between both range: TOM and EOM
			//-------------------------------------------
			double distance = Distance_between_Two_Phi(pylon_other);

			if (distance > 0)
			{
				//-------------------------------------------
				//			range and range_hat
				//-------------------------------------------
				double range = pylon_other.Get_Range(); // r
				double range_hat = Object_in_Spherical_Position.Range; // r hat
				//-------------------------------------------
				//			theta and theta_hat
				//-------------------------------------------
				double theta = pylon_other.Get_Azimuth() - PI / 2; // theta
				double theta_hat = Object_in_Spherical_Position.Azimuth - PI / 2; // theta hat
				//-------------------------------------------
				//			delta of angles (theta and theta_Hat)
				//-------------------------------------------
				double delta_Angle = theta - theta_hat;
				//
				// TODO: check this function
				//
				part_1 = (range_hat * cos(delta_Angle) - range) / distance;
				part_2 = (1 - Cnr) / 2;
				part_3 = (1 + Cnr) / 2;

				Rnr_Result_Function = part_1 * part_2 + part_3;
			}

			return Rnr_Result_Function;
		}
		// -----------------------------------------------------------------
		//  RlfFunction  
		//  Haim Otachi		08/12/2015
		// 	Description:	
		// 	Reference:		
		//  Input value:	
		//  Return Value:	
		// -----------------------------------------------------------------
		double C_Position::RlfFunction(double Clf)
		{
			//-------------------------------------------
			//	we take the correct range and azimuth
			//-------------------------------------------
			double range = Object_in_Spherical_Position.Range;
			double azimuth = Object_in_Spherical_Position.Azimuth;
			//-------------------------------------------
			//	we calculate the risk function and return the answer
			//-------------------------------------------
			return cos(azimuth - PI / 2) * exp(-Clf * range);
		}
	#pragma endregion

	#pragma region Operator Overloading
		// --------------------------------------------------
		//  Operator=  
		//  Haim Otachi     17/08/2015
		// 	Description:	= opeartor (assignment)
		// 	Reference:		
		//  Input value:	reference to other struct
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::operator=(C_Position% Position_other)
		{
			//-------------------------------------
			//			Object coordinates
			//-------------------------------------
			Object_in_UTM_position = Position_other.Object_in_UTM_position;
			Object_in_Cartesian_Position = Position_other.Object_in_Cartesian_Position;
			Object_in_Spherical_Position = Position_other.Object_in_Spherical_Position;
			Object_in_Screen_Position = Position_other.Object_in_Screen_Position;
			Object_in_NED_Position = Position_other.Object_in_NED_Position;
			//-------------------------------------
			//			Relative coordinates 
			//-------------------------------------
			Screen_in_UTM_Position = Position_other.Screen_in_UTM_Position;
			Screen_in_UTM_North = Position_other.Screen_in_UTM_North;

			Radar_in_UTM_Position = Position_other.Radar_in_UTM_Position;
			Radar_in_UTM_North = Position_other.Radar_in_UTM_North;

			meter_per_pixel = Position_other.meter_per_pixel;
		}
		// --------------------------------------------------
		//  Operator=  
		//  Haim Otachi     17/08/2015
		// 	Description:	= opeartor (assignment)
		// 	Reference:		
		//  Input value:	reference to Number
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::operator=(int& Number)
		{
			//-------------------------------------
			//			Object coordinates
			//-------------------------------------
			Object_in_UTM_position = Number;
			Object_in_Cartesian_Position = Number;
			Object_in_Spherical_Position = Number;
			Object_in_Screen_Position = Number;
			Object_in_NED_Position = Number;
			//-------------------------------------
			//			Relative coordinates 
			//-------------------------------------
			Screen_in_UTM_Position = Number;
			Screen_in_UTM_North = Number;

			Radar_in_UTM_Position = Number;
			Radar_in_UTM_North = Number;

			meter_per_pixel = Number;
		}
		// --------------------------------------------------
		//  operator+=  
		//  Alon Slapak     25.8.2015
		// 	Description:	Cartesian offset  (+= opeartor )
		// 	Reference:		
		//  Input value:	Cartesian offset in meters (in NED coordinates)
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::operator+=(C_CartesianPoint% cartesian_offset)
		{
			Object_in_NED_Position += cartesian_offset;
			Convert_NED_To_ALL();
		}
		// --------------------------------------------------
		//  operator-=  
		//  Haim Otachi     09/02/2015
		// 	Description:	Cartesian offset  (-= opeartor )
		// 	Reference:		
		//  Input value:	Cartesian offset in meters (in NED coordinates)
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::operator-=(C_CartesianPoint% cartesian_offset)
		{
			Object_in_NED_Position -= cartesian_offset;
			Convert_NED_To_ALL();
		}
		// --------------------------------------------------
		//  operator-  
		//  Haim Otachi     09/03/2015
		// 	Description:	- the function calculate the difference between two points: 'second point' and 'first point'.
		//					- the points are inserted such as C_position object.
		//					
		//					'first point' - is a bottom left point of the border.
		//					'second point' - is a top right point of the border.
		//							
		//									  -> 'second point'
		//									 /|  
		//							        / |	
		//						           /  |
		//                                /   |
		//                               /    |
		//                              /	  |
		//					           /  	  |
		//					          /	      |
		//					         /		  |
		//		 <-'first point'	 ----------
		//
		//					or like this:
		//							 --------------- -> 'second point'
		//							|			    |
		//							|               |
		//			<-'first point'	 ---------------
		//
		//
		// 	Reference:		
		//  Input value:	the 'first point' and 'second point'
		//  Return Value:	the difference in cartesian point unit .
		// --------------------------------------------------
		C_CartesianPoint C_Position::operator-(C_Position% Second_Point)
		{
			C_Position answer;
			answer.set_Radar_in_UTM_Position(Second_Point.get_Object_in_UTM_Position());
			answer.set_Object_in_UTM_Position(Object_in_UTM_position);
			return answer.get_Object_in_Cartesian_Position();
		}
		// --------------------------------------------------
		//  operator+=  
		//  Alon Slapak     25.8.2015
		// 	Description:	Spherical offset  (+= opeartor )
		// 	Reference:		
		//  Input value:	Spherical offset meters and radians (in NED coordinates)
		//  Return Value:	
		// --------------------------------------------------
		void C_Position::operator+=(C_SphericalPoint% spherical_offset)
		{
			Object_in_NED_Position += spherical_offset.Convert_Spherical_To_Cartesian();
			Convert_NED_To_ALL();
		}
	#pragma endregion
}