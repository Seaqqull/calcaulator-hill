#define _CRT_SECURE_NO_WARNINGS
#if !defined(MY_NUMERICS_H)

#define MY_NUMERICS_H
#include "String.h"
#include "Checkup.h"
#include "Window.h"
#include "Files_Struct.h"
#include "Hill_incryption.h"
using namespace std;
class Numerics
{
private:		
	String Base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	String Number = "", Number_ = "";
	ui Current_system = 2;
	Window *Show_system_Numeric, *Number_First_Window, *Number_Second_Window, *Result, *Information;

	String Get_Decimal(String Number, int system_);

	friend int Is_Similar(String Number, String Number_);

	void Is_writen();

	ui Get_Current(String str);

	String Get_Sum(String number_1, String number_2, int system_);

	String Get_Point(String number1, String number2, int system);

	String Get_Defference(String number1, String number2, int system);

	void Show_Result(char* Caption, String Answer);
public:
	Numerics();

	void Clear();

	~Numerics();			

	void Set_Numbers(bool flag, bool file_);

	void Set_System();
	
	void Show_Information(bool flag);

	void Consider_Sum();

	void Consider_Difference();

	void Consider_Point();
};
#endif