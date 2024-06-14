// CNameSetting.cpp : implementation file
//

#include "pch.h"
#include "resource.h"
#include "YachtDicePrototype2.h"
#include "afxdialogex.h"
#include "CNameSetting.h"
#include "YachtDice1Dlg.h"

// CNameSetting dialog

IMPLEMENT_DYNAMIC(CNameSetting, CDialogEx)

CNameSetting::CNameSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CNameSetting::~CNameSetting()
{
}

void CNameSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editBox);
	DDX_Control(pDX, IDCANCEL, m_pic_Cancle);
	DDX_Control(pDX, IDOK, m_pic_OK);
}

BEGIN_MESSAGE_MAP(CNameSetting, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CNameSetting::OnBnClickedOk)
	ON_WM_SHOWWINDOW()
	ON_STN_CLICKED(IDC_STATIC_USERNAME, &CNameSetting::OnStnClickedStaticUsername)
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

// CNameSetting message handlers

BOOL CNameSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO:  Add extra initialization here
	backImage.Load(_T("BACKGROUND.png"));

	m_pic_Cancle.LoadBitmaps(IDB_CANCLE);
	m_pic_Cancle.SizeToContent();

	m_pic_OK.LoadBitmaps(IDB_OK);
	m_pic_OK.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CNameSetting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	CRect rect; // 픽쳐 컨트롤의 크기를 저장할 CRect 객체
	GetClientRect(&rect);

	backImage.StretchBlt(dc.m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY); // 이미지를 픽쳐 컨트롤 크기로 조정
}

void CNameSetting::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT_NAME, m_strInput);

	if (m_strInput.IsEmpty())
	{
		AfxMessageBox(_T("닉네임을 입력해주세요."), MB_OK | MB_ICONWARNING);
	}
	else
	{
		CYachtDice1Dlg dlgGame;
		dlgGame.SetData(m_strInput);
		dlgGame.DoModal();

		CDialogEx::OnOK();
	}
}

void CNameSetting::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	// 다이얼로그가 표시될 때 포커스를 설정
	if (bShow)
	{
		PostMessage(WM_NEXTDLGCTL, (WPARAM)m_editBox.GetSafeHwnd(), TRUE);
	}
}

void CNameSetting::OnStnClickedStaticUsername()
{
	// TODO: Add your control notification handler code here
}

HCURSOR CNameSetting::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return static_cast<HCURSOR>(m_hIcon);
}
