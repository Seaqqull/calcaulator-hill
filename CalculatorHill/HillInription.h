#pragma once


enum CurrentMode
{
	Encryption = 0,
	Decryption = 1,
};

class HillIncryption : public Menu
{
private:
	CurrentMode _mode = CurrentMode::Encryption;
	Window* _wInputWord, * _wInputKey, * _wMode, * _wResult, * _wSystem;
	String _base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//
	String _baseAdditional = "0123456789abcdefghijklmnopqrstuvwxyz";//
	String _helpSymbols = " !\"$%&'()*+-./:;<=>@[\\]^_`{|}";//
	String* _abeth;
	String* _word, * _key, * _result;
	ui _currentSystem = 2, _parity;
	int  _determinant, _reDeterminant;
	ui** _mtrixWords, ** _mtrixKeys, ** _resultIncrypting, ** _mtrixReverse;
	

	ui GetMod(int c);

	void ShowCurrentMode();
	
	ui GetParity(String& str);

	ui GetCurrent(String str);

	int Inverse(int a, int n);

	ui GCD(ui number1, ui number2);

	void GetReverse(ui** mtrix, ui n);

	int GetDeterminant(ui** mtrix, ui n);
	
	bool DoInput(String& str, Window wActive);

	ui FindInAbeth(char letter, String abeth);

	void DoWriteWindow(String str, Window wActive);

	std::vector<Item> GetPosibleParity(String str);	
		
	void SwapColumns(float** mtrix, int col1, int col2);

	void SwapRows(float** mtrix, int row1, int row2, int n);
	
	void ExtendedEuclid(int a, int b, int* x, int* y, int* d);
	
public:
	HillIncryption();

	
	void DoIncryption();

	void ChangeCurrentMode();

	void ShowInformation(bool flag);

	bool SetIncryptionText(bool flag);
};
