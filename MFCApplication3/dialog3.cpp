// dialog3.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "dialog3.h"
#include "afxdialogex.h"
#include"Crawler.h"

// dialog3 对话框

IMPLEMENT_DYNAMIC(dialog3, CDialogEx)
extern info inf;
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
	DDX_Control(pDX, IDC_EDIT1, jobName);
	DDX_Control(pDX, IDC_EDIT2, urlSource);
	DDX_Control(pDX, IDC_EDIT3, company);
	DDX_Control(pDX, IDC_EDIT7, salary);
	DDX_Control(pDX, IDC_EDIT10, contact);
	DDX_Control(pDX, IDC_EDIT13, jobInformation);
	DDX_Control(pDX, IDC_EDIT14, companyInformation);
	DDX_Control(pDX, IDC_EDIT4, Info1);
}


BEGIN_MESSAGE_MAP(dialog3, CDialogEx)
	ON_BN_CLICKED(IDOK, &dialog3::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT4, &dialog3::OnEnChangeEdit4)
END_MESSAGE_MAP()


// dialog3 消息处理程序


void dialog3::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void dialog3::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


BOOL dialog3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	jobName.SetWindowTextA(inf.name.c_str());
	urlSource.SetWindowTextA(inf.html.c_str());
	company.SetWindowTextA(inf.company.c_str());
	//MessageBox(inf.Info.c_str());
	Info1.SetWindowTextA(inf.Info.c_str());
	salary.SetWindowTextA(inf.salary.c_str());
	contact.SetWindowTextA(inf.contact.c_str());
	jobInformation.SetWindowTextA(inf.jobInformation.c_str());
	companyInformation.SetWindowTextA(inf.companyInformation.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
