// YachtDice1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "YachtDicePrototype2.h"
#include "afxdialogex.h"
#include "YachtDice1Dlg.h"
#include "resource.h" 
#include "CTutorial.h"

#include <Windows.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool arr[5] = { 1,1,1,1,1 };

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


    DDX_Control(pDX, IDC_DICE_BUTTON2, m_dice1);
    DDX_Control(pDX, IDC_DICE_BUTTON3, m_dice2);
    DDX_Control(pDX, IDC_DICE_BUTTON4, m_dice3);
    DDX_Control(pDX, IDC_DICE_BUTTON5, m_dice4);
    DDX_Control(pDX, IDC_DICE_BUTTON6, m_dice5);

    DDX_Control(pDX, IDC_DICE_BUTTON7, m_score1);
    DDX_Control(pDX, IDC_DICE_BUTTON8, m_score2);
    DDX_Control(pDX, IDC_DICE_BUTTON9, m_score3);
    DDX_Control(pDX, IDC_DICE_BUTTON10, m_score4);
    DDX_Control(pDX, IDC_DICE_BUTTON11, m_score5);
}


BEGIN_MESSAGE_MAP(CYachtDice1Dlg, CDialogEx)
    ON_WM_CTLCOLOR()
    ON_WM_DRAWITEM()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_Roll, &CYachtDice1Dlg::OnBnClickedRoll)
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_TUTORIAL_BTN, &CYachtDice1Dlg::OnBnClickedTutorialBtn)


    ON_MESSAGE(WM_USER + 1, &CYachtDice1Dlg::OnUpdateDice)
    ON_BN_CLICKED(IDC_DICE_BUTTON2, &CYachtDice1Dlg::OnBnClickedDiceButton2)
    ON_BN_CLICKED(IDC_DICE_BUTTON3, &CYachtDice1Dlg::OnBnClickedDiceButton3)
    ON_BN_CLICKED(IDC_DICE_BUTTON4, &CYachtDice1Dlg::OnBnClickedDiceButton4)
    ON_BN_CLICKED(IDC_DICE_BUTTON5, &CYachtDice1Dlg::OnBnClickedDiceButton5)
    ON_BN_CLICKED(IDC_DICE_BUTTON6, &CYachtDice1Dlg::OnBnClickedDiceButton6)
    ON_BN_CLICKED(IDC_DICE_BUTTON7, &CYachtDice1Dlg::OnBnClickedDiceButton7)
    ON_BN_CLICKED(IDC_DICE_BUTTON8, &CYachtDice1Dlg::OnBnClickedDiceButton8)
    ON_BN_CLICKED(IDC_DICE_BUTTON9, &CYachtDice1Dlg::OnBnClickedDiceButton9)
    ON_BN_CLICKED(IDC_DICE_BUTTON10, &CYachtDice1Dlg::OnBnClickedDiceButton10)
    ON_BN_CLICKED(IDC_DICE_BUTTON11, &CYachtDice1Dlg::OnBnClickedDiceButton11)
    ON_BN_CLICKED(IDC_ChooseCategory, &CYachtDice1Dlg::OnBnClickedChoosecategory)
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
    pButton2 = (CButton*)GetDlgItem(IDC_DICE_BUTTON2);
    pButton3 = (CButton*)GetDlgItem(IDC_DICE_BUTTON3);
    pButton4 = (CButton*)GetDlgItem(IDC_DICE_BUTTON4);
    pButton5 = (CButton*)GetDlgItem(IDC_DICE_BUTTON5);
    pButton6 = (CButton*)GetDlgItem(IDC_DICE_BUTTON6);
    pButton7 = (CButton*)GetDlgItem(IDC_DICE_BUTTON7);
    pButton8 = (CButton*)GetDlgItem(IDC_DICE_BUTTON8);
    pButton9 = (CButton*)GetDlgItem(IDC_DICE_BUTTON9);
    pButton10 = (CButton*)GetDlgItem(IDC_DICE_BUTTON10);
    pButton11 = (CButton*)GetDlgItem(IDC_DICE_BUTTON11);


    pButton7->EnableWindow(FALSE);
    pButton8->EnableWindow(FALSE);
    pButton9->EnableWindow(FALSE);
    pButton10->EnableWindow(FALSE);
    pButton11->EnableWindow(FALSE);

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

// 비트맵 리소스를 로드하는 함수
HBITMAP LoadBitmapFromResource(HINSTANCE hInstance, int resourceID) {
    return LoadBitmap(hInstance, MAKEINTRESOURCE(resourceID));

}

vector<int> RemoveArr(int idx) {
    vector<int> vec = { 0,1,2,3,4 };

    vec.erase(vec.begin() + idx);

    return vec;
}

void CYachtDice1Dlg::OnBnClickedRoll()
{
    vector<int> indices = { IDB_dice_1, IDB_dice_2, IDB_dice_3, IDB_dice_4, IDB_dice_5, IDB_dice_6 };

    //random_shuffle(indices.begin(), indices.end());

    HINSTANCE hInstance = GetModuleHandle(nullptr);

    for (int j = 0; j < 5; ++j) {
        int i = rand() % 6;
        HBITMAP hBitmap = LoadBitmapFromResource(hInstance, indices[i]);
        if (hBitmap == nullptr) {
            AfxMessageBox(_T("Failed to load bitmap!"));
            return;
        }
        if (arr[j] == 1) {
            PostMessage(WM_USER + 1, j, reinterpret_cast<LPARAM>(hBitmap));
            CString scoreStr;
            scoreStr.Format(_T("%d"), indices[i]);
            switch (j) {
            case 0:
                m_score1.SetWindowText(scoreStr);

            case 1:
                m_score2.SetWindowText(scoreStr);

            case 2:
                m_score3.SetWindowText(scoreStr);

            case 3:
                m_score4.SetWindowText(scoreStr);

            case 4:
                m_score5.SetWindowText(scoreStr);

            }

        }

    }

    pButton2->ShowWindow(SW_SHOW);
    pButton3->ShowWindow(SW_SHOW);
    pButton4->ShowWindow(SW_SHOW);
    pButton5->ShowWindow(SW_SHOW);
    pButton6->ShowWindow(SW_SHOW);


    // 이하 현정님 파트
    // 
    // 
    // 랜덤 주사위 이미지를 생성하고 갱신합니다.
    for (int i = 0; i < 5; i++)
    {
        int randomIndex = rand() % 6; // 0부터 5 사이의 랜덤 숫자 생성
        ShowDiceImage(i, randomIndex); // 주사위 이미지 갱신
    }
}

void AdjustButtonToBitmap(CButton& button, HBITMAP hBitmap)
{
    BITMAP bm;
    GetObject(hBitmap, sizeof(BITMAP), &bm);
    button.SetBitmap(hBitmap);
    //button.SetWindowPos(nullptr, 0, 0, 200, 200, SWP_NOMOVE | SWP_NOZORDER);
}

LRESULT CYachtDice1Dlg::OnUpdateDice(WPARAM wParam, LPARAM lParam)
{
    int diceIndex = static_cast<int>(wParam);
    HBITMAP hBitmap = reinterpret_cast<HBITMAP>(lParam);

    switch (diceIndex)
    {
    case 0:
        AdjustButtonToBitmap(m_dice1, hBitmap);
        break;

    case 1:
        AdjustButtonToBitmap(m_dice2, hBitmap);
        break;

    case 2:
        AdjustButtonToBitmap(m_dice3, hBitmap);
        break;

    case 3:
        AdjustButtonToBitmap(m_dice4, hBitmap);
        break;

    case 4:
        AdjustButtonToBitmap(m_dice5, hBitmap);
        break;
    }

    return 0;
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

void CYachtDice1Dlg::OnBnClickedDiceButton2()
{
    // TODO: Add your control notification handler code here
    // 버튼 2에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton2->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 7에 이미지를 설정합니다.
    pButton7->SetBitmap(hBitmap);

    // 버튼 2에 있는 이미지를 삭제합니다.
    pButton2->SetBitmap(nullptr);
    arr[0] = false;

    pButton2->EnableWindow(FALSE);
    pButton7->EnableWindow(TRUE);
}


void CYachtDice1Dlg::OnBnClickedDiceButton3()
{
    // TODO: Add your control notification handler code here
     // 버튼 3에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton3->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 8에 이미지를 설정합니다.
    pButton8->SetBitmap(hBitmap);

    // 버튼 3에 있는 이미지를 삭제합니다.
    pButton3->SetBitmap(nullptr);
    arr[1] = false;

    pButton3->EnableWindow(FALSE);
    pButton8->EnableWindow(TRUE);
}


void CYachtDice1Dlg::OnBnClickedDiceButton4()
{
    // TODO: Add your control notification handler code here
    // 버튼 4에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton4->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 9에 이미지를 설정합니다.
    pButton9->SetBitmap(hBitmap);

    // 버튼 4에 있는 이미지를 삭제합니다.
    pButton4->SetBitmap(nullptr);
    arr[2] = false;

    pButton4->EnableWindow(FALSE);
    pButton9->EnableWindow(TRUE);
}


void CYachtDice1Dlg::OnBnClickedDiceButton5()
{
    // TODO: Add your control notification handler code here
    // 버튼 5에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton5->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 10에 이미지를 설정합니다.
    pButton10->SetBitmap(hBitmap);

    // 버튼 5에 있는 이미지를 삭제합니다.
    pButton5->SetBitmap(nullptr);
    arr[3] = false;

    pButton5->EnableWindow(FALSE);
    pButton10->EnableWindow(TRUE);
}


void CYachtDice1Dlg::OnBnClickedDiceButton6()
{
    // TODO: Add your control notification handler code here
    // 버튼 6에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton6->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 11에 이미지를 설정합니다.
    pButton11->SetBitmap(hBitmap);

    // 버튼 6에 있는 이미지를 삭제합니다.
    pButton6->SetBitmap(nullptr);
    arr[4] = false;

    pButton6->EnableWindow(FALSE);
    pButton11->EnableWindow(TRUE);
}


void CYachtDice1Dlg::OnBnClickedDiceButton7()
{
    pButton2->EnableWindow(TRUE);

    // TODO: Add your control notification handler code here
    // 버튼 7에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton7->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 2에 이미지를 설정합니다.
    pButton2->SetBitmap(hBitmap);

    // 버튼 7에 있는 이미지를 삭제합니다.
    pButton7->SetBitmap(nullptr);
    arr[0] = true;

    CString str;
    pButton7->GetWindowText(str);
    //m_showScore.SetWindowText(str);


    //CString str;
    //GetDlgItemText(IDC_BUTTON7, str);
    //m_showScore.SetWindowText(str);

    pButton7->EnableWindow(FALSE);
}


void CYachtDice1Dlg::OnBnClickedDiceButton8()
{
    pButton3->EnableWindow(TRUE);

    // TODO: Add your control notification handler code here
    // 버튼 8에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton8->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 3에 이미지를 설정합니다.
    pButton3->SetBitmap(hBitmap);

    // 버튼 8에 있는 이미지를 삭제합니다.
    pButton8->SetBitmap(nullptr);
    arr[1] = true;

    CString str;
    pButton8->GetWindowText(str);
    //m_showScore.SetWindowText(str);


    //CString str;
    //GetDlgItemText(IDC_BUTTON7, str);
    //m_showScore.SetWindowText(str);

    pButton8->EnableWindow(FALSE);
}


void CYachtDice1Dlg::OnBnClickedDiceButton9()
{
    pButton4->EnableWindow(TRUE);

    // TODO: Add your control notification handler code here
    // 버튼 9에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton9->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 4에 이미지를 설정합니다.
    pButton4->SetBitmap(hBitmap);

    // 버튼 9에 있는 이미지를 삭제합니다.
    pButton9->SetBitmap(nullptr);
    arr[2] = true;

    CString str;
    pButton9->GetWindowText(str);
    //m_showScore.SetWindowText(str);


    //CString str;
    //GetDlgItemText(IDC_BUTTON7, str);
    //m_showScore.SetWindowText(str);

    pButton9->EnableWindow(FALSE);
}


void CYachtDice1Dlg::OnBnClickedDiceButton10()
{
    pButton5->EnableWindow(TRUE);

    // TODO: Add your control notification handler code here
    // 버튼 10에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton10->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 5에 이미지를 설정합니다.
    pButton5->SetBitmap(hBitmap);

    // 버튼 10에 있는 이미지를 삭제합니다.
    pButton10->SetBitmap(nullptr);
    arr[3] = true;

    CString str;
    pButton10->GetWindowText(str);
    //m_showScore.SetWindowText(str);


    //CString str;
    //GetDlgItemText(IDC_BUTTON7, str);
    //m_showScore.SetWindowText(str);}

    pButton10->EnableWindow(FALSE);
}


void CYachtDice1Dlg::OnBnClickedDiceButton11()
{
    pButton6->EnableWindow(TRUE);

    // TODO: Add your control notification handler code here
    // 버튼 11에서 이미지를 추출합니다.
    HBITMAP hBitmap = (HBITMAP)pButton11->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

    // 버튼 6에 이미지를 설정합니다.
    pButton6->SetBitmap(hBitmap);

    // 버튼 11에 있는 이미지를 삭제합니다.
    pButton11->SetBitmap(nullptr);
    arr[4] = true;

    CString str;
    pButton11->GetWindowText(str);
    //m_showScore.SetWindowText(str);


    //CString str;
    //GetDlgItemText(IDC_BUTTON7, str);
    //m_showScore.SetWindowText(str);}

    pButton11->EnableWindow(FALSE);
}


void CYachtDice1Dlg::OnBnClickedChoosecategory()
{
    // TODO: Add your control notification handler code here
    pButton2->ShowWindow(SW_HIDE);
    pButton3->ShowWindow(SW_HIDE);
    pButton4->ShowWindow(SW_HIDE);
    pButton5->ShowWindow(SW_HIDE);
    pButton6->ShowWindow(SW_HIDE);
    pButton7->EnableWindow(FALSE);
    pButton8->EnableWindow(FALSE);
    pButton9->EnableWindow(FALSE);
    pButton10->EnableWindow(FALSE);
    pButton11->EnableWindow(FALSE);
}
