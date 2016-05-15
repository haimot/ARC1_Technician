#include "C_Point2D.h"
#include <cmath>
#define PI       3.14159265358979323846

//-------------------------------------
//			Other Constructors
//-------------------------------------
C_Point2D::C_Point2D(double x, double y) : x(x), y(y) { }
//-------------------------------------
//			Copy Constructor
//-------------------------------------
C_Point2D::C_Point2D(C_Point2D % other) : x(other.x), y(other.y) {}

#pragma region property
//-------------------------------------------
//			X coordinate of point
//-------------------------------------------
double C_Point2D::X::get() { return x; }
void C_Point2D::X::set(double x_other) { x = x_other; }
//-------------------------------------------
//			Y coordinate of point
//-------------------------------------------
double C_Point2D::Y::get() { return y; }
void C_Point2D::Y::set(double y_other) { y = y_other; }
#pragma endregion

#pragma region Operator Overloading
// --------------------------------------------------
//  operator+=
//  Haim Otachi 23.8.2015
// 	Description:	+= opeartor
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value: 
// --------------------------------------------------
void C_Point2D::operator+=(C_Point2D% Point2D_other)
{
	x += Point2D_other.x;
	y += Point2D_other.y;
}
// --------------------------------------------------
//  operator-=
//  Haim Otachi 23.8.2015
// 	Description:	-= opeartor
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value: 
// --------------------------------------------------
void C_Point2D::operator-=(C_Point2D% Point2D_other)
{
	x -= Point2D_other.x;
	y -= Point2D_other.y;
}
// --------------------------------------------------
//  operator*=
//  Haim Otachi 23.8.2015
// 	Description:	*= opeartor (matlab like elementwise multiplication)
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value: 
// --------------------------------------------------
void C_Point2D::operator*=(C_Point2D% Point2D_other)
{
	x *= Point2D_other.x;
	y *= Point2D_other.y;
}
// --------------------------------------------------
//  operator*=
//  Alon Slapak 23.8.2015
// 	Description:	*= opeartor (with constant)
// 	Reference: 
//	Input Value:	Number to multiply with
//  Return Value: 
// --------------------------------------------------
void C_Point2D::operator*=(double Number)
{
	x *= Number;
	y *= Number;
}
// --------------------------------------------------
//  operator=
//  Haim Otachi 23.8.2015
// 	Description:	= opeartor (assignment)
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value: 
// --------------------------------------------------
void C_Point2D::operator=(C_Point2D% Point2D_other)
{
	x = Point2D_other.x;
	y = Point2D_other.y;
}
// --------------------------------------------------
//  operator==
//  Haim Otachi 23.8.2015
// 	Description:	== opeartor (eqaulity) 
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value:  true if x or y are equal to those of the referenced class (respectively)
// --------------------------------------------------
bool C_Point2D::operator == (C_Point2D% Point2D_other)
{
	return (x == Point2D_other.x) && (y == Point2D_other.y);
}
// --------------------------------------------------
//  operator!=
//  Haim Otachi 23.8.2015
// 	Description:	!= opeartor (inequality)
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value:  true if x or y are differnet from those of the referenced class (respectively)
// --------------------------------------------------
bool C_Point2D::operator != (C_Point2D% Point2D_other)
{
	return (x != Point2D_other.x) || (y != Point2D_other.y);
}
// --------------------------------------------------
//  operator-
//  Alon Slapak 23.8.2015
// 	Description:	- opeartor   (binary - operator)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value:	The result of the binary - operator
// --------------------------------------------------
C_Point2D C_Point2D::operator-(C_Point2D% Point2D_other)
{
	C_Point2D Point2D_temp;
	Point2D_temp.x = x - Point2D_other.x;
	Point2D_temp.y = y - Point2D_other.y;
	return Point2D_temp;
}
// --------------------------------------------------
//  operator+
//  Alon Slapak 23.8.2015
// 	Description:	+ opeartor   (binary + operator)
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value:	The result of the binary + operator
// --------------------------------------------------
C_Point2D C_Point2D::operator+(C_Point2D% Point2D_other)
{
	C_Point2D Point2D_temp;
	Point2D_temp.x = x + Point2D_other.x;
	Point2D_temp.y = y + Point2D_other.y;
	return Point2D_temp;
}
#pragma endregion

#pragma region Methods
// --------------------------------------------------
//  Norm  
//  Alon Slapak 23/8/2015
// 	Description:	return the norm of this point: sqrt(x^2+y^2)
// 	Reference:		
//  Input value:	
//  Return Value:	norm of this point
// --------------------------------------------------
double C_Point2D::Norm()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

// --------------------------------------------------
//  Distance_between_points  
//  Alon Slapak 22/4/2015
// 	Description:	Calculate distance between 2 points
// 	Reference:		
//  Input value:	2 points
//  Return Value:	The distacne between the 2 points
// --------------------------------------------------
double C_Point2D::Distance_between_points(C_Point2D Point2D_other)
{
	return sqrt(pow(x - Point2D_other.x, 2) + pow(y - Point2D_other.y, 2));
}
// --------------------------------------------------
//  operator+=
//  Alon Slapak 23.8.2015
// 	Description:	+= opeartor
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value: 
// --------------------------------------------------
double C_Point2D::Distance_between_pointsVersion_2(C_Point2D Point2D_other)
{
	double x1 = x * (PI / 180);
	double x2 = Point2D_other.x * (PI / 180);

	double y1 = y * (PI / 180);
	double y2 = Point2D_other.y * (PI / 180);


	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// --------------------------------------------------
//  Distance_between_point_and_line  
//  Alon Slapak 24/4/2015
// 	Description:	Calculate distance between point and line (given by two points)
// 	Reference:		http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html Eq. (14)
//  Input value:	point, Line (given by 2 points)
//  Return Value:	The distacne between the point and the line
// --------------------------------------------------
double C_Point2D::Distance_between_point_and_line(C_Point2D Line_1, C_Point2D Line_2)
{
	double denominator, numerator;
	numerator = abs((Line_2.x - Line_1.x)*(Line_1.y - y) - (Line_1.x - x)*(Line_2.y - Line_1.y));
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
double C_Point2D::Line_angle(C_Point2D point_1, C_Point2D point_2)
{
	double x1, x2, y1, y2, t1, t2;
	double norm1, norm2, inner_prod;

	x1 = (point_2.x - point_1.x);
	y1 = (point_2.y - point_1.y);
	x2 = (x - point_1.x);
	y2 = (y - point_1.y);

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
C_Point2D C_Point2D::Line_point_projection(C_Point2D point_1, C_Point2D point_2)
{
	double t, x1, x2, y1, y2;
	C_Point2D closest_point;

	x1 = (point_2.x - point_1.x);
	y1 = (point_2.y - point_1.y);
	x2 = (x - point_1.x);
	y2 = (y - point_1.y);
	t = (x1 * x2 + y1 * y2) / (x1 * x1 + y1 * y1);

	closest_point.x = point_1.x + t * (point_2.x - point_1.x);
	closest_point.y = point_1.y + t * (point_2.y - point_1.y);

	return closest_point;
}
// --------------------------------------------------
//  Translate
//  Alon Slapak 25.8.2015
// 	Description:	shifting a cartesian point by the offsets
// 	Reference: 
//	Input Value:	offset to X and to Y
//  Return Value: 
// --------------------------------------------------
void C_Point2D::Translate(double offset_X, double offset_Y)
{
	x += offset_X;
	y += offset_Y;
}
// --------------------------------------------------
//  Translate
//  Alon Slapak 25.8.2015
// 	Description:	shifting a cartesian point by the offsets
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_Point2D::Translate(C_Point2D% offset)
{
	x += offset.x;
	y += offset.y;
}
// --------------------------------------------------
//  Rotate
//  Alon Slapak 25.8.2015
// 	Description:	Rotationg the coordinates system about the z axis
// 	Reference: 
//	Input Value:	Rotating angle [Radians]
//  Return Value: 
// --------------------------------------------------
void C_Point2D::Rotate(double theta)
{
	// --------------------------------------------------
	// To avoid changing the X and the Y during calculations
	// --------------------------------------------------
	double temp_x = cos(theta) * x - sin(theta) * y;
	double temp_y = sin(theta) * x + cos(theta) * y;

	x = temp_x;
	y = temp_y;
}
// --------------------------------------------------
//  Scale
//  Alon Slapak 25.8.2015
// 	Description:	Scaling the coordinates by 3 scaling factors
// 	Reference: 
//	Input Value:	Scaling factors to each of the coordinates
//  Return Value: 
// --------------------------------------------------
void C_Point2D::Scale(double ScaleX, double ScaleY)
{
	x *= ScaleX;
	y *= ScaleY;
}
#pragma endregion



