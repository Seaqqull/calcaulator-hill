#pragma once


struct Item
{
	String Title;
	ui  Main;
	ui  Addition;

	~Item()
	{
		Title.~String();
	}
};


class Menu :
	public Window
{
protected:
	ui _menuFrame,
	   _choiseText, 
	   _mainSelected, 
	   _additionSelected;	
	std::vector<Item> _menuItems;

	std::vector<Item> GetItems(ui);
	bool choiseMenu(ui, ui, ui, ui, std::vector<Item>);
	void DrawMenu(ui, ui, ui, ui, ui, std::vector<Item>);

public:
	Menu(int left_, int top_, int right_, int bottom_, int bgcolour, int shadowcolor, int textcolor, int bordercolor, bool frame, int choiseText = Blue, int menuFrame = White) :
		Window(left_, top_, right_, bottom_, bgcolour, shadowcolor, textcolor, bordercolor, frame)
	{
		this->_choiseText = choiseText;
		this->_menuFrame = menuFrame;
	}


	ui GetMain() { return _mainSelected; }
	ui GetAddition() { return _additionSelected; }
	
	void DoMenu();
	void AddMenu(Item& newMenu);
};

