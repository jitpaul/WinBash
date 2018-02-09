#include "filesystem.h"


		FileSystem::FileSystem() {
			root = new Directory("root");
			currentDir = "root";
		}

	    //Show Contents of the Directory
	    void FileSystem::ls() {
		    Directory* tempDir = nullptr;
		    cd("",tempDir);
		    tempDir->printAll();
	    }

	    //Make Directory
	    void FileSystem::mkdir(string name) {
		    Directory* tempDir = nullptr;
		    cd("",tempDir);
		    if (tempDir->getDir(name)) {
			    cout << "Directory already exists." << endl;
			    return;
		    }
		    Directory* newDirec = new Directory(name);
		    tempDir->setDir(name, newDirec);
		    currentDir = currentDir + "/" + name;
		    return;
	    }

	    //Create File
	    void FileSystem::createFile(string name) {
		    Directory* tempDir=nullptr;
		    cd("", tempDir);
		    if (tempDir->getFile(name)) {
			    cout << "File already exists." << endl;
			    return;
		    }
		    File* newFile = new File(name);
		    tempDir->setFile(name, newFile);
		    return;
	    }

	    //View File
	    string FileSystem::viewFile(string name) {
		    Directory* tempDir=nullptr;
		    cd("", tempDir);
		    if (!tempDir->getFile(name)) {
			    cout << "File does not exist." << endl;
			    return "";
		    }
		    return tempDir->getFile(name)->getContent();
	    }

	    //Add to File
	    void FileSystem::addToFile(string name,string content) {
		    Directory* tempDir=nullptr;
		    cd("", tempDir);
		    if (!tempDir->getFile(name)) {
			    cout << "File does not exist." << endl;
			    return;
		    }
		    tempDir->getFile(name)->setContent(content);
	    }
	
	    //Delete File or Directory
	    void FileSystem::del(string name) {
		    Directory* tempDir = nullptr; 
		    cd("",tempDir);
		    tempDir->deleteDir(name);
		    tempDir->deleteFile(name);
		    return;
	    }

	    //Navigate to Directory
	    void FileSystem::cd(string path, Directory*& ptr) {
		    if (path == "..") {
			    if (currentDir == "root") return;
			    else currentDir = currentDir.substr(0, currentDir.rfind("/"));}
		    else {
				if(path !="") path = currentDir + "/" + path;
				else path = currentDir;
				if (path == "root") { ptr = root; return; }
				auto pos1 = path.find("/", 0);
				auto pos2 = path.find("/", pos1 + 1);
				if (pos2 == string::npos) pos2 = path.size();
				Directory* tempDir = root;
				while (pos1 != string::npos) {
					string tp = path.substr(pos1 + 1, pos2 - pos1 - 1);
					tempDir = tempDir->getDir(tp);
					if(!tempDir) {
						cout << "The System cannot find the path specified." << endl;
						return;
					}
					pos1 = path.find("/", pos1 + 1);
					pos2 = path.find("/", pos1 + 1);
					if (pos2 == string::npos) pos2 = path.size();
				}
				if (tempDir) {
					ptr = tempDir; currentDir = path;
				}
		    }
	    }

	    string FileSystem::getDirectory() {
		    return currentDir;
	    }

	    void FileSystem::parse2(string temp, int& command, string &path, string &content, string &fileName, string &name) {
		    string cmd;
		    int pos1 = temp.find(" ", 0);
		    if (pos1 != string::npos) {
			    cmd = temp.substr(0, pos1);
			    if (cmd == "mkdir") { command = 2; path = temp.substr(pos1 + 1);}
			    else if (cmd == ">") { command = 3; fileName = temp.substr(pos1 + 1);}
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
			    else command = 15;
			}
		    else {
			    if (temp == "ls") command = 1;
			    else if (temp == "cls") command = 5;
			    else if (temp == "exit") command = 6;
			    else command = 15;
			}
	    }

	//Parse input string
	void FileSystem::parse(string temp) {
		regex pt("(ls)|(mkdir) [0-9A-Za-z]+|(cls)|(exit)|(cd \\.\\.)|(cd) [0-9A-Za-z]+(/[0-9A-Za-z]+)*|(rm) [0-9A-Za-z]+(.[A-Za-z]+)?|(>) [0-9A-Za-z]+(.)[A-Za-z]+|(cat) [0-9A-Za-z]+(.)[A-Za-z]+|(vi) [0-9A-Za-z]+(.)[A-Za-z]+ \".*\"");
		if (!regex_match(temp, pt)) {
			cout << "Incorrect Command." << endl;
			return;
		}
		int command;
		string path="", content="",fileName="", name="";
		Directory* tempPtr = nullptr;
		parse2(temp, command, path, content, fileName, name);
		switch (command) {
		case 1://ls		
			ls();
			break;
		case 2://mkdir
			mkdir(path);
			break;
		case 3://>
			createFile(fileName);
			break;
		case 4://cat			
			cout << viewFile(fileName) << endl;
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
			del(name);
			break;
		default:
			cout << "Incorrect Command." << endl;
		};	
	}

	//save FileSystem to disk
	void FileSystem::saveFS(string location) {

	}

	//load FileSystem from disk
	void FileSystem::loadFS(string location) {

	}

	//reset FileSystem
	void FileSystem::resetFS() {

	}
