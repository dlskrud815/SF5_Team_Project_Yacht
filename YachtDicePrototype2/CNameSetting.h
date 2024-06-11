#pragma once
#include "afxdialogex.h"


// CNameSetting dialog

class CNameSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CNameSetting)

public:
	CNameSetting(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNameSetting();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CImage backImage;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	CString m_strInput; //닉네임
	afx_msg void OnBnClickedOk();
};
