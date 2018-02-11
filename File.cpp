#include "file.h"

File::File() :name(""), content(""), updateDate("") {}

File::File(string n) :name(n), content(""), updateDate("") {}

string File::getContent() { 
	string ret="";
	for (FileBlock* fb : fileBlocks)
		ret.append(fb->getContent());
	return ret;
}

void File::setContent(std::vector<FileBlock*> newBlocks) {
	for(FileBlock* fb: newBlocks)
	    fileBlocks.push_back(fb);
}

string File::getUpdateDate() { return updateDate; }

void File::setUpdateDate(string date) { updateDate = date; }
