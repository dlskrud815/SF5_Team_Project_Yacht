#pragma once
#include "afxdialogex.h"


// CYachtDice1Dlg dialog

class CYachtDice1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYachtDice1Dlg)

public:
	bool picture = true;
	CYachtDice1Dlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CYachtDice1Dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_YACHTDICE1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
public:
	CImage back;

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedRoll();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT OnUpdateDice(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	CButton m_btnPlayers[12]; // 모든 버튼을 담을 배열
	CBitmapButton* m_btnRoll;

	CStatic m_dicePics[5]; // Picture Control 배열
	CBitmap m_diceBitmaps[6]; // Bitmap 이미지 배열

	void LoadDiceBitmaps();
	void ShowDiceImage(int diceIndex, int imageIndex);
	void ArrangeDicePics(); // Picture Control 정렬 함수

	CString m_strData;

public:
	CBitmapButton m_bitmapBtn;

	afx_msg void OnPaint();
	afx_msg void OnBnClickedTutorialBtn();

	void SetData(const CString& str);
	CFont m_font;


	CBitmapButton m_dice1;
	CBitmapButton m_dice2;
	CBitmapButton m_dice3;
	CBitmapButton m_dice4;
	CBitmapButton m_dice5;

	CButton m_showScore;
	CButton m_score1;
	CButton m_score2;
	CButton m_score3;
	CButton m_score4;
	CButton m_score5;

	afx_msg void OnBnClickedDiceButton2();
	afx_msg void OnBnClickedDiceButton3();
	afx_msg void OnBnClickedDiceButton4();
	afx_msg void OnBnClickedDiceButton5();
	afx_msg void OnBnClickedDiceButton6();
	afx_msg void OnBnClickedDiceButton7();
	afx_msg void OnBnClickedDiceButton8();
	afx_msg void OnBnClickedDiceButton9();
	afx_msg void OnBnClickedDiceButton10();
	afx_msg void OnBnClickedDiceButton11();
	afx_msg void OnBnClickedChoosecategory();
};
