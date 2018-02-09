#include "filesystem.h"


int main() {
	FileSystem obj;
	string temp;
	while (1) {
		cout << obj.getDirectory() << ": ";
		getline(cin, temp);
		obj.parse(temp);
	}
	return 0;
}