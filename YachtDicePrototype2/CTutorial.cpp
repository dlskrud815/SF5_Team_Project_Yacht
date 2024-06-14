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
	m_hIcon = AfxGetApp()->LoadIcon(IDI_DICE_ICON);
}

CTutorial::~CTutorial()
{
}

void CTutorial::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTutorial, CDialogEx)
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTutorial message handlers


BOOL CTutorial::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	AllocForm1();
	AllocForm2();
	ShowForm1();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


HCURSOR CTutorial::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return static_cast<HCURSOR>(m_hIcon);
}

void CTutorial::AllocForm1()
{
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	CRect rectOfPanelArea;

	GetDlgItem(IDC_TUTORIAL_DLG1)->GetWindowRect(&rectOfPanelArea);
	ScreenToClient(&rectOfPanelArea);
	m_tutorial1 = new TUTORIAL1();
	m_tutorial1->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_TUTORIAL1, &context);
	m_tutorial1->OnInitialUpdate();
	//m_tutorial1->ShowWindow(SW_SHOW);
	//GetDlgItem(IDC_TUTORIAL_DLG1)->DestroyWindow();
}


void CTutorial::AllocForm2()
{
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	CRect rectOfPanelArea;

	GetDlgItem(IDC_TUTORIAL_DLG1)->GetWindowRect(&rectOfPanelArea);
	ScreenToClient(&rectOfPanelArea);
	m_tutorial2 = new TUTORIAL2();
	m_tutorial2->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_TUTORIAL2, &context);
	m_tutorial2->OnInitialUpdate();
	//m_tutorial2->ShowWindow(SW_SHOW);
	//GetDlgItem(IDC_TUTORIAL_DLG1)->DestroyWindow();
}

void CTutorial::HideForm1()
{
	m_tutorial1->ShowWindow(SW_HIDE);
}

void CTutorial::HideForm2()
{
	m_tutorial2->ShowWindow(SW_HIDE);
}

void CTutorial::ShowForm1()
{
	m_tutorial1->ShowWindow(SW_SHOW);
}

void CTutorial::ShowForm2()
{
	m_tutorial2->ShowWindow(SW_SHOW);
}