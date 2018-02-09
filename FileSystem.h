#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <regex>
#include "file.h"
#include "directory.h"

using std::string;
using std::pair;
using std::map;
using std::cout;
using std::cin;
using std::endl;
using std::regex;


class FileSystem {
	Directory* root;
	string currentDir;

public:
	FileSystem();

	//Show Contents of the Directory
	void ls();

	//Make Directory
	void mkdir(string);

	//Create File
	void createFile(string);

	//View File
	string viewFile(string);

	//Add to File
	void addToFile(string, string);

	//Delete File or Directory
	void del(string);

	//Navigate to Directory
	void cd(string, Directory*&);

	string getDirectory();

	void parse2(string, int&, string &, string &, string &, string &);

	//Parse input string
	void parse(string);

	//save FileSystem to disk
	void saveFS(string loc = "");

	//save FileSystem from disk
	void loadFS(string);

	//reset FileSystem
	void resetFS();
};
