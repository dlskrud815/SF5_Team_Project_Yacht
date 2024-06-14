#pragma once



// TUTORIAL2 form view

class TUTORIAL2 : public CFormView
{
	DECLARE_DYNCREATE(TUTORIAL2)

public:
	TUTORIAL2();           
	virtual ~TUTORIAL2();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TUTORIAL2 };
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
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	CImage back;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedPreviousBtn1();
};


