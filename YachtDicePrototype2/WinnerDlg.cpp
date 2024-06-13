// WinnerDlg.cpp : implementation file
//

#include "pch.h"
#include "YachtDicePrototype2.h"
#include "afxdialogex.h"
#include "WinnerDlg.h"


// WinnerDlg dialog

IMPLEMENT_DYNAMIC(WinnerDlg, CDialogEx)

WinnerDlg::WinnerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WinnerDlg, pParent)
{
    m_textColor = RGB(255, 255, 255); // White color for text
    m_brush.CreateStockObject(NULL_BRUSH); // Transparent background brush
}

WinnerDlg::~WinnerDlg()
{
}

void WinnerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_WINNER, m_winner_name);
    DDX_Control(pDX, IDC_STATIC_LOSER, m_loser_name);
    DDX_Control(pDX, IDC_WINNER_SCORE, m_winner_score);
    DDX_Control(pDX, IDC_LOSER_SCORE, m_loser_score);
    DDX_Control(pDX, IDOK, m_okButton);
}


BEGIN_MESSAGE_MAP(WinnerDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDOK, &WinnerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// WinnerDlg message handlers

void WinnerDlg::SetData(int cpu, int player, CString name)
{
	m_cpuScore = cpu;
	m_playerScore = player;
    m_name = name;
}

BOOL WinnerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
    LOGFONT lrf;
    memset(&lrf, 0, sizeof(LOGFONT));
    lrf.lfHeight = 100; // Font height
    lrf.lfWeight = FW_SEMIBOLD; // Bold weight
    lrf.lfUnderline = TRUE; // Underline
    _tcscpy_s(lrf.lfFaceName, _T("Segoe Script")); // Font face name

    m_nameFont.CreateFontIndirect(&lrf);

    memset(&lrf, 0, sizeof(LOGFONT));
    lrf.lfHeight = 80; // Font height
    //lrf.lfWeight = FW_SEMIBOLD; // Bold weight
    _tcscpy_s(lrf.lfFaceName, _T("Segoe Script")); // Font face name

    m_scoreFont.CreateFontIndirect(&lrf);


    m_winner_name.SetFont(&m_nameFont);
    m_loser_name.SetFont(&m_nameFont);
    m_winner_score.SetFont(&m_scoreFont);
    m_loser_score.SetFont(&m_scoreFont);

    CString winner_score, loser_score;

    if (m_cpuScore > m_playerScore) // CPU Win
    {
        back.Load(_T("WIN_BACKGROUND.png"));

        m_winner_name.SetWindowTextW(L"CPU");
        m_loser_name.SetWindowTextW(m_name);

        
        winner_score.Format(_T("%d points"), m_cpuScore);
        loser_score.Format(_T("%d points"), m_playerScore);

        m_winner_score.SetWindowTextW(winner_score);
        m_loser_score.SetWindowTextW(loser_score);
    }
    else if (m_playerScore >= m_cpuScore) // Player Win
    {
        if (m_playerScore == m_cpuScore)
        {
            back.Load(_T("DRAW_BACKGROUND.png"));
        }
        else
        {
            back.Load(_T("WIN_BACKGROUND.png"));
        }

        m_winner_name.SetWindowTextW(m_name);
        m_loser_name.SetWindowTextW(L"CPU");


        winner_score.Format(_T("%d points"), m_playerScore);
        loser_score.Format(_T("%d points"), m_cpuScore);

        m_winner_score.SetWindowTextW(winner_score);
        m_loser_score.SetWindowTextW(loser_score);
    }

    // OK 버튼에 비트맵 이미지 설정
    m_okButton.LoadBitmaps(IDB_BITMAP5); // IDB_OK_BITMAP은 리소스에 추가된 비트맵의 리소스 ID입니다.
    m_okButton.SizeToContent();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void WinnerDlg::OnPaint()
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


HBRUSH WinnerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  Change any attributes of the DC here
    if (nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetTextColor(m_textColor); // Set the text color
        pDC->SetBkMode(TRANSPARENT); // Set the background mode to transparent
        hbr = (HBRUSH)m_brush; // Return the transparent brush
    }

    // TODO:  Return a different brush if the default is not desired
    return hbr;
}


void WinnerDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    CDialogEx::OnOK();

    // 부모 다이얼로그 닫기
    if (GetParent() != nullptr)
    {
        GetParent()->SendMessage(WM_CLOSE);
    }
}
