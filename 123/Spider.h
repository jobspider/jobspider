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
	bool AnalyseUrl(string url);//����������������Դ��
	bool Connect();
	bool Init();			//��ʼ��
	string getHtml();		//��ȡ����ҳ����
};
bool StartCatch(string url);
