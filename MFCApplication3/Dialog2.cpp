// Dialog2.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "Dialog2.h"
#include "afxdialogex.h"
#include "dialog3.h"


// Dialog2 对话框

IMPLEMENT_DYNAMIC(Dialog2, CDialogEx)

Dialog2::Dialog2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Dialog2::~Dialog2()
{
}

void Dialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctllist1);
}

BEGIN_MESSAGE_MAP(Dialog2, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog2::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &Dialog2::OnBnClickedButton2)
END_MESSAGE_MAP()


// Dialog2 消息处理程序


BOOL Dialog2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwStyle = m_ctllist1.GetExtendedStyle();                    //添加列表框的网格线！！！

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_ctllist1.SetExtendedStyle(dwStyle);
	CString s1, s2, s3, s4, s5, s6;
	s1 = "SN";
	s2 = "Job Name";
	s3 = "Company";
	s4 = "Work Place";
	s5 = "Salary";
	s6 = "Pubdate";
	m_ctllist1.InsertColumn(0, s1.GetString(), LVCFMT_LEFT, 50);              //添加列标题！！！！！
	m_ctllist1.InsertColumn(1, s2.GetString(), LVCFMT_LEFT, 300);
	m_ctllist1.InsertColumn(2, s3.GetString(), LVCFMT_LEFT, 300);
	m_ctllist1.InsertColumn(3, s4.GetString(), LVCFMT_LEFT, 100);
	m_ctllist1.InsertColumn(4, s5.GetString(), LVCFMT_LEFT, 100);
	m_ctllist1.InsertColumn(5, s6.GetString(), LVCFMT_LEFT, 100);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Dialog2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void Dialog2::OnBnClickedButton2()
{
	dialog3 dlg;
	dlg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
