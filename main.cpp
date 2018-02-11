#include "filesystem.h"


int main() {
	FileSystem obj(100);
	string str;
	while (true) {
		cout << obj.getDirectory() << ": ";
		getline(cin, str);
		obj.parse(str);
	}
	obj.saveFS();
	return 0;
}