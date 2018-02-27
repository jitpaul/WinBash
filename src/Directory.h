#pragma once

#include <map>
#include <string>
#include <experimental/filesystem>
#include "file.h"
namespace fs = std::experimental::filesystem;

class Directory {

	Directory(std::string);
	Directory* getDir(std::string);
	void setDir(std::string, Directory*);
	std::vector<FileBlock*> deleteDir(std::string);
	std::string getFileContent(std::string);
	void setFileContent(std::string, std::vector<FileBlock*>&);
	std::vector<FileBlock*> deleteFile(std::string, int flag =0);
	void createDir(std::string);
	void createFile(std::string);
	void printAll();
	std::string getUpdateDate();
	void setUpdateDate(std::string);
	void storeToDisk(fs::path);
	std::vector<FileBlock*> resetContent();
	bool fileExists(std::string);

	std::string name;
	std::string updateDate;
	std::map <std::string, Directory*> dir;
	std::map <std::string, File*> file;
	friend class FileSystem;
};