#include<WinSock2.h>
#include<iostream>
#include<queue>
#include<windows.h>
using namespace std;

class CHttp {
public:
	string host;
	string object;
	CHttp();
	~CHttp();
	bool AnalyseUrl(string url);
};

class Job {
public:
	string name;
	string company;
	string place;
	string salary;
	string time;
	string html;
};
//string HttpRequest(char * host, short port, char * object, char * lpPostData, int nPostDataLen);
string getHtml(string url, char* filename);
void searchJob();
void parse(string html);