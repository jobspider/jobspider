#include<WinSock2.h>
#include<iostream>
#include<queue>
#include<windows.h>
using namespace std;
class CHttp {
private:
	SOCKET m_socket;
	string m_host;
	string m_object;
public:
	CHttp();
	~CHttp();
	bool AnalyseUrl(string url);//解析出主机名和资源名
	bool Connect();
	bool Init();			//初始化
	string getHtml();		//获取子网页数据
};
bool StartCatch(string url);
