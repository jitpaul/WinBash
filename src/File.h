#pragma once
#include <string>
#include <list>
#include <vector>
#include "FileBlock.h"

class File {

	File();
	File(std::string n);
	std::string getContent(); //Get file content
	void setContent(std::vector<FileBlock*> fileBlocks); //Set file content
	std::string getUpdateDate(); //Get last update date of the file
	void setUpdateDate(std::string date); //Set last update date of the file
	friend class Directory;

	std::string updateDate; //Last update date
	std::string name; //Name of file
	std::string content; //File Content
	std::list<FileBlock*> fileBlocks;//FileBlocks used by the file
};