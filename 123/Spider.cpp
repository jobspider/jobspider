#include"pch.h"
#include"Spider.h"
#include<string>
#include<codecvt>
#pragma comment(lib,"ws2_32.lib")
CHttp::CHttp() {
	m_socket = NULL;
}
CHttp::~CHttp() {
	WSACleanup();
}


bool CHttp::AnalyseUrl(string url) {
	int k = 8;
	if (string::npos == url.find("https://")) {
		k = 7;
		if (string::npos == url.find("http://")) {
			return false;
		}
	}
	//主机名
	int i = url.find('/',k);
	m_host=url.substr(k, i-k);
	m_object = url.substr(i);
	cout <<"主机名:"<< m_host<<endl;
	cout <<"资源名:"<<m_object << endl;
	return true;
}
bool CHttp::Init() {
	WSADATA wd;
	if (0!=WSAStartup(MAKEWORD(2, 2), &wd)) 
		return false;
	if(LOBYTE(wd.wVersion)!=2||LOBYTE(wd.wVersion)!=2)
	return false; 

	return true;
}


bool CHttp::Connect() {

	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_socket == INVALID_SOCKET)
		return false;
	hostent *p=gethostbyname(m_host.c_str());

	if (p == NULL)
		return false;
	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port =htons(80);
	memcpy(&sa.sin_addr, p->h_addr, 4);

	if (SOCKET_ERROR == connect(m_socket, (sockaddr*)&sa, sizeof(sockaddr))) 
		return false;
	

	return true;
}

string CHttp::getHtml()
{
	string sInfo;
	sInfo = "GET "+m_object + " HTTP/1.1\r\n";
	sInfo += "Host: " + m_host + "\r\n";
	sInfo +="User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36\r\n";
	sInfo += "Connection: Close\r\n\r\n";
	cout << "发送请求:"<<endl;
	cout << sInfo<<endl;
	if (SOCKET_ERROR == send(m_socket, sInfo.c_str(), sInfo.length(), 0))
		return false;

	string recieve;//接收网页源码
	char Buffer[1024];
	memset(Buffer, 0, 1024);
	int nRecv = 0;
	while ((nRecv=recv(m_socket, Buffer, 1024, 0))>0) {
		recieve += Buffer;
	}

	return recieve;  
}

bool StartCatch() {

	return 0;

}



wstring UTF8ToUnicode(const string & str)
{
	wstring ret;
	try {
		wstring_convert<codecvt_utf8<wchar_t> > wcv;
		ret = wcv.from_bytes(str);
	}
	catch (const exception & e) {
		cerr << e.what() << endl;
	}
	return ret;
}


string Utf8ToGbk(const char *src_str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

int main() {

	string startURL;
	cin >> startURL;
	CHttp c;
	if (c.AnalyseUrl(startURL)) 
		cout << "解析成功" << endl;
	if (c.Init()) 
		cout << "初始化成功" << endl;	
	if (c.Connect())
		cout << "连接成功" << endl;
	string get = Utf8ToGbk(c.getHtml().c_str());
	cout << get;
	FILE * fp;
	errno_t t = fopen_s(&fp, "1.txt", "w");
	fwrite(get.c_str(), 1, get.length(), fp);
	fclose(fp);
	
	
}