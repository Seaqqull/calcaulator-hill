#include "Files_Struct.h"

array<Item> Files_Struct::GetFirstDirectory(uint &count_folder){
	_finddata_t File_info;
	ui current_number = 0;
	array<Item> Items;
	Item Current;
	String NameDirectory("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	String Path;
	Current.addition = 0;
	Current.item = "<--";
	Current.main = 1;
	Items.Add(Current);	
	long beg;
	while (current_number < NameDirectory.GetLength()){
		Path = NameDirectory[current_number];
		Path += ":\\";
		beg = _findfirst(Path + "*.*", &File_info);
		if (beg > 0){
			Current.item = NameDirectory[current_number];
			Current.main = current_number + 2;
			Items.Add(Current);			
		}
		current_number++;
	}
	count_folder = Items.GetCount();
	return Items;
}

array<Item> Files_Struct::GetItems(String Path, uint &count_folder){
	_finddata_t File_info;
	array<Item> Items;
	Item Current;
	Current.addition = 0;
	count_folder = 0;
	long beg = _findfirst(Path + "*.*", &File_info);
	int i = 0;	
	Current.item = "<--";
	Current.main = 1;
	Items.Add(Current);	
	do
	{
		Current.item = File_info.name; /*32 / 16*/
		if (File_info.attrib == 16 /*&& File_info.size == 0*/ && strlen(File_info.name) < 20 && File_info.name[0] != '.'){			
			Current.main = Items.GetCount() + 1;
			Items.Add(Current);
			}		
		i++;
	} while (_findnext(beg, &File_info) >= 0);//Заменить вайл для роботы без папок и файлов с тхт а так же добавить первый пункт
	count_folder = Items.GetCount();
	beg = _findfirst(Path + "*.txt", &File_info);
	while (beg >= 0)
	{
		if (strlen(File_info.name) < 20){
			Current.item = File_info.name;
			Current.main = Items.GetCount() + 1;
			Items.Add(Current);
		}
		if (_findnext(beg, &File_info) < 0) break;
	}
	return Items;
}

void Files_Struct::Go_Back(String& Path){
	--Path;
	while (Path[strlen(Path) - 1] != '\\')
		--Path;	
}

String Files_Struct::Get_File(){
	array<Item> Items; 
	String Path("");
	uint choise = 1, key, count_folder;
	while (true)
	{		
		if (!(Path == ""))
			Items = GetItems(Path, count_folder);
		else
			Items = GetFirstDirectory(count_folder);
		DrawMenu(left, right, top, bottom, choise, Items);
		SetConsoleTitle(TEXT("Numerics - " + Path));
		key = _getch();
		if (key == 224) key = _getch();//special-down
		if (key == 27) return Path;//esc

		if (key == 13)
		{
			//return Path;//back	
			if (choise == 1){
				if (Path.GetLength() > 3)
					Go_Back(Path);
				else				
					Path = "";				
			}
			else if (choise <= count_folder){
				if (Path == ""){
					Path += Items[choise - 1].item;
					Path += +":\\";
				}
				else{
					Path += Items[choise - 1].item;
					Path += +"\\";
				}
			}
			else
			{
				Path += Items[choise - 1].item;
				return Path;
			}
			choise = 1;
		}
		if (key == 72 && choise > 1) choise--;
		if (key == 80 && choise < Items.GetCount()) choise++;
	}
}

bool Files_Struct::Open_Number(String& Number){
	std::ifstream Ifs;
	String Path = Get_File();
	Ifs.open(Path, std::ios::in);
	if (Ifs.is_open()){
		Ifs >> Number;
		Ifs.close();
		return true;
	}
	return false;
}

void Files_Struct::SaveData(String Abeth, ui** Mtrix, String Name, String Name_, ui FullLenght, ui CurrentLenght, bool new_file, ui System_){
	std::ofstream Ofs;	
	if (new_file)
		Ofs.open(Name_, std::ios::out);
	else 
		Ofs.open(Name_, std::ios::out | std::ios::app);
	Ofs << Name << '\n';
	for (ui i(0); i < FullLenght; i++){
		for (ui j(0); j < CurrentLenght; j++)
			Ofs << Abeth[Mtrix[i][j]] << ' ';
	}
	if (System_)
		Ofs << "\nSystem\n" << System_  - 29 << '\n';
	else
	Ofs << '\n';
	
	Ofs.close();
}

Files_Struct::~Files_Struct()
{
}
