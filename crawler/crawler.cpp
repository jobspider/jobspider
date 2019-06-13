#include"pch.h"
#include"crawler.h"
#include "Wininet.h"
#include<Windows.h>
#include<string>
#pragma comment(lib,"Wininet.lib")
using namespace std;



CHttp::CHttp()
{
	object = "";
	host = "";
}

CHttp::~CHttp()
{
}

bool CHttp::AnalyseUrl(string url)
{
	int k = 8;
	if (string::npos == url.find("https://")) {
		k = 7;
		if (string::npos == url.find("http://")) {
			return false;
		}
	}
	int i;
	if ((i = url.find('/', k)) == -1) {
		i = url.length();
		host = url.substr(k);
		object = "/";
		cout << "主机名:" << host << endl;
		cout << "资源名:" << object << endl;
	}
	else {
		//主机名
		host = url.substr(k, i - k);
		//资源名
		object = url.substr(i);
		cout << "主机名:" << host << endl;
		cout << "资源名:" << object << endl;
	}
	return true;
}

string HttpRequest(char * host, short port, char * object, char * lpPostData, int nPostDataLen)
{
	//创建HINTERNET句柄
	HINTERNET hInternet, hConnect, hRequest;
	BOOL bRet;
	string strResponse;
	hInternet = 0;
	hConnect = 0;
	hRequest = 0;
	//开始连接
	//Open得到Connect句柄
	hInternet = (HINSTANCE)InternetOpen("User-Agent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hInternet) {
		InternetCloseHandle(hInternet);
		cout << "连接失败" << endl;
		return false;
	}
	//Connect得到request句柄 访问HTTP
	hConnect = (HINSTANCE)InternetConnect(hInternet, host, port, NULL, "HTTP/1.1", INTERNET_SERVICE_HTTP, 0, 0);
	if (!hConnect) {
		InternetCloseHandle(hConnect);
		cout << "连接失败" << endl;
		return false;
	}
	//Request发送数据
	hRequest = (HINSTANCE)HttpOpenRequest(hConnect, "GET", object, "HTTP/1.1", NULL, NULL, INTERNET_FLAG_RELOAD, 0);
	if (!hRequest) {
		InternetCloseHandle(hConnect);
		cout << "连接失败" << endl;
		return false;
	}

	
	//bRet = HttpAddRequestHeaders(hRequest,"Content-Type: application/x-www-form-urlencoded",Len(FORMHEADERS),HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
	//接收数据
	bRet = HttpSendRequest(hRequest, NULL, 0, lpPostData, nPostDataLen);
	while (TRUE)
	{
		char Buffer[4096];
		unsigned long lNumberOfBytesRead;
		bRet = InternetReadFile(hRequest, Buffer, sizeof(Buffer) - 1, &lNumberOfBytesRead);
		if (!bRet || !lNumberOfBytesRead)
			break;
		Buffer[lNumberOfBytesRead] = 0;
		strResponse += Buffer;
	}

	return strResponse;
}


int main()
{
	CHttp c;
	string url;
	cin >> url;

	while(!c.AnalyseUrl(url)) {
		cout <<"无效网址"<< endl;
		cin >> url;
	}

	//https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,1.html
	//https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,2.html
	//https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,3.html
	//改最后的数字跳转页码

	char a[30];
	strcpy_s(a, c.host.c_str());
	char b[100];
	strcpy_s(b, c.object.c_str());
	string recieve = HttpRequest(a, 80, b, NULL, 0);

	cout << recieve.c_str();

	FILE * fp;
	errno_t t = fopen_s(&fp, "log.txt", "w");
	fwrite(recieve.c_str(), 1, recieve.length(), fp);
	fclose(fp);
	return 0;
}


