#include "Hill_incryption.h"

Hill_incryption::Hill_incryption() : Menu(2, 1, 23, 13, Green, Blue, Blue, LightGray, true)
{
	Input_Word_Window = new Window(26, 1, 72, 5, Green, Blue, Blue, LightGray, false);
	Input_Key_Window = new Window(26, 7, 72, 9, Green, Blue, Blue, LightGray, false);
	ResultOf = new Window(26, 12, 72, 15, Green, Blue, Blue, LightGray, false);
	Window_Mode = new Window(2, 15, 23, 18, Green, Blue, Blue, LightGray, false);	
	ChoseSystem = new Window(68, 17, 78, 20, Green, Blue, Blue, LightGray, false);
	Word_ = new String(' ', (Input_Word_Window->GetRight() - Input_Word_Window->GetLeft() - 1) * (Input_Word_Window->GetBottom() - Input_Word_Window->GetTop() - 1));
	Key_ = new String(' ', (Input_Key_Window->GetRight() - Input_Key_Window->GetLeft() - 1) * (Input_Key_Window->GetBottom() - Input_Key_Window->GetTop() - 1));
	Result = new String("");
}

ui Hill_incryption::Get_Current(String str){
	ui new_system = Current_system, pre_system = 0, i = 0;
	while (i<str.GetLength()){
		pre_system = Base.GetPosition(str[i++]) + 1;
		if (new_system < pre_system && pre_system >= Current_system) new_system = pre_system;
	}
	i = 0;
	while (i<str.GetLength()){
		pre_system = Base_.GetPosition(str[i++]) + 1;
		if (new_system < pre_system && pre_system >= Current_system) new_system = pre_system;
	}
	if (new_system < 32){
		for (ui i(2); i < 33; i *= 2)
			if (i >= new_system){
				new_system = i;
				break;
			}
	}
	return new_system;
}

ui Hill_incryption::Find_in_abeth(char letter, String Abeth){
	String Abeth_hlp("");
	for (ui i(0); i < Current_system; i++)
		Abeth_hlp += Base_[i];
	Abeth_hlp += Help_Symbols;
	ui key = letter;
	for (ui i(0); i < Abeth.GetLength(); i++)
		if ((char)key == Abeth[i])	return i;
		else if ((char)key == Abeth_hlp[i]) return i;		
	return -1;
}

array<Item> Hill_incryption::Get_Posible_Parity(String str){
	array<Item> Items;
	Item Current;
	Current.addition = 0;
	Current.main = 1;
	for (ui i(2); i <= str.GetLength() && i < 8; i++)
		if (str.GetLength() % i == 0) { 
			Current.item = (int)i;
			Items.Add(Current);
			Current.main++;
		}
	Current.item = "Add \" \"";
	Items.Add(Current);
	return Items;
}

ui Hill_incryption::Get_Parity(String& str){
	ui parity = 1;
	array<Item> Items;	
	CursorVisible(false);
	uint choise = 1, key;
	while (true)
	{				
		Items = Get_Posible_Parity(str);
		DrawMenu(left, right, top, bottom, choise, Items);		
		key = _getch();
		if (key == 224) key = _getch();//special-down
		if (key == 13)
		{
			if (choise < Items.GetCount()){
				parity = Items[choise - 1].item.GetInt();
				return parity;
			}
			else{
				choise = 1;
				str += " ";
			}
		}
		if (key == 72 && choise > 1) choise--;
		if (key == 80 && choise < Items.GetCount()) choise++;
	}
	CursorVisible(true);
	return parity;
}
//
void Hill_incryption::extended_euclid(int a, int b, int *x, int *y, int *d){
	int q, r, x1, x2, y1, y2;
	if (b == 0) {
		*d = a, *x = 1, *y = 0;
		return;
	}

	x2 = 1, x1 = 0, y2 = 0, y1 = 1;
	while (b > 0) {
		q = a / b, r = a - q * b;
		*x = x2 - q * x1, *y = y2 - q * y1;
		a = b, b = r;
		x2 = x1, x1 = *x, y2 = y1, y1 = *y;
	}

	*d = a, *x = x2, *y = y2;
}

int Hill_incryption::inverse(int a, int n){
	int d, x, y;
	extended_euclid(a, n, &x, &y, &d);
	if (d == 1) return x;
	return 0;
}
//
bool Hill_incryption::DoInput(String& str_, Window Active){
	String str(' ', (Active.GetRight() - Active.GetLeft() - 1) * (Active.GetBottom() - Active.GetTop() - 1));
	for (ui i(0); i < str_.GetLength(); i++)
		str[i] = str_[i];
	ui x_ = 1, y_ = 1;
	int key;
	CursorVisible(true);
	Active.WriteString(0, 0, str);
	do{
		GotoXY(Active.GetLeft() + x_, Active.GetTop() + y_);
		key = _getch();
		if (key == 224){
			key = _getch();//special
			if (key == 72 && GetCurrentY() > Active.GetTop() + 1) 	//Down
				GotoXY(GetCurrentX(), GetCurrentY() - 1);
			else if (key == 80 && GetCurrentY() < Active.GetBottom() - 1)//Up
				GotoXY(GetCurrentX(), GetCurrentY() + 1);
			else if (key == 75 && GetCurrentX() > Active.GetLeft() + 1) // left		
				GotoXY(GetCurrentX() - 1, GetCurrentY());
			else if (key == 77 && GetCurrentX() < Active.GetRight() - 1 && GetCurrentX() - Active.GetLeft() < str.GetLength()) // right
				GotoXY(GetCurrentX() + 1, GetCurrentY());
			x_ = GetCurrentX() - Active.GetLeft();
			y_ = GetCurrentY() - Active.GetTop();
			if (key == 83){//delete
				str[((y_ - 1) * (Active.GetRight() - Active.GetLeft() - 1)) + (x_ - 1)] = ' ';
				Active.WriteChar(x_ - 1, y_ - 1, str[((y_ - 1) * (Active.GetRight() - Active.GetLeft() - 1)) + (x_ - 1)]);
				--x_;
				if (x_ < 1 && y_ > 1){
					--y_;
					x_ = (Active.GetRight() - Active.GetLeft() - 1);
				}
				else if (x_ < 1)
					x_ = 1;
			}
		}
		else if (key == 27){//esc	
			str_ = " ";
			Active.Hide();
			return false;
		}
		else if (key >= 32 && key <= 126){
			if (GetCurrentX() - Active.GetLeft() <= str.GetLength()){
				str[((y_ - 1) * (Active.GetRight() - Active.GetLeft() - 1)) + (x_ - 1)] = key;
				Active.WriteChar(x_ - 1, y_ - 1, str[((y_ - 1) * (Active.GetRight() - Active.GetLeft() - 1)) + (x_ - 1)]);
				++x_;
				if (x_ > (Active.GetRight() - Active.GetLeft() - 1) && y_ < (Active.GetBottom() - Active.GetTop() - 1)){
					++y_;
					x_ = 1;
				}
				else if (x_ > (Active.GetRight() - Active.GetLeft() - 1))
					--x_;
			}
		}
		else if (key == 8){//backspace					
			--x_;
			if (x_ < 1 && y_ > 1){
				--y_;
				x_ = (Active.GetRight() - Active.GetLeft() - 1);
			}
			else if (x_ < 1)
				x_ = 1;
			str[(((y_ - 1) * (Active.GetRight() - Active.GetLeft() - 1)) + (x_ - 1))] = ' ';
			Active.WriteChar(x_ - 1, y_ - 1, str[((y_ - 1) * (Active.GetRight() - Active.GetLeft() - 1)) + (x_ - 1)]);
		}
	} while (key != 13);
	Active.Show();
	str = str.Trim(' ', true, true);
	Active.WriteString(0, 0, str);
	str_ = str;
	return true;
}

void Hill_incryption::Do_write_window(String str, Window Active){
	int k = 0;
	for (ui i(0); i < str.GetLength(); i++){
		if (i % (Input_Key_Window->GetRight() - Input_Key_Window->GetLeft() - 1) == 0)
			k = i / (Input_Key_Window->GetRight() - Input_Key_Window->GetLeft() - 1);
		GotoXY(27 + (i - ((Input_Key_Window->GetRight() - Input_Key_Window->GetLeft() - 1) * k)), 2 + k);
		std::cout << str[i];
	}
}

ui Hill_incryption::Get_Mod(int c)
{
	if (c>0)
	{
		ui c2 = c / Current_system;
		return c - (Current_system * c2);
	}
	if (c<0)
	{
		ui c2 = abs(c) / Current_system + 1;
		return c + (Current_system * c2);
	}
	return 0;
}

void Hill_incryption::Get_Reverse(ui **Mtrix, ui n){
	MtrixReverse = new ui*[n];
	for (ui i(0); i < n; i++)
		MtrixReverse[i] = new ui[n];
	ui current_col = 0, current_row = 0, pos_col = 0, pos_row = 0, **MtrixMinor = new ui*[n - 1];
	for (ui i(0); i < n - 1; i++)
		MtrixMinor[i] = new ui[n - 1];
	while (current_row < n){
		for (ui i(0); i < n; i++){
			if (i != current_row){
				for (ui j(0); j < n; j++)
					if (j != current_col)
						MtrixMinor[pos_row][pos_col++] = Mtrix[i][j];
				++pos_row;
			}
			pos_col = 0;
		}
		pos_row = pos_col = 0;

		MtrixReverse[current_col++][current_row] = Get_Mod((int)(pow((-1), current_row + current_col) * GetDeterminant(MtrixMinor, n - 1))*Re_Determinant); //Get_Mod(*Determinant);
		if (current_col >= n){//==
			++current_row;
			current_col = 0;
		}
	}
}

ui Hill_incryption::GCD(ui number1, ui number2) {
	return number2 ? GCD(number2, number1%number2) : number1;
}
//
void Hill_incryption::Swap_Columns(float** Mtrix, int col1, int col2)
{
	float* temp = Mtrix[col1];
	Mtrix[col1] = Mtrix[col2];
	Mtrix[col2] = temp;
}

void Hill_incryption::Swap_Rows(float** Mtrix, int row1, int row2, int n)
{
	float temp;
	for (int i = 0; i<n; ++i){
		temp = Mtrix[i][row1];
		Mtrix[i][row1] = Mtrix[i][row2];
		Mtrix[i][row2] = temp;
	}
}

int Hill_incryption::GetDeterminant(ui **Mtrix, ui n_){
	//printMatrix(matr, n);
	int n = n_,//dimension of the matrix
		x, y;

	float **matr = new float*[n];
	for (x = 0; x<n; ++x)
		matr[x] = new float[n];

	for (y = 0; y<n; ++y)
		for (x = 0; x<n; ++x)
			matr[x][y] = (float)(Mtrix[x][y]);
	//printMatrix(matr, n);
	float determ = 1.0;
	int sign = +1;
	for (int i = 0; i<n; ++i) //move along main diagonal
	{
		//search non-null element in (i,i,  n,n)-part of the matrix
		int nonull_x = 0, nonull_y = 0;
		bool success_finding_nonull_element = false;

		for (x = i; x<n; ++x)
			for (y = i; y<n; ++y)
				if (!success_finding_nonull_element && matr[x][y])
				{
					nonull_x = x;
					nonull_y = y;
					success_finding_nonull_element = true;
				}

		if (!success_finding_nonull_element) //no non-null elements
		{
			determ = 0.0;
			break;
		}

		if (nonull_x != i){
			Swap_Columns(matr, i, nonull_x);
			sign = -sign;
		}

		if (nonull_y != i){
			Swap_Rows(matr, i, nonull_y, n);
			sign = -sign;
		}

		//now matr[i][i] != 0  !!!
		determ *= matr[i][i];
		for (x = n - 1; x >= i; --x)
			matr[x][i] /= matr[i][i];
		//now matr[i][i] == 1;
		for (y = i + 1; y<n; ++y)
			for (x = n - 1; x >= i; --x)
				matr[x][y] -= matr[x][i] * matr[i][y];
	}
	//determ *= sign;
	determ = round(determ);
	return (int)determ;//Get_Mod()
}
//
bool Hill_incryption::Set_Incryption_Text(bool flag){	
	if (flag){		
		//ChoseSystem->Show();
		Window().ShowBackground();
		Input_Word_Window->Show();
		if (Mode == CurrentMode::Decryption){
			ChoseSystem->Show();
			Checkup S(48, 57, 2);
			String temp;
			int numb_;
			ChoseSystem->WriteString(1, 0, "Система");
			//Input_Word_Window->Show();
			do{
				GotoXY(72, 19);
				std::cout << "   ";
				S.DoInput(19, 72);
				temp = S.GetString();
				numb_ = temp.GetInt();
				S.ClearString();
			} while (numb_ < 2 || numb_ > 36);
			Current_system = numb_;
		}
		if (!DoInput(*Word_, *Input_Word_Window))
			return false;
		Parity = Get_Parity(*Word_);
		if (Mode == CurrentMode::Encryption){	//		
			GotoXY(35, 6);
			SetColor(Black, DarkGray);
			std::cout << "Длина ключа должна быть " << pow(Parity, 2);
			Current_system = Get_Current(*Word_);
		}
		
		//Input_Key_Window->Hide();

		//Current_system = Get_Current(*Word_) ;
		Abeth_ = new String("");	
		//Current_system = 36;//!!!
		for (ui i(0); i < Current_system; i++)
			(*Abeth_) += Base[i];
		(*Abeth_) += Help_Symbols;	
		Current_system += Help_Symbols.GetLength();
		
		if (Mode == CurrentMode::Decryption){
			bool flag_;
			do{
				flag_ = true;
				for (ui i(0); i < Word_->GetLength(); i++)
					if (Find_in_abeth((*Word_)[i], *Abeth_) == -1)
						flag_ = false;
				if (!flag_)
					if (!DoInput(*Word_, *Input_Word_Window))
						return false;
			} while (!flag_);
		}

		MtrixWords = new ui*[Word_->GetLength() / Parity];
		for (ui i(0); i < Word_->GetLength() / Parity; i++)
			MtrixWords[i] = new ui[Parity];
		
		ui current = 0;
		for (ui i(0); i < Word_->GetLength() / Parity; i++)
			for (ui j(0); j < Parity; j++)
				MtrixWords[i][j] = Find_in_abeth((*Word_)[current++], *Abeth_);		
		return true;
	}
	else{
		if ((*Word_)[0] == ' '){
			Window().ShowBackground();
			if (!Set_Incryption_Text(true))
				return false;
		}
		bool flag_;
		//ui Number;//больший общий делитель
		do{
			flag_ = true;
			Key_ = new String(' ', (int)pow(Parity, 2));//(int) - можно убрать
			Input_Key_Window->Show();
			if(!DoInput(*Key_, *Input_Key_Window))
				return false;	
			if (Key_->GetLength() != pow(Parity, 2))
				flag_ = false;
			for (ui i(0); i < Key_->GetLength(); i++)
				if (Find_in_abeth((*Key_)[i], *Abeth_) == -1)
					flag_ = false;
			if (flag_){
					ui current = 0;
					MtrixKeys = new ui*[Parity];
					for (ui i(0); i < Parity; i++)
						MtrixKeys[i] = new ui[Parity];
					for (ui i(0); i < Parity; i++)
						for (ui j(0); j < Parity; j++)
							MtrixKeys[i][j] = Find_in_abeth((*Key_)[current++], *Abeth_);
					if (Mode == CurrentMode::Encryption){//
						Determinant = Get_Mod(GetDeterminant(MtrixKeys, Parity));
						/*Number = GCD(Determinant, Current_system);*/
						Re_Determinant = inverse(Determinant, Current_system);
						if (Re_Determinant == 0 /*|| Number > 1*/)	flag_ = false;
						else
							Re_Determinant = Get_Mod(Re_Determinant);
					}
				}			
		} while (!flag_);
		return true;
	}
}

void Hill_incryption::Do_Incryption(){
	ShowCurrentMode();
	if ((*Word_)[0] == ' ')
		if (!Set_Incryption_Text(true)){	//slovo
			Window_Mode->Hide();
			return;		
		}
	if ((*Key_)[0] == ' ')
		if (!Set_Incryption_Text(false)){ //kluch
			Window_Mode->Hide();
			return;		
		}
	Result_Incrypting = new ui*[Word_->GetLength() / Parity];
	for (ui i(0); i < Word_->GetLength() / Parity; i++)
		Result_Incrypting[i] = new ui[Parity];	
	for (ui i(0); i < Word_->GetLength() / Parity; i++)
		for (ui j(0); j < Parity; j++)
			Result_Incrypting[i][j] = 0;
	for (ui current(0); current < Word_->GetLength() / Parity; current++)
		for (ui k(0); k < Parity; k++)
			for (ui j(0); j < Parity; j++)
				Result_Incrypting[current][k] += MtrixKeys[k][j] * MtrixWords[current][j];	
	for (ui i(0); i < Word_->GetLength() / Parity; i++)
		for (ui j(0); j < Parity; j++){
			Result_Incrypting[i][j] = Get_Mod(Result_Incrypting[i][j]);
			(*Result) += (*Abeth_)[Result_Incrypting[i][j]];
		}	
	if (Mode == CurrentMode::Encryption){
		Get_Reverse(MtrixKeys, Parity);
		Files_Struct().SaveData(*Abeth_, MtrixWords, "Word", "HillIncryption.txt", Word_->GetLength() / Parity, Parity, true);
		Files_Struct().SaveData(*Abeth_, MtrixKeys, "Key", "HillIncryption.txt", Parity, Parity, false);
		Files_Struct().SaveData(*Abeth_, Result_Incrypting, "EncryptionResult", "HillIncryption.txt", Word_->GetLength() / Parity, Parity, false);
		Files_Struct().SaveData(*Abeth_, MtrixReverse, "ReverseKey", "HillIncryption.txt", Parity, Parity, false, Current_system);
	}
	else if (Mode == CurrentMode::Decryption){
		Files_Struct().SaveData(*Abeth_, MtrixWords, "Word", "HillDecryption.txt", Word_->GetLength() / Parity, Parity, true);
		Files_Struct().SaveData(*Abeth_, MtrixKeys, "Key", "HillDecryption.txt", Parity, Parity, false);
		Files_Struct().SaveData(*Abeth_, Result_Incrypting, "DecryptionResult", "HillDecryption.txt", Word_->GetLength() / Parity, Parity, false);
	}
	ResultOf->Show();	
	ResultOf->WriteString(1, 0, *Result);
	_getch();
	Window().ShowBackground();
	Word_ = new String(' ', (Input_Word_Window->GetRight() - Input_Word_Window->GetLeft() - 1) * (Input_Word_Window->GetBottom() - Input_Word_Window->GetTop() - 1));
	Key_ = new String(' ', (Input_Key_Window->GetRight() - Input_Key_Window->GetLeft() - 1) * (Input_Key_Window->GetBottom() - Input_Key_Window->GetTop() - 1));
	Result = new String("");
}

void Hill_incryption::ShowCurrentMode(){
	Window_Mode->Show();
	Window_Mode->WriteString(5, 0, "<-Режим->");
	Window_Mode->WriteString(4, 1, "\t\t");
	switch (Mode)
	{
	case Encryption:		
		Window_Mode->WriteString(5, 1, "Шифрование");
		break;
	case Decryption:		
		Window_Mode->WriteString(5, 1, "Дешифрование");
		break;
	}
}

void Hill_incryption::ChangeCurrentMode(){	
	int ch = 0;		
	do{
		ShowCurrentMode();
		ch = _getch();
		switch (ch){
			if (ch == 224){
			case 72:
				if (Mode == CurrentMode::Encryption) Mode = CurrentMode::Decryption;
				break;
			case 80:
				if (Mode == CurrentMode::Decryption) Mode = CurrentMode::Encryption;
				break;
			}
		}				
	} while (ch != 13);		
	Word_ = new String(' ', (Input_Word_Window->GetRight() - Input_Word_Window->GetLeft() - 1) * (Input_Word_Window->GetBottom() - Input_Word_Window->GetTop() - 1));
	Key_ = new String(' ', (Input_Key_Window->GetRight() - Input_Key_Window->GetLeft() - 1) * (Input_Key_Window->GetBottom() - Input_Key_Window->GetTop() - 1));
	Result = new String("");
	Window().ShowBackground();
}

void Hill_incryption::Show_Information(bool flag){
	Window().ShowBackground();
	Window Information(26, 1, 61, 11, Green, Blue, Blue, LightGray, true);
	Information.Show();
	if (flag){
		Information.WriteString(6, 0, "-----Метод  Хилла-----");
		Information.WriteString(1, 1, "1.Вводим слово: GOD");
		Information.WriteString(1, 2, "2.Вводим ключ(длиной квадрат от кратности длины слова): GYBNQKURP");
		Information.WriteString(1, 4, "3.Проверка ключа на коректность.");
		Information.WriteString(1, 5, "Нахождение детерминанта от  матрицы ключа и дальнейшая его проверка.");
		Information.WriteString(1, 7, "4.Cоздание ключа путем умножения матриц: LUN");
		_getch();
		Information.Hide();
	}
	else{
		Information.WriteString(6, 0, "-----Хилл / файлы-----");
		Information.WriteString(1, 1, "Hill -> Файл");
		Information.WriteString(1, 2, "Word -> Слово для шифрования");
		Information.WriteString(1, 3, "Key -> Ключ для шифрования");
		Information.WriteString(1, 4, "IncriptionResult -> Результат шифрования");
		Information.WriteString(1, 6, "ReverseKey -> Ключ для дешифрования");		
		Information.WriteString(1, 8, "System -> Система шифрования");
		_getch();
		Information.Hide();
	}
}