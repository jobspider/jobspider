// dialog3.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "dialog3.h"
#include "afxdialogex.h"


// dialog3 对话框

IMPLEMENT_DYNAMIC(dialog3, CDialogEx)

dialog3::dialog3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

dialog3::~dialog3()
{
}

void dialog3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dialog3, CDialogEx)
	ON_BN_CLICKED(IDOK, &dialog3::OnBnClickedOk)
END_MESSAGE_MAP()


// dialog3 消息处理程序


void dialog3::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
