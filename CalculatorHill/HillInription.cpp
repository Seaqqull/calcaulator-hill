#include "Headers.h"


HillIncryption::HillIncryption() : Menu(2, 1, 23, 13, Green, Blue, Blue, LightGray, true)
{
	_wInputWord = new Window(26, 1, 72, 5, Green, Blue, Blue, LightGray, false);
	_wInputKey = new Window(26, 7, 72, 9, Green, Blue, Blue, LightGray, false);
	_wResult = new Window(26, 12, 72, 15, Green, Blue, Blue, LightGray, false);
	_wSystem = new Window(68, 17, 78, 20, Green, Blue, Blue, LightGray, false);
	_wMode = new Window(2, 15, 23, 18, Green, Blue, Blue, LightGray, false);

	_word = new String(' ', (_wInputWord->GetRight() - _wInputWord->GetLeft() - 1) * (_wInputWord->GetBottom() - _wInputWord->GetTop() - 1));
	_key = new String(' ', (_wInputKey->GetRight() - _wInputKey->GetLeft() - 1) * (_wInputKey->GetBottom() - _wInputKey->GetTop() - 1));
	_result = new String("");
}


ui HillIncryption::GetMod(int c)
{
	if (c > 0)
	{
		ui c2 = c / _currentSystem;

		return c - (_currentSystem * c2);
	}
	if (c < 0)
	{
		ui c2 = abs(c) / _currentSystem + 1;

		return c + (_currentSystem * c2);
	}

	return 0;
}

void HillIncryption::ShowCurrentMode() {
	_wMode->Show();
	_wMode->WriteString(5, 0, "<-Mode->");
	_wMode->WriteString(4, 1, "\t\t");

	switch (_mode)
	{
	case Encryption:
		_wMode->WriteString(5, 1, "Encryption");
		break;
	case Decryption:
		_wMode->WriteString(5, 1, "Decryption");
		break;
	}
}

ui HillIncryption::GetCurrent(String str) {
	ui newSystem = _currentSystem, preSystem = 0, i = 0;
	
	while (i < str.GetLength()) {
		preSystem = _base.GetPosition(str[i++]) + 1;
		if (newSystem < preSystem && preSystem >= _currentSystem) newSystem = preSystem;
	}
	
	i = 0;
	
	while (i < str.GetLength()) {
		preSystem = _base.GetPosition(str[i++]) + 1;
		if (newSystem < preSystem && preSystem >= _currentSystem) newSystem = preSystem;
	}
	
	if (newSystem < 32) {
		for (ui i(2); i < 33; i *= 2)
			if (i >= newSystem) {
				newSystem = i;
				break;
			}
	}
	
	return newSystem;
}

ui HillIncryption::GetParity(String& str) {
	std::vector<Item> items;
	ui choise = 1, key;
	ui parity = 1;		

	CursorVisible(false);
	
	while (true)
	{
		items = GetPosibleParity(str);
		DrawMenu(_left, _right, _top, _bottom, choise, items);

		key = _getch();
		
		if (key == 224) key = _getch();//special-down
		if (key == 13)
		{
			if (choise < items.size()) {
				parity = items[choise - 1].Title.GetInt();
		
				return parity;
			}
			else {
				choise = 1;
				str += " ";
			}
		}
		if (key == 72 && choise > 1) choise--;
		if (key == 80 && choise < items.size()) choise++;
	}

	CursorVisible(true);
	
	return parity;
}

int HillIncryption::Inverse(int a, int n) {
	int d, x, y;

	ExtendedEuclid(a, n, &x, &y, &d);
	
	return (d == 1)? x : 0;	
}

ui HillIncryption::GCD(ui number1, ui number2) {
	return number2 ? GCD(number2, number1 % number2) : number1;
}

void HillIncryption::GetReverse(ui** mtrix, ui n) {
	_mtrixReverse = new ui * [n];
	ui currentCol = 0, currentRow = 0, posCol = 0, posRow = 0, ** mtrixMinor = new ui * [n - 1];

	for (ui i(0); i < n; i++)
		_mtrixReverse[i] = new ui[n];	

	for (ui i(0); i < n - 1; i++)
		mtrixMinor[i] = new ui[n - 1];

	while (currentRow < n) {
		for (ui i(0); i < n; i++) {
			if (i != currentRow) {
				for (ui j(0); j < n; j++)
					if (j != currentCol)
						mtrixMinor[posRow][posCol++] = mtrix[i][j];
				++posRow;
			}
			posCol = 0;
		}
		posRow = posCol = 0;

		_mtrixReverse[currentCol++][currentRow] =
			GetMod((int)(pow((-1), currentRow + currentCol) * GetDeterminant(mtrixMinor, n - 1)) * _reDeterminant); //Get_Mod(*Determinant);
		
		if (currentCol >= n) {//==
			++currentRow;
			currentCol = 0;
		}
	}
}

int HillIncryption::GetDeterminant(ui** mtrix, ui n_) {
	//printMatrix(matr, n);
	int n = n_,//dimension of the matrix
		x, y;
	float** matr = new float* [n];	
	float determ = 1.0;
	int sign = +1;

	for (x = 0; x < n; ++x)
		matr[x] = new float[n];

	for (y = 0; y < n; ++y)
		for (x = 0; x < n; ++x)
			matr[x][y] = (float)(mtrix[x][y]);
	//printMatrix(matr, n);
	
	for (int i = 0; i < n; ++i) //move along main diagonal
	{
		//search non-null element in (i,i,  n,n)-part of the matrix
		int nonullX = 0, nonullY = 0;
		bool successFindingNonullElement = false;

		for (x = i; x < n; ++x)
			for (y = i; y < n; ++y)
				if (!successFindingNonullElement && matr[x][y])
				{
					nonullX = x;
					nonullY = y;
					successFindingNonullElement = true;
				}

		if (!successFindingNonullElement) //no non-null elements
		{
			determ = 0.0;
			break;
		}

		if (nonullX != i) {
			SwapColumns(matr, i, nonullX);
			sign = -sign;
		}

		if (nonullY != i) {
			SwapRows(matr, i, nonullY, n);
			sign = -sign;
		}

		//now matr[i][i] != 0 
		determ *= matr[i][i];
		for (x = n - 1; x >= i; --x)
			matr[x][i] /= matr[i][i];
		//now matr[i][i] == 1;
		for (y = i + 1; y < n; ++y)
			for (x = n - 1; x >= i; --x)
				matr[x][y] -= matr[x][i] * matr[i][y];
	}

	//determ *= sign;	
	determ = round(determ);

	return (int)determ;//Get_Mod()
}

ui HillIncryption::FindInAbeth(char letter, String abeth) {
	String _abethhlp("");
	ui key = letter;

	for (ui i(0); i < _currentSystem; i++)
		_abethhlp += _base[i];

	_abethhlp += _helpSymbols;
	
	for (ui i(0); i < abeth.GetLength(); i++)
		if ((char)key == abeth[i])	return i;
		else if ((char)key == _abethhlp[i]) return i;
	
	return -1;
}

bool HillIncryption::DoInput(String& str_, Window wActive) {
	String str(' ', (wActive.GetRight() - wActive.GetLeft() - 1) * (wActive.GetBottom() - wActive.GetTop() - 1));
	ui x_ = 1, y_ = 1;
	int key;

	for (ui i(0); i < str_.GetLength(); i++)
		str[i] = str_[i];		
	
	CursorVisible(true);
	wActive.WriteString(0, 0, str);

	do {
		GotoXY(wActive.GetLeft() + x_, wActive.GetTop() + y_);
		key = _getch();

		if (key == 224) {
			key = _getch();//special
		
			if (key == 72 && GetCurrentY() > wActive.GetTop() + 1) 	//Down
				GotoXY(GetCurrentX(), GetCurrentY() - 1);
			else if (key == 80 && GetCurrentY() < wActive.GetBottom() - 1)//Up
				GotoXY(GetCurrentX(), GetCurrentY() + 1);
			else if (key == 75 && GetCurrentX() > wActive.GetLeft() + 1) // left		
				GotoXY(GetCurrentX() - 1, GetCurrentY());
			else if (key == 77 && GetCurrentX() < wActive.GetRight() - 1 && GetCurrentX() - wActive.GetLeft() < str.GetLength()) // right
				GotoXY(GetCurrentX() + 1, GetCurrentY());
			
			x_ = GetCurrentX() - wActive.GetLeft();
			y_ = GetCurrentY() - wActive.GetTop();
			
			if (key == 83) {//delete
				str[((y_ - 1) * (wActive.GetRight() - wActive.GetLeft() - 1)) + (x_ - 1)] = ' ';
				wActive.WriteChar(x_ - 1, y_ - 1, str[((y_ - 1) * (wActive.GetRight() - wActive.GetLeft() - 1)) + (x_ - 1)]);
				--x_;
				
				if (x_ < 1 && y_ > 1) {
					--y_;
					x_ = (wActive.GetRight() - wActive.GetLeft() - 1);
				}
				else if (x_ < 1)
					x_ = 1;
			}
		}
		else if (key == 27) {//esc	
			str_ = " ";
			wActive.Hide();

			return false;
		}
		else if (key >= 32 && key <= 126) {
			if (GetCurrentX() - wActive.GetLeft() <= str.GetLength()) {
				str[((y_ - 1) * (wActive.GetRight() - wActive.GetLeft() - 1)) + (x_ - 1)] = key;
				wActive.WriteChar(x_ - 1, y_ - 1, str[((y_ - 1) * (wActive.GetRight() - wActive.GetLeft() - 1)) + (x_ - 1)]);
				++x_;
				
				if (x_ > (wActive.GetRight() - wActive.GetLeft() - 1) && y_ < (wActive.GetBottom() - wActive.GetTop() - 1)) {
					++y_;
					x_ = 1;
				}
				else if (x_ > (wActive.GetRight() - wActive.GetLeft() - 1))
					--x_;
			}
		}
		else if (key == 8) {//backspace					
			--x_;
			
			if (x_ < 1 && y_ > 1) {
				--y_;
				x_ = (wActive.GetRight() - wActive.GetLeft() - 1);
			}
			else if (x_ < 1)
				x_ = 1;
			
			str[(((y_ - 1) * (wActive.GetRight() - wActive.GetLeft() - 1)) + (x_ - 1))] = ' ';
			wActive.WriteChar(x_ - 1, y_ - 1, str[((y_ - 1) * (wActive.GetRight() - wActive.GetLeft() - 1)) + (x_ - 1)]);
		}
	} while (key != 13);
		
	str = str.Trim(' ', true, true);
	str_ = str;

	wActive.Show();
	wActive.WriteString(0, 0, str);	
	
	return true;
}

void HillIncryption::DoWriteWindow(String str, Window wActive) {
	int k = 0;

	for (ui i(0); i < str.GetLength(); i++) {
		if (i % (_wInputKey->GetRight() - _wInputKey->GetLeft() - 1) == 0)
			k = i / (_wInputKey->GetRight() - _wInputKey->GetLeft() - 1);

		GotoXY(27 + (i - ((_wInputKey->GetRight() - _wInputKey->GetLeft() - 1) * k)), 2 + k);
		printf((const char*)str[i]);
	}
}

std::vector<Item> HillIncryption::GetPosibleParity(String str) {
	std::vector<Item> items;
	Item currenItem;
	
	currenItem.Addition = 0;
	currenItem.Main = 1;

	for (ui i(2); i <= str.GetLength() && i < 8; i++)
		if (str.GetLength() % i == 0) {
			currenItem.Title = (int)i;
			items.push_back(currenItem);
			currenItem.Main++;
		}
	
	currenItem.Title = "Add \" \"";
	items.push_back(currenItem);
	
	return items;
}

void HillIncryption::SwapColumns(float** mtrix, int col1, int col2)
{
	float* temp = mtrix[col1];

	mtrix[col1] = mtrix[col2];
	mtrix[col2] = temp;
}

void HillIncryption::SwapRows(float** mtrix, int row1, int row2, int n)
{
	float temp;

	for (int i = 0; i < n; ++i) {
		temp = mtrix[i][row1];
		mtrix[i][row1] = mtrix[i][row2];
		mtrix[i][row2] = temp;
	}
}

void HillIncryption::ExtendedEuclid(int a, int b, int* x, int* y, int* d) {
	int q, r, x1, x2, y1, y2;

	if (b == 0) {
		*d = a, * x = 1, * y = 0;
		return;
	}

	x2 = 1, x1 = 0, y2 = 0, y1 = 1;
	while (b > 0) {
		q = a / b, r = a - q * b;
		*x = x2 - q * x1, * y = y2 - q * y1;
		a = b, b = r;
		x2 = x1, x1 = *x, y2 = y1, y1 = *y;
	}

	*d = a, * x = x2, * y = y2;
}


void HillIncryption::DoIncryption() {
	ShowCurrentMode();

	if ((*_word)[0] == ' ')
		if (!SetIncryptionText(true)) {	//word
			_wMode->Hide();
			return;
		}

	if ((*_key)[0] == ' ')
		if (!SetIncryptionText(false)) { //key
			_wMode->Hide();
			return;
		}

	_resultIncrypting = new ui * [_word->GetLength() / _parity];
	for (ui i(0); i < _word->GetLength() / _parity; i++)
		_resultIncrypting[i] = new ui[_parity];

	for (ui i(0); i < _word->GetLength() / _parity; i++)
		for (ui j(0); j < _parity; j++)
			_resultIncrypting[i][j] = 0;

	for (ui current(0); current < _word->GetLength() / _parity; current++)
		for (ui k(0); k < _parity; k++)
			for (ui j(0); j < _parity; j++)
				_resultIncrypting[current][k] += _mtrixKeys[k][j] * _mtrixWords[current][j];
	
	for (ui i(0); i < _word->GetLength() / _parity; i++)
		for (ui j(0); j < _parity; j++) {
			_resultIncrypting[i][j] = GetMod(_resultIncrypting[i][j]);
			(*_result) += (*_abeth)[_resultIncrypting[i][j]];
		}
	
	
	if (_mode == CurrentMode::Encryption) {
		GetReverse(_mtrixKeys, _parity);
		Files::SaveData(*_abeth, _mtrixWords, "Word", "HillIncryption.txt", _word->GetLength() / _parity, _parity, true);
		Files::SaveData(*_abeth, _mtrixKeys, "Key", "HillIncryption.txt", _parity, _parity, false);
		Files::SaveData(*_abeth, _resultIncrypting, "Encryption_result", "HillIncryption.txt", _word->GetLength() / _parity, _parity, false);
		Files::SaveData(*_abeth, _mtrixReverse, "ReverseKey", "HillIncryption.txt", _parity, _parity, false, _currentSystem);
	}
	else if (_mode == CurrentMode::Decryption) {
		Files::SaveData(*_abeth, _mtrixWords, "Word", "HillDecryption.txt", _word->GetLength() / _parity, _parity, true);
		Files::SaveData(*_abeth, _mtrixKeys, "Key", "HillDecryption.txt", _parity, _parity, false);
		Files::SaveData(*_abeth, _resultIncrypting, "Decryption_result", "HillDecryption.txt", _word->GetLength() / _parity, _parity, false);
	}
	
	_wResult->Show();
	_wResult->WriteString(1, 0, *_result);
	_getch();		
	
	_word = new String(' ', (_wInputWord->GetRight() - _wInputWord->GetLeft() - 1) * (_wInputWord->GetBottom() - _wInputWord->GetTop() - 1));
	_key = new String(' ', (_wInputKey->GetRight() - _wInputKey->GetLeft() - 1) * (_wInputKey->GetBottom() - _wInputKey->GetTop() - 1));
	_result = new String("");

	Window::ShowBackground();
}

void HillIncryption::ChangeCurrentMode() {
	int ch = 0;

	do {
		ShowCurrentMode();
		ch = _getch();

		switch (ch) {
			if (ch == 224) {
		case 72:
			if (_mode == CurrentMode::Encryption) _mode = CurrentMode::Decryption;
			break;
		case 80:
			if (_mode == CurrentMode::Decryption) _mode = CurrentMode::Encryption;
			break;
			}
		}
	} while (ch != 13);

	_word = new String(' ', (_wInputWord->GetRight() - _wInputWord->GetLeft() - 1) * (_wInputWord->GetBottom() - _wInputWord->GetTop() - 1));
	_key = new String(' ', (_wInputKey->GetRight() - _wInputKey->GetLeft() - 1) * (_wInputKey->GetBottom() - _wInputKey->GetTop() - 1));
	_result = new String("");

	Window::ShowBackground();
}

void HillIncryption::ShowInformation(bool flag) 
{
	Window::ShowBackground();
	Window information(26, 1, 61, 11, Green, Blue, Blue, LightGray, true);
	information.Show();

	if (flag) {
		information.WriteString(6, 0, "-----Hill method-----");
		information.WriteString(1, 1, "1.Enter word: GOD");
		information.WriteString(1, 2, "2.Enter the key: GYBNQKURP");
		information.WriteString(1, 3, "(Square length of word length)");
		information.WriteString(1, 4, "3.Key validation");
		information.WriteString(1, 5, "(Check determinant of matrix key)");
		information.WriteString(1, 6, "4.Creating a key: LUN");
		information.WriteString(1, 7, "(By multiplying the matrices)");
		_getch();
		information.Hide();
	}
	else {
		information.WriteString(6, 0, "-----Hill / files-----");
		information.WriteString(1, 1, "Hill -> File");
		information.WriteString(1, 2, "Word -> Encoding word");
		information.WriteString(1, 3, "Key -> Key for encoding");
		information.WriteString(1, 4, "IncriptionResult ->");
		information.WriteString(1, 5, "(Encoding result)");
		information.WriteString(1, 6, "ReverseKey ->");
		information.WriteString(1, 7, "(Key for decoding)");
		information.WriteString(1, 8, "System -> Encoding system");
		_getch();
		information.Hide();
	}
}

bool HillIncryption::SetIncryptionText(bool flag) {
	if (flag) {		
		Window::ShowBackground();
		_wInputWord->Show();

		if (_mode == CurrentMode::Decryption) {
			_wSystem->Show();
			_wSystem->WriteString(1, 0, "System");

			Checkup systemC(48, 57, 2);
			String temp;
			int numb_;			
		
			do {
				GotoXY(72, 19);
				printf("   ");
				
				systemC.DoInput(19, 72);
				
				temp = systemC.GetString();
				numb_ = temp.GetInt();
				
				systemC.ClearString();
			} while (numb_ < 2 || numb_ > 36);
			
			_currentSystem = numb_;
		}
		
		if (!DoInput(*_word, *_wInputWord))
			return false;
		
		_parity = GetParity(*_word);
		
		if (_mode == CurrentMode::Encryption) {	//		
			GotoXY(35, 6);
			SetColor(Black, DarkGray);
		
			String number;
			number = (int)(pow(_parity, 2));

			printf("Key length must be " + number);
			
			_currentSystem = GetCurrent(*_word);
		}
		
		_abeth = new String("");

		for (ui i(0); i < _currentSystem; i++)
			(*_abeth) += _base[i];

		(*_abeth) += _helpSymbols;
		_currentSystem += _helpSymbols.GetLength();

		if (_mode == CurrentMode::Decryption) {
			bool flag_;

			do {
				flag_ = true;

				for (ui i(0); i < _word->GetLength(); i++)
					if (FindInAbeth((*_word)[i], *_abeth) == -1)
						flag_ = false;

				if (!flag_)
					if (!DoInput(*_word, *_wInputWord))
						return false;
			} while (!flag_);
		}

		_mtrixWords = new ui * [_word->GetLength() / _parity];
		
		for (ui i(0); i < _word->GetLength() / _parity; i++)
			_mtrixWords[i] = new ui[_parity];

		ui current = 0;
		
		for (ui i(0); i < _word->GetLength() / _parity; i++)
			for (ui j(0); j < _parity; j++)
				_mtrixWords[i][j] = FindInAbeth((*_word)[current++], *_abeth);
		return true;
	}
	else {
		if ((*_word)[0] == ' ') {
			Window::ShowBackground();
		
			if (!SetIncryptionText(true))
				return false;
		}
		bool flag_;		
		
		do {
			flag_ = true;
			_key = new String(' ', (int)pow(_parity, 2));
			
			_wInputKey->Show();
		
			if (!DoInput(*_key, *_wInputKey))
				return false;
			if (_key->GetLength() != pow(_parity, 2))
				flag_ = false;
			for (ui i(0); i < _key->GetLength(); i++)
				if (FindInAbeth((*_key)[i], *_abeth) == -1)
					flag_ = false;
			if (flag_) {
				ui current = 0;
				_mtrixKeys = new ui * [_parity];
			
				for (ui i(0); i < _parity; i++)
					_mtrixKeys[i] = new ui[_parity];
				
				for (ui i(0); i < _parity; i++)
					for (ui j(0); j < _parity; j++)
						_mtrixKeys[i][j] = FindInAbeth((*_key)[current++], *_abeth);
				
				if (_mode == CurrentMode::Encryption) {//
					_determinant = GetMod(GetDeterminant(_mtrixKeys, _parity));
				
					_reDeterminant = Inverse(_determinant, _currentSystem);
				
					if (_reDeterminant == 0 /*|| Number > 1*/)	flag_ = false;
					else
						_reDeterminant = GetMod(_reDeterminant);
				}
			}
		} while (!flag_);
		return true;
	}
}
