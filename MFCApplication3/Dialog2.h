#pragma once

#include"dialog3.h"
// Dialog2 对话框

class Dialog2 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog2)

public:
	Dialog2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dialog2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//	HICON m_hIcon1;
	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl m_ctllist1;
	virtual BOOL OnInitDialog();
	CListCtrl m_ctllist1;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CEdit condition;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
