#pragma once
#include <string>


class FileBlock {
	static int size;
	char* array;
public:
	FileBlock();

	void addContent(std::string str);

	std::string getContent();

	static int getSize() {
		return size;
	}

	~FileBlock();
};