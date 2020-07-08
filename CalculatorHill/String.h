#pragma once


class String
{
private:
	char* _str;
	ui _length;
public:
	String();
	String(char, int);
	String(const char*);
	String(const String&);
	
	~String();
	
	//methods

	ui GetSize();	
	ui GetLength();	
	char& GetAt(int);	
	bool IsThere(char);	
	int GetPosition(char);
	int Compare(const char*);
	
	void Conversaly();
	void SetAt(int, char);

	int GetInt();
	double GetDouble();

	String TrimLeft(char letter);
	String TrimRight(char letter);
	String Trim(char letter, bool from_beg, bool from_end);
	
	//types
	operator char* ();

	//operators		
	String& operator=(char);
	String& operator=(const int);
	String& operator=(const long);
	String& operator=(const char*);
	String& operator=(const String&);
		
	String operator+(char) const;
	String operator+(const char*) const;
	String operator+(const String&) const;
	
	bool operator==(const char*);
	bool operator==(const String&);
	friend bool operator ==(const char*, const String&);	
	
	String& operator+=(char);
	String& operator+=(int);
	String& operator+=(const char*);
	String& operator+=(const String&);

	void operator--();// { str[length - 1] = NULL; length--; }

	char& operator[](int);
	void operator >>(const char*);

	friend String operator+(char, const String&);
	friend String operator+(const char*, const String&);

	friend std::istream& operator>>(std::istream&, String&);
	friend std::ostream& operator<<(std::ostream&, String&);
};

