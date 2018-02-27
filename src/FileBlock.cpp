#include "FileBlock.h"
#define DEFAULT_BLOCK_SIZE 100

    //Constructor
	FileBlock::FileBlock() {
		array = new char[size];
	}


	//Add content to FileBlock
	void FileBlock::addContent(std::string str) {
		int i = 0;
		for (i = 0; i < int(str.size()); i++) array[i] = str[i];
		array[i] = '\0';
	}


	//Get the contents of the FileBlock
	std::string FileBlock::getContent() {
		std::string ret;
		int i = 0;
		while(array[i]!='\0') ret.append(std::string(1, array[i++]));
		return ret;

	}


    //Destructor
	FileBlock::~FileBlock() {
		delete[]array;
	}


	//Get the size of a fileBlock
	int FileBlock::getSize() { return size; }


	//FileBlock Size
	int FileBlock::size = DEFAULT_BLOCK_SIZE;