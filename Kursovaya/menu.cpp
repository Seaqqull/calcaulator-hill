#include "menu.h"
namespace Project
{
	array<Item> Menu::GetItems(uint flag)
	{
		array <Item> FlagItems;
		for (uint i = 0; i < items.GetCount(); i++) if (items[i].addition == flag) FlagItems.Add(items[i]);
		return FlagItems;
	}
	void Menu::DoMenu()
	{
		CursorVisible(0);
		choiseMenu(left, right, top, bottom, GetItems(0));
	}
	bool Menu::choiseMenu(uint left, uint right, uint top, uint bottom, array <Item> Items)
	{
		bool flag = true;
		uint choise = 1, key;
		mainSelected = -1;
		additionSelected = -1;

		while (flag)
		{
			DrawMenu(left, right, top, bottom, choise, Items);
			key = _getch();
			if (key == 224) key = _getch();//special
			if (key == 27) flag = (Items[choise - 1].main == 0)? false : true;

			if (key == 13)
			{
				if (choise == Items.GetCount()) return true;//back
				if (!Items[choise - 1].addition && GetItems(Items[choise - 1].main).GetCount())//addition
					flag = choiseMenu(left, right, top, bottom, GetItems(Items[choise - 1].main));
				else//close adition
				{
					mainSelected = Items[choise - 1].addition;
					additionSelected = choise;
					return false;
				}
			}
			if (key == 72 && choise > 1) choise--;
			if (key == 80 && choise < Items.GetCount()) choise++;
		}
		return true;
	}
	void Menu::DrawMenu(uint left, uint right, uint top, uint bottom, uint choise, array <Item> Items)
	{
		Show();
		uint i = 0;
		if (choise >(((bottom - 2) - (top + 2)) / 2 + 1))
		{
			i = choise - (((bottom - 2) - (top + 2)) / 2 + 1);
			choise = (bottom - 2) / 2;
		}
		GotoXY(left + 2, top);
		for (; i < Items.GetCount() && GetCurrentY() < bottom - 2; i++)
		{
			GotoXY(left + 2, GetCurrentY() + 2);
			if (GetCurrentY() - (top - 1) == 2 * choise + 1)
			{
				SetColor(choiseText, menuFrame);
				for (uint k = left + 2; k < right - 1; k++) printf(" ");				
			}
			GotoXY((left + right - Items[i].item.GetLength()) / 2 + 1, GetCurrentY());
			printf(Items[i].item);
			GotoXY(right - 2, GetCurrentY());
			SetColor(textcolor, bordercolor);
		}
	}

}