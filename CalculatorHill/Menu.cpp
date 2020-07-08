#include "Headers.h"


void Menu::DoMenu()
{
	CursorVisible(0);
	choiseMenu(_left, _right, _top, _bottom, GetItems(0));
}

void Menu::AddMenu(Item& newMenu)
{
	_menuItems.push_back(newMenu);
}

std::vector<Item> Menu::GetItems(ui flag)
{
	std::vector <Item> menuItems;

	for (ui i = 0; i < _menuItems.size(); i++) 
		if (_menuItems[i].Addition == flag) 
			menuItems.push_back(_menuItems[i]);

	return menuItems;
}

bool Menu::choiseMenu(ui left, ui right, ui top, ui bottom, std::vector<Item> menuItems)
{
	ui choise = 1, key;
	bool flag = true;
	
	_additionSelected = -1;
	_mainSelected = -1;
	

	while (flag)
	{
		DrawMenu(left, right, top, bottom, choise, menuItems);
		
		key = _getch();
		
		if (key == SPECIAL_KEY) key = _getch();
		if (key == ESC) flag = (menuItems[choise - 1].Main == 0) ? false : true;

		if (key == ENTER)
		{
			if (choise == menuItems.size()) return true;//back
			if (!menuItems[choise - 1].Addition && GetItems(menuItems[choise - 1].Main).size())//addition menu
				flag = choiseMenu(left, right, top, bottom, GetItems(menuItems[choise - 1].Main));
			else//close adition
			{
				_mainSelected = menuItems[choise - 1].Addition;
				_additionSelected = choise;
				return false;
			}
		}
		if (key == ARROW_UP && choise > 1) choise--;
		if (key == ARROW_DOWN && choise < menuItems.size()) choise++;
	}
	return true;
}

void Menu::DrawMenu(ui left, ui right, ui top, ui bottom, ui choise, std::vector<Item> menuItems)
{
	Show();

	ui i = 0;

	if (choise > (((bottom - 2) - (top + 2)) / 2 + 1))
	{
		i = choise - (((bottom - 2) - (top + 2)) / 2 + 1);
		choise = (bottom - 2) / 2;
	}

	GotoXY(left + 2, top);

	for (; i < menuItems.size() && GetCurrentY() < bottom - 2; i++)
	{
		GotoXY(left + 2, GetCurrentY() + 2);

		if (GetCurrentY() - (top - 1) == 2 * choise + 1)
		{
			SetColor(_choiseText, _menuFrame);
			for (ui k = left + 2; k < right - 1; k++) printf(" ");
		}

		GotoXY((left + right - menuItems[i].Title.GetLength()) / 2 + 1, GetCurrentY());
		printf(menuItems[i].Title);

		GotoXY(right - 2, GetCurrentY());
		SetColor(_textColor, _borderColor);
	}
}
