#include "FileBlock.h"

#define DEFAULT_BLOCK_SIZE 100


	FileBlock::FileBlock() {
		array = new char[size];
	}


	void FileBlock::addContent(std::string str) {
		int i = 0;
		for (i = 0; i < str.size(); i++) array[i] = str[i];
		array[i] = '\0';
	}


	std::string FileBlock::getContent() {
		std::string ret;
		int i = 0;
		while(array[i]!='\0') ret.append(std::string(1, array[i++]));
		return ret;

	}


	FileBlock::~FileBlock() {
		delete[]array;
	}

	int FileBlock::size = DEFAULT_BLOCK_SIZE;