#include "file.h"

File::File() :name(""), content(""), updateDate("") {}

File::File(string n) :name(n), content(""), updateDate("") {}

string File::getContent() { return content; }

void File::setContent(string c) { content.append(c); }

string File::getUpdateDate() { return updateDate; }

void File::setUpdateDate(string date) { updateDate = date; }