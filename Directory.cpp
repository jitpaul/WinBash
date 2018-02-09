#include "directory.h"
#include <iostream>
using std::pair;
using std::cout;
using std::endl;



Directory::Directory(string n) :name(n),updateDate("") {}

Directory* Directory::getDir(string dirName) {
	if (dir.find(dirName) == dir.end()) return nullptr;
	else return dir[dirName];
}

void Directory::setDir(string dirName, Directory* newDir) {
	dir[dirName] = newDir;
}

void Directory::deleteDir2() {
	for (pair<string, Directory*> tp : dir) {
		tp.second->deleteDir2();
		delete tp.second;
	}
	for (pair<string, File*> tp : file) {
		delete tp.second;
	}
}


void Directory::deleteDir(string dirName) {
	if (dir.find(dirName) == dir.end()) return;
	dir[dirName]->deleteDir2();
	delete dir[dirName];
	dir.erase(dirName);
}

File* Directory::getFile(string fileName) {
	if (file.find(fileName) == file.end()) return nullptr;
	else return file[fileName];
}

void Directory::setFile(string fileName, File* newFile) {
	file[fileName] = newFile;
}

void Directory::deleteFile(string fileName) {
	if (file.find(fileName) == file.end()) return;
	delete file[fileName];
	file.erase(fileName);
}

void Directory::printAll() {
	for (pair<string, Directory*> tp : dir)
		cout << tp.first + " " + tp.second->updateDate + " " + "Type:Directory" << endl;
	for (pair<string, File*> tp : file)
		cout << tp.first + " " + tp.second->getUpdateDate() + " " + "Type:File" << endl;
}

string Directory::getUpdateDate() { return updateDate; }

void Directory::setUpdateDate(string date) { updateDate = date; }


void Directory::create(fs::path currPath) {
	currPath /= name;
	fs::create_directory(currPath);
	for (pair<string, Directory*> tp : dir)
		tp.second->create(currPath);

	for (pair<string, File*> tp : file) {
		std::fstream f(currPath.string() +"\\" +tp.first, std::ios::out);
		f << tp.second->getContent();
		f.close();
	}
}