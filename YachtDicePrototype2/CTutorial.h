#pragma once
#include "afxdialogex.h"


// CTutorial dialog

class CTutorial : public CDialogEx
{
	DECLARE_DYNAMIC(CTutorial)

public:
	CTutorial(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTutorial();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TUTORIAL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CImage back;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
