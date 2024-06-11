
// YachtDicePrototype2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "YachtDicePrototype2.h"
#include "YachtDicePrototype2Dlg.h"

#include "CNameSetting.h"
#include "CTutorial.h"
#include "YachtDice1Dlg.h"

#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CYachtDicePrototype2Dlg dialog



CYachtDicePrototype2Dlg::CYachtDicePrototype2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_YACHTDICEPROTOTYPE2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYachtDicePrototype2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, m_q_bmp);
	DDX_Control(pDX, IDC_BUTTON1, m_start_bmp);
}

BEGIN_MESSAGE_MAP(CYachtDicePrototype2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CYachtDicePrototype2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CYachtDicePrototype2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CYachtDicePrototype2Dlg message handlers
// 대체로 가장 먼저 실행되는 코드, 초기 세팅
// 대체로 가장 먼저 실행되는 코드, 초기 세팅
// 대체로 가장 먼저 실행되는 코드, 초기 세팅
// 대체로 가장 먼저 실행되는 코드, 초기 세팅
// 대체로 가장 먼저 실행되는 코드, 초기 세팅

BOOL CYachtDicePrototype2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	main.Load(_T("main_noBT.bmp"));//이미지 로드

	m_start_bmp.LoadBitmaps(IDB_BITMAP4, NULL, NULL, NULL); // 첫 번째 인자에는 추가한 비트맵 ID명
	m_start_bmp.SizeToContent(); // 이미지 크기에 버튼 크기를 맞춰주는 작업

	m_q_bmp.LoadBitmaps(IDB_BITMAP3, NULL, NULL, NULL); // 첫 번째 인자에는 추가한 비트맵 ID명
	m_q_bmp.SizeToContent(); // 이미지 크기에 버튼 크기를 맞춰주는 작업

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CYachtDicePrototype2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CYachtDicePrototype2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{CPaintDC dc(this);

		CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
		GetClientRect(&rect);
		//m_picture_control.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
		//CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
		//dc = m_picture_control.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.

		main.StretchBlt(dc.m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
		//ReleaseDC(dc);//DC 해제

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CYachtDicePrototype2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CYachtDicePrototype2Dlg::OnBnClickedButton3()
{
	CTutorial dlgT;
	dlgT.DoModal();
	// TODO: Add your control notification handler code here
}


void CYachtDicePrototype2Dlg::OnBnClickedButton1()
{
	CNameSetting dlgN1;
	dlgN1.DoModal();
	// TODO: Add your control notification handler code here
}