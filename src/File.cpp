#include "file.h"

    File::File() :name(""), content(""), updateDate("") {}


    File::File(std::string n) :name(n), content(""), updateDate("") {}

	//Get file content
    std::string File::getContent() { 
	    std::string ret="";
	    for (FileBlock* fb : fileBlocks)
		    ret.append(fb->getContent());
	    return ret;
    }

    //Set file content
    void File::setContent(std::vector<FileBlock*> newBlocks) {
	    for(FileBlock* fb: newBlocks)
	        fileBlocks.push_back(fb);
    }

    //Get last update date of the file
    std::string File::getUpdateDate() { return updateDate; }

	//Set last update date of the file
    void File::setUpdateDate(std::string date) { updateDate = date; }
