#ifndef C_Cartesian_Point_H
#define C_Cartesian_Point_H
#include "C_Point2D.h"

//-----------------------------------------
//		Class:		C_CartesianPoint
//-----------------------------------------
public ref class C_CartesianPoint
{
	//-------------------------------------
	//		Fields
	//-------------------------------------
	private:
	C_Point2D point2D;
	double z;

	public:
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	C_CartesianPoint() {}
	//-------------------------------------
	//			Other Constructors
	//-------------------------------------
	C_CartesianPoint(double x, double y);
	//-------------------------------------
	//			Copy Constructor
	//-------------------------------------
	C_CartesianPoint(C_CartesianPoint% other);

	#pragma region Property
	//-------------------------------------------
	//			point2D coordinate (x,y) of the point
	//-------------------------------------------
	C_Point2D get_point2D();
	void set_point2D(double x, double y);
	//-------------------------------------------
	//			X coordinate of point
	//-------------------------------------------
	property double X {double get(); void set(double x); }
	//-------------------------------------------
	//			Y coordinate of point
	//-------------------------------------------
	property double Y {double get(); void set(double y); }
	//-------------------------------------------
	//			Z coordinate of point
	//-------------------------------------------
	property double Z {double get(); void set(double z); }
	#pragma endregion

	#pragma region Methods
	public:
	double Distance_between_points(C_CartesianPoint% cartesian_Point_other);
	double Distance_between_point_and_line(C_CartesianPoint Line_1, C_CartesianPoint Line_2);
	double Line_angle(C_CartesianPoint point_1, C_CartesianPoint point_2);
	C_CartesianPoint Line_point_projection(C_CartesianPoint point_1, C_CartesianPoint point_2);
	int Target_is_in_RADAR_FOV(float Radar_angle, C_CartesianPoint Target, int Radar_Range, int Radar_FOV);

	double Norm();
	void Rotate_XY(double theta);
	void Translate(C_CartesianPoint% offset);
	void Translate(double offset_X, double offset_Y, double offset_Z);
	void Scale(double ScaleX, double ScaleY, double ScaleZ);
	#pragma endregion

	#pragma region Operator Overloading
	void operator=(C_CartesianPoint% CartesianPoint_other);
	void operator+=(C_CartesianPoint% CartesianPoint_other);
	void operator-=(C_CartesianPoint% CartesianPoint_other);
	void operator*=(C_CartesianPoint% CartesianPoint_other);
	void operator*=(double Number);
	void operator=(int& Number);

	bool operator==(C_CartesianPoint% CartesianPoint_other);
	bool operator!=(C_CartesianPoint% CartesianPoint_other);

	C_CartesianPoint operator+(C_CartesianPoint% CartesianPoint_other);
	C_CartesianPoint operator-(C_CartesianPoint% CartesianPoint_other);
	#pragma endregion
};
#endif  // of RADAR_cartesian_coordinates_H 




