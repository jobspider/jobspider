// Dialog2.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "Dialog2.h"
#include "afxdialogex.h"
#include "dialog3.h"
#include"Crawler.h"
#include<regex>
// Dialog2 对话框

IMPLEMENT_DYNAMIC(Dialog2, CDialogEx)
extern Job *jobs;
info inf;
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
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Dialog2::OnLvnItemchangedList1)
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
	POSITION pos = m_ctllist1.GetFirstSelectedItemPosition();
	if(pos == NULL)
	{
		MessageBox("请至少选择一项", "", MB_ICONEXCLAMATION);
		return;
	}
	int nId = (int)m_ctllist1.GetNextSelectedItem(pos);
	string name = m_ctllist1.GetItemText(nId, 0);
	dialog3 dlg;
	int  i = 0;
	Job job;
	while (jobs[i].name != "") {
		if (!string::npos==jobs[i].name.find(name)) {
			job = jobs[i];
			break;
		}
		i++;
	}
	string s = getHtmlItem(job.html);
	//储存解析结果
	smatch result;
	//定义正则表达式
	regex strPattern("<p\\sclass=\"msg\\sltype\"\\stitle=\"(.*)\">");
	regex numberPattern("");
	regex experiencePattern("");
	regex educationPattern("");
	regex contactPattern("<span\\sclass=\"label\">(.*)</span>(.*)</p >");
	regex typePattern("");
	//regex jobInforPattern(R);
	regex regzhiwei("<div class=\"tBorderTop_box\">[\\s\\S]*?<div class=\"mt10\">");
	regex componyInforPattern("<div class=\"tmsg inbox\">[\\s\\S]*?</div>");
	//开始爬取的正则表达式
	regex numberStartPattern("<div\\sclass=\"tHeader\\stHjob\">");
	regex companyStartPattern("<div\\sclass=\"tmsg\\sinbox\">");

	//定义字符串的开始与结尾
	string::const_iterator start = s.begin();
	string::const_iterator end = s.end();
	//找到开始解析的位置
	while (!regex_search(start, end, result, numberStartPattern))
		start = result[0].second;
	//开始解析信息主体部分
	//解析小要求
	i = 1;
	//替换空格及不必要的字符正则表达式
	regex pattern1("([^nbsp&;|])");
	regex replaceShort("[&nbsp;|]");
	regex replaceJob("[<div class=\"tBorderTop_bxm\">/a-z ]");
	regex replaceCompony("[a-z<>A-Z/=\". &;]");
	regex replaceSpace("[/ ^\\s + | \\s + $ / g]");

	if (regex_search(start, end, result, strPattern))
	{
		string str = result[1];
		string s = regex_replace(str, replaceShort, "");
		//cout << "简介：" << s << endl;
		//dlg.Info.SetWindowTextA(s.c_str());
		inf.Info = s;
	}

		if (regex_search(start, end, result, regzhiwei))
		{
			string str2 = regex_replace(result.str(), replaceJob, "");
			//cout << "工作信息：" << regex_replace(str2, replaceSpace, "") << endl;
			//dlg.jobInformation.SetWindowTextA(a.c_str());
			string a = regex_replace(str2, replaceSpace, "");
			inf.jobInformation = a;
		}
		if (regex_search(start, end, result, contactPattern)) {
			//cout << "联系方式:" << result[2] << endl;
			string a = result[2];
			//dlg.contact.SetWindowTextA(a.c_str());
			inf.contact = a;
		}
		if (regex_search(start, end, result, componyInforPattern))
		{
			string str = regex_replace(result.str(), replaceCompony, "");
			//cout << "公司信息：" << regex_replace(str, replaceSpace, "") << endl;
			string a = regex_replace(str, replaceSpace, "");
			//dlg.companyInformation.SetWindowTextA(a.c_str());
			inf.companyInformation = a;
		}
		inf.company = job.company;
		inf.salary = job.salary;
		inf.html = job.html;
		inf.name = job.name;
		dlg.DoModal();
		/*dlg.company.SetWindowTextA(job.company.c_str());
		dlg.salary.SetWindowTextA(job.salary.c_str());
		dlg.urlSource.SetWindowTextA(job.html.c_str());
		*/
		// TODO: 在此添加控件通知处理程序代码
	}






	void Dialog2::OnBnClickedButton1()
	{
		CString s;
		int i = 0;
		int k = 0;
		condition.GetWindowText(s);
		if (s == "") {
			m_ctllist1.DeleteAllItems();
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
					CString name = jobs[i].name.c_str();
					m_ctllist1.InsertItem(k, name.GetString());
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




	void Dialog2::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		// TODO: 在此添加控件通知处理程序代码
		*pResult = 0;
	}
