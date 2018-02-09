#pragma once

#include <map>
#include <string>
#include <experimental/filesystem>
#include <fstream>
#include "file.h"

using std::string;
using std::map;
namespace fs = std::experimental::filesystem;

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
	void create(fs::path);

private:
	string name;
	string updateDate;
	map <string, Directory*> dir;
	map <string, File*> file;

};