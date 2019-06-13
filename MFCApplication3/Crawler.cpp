#include"stdafx.h"
#include"crawler.h"
#include "Wininet.h"
#include<Windows.h>
#include <thread>
#include<string>
#include<regex>
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
		memset(Buffer, 0, 4096);
		unsigned long lNumberOfBytesRead;
		bRet = InternetReadFile(hRequest, Buffer, sizeof(Buffer) - 1, &lNumberOfBytesRead);
		if (!bRet || !lNumberOfBytesRead)
			break;
		Buffer[lNumberOfBytesRead] = 0;
		strResponse += Buffer;
	}

	return strResponse;
}






string getHtml(string url, char* filename)
{
	CHttp c;
	while (!c.AnalyseUrl(url)) {
		cout << "无效网址" << endl;
		cin >> url;
	}


	char a[30];
	strcpy_s(a, c.host.c_str());
	char b[100];
	strcpy_s(b, c.object.c_str());
	string recieve = HttpRequest(a, 80, b, NULL, 0);

	//cout << recieve.c_str();
	FILE * fp;
	errno_t t = fopen_s(&fp, filename, "w");
	fwrite(recieve.c_str(), 1, recieve.length(), fp);
	fclose(fp);
	return recieve;

}


void searchJob() {
	//https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,1.html
	//https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,2.html
	//https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,3.html
	//改最后的数字跳转页码

	int i = 1;
	while (i < 30) {
		string url = "https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,";

		char page[50];
		sprintf_s(page, "%d", i);

		url = url + page + ".html";
		cout << "正在爬取:" + url << endl;
		getHtml(url, page);
		i++;

		Sleep(500);
	}

}

//解析职位列表
void Job::parse(string html)
{
	//储存结果
	smatch result;
	//定义正则表达式
	regex jobPattern("<a\\starget=\"_blank\"\\stitle=\"(.*)\"\\shref=\"(.*)\"\\sonmousedown=\"\"");
	regex componyPattern("<span\\sclass=\"t2\"><a\\starget=\"_blank\"\\stitle=\"(.*)\"\\shref=\"(.*)\">(.*)</ a></span>");
	regex locationPattern("<span\\sclass=\"t3\">(.*)</span>");
	regex salaryPattern("<span\\sclass=\"t4\">(.*)</span>");
	regex dataPattern("<span\\sclass=\"t5\">(.*)</span>");
	regex startPattern("<div\\sclass=\"el\">");
	//定义解析开始与结束的部分
	string::const_iterator start = html.begin();
	string::const_iterator end = html.end();
	string temp;
	//找到职位列表的起始位置
	while (!regex_search(start, end, result, startPattern))
		start = result[0].second;
	//定义一个结构体数组存储职位信息
	//开始解析

	while (start != end) {
		//匹配职位名
		if (regex_search(start, end, result, jobPattern))
		{
			cout << "职位：" << result[1] << " " << result[2] << endl;
		}
		//匹配公司名
		if (regex_search(start, end, result, componyPattern))
		{
			cout << "公司：" << result[1] << " " << result[2] << endl;
		}
		//匹配公司所在地区
		if (regex_search(start, end, result, locationPattern))
		{

			cout << "公司所在地：" << result[1] << endl;
		}
		//匹配薪水
		if (regex_search(start, end, result, salaryPattern))
		{

			cout << "薪资：" << result[1] << endl;
		}
		//匹配发布日期
		if (regex_search(start, end, result, dataPattern))
		{
			cout << "发布日期：" << result[1] << endl;
		}
		cout << endl;
		start = result[0].second;

	}



}


/*
int main() {
	std::thread t1(searchJob);
	t1.detach();
	std::thread t2(getchar);
	t2.join();
}*/

