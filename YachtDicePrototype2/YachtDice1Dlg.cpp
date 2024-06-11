// YachtDice1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "YachtDicePrototype2.h"
#include "afxdialogex.h"
#include "YachtDice1Dlg.h"
#include "resource.h" 
#include "CTutorial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CYachtDice1Dlg dialog

IMPLEMENT_DYNAMIC(CYachtDice1Dlg, CDialogEx)

CYachtDice1Dlg::CYachtDice1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_YACHTDICE1_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CYachtDice1Dlg::~CYachtDice1Dlg()
{
}

void CYachtDice1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TUTORIAL_BTN, m_bitmapBtn);
}


BEGIN_MESSAGE_MAP(CYachtDice1Dlg, CDialogEx)
    ON_WM_CTLCOLOR()
    ON_WM_DRAWITEM()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_Roll, &CYachtDice1Dlg::OnBnClickedRoll)
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_TUTORIAL_BTN, &CYachtDice1Dlg::OnBnClickedTutorialBtn)
END_MESSAGE_MAP()


// CYachtDice1Dlg message handlers

BOOL CYachtDice1Dlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here
    
    back.Load(_T("GameBoard_Background.png"));
    
    // 닉네임
    m_font.CreatePointFont(130, _T("Ravie"));
    GetDlgItem(IDC_STATIC_NAME)->SetFont(&m_font);
    GetDlgItem(IDC_STATIC_NAME2)->SetFont(&m_font);
    SetDlgItemText(IDC_STATIC_NAME, m_strData);

    // 모든 버튼에 owner draw 스타일 적용
    for (int i = IDC_p1_1; i <= IDC_p1_12; i++)
    {
        m_btnPlayers[i - IDC_p1_1].SubclassDlgItem(i, this);
        m_btnPlayers[i - IDC_p1_1].ModifyStyle(0, BS_OWNERDRAW);
    }

    // Picture Controls 초기화
    for (int i = 0; i < 5; i++)
    {
        m_dicePics[i].SubclassDlgItem(IDC_Dices_1 + i, this);
    }


    // Bitmap 이미지 로드
    LoadDiceBitmaps();

    srand(time(nullptr));

    // 임의로 첫 번째 주사위를 각 Picture Control에 표시 (테스트용)
    for (int i = 0; i < 5; i++)
    {
        // 랜덤한 이미지 인덱스 선택 (0부터 5까지)
        int randomIndex = rand() % 6;
        ShowDiceImage(i, 0);
    }

    // 주사위를 정렬합니다.
    ArrangeDicePics();

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

HBRUSH CYachtDice1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // 모든 버튼의 배경을 투명하게 설정
    if (nCtlColor == CTLCOLOR_BTN)
    {
        pDC->SetBkMode(TRANSPARENT);
        return (HBRUSH)GetStockObject(NULL_BRUSH);
    }

    if (nCtlColor == CTLCOLOR_STATIC)
    {
        // Picture Control의 배경을 투명하게 설정
        if (pWnd->GetDlgCtrlID() >= IDC_Dices_1 && pWnd->GetDlgCtrlID() <= IDC_Dices_5)
        {
            pDC->SetBkMode(TRANSPARENT);
            return (HBRUSH)GetStockObject(NULL_BRUSH);
        }
    }

    if (nCtlColor == CTLCOLOR_STATIC)
    {
        // Static text의 배경색을 투명하게 설정
        pDC->SetBkMode(TRANSPARENT);
        return (HBRUSH)GetStockObject(NULL_BRUSH);
    }

    return hbr;
}

void CYachtDice1Dlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // 모든 버튼을 그리는 코드
    for (int i = IDC_p1_1; i <= IDC_p1_12; i++)
    {
        if (nIDCtl == i)
        {
            CDC dc;
            dc.Attach(lpDrawItemStruct->hDC);

            // 버튼의 영역 설정
            CRect rect(lpDrawItemStruct->rcItem);

            // 버튼의 배경을 투명하게 설정
            dc.SetBkMode(TRANSPARENT);

            // 버튼의 텍스트 출력
            CString strText;
            m_btnPlayers[i - IDC_p1_1].GetWindowText(strText);
            dc.DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            dc.Detach();
            return;
        }
    }

}

void CYachtDice1Dlg::LoadDiceBitmaps()
{
    // Bitmap 이미지 로드
    m_diceBitmaps[0].LoadBitmap(IDB_dice_1);
    m_diceBitmaps[1].LoadBitmap(IDB_dice_2);
    m_diceBitmaps[2].LoadBitmap(IDB_dice_3);
    m_diceBitmaps[3].LoadBitmap(IDB_dice_4);
    m_diceBitmaps[4].LoadBitmap(IDB_dice_5);
    m_diceBitmaps[5].LoadBitmap(IDB_dice_6);

}

void CYachtDice1Dlg::ShowDiceImage(int diceIndex, int imageIndex)
{
    // Picture Control에 Bitmap 이미지 설정
    if (diceIndex < 0 || diceIndex >= 5 || imageIndex < 0 || imageIndex >= 6)
        return;

    m_dicePics[diceIndex].SetBitmap((HBITMAP)m_diceBitmaps[imageIndex].GetSafeHandle());
}

void CYachtDice1Dlg::ArrangeDicePics()
{
    // Picture Control 정렬
    int spacing = 50; // 컨트롤 사이의 간격
    int left = 735; // 첫 번째 컨트롤의 왼쪽 위치
    int top = 350; // 첫 번째 컨트롤의 상단 위치
    int width, height;

    // 첫 번째 Picture Control의 크기를 가져옵니다.
    CRect rect;
    m_dicePics[0].GetWindowRect(&rect);
    width = rect.Width();
    height = rect.Height();

    for (int i = 0; i < 5; i++)
    {
        m_dicePics[i].SetWindowPos(NULL, left + i * (width + spacing), top, width, height, SWP_NOZORDER);
    }
}

void CYachtDice1Dlg::OnBnClickedRoll()
{
    // 랜덤 주사위 이미지를 생성하고 갱신합니다.
    for (int i = 0; i < 5; i++)
    {
        int randomIndex = rand() % 6; // 0부터 5 사이의 랜덤 숫자 생성
        ShowDiceImage(i, randomIndex); // 주사위 이미지 갱신
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CYachtDice1Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CYachtDice1Dlg::OnPaint()
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

void CYachtDice1Dlg::OnBnClickedTutorialBtn()
{
    // TODO: Add your control notification handler code here
    CTutorial dlgT;
    dlgT.DoModal();
}

void CYachtDice1Dlg::SetData(const CString& strData)
{
    m_strData = strData;
}