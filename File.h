#pragma once
#include <string>
#include <list>
#include <vector>
#include "FileBlock.h"
using std::string;

class File {

public:
	File();
	File(string n);
	string getContent();
	void setContent(std::vector<FileBlock*> fileBlocks);
	string getUpdateDate();
	void setUpdateDate(string date);
	friend class Directory;

private:
	string updateDate;
	string name;
	string content;
	std::list<FileBlock*> fileBlocks;
};