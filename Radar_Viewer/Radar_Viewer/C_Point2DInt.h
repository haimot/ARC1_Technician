#ifndef C_POINT2DINT_H
#define C_POINT2DINT_H

//-----------------------------------------
//		Class:		C_point2DInt
//-----------------------------------------
public ref class C_Point2DInt
{
	//-----------------------------------------
	//		Fields
	//-----------------------------------------
	private:
	int screen_x;
	int screen_y;

	public:
	//-------------------------------------
	//			Default Constructor
	//-------------------------------------
	C_Point2DInt() {}
	//-------------------------------------
	//			Other Constructors
	//-------------------------------------						
	C_Point2DInt(int x, int y);
	//-------------------------------------
	//			Copy Constructor
	//-------------------------------------
	C_Point2DInt(C_Point2DInt% Point2DInt_other);
	//-------------------------------------------
	//			Get/Set X coordinate of point
	//-------------------------------------------
	property int Screen_X { int get(); void set(int screen_x_other); }
	//-------------------------------------------
	//			Get/Set Y coordinate of point
	//-------------------------------------------
	property int Screen_Y { int get(); void set(int screen_y_other); }
	//-------------------------------------------
	//			Get/Set X and Y coordinates of point
	//-------------------------------------------
	void set_Point(int New_x, int New_y);
	void set_Point(C_Point2DInt% Point2DInt_Other);
	//-------------------------------------------
	//			Methods
	//-------------------------------------------
	double Distance_between_points(C_Point2DInt% point);
	void Rotate(double theta);
	void Translate(C_Point2DInt% offset);
	void Translate(int offset_X, int offset_Y);
	void Scale(double ScaleX, double ScaleY);
	//-------------------------------------------
	//			Operators
	//-------------------------------------------
	void operator=(C_Point2DInt% Point2DInt_other);
	void operator+=(C_Point2DInt% Point2DInt_other);
	void operator-=(C_Point2DInt% Point2DInt_other);
	void operator*=(C_Point2DInt% Point2DInt_other);
	void operator*=(int Number);
	void operator=(int& Number);
};
#endif




