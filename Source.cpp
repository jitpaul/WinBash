#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <regex>

using namespace std;

class FileSystem
{
	struct Node {
		string name;
		map <string, Node*> dir;
		map <string, string> files;
	}*root, *tempNode;

    public:

	FileSystem() {
		root = new Node;
		root->name = "root";}


	//Show Contents of the Directory
	void ls(string currentDir) {
		string tp;
		if (currentDir == "root") {
			for (pair <string, Node*> pr : root->dir)
				cout << pr.first << endl;
			for (pair <string, string> pr : root->files)
				cout << pr.first << endl;
			return;}
		auto pos1 = currentDir.find("/", 0);
		auto pos2 = currentDir.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = currentDir.size();
		tempNode = root;
		while (pos1 != string::npos) {
			tp = currentDir.substr(pos1 + 1, pos2 - pos1 - 1);
			if (tempNode)
				tempNode = (tempNode->dir)[tp];
			pos1 = currentDir.find("/", pos1 + 1);
			pos2 = currentDir.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = currentDir.size();}
		if (tempNode) {
			for (pair <string, Node*> pr : tempNode->dir)
				cout << pr.first << endl;
			for (pair <string, string> pr : tempNode->files)
				cout << pr.first << endl;}
		return;}


	//Make Directory
	void mkdir(string path,string currentDir) {
		path = currentDir + "/" + path;
		auto pos1 = path.find("/", 0);;
		auto pos2 = path.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = path.size();
		string tp;
		tempNode = root;
		while (pos1 != string::npos) {
			tp = path.substr(pos1 + 1, pos2 - pos1 - 1);
			auto it = (tempNode->dir).find(tp);
			if (it != (tempNode->dir).end())
				tempNode = it->second;
			else if (tp != "") {
				Node * newNode = new Node;
				newNode->name = tp;
				(tempNode->dir)[tp] = newNode;
				tempNode = newNode;}
			pos1 = path.find("/", pos1 + 1);
			pos2 = path.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = path.size();}
		return;}


	//Create File
	void createFile(string filePath, string fileName) {
		auto pos1 = filePath.find("/", 0);
		auto pos2 = filePath.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = filePath.size();
		tempNode = root;
		while (pos1 != string::npos) {
			tempNode = ((tempNode->dir).find(filePath.substr(pos1 + 1, pos2 - pos1 - 1)))->second;
			pos1 = filePath.find("/", pos1 + 1);
			pos2 = filePath.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = filePath.size();}	
		auto it = (tempNode->files).find(fileName);
		if (it == (tempNode->files).end())
			(tempNode->files)[fileName] = "";
		else
			cout << "File Already Exists" << endl;
		return;}


	//View File
	string viewFile(string filePath, string fileName) {
		auto pos1 = filePath.find("/", 0);
		auto pos2 = filePath.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = filePath.size();
		tempNode = root;
		while (pos1 != string::npos) {
			tempNode = ((tempNode->dir).find(filePath.substr(pos1 + 1, pos2 - pos1 - 1)))->second;
			pos1 = filePath.find("/", pos1 + 1);
			pos2 = filePath.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = filePath.size();}
		auto it = (tempNode->files).find(fileName);
		if (it == (tempNode->files).end())
			return "Incorrect FileName";
		else
			return it->second;}


	//Add to File
	void addToFile(string filePath,string fileName,string content) {
		auto pos1 = filePath.find("/", 0);
		auto pos2 = filePath.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = filePath.size();
		tempNode = root;
		while (pos1 != string::npos) {
			tempNode = ((tempNode->dir).find(filePath.substr(pos1 + 1, pos2 - pos1 - 1)))->second;
			pos1 = filePath.find("/", pos1 + 1);
			pos2 = filePath.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = filePath.size();}
		((tempNode->files)[fileName]).append(content + "\n");
		return;}
	

	//Delete File or Directory
	void del(string filePath,string name) {
		auto pos1 = filePath.find("/", 0);
		auto pos2 = filePath.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = filePath.size();
		tempNode = root;
		while (pos1 != string::npos) {
			tempNode = ((tempNode->dir).find(filePath.substr(pos1 + 1, pos2 - pos1 - 1)))->second;
			pos1 = filePath.find("/", pos1 + 1);
			pos2 = filePath.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = filePath.size();}
		auto it = (tempNode->files).find(name);
		if (it != (tempNode->files).end())
			(tempNode->files).erase(it);
		else {
			auto it = (tempNode->dir).find(name);
			if (it != (tempNode->dir).end())
				(tempNode->dir).erase(it);}
		return;}


	//Navigate to Directory
	string cd(string path, string currentDir) {
		string ret = "",tp;
		if (path == "..") {
			if (currentDir == "root")
				ret = currentDir;
			else
				ret = currentDir.substr(0, currentDir.rfind("/"));}
		else {
				path = currentDir + "/" + path;
				auto pos1 = path.find("/", 0);
				auto pos2 = path.find("/", pos1 + 1);
				if (pos2 == string::npos)
					pos2 = path.size();
				tempNode = root;
				while (pos1 != string::npos) {
					tp = path.substr(pos1 + 1, pos2 - pos1 - 1);
					if (tempNode)
						tempNode = (tempNode->dir)[tp];
					pos1 = path.find("/", pos1 + 1);
					pos2 = path.find("/", pos1 + 1);
					if (pos2 == string::npos)
						pos2 = path.size();}
				if (tempNode)
					ret = path;
				else
					ret = currentDir;}
			return ret;}
};



	string path, content, cmd, currentDir = "root",fileName,name;
	int command, pos1, pos2, pos3;
	void parse(string temp) {
		pos1 = temp.find(" ", 0);
		if (pos1 != string::npos) {
			cmd = temp.substr(0, pos1);
			if (cmd == "mkdir") {
				command = 2;
				path = temp.substr(pos1 + 1);}
			else if (cmd == ">") {
				command = 3;
				fileName = temp.substr(pos1 + 1);}
			else if (cmd == "cat") {
				command = 4;
				fileName = temp.substr(pos1 + 1);}
			else if (cmd == "vi") {
				command = 8;
				auto pos2 = temp.find("\"",pos1+1);
				auto pos3 = temp.rfind("\"");
				fileName = temp.substr(pos1 + 1, (temp.find(" ", pos1 + 1))-pos1-1);
				content = temp.substr(pos2+1,pos3-pos2-1);}
			else if (cmd == "rm") {
				command = 9;
				name = temp.substr(pos1 + 1);}
			else if (cmd == "cd") {
				command = 7;
				path = temp.substr(pos1 + 1);}
			else
				command = 15;}
		else {
			if (temp == "ls")
				command = 1;
			else if (temp == "cls")
				command = 5;
			else if (temp == "exit")
				command = 6;
			else
				command = 15;}}



	int main() {
		FileSystem *obj = new FileSystem();
		string temp;
		vector<string> resVector;
		regex pt("(ls)|(mkdir) [0-9A-Za-z]+(/[0-9A-Za-z]+)*|(cls)|(exit)|(cd \\.\\.)|(cd) [0-9A-Za-z]+(/[0-9A-Za-z]+)*|(rm) [0-9A-Za-z]+(.[A-Za-z]+)?|(>) [0-9A-Za-z]+(.)[A-Za-z]+|(cat) [0-9A-Za-z]+(.)[A-Za-z]+|(vi) [0-9A-Za-z]+(.)[A-Za-z]+ \".*\"");
		while (1) {
			cout << currentDir << ": ";
			getline(cin, temp);
			if (!regex_match(temp, pt)) {
				cout << "Incorrect Command." << endl;
				continue;}
			parse(temp);
			switch (command) {
			case 1://ls		
				obj->ls(currentDir);
				break;
			case 2://mkdir
				obj->mkdir(path,currentDir);
				break;
			case 3://>
				obj->createFile(currentDir, fileName);
				break;
			case 4://cat			
				cout<<obj->viewFile(currentDir, fileName)<<endl;
				break;
			case 5://clear Screen
				system("cls");
				break;
			case 6://exit
				return 0;
			case 7://cd
				currentDir = obj->cd(path,currentDir);
				break;
			case 8://vi	
				obj->addToFile(currentDir,fileName,content);
				break;
			case 9://rm				
				obj->del(currentDir,name);
				break;
			default:
				cout << "Incorrect Command." << endl;};}
		return 0;
}