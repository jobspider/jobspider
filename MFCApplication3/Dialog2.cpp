// Dialog2.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "Dialog2.h"
#include "afxdialogex.h"
#include "dialog3.h"
#include"Crawler.h"

// Dialog2 对话框

IMPLEMENT_DYNAMIC(Dialog2, CDialogEx)
extern Job *jobs;
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
	DDX_Control(pDX, IDC_EDIT1, condition);
}

BEGIN_MESSAGE_MAP(Dialog2, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog2::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &Dialog2::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Dialog2::OnBnClickedButton1)
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
	CString s1, s2, s3, s4, s5;
	s1 = "职位名";
	s2 = "公司名";
	s3 = "工作地点";
	s4 = "薪资";
	s5 = "发布时间";
	m_ctllist1.InsertColumn(0, s1.GetString(), LVCFMT_LEFT, 300);              //添加列标题！！！！！
	m_ctllist1.InsertColumn(1, s2.GetString(), LVCFMT_LEFT, 300);
	m_ctllist1.InsertColumn(2, s3.GetString(), LVCFMT_LEFT, 300);
	m_ctllist1.InsertColumn(3, s4.GetString(), LVCFMT_LEFT, 100);
	m_ctllist1.InsertColumn(4, s5.GetString(), LVCFMT_LEFT, 100);
	int i = 0;
	CString s;
	while(jobs[i].name!=""){
		s = jobs[i].name.c_str();
		m_ctllist1.InsertItem(i, s.GetString());
		m_ctllist1.SetItemText(i, 1,jobs[i].company.c_str());	
		m_ctllist1.SetItemText(i, 2, jobs[i].place.c_str());
		m_ctllist1.SetItemText(i, 3, jobs[i].salary.c_str());
		m_ctllist1.SetItemText(i, 4, jobs[i].time.c_str());
		i++;
	}
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


void Dialog2::OnBnClickedButton1()
{
	CString s;
	int i = 0;
	int k = 0;
	condition.GetWindowText(s);
	if (s == "") {
		while (jobs[i].name != "") {
			s = jobs[i].name.c_str();
			m_ctllist1.InsertItem(i, s.GetString());
			m_ctllist1.SetItemText(i, 1, jobs[i].company.c_str());
			m_ctllist1.SetItemText(i, 2, jobs[i].place.c_str());
			m_ctllist1.SetItemText(i, 3, jobs[i].salary.c_str());
			m_ctllist1.SetItemText(i, 4, jobs[i].time.c_str());
			i++;
		}
	}
	else {
		m_ctllist1.DeleteAllItems();
		while (jobs[i].name != "") {
			if (string::npos != jobs[i].name.find(s) || string::npos != jobs[i].company.find(s) || string::npos != jobs[i].place.find(s) || string::npos != jobs[i].salary.find(s) || string::npos != jobs[i].time.find(s)) {
				s = jobs[i].name.c_str();
				m_ctllist1.InsertItem(k, s.GetString());
				m_ctllist1.SetItemText(k, 1, jobs[i].company.c_str());
				m_ctllist1.SetItemText(k, 2, jobs[i].place.c_str());
				m_ctllist1.SetItemText(k, 3, jobs[i].salary.c_str());
				m_ctllist1.SetItemText(k, 4, jobs[i].time.c_str());
				k++;
			}
			i++;
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}


