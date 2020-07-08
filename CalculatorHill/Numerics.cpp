#include "Headers.h"

Numerics::Numerics() {
	BASE_POSITION = std::vector<int>(BASE.GetLength());
	BASE_POSITION_A = new int[BASE.GetLength()];
	std::fill(BASE_POSITION.begin(), BASE_POSITION.end(), EVERYWHERE);
	std::copy(BASE_POSITION.begin(), BASE_POSITION.end(), BASE_POSITION_A);

	BASE_COUNT = std::vector<bool>(BASE.GetLength());
	BASE_COUNT_A = new bool[BASE.GetLength()];
	std::fill(BASE_COUNT.begin(), BASE_COUNT.end(), FALSE);
	std::copy(BASE_COUNT.begin(), BASE_COUNT.end(), BASE_COUNT_A);
	
	
	_wNumberSecond = new Window(26, 6, 56, 9, Green, Blue, Blue, WINDOW_COLOR, false);
	_wNumberFirst = new Window(26, 1, 56, 4, Green, Blue, Blue, WINDOW_COLOR, false);
	_wResult = new Window(26, 11, 61, 14, Green, Blue, Blue, WINDOW_COLOR, true);

	_wInformation = new Window(26, 1, 61, 8, Green, Blue, Blue, WINDOW_COLOR, true);
	
	_wSystem = new Window(58, 1, 68, 5, Green, Blue, Blue, WINDOW_COLOR, false);
}


void Numerics::AreWriten() {
	if (_nFirst == "")
		SetNumbers(true, false);
	if (_nSecond == "")
		SetNumbers(false, false);
}

ui Numerics::GetCurrentSystem(String number) {
	ui newSystem = _system, preNewSystem = 0, i = 0;

	while (i < number.GetLength()) {
		preNewSystem = BASE.GetPosition(number[i++]) + 1;
		
		if ((newSystem < preNewSystem) && 
			(preNewSystem >= _system)) 
			newSystem = preNewSystem;
	}
	
	if (newSystem > _system) {
		for (ui i(2); i < 37; i *= 2)
			if (i >= newSystem) {
				newSystem = i;
				break;
			}
	}
	
	return newSystem;
}

String Numerics::GetDecimal(String number, int system) {
	String numberDec;
	long numberBuffer = 0;

	for (ui i(0); i < number.GetLength(); i++)
		for (ui j(0); j < 36; j++)
			if (number[i] == BASE[j])
				numberBuffer += (long)(j * pow(system, (number.GetLength() - i - 1)));
	numberDec = numberBuffer;

	return (number[0] == '-')? ('-' + numberDec) : numberDec;
}

void Numerics::ShowResult(char* caption, String answer) {
	_wResult->Show();

	_resultCaption = String(caption);
	_resultCaption += ": ";
	
	_wResult->WriteString(1, 0, _resultCaption + answer);

	_inDecimal = GetDecimal(answer, _system);
	_wResult->WriteString(1, 1, "In decimal: " + _inDecimal);

	std::ofstream Ofs;

	Ofs.open("Result.txt", std::ios::out);
	Ofs << caption << '(' << _system << "): " << _nFirst << ',' << _nSecond << " -> " << answer;
	Ofs.close();

	_getch();
	_nFirst = _nSecond = "";

	Window::ShowBackground();
}

String Numerics::GetSum(String nFirst, String nSecond, int system) {
	int major = 0, position_i = nFirst.GetLength() - 1, position_j = nSecond.GetLength() - 1,//1<2
		i_ = -1, j_ = -1;// current position in the entered numbers
	String Answer;

	do {
		if (position_i >= 0 || position_j >= 0) {			
			for (int i(0); i < system && position_i >= 0; i++) // Find absolute rank-value in base
				if (nFirst[position_i] == BASE[i]) { i_ = i; break; }

			for (int i(0); i < system && position_j >= 0; i++) // Find absolute rank-value in base
				if (nSecond[position_j] == BASE[i]) { j_ = i; break; }

			if ((i_ + j_ + major) >= system) {
				Answer += BASE[i_ + j_ + major - system];
				major = 1;
			}
			else {
				Answer += BASE[i_ + j_ + major];
				major = 0;
			}

			position_i--;
			position_j--;

			i_ = 0;
			j_ = 0;
		}
		else {
			Answer += '1';
			major = 0;
			break;
		}
		if (position_i < 0 && position_j < 0 && major == 0)
			break;
	} while (true);

	Answer.Conversaly();

	return Answer;
}

String Numerics::GetDifference(String nFirst, String nSecond, int system)
{
	int numberSimilarity = AreSimilar(nFirst, nSecond);

	if (numberSimilarity == 0) return "0"; // Equal
	else if (numberSimilarity == 1) // First bigger
	{
		String tmp(nFirst);
		nFirst = String(nSecond);
		nSecond = String(tmp);
	}

	String answer("");

	int i_, j_,//1<2
		position_i = nFirst.GetLength() - 1, position_j = nSecond.GetLength() - 1,
		hlp = 0;// current position in the entered numbers

	// nFirst - smaller
	// nSecond - bigger
	do {
		for (int i(0); i < system; i++) // Find absolute rank-value in base
			if (nFirst[position_i] == BASE[i]) { i_ = i; break; }

		for (int i(0); i < system; i++) // Find absolute rank-value in base
			if (nSecond[position_j] == BASE[i]) { j_ = i; break; }

		if (j_ - i_ < 0) { // If we can't substract from bigger without taking additional value higher rank
			for (int i(position_j - 1); i >= 0; i--) {
				if (nSecond[i] == BASE[0]) // If already the smallest rank
				{
					nSecond[i] = BASE[system - 1];
					continue;
				}

				// We substract 1 from higher rank and use in calculating for current(lower-rank)
				for (int j(0); j < system; j++)
					if (nSecond[i] == BASE[j]) { nSecond[i] = BASE[j - 1]; break; }
				break;
			}
			answer += BASE[system + j_ - i_];
		}
		else // Otherwise we just assign absolute value of substracted rank
			answer += BASE[j_ - i_];

		position_i--;
		position_j--;

		if (position_j == -1 && position_i == -1) break; // If we can't continue substraction
		else if (position_i == -1 && position_j != -1) { // If higher-rank numbers have left
			for (int i(position_j); i >= 0; i--) // Assign remaining higher rank numbers
				answer += nSecond[i];
			break;
		}
		
	} while (true);

	for (int i(answer.GetLength() - 1);; i--) // Remove from end(beginning of the resulted number): 0's
	{
		if (answer[i] == '0') { hlp++; continue; }
		for (int j(hlp); j > 0; j--)
			--answer;
		break;
	}
				
	if(numberSimilarity == -1)
		answer += "-";
	answer.Conversaly(); // Reverse, to present number in the proper order

	return answer;
}

String Numerics::GetMultiplication(String number1, String number2, int system_) {
	String Answer("0");
	String Current("");

	int major = NULL,
		i_ = 0, j_ = 0, current_Point = NULL; // current position in the entered numbers
	
	for (int i(number1.GetLength() - 1); i >= 0; i--) {
		for (int k(0); k < system_; k++) // Find absolute rank-value in base
			if (number1[i] == BASE[k]) { i_ = k; break; }

		for (int j(number2.GetLength() - 1); j >= 0; j--) {
			for (int k(0); k < system_; k++) // Find absolute rank-value in base
				if (number2[j] == BASE[k]) { j_ = k; break; }

			current_Point = i_ * j_; // Calculate multiplicated rank

			// Fitting getted rank into current system
			if ((current_Point + major) % system_ >= system_) { 
				Current += BASE[((current_Point + major) % system_) - system_];
				major = 1;
			}
			else {
				Current += BASE[(current_Point + major) % system_];
				major = (current_Point + major) / system_;
			}
		}

		if (major != NULL) Current += BASE[major];
		major = NULL;

		Current.Conversaly();
		for (ui k(i); k < number1.GetLength() - 1; k++) Current += "0";
		Answer.Conversaly();

		Answer = GetSum(Answer, Current, system_);
		Answer.Conversaly();
		
		Current = "";
	}

	Answer.Conversaly(); // Reverse, to present number in the proper order
	return Answer;
}


void Numerics::Clear() {
	if (!(_nFirst == "") || !(_nSecond == ""))
		Window::ShowBackground();

	_nFirst = _nSecond = "";
}

void Numerics::SetSystem() {
	if (_nFirst == "" && _nSecond == "")
		Window::ShowBackground();

	int inputCharacter = 0;
	char* number = new char[3];

	_wSystem->Show();
	_wSystem->WriteString(0, 0, "<- Up ->");
	_wSystem->WriteString(0, 2, "<-Down->");

	sprintf(number, "%d", _system);

	_wSystem->WriteString(2, 1, "   ");
	_wSystem->WriteString(4, 1, number);

	do {

		inputCharacter = _getch();

		switch (inputCharacter) {
			case ARROW_UP:
				if (_system < 36) _system++;
				else if (_system == 36)	_system = 2;
				break;
			case ARROW_DOWN:
				if (_system > 2) _system--;
				else if (_system == 2) _system = 36;
				break;
			case ENTER:
				inputCharacter = -1;
				break;
		}

		sprintf(number, "%d", _system);
		
		_wSystem->WriteString(3, 1, "   ");
		_wSystem->WriteString(4, 1, number);
	} while (inputCharacter != -1);
	
	if (!(_nFirst == ""))
	{
		_system = GetCurrentSystem(_nFirst);

		_inDecimal = GetDecimal(_nFirst, _system);
		
		_wNumberFirst->WriteString(1, 1, (char*)(new String(' ', _wNumberFirst->GetRight() - _wNumberFirst->GetLeft())));
		_wNumberFirst->WriteString(1, 1, "In decimal: " + _inDecimal);
	}
		
	
	if (!(_nSecond == ""))
	{
		_system = GetCurrentSystem(_nSecond);

		_inDecimal = GetDecimal(_nSecond, _system);
		_wNumberSecond->WriteString(1, 1, (char*)(new String(' ', _wNumberFirst->GetRight() - _wNumberFirst->GetLeft())));
		_wNumberSecond->WriteString(1, 1, "In decimal: " + _inDecimal);
	}
		
	
	sprintf(number, "%d", _system);
	
	_wSystem->WriteString(3, 1, "   ");
	_wSystem->WriteString(4, 1, number);
}

void Numerics::ConsiderSum() {
	AreWriten();
	ShowResult((char*)"Sum", GetSum(_nFirst, _nSecond, _system));
}

void Numerics::ConsiderDifference() {
	AreWriten();
	ShowResult((char*)"Difference", GetDifference(_nFirst, _nSecond, _system));
}

void Numerics::ConsiderMultiplication() {
	AreWriten();
	ShowResult((char*)"Multiplication", GetMultiplication(_nFirst, _nSecond, _system));
}

void Numerics::ShowInformation(bool flag) {
	Window::ShowBackground();
	_wInformation->Show();

	if (flag) {
		_wInformation->WriteString(6, 0, "-----About app-----");
		_wInformation->WriteString(1, 1, "Calculator performs calculations");
		_wInformation->WriteString(1, 2, "in different system: 2-36");
		_wInformation->WriteString(1, 3, "You can perform such actions:");
		_wInformation->WriteString(1, 5, "Sum, difference, multiplication.");
		_getch();
		_wInformation->Hide();
	}
	else {
		_wInformation->WriteString(6, 0, "---Additional---");
		_wInformation->WriteString(1, 1, "App allows to save/download ");
		_wInformation->WriteString(1, 2, "numbers from selected path.");
		_wInformation->WriteString(1, 4, "Only .txt files can be read.");
		_getch();
		_wInformation->Hide();
	}
}

void Numerics::SetNumbers(bool flag, bool file_) {
	if (_nFirst == "" && _nSecond == "")
		Window::ShowBackground();

	char* number = new char[3];
	sprintf(number, "%d", _system);

	_wSystem->Show();
	_wSystem->WriteString(0, 0, "<- Up ->");
	_wSystem->WriteString(0, 2, "<-Down->");
	_wSystem->WriteString(3, 1, "   ");
	_wSystem->WriteString(4, 1, number);

	Checkup numberCheck(48, (_system > 10) ? 64 + _system - 10 : 47 + _system, INPUT_SIZE, BASE_POSITION_A, BASE, BASE_COUNT_A);

	if (flag) {
		if (file_) {
			Files files;
			if (files.OpenNumber(_nFirst)) {
				_wNumberFirst->Show();
				
				_nFirst = _nFirst.TrimLeft('0');
				_system = GetCurrentSystem(_nFirst);

				_wNumberFirst->WriteString(1, 0, "First number: " + _nFirst);

				_inDecimal = GetDecimal(_nFirst, _system);
				_wNumberFirst->WriteString(1, 1, "In decimal: " + _inDecimal);
			}
			SetConsoleTitle(TEXT("Numerics"));
		}
		else {
			_wNumberFirst->Show();
			_wNumberFirst->WriteString(1, 0, "Enter first number:");
			
			numberCheck.DoInput(2, NUMBER_INPUT_X);
			_nFirst = numberCheck.GetString();
			numberCheck.ClearString();
			
			_wNumberFirst->Show();
			_wNumberFirst->WriteString(1, 0, "First number:");
			
			_nFirst = _nFirst.TrimLeft('0');

			_wNumberFirst->WriteString(1, 0, "First number: " + _nFirst);

			_inDecimal = GetDecimal(_nFirst, _system);
			_wNumberFirst->WriteString(1, 1, "In decimal: " + _inDecimal);
		}
	}
	else {
		if (file_) {
			Files files;
			if (files.OpenNumber(_nSecond)) {
				_wNumberSecond->Show();				
				
				_nSecond = _nSecond.TrimLeft('0');
				_system = GetCurrentSystem(_nSecond);

				_wNumberSecond->WriteString(1, 0, "Second number: " + _nSecond);

				_inDecimal = GetDecimal(_nSecond, _system);
				_wNumberSecond->WriteString(1, 1, "In decimal: " + _inDecimal);								
			}
			SetConsoleTitle(TEXT("Numerics"));
		}
		else {
			_wNumberSecond->Show();
			_wNumberSecond->WriteString(1, 0, "Enter second number:");
			
			numberCheck.DoInput(7, NUMBER_INPUT_X);
			_nSecond = numberCheck.GetString();
			numberCheck.ClearString();
			
			_wNumberSecond->Show();			
			
			_nSecond = _nSecond.TrimLeft('0');			

			_wNumberSecond->WriteString(1, 0, "Second number: " + _nSecond);			

			_inDecimal = GetDecimal(_nSecond, _system);
			_wNumberSecond->WriteString(1, 1, "In decimal: " + _inDecimal);
		}
	}
	sprintf(number, "%d", _system);
	_wSystem->WriteString(3, 1, "   ");
	_wSystem->WriteString(4, 1, number);
}

int Numerics::AreSimilar(String numberFirst, String numberSecond) 
{
	if (numberFirst.GetLength() > numberSecond.GetLength())
		return 1;
	else if (numberFirst.GetLength() < numberSecond.GetLength())
		return -1;

	for (int i(numberFirst.GetLength() - 1); i >= 0; i--) 
	{
		if ((int)(numberFirst[i]) > (int)(numberSecond[i]))
			return 1;
		else if ((int)(numberFirst[i]) < (int)(numberSecond[i]))
			return -1;
	}

	return 0;
}
