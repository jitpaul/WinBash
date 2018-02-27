#pragma once
#include <string>


class FileBlock {
	
	FileBlock();
	void addContent(std::string); //Add content to FileBlock
	std::string getContent(); //Get the contents of the FileBlock
	static int getSize(); //Get the size of a fileBlock
	~FileBlock();

	static int size; //FileBlock Size
	char* array;
	friend class File;
	friend class FileSystem;
};