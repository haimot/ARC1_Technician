#include "C_Point2DInt.h"
#include <iostream>

//#include <iostream>

//-------------------------------------
//			Other Constructors
//-------------------------------------						
C_Point2DInt::C_Point2DInt(int x, int y) : screen_x(x), screen_y(y) { }
//-------------------------------------
//			Copy Constructor
//-------------------------------------
C_Point2DInt::C_Point2DInt(C_Point2DInt % Point2DInt_other) : screen_x(Point2DInt_other.screen_x), screen_y(Point2DInt_other.screen_y) {}


//-------------------------------------------
//			Get/Set X coordinate of point
//-------------------------------------------
int C_Point2DInt::Screen_X::get() { return screen_x; }
void C_Point2DInt::Screen_X::set(int screen_x_other) { screen_x = screen_x_other; }

//int C_Point2DInt::get_X() { return screen_x; }
//void C_Point2DInt::set_X(int x_other) { screen_x = x_other; }
//-------------------------------------------
//			Get/Set Y coordinate of point
//-------------------------------------------
int C_Point2DInt::Screen_Y::get() { return screen_y; }
void C_Point2DInt::Screen_Y::set(int screen_y_other) { screen_y = screen_y_other; }

//int C_Point2DInt::get_Y() { return screen_y; }
//void C_Point2DInt::set_Y(int y_other) { screen_y = y_other; }
//-------------------------------------------
//			Get/Set X and Y coordinates of point
//-------------------------------------------
//-------------------------------------------
//			Get/Set X and Y coordinates of point
//-------------------------------------------
void C_Point2DInt::set_Point(int New_x, int New_y)
{
	screen_x = New_x;
	screen_y = New_y;
}
void C_Point2DInt::set_Point(C_Point2DInt% Point2DInt_Other)
{
	screen_x = Point2DInt_Other.screen_x;
	screen_y = Point2DInt_Other.screen_y;
}

// --------------------------------------------------
//  operator+=
//  Haim Otachi 23.8.2015
// 	Description:	+= opeartor
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value: 
// --------------------------------------------------
void C_Point2DInt::operator+=(C_Point2DInt% Point2DInt_other)
{
	screen_x = screen_x + Point2DInt_other.screen_x;
	screen_y = screen_y + Point2DInt_other.screen_y;
}
// --------------------------------------------------
//  operator-=
//  Haim Otachi 23.8.2015
// 	Description:	-= opeartor
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value: 
// --------------------------------------------------
void C_Point2DInt::operator-=(C_Point2DInt% Point2DInt_other)
{
	screen_x = screen_x - Point2DInt_other.screen_x;
	screen_y = screen_y - Point2DInt_other.screen_y;
}

// --------------------------------------------------
//  operator =
//  Haim Otachi 23.8.2015
// 	Description:	= opeartor (assignment)
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value: 
// --------------------------------------------------
void C_Point2DInt::operator=(C_Point2DInt% Point2DInt_other)
{
	screen_x = Point2DInt_other.screen_x;
	screen_y = Point2DInt_other.screen_y;
}
// --------------------------------------------------
//  operator*=
//  Haim Otachi 23.8.2015
// 	Description:	*= opeartor (Matlab-like .* operation with another class) 
// 	Reference: 
//	Input Value:	reference to other struct
//  Return Value: 
// --------------------------------------------------
void C_Point2DInt::operator*=(C_Point2DInt% Point2DInt_other)
{
	screen_x = screen_x * Point2DInt_other.screen_x;
	screen_y = screen_y * Point2DInt_other.screen_y;
}
// --------------------------------------------------
//  operator*=
//  Haim Otachi 23.8.2015
// 	Description:	*= opeartor   (constant value)
// 	Reference: 
//	Input Value:	constant integer
//  Return Value: 
// --------------------------------------------------
void C_Point2DInt::operator*=(int Number)
{
	screen_x = screen_x * Number;
	screen_y = screen_y * Number;
}

void C_Point2DInt::operator=(int& Number)
{
	screen_x = Number;
	screen_y = Number;
}

// --------------------------------------------------
//  Distance_between_points  
//  Alon Slapak 22/4/2015
// 	Description:	Calculate distance between 2 points
// 	Reference:		
//  Input value:	2 points
//  Return Value:	The distacne between the 2 points
// --------------------------------------------------
double C_Point2DInt::Distance_between_points(C_Point2DInt% Point2DInt_other)
{
	return sqrt(pow(screen_x - Point2DInt_other.screen_x, 2) + pow(screen_y - Point2DInt_other.screen_y, 2));
}

// --------------------------------------------------
//  Translate
//  Alon Slapak 25.8.2015
// 	Description:	shifting a cartesian point by the offsets
// 	Reference: 
//	Input Value:	offset to X and to Y
//  Return Value: 
// --------------------------------------------------
void C_Point2DInt::Translate(int offset_X, int offset_Y)
{
	screen_x += offset_X;
	screen_y += offset_Y;
}
// --------------------------------------------------
//  Translate
//  Alon Slapak 25.8.2015
// 	Description:	shifting a cartesian point by the offsets
// 	Reference: 
//	Input Value:	reference to other class
//  Return Value: 
// --------------------------------------------------
void C_Point2DInt::Translate(C_Point2DInt% offset)
{
	screen_x += offset.screen_x;
	screen_y += offset.screen_y;
}
// --------------------------------------------------
//  Rotate
//  Alon Slapak 25.8.2015
// 	Description:	Rotationg the coordinates system about the z axis
// 	Reference: 
//	Input Value:	Rotating angle [Radians]
//  Return Value: 
// --------------------------------------------------
void C_Point2DInt::Rotate(double theta)
{
	// --------------------------------------------------
	// To avoid changing the X and the Y during calculations
	// --------------------------------------------------
	double temp_x = cos(theta) * screen_x - sin(theta) * screen_y;
	double temp_y = sin(theta) * screen_x + cos(theta) * screen_y;

	screen_x = (int)temp_x;
	screen_y = (int)temp_y;
}
// --------------------------------------------------
//  Scale
//  Alon Slapak 25.8.2015
// 	Description:	Scaling the coordinates by 3 scaling factors
// 	Reference: 
//	Input Value:	Scaling factors to each of the coordinates
//  Return Value: 
// --------------------------------------------------
void C_Point2DInt::Scale(double ScaleX, double ScaleY)
{
	screen_x = (int)(ScaleX * screen_x);
	screen_y = (int)(ScaleY * screen_y);
}



