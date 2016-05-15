#ifndef C_Point2D_H
#define C_Point2D_H
//-----------------------------------------
//		Class:		Point2D
//-----------------------------------------
public ref class C_Point2D
{
	//-----------------------------------------
	//			Fields
	//-----------------------------------------
	private:
	double x;
	double y;

	public:
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	C_Point2D() {}
//-------------------------------------
//			Other Constructors
//-------------------------------------
C_Point2D(double x, double y);
//-------------------------------------
//			Copy Constructor
//-------------------------------------
C_Point2D(C_Point2D % other);


#pragma region property
//-------------------------------------------
//			X coordinate of point
//-------------------------------------------
property double X {double get(); void set(double x_other); }
//-------------------------------------------
//			Y coordinate of point
//-------------------------------------------
property double Y{double get(); void set(double y_other); }
#pragma endregion

#pragma region Methods
double Norm();
double Distance_between_points(C_Point2D Point2D_other);
double Distance_between_pointsVersion_2(C_Point2D Point2D_other);
double Distance_between_point_and_line(C_Point2D Line_1, C_Point2D Line_2);
double Line_angle(C_Point2D point_1, C_Point2D point_2);
C_Point2D Line_point_projection(C_Point2D point_1, C_Point2D point_2);
void Rotate(double theta);
void Translate(C_Point2D% offset);
void Translate(double offset_X, double offset_Y);
void Scale(double ScaleX, double ScaleY);
#pragma endregion

#pragma region Operator Overloading
void operator=(C_Point2D% Point2D_other);
void operator+=(C_Point2D% Point2D_other);
void operator-=(C_Point2D% Point2D_other);
void operator*=(C_Point2D% Point2D_other);
void operator*=(double Number);

bool operator==(C_Point2D% CartesianPoint_other);
bool operator!=(C_Point2D% CartesianPoint_other);

C_Point2D operator+(C_Point2D% Point2D_other);
C_Point2D operator-(C_Point2D% Point2D_other);
#pragma endregion
};
#endif  // of POINT2D_H



