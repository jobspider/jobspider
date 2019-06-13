
// MFCApplication3Dlg.cpp: 实现文件

#include"stdafx.h"
#include"Crawler.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "Dialog1.h"
#include "Dialog2.h"
#include "dialog3.h"
#include<regex>
#include<time.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
HANDLE t1;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctllist1;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ctllist1);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 对话框



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctllist);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication3Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication3Dlg::OnBnClickedButton2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCApplication3Dlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication3Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	DWORD dwStyle = m_ctllist.GetExtendedStyle();                    //添加列表框的网格线！！！

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_ctllist.SetExtendedStyle(dwStyle);


	CString s1, s2, s3;
	s1 = "State";
	s2 = "Time";
	s3 = "Operation";
	m_ctllist.InsertColumn(0, s1.GetString(), LVCFMT_LEFT, 100);              //添加列标题！！！！！
	m_ctllist.InsertColumn(1, s2.GetString(), LVCFMT_LEFT, 100);
	m_ctllist.InsertColumn(2, s3.GetString(), LVCFMT_LEFT, 500);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

Job *jobs = new Job[100];
CWinThread *pThread=NULL;//线程定义

void CMFCApplication3Dlg::OnBnClickedButton0() {
	pThread = AfxBeginThread((AFX_THREADPROC)Crawl,this);
}

UINT CMFCApplication3Dlg::Crawl(LPVOID pParam) {
	CMFCApplication3Dlg *pDlg = (CMFCApplication3Dlg*)pParam;
	//HWND hwnd = (HWND)pParam;
	//string t = getHtml("https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,1.html", "1");
	int n = 1;//页码
	string url = "https://search.51job.com/list/010000,000000,0000,00,9,99,%2B,2,";
	int i = 0;//工作编号
	while (n < 2) {//爬取前30页
		char page[3];
		sprintf_s(page, "%d", n);
		url = url + page + ".html";
		//cout << "正在爬取:" + url << endl;
		string t = getHtml(url, page);
		//储存结果
		smatch result;
		//定义正则表达式
		regex jobPattern("<a\\starget=\"_blank\"\\stitle=\"(.*)\"\\shref=\"(.*)\"\\sonmousedown=\"\"");
		regex componyPattern("<span\\sclass=\"t2\"><a\\starget=\"_blank\"\\stitle=\"(.*)\"\\shref");
		regex locationPattern("<span\\sclass=\"t3\">(.*)</span>");
		regex salaryPattern("<span\\sclass=\"t4\">(.*)</span>");
		regex dataPattern("<span\\sclass=\"t5\">(.*)</span>");
		regex startPattern("<div\\sclass=\"el\">");
		//定义解析开始与结束的部分
		string::const_iterator start = t.begin();
		string::const_iterator end = t.end();
		string temp;
		//找到职位列表的起始位置
		while (!regex_search(start, end, result, startPattern))
			start = result[0].second;
		start = result[0].second;
		while (!regex_search(start, end, result, startPattern))
			start = result[0].second;
		//定义一个结构体数组存储职位信息
		//开始解析
		while (start != end) {
			//匹配职位名
			if (regex_search(start, end, result, jobPattern))
			{
				//cout << "职位：" << result[1] << " " << result[2] << endl;
				jobs[i].name = result[1];
				jobs[i].html = result[2];
			}
			//匹配公司名
			if (regex_search(start, end, result, componyPattern))
			{
				//cout << "公司：" << result[1] << " " << result[2] << endl;
				jobs[i].company = result[1];
			}
			//匹配公司所在地区
			if (regex_search(start, end, result, locationPattern))
			{

				//cout << "公司所在地：" << result[1] << endl;
				jobs[i].place = result[1];
			}
			//匹配薪水
			if (regex_search(start, end, result, salaryPattern))
			{

				//cout << "薪资：" << result[1] << endl;
				jobs[i].salary = result[1];
			}
			//匹配发布日期
			if (regex_search(start, end, result, dataPattern))
			{
				//cout << "发布日期：" << result[1] << endl;
				jobs[i].time = result[1];
			}
			//显示工作名称
			CString number;
			number.Format("%d", i + 1);
			CString s = "第" + number + "项工作";
			pDlg->m_ctllist.InsertItem(i, s.GetString());
			//显示时间
			char time[10];
			SYSTEMTIME st;
			GetLocalTime(&st);
			sprintf_s(time, "%d:%d:%d",
				st.wHour,
				st.wMinute,
				st.wSecond);
			pDlg->m_ctllist.SetItemText(i, 1, time);
			pDlg->m_ctllist.SetItemText(i, 2, "扒取成功");
			::UpdateWindow(pDlg->m_hWnd);
			//cout << endl;
			i++;
			Sleep(500);
			start = result[0].second;
		}
		n++;
	}
	return 0;
}





void CMFCApplication3Dlg::OnBnClickedCheck1() {

}

void CMFCApplication3Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Dialog2 dlg;
	pThread->SuspendThread();
	dlg.DoModal();
	
}



void CMFCApplication3Dlg::OnBnClickedButton6()
{
	pThread->ResumeThread();
	// TODO: 在此添加控件通知处理程序代码
}
