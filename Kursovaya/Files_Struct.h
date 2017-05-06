#if !defined(MY_Files_Struct_H)

#define MY_Files_Struct_H
#include <io.h>
#include <fstream>
#include "menu.h"
using namespace Project;
class Files_Struct : public Menu
{
public:
	Files_Struct() : Menu(2, 1, 23, 13, Green, Blue, Blue, LightGray, true){};
	String Get_File();
	bool Open_Number(String& Number);
	void SaveData(String Abeth, ui** Mtrix, String Name, String Name_, ui FullLenght, ui CurrentLenght, bool new_file, ui System_ = 0);
	void Go_Back(String& Path);
	array<Item> GetFirstDirectory(uint &count_folder);
	array<Item> GetItems(String Path, uint &count_folder);
	~Files_Struct();
};
#endif