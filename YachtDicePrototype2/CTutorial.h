#pragma once
#include "afxdialogex.h"
#include "TUTORIAL1.h"
#include "TUTORIAL2.h"

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
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	TUTORIAL1* m_tutorial1;
	TUTORIAL2* m_tutorial2;
	void AllocForm1();
	void AllocForm2();

	CImage back;
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
};
