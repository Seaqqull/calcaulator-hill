#pragma once


class Numerics
{
private:
	String BASE = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::vector<int> BASE_POSITION;	
	std::vector<bool> BASE_COUNT;
	
	int* BASE_POSITION_A;
	bool* BASE_COUNT_A;

	String _nFirst = "", _nSecond = "", _inDecimal, _resultCaption;
	ui _system = 2;
	Window *_wResult, 
		*_wSystem,
		*_wInformation,
		*_wNumberFirst,
		*_wNumberSecond;	
	

	void AreWriten();

	ui GetCurrentSystem(String number);
	
	String GetDecimal(String number, int system);

	void ShowResult(char* caption, String answer);
	
	String GetSum(String nFirst, String nSecond, int system);	

	String GetDifference(String nFirst, String nSecond, int system);

	String GetMultiplication(String nFirst, String nSecond, int system);

public:
	Numerics();	

	~Numerics() { }


	void Clear();
	
	void SetSystem();
	
	void ConsiderSum();		

	void ConsiderDifference();

	void ConsiderMultiplication();

	void ShowInformation(bool flag);

	void SetNumbers(bool flag, bool file_);

	int AreSimilar(String nFirst, String nSecond);
};
