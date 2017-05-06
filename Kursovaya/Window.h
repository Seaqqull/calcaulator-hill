#if !defined(MY_WINDOW_H)

#define MY_WINDOW_H
#include <windows.h>
#include <iostream>
typedef unsigned int ui;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
class Window
{
protected:
	bool frame;
	char Characters[3];
	ui
		left, top, right, bottom,
		bgcolor, bordercolor, shadowcolor, textcolor, typeshadow;
public:

	Window(ui left = 0, ui top = 0, ui right = GetCols(), ui bottom = GetRows(), ui bgcolour = Green, ui shadowcolor = White, ui textcolor = Black, ui bordercolor = Black, bool frame = true);
	void ShowBackground();
	void Show();
	void Hide();
	void WriteString(ui x, ui y, const char * str, ui st = 0, ui w = 500, ui h = 500);
	void WriteChar(ui x, ui y, char str);
	ui GetLeft(){ return left; }
	ui GetTop(){ return top; }
	ui GetRight(){ return right; }
	ui GetBottom(){ return bottom; }
	friend void SetColor(ui, ui);
	friend void GotoXY(ui, ui);
	friend ui GetCurrentY();
	friend ui GetRows();
	friend ui GetCols();
	friend ui GetCurrentX();
	friend void SetSize(ui, ui);
	friend void CursorVisible(bool);

};

#endif;