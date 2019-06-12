﻿#include"pch.h"
#include<Windows.h>
#include <iostream>
#include "Wininet.h"
#pragma comment(lib,"Wininet.lib")
using namespace std;

//模拟浏览器发送HTTP请求函数
string HttpRequest(char * lpHostName, short sPort, char * lpUrl, char * lpMethod, char * lpPostData, int nPostDataLen)
{
	HINTERNET hInternet, hConnect, hRequest;
	BOOL bRet;
	string strResponse;
	hInternet = NULL;
	hConnect = NULL;
	hRequest = NULL;

	hInternet = (HINSTANCE)InternetOpen("User-Agent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hInternet)
		goto Ret0;

	hConnect = (HINSTANCE)InternetConnect(hInternet, lpHostName, sPort, NULL, "HTTP/1.1", INTERNET_SERVICE_HTTP, 0, 0);
	if (!hConnect)
		goto Ret0;

	hRequest = (HINSTANCE)HttpOpenRequest(hConnect, lpMethod, lpUrl, "HTTP/1.1", NULL, NULL, INTERNET_FLAG_RELOAD, 0);
	if (!hRequest)
		goto Ret0;

	//bRet = HttpAddRequestHeaders(hRequest,"Content-Type: application/x-www-form-urlencoded",Len(FORMHEADERS),HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
	//if(!bRet)
	//goto Ret0;

	bRet = HttpSendRequest(hRequest, NULL, 0, lpPostData, nPostDataLen);
	while (TRUE)
	{
		char cReadBuffer[4096];
		unsigned long lNumberOfBytesRead;
		bRet = InternetReadFile(hRequest, cReadBuffer, sizeof(cReadBuffer) - 1, &lNumberOfBytesRead);
		if (!bRet || !lNumberOfBytesRead)
			break;
		cReadBuffer[lNumberOfBytesRead] = 0;
		strResponse = strResponse + cReadBuffer;
	}

Ret0:
	if (hRequest)
		InternetCloseHandle(hRequest);
	if (hConnect)
		InternetCloseHandle(hConnect);
	if (hInternet)
		InternetCloseHandle(hInternet);

	return strResponse;
}
/*
int main()
{
	//CString strResponse = HttpRequest("translate.google.com",80,"/translate_t?langpair=en|zh-CN","POST","hl=zh-CN&ie=UTF-8&text=this is me&langpair=en|zh-CN",strlen("hl=zh-CN&ie=UTF-8&text=this is me&langpair=en|zh-CN"));
	
	char a[] = "search.51job.com";
	char b[] = "/";
	char c[] = "GET";
	string strResponse = HttpRequest(a, 80, b, c, NULL, 0);

	cout << strResponse.c_str();

	FILE * fp;
	errno_t t=fopen_s(&fp, "1.txt", "w");
	fwrite(strResponse.c_str(), 1, strResponse.length(), fp);
	fclose(fp);
	return 0;
}*/