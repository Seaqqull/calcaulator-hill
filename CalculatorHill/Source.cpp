#include "Headers.h"


int main(int argc, char** argv)
{
	SetConsoleTitle(TEXT("Calculator&Hill"));
	
	static const String Base("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	Window::SetSize(APP_WIDTH, APP_HEIGHT);
	Window::ShowBackground();
	Window::CursorVisible(false);

	Item menuItem;
	ui main = 0, adition = 0;
	Menu mainMenu(2, 1, 23, 13, Green, Blue, Blue, LightGray, true);

	Numerics calculator;
	HillIncryption incryptor;

	// 1
	menuItem.Title = "Calculator";
	menuItem.Addition = 0;
	menuItem.Main = 1;
	mainMenu.AddMenu(menuItem);	

	menuItem.Title = "Enter first number";
	menuItem.Addition = 1;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Read first number";
	menuItem.Addition = 1;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Enter second number";
	menuItem.Addition = 1;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Read second number";
	menuItem.Addition = 1;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Summ";
	menuItem.Addition = 1;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Difference";
	menuItem.Addition = 1;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Multiplication";
	menuItem.Addition = 1;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "System";
	menuItem.Addition = 1;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Back";
	menuItem.Addition = 1;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);

	// 2
	menuItem.Title = "Hill";
	menuItem.Addition = 0;
	menuItem.Main = 2;
	mainMenu.AddMenu(menuItem);

	menuItem.Title = "Enter message";
	menuItem.Addition = 2;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Enter key";
	menuItem.Addition = 2;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Execute";
	menuItem.Addition = 2;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Mode";
	menuItem.Addition = 2;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Back";
	menuItem.Addition = 2;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);

	// 3
	menuItem.Title = "About app";
	menuItem.Addition = 0;
	menuItem.Main = 3;
	mainMenu.AddMenu(menuItem);
	
	menuItem.Title = "Main";
	menuItem.Addition = 3;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Work with files";
	menuItem.Addition = 3;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Encoding";
	menuItem.Addition = 3;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Hill/Files";
	menuItem.Addition = 3;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	menuItem.Title = "Back";
	menuItem.Addition = 3;
	menuItem.Main = 0;
	mainMenu.AddMenu(menuItem);
	
	// 4
	menuItem.Title = "Exit";
	menuItem.Addition = 0;
	menuItem.Main = 4;
	mainMenu.AddMenu(menuItem);

	while (true)
	{
		mainMenu.DoMenu();
		main = (mainMenu.GetMain()) ? mainMenu.GetMain() : mainMenu.GetAddition();
		adition = mainMenu.GetAddition();

		switch (main)
		{
		case 1:
			switch (adition) {
			case 1:
				calculator.SetNumbers(true, false);
				break;
			case 2:
				calculator.SetNumbers(true, true);
				break;
			case 3:
				calculator.SetNumbers(false, false);
				break;
			case 4:
				calculator.SetNumbers(false, true);
				break;
			case 5:
				calculator.ConsiderSum();
				break;
			case 6:
				calculator.ConsiderDifference();
				break;
			case 7:
				calculator.ConsiderMultiplication();
				break;
			case 8:
				calculator.SetSystem();
				break;
			}
			break;
		case 2:
			calculator.Clear();
			switch (adition) {
			case 1:
				incryptor.SetIncryptionText(true);
				break;
			case 2:
				incryptor.SetIncryptionText(false);
				break;
			case 3:
				incryptor.DoIncryption();
				break;
			case 4:
				incryptor.ChangeCurrentMode();
				break;
			}
			break;
		case 3:
			switch (adition) {
			case 1:
				calculator.ShowInformation(true);
				break;
			case 2:
				calculator.ShowInformation(false);
				break;
			case 3:
				incryptor.ShowInformation(true);
				break;
			case 4:
				incryptor.ShowInformation(false);
				break;
			}
			break;
		default:
			return 0;
		}
	}
}
