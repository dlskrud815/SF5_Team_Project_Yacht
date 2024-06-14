#pragma once



// TUTORIAL1 form view

class TUTORIAL1 : public CFormView
{
	DECLARE_DYNCREATE(TUTORIAL1)

public:
	TUTORIAL1();          
	virtual ~TUTORIAL1();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TUTORIAL1 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	CImage back;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedNextBtn1();
	CBitmapButton m_next_btn;
};


