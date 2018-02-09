#pragma once

#include <map>
#include <string>
#include "file.h"

using std::string;
using std::map;

class Directory {
public:
	Directory(string);
	Directory* getDir(string);
	void setDir(string, Directory*);
	void deleteDir2();
	void deleteDir(string);
	File* getFile(string);
	void setFile(string, File*);
	void deleteFile(string);
	void printAll();
	string getUpdateDate();
	void setUpdateDate(string);

private:
	string name;
	string updateDate;
	map <string, Directory*> dir;
	map <string, File*> file;

};