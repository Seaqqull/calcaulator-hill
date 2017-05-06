#if !defined(MY_MENU_H)

#define MY_MENU_H


// <windows.h>
#include "array.h"
#include "Window.h"
#include "String.h"
#include <conio.h>
namespace Project
{

	struct Item
	{
		String item;
		uint  main;
		uint  addition;
	};

	class Menu :public Window
	{
	protected:
		uint choiseText, menuFrame, mainSelected, additionSelected;
		void DrawMenu(uint, uint, uint, uint, uint, array<Item>);
		array<Item> GetItems(uint);
		bool choiseMenu(uint, uint, uint, uint, array<Item>);

	public:

		array<Item> items;
		uint GetMain(){ return mainSelected; }
		uint GetAddition(){ return additionSelected; }
		Menu(int left_, int top_, int right_, int bottom_, int bgcolour, int shadowcolor, int textcolor, int bordercolor, bool frame, int choiseText = Blue, int menuFrame = White) :Window(left_, top_, right_, bottom_, bgcolour, shadowcolor, textcolor, bordercolor, frame)
		{this->choiseText = choiseText; this->menuFrame = menuFrame;}
		void DoMenu();
	};

	
}
#endif;