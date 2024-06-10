// CNameSetting.cpp : implementation file
//

#include "pch.h"
#include "YachtDicePrototype2.h"
#include "afxdialogex.h"
#include "CNameSetting.h"


// CNameSetting dialog

IMPLEMENT_DYNAMIC(CNameSetting, CDialogEx)

CNameSetting::CNameSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NAME_DIALOG, pParent)
{

}

CNameSetting::~CNameSetting()
{
}

void CNameSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNameSetting, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CNameSetting message handlers


BOOL CNameSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	backImage.Load(_T("BACKGROUND.png"));


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CNameSetting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	GetClientRect(&rect);

	backImage.StretchBlt(dc.m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
}
