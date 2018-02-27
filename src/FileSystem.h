#pragma once
#include <string>
#include "file.h"
#include "directory.h"
#define DEFAULT_MEMORY_LIMIT 10000

class FileSystem {
	
	FileSystem(); //Default Constructor
	FileSystem(int); //Parameterized Constructor
	void initializeMemory(); //Initialize memory for File Blocks
	void ls(); //Show Contents of the Directory
	void mkdir(std::string); //Make Directory
	void createFile(std::string); //Create File	
	std::string viewFile(std::string); //View File
	void addToFile(std::string, std::string); //Add to File
	void delFile(std::string); //Delete File
	void delDir(std::string); //Delete Directory	
	void cd(std::string, Directory*&); //Navigate to Directory
	std::string getDirectory(); //Get the display path in the console window
	void parse2(std::string, int&, std::string &, std::string &, std::string &, std::string &); //Helper Function to parse input string
	void parse(std::string); //Parse input string
	void saveFS(std::string loc = ""); //Save FileSystem to disk
	void mountFS(std::string); //Save FileSystem from disk
	void resetFS(); //Reset FileSystem
	void history(); //Get History
	~FileSystem(); //Destructor

	Directory* root; //Root Directory
	std::string currentDir; //Current Directory
	int memoryLimit = DEFAULT_MEMORY_LIMIT; //Maximum Allowed Heap Size 
	std::vector <FileBlock*> fileBlocks; // Array that stores all the available fileblocks

public:
	static void run(); //Run FileSystem
};
