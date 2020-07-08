#include "Headers.h"


String Files::GetFile()
{
	ui choise = 1, key, folderCount;
	std::vector<Item> menuItems;
	String path("");
	

	while (true)
	{
		if (!(path == ""))
			menuItems = GetItems(path, folderCount);
		else
			menuItems = GetFirstDirectory(folderCount);

		Window::SetWindowTitle(Window::ComposeStringWide(3, PROJECT_NAME, " - ", (char*)path));
		DrawMenu(_left, _right, _top, _bottom, choise, menuItems);
		
		key = _getch();

		if (key == SPECIAL_KEY) key = _getch();
		if (key == ESC) return path;

		if (key == ENTER)
		{
			if (choise == 1) // Go up in the hierarchy
			{
				if (path.GetLength() > 3) // Go up in folder
					GoBack(path);
				else // Go up, check disks
					path = "";
			}
			else if (choise <= folderCount) // Open the folder
			{ 
				if (path == "") 
				{
					path += menuItems[choise - 1].Title;
					path += +":\\";
				}
				else 
				{
					path += menuItems[choise - 1].Title;
					path += +"\\";
				}
			}
			else // Open file
			{
				path += menuItems[choise - 1].Title;
				return path;
			}
			choise = 1;
		}
		if (key == ARROW_UP && choise > 1) choise--;
		if (key == ARROW_DOWN && choise < menuItems.size()) choise++;
	}
}

void Files::GoBack(String& path)
{
	--path;
	while (path[strlen(path) - 1] != '\\')
		--path;
}

bool Files::OpenNumber(String& number)
{
	String path = GetFile();
	std::ifstream inputfs;	

	inputfs.open(path, std::ios::in);

	if (inputfs.is_open())
	{
		inputfs >> number;
		inputfs.close();
		
		return true;
	}

	return false;
}

std::vector<Item> Files::GetFirstDirectory(ui& folderCount)
{
	std::vector<Item> menuItems;
	_finddata_t fileInfo;
	
	ui currentNumber = 0;
	long beg;
	
	Item currentItem;
	currentItem.Title = "<--";
	currentItem.Addition = 0;
	currentItem.Main = 1;
	menuItems.push_back(currentItem);

	String directoryNames("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	String path;

	while (currentNumber < directoryNames.GetLength()) 
	{
		path = directoryNames[currentNumber];
		path += ":\\";
		beg = _findfirst(path + "*.*", &fileInfo);
		if (beg > 0) // -1 if not found
		{
			currentItem.Title = directoryNames[currentNumber];
			currentItem.Main = currentNumber + 2;
			menuItems.push_back(currentItem);
		}
		currentNumber++;
	}
	folderCount = menuItems.size();
	return menuItems;
}

std::vector<Item> Files::GetItems(String path, ui& folderCount)
{
	folderCount = 0;

	_finddata_t fileInfo;
	long beg = _findfirst(path + "*.*", &fileInfo);	
	
	Item currentItem;	
	currentItem.Title = "<--";
	currentItem.Addition = 0;
	currentItem.Main = 1;
	
	std::vector<Item> menuItems;// = new std::vector<Item>();
	menuItems.push_back(currentItem);

	do
	{
		currentItem.Title = fileInfo.name; /*32 - txt/ 16 - folders*/
		if (fileInfo.attrib == 16 /*&& fileInfo.size == 0*/ && strlen(fileInfo.name) < 20 && fileInfo.name[0] != '.') 
		{
			currentItem.Main = menuItems.size() + 1;
			menuItems.push_back(currentItem);
		}
	} while (_findnext(beg, &fileInfo) >= 0);

	folderCount = menuItems.size();
	beg = _findfirst(path + "*.txt", &fileInfo);
	
	while (beg >= 0)// -1 there is no file
	{
		if (strlen(fileInfo.name) < 20) 
		{
			currentItem.Title = fileInfo.name;
			currentItem.Main = menuItems.size() + 1;
			menuItems.push_back(currentItem);
		}
		if (_findnext(beg, &fileInfo) < 0) break;
	}
	
	
	return menuItems;
}

void Files::SaveData(String Abeth, ui** mtrix, String nameOne, String nameTwo, ui fullLenght, ui currentLenght, bool newFile, ui system)
{
	std::ofstream Ofs;
	if (newFile)
		Ofs.open(nameTwo, std::ios::out);
	else
		Ofs.open(nameTwo, std::ios::out | std::ios::app);
	Ofs << nameOne << '\n';
	for (ui i(0); i < fullLenght; i++) {
		for (ui j(0); j < currentLenght; j++)
			Ofs << Abeth[mtrix[i][j]] << ' ';
	}
	if (system)
		Ofs << "\nSystem\n" << system - 29 << '\n';
	else
		Ofs << '\n';

	Ofs.close();
}