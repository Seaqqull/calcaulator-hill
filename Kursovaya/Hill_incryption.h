#if !defined(MY_HILL_H)

#define MY_HILL_H
#include "String.h"
#include "Checkup.h"
#include "Window.h"
#include "Files_Struct.h"
enum CurrentMode
{
	Encryption = 0,
	Decryption = 1,	
};
class Hill_incryption : public Menu
{
private:
	CurrentMode Mode = CurrentMode::Encryption;
	Window *Input_Word_Window, *Input_Key_Window, *Window_Mode, *ResultOf, *ChoseSystem;
	String Base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//
	String Base_ = "0123456789abcdefghijklmnopqrstuvwxyz";//
	String Help_Symbols = " !\"$%&'()*+-./:;<=>@[\\]^_`{|}";//
	String *Abeth_;
	String *Word_, *Key_, *Result;
	ui Current_system = 2, Parity;
	int  Determinant, Re_Determinant;
	ui **MtrixWords, **MtrixKeys, **Result_Incrypting, **MtrixReverse;
	void Do_write_window(String str, Window Active);
	
	ui Find_in_abeth(char letter, String Abeth);

	array<Item> Get_Posible_Parity(String str);

	ui Get_Parity(String& str);

	ui Get_Current(String str);

	ui Get_Mod(int c);

	ui Hill_incryption::GCD(ui number1, ui number2);

	bool DoInput(String& str, Window Active);
	//
	void Swap_Columns(float** B, int col1, int col2);

	void Swap_Rows(float** B, int row1, int row2, int n);

	int GetDeterminant(ui **Mtrix, ui n);

	//int GetFromMinor(ui** Mtrix, ui n);//

	void Get_Reverse(ui **Mtrix, ui n);//

	void ShowCurrentMode();
	//Mode
	void extended_euclid(int a, int b, int *x, int *y, int *d);

	int inverse(int a, int n);
public:
	Hill_incryption();
	
	void Do_Incryption();	
		
	bool Set_Incryption_Text(bool flag);

	void ChangeCurrentMode();

	void Show_Information(bool flag);

	//~Hill_incryption();
};
#endif