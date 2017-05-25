#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class FileSystem
{
	struct Node
	{
		string name;
		string type;
		string content;
		map <string, Node*> dir;
	}*root, *tempNode;

public:
	FileSystem()
	{
		root = new Node;
		root->name = "Root";
		root->type = "Dir";
		root->content = "";
	}

	vector<string> ls(string path)
	{
		vector <string> res;
		string st;
		if (path == "/")
		{
			for (pair <string, Node*> pr : root->dir)
			{
				st = pr.first;
				res.push_back(st);
			}
			return res;
		}
		auto pos1 = path.find("/", 0);
		auto pos2 = path.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = path.size();
		string tp;
		tempNode = root;
		while (pos1 != string::npos)
		{
			tp = path.substr(pos1 + 1, pos2 - pos1 - 1);
			tempNode = (tempNode->dir)[tp];
			if (tempNode->type == "File")
			{
				res.push_back(tempNode->name);
				return res;
			}
			pos1 = path.find("/", pos1 + 1);
			pos2 = path.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = path.size();
		}
		for (pair <string, Node*> pr : tempNode->dir)
		{
			st = pr.first;
			res.push_back(st);
		}
		return res;
	}

	void mkdir(string path)
	{
		auto pos1 = path.find("/", 0);
		auto pos2 = path.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = path.size();
		string tp;
		tempNode = root;
		while (pos1 != string::npos)
		{
			tp = path.substr(pos1 + 1, pos2 - pos1 - 1);
			auto it = (tempNode->dir).find(tp);
			if (it != (tempNode->dir).end())
				tempNode = it->second;
			else
			{
				Node * newNode = new Node;
				newNode->name = tp;
				newNode->type = "Dir";
				newNode->content = "";
				(tempNode->dir)[tp] = newNode;
				tempNode = newNode;
			}
			pos1 = path.find("/", pos1 + 1);
			pos2 = path.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = path.size();
		}
		return;
	}

	void addContentToFile(string filePath, string content)
	{
		auto pos1 = filePath.find("/", 0);
		auto pos2 = filePath.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = filePath.size();
		string tp;
		tempNode = root;
		while (pos1 != string::npos)
		{
			tp = filePath.substr(pos1 + 1, pos2 - pos1 - 1);
			auto it = (tempNode->dir).find(tp);
			if (it != (tempNode->dir).end())
				tempNode = it->second;
			else
			{
				Node * newNode = new Node;
				newNode->name = tp;
				newNode->type = "File";
				newNode->content = content;
				(tempNode->dir)[tp] = newNode;
				return;
			}
			pos1 = filePath.find("/", pos1 + 1);
			pos2 = filePath.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = filePath.size();
		}
		(tempNode->content).append(content);
		return;
	}

	string readContentFromFile(string filePath)
	{
		auto pos1 = filePath.find("/", 0);
		auto pos2 = filePath.find("/", pos1 + 1);
		if (pos2 == string::npos)
			pos2 = filePath.size();
		string tp;
		tempNode = root;
		while (pos1 != string::npos)
		{
			tp = filePath.substr(pos1 + 1, pos2 - pos1 - 1);
			tempNode = (tempNode->dir)[tp];
			pos1 = filePath.find("/", pos1 + 1);
			pos2 = filePath.find("/", pos1 + 1);
			if (pos2 == string::npos)
				pos2 = filePath.size();
		}
		return tempNode->content;
	}
};

string path, content,cmd;
int command,pos1, pos2,pos3;
void parse(string temp)
{	
	pos1 = temp.find(" ", 0);
	if ( pos1 != string::npos)
	{
		cmd = temp.substr(0, pos1);
		if (cmd == "ls")
		{
			command = 1;
			pos2 = temp.find(" ", pos1 + 1);
			if (pos2 != string::npos)
				command = 7;
			else
				path = temp.substr(pos1 + 1, temp.size() - pos1 - 1);
		}
		else if (cmd == "mkdir")
		{
		    command = 2;
			pos2 = temp.find(" ", pos1+1);
			if (pos2 != string::npos)
				command = 7;
			else
				path = temp.substr(pos1 + 1,temp.size()-pos1-1);
	    }
		else if (cmd == "addContentToFile")
		{
			command = 3;
			pos2 = temp.find(" ", pos1 + 1);
			pos3 = temp.find(" ", pos2 + 1);
			if (pos2 != string::npos && pos3 == string::npos)
			{
				path = temp.substr(pos1 + 1, pos2-pos1-1);
				content = temp.substr(pos2 + 1, temp.size() - pos2 - 1);
			}
			else
				command = 7;

		}
		else if (cmd == "readContentFromFile")
		{
			command = 4;
			pos2 = temp.find(" ", pos1 + 1);
			if (pos2 != string::npos)
				command = 7;
			else
				path = temp.substr(pos1 + 1, temp.size() - pos1 - 1);
		}
		else
			command = 7;

	}
	else
	{
		if (temp == "cls")
			command = 5;
		else if (temp == "exit")
			command = 6;
		else
			command = 7;
	}
}

int main()
{
	 
	 FileSystem *obj = new FileSystem();
	 string temp;
	 vector<string> resVector;
	 cout << "command -> ";
	 getline(cin,temp);
	 parse(temp);
	 
	 while (1)
	 {		 
		 switch (command)
		 {
		 case 1:	//ls		
			 resVector = obj->ls(path);
			 for (string tp : resVector)
				 cout << tp << endl;
			 break;
		 case 2://mkdir
			 obj->mkdir(path);
			 break;
		 case 3://addContentToFile
			 obj->addContentToFile(path, content);
			 break;
		 case 4://readContentFromFile				
			 cout << obj->readContentFromFile(path);
			 break;
		 case 5://clear Screen
			 system("cls");
			 break;
		 case 6://exit
			 return 0;
		 default:
			 cout << endl<<"Incorrect Command.";
		 };
		 cout <<endl<<"command -> ";
		 getline(cin,temp);
		 parse(temp);
	 }
	 return 0;

}

