#include "filesystem.h"
#include <windows.h>
#include <Lmcons.h>
#include <cctype>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <regex>
#include <iostream>
#include <map>

        //Default Constructor
		FileSystem::FileSystem() {
			root = new Directory("root");
			currentDir = "root";
			initializeMemory();
		}

		//Parameterized Constructor
		FileSystem::FileSystem(int limit):memoryLimit(limit) {
			root = new Directory("root");
			currentDir = "root";
			initializeMemory();
		}


		//Initialize memory for File Blocks
		void FileSystem::initializeMemory() {
			int maxBlocks = memoryLimit / FileBlock::getSize();
			for (int i = 0; i < maxBlocks; i++)
				fileBlocks.push_back(new FileBlock());
		}


	    //Show Contents of the current Directory
	    void FileSystem::ls() {
		    Directory* tempDir = nullptr;
		    cd("",tempDir);
		    tempDir->printAll();
	    }


	    //Create a new Directory within the current Directory
	    void FileSystem::mkdir(std::string name) {
		    Directory* tempDir = nullptr;
		    cd("",tempDir);
		    tempDir->createDir(name);
		    return;
	    }


	    //Create a new File within the current Directory
	    void FileSystem::createFile(std::string name) {
		    Directory* tempDir=nullptr;
		    cd("", tempDir);
		    tempDir->createFile(name);
		    return;
	    }


	    //View the contents of the File
	    std::string FileSystem::viewFile(std::string name) {
		    Directory* tempDir=nullptr;
		    cd("", tempDir);
		    return tempDir->getFileContent(name);
	    }


	    //Append content to File
	    void FileSystem::addToFile(std::string name,std::string content) {
		    Directory* tempDir=nullptr;
		    cd("", tempDir);
		    if (!tempDir->fileExists(name)) {
			    std::cout << "File does not exist." << std::endl;
			    return;
		    }
			std::vector<FileBlock*> newBlocks;
			int s = FileBlock::getSize();
			int i = 0;
			std::string temp;
			while (i<int(content.size())) {
				temp = content.substr(i,s);
				if (fileBlocks.size() == 0) {
					std::cout << " Memory Limit Exceeded." << std::endl;
					for (FileBlock* tp : newBlocks) fileBlocks.push_back(tp);
					return;
				}
				fileBlocks.back()->addContent(temp);
				newBlocks.push_back(fileBlocks.back());
				fileBlocks.pop_back();
				i += s;
			}
		    tempDir->setFileContent(name, newBlocks);
	    }
	

	    //Delete a File
	    void FileSystem::delFile(std::string name) {
		    Directory* tempDir = nullptr; 
		    cd("",tempDir);
			std::vector<FileBlock*> freeBlocks  = tempDir->deleteFile(name);
			fileBlocks.insert(fileBlocks.begin()+fileBlocks.size(), freeBlocks.begin(), freeBlocks.end());
		    return;
	    }


		//Delete a Directory
		void FileSystem::delDir(std::string name) {
			Directory* tempDir = nullptr;
			cd("", tempDir);
			std::vector<FileBlock*> freeBlocks = tempDir->deleteDir(name);
			fileBlocks.insert(fileBlocks.begin() + fileBlocks.size(), freeBlocks.begin(), freeBlocks.end());
			return;
		}


	    //Navigate to Directory
	    void FileSystem::cd(std::string path, Directory*& ptr) {
		    if (path == "..") {
			    if (currentDir == "root") return;
			    else currentDir = currentDir.substr(0, currentDir.rfind("/"));}
		    else {
				if(path !="") path = currentDir + "/" + path;
				else path = currentDir;
				if (path == "root") { ptr = root; return; }
				auto pos1 = path.find("/", 0);
				auto pos2 = path.find("/", pos1 + 1);
				if (pos2 == std::string::npos) pos2 = path.size();
				Directory* tempDir = root;
				while (pos1 != std::string::npos) {
					std::string tp = path.substr(pos1 + 1, pos2 - pos1 - 1);
					tempDir = tempDir->getDir(tp);
					if(!tempDir) {
						std::cout << "The System cannot find the path specified." << std::endl;
						return;
					}
					pos1 = path.find("/", pos1 + 1);
					pos2 = path.find("/", pos1 + 1);
					if (pos2 == std::string::npos) pos2 = path.size();
				}
				if (tempDir) {
					ptr = tempDir; currentDir = path;
				}
		    }
	    }

        //Get the display path in the console window
	    std::string FileSystem::getDirectory() {
			char userName[UNLEN + 1];
			char computerName[MAX_COMPUTERNAME_LENGTH + 1];
			DWORD userName_len = UNLEN + 1;
			DWORD computerName_len = MAX_COMPUTERNAME_LENGTH + 1;
			GetUserName(userName, &userName_len);
			GetComputerName(computerName, &computerName_len);
			std::string str = userName;
			str.append("@");
			str.append(computerName);
		    str.append(":" + currentDir + "$ ");
			std::transform(str.begin(), str.end(), str.begin(), tolower);
			return str;
	    }


		//Helper Function to parse input string
	    void FileSystem::parse2(std::string temp, int& command, std::string &path, std::string &content, std::string &fileName, std::string &name) {
		    std::string cmd;
		    int pos1 = temp.find(" ", 0);
		    if (pos1 != std::string::npos) {
			    cmd = temp.substr(0, pos1);
			    if (cmd == "mkdir") { command = 2; path = temp.substr(pos1 + 1);}
				else if (cmd == "rmdir") { command = 10; name = temp.substr(pos1 + 1); }
			    else if (cmd == ">" || "touch") { command = 3; fileName = temp.substr(pos1 + 1);}
			    else if (cmd == "cat") { command = 4; fileName = temp.substr(pos1 + 1);}
			    else if (cmd == "vi") { 
					command = 8;
				    auto pos2 = temp.find("\"",pos1+1);
				    auto pos3 = temp.rfind("\"");
				    fileName = temp.substr(pos1 + 1, (temp.find(" ", pos1 + 1))-pos1-1);
				    content = temp.substr(pos2+1,pos3-pos2-1);
				}
			    else if (cmd == "rm") { command = 9; name = temp.substr(pos1 + 1);}
			    else if (cmd == "cd") { command = 7; path = temp.substr(pos1 + 1);}
				else if (cmd == "savefs") { command = 12; path = temp.substr(pos1 + 1); }
				else if (cmd == "mountfs") { command = 11; path = temp.substr(pos1 + 1); }
			    else command = 15;
			}
		    else {
			    if (temp == "ls") command = 1;
			    else if (temp == "clear") command = 5;
			    else if (temp == "exit") command = 6;
				else if (temp == "history") command = 14;
				else if (temp == "resetfs") command = 13;
				else if (temp == "savefs") command = 12;
			    else command = 15;
			}
	    }


	    //Parse input string
	    void FileSystem::parse(std::string temp) {
		    std::string exp = "";
		    exp = exp +	"(ls)|" +
			    "(mkdir) [0-9A-Za-z]+|" +
				"(mountfs) ([0-9A-Za-z]+(/)?)*|" +
				"(resetfs)|" +
				"(savefs)|" +
			    "(clear)|" +
			    "(exit)|" +
				"(history)|" +
			    "(cd \\.\\.)|" +
			    "(cd) [0-9A-Za-z]+(/[0-9A-Za-z]+)*|" +
			    "(rm) [0-9A-Za-z]+(.[A-Za-z]+)?|" +
			    "(>) [0-9A-Za-z]+(.)[A-Za-z]+|" +
				"(touch) [0-9A-Za-z]+(.)[A-Za-z]+|" +
			    "(cat) [0-9A-Za-z]+(.)[A-Za-z]+|" +
			    "(rmdir) [0-9A-Za-z]+|" +
			    "(vi) [0-9A-Za-z]+(.)[A-Za-z]+ \".*\"";		  
		    std::regex pt(exp);
		    if (!std::regex_match(temp, pt)) {
			    std::cout << "Incorrect Command." << std::endl;
			    return;
		    }
		    int command;
		    std::string path="", content="",fileName="", name="";
		    Directory* tempPtr = nullptr;
		    parse2(temp, command, path, content, fileName, name);
		    switch (command) {
		    case 1://ls		
			    ls();
			    break;
		    case 2://mkdir
			    mkdir(path);
			    break;
		    case 3://> or touch
			    createFile(fileName);
			    break;
		    case 4://cat			
			    std::cout << viewFile(fileName) << std::endl;
			    break;
		    case 5://clear Screen
			    system("cls");
			    break;
		    case 6://exit
			    exit(0);
		    case 7://cd
			    cd(path,tempPtr);
			    break;
		    case 8://vi	
			    addToFile(fileName, content);
			    break;
		    case 9://rm				
			    delFile(name);
			    break;
		    case 10://rm				
			    delDir(name);
			    break;
			case 11://mountfs				
				mountFS(name);
				break;
			case 12://savefs				
				saveFS();
				break;
			case 13://resetfs				
				resetFS();
				break;
			case 14://history				
				history();
				break;
		    default:
			    std::cout << "Incorrect Command." << std::endl;
		    };	
	    }


	    //Save FileSystem to disk
	    void FileSystem::saveFS(std::string location) {
		    fs::path currPath;
		    if (location == "") currPath = fs::current_path();
		    else currPath = location;
		    root->storeToDisk(currPath);
	    }


	    //Load FileSystem from disk
	    void FileSystem::mountFS(std::string location) {
			resetFS();
			return;
	    }


	    //Reset FileSystem
	    void FileSystem::resetFS() {
			std::vector<FileBlock*> freeBlocks = root->resetContent();
			fileBlocks.insert(fileBlocks.begin() + fileBlocks.size(), freeBlocks.begin(), freeBlocks.end());
			currentDir = "root";
			return;
	    }


	    //Get History
	    void FileSystem::history() {
			return;
	    }


		//Run FileSystem
		void FileSystem::run() {
			FileSystem obj;
			std::string str;
			while (true) {
				std::cout << obj.getDirectory();
				getline(std::cin, str);
				obj.parse(str);
			}
		}


		//Destructor
	    FileSystem::~FileSystem() {
			resetFS();
		    for (FileBlock* fb : fileBlocks)
			    delete fb;
	    }
