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
class info {
public:
	string name;
	string company;
	string salary;
	string html;
	string Info;
	string jobInformation;
	string contact;
	string companyInformation;
};
//string HttpRequest(char * host, short port, char * object, char * lpPostData, int nPostDataLen);
string getHtml(string url, char* filename);
void searchJob();
void parse(string);
//解析职位信息
void parseInfor(string);
//获得子链接
string getHtmlItem(string);