#include "C_SphericalPoint.h"
#include <iostream>

#define PI				3.14159265358979323846
#define	GOOD			0
#define FAULT			1

//-------------------------------------
//			Other Constructors
//-------------------------------------
C_CartesianPoint::C_CartesianPoint(double x, double y) : point2D(x, y), z(0) {}
//-------------------------------------
//			Copy Constructor
//-------------------------------------
C_CartesianPoint::C_CartesianPoint(C_CartesianPoint% other) : point2D(other.X, other.Y), z(other.Z) {}

#pragma region Property
//-------------------------------------------
//			Get/Set point2D coordinate (x,y) of the point
//-------------------------------------------
C_Point2D C_CartesianPoint::get_point2D() { return point2D; }
void C_CartesianPoint::set_point2D(double x, double y) { point2D.X = x; point2D.Y = y; }
//-------------------------------------------
//			X coordinate of point
//-------------------------------------------
double C_CartesianPoint::X::get() { return point2D.X; }
void C_CartesianPoint::X::set(double x) { point2D.X = x; }
//-------------------------------------------
//			Y coordinate of point
//-------------------------------------------
double C_CartesianPoint::Y::get() { return point2D.Y; }
void C_CartesianPoint::Y::set(double y) { point2D.Y = y; }
//-------------------------------------------
//			Z coordinate of point
//-------------------------------------------
double C_CartesianPoint::Z::get() { return z; }
void C_CartesianPoint::Z::set(double z_other) { z = z_other; }
#pragma endregion

// --------------------------------------------------
//  operator=
//  Haim Otachi 23.8.2015
// 	Description:	= opeartor   (assignment)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::operator=(C_CartesianPoint% CartesianPoint_other)
{
	point2D = CartesianPoint_other.get_point2D();
	z = CartesianPoint_other.Z;
}
// --------------------------------------------------
//  operator+=
//  Haim Otachi 23.8.2015
// 	Description:	+= opeartor
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::operator+=(C_CartesianPoint% CartesianPoint_other)
{
	point2D += CartesianPoint_other.point2D;
	z += CartesianPoint_other.z;
}
// --------------------------------------------------
//  operator-=
//  Haim Otachi 23.8.2015
// 	Description:	-= opeartor
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::operator-=(C_CartesianPoint% CartesianPoint_other)
{
	point2D -= CartesianPoint_other.point2D;
	z -= CartesianPoint_other.z;
}
// --------------------------------------------------
//  operator*=
//  Haim Otachi 23.8.2015
// 	Description:	*= opeartor (matlab-like '.*' elementwise multiplication)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::operator*=(C_CartesianPoint% CartesianPoint_other)
{
	point2D *= CartesianPoint_other.point2D;
	z *= CartesianPoint_other.z;
}
// --------------------------------------------------
//  operator=
//  Haim Otachi 30/09
// 	Description:	
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::operator=(int& Number) { X = Number; Y = Number; z = Number; }
// --------------------------------------------------
//  operator*=
//  Haim Otachi 23.8.2015
// 	Description:	*= opeartor (with constant)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::operator*=(double Number) { point2D *= Number; z *= Number; }
// --------------------------------------------------
//  operator==
//  Haim Otachi 23.8.2015
// 	Description:	== opeartor   (equality)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value:  true if x or y are equal to those of the referenced class (respectively)
// --------------------------------------------------
bool C_CartesianPoint::operator==(C_CartesianPoint% CartesianPoint_other) { return (point2D == CartesianPoint_other.point2D) && (z == CartesianPoint_other.z); }
// --------------------------------------------------
//  operator!=
//  Haim Otachi 23.8.2015
// 	Description:	!= opeartor   (inequality)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value:  true if x or y are differnet from those of the referenced class (respectively)
// --------------------------------------------------
bool C_CartesianPoint::operator!=(C_CartesianPoint% CartesianPoint_other) { return (point2D != CartesianPoint_other.point2D) || (z != CartesianPoint_other.z); }
// --------------------------------------------------
//  operator+
//  Alon Slapak 23.8.2015
// 	Description:	+ opeartor   (binary + operator)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value:	The result of the binary + operator
// --------------------------------------------------
C_CartesianPoint C_CartesianPoint::operator+(C_CartesianPoint% CartesianPoint_other)
{
	C_CartesianPoint CartesianPoint_temp;
	CartesianPoint_temp.point2D = point2D + CartesianPoint_other.point2D;
	CartesianPoint_temp.z = z + CartesianPoint_other.z;
	return CartesianPoint_temp;
}
// --------------------------------------------------
//  operator-
//  Alon Slapak 23.8.2015
// 	Description:	- opeartor   (binary - operator)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value:	The result of the binary + operator
// --------------------------------------------------
C_CartesianPoint C_CartesianPoint::operator-(C_CartesianPoint% CartesianPoint_other)
{
	C_CartesianPoint CartesianPoint_temp;
	CartesianPoint_temp.point2D = point2D - CartesianPoint_other.point2D;
	CartesianPoint_temp.z = z - CartesianPoint_other.z;
	return CartesianPoint_temp;
}
// --------------------------------------------------
//  Distance_between_points  
//  Alon Slapak 22/4/2015
// 	Description:	Calculate distance between 2 points
// 	Reference:		
//  Input value:	2 pointsmnjnj
//  Return Value:	The distacne between the 2 points
// --------------------------------------------------
double C_CartesianPoint::Distance_between_points(C_CartesianPoint% cartesian_Point_other)
{
	C_Point2D Point2D_temp;
	Point2D_temp = point2D - cartesian_Point_other.point2D;
	return Point2D_temp.Norm();
}
// --------------------------------------------------
//  Distance_between_point_and_line  
//  Alon Slapak 24/4/2015
// 	Description:	Calculate distance between point and line (given by two points)
// 	Reference:		http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html Eq. (14)
//  Input value:	point, Line (given by 2 points)
//  Return Value:	The distacne between the point and the line
// --------------------------------------------------
double C_CartesianPoint::Distance_between_point_and_line(C_CartesianPoint Line_1, C_CartesianPoint Line_2)
{
	double denominator, numerator;
	numerator = abs((Line_2.point2D.X - Line_1.point2D.X)*(Line_1.point2D.Y - point2D.Y) - (Line_1.point2D.X - point2D.X)*(Line_2.point2D.Y - Line_1.point2D.Y));
	denominator = Line_1.Distance_between_points(Line_2);

	return numerator / denominator;
}
// --------------------------------------------------
//  Line_angle  
//  Alon Slapak 13/2/2015
// 	Description:	Calculate angle constructed by 3 points 
// 	Reference:		http://math.stackexchange.com/questions/361412/finding-the-angle-between-three-points
//  Input value:	Three points
//  Return Value:	The angle p1 <- p2 -> p3 (namely, p2 is the vertex)
// --------------------------------------------------
double C_CartesianPoint::Line_angle(C_CartesianPoint point_1, C_CartesianPoint point_2)
{
	double x1, x2, y1, y2, t1, t2;
	double norm1, norm2, inner_prod;

	x1 = (point_2.X - point_1.X);
	y1 = (point_2.Y - point_1.Y);

	x2 = (point2D.X - point_1.X);
	y2 = (point2D.Y - point_1.Y);

	norm1 = sqrt(pow(x1, 2) + pow(y1, 2));
	norm2 = sqrt(pow(x2, 2) + pow(y2, 2));

	inner_prod = x1 * x2 + y1 * y2;
	t1 = inner_prod / (norm1*norm2);
	t2 = acos(t1);

	return (acos(inner_prod / (norm1*norm2)));
}
// --------------------------------------------------
//  Line_point_projection  
//  Alon Slapak 13/2/2015
// 	Description:	Calculate the closest point on a line to external point 
// 	Reference:		http://math.stackexchange.com/questions/13176/how-to-find-a-point-on-a-line-closest-to-another-given-point
//  Input value:	Three points:
//					The 1st is the external one
//					The 2nd and 3rd define the line
//  Return Value:	the closes point on the line
// --------------------------------------------------
C_CartesianPoint C_CartesianPoint::Line_point_projection(C_CartesianPoint point_1, C_CartesianPoint point_2)
{
	double t, x1, x2, y1, y2;
	C_CartesianPoint closest_point;

	x1 = (point_2.X - point_1.X);
	y1 = (point_2.Y - point_1.Y);

	x2 = (X - point_1.X);
	y2 = (Y - point_1.Y);

	t = (x1 * x2 + y1 * y2) / (x1 * x1 + y1 * y1);

	double newX, newY;

	newX = point_1.point2D.X + t * (point_2.point2D.X - point_1.point2D.X);
	newY = point_1.point2D.Y + t * (point_2.point2D.Y - point_1.point2D.Y);

	closest_point.set_point2D(newX, newY);

	return closest_point;
}
// --------------------------------------------------
//  Translate
//  Haim Otachi 23.8.2015
// 	Description:	shifting a cartesian point by the offsets
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::Translate(double offset_X, double offset_Y, double offset_Z) { point2D += C_Point2D(offset_X, offset_Y); z += offset_Z; }
// --------------------------------------------------
//  Translate
//  Haim Otachi 23.8.2015
// 	Description:	shifting a cartesian point by the offsets
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::Translate(C_CartesianPoint% offset) { point2D += offset.point2D; z += offset.z; }
// --------------------------------------------------
//  Rotate_XY
//  Haim Otachi 23.8.2015
// 	Description:	Rotationg the coordinates system about the z axis
// 	Reference: 
//	Input Value:	Rotating angle [Radians]
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::Rotate_XY(double theta) { point2D.Rotate(theta); }
// --------------------------------------------------
//  Scale
//  Haim Otachi 23.8.2015
// 	Description:	Scaling the coordinates by 3 scaling factors
// 	Reference: 
//	Input Value:	Scaling factors to each of the coordinates
//  Return Value: 
// --------------------------------------------------
void C_CartesianPoint::Scale(double ScaleX, double ScaleY, double ScaleZ) { point2D.Scale(ScaleX, ScaleY); z *= ScaleZ; }
// --------------------------------------------------
//  Norm
//  Alon Slapak	25.8.2015
// 	Description:	Scaling the coordinates by 3 scaling factors
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
double C_CartesianPoint::Norm() { return sqrt(pow(point2D.Norm(),2) + z*z); }
// --------------------------------------------------
//   Target_is_in_RADAR_FOV
//  Haim Otachi	    02/09/2015
// 	Description:	
// 	Reference: 
//	Input Value:	
//  Return Value: 
// --------------------------------------------------
int C_CartesianPoint::Target_is_in_RADAR_FOV(float Radar_angle, C_CartesianPoint Target, int Radar_Range, int Radar_FOV)
{
	double target_angle;
	double target_range;

	double temp_range;
	// --------------------------------------------------
	//	Calculate range and angle to target
	// --------------------------------------------------
	target_range = sqrt(pow(Target.X - X, 2) + pow(Target.Y - Y, 2));
	target_angle = atan2(Target.X - X, Target.Y - Y) * 180.0 / PI;
	temp_range = target_range * target_angle;
	// --------------------------------------------------
	//	Check if in FOV
	// --------------------------------------------------
	if ((target_range <= Radar_Range) && (fabs(target_angle - Radar_angle) <= Radar_FOV / 2))
	{
		return GOOD;
}
else
{
	return FAULT;
}
}



