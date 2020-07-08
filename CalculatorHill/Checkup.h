#pragma once


enum
{
	DIGIT_MIN = 48,
	DIGIT_MAX = 57,
	ENG_MIN_LOWER = 97,
	ENG_MAX_LOWER = 122,
	ENG_MIN_UPPER = 65,
	ENG_MAX_UPPER = 90
};


class Checkup
{
private:
	CONSOLE_SCREEN_BUFFER_INFO C;
	char* _rules, * _string;
	ui  _left, _right;
	int* _position;
	ui _size, _i;
	bool _flag, * _countP;

	
	void Clear();//Clear string in procees of writing 
	void AddSymbol(int);
	void RemoveSymbol();
	void Copy(const Checkup&);
	bool GetAdditionRules(int);	

public:
	//Constructors
	Checkup(ui left, ui right, ui size, int* position = NULL, char* rules = NULL, bool* countP = NULL);
	Checkup(const Checkup& obj) { Copy(obj); }
	Checkup& operator =(const Checkup& obj) { Copy(obj); return *this; }
	~Checkup();

	//Rules
	ui GetRulesLen() { return (_rules) ? strlen(_rules) : 0; }
	void SetRules(int* position = NULL, char* rules = NULL, bool* countP = NULL);

	//Adition Rule
	void GetRules(char*& rules);
	char* GetRules() { return _rules; }	

	//Left Rule	
	ui GetLeftRule() { return _left + 1; }
	void SetLeftRule(ui left) { if (left < _right) _left = left - 1; }

	//Right Rule
	ui GetRightRule() { return _right - 1; }
	void SetRightRule(ui right) { if (_left < right) _right = right + 1; }

	//Position of the Rules
	int* GetPositionAdditionRules() { return _position; }
	void GetPositionAdditionRules(int*& position);

	//Posobility of rules
	bool* GetCPositionAdditionRules() { return _countP; }
	void GetCPositionAdditionRules(bool*& countP);

	//Console Info
	static void GotoXY(CONSOLE_SCREEN_BUFFER_INFO c, SHORT i = NULL);
	static CONSOLE_SCREEN_BUFFER_INFO  GetCurrentPosition();

	//String
	void ClearString();
	void NewStrLen(ui);		
	ui GetSize() { return _size - 1; }
	ui GetStrLen() { return strlen(_string); }

	//Message
	void GetString(char*& string);
	void OutData() { printf(_string); }
	char* GetString() { return _string; }
	
	//Input
	void DoInput(ui y, ui x);

	//Convert
	int GetInt();
	double GetDouble();

};
