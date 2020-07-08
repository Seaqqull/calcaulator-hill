#include "Headers.h"


String::String()
{
	_length = NULL;
	_str = NULL;
}

String::String(const char* line) : String()
{
	if (!line) return;

	_length = strlen(line);
	_str = new char[_length + 1];

	strcpy(_str, line);
	_str[_length] = '\0';
}

String::String(char c, int repeat) {
	_length = repeat;
	_str = new char[_length + 1];

	for (ui i = 0; i < _length; i++)
		_str[i] = c;
	_str[_length] = '\0';
}

String::String(const String& line_object) : String(line_object._str)
{

}

String::~String()
{
	if (_str) delete[] _str;
	_str = nullptr;
}


//methods

ui String::GetSize()
{
	return _length + 1;
}

ui String::GetLength()
{
	return _length;
}


void String::Conversaly() {
	char* newStr = new char[_length + 1];

	for (int i(_length - 1); i >= 0; i--)
		newStr[_length - i - 1] = _str[i];

	newStr[_length] = '\0';
	strcpy(_str, newStr);

	delete[] newStr;
}

char& String::GetAt(int position)
{
	return _str[position];
}

bool String::IsThere(char letter)
{
	for (ui i(0); i < _length; i++)
		if (_str[i] == letter) return true;
	return false;
}

int String::GetPosition(char letter) 
{
	if (IsThere(letter))
		for (ui i(0); i < _length; i++)
			if (_str[i] == letter)
				return i;
	return -1;
}

int String::Compare(const char* str) 
{
	return strcmp(this->_str, str);
}

String String::TrimLeft(char letter) 
{
	String s(_str);
	s.Conversaly();

	for (int i(s._length - 1); i >= 0; i--)
		if (s[i] == letter)
			--s;
		else
			break;

	s.Conversaly();
	return s;
}

String String::TrimRight(char letter) 
{
	String s(_str);

	for (int i(s._length - 1); i >= 0; i--)
		if (s[i] == letter)
			--s;
		else
			break;

	return s;
}

void String::SetAt(int position, char c) 
{
	_str[position] = c;
}

String String::Trim(char letter, bool from_beg, bool from_end) 
{
	String s(_str);

	if (from_end)
		s = s.TrimRight(letter);
	if (from_beg)
		s = s.TrimLeft(letter);

	return s;
}


int String::GetInt()
{
	return atoi(_str);
}

double String::GetDouble()
{
	return atof(_str);
}


//types

String::operator char* () 
{
	return _str;
}


//operators
//=
String& String::operator=(char otherChar) 
{
	if (_str)
		delete[] _str;

	_length = 1;
	_str = new char[_length + 1];

	_str[0] = otherChar;
	_str[_length] = '\0';

	return *this;
}

String& String::operator=(const int number)
{
	if (_str)
		delete[] _str;

	int count = 0;
	char buff[100];

	sprintf(buff, "%d", number);
	for (int i(0); i < 100; i++) {
		if (buff[i] != '\0') count++;
	}

	_length = count;
	_str = new char[_length + 1];

	strcpy(_str, buff);
	_str[_length] = '\0';

	return *this;
}

String& String::operator=(const long number)
{
	if (_str)
		delete[] _str;

	int count = 0;
	char buff[255];

	sprintf(buff, "%d", number);
	for (int i(0); i < 100; i++) {
		if (buff[i] != '\0') count++;
	}

	_length = count;
	_str = new char[_length + 1];

	strcpy(_str, buff);
	_str[_length] = '\0';

	return *this;
}

String& String::operator=(const char* otherString) 
{
	if (_str) delete[] _str;

	_length = strlen(otherString);
	_str = new char[_length + 1];

	strcpy(_str, otherString);
	_str[_length] = '\0';

	return *this;
}

String& String::operator=(const String& otherString)
{
	if (_str) delete[] _str;

	_length = otherString._length;
	_str = new char[_length + 1];

	strcpy(_str, otherString._str);
	_str[_length] = '\0';

	return *this;
}

//+
String String::operator+(char key) const
{
	String s(_str);
	s += key;
	return s;
}

String String::operator+(const char* otherString) const
{
	String s(_str);
	s += otherString;
	return s;
}

String String::operator+(const String& otherString) const
{
	String s(_str);
	s += otherString._str;
	return s;
}


String operator+(char key, const String& otherString)
{
	String s(key, 1);
	s += otherString._str;
	return s;
}

String operator+(const char* line_object, const String& otherString)
{
	String s(line_object);
	s += otherString._str;
	return s;
}


//==
bool String::operator==(const char* str)
{
	return Compare(str) == 0;
}

bool String::operator==(const String& otherString)
{
	return Compare(otherString._str) == 0;
}

bool operator==(const char* line_object, const String& otherString) {
	return strcmp(otherString._str, line_object) == 0;
}

//+=
String& String::operator+=(int number) 
{
	_length += 1;
	char* new_line = new char[_length + 1];

	strcpy(new_line, _str);
	delete[] _str;

	new_line[_length - 1] = 48 + number;
	new_line[_length] = '\0';
	_str = new_line;
	return *this;
}

String& String::operator+=(char letter)
{
	int count = (_str) ? _length : 0;

	char* new_line = new char[count + 2];

	if (_str) {
		strcpy(new_line, _str);
		delete[] _str;
	}

	new_line[count] = letter;
	new_line[count + 1] = '\0';

	_str = new_line;
	_length = ++count;

	return *this;
}

String& String::operator+=(const char* otherString)
{
	int count = strlen(otherString);
	if (count == 0) return *this;

	char* newString = new char[((_str) ? _length : 0) + count + 1];

	if (_str)
	{
		strcpy(newString, _str);
		delete[] _str;
	}
	strcat(newString, otherString);

	_str = newString;
	_length += count;
	_str[_length] = '\0';

	return *this;
}

String& String::operator+=(const String& otherString)
{
	if (otherString._length == 0) return *this;

	char* newString = new char[((_str) ? _length : 0) + otherString._length + 1];

	if (_str) {
		strcpy(newString, _str);
		delete[] _str;
	}
	strcat(newString, otherString._str);

	_str = newString;
	_length += otherString._length;
	_str[_length] = '\0';

	return *this;
}


void String::operator--()
{
	if (_length == 0) return;

	char* newStr = new char[_length];
	_length--;

	for (size_t i = 0; i < _length; i++)
		newStr[i] = _str[i];

	delete[] _str;

	_str = newStr;
	_str[_length] = '\0';
	//str[_length - 1] = NULL; _length--;
}

char& String::operator[](int position) 
{
	return GetAt(position);
}


void String::operator>>(const char* line_object)
{
	(*this) += line_object;
}


std::istream& operator>>(std::istream& ics, String& lineObject) 
{
	delete[] lineObject._str;

	char* newString = new char[50];

	ics >> newString;
	lineObject._str = new char[strlen(newString) + 1];
	
	strcpy(lineObject._str, newString);
	lineObject._length = strlen(lineObject._str);
	lineObject._str[lineObject.GetLength()] = '\0';
	
	delete[] newString;

	return ics;
}

std::ostream& operator<<(std::ostream& ocs, String& lineObject)
{
	ocs << lineObject._str;
	return ocs;
}
