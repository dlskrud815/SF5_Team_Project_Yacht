#pragma once
#include "afxdialogex.h"


// WinnerDlg dialog

class WinnerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WinnerDlg)

public:
	WinnerDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~WinnerDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WinnerDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	

protected:
	CBrush m_brush;
	COLORREF m_textColor;
	CFont m_nameFont, m_scoreFont;


	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	int m_cpuScore, m_playerScore;
	CString m_name;

	CStatic m_winner_name;
	CStatic m_loser_name;
	CStatic m_winner_score;
	CStatic m_loser_score;

	CImage back;

public:
	void SetData(int cpu, int player, CString name);
	afx_msg void OnBnClickedOk();
};
