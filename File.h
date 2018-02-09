#pragma once
#include <string>
using std::string;

class File {

public:
	File();
	File(string n);
	string getContent();
	void setContent(string c);
	string getUpdateDate();
	void setUpdateDate(string date);

private:
	string updateDate;
	string name;
	string content;
};