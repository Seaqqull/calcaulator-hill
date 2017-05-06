#include "Window.h"

void Window::WriteString(ui x, ui y, const char * str, ui st, ui w, ui h)
{
	if (x<0 || x>right - left - 2) return;
	if (y<0 || y>bottom - top - 2) return;
	ui i = 0;
	for (ui j = 0; j<h && top + 1 + y + j<bottom; j++)
	{
		GotoXY(left + 1 + x, top + 1 + y + j);
		for (ui k = 0; k < w && str && str[i] && str[i] != '\n' && left + 1 + x + k<right; i++, k++) printf("%c", str[i]);
		if (str[i] == '\n') i++;
		if (!str[i]) break;
	}
}

void Window::WriteChar(ui x, ui y, char str){
	if (x<0 || x>right - left - 2) return;
	if (y<0 || y>bottom - top - 2) return;
	ui i = 0;
	GotoXY(left + 1 + x, top + 1 + y);
	printf("%c", str);
}
Window::Window(ui left, ui top, ui right, ui bottom, ui bgcolour, ui shadowcolor, ui textcolor, ui bordercolor, bool frame)
{
	if (right < 2) right = GetCols() - 1;
	if (bottom < 2) bottom = GetRows() - 2;
	if (left < 0 || left >= GetCols() - 2) left = 0;
	if (top < 0 || top >= GetRows() - 2) top = 0;
	if (right - left < 2) right = left + 2;
	if (bottom - top < 2) bottom = top + 2;

	this->bgcolor = bgcolour;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	this->shadowcolor = shadowcolor;
	this->textcolor = textcolor;
	this->bordercolor = bordercolor;
	this->frame = frame;

	Characters[0] = (char)220;
	Characters[1] = (char)177;
	Characters[2] = (char)178;
}
void Window::Show()
{
	setlocale(LC_ALL, "C");
	ui i, j;
	SetColor(shadowcolor, bgcolor);
	GotoXY(left, top);
	printf("%c", Characters[0]);
	for (i = left + 1; i < right; i++)
	{
		printf("%c", Characters[1]);
	}
	SetColor(shadowcolor, bgcolor);
	printf("%c", Characters[0]);
	for (i = top + 1; i<bottom; i++)
	{
		SetColor(shadowcolor, bgcolor);
		GotoXY(left, i);
		ui right = this->right;
		if (frame)
		{
			printf("%c", Characters[2]);
		}
		else
		{
			GotoXY(left + 1, i);
			right--;
		}

		SetColor(bordercolor, bordercolor);
		for (j = left + 1; j < right; j++)
		{
			printf(" ");
		}
		if (frame)
		{
			SetColor(shadowcolor, bgcolor);
			printf("%c", Characters[2]);
		}
		else
		{
			printf(" ");
		}
	}
	SetColor(shadowcolor, bgcolor);
	GotoXY(left, bottom);
	printf("%c", Characters[0]);
	for (i = left + 1; i < right; i++)
	{
		printf("%c", Characters[1]);
	}
	printf("%c", Characters[0]);
	GotoXY(left + 2, top + 2);
	SetColor(textcolor, bordercolor);
	setlocale(LC_ALL, "RUSSIAN");
}
void Window::Hide()
{
	setlocale(LC_ALL, "C");
	ui i, j;
	SetColor(DarkGray, DarkGray);
	GotoXY(left, top);
	printf(" ");
	for (i = left + 1; i < right; i++)
	{
		printf(" ");
	}
	printf(" ");
	for (i = top + 1; i<bottom; i++)
	{
		GotoXY(left, i);
		ui right = this->right;
		if (frame)
		{
			printf(" ");
		}
		else
		{
			GotoXY(left + 1, i);
			right--;
		}

		for (j = left + 1; j < right; j++)
		{
			printf(" ");
		}
		if (frame)
		{
			printf(" ");
		}
		else
		{
			printf(" ");
		}
	}
	GotoXY(left, bottom);
	printf(" ");
	for (i = left + 1; i < right; i++)
	{
		printf(" ");
	}
	printf(" ");
	GotoXY(left + 2, top + 2);
	SetColor(textcolor, bordercolor);
	setlocale(LC_ALL, "RUSSIAN");
}
void Window::ShowBackground()
{
	SetColor(Black, DarkGray);
	for (ui j = top; j < bottom; j++)
	{
		GotoXY(left, j);
		for (ui i = left; i < right; i++)
		{
			printf(" ");
		}
	}
}
void SetColor(ui textcolor, ui bkcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(WORD)((bkcolor << 4) | textcolor));
}
void GotoXY(ui X, ui Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
ui GetCurrentY()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwCursorPosition.Y;
}
ui GetRows()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwSize.Y;
}
ui GetCols()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwSize.X;
}
ui GetCurrentX(){
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwCursorPosition.X;
}
void SetSize(ui X, ui Y)
{
	COORD coord = { X, Y };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void CursorVisible(bool action)
{
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = action;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}


