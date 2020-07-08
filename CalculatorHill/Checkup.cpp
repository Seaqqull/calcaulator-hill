#include "Headers.h"


//Constructors
Checkup::Checkup(ui left, ui right, ui size, int* position, char* rules, bool* countP)
{
	_right = right + 1;
	_left = left - 1;	
	_size = size + 1;

	_flag = FALSE;
	_i = NULL;

	SetRules(position, rules, countP);

	_string = NULL;

	_string = new char[size];
	memset(_string, NULL, size);
}

Checkup::~Checkup()
{
	delete[] _rules;
	//delete[] string;
	delete[] _countP;
	delete[] _position;
}


//Private
void Checkup::Clear()
{
	GotoXY(C);
	for (ui j = NULL; j < GetStrLen(); j++) printf("%c", SPACE);
	ClearString();
	GotoXY(C);
}

void Checkup::RemoveSymbol()
{
	ui j = GetStrLen(); 
	if (!j) return;

	if (_i < j)
	{
		ui k = _i;
		while (k < j)
		{
			_string[k] = _string[k + 1];
			k++;
		}
	}
	else
	{
		_i--;
		if (_string[_i]) _string[_i] = NULL;
	}
}

void Checkup::AddSymbol(int key)
{
	ui j = GetStrLen();
	if (j >= _size) return;

	if (_flag)
	{
		if (_i)
		{
			if (j < _size - 1)
				while (_i <= j)
				{
					_string[j + 1] = _string[j];
					j--;
				}
		}
		else
		{
			j++;
			while (NULL < j)
			{
				_string[j] = _string[j - 1];
				j--;
			}
		}
		_string[_i] = key;
	}
	else
	{
		_string[_i] = key;
		if (_i >= j)
		{
			_i++;
			_string[_i] = NULL;
		}
	}
}

void Checkup::Copy(const Checkup& obj)
{
	_right = obj._right;
	_left = obj._left;
	_size = obj._size;

	_position = obj._position;

	_flag = obj._flag;
	_i = obj._i;

	SetRules(obj._position, obj._rules, obj._countP);

	if (obj._string)
	{
		_string = new char[strlen(obj._string) + 1];
		strcpy(_string, obj._string);
	}
}

bool Checkup::GetAdditionRules(int key)
{
	bool flag = FALSE;

	if (!GetRulesLen())
		return TRUE;

	for (ui j = NULL; j < GetRulesLen(); j++) {
		if (_rules[j] == key &&
			((_position[j] == EVERYWHERE) || (_position[j] == _i)))
		{
			flag = TRUE;
			if (!_countP[j]) continue;

			for (ui h = NULL; h < GetStrLen(); h++)
				if (_string[h] == key)
				{
					flag = FALSE;
					break;
				}
		}
	}

	return flag;
}


//Rules 
void Checkup::SetRules(int* position, char* rules, bool* countP)
{
	if (rules)
	{
		_rules = NULL;
		_rules = new char[strlen(rules) + 1];
		strcpy(_rules, rules);
	}
	if (position)
	{
		_position = NULL;
		_position = new int[COUNT_OF(position)];
		for (ui j = NULL; j < COUNT_OF(position); j++) 
			_position[j] = position[j];
	}
	if (countP)
	{
		_countP = NULL;
		_countP = new bool[COUNT_OF_BOOl(countP)];
		for (ui j = NULL; j < COUNT_OF_BOOl(countP); j++) 
			_countP[j] = countP[j];
	}
}

//Adition rules
void Checkup::GetRules(char*& rules)
{
	rules = new char[GetRulesLen() + 1];
	strcpy_s(rules, GetRulesLen() + 1, (const char*)_rules);
}

//Position of Rules
void Checkup::GetPositionAdditionRules(int*& position)
{
	position = new int[COUNT_OF(_position)];
	for (ui j = NULL; j < COUNT_OF(_position); j++) 
		position[j] = _position[j];
}

//Posobility of Rules
void Checkup::GetCPositionAdditionRules(bool*& countP)
{
	countP = new bool[COUNT_OF_BOOl(_position)];
	for (ui j = NULL; j < COUNT_OF_BOOl(_position); j++) 
		countP[j] = _countP[j];
}

//Message
void Checkup::GetString(char*& string)
{
	string = new char[GetStrLen() + 1];
	strcpy(string, _string);
}

//Console Info
void Checkup::GotoXY(CONSOLE_SCREEN_BUFFER_INFO c, SHORT i)
{
	COORD coord = { c.dwCursorPosition.X + i, c.dwCursorPosition.Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

CONSOLE_SCREEN_BUFFER_INFO  Checkup::GetCurrentPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
	{
		c.dwCursorPosition.X = NULL;
		c.dwCursorPosition.Y = NULL;
	}
	return c;
}

//String
void Checkup::ClearString()
{
	memset(_string, NULL, GetStrLen());
	_i = NULL;
}

void Checkup::NewStrLen(ui size)
{
	_string = NULL;
	_string = new char[size + 1];

	memset(_string, NULL, size + 1);
	
	_size = size + 1;
}

//Input
void Checkup::DoInput(ui y, ui x)
{
	ui key;

	C.dwCursorPosition.X = x;
	C.dwCursorPosition.Y = y;
	
	//C = GetCurrentPosition();
	while (true)
	{
		GotoXY(C);
		printf(_string);
		printf("%c", SPACE);
		GotoXY(C, _i);
		key = _getch();
		if (((GetAdditionRules(key)) && (_left < key && key < _right)) && (_i < _size - 1)) AddSymbol(key);
		if (key == SPECIAL_KEY)
		{
			key = _getch();
			if (key == DELETE_) Clear();
		}
		if (key == ENTER && _i) break;
		if (key == BACKSPACE) RemoveSymbol();
		if (key == ARROW_LEFT && _i) _i--;
		if (key == ARROW_RIGHT && _i < GetStrLen() && _i >= NULL) _i++;
		
		_flag = (key == ADDITION) ? TRUE : FALSE;
	}
}

//Convert
int Checkup::GetInt() {
	return atoi(_string);
}

double Checkup::GetDouble() {
	return atof(_string);
}
