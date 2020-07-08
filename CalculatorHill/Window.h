#pragma once


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
	bool _frame;
	char _characters[3];
	ui
		_left, _top, _right, _bottom,
		_bgColor, _borderColor, _shadowColor, _textColor, _typeShadow;
public:
	Window(ui left = 0, ui top = 0, ui right = GetCols(), ui bottom = GetRows(), ui bgcolour = Green, ui shadowcolor = White, ui textcolor = Black, ui bordercolor = Black, bool frame = true);
	
	
	void Show();
	void Hide();	
	void WriteChar(ui x, ui y, char character);
	void WriteString(ui x, ui y, const char* str, ui w = 500, ui h = 500);
		
	ui GetTop() { return _top; }
	ui GetLeft() { return _left; }
	ui GetRight() { return _right; }
	ui GetBottom() { return _bottom; }

	static ui GetRows();
	static ui GetCols();
	static ui GetCurrentX();
	static ui GetCurrentY();

	static void ShowBackground();
	static void SetColor(ui, ui);
	static void CursorVisible(bool);
	static void GotoXY(SHORT, SHORT);
	static void SetSize(SHORT, SHORT);
	
	static void SetWindowTitle(wchar_t*);
	static char* ComposeString(size_t, ...);
	static wchar_t* ComposeStringWide(size_t, ...);
};
