#define _CRT_SECURE_NO_WARNINGS
#if !defined(MY_CHECKUP_H)

#define MY_CHECKUP_H


#include <iostream>
#include <windows.h>
#include <conio.h>
//#include <string.h>
//#include <stdlib.h> 
#include <malloc.h>

#define EVERYWHERE -1
#define ENTER 13
#define BACKSPACE 8
#define SPACE 32
#define LEFTROTATE 75
#define RIGHTROTATE 77
#define ADDITION 43
#define DELETE_ 83
#define ENHANCED_KEY_ 224
#define COUNT_OF(Array) (_msize(Array)/4) 
#define COUNT_OF_BOOl(Array) (_msize(Array))

typedef unsigned int ui;

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
	char * rules, *string;
	ui  left, right, *position;
	ui size, i;
	bool flag, *countP;

	//Check adition rules
	bool GetAdditionRules(int);
	//Add Symbol
	void AddSymbol(int);
	//Remove Symbol
	void RemoveSymbol();
	//Clear string in procees of writing 
	void Clear();
	//доп_размер
	int Size_of(int* mas)
	{
		int i = 0;
		while (mas)
			i++;
		return i;
	}
	//Coping
	void Copy(const Checkup&);

public:
	//Constructors!!!
	Checkup(ui left, ui right, ui size, ui* position = NULL, char* rules = NULL, bool* countP = NULL);
	Checkup(const Checkup& obj){ Copy(obj); }
	Checkup& operator =(const Checkup& obj){ Copy(obj); return *this; }
	~Checkup();

	//Rules!!!
	void SetRules(ui *position = NULL, char *rules = NULL, bool *countP = NULL);
	ui GetRulesLen(){ if (rules)return strlen(rules); else return 0; }
	
	//Adition Rule!!!
	char * GetRules() { return rules; }
	void GetRules(char *& rules);

	//Left Rule!!!
	void SetLeftRule(ui left){ if (left < right) this->left = left - 1; }
	ui GetLeftRule(){ return left + 1; }

	//Right Rule!!!
	void SetRightRule(ui right){ if (left < right) this->right = right + 1; }
	ui GetRightRule(){ return right - 1; }

	//Position of the Rules!!!
	ui* GetPositionAdditionRules(){ return position; }
	void GetPositionAdditionRules(ui *&position);

	//Posobility of rules!!!
	bool* GetCPositionAdditionRules(){ return countP; }
	void GetCPositionAdditionRules(bool *&countP);

	//Console Info!!!
	friend void GotoXY(CONSOLE_SCREEN_BUFFER_INFO c, ui i = NULL);
	friend CONSOLE_SCREEN_BUFFER_INFO  GetCurrentPosition();
	
	//String!!!
	void ClearString();
	ui GetStrLen(){ return strlen(string); }
	void NewStrLen(ui);
	ui GetSize(){ return size - 1; }

	//Message!!!
	void OutData(){ printf(string); }
	char* GetString() { return string; }
	void GetString(char *& string);

	//Input!!!
	void DoInput(ui y, ui x);

	//Convert
	int GetInt();
	double GetDouble();

	//Numerics
	//friend int ChoseSystem(int number);
};
#endif