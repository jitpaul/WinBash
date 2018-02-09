#include "filesystem.h"


int main() {
	FileSystem obj;
	string str;
	int i = 1;
	while (i++<10) {
		cout << obj.getDirectory() << ": ";
		getline(cin, str);
		obj.parse(str);
	}
	obj.saveFS();
	return 0;
}