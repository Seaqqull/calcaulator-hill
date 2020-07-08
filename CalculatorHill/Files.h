#pragma once


class Files : public Menu
{
public:
	Files() :
		Menu(2, 1, 23, 13, Green, Blue, Blue, WINDOW_COLOR, true) {};
	~Files() { };


	String GetFile();
	void GoBack(String& path);
	bool OpenNumber(String& number);
	std::vector<Item> GetFirstDirectory(ui& folderCount);
	std::vector<Item> GetItems(String path, ui& folderCount);
	static void SaveData(String Abeth, ui** mtrix, String nameOne, String nameTwo, ui fullLenght, ui currentLenght, bool newFile, ui system = 0);
};
