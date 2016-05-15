#ifndef C_POSITION_H
#define C_POSITION_H
//-----------------------------------------
//			ROD_Position.h
//-----------------------------------------
#include "C_Point2D.h"
#include "C_Point2DInt.h"
#include "C_CartesianPoint.h"
#include "C_SphericalPoint.h"
#include "C_UTM_Coordinates.h"

namespace ROD_Position
{
	public ref class C_Position
	{
		#pragma region Fields
		//---------------------------------------
		//
		//
		//
		//				NED								RADAR
		//					|	
		//					|        /                /
		//					|       /				 /
		//					|      /				/
		//					|     /                X------------
		//					|    /                  \
		//					|   /                    \
		//					|  /                      \
		//					| /                        \
		//					|/
		//					+------------------------------
		//            Origin(NED + SCREEN)           
		//							
		// 
		//
		//			NED <---+------>    Rotate & Scale		<--->  SCREEN
		//					|
		//					+------>		ECEF			<--->  UTM
		//					|
		//					+------>	translate & rotate	<--->  Radar cartesian
		//																^
		//															 (trnasformation)	
		//																v
		//															Radar spherical
		//		Comments:
		//			1. Angles
		//				1.1 UTM are in degrees
		//				1.2 All oteher angles are in radians
		//				1.3 Positive angles is counterclockwise 
		//				1.4 Azimuth angles poitive are clockwise 
		//			2. Screen:
		//				2.1 2D: resides on the NED X,Y
		//				2.2 Origin of NED = Origin of Screen = [Screen_in_UTM_Position]
		//				2.3 Rotation by: [Screen_in_UTM_North]
		//			3. Radar (cartesian and spherical) 
		//				3.1 Spherical coordinates (r, θ, φ) as often used in mathematics https://en.wikipedia.org/wiki/Spherical_coordinate_system 
		//				3.2 YAW (Heading)	is about Z, when X is the zero
		//				3.3 ROLL			is about Y, when X is the zero
		//				3.4 PITCH			is about X, when Y is the zero
		//
		//					Z
		//					|     Y     
		//					|    /      
		//					|   /        
		//					|  /         
		//			   ___	| /          
		//		\	    |	|/
		//		 \====(   )	+----------- X
		//				   
		//				
		//---------------------------------------
		private:
		//-------------------------------------
		//			Object coordinates
		//-------------------------------------
		C_UTM_Coordinates Object_in_UTM_position; // Lla Point (UTM Unit - (Latitude, Longitude, Altitude))
		C_CartesianPoint Object_in_Cartesian_Position; // Local Point (Cartesian Unit - (X,Y,Z))
		C_SphericalPoint Object_in_Spherical_Position; // Spherical Point (R,Theta, phi)
		C_Point2DInt Object_in_Screen_Position; // Pixel Point  (Pixel point of the screen - (X,Y))
		C_CartesianPoint Object_in_NED_Position; // Reference Point in Cartesian point unit - (X,Y,Z)
		//-------------------------------------
		//			Screen position
		//-------------------------------------
		C_UTM_Coordinates Screen_in_UTM_Position;
		double Screen_in_UTM_North;
		//-------------------------------------
		//			RADAR position
		//-------------------------------------
		C_UTM_Coordinates Radar_in_UTM_Position;
		double Radar_in_UTM_North;
		//-------------------------------------
		//			Auxiliaries
		//-------------------------------------
		double meter_per_pixel;
		#pragma endregion

		#pragma region Constructors
		public:
		//-------------------------------------
		//			Constructors
		//-------------------------------------
		C_Position();
		C_Position(double lat, double lon);
		C_Position(double x, double y, double z);
		C_Position(C_UTM_Coordinates Screen_in_UTM_Position_other);
		C_Position(C_UTM_Coordinates Screen_in_UTM_Position_other, C_UTM_Coordinates Radar_in_UTM_Position_other);
		C_Position(C_CartesianPoint CartesianPoint_other);
		C_Position(C_SphericalPoint SphericalPoint_other);
		C_Position(C_Point2DInt Point2DInt_other);
		//-------------------------------------
		//			Copy Constructor
		//-------------------------------------
		C_Position(C_Position% other);
		#pragma endregion

		#pragma region Set And Get
		//-------------------------------------------
		//			Get/Set Object coordinates: UTM Coordinate
		//-------------------------------------------
		C_UTM_Coordinates get_Object_in_UTM_Position();
		void set_Object_in_UTM_Position(double lat, double lon, double alt);
		void set_Object_in_UTM_Position(C_UTM_Coordinates% UTM_Coordinates_Other);
		//-------------------------------------------
		//			Get/Set Object coordinates: Cartesian Point
		//-------------------------------------------
		C_CartesianPoint get_Object_in_Cartesian_Position();
		void set_Object_in_Cartesian_Position(double x, double y, double z);
		void set_Object_in_Cartesian_Position(C_CartesianPoint% CartesianPoint_other);
		//-------------------------------------------
		//			Get/Set Object coordinates: Spherical Point
		//-------------------------------------------
		C_SphericalPoint get_Object_in_Spherica_Position();
		void set_Object_in_Spherica_Position(double Range, double theta, double phi);
		void set_Object_in_Spherica_Position(C_SphericalPoint% SphericalPoint_other);
		//-------------------------------------------
		//			Get/Set Object coordinates: Screen Coordinates
		//-------------------------------------------
		C_Point2DInt get_Object_in_Screen_Position();
		void set_Object_in_Screen_Position(int x, int y);
		void set_Object_in_Screen_Position(C_Point2DInt% Screen_coordinates_other);
		//-------------------------------------------
		//			Get/Set Latitude of utm coordinate
		//-------------------------------------------
		property double Latitude {double get(); void set(double Latitude_Other); }
		//-------------------------------------------
		//			Get/Set Longitude of utm coordinate
		//-------------------------------------------
		property double Longitude {double get(); void set(double Longitude_Other); }
		//-------------------------------------------
		//			Get/Set altitude of utm coordinate
		//-------------------------------------------
		property double Altitude {double get(); void set(double Altitude_Other); }
		//-------------------------------------------
		//			Get/Set X pixel of screen coordinate
		//-------------------------------------------
		property int Screen_X {int get(); void set(int Screen_X_Other); }
		//-------------------------------------------
		//			Get/Set Y pixel of screen coordinate
		//-------------------------------------------
		property int Screen_Y {int get(); void set(int Screen_Y_Other); }
		//-------------------------------------------
		//			Get/Set Range of Spherical Coordinates
		//-------------------------------------------
		double Get_Range();
		void Set_Range(double Range_Other);
		//-------------------------------------------
		//			Get/Set Theta of Spherical Coordinates
		//-------------------------------------------
		double Get_Azimuth();
		void Set_Azimuth(double Azimuth_Other);
		//-------------------------------------------
		//			Get/Set relative coordinates: Screen_in_UTM_Position
		//-------------------------------------------
		C_UTM_Coordinates get_Screen_in_UTM_Position();
		void set_Screen_in_UTM_Position(double Latitude, double Longitude);
		void set_Screen_in_UTM_Position(C_UTM_Coordinates% Screen_in_UTM_Position_other);
		//-------------------------------------------
		//			Get/Set relative coordinates: Screen in UTM North
		//-------------------------------------------
		double get_Screen_in_UTM_North();
		void set_Screen_in_UTM_North(double angle);
		//-------------------------------------------
		//			Get/Set relative coordinates: Radar_in_UTM_Position
		//-------------------------------------------
		C_UTM_Coordinates get_Radar_in_UTM_Position();
		void set_Radar_in_UTM_Position(double Latitude, double Longitude, double Altitude);
		void set_Radar_in_UTM_Position(C_UTM_Coordinates% Radar_in_UTM_Position_other);
		//-------------------------------------------
		//			Get/Set relative coordinates: Radar in UTM North
		//-------------------------------------------
		double get_Radar_in_UTM_North();
		void set_Radar_in_UTM_North(double angle);
		//-------------------------------------------
		//			Get/Set relative coordinates: Meters per pixel
		//-------------------------------------------
		double get_Meter_Per_Pixel();
		void set_Meter_Per_Pixel(double meter_per_pixel_other);
		#pragma endregion

		#pragma region Methods
		//-----------------------------------------
		//		Private Methods:   Private methods of C_Position Class
		//-----------------------------------------
		private:
		//-----------------------------------------
		//		Convert from all coordinate system to reference system unit - NED coordinate (in cartesian point)
		//-----------------------------------------
		void Convert_UTM_To_NED();
		void Convert_Screen_To_NED();
		void Convert_RADAR_Cartesian_To_NED();
		void Convert_RADAR_Spherical_To_NED();
		//-----------------------------------------
		//		Convert from reference system unit - NED coordinate (in cartesian point) to all coordinate system 
		//-----------------------------------------
		void Convert_NED_To_UTM();
		void Convert_NED_To_Screen();
		void Convert_NED_To_RADAR_Cartesian();
		void Convert_NED_To_RADAR_Spherical();
		void Convert_NED_To_ALL();
		//-----------------------------------------
		//		Public Methods:   Public methods of C_Position Class
		//-----------------------------------------
		public:
		C_Position Line_point_projection(C_Position point_1, C_Position point_2);
		double Line_angle(C_Position point_1, C_Position point_2);
		double Maximal_projected_distanc(C_Position% Position_other);

		double Distance_To(C_Position Position_Other);
		double Azimuth_To(C_Position Position_Other);

		C_CartesianPoint Calc_Left_Point_Of_Line();
		C_CartesianPoint Calc_Right_Point_Of_Line();
		//-------------------------------------------
		//			   Error Function 
		//-------------------------------------------
		double Distance_between_Two_Phi(C_Position% pylon_other);
		double DeltaFunction(C_Position% pylon_other, double DMax);
		double RnrFunction(C_Position% pylon_other, double Cnr);
		double RlfFunction(double Clf);
		#pragma endregion

		#pragma region Operator Overloading
		//-----------------------------------------
		//		Operator Overloading
		//-----------------------------------------
		void operator=(C_Position% Position_other);
		void operator=(int& Number);
		void operator+=(C_CartesianPoint% cartesian_offset);
		void operator-=(C_CartesianPoint% cartesian_offset);
		void operator+=(C_SphericalPoint% spherical_offset);

		C_CartesianPoint operator-(C_Position% Position_offset);
		#pragma endregion
	};
}

#endif



