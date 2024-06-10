// CTutorial.cpp : implementation file
//

#include "pch.h"
#include "YachtDicePrototype2.h"
#include "afxdialogex.h"
#include "CTutorial.h"


// CTutorial dialog

IMPLEMENT_DYNAMIC(CTutorial, CDialogEx)

CTutorial::CTutorial(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TUTORIAL_DIALOG, pParent)
{

}

CTutorial::~CTutorial()
{
}

void CTutorial::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTutorial, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTutorial message handlers


BOOL CTutorial::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	back.Load(_T("BACKGROUND.png"));//이미지 로드

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTutorial::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	GetClientRect(&rect);
	//m_picture_control.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	//CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	//dc = m_picture_control.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.

	back.StretchBlt(dc.m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
}
