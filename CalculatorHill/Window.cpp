#include "Headers.h"


Window::Window(ui left, ui top, ui right, ui bottom, ui bgColour, ui shadowColor, ui textColor, ui borderColor, bool frame)
{
	if (right < 2) right = GetCols() - 1;
	if (bottom < 2) bottom = GetRows() - 2;
	if (left < 0 || left >= GetCols() - 2) left = 0;
	if (top < 0 || top >= GetRows() - 2) top = 0;
	if (right - left < 2) right = left + 2;
	if (bottom - top < 2) bottom = top + 2;

	_bgColor = bgColour;
	_left = left;
	_right = right;
	_top = top;
	_bottom = bottom;
	_shadowColor = shadowColor;
	_textColor = textColor;
	_borderColor = borderColor;
	_frame = frame;

	_characters[0] = (char)220; // Borders
	_characters[1] = (char)177; // Up - down
	_characters[2] = (char)178; // Left - Right
}


void Window::Show()
{
	ui i, j;


	GotoXY(_left, _top);
	SetColor(_shadowColor, _bgColor);
	printf("%c", _characters[0]);
	
	for (i = _left + 1; i < _right; i++)
	{
		printf("%c", _characters[1]);
	}
	

	SetColor(_shadowColor, _bgColor);
	printf("%c", _characters[0]);
	
	for (i = _top + 1; i < _bottom; i++)
	{
		GotoXY(_left, i);
		SetColor(_shadowColor, _bgColor);
		
		ui _right = this->_right;
		if (_frame)
		{
			printf("%c", _characters[2]);
		}
		else
		{
			GotoXY(_left + 1, i);
			_right--;
		}

		SetColor(_borderColor, _borderColor);
		for (j = _left + 1; j < _right; j++)
		{
			printf(" ");
		}
		if (_frame)
		{
			SetColor(_shadowColor, _bgColor);
			printf("%c", _characters[2]);
		}
		else
		{
			printf(" ");
		}
	}


	GotoXY(_left, _bottom);
	SetColor(_shadowColor, _bgColor);	
	printf("%c", _characters[0]);

	for (i = _left + 1; i < _right; i++)
	{
		printf("%c", _characters[1]);
	}
	
	printf("%c", _characters[0]);
	
	GotoXY(_left + 2, _top + 2);
	SetColor(_textColor, _borderColor);
}

void Window::Hide()
{
	ui i, j;
	
	GotoXY(_left, _top);
	SetColor(BACKGROUND_COLOR, BACKGROUND_COLOR);
	printf(" ");

	for (i = _left + 1; i < _right; i++)
	{
		printf(" ");
	}
	
	printf(" ");
	
	for (i = _top + 1; i < _bottom; i++)
	{
		GotoXY(_left, i);
		ui _right = this->_right;
		
		if (_frame)
		{
			printf(" ");
		}
		else
		{
			GotoXY(_left + 1, i);
			_right--;
		}

		for (j = _left + 1; j < _right; j++)
		{
			printf(" ");
		}
		if (_frame)
		{
			printf(" ");
		}
		else
		{
			printf(" ");
		}
	}
	
	GotoXY(_left, _bottom);
	printf(" ");
	
	for (i = _left + 1; i < _right; i++)
	{
		printf(" ");
	}
	
	printf(" ");
	
	GotoXY(_left + 2, _top + 2);
	SetColor(_textColor, _borderColor);	
}

void Window::WriteChar(ui x, ui y, char character)
{
	if (x<0 || x>_right - _left - 2) return;
	if (y<0 || y>_bottom - _top - 2) return;

	GotoXY(_left + 1 + x, _top + 1 + y);
	printf("%c", character);
}

void Window::WriteString(ui x, ui y, const char* str, ui w, ui h)
{
	if (x<0 || x>_right - _left - 2) return;
	if (y<0 || y>_bottom - _top - 2) return;

	ui i = 0;
	for (ui j = 0; j < h && _top + 1 + y + j < _bottom; j++)
	{
		GotoXY(_left + 1 + x, _top + 1 + y + j);
		for (ui k = 0; k < w && str && str[i] && str[i] != '\n' && _left + 1 + x + k < _right; i++, k++) 
			printf("%c", str[i]);
		if (str[i] == '\n') i++;
		if (!str[i]) break;
	}
}


ui Window::GetRows()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwSize.Y;
}

ui Window::GetCols()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwSize.X;
}

ui Window::GetCurrentX() {
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwCursorPosition.X;
}

ui Window::GetCurrentY()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwCursorPosition.Y;
}


void Window::ShowBackground()
{
	SetColor(BACKGROUND_COLOR, BACKGROUND_COLOR);

	for (ui j = 0; j < APP_HEIGHT; j++)
	{
		GotoXY(0, j);
		for (ui i = 0; i < APP_WIDTH; i++)
		{
			printf(" ");
		}
	}
}

void Window::GotoXY(SHORT X, SHORT Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Window::SetSize(SHORT X, SHORT Y)
{
	COORD coord = { X, Y };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Window::CursorVisible(bool action)
{
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = action;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

void Window::SetColor(ui textcolor, ui bkcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(WORD)((bkcolor << 4) | textcolor));
}


void Window::SetWindowTitle(wchar_t* title)
{
	SetConsoleTitle(title);
	delete title;
}

char* Window::ComposeString(size_t stringNumber, ...)
{
	std::vector<char*> strings;
	char* composedString;
	int overalSize = 0;
	va_list ap;
	
	va_start(ap, stringNumber);
	
	for (size_t i = 0; i < stringNumber; i++) {
		strings.push_back(va_arg(ap, char*));
		overalSize += strlen(strings.at(i));
	}

	composedString = new char[overalSize + 1];
	size_t stringPointer = 0;
	for (size_t i = 0; i < strings.size(); i++)
	{		
		for (size_t j = 0; j < strlen(strings[i]); j++)
		{
			composedString[stringPointer++] = strings[i][j];
		}		
	}
	composedString[stringPointer] = '\0';

	va_end(ap);

	return composedString;
}

wchar_t* Window::ComposeStringWide(size_t stringNumber, ...)
{
	std::vector<char*> strings;
	char* composedString;
	int overalSize = 0;
	va_list ap;

	va_start(ap, stringNumber);

	for (size_t i = 0; i < stringNumber; i++) {
		strings.push_back(va_arg(ap, char*));
		overalSize += strlen(strings.at(i));
	}

	composedString = new char[overalSize + 1];
	size_t stringPointer = 0;
	for (size_t i = 0; i < strings.size(); i++)
	{
		for (size_t j = 0; j < strlen(strings[i]); j++)
		{
			composedString[stringPointer++] = strings[i][j];
		}
	}
	composedString[stringPointer] = '\0';

	va_end(ap);

	wchar_t* composedStringW = new wchar_t[stringPointer * 2];
	mbstowcs(composedStringW, composedString, stringPointer + 1);	
	delete[] composedString;

	return composedStringW;
}
