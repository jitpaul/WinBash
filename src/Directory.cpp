#include "directory.h"
#include <iostream>
#include <fstream>


    Directory::Directory(std::string n) :name(n),updateDate("") {}


    Directory* Directory::getDir(std::string dirName) {
	    if (dir.find(dirName) == dir.end()) return nullptr;
	    else return dir[dirName];
    }


    void Directory::setDir(std::string dirName, Directory* newDir) {
	    dir[dirName] = newDir;
    }


    //Delete a directory and all its contents
    std::vector<FileBlock*> Directory::deleteDir(std::string dirName) {
	    if (dir.find(dirName) == dir.end()) return {};
	    std::vector<FileBlock*> ret = dir[dirName]->resetContent();
	    delete dir[dirName];
	    dir.erase(dirName);
	    return ret;
    }

    bool Directory::fileExists(std::string fileName) {
	    if (file.find(fileName) == file.end()) return false;
	    return true;
    }


    std::string Directory::getFileContent(std::string fileName) {
	    if(!fileExists(fileName)) 
		    std::cout << "File does not exist." << std::endl;
	    return file[fileName]->getContent();
    }


    void Directory::setFileContent(std::string fileName, std::vector<FileBlock*>& newBlocks) {
	    file[fileName]->setContent(newBlocks);
    }


    //Delete a File
    std::vector<FileBlock*> Directory::deleteFile(std::string fileName, int flag) {
	    if (file.find(fileName) == file.end()) return{};
	    std::vector<FileBlock*> ret;
	    for (FileBlock* tp : file[fileName]->fileBlocks)
		    ret.push_back(tp);
		if (flag == 0) {
			delete file[fileName];
			file.erase(fileName);
		}
	    return ret;
    }


    //Create Directory
    void Directory::createDir(std::string name) {
	    if (getDir(name)) {
		    std::cout << "Directory already exists." << std::endl;
		    return;
	    }
	    Directory* newDirec = new Directory(name);
	    setDir(name, newDirec);
	    return;
    }


    //Create File
    void Directory::createFile(std::string name) {
	    if (fileExists(name)) {
		    std::cout << "File already exists." << std::endl;
		    return;
	    }
	    File* newFile = new File(name);
	    file[name] = newFile;
	    return;
    }


    void Directory::printAll() {
	     for (std::pair<std::string, Directory*> tp : dir)
		     std::cout << tp.first + "  " + tp.second->updateDate + "  " + "Type:Directory" << std::endl;
	    for (std::pair<std::string, File*> tp : file)
		    std::cout << tp.first + "  " + tp.second->getUpdateDate() + " " + "Type:File" << std::endl;
    }


    std::string Directory::getUpdateDate() { return updateDate; }


    void Directory::setUpdateDate(std::string date) { updateDate = date; }


    void Directory::storeToDisk(fs::path currPath) {
	    currPath /= name;
	    fs::create_directory(currPath);
	    for (std::pair<std::string, Directory*> tp : dir)
		    tp.second->storeToDisk(currPath);
	    for (std::pair<std::string, File*> tp : file) {
		    std::fstream f(currPath.string() +"\\" +tp.first, std::ios::out | std::ios::trunc);
		    f << tp.second->getContent();
		    f.close();
	    }
    }


    std::vector<FileBlock*> Directory::resetContent() {
	    std::vector<FileBlock*> ret;
	    for (std::pair<std::string, Directory*> tp : dir) {
		    std::vector<FileBlock*> tempRet = tp.second->resetContent();
		    ret.insert(ret.begin() + ret.size(), tempRet.begin(), tempRet.end());
		    delete tp.second;
	    }
	    for (std::pair<std::string, File*> tp : file) {
		    std::vector<FileBlock*> tempRet = deleteFile(tp.first,1);
		    ret.insert(ret.begin() + ret.size(), tempRet.begin(), tempRet.end());
		    delete tp.second;
	    }
	    dir.clear();
	    file.clear();
	    return ret;
    }