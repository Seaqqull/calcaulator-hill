#include "Numerics.h"

Numerics::Numerics(){
	Show_system_Numeric = new Window(58, 1, 68, 5, Green, Blue, Blue, LightGray, false);
	Number_First_Window = new Window(26, 1, 56, 2, Green, Blue, Blue, LightGray, false);
	Number_Second_Window = new Window(26, 5, 56, 7, Green, Blue, Blue, LightGray, false);
	Result = new Window(26, 9, 61, 11, Green, Blue, Blue, LightGray, true);
	Information = new Window(26, 1, 61, 8, Green, Blue, Blue, LightGray, true);
	
	//Incryption_Words = new String(' ', 315);
}

Numerics::~Numerics(){
}

String Numerics::Get_Decimal(String Number, int system_){
	String Result;
	long pre_number = 0;

	for (ui i(0); i < Number.GetLength(); i++)
		for (ui j(0); j < 36; j++)
			if (Number[i] == Base[j])
				pre_number += (long)(j * pow(system_, (Number.GetLength() - i - 1)));//(long) - можно убрать
	Result = pre_number;

	return Result;
}

ui Numerics::Get_Current(String str){
	ui new_system = Current_system, pre_system = 0, i = 0;
	while (i<str.GetLength()){
		pre_system = Base.GetPosition(str[i++]) + 1;
		if (new_system < pre_system && pre_system >= Current_system) new_system = pre_system;
	}
	if (new_system > Current_system){
		for (ui i(2); i<37; i *= 2)
			if (i >= new_system){
				new_system = i;
				break;
			}
	}
	return new_system;
}

int Is_Similar(String Number, String Number_){
	if (Number.GetLength() > Number_.GetLength())
		return 1;
	else if (Number.GetLength() < Number_.GetLength())
		return -1;
	for (int i(Number.GetLength() - 1); i >= 0; i--){
		if ((int)(Number[i]) > (int)(Number_[i]))
			return 1;
		else if ((int)(Number[i]) < (int)(Number_[i]))
			return -1;
	}
	return 0;
}

String Numerics::Get_Sum(String number_1, String number_2, int system_){
	int major = 0, i_ = number_1.GetLength() - 1, j_ = number_2.GetLength() - 1,//1<2
		position_i = -1, position_j = -1;// current position in the entered numbers
	bool exit = false;//when Sum finished
	String Answer;
	do{
		if (i_ >= 0 && j_ >= 0){
			for (int i(0); i < system_; i++){
				if (position_i == -1)
					if (number_1[i_] == Base[i])	position_i = i;
				if (position_j == -1)
					if (number_2[j_] == Base[i])	position_j = i;
				if (position_i != -1 && position_j != -1)
					break;
			}
			if ((position_i + position_j + major) >= system_){
				Answer += Base[position_i + position_j + major - system_];
				major = 1;
			}
			else{
				Answer += Base[position_i + position_j + major];
				major = 0;
			}
			position_i = -1;
			position_j = -1;
			i_--;
			j_--;
		}
		else if (i_ >= 0 && j_ < 0){
			for (int i(0); i < system_; i++)
				if (number_1[i_] == Base[i])	position_i = i;

			if ((position_i + major) >= system_){
				Answer += Base[position_i + major - system_];
				major = 1;
			}
			else{
				Answer += Base[position_i + major];
				major = 0;
			}
			i_--;
		}
		else if (j_ >= 0 && i_ < 0){
			for (int i(0); i < system_; i++)
				if (number_2[j_] == Base[i])	position_j = i;

			if ((position_j + major) >= system_){
				Answer += Base[position_j + major - system_];
				major = 1;
			}
			else{
				Answer += Base[position_j + major];
				major = 0;
			}
			j_--;
		}
		else{
			Answer += '1';
			major = 0;
			exit = true;
		}
		if (i_ < 0 && j_ < 0 && major == 0)
			exit = true;

	} while (!exit);
	Answer.Conversaly();
	return Answer;
}

String Numerics::Get_Point(String number1, String number2, int system_){
	String Answer("0");
	String Current("");
	int major = NULL, /*i_ = number_1.GetLength() - 1, j_ = number_2.GetLength() - 1,*///1<2
		position_i = 0, position_j = 0, current_Point = NULL;// current position in the entered numbers
	for (int i(number1.GetLength() - 1); i >= 0; i--){
		for (int k(0); k < system_; k++)
			if (number1[i] == Base[k]){ position_i = k; break; }
		for (int j(number2.GetLength() - 1); j >= 0; j--){
			for (int k(0); k < system_; k++)
				if (number2[j] == Base[k]){ position_j = k; break; }
			current_Point = position_i * position_j;
			
			if ((current_Point + major) % system_ >= system_){
				Current += Base[((current_Point + major) % system_) - system_];
				major = 1;
			}
			else{
				Current += Base[(current_Point + major) % system_];
				major = (current_Point + major) / system_;
			}
		}	
		if (major != NULL) Current += Base[major];
		major = NULL;

		Current.Conversaly();
		for (ui k(i); k < number1.GetLength() - 1; k++) Current += "0";

		Answer.Conversaly();		
		Answer = Get_Sum(Answer, Current, system_);
		Answer.Conversaly();		
		Current = "";
	}

	Answer.Conversaly();
	return Answer;
}

String Numerics::Get_Defference(String number1, String number2, int system_){
	String Answer("");
	int major = 0, i_ = number1.GetLength() - 1, j_ = number2.GetLength() - 1,//1<2
		position_i = number1.GetLength() - 1, position_j = number2.GetLength() - 1,
		hlp = 0;// current position in the entered numbers
	bool exit = false;//when Sum finished
	if (Is_Similar(number1, number2) == 1){
		do{
			for (int i(0); i < system_; i++)
				if (number1[position_i] == Base[i]){ i_ = i; break; }

			for (int i(0); i < system_; i++)
				if (number2[position_j] == Base[i]){ j_ = i; break; }

			if (i_ - j_ < 0){
				for (int i(position_i - 1); i >= 0; i--){
					if (number1[i] == Base[0])
						number1[i] = Base[system_ - 1];
					else{
						for (int j(0); j < system_; j++)
							if (number1[i] == Base[j]) number1[i] = Base[j - 1];
						//место для удаления 0 на первой позиции
						break;
					}
				}
				number1[position_i] = Base[system_ + i_ - j_];
				Answer += number1[position_i];
			}
			else
				Answer += Base[i_ - j_];			

			position_i--;
			position_j--;
			
			if (position_j == -1 && position_i != -1){
				for (int i(position_i); i >= 0; i--)
					Answer += number1[i];
				exit = true;
			}
			if (position_j == -1 && position_i == -1) exit = true;
		} while (!exit);
		for (int i(Answer.GetLength() - 1);; i--)
			if (Answer[i] == '0') hlp++;
			else {
				for (int j(hlp); j > 0; j--)
					--Answer;
				break;
			}
	}
	else if (Is_Similar(number1, number2) == -1){
		do{
			for (int i(0); i < system_; i++)
				if (number1[position_i] == Base[i]) i_ = i;

			for (int i(0); i < system_; i++)
				if (number2[position_j] == Base[i]) j_ = i;

			if (j_ - i_ < 0){
				for (int i(position_j - 1); i >= 0; i--){
					if (number2[i] == Base[0])
						number2[i] = Base[system_ - 1];
					else{
						for (int j(0); j < system_; j++)
							if (number2[i] == Base[j]) number2[i] = Base[j - 1];
						//место для удаления 0 на первой позиции
						break;
					}
				}
				number2[position_j] = Base[system_ + j_ - i_];
				Answer += number2[position_j];
			}
			else{
				number2[position_j] = Base[j_ - i_];
				Answer += number2[position_j];
			}

			position_i--;
			position_j--;

			if (position_i == -1 && position_j != -1){
				for (int i(position_j); i > 0; i--)
					Answer += number2[i];
				exit = true;
			}

			if (position_j == -1 && position_i == -1) exit = true;
		} while (!exit);

		for (int i(Answer.GetLength() - 1);; i--)
			if (Answer[i] == '0') hlp++;
			else {
				for (int j(hlp); j > 0; j--)
					--Answer;
				break;
			}
		Answer += "-";
	}
	else
		Answer = "0";

	Answer.Conversaly();

	return Answer;
}

void Numerics::Is_writen(){
	if (Number == "")
		Set_Numbers(true, false);
	if (Number_ == "")
		Set_Numbers(false, false);
}

void Numerics::Set_Numbers(bool flag, bool file_){
	if (Number == "" && Number_ == "")
		Window().ShowBackground();
	char* number = new char[3];
	sprintf(number, "%d", Current_system);
	Show_system_Numeric->Show();
	Show_system_Numeric->WriteString(0, 0, "<-Вверх->");
	Show_system_Numeric->WriteString(0, 2, "<-Вниз ->");
	Show_system_Numeric->WriteString(3, 1, "   ");
	Show_system_Numeric->WriteString(4, 1, number);
	Checkup Number_check(48, (Current_system > 10)? 64 + Current_system - 10 : 47 + Current_system, 5/*, position_wtite, letters, can_write*/);
	
	if (flag){
		if (file_){			
			Files_Struct Fs;
			if (Fs.Open_Number(Number)){				
				Number_First_Window->Show();
				Number_First_Window->WriteString(1, 0, "Первое число:");
				Number = Number.TrimLeft('0');
				Current_system = Get_Current(Number);
				Number_First_Window->WriteString(15, 0, Number);
			}
			SetConsoleTitle(TEXT("Numerics"));
		}
		else{
			Number_First_Window->Show();
			Number_First_Window->WriteString(1, 0, "Введите первое число:");
			Number_check.DoInput(2, 49);
			Number = Number_check.GetString();
			Number_check.ClearString();
			Number_First_Window->Show();
			Number_First_Window->WriteString(1, 0, "Первое число:");
			Number = Number.TrimLeft('0');
			Number_First_Window->WriteString(15, 0, Number);
		}
	}
	else{
		if (file_){
			Files_Struct Fs;								
			if (Fs.Open_Number(Number_)){
				Number_Second_Window->Show();
				Number_Second_Window->WriteString(1, 0, "Второе число:");
				Number_ = Number_.TrimLeft('0');
				Current_system = Get_Current(Number_);
				Number_Second_Window->WriteString(15, 0, Number_);
			}
			SetConsoleTitle(TEXT("Numerics"));
		}
		else{
			Number_Second_Window->Show();
			Number_Second_Window->WriteString(1, 0, "Введите второе число:");
			Number_check.DoInput(6, 49);
			Number_ = Number_check.GetString();
			Number_check.ClearString();
			Number_Second_Window->Show();
			Number_Second_Window->WriteString(1, 0, "Второе число:");
			Number_ = Number_.TrimLeft('0');
			Number_Second_Window->WriteString(15, 0, Number_);
		}
	}
	sprintf(number, "%d", Current_system);
	Show_system_Numeric->WriteString(3, 1, "   ");
	Show_system_Numeric->WriteString(4, 1, number);
}

void Numerics::Set_System(){
	if (Number == "" && Number_ == "")
		Window().ShowBackground();
	int ch = 0;
	char* number = new char[3];
	Show_system_Numeric->Show();
	Show_system_Numeric->WriteString(0, 0, "<-Вверх->");
	Show_system_Numeric->WriteString(0, 2, "<-Вниз ->");
	sprintf(number, "%d", Current_system);
	Show_system_Numeric->WriteString(2, 1, "   ");
	Show_system_Numeric->WriteString(4, 1, number);	
	do{
		
		ch = _getch();
		switch (ch){
		case 72:
			if (Current_system < 36) Current_system++;
			else if (Current_system == 36)	Current_system = 2;
			break;
		case 80:
			if (Current_system > 2) Current_system--;
			else if (Current_system == 2) Current_system = 36;
			break;
		case 13:
			ch = -1;
			break;
		}		
		sprintf(number, "%d", Current_system);
		Show_system_Numeric->WriteString(3, 1, "   ");
		Show_system_Numeric->WriteString(4, 1, number);
	} while (ch != -1);
	if (!(Number == ""))
		Current_system = Get_Current(Number);			
	if (!(Number_ == ""))
		Current_system = Get_Current(Number_);
	sprintf(number, "%d", Current_system);
	Show_system_Numeric->WriteString(3, 1, "   ");
	Show_system_Numeric->WriteString(4, 1, number);
}

void Numerics::Show_Result(char* Caption, String Answer){
	Result->Show();
	Result->WriteString(1, 0, Caption);
	Result->WriteString(15, 0, Answer);
	ofstream Ofs;
	Ofs.open("Result.txt", ios::out);
	Ofs << Number << ' ' << Caption << ' ' << Number_ << ' ' << Answer;
	Ofs.close();
	_getch();
	Number = Number_ = "";
	Window().ShowBackground();
}

void Numerics::Show_Information(bool flag){
	Window ().ShowBackground();
	Information->Show();
	if (flag){
		Information->WriteString(6, 0, "-----О приложении-----");
		Information->WriteString(1, 1, "Приложение вычисляет:");
		Information->WriteString(1, 2, "Сложение, умножение, разность.");
		Information->WriteString(1, 3, "Чисел в различных системах счисления.");
		Information->WriteString(1, 5, "Шифрует, дешифрует сообщения.");
		_getch();
		Information->Hide();
	}
	else{
		Information->WriteString(6, 0, "---Работа с файлами---");
		Information->WriteString(1, 1, "Числа считываются/записываются по таким правилам:");
		Information->WriteString(1, 3, "Число");
		Information->WriteString(1, 4, "Перед считыванием выберите желаемую систему счисления.");
		_getch();
		Information->Hide();
	}	
}

void Numerics::Consider_Sum(){	
	Is_writen();
	Show_Result("Сумма", Get_Sum(Number, Number_, Current_system));
}

void Numerics::Consider_Difference(){
	Is_writen();
	Show_Result("Разность", Get_Defference(Number, Number_, Current_system));
}

void Numerics::Consider_Point(){
	Is_writen();
	Show_Result("Произвидение", Get_Point(Number, Number_, Current_system));
}

void Numerics::Clear(){
if (!(Number == "") || !(Number_ == ""))
	Window().ShowBackground();
Number = Number_ = ""; 
}
