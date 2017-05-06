#include "Checkup.h"

//Private
bool Checkup::GetAdditionRules(int key)
{
	bool flag = FALSE;
	if (GetRulesLen()){
		for (ui j = NULL; j < GetRulesLen(); j++){
			if (rules[j] == key && (position[j] == EVERYWHERE || (position[j] == i)))
			{
				flag = TRUE;				
				if (countP[j])
				{
					for (ui h = NULL; h < GetStrLen(); h++)
						if (string[h] == key)
						{							
							flag = FALSE;
							break;
						}
				}
			}
		}
	}
	return flag;
}
void Checkup::AddSymbol(int key)
{
	ui j = GetStrLen(); //¬ычислим размер строки
	if (j < size) //-1 ибо последний символ должен быть завершающим \0
		if (flag)// если была нажата клавиша "+"
		{
			if (i) //если строка не пуста (!)
			{
				if (j < size - 1) // чтобы случайно не поставить на позицию последнего \0
					while (i <= j) //ƒелаем сдвиг вправо (на указанный диапазон)
					{
						string[j + 1] = string[j];
						j--;
					}
			}
			else
			{
				j++;
				while (NULL < j) //ƒелаем сдвиг вправо (на указанный диапазон)
				{
					string[j] = string[j - 1];
					j--;
				}
			}
			string[i] = key;
		}
		else
		{
			string[i] = key;
			if (i >= j) //Ќо если мы записываем вконце
			{
				i++;
				string[i] = NULL;
			}
		}
}
void Checkup::RemoveSymbol()
{
	ui j = GetStrLen(); //¬ычислим размер строки
	if (j) // ≈сли строка не пуста (!)
	{
		if (i < j)
		{
			ui k = i;
			while (k < j) // —двиг влево
			{
				string[k] = string[k + 1];
				k++;
			}
		}
		else
		{
			i--; //ƒаже если мы шли по циклу,далее шаблонные действи€
			if (string[i]) string[i] = NULL; //¬ цикле мы могли случайно уже сделать присвоени€ нул€
		}
	}
}
void Checkup::Clear()
{
	GotoXY(C);
	for (ui j = NULL; j < GetStrLen(); j++) printf("%c", SPACE);
	ClearString();
	GotoXY(C);
}
void Checkup::Copy(const Checkup & obj)
{
	this->left = obj.left;
	this->right = obj.right;
	this->size = obj.size;
	//!!!
	this->position = obj.position;

	flag = obj.flag;
	i = obj.i;

	SetRules(obj.position, obj.rules, obj.countP);

	if (obj.string)
	{
		this->string = new char[strlen(obj.string) + 1];
		strcpy(this->string, obj.string);
	}
}

//Constructors
Checkup::Checkup(ui left, ui right, ui size, ui *position, char *rules, bool*countP)
{
	this->left = left - 1;
	this->right = right + 1;
	this->size = size + 1;

	flag = FALSE;
	i = NULL;

	SetRules(position, rules, countP);

	string = NULL;

	string = new char[size];
	memset(string, NULL, size);
}
Checkup::~Checkup()
{
	delete rules;
	//delete string;
	delete countP;
	delete position;
}

//Rules 
void Checkup::SetRules(ui *position, char *rules, bool *countP)
{
	if (rules)
	{
		this->rules = NULL;
		this->rules = new char[strlen(rules) + 1];
		strcpy(this->rules, rules);
	}
	if (position)
	{
		this->position = NULL;
		this->position = new ui[COUNT_OF(position)];//zamrna
		for (ui j = NULL; j < COUNT_OF(position); j++) this->position[j] = position[j];
	}
	if (countP)
	{
		this->countP = NULL;
		this->countP = new bool[COUNT_OF_BOOl(countP)];
		for (ui j = NULL; j < COUNT_OF_BOOl(countP); j++) this->countP[j] = countP[j];
	}
}

//Adition rules
void Checkup::GetRules(char *& rules)
{
	rules = new char[GetRulesLen() + 1];
	strcpy_s(rules, GetRulesLen() + 1, (const char*)this->rules);
}

//Position of Rules
void Checkup::GetPositionAdditionRules(ui *&position)
{
	position = new ui[COUNT_OF(this->position)];
	for (ui j = NULL; j < COUNT_OF(this->position); j++) position[j] = this->position[j];
}

//Posobility of Rules
void Checkup::GetCPositionAdditionRules(bool *&countP)
{
	countP = new bool[COUNT_OF_BOOl(this->position)];
	for (ui j = NULL; j < COUNT_OF_BOOl(this->position); j++) countP[j] = this->countP[j];
}

//Message
void Checkup::GetString(char *& string)
{
	string = new char[GetStrLen() + 1];
	strcpy(string, this->string);
}

//Console Info
void GotoXY(CONSOLE_SCREEN_BUFFER_INFO c, ui i)
{
	COORD coord = { c.dwCursorPosition.X + i, c.dwCursorPosition.Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
CONSOLE_SCREEN_BUFFER_INFO  GetCurrentPosition()
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
void Checkup::NewStrLen(ui size)
{
	string = NULL;
	string = new char[size + 1];
	memset(string, NULL, size + 1);
	this->size = size + 1;
}
void Checkup::ClearString()
{
	memset(string, NULL, GetStrLen());
	i = NULL;
}

//Input
void Checkup::DoInput(ui y, ui x)
{
	C.dwCursorPosition.X = x;
	C.dwCursorPosition.Y = y;
	ui key;
	//C = GetCurrentPosition();
	while (true)
	{
		GotoXY(C);
		printf(string);
		printf("%c", SPACE);
		GotoXY(C, i);
		key = _getch();
		if (((GetAdditionRules(key)) || (left < key && key < right)) && (i < size - 1)) AddSymbol(key);
		if (key == ENHANCED_KEY_) key = _getch();
		if (key == ENTER && i) break;
		if (key == BACKSPACE) RemoveSymbol();
		if (key == LEFTROTATE && i) i--;
		if (key == RIGHTROTATE && i < GetStrLen() && i >= NULL) i++;
		if (key == DELETE_) Clear();
		flag = (key == ADDITION) ? TRUE : FALSE;
	}
}

//Convert
int Checkup::GetInt(){
	return atoi(string);
}
double Checkup::GetDouble(){
	return atof(string);
}
