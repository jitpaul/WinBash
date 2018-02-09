#include "filesystem.h"


int main() {
	FileSystem obj;
	string str;
	while (1) {
		cout << obj.getDirectory() << ": ";
		getline(cin, str);
		obj.parse(str);
	}
	return 0;
}