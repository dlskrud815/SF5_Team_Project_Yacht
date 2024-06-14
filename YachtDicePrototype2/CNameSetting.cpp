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
	m_hIcon = AfxGetApp()->LoadIcon(IDI_DICE_ICON);
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
	ON_WM_CTLCOLOR()
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

	CFont font;
	font.CreateFont(
		50,                         // 폰트 높이
		0,                          // 폰트 너비
		0,                          // 텍스트 각도
		0,                          // 기준선에서의 각도
		FW_NORMAL,                  // 폰트 굵기
		FALSE,                      // 기울임
		FALSE,                      // 밑줄
		0,                          // 취소선
		DEFAULT_CHARSET,            // 문자 집합
		OUT_DEFAULT_PRECIS,         // 출력 정밀도
		CLIP_DEFAULT_PRECIS,        // 클리핑 정밀도
		DEFAULT_QUALITY,            // 출력 품질
		DEFAULT_PITCH | FF_SWISS,   // 글꼴 이름
		_T("Segoe Script")                 // 글꼴
	);
	m_editBox.SetFont(&font);

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

HBRUSH CNameSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// IDC_EDIT_NAME 컨트롤의 핸들 확인
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_NAME)
	{
		pDC->SetBkColor(RGB(104, 63, 45));  // 에디트 박스 배경색 설정
		pDC->SetTextColor(RGB(255, 255, 255));  // 에디트 박스 텍스트 색상 설정

		COLORREF rgbColor = RGB(104, 63, 45);
		hbr = CreateSolidBrush(rgbColor);
	}

	return hbr;
}

HCURSOR CNameSetting::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return static_cast<HCURSOR>(m_hIcon);
}