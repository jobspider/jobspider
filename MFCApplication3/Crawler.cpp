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
		//cout << "������:" << host << endl;
		//cout << "��Դ��:" << object << endl;
	}
	else {
		//������
		host = url.substr(k, i - k);
		//��Դ��
		object = url.substr(i);
		//cout << "������:" << host << endl;
		//cout << "��Դ��:" << object << endl;
	}
	return true;
}



string HttpRequest(char * host, short port, char * object, char * lpPostData, int nPostDataLen)
{
	//����HINTERNET���
	HINTERNET hInternet, hConnect, hRequest;
	BOOL bRet;
	string strResponse;
	hInternet = 0;
	hConnect = 0;
	hRequest = 0;
	//��ʼ����
	//Open�õ�Connect���
	hInternet = (HINSTANCE)InternetOpen("User-Agent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hInternet) {
		InternetCloseHandle(hInternet);
		//cout << "����ʧ��" << endl;
		return false;
	}
	//Connect�õ�request��� ����HTTP
	hConnect = (HINSTANCE)InternetConnect(hInternet, host, port, NULL, "HTTP/1.1", INTERNET_SERVICE_HTTP, 0, 0);
	if (!hConnect) {
		InternetCloseHandle(hConnect);
		//cout << "����ʧ��" << endl;
		return false;
	}
	//Request��������
	hRequest = (HINSTANCE)HttpOpenRequest(hConnect, "GET", object, "HTTP/1.1", NULL, NULL, INTERNET_FLAG_RELOAD, 0);
	if (!hRequest) {
		InternetCloseHandle(hConnect);
		//cout << "����ʧ��" << endl;
		return false;
	}


	//bRet = HttpAddRequestHeaders(hRequest,"Content-Type: application/x-www-form-urlencoded",Len(FORMHEADERS),HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
	//��������
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
	c.AnalyseUrl(url);


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
	//������������תҳ��

	int i = 1;
	while (i < 30) {
		string url = "https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,";

		char page[50];
		sprintf_s(page, "%d", i);

		url = url + page + ".html";
		//cout << "������ȡ:" + url << endl;
		getHtml(url, page);
		i++;

		Sleep(500);
	}

}


extern Job *jobs;
//����ְλ�б�
void parse(string html)
{
	//������
	smatch result;
	//����������ʽ
	regex jobPattern("<a\\starget=\"_blank\"\\stitle=\"(.*)\"\\shref=\"(.*)\"\\sonmousedown=\"\"");
	regex componyPattern("<span\\sclass=\"t2\"><a\\starget=\"_blank\"\\stitle=\"(.*)\"\\shref");
	regex locationPattern("<span\\sclass=\"t3\">(.*)</span>");
	regex salaryPattern("<span\\sclass=\"t4\">(.*)</span>");
	regex dataPattern("<span\\sclass=\"t5\">(.*)</span>");
	regex startPattern("<div\\sclass=\"el\">");
	//���������ʼ������Ĳ���
	string::const_iterator start = html.begin();
	string::const_iterator end = html.end();
	string temp;
	//�ҵ�ְλ�б����ʼλ��
	while (!regex_search(start, end, result, startPattern))
		start = result[0].second;
	//����һ���ṹ������洢ְλ��Ϣ
	//��ʼ����
	int i = 0;
	while (start != end) {
		//ƥ��ְλ��
		if (regex_search(start, end, result, jobPattern))
		{
			//cout << "ְλ��" << result[1] << " " << result[2] << endl;
			jobs[i].name = result[1];
			jobs[i].html = result[2];
		}
		//ƥ�乫˾��
		if (regex_search(start, end, result, componyPattern))
		{
			//cout << "��˾��" << result[1] << " " << result[2] << endl;
			jobs[i].company = result[1];
		}
		//ƥ�乫˾���ڵ���
		if (regex_search(start, end, result, locationPattern))
		{

			//cout << "��˾���ڵأ�" << result[1] << endl;
			jobs[i].place = result[1];
		}
		//ƥ��нˮ
		if (regex_search(start, end, result, salaryPattern))
		{

			//cout << "н�ʣ�" << result[1] << endl;
			jobs[i].salary = result[1];
		}
		//ƥ�䷢������
		if (regex_search(start, end, result, dataPattern))
		{
			//cout << "�������ڣ�" << result[1] << endl;
			jobs[i].time = result[1];
		}

		//cout << endl;
		start = result[0].second;
		i++;
	}



}

string getHtmlItem(string url)
{
	CHttp c;
	c.AnalyseUrl(url);


	char a[30];
	strcpy_s(a, c.host.c_str());
	char b[100];
	strcpy_s(b, c.object.c_str());
	string recieve = HttpRequest(a, 80, b, NULL, 0);

	return recieve;

}

void parseInfor(string html)
{
	//����������
	smatch result;
	//����������ʽ
	regex strPattern("<p\\sclass=\"msg\\sltype\"\\stitle=\"(.*)\">");
	regex numberPattern("");
	regex experiencePattern("");
	regex educationPattern("");
	regex contactPattern("<span\\sclass=\"label\">(.*)</span>(.*)</p >");
	regex typePattern("");
	//regex jobInforPattern(R);
	regex regzhiwei("<div class=\"tBorderTop_box\">[\\s\\S]*?<div class=\"mt10\">");
	regex componyInforPattern("<div class=\"tmsg inbox\">[\\s\\S]*?</div>");
	//��ʼ��ȡ��������ʽ
	regex numberStartPattern("<div\\sclass=\"tHeader\\stHjob\">");
	regex companyStartPattern("<div\\sclass=\"tmsg\\sinbox\">");

	//�����ַ����Ŀ�ʼ���β
	string::const_iterator start = html.begin();
	string::const_iterator end = html.end();
	//�ҵ���ʼ������λ��
	while (!regex_search(start, end, result, numberStartPattern))
		start = result[0].second;
	//��ʼ������Ϣ���岿��
	//����СҪ��
	int i = 1;
	//�滻�ո񼰲���Ҫ���ַ�������ʽ
	regex pattern1("([^nbsp&;|])");
	regex replaceShort("[&nbsp;|]");
	regex replaceJob("[<div class=\"tBorderTop_bxm\">/a-z ]");
	regex replaceCompony("[a-z<>A-Z/=\". &;]");
	regex replaceSpace("[/ ^\\s + | \\s + $ / g]");
	while (start != end)
	{
		if (regex_search(start, end, result, strPattern))
		{
			string str = result[1];
			string s = regex_replace(str, replaceShort, "");
			cout << "��飺" << s << endl;
		}

		if (regex_search(start, end, result, regzhiwei))
		{
			string str2 = regex_replace(result.str(), replaceJob, "");

			cout << "������Ϣ��" << regex_replace(str2, replaceSpace, "") << endl;
		}
		if (regex_search(start, end, result, contactPattern))
			cout << "��ϵ��ʽ:" << result[2] << endl;

		if (regex_search(start, end, result, componyInforPattern))
		{
			string str = regex_replace(result.str(), replaceCompony, "");
			cout << "��˾��Ϣ��" << regex_replace(str, replaceSpace, "") << endl;
		}

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

