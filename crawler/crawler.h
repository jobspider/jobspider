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