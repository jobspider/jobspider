﻿#pragma once


// dialog3 对话框

class dialog3 : public CDialogEx
{
	DECLARE_DYNAMIC(dialog3)

public:
	dialog3(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
