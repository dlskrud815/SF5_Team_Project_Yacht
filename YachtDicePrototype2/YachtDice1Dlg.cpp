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
#include <numeric>
#include <random>
#include <chrono>
#include <iterator> // std::begin, std::end

using namespace std;

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

    DDX_Control(pDX, IDC_STATIC_TURN1, m_turn_user);
    DDX_Control(pDX, IDC_STATIC_TURN2, m_turn_cpu);


    // 컨트롤과 멤버 변수를 연결
    DDX_Control(pDX, IDC_p1_sub, m_p1Sub);
    DDX_Control(pDX, IDC_p1_bonus, m_p1Bonus);
    DDX_Control(pDX, IDC_p1_total, m_p1Total);
    for (int i = 0; i < 12; i++) {
        DDX_Control(pDX, IDC_p1_1 + i, m_p1[i]);
    }
    DDX_Control(pDX, IDC_round_num, m_round_num);
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

    ON_BN_CLICKED(IDC_p1_1, &CYachtDice1Dlg::OnBnClickedp1_1)
    ON_BN_CLICKED(IDC_p1_2, &CYachtDice1Dlg::OnBnClickedp1_2)
    ON_BN_CLICKED(IDC_p1_3, &CYachtDice1Dlg::OnBnClickedP1_3)
    ON_BN_CLICKED(IDC_p1_4, &CYachtDice1Dlg::OnBnClickedP1_4)
    ON_BN_CLICKED(IDC_p1_5, &CYachtDice1Dlg::OnBnClickedP1_5)
    ON_BN_CLICKED(IDC_p1_6, &CYachtDice1Dlg::OnBnClickedP1_6)
    ON_BN_CLICKED(IDC_p1_7, &CYachtDice1Dlg::OnBnClickedP1_7)
    ON_BN_CLICKED(IDC_p1_8, &CYachtDice1Dlg::OnBnClickedP1_8)
    ON_BN_CLICKED(IDC_p1_9, &CYachtDice1Dlg::OnBnClickedP1_9)
    ON_BN_CLICKED(IDC_p1_10, &CYachtDice1Dlg::OnBnClickedP1_10)
    ON_BN_CLICKED(IDC_p1_11, &CYachtDice1Dlg::OnBnClickedP1_11)
    ON_BN_CLICKED(IDC_p1_12, &CYachtDice1Dlg::OnBnClickedP1_12)
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

    vector <int> cpuEditIds = { IDC_cpu_1, IDC_cpu_2, IDC_cpu_3, IDC_cpu_4, IDC_cpu_5, IDC_cpu_6, IDC_cpu_7,
            IDC_cpu_8, IDC_cpu_9, IDC_cpu_10, IDC_cpu_11, IDC_cpu_12, IDC_cpu_sub, IDC_cpu_bonus, IDC_cpu_total };

    vector <int> playerEditIds = { IDC_p1_1, IDC_p1_2, IDC_p1_3, IDC_p1_4, IDC_p1_5, 
            IDC_p1_6, IDC_p1_7, IDC_p1_8, IDC_p1_9, IDC_p1_10, IDC_p1_11, IDC_p1_12};

    vector <int> DiceButtonIds = { IDC_DICE_BUTTON2, IDC_DICE_BUTTON3, IDC_DICE_BUTTON4, IDC_DICE_BUTTON5, IDC_DICE_BUTTON6, IDC_DICE_BUTTON7, IDC_DICE_BUTTON8,
            IDC_DICE_BUTTON9, IDC_DICE_BUTTON10, IDC_DICE_BUTTON11};

    //cpu 점수판 초기화
    for (int id : cpuEditIds)
    {
        CEdit* pEdit = reinterpret_cast<CEdit*>(GetDlgItem(id));
        if (pEdit != nullptr)
        {
            m_cpuEditControls.push_back(pEdit);
        }
    }
    for (int i = 0; i < m_cpuEditControls.size(); i++)
    {
        m_cpuEditControls[i]->SetWindowText(L"");
    }

    //플레이어 점수판 초기화
    for (int id : playerEditIds)
    {
        CButton* pButton = reinterpret_cast<CButton*>(GetDlgItem(id));
        if (pButton != nullptr)
        {
            m_playerEditControls.push_back(pButton);
        }
    }
    for (int i = 0; i < m_playerEditControls.size(); i++)
    {
        m_playerEditControls[i]->SetWindowText(L"");
    }
    m_p1Sub.SetWindowText(L"");
    m_p1Bonus.SetWindowText(L"");
    m_p1Total.SetWindowText(L"");

    //주사위 버튼 초기화?
    for (int id : DiceButtonIds)
    {
        CButton* pButton = reinterpret_cast<CButton*>(GetDlgItem(id));
        if (pButton != nullptr)
        {
            m_DiceButtonControls.push_back(pButton);
        }
    }
    for (int i = 5; i < 10; i++) //BUTTON7 ~ 11
    {
        m_DiceButtonControls[i]->ShowWindow(SW_HIDE);
    }

    back.Load(_T("GameBoard_Background.png"));
    
    // 닉네임
    // Create a LOGFONT structure
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 50; // Font height
    lf.lfWeight = FW_BOLD; // Bold weight
    _tcscpy_s(lf.lfFaceName, _T("Segoe Script")); // Font face name

    // Create the bold font
    m_boldFont.CreateFontIndirect(&lf);
    GetDlgItem(IDC_STATIC_NAME)->SetFont(&m_boldFont);
    GetDlgItem(IDC_STATIC_NAME2)->SetFont(&m_boldFont);
    SetDlgItemText(IDC_STATIC_NAME, m_strData);

    m_rollFont.CreatePointFont(135, _T("Segoe Script"));
    GetDlgItem(IDC_roll_num)->SetFont(&m_rollFont);

    // 주사위 돌린 횟수 체크할 변수 초기화
    m_roll = 0;

    //라운드 초기화
    m_round = 1;
    CString strRound;
    strRound.Format(_T("%d"), m_round);
    GetDlgItem(IDC_round_num)->SetWindowTextW(strRound);

    // 툴팁컨트롤을 생성한다.
    m_tip_ctrl.Create(this);
    m_tip_ctrl.AddTool(GetDlgItem(IDC_DICE_BUTTON2), _T("주사위 1 선택"));
    m_tip_ctrl.SetMaxTipWidth(300);
    m_tip_ctrl.SetDelayTime(TTDT_AUTOPOP, 2000);


    // roll 직후, 주사위 상태(선택 여부)를 확인하는 벡터
    for (int i = 0; i < 5; i++) {

        pickDice.push_back(0);
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    //턴 이미지
    m_Pepe1.LoadBitmapW(IDB_PEPE1);
    m_Pepe2.LoadBitmapW(IDB_PEPE2);

    m_turn_user.SetBitmap(m_Pepe1);
    m_turn_cpu.SetBitmap(m_Pepe2);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

HBRUSH CYachtDice1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

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

        // IDC_roll_num 글자색 흰색
        if (pWnd->GetDlgCtrlID() == IDC_roll_num)
        {
            pDC->SetTextColor(RGB(255, 255, 255));
        }
        pDC->SetBkMode(TRANSPARENT);
        return (HBRUSH)GetStockObject(NULL_BRUSH);
    }

    return hbr;
}


// 비트맵 리소스를 로드하는 함수
HBITMAP LoadBitmapFromResource(HINSTANCE hInstance, int resourceID) {
    return LoadBitmap(hInstance, MAKEINTRESOURCE(resourceID));

}

void CYachtDice1Dlg::OnBnClickedRoll()
{
    vector<int> indices = { IDB_dice_1, IDB_dice_2, IDB_dice_3, IDB_dice_4, IDB_dice_5, IDB_dice_6 };

    random_shuffle(indices.begin(), indices.end());

    HINSTANCE hInstance = GetModuleHandle(nullptr);

    m_ready_dices.clear();
   // m_top_dices.clear();


    // 벡터의 크기를 미리 설정
    m_ready_dices.resize(5);
    m_top_dices.resize(5);

    for (int j = 0; j < 5; ++j) {
        int i = rand() % 6;

        int diceValue = indices[i] - 139;
        m_ready_dices[j] = diceValue;

        HBITMAP hBitmap = LoadBitmapFromResource(hInstance, indices[i]);
        if (hBitmap == nullptr) {
            AfxMessageBox(_T("Failed to load bitmap!"));
            return;
        }
        if (!pickDice[j]) {
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

    for (int i = 0; i < 5; i++)
    {
        if (pickDice[i])
        {
            //BUTTON2 ~ 6
            m_DiceButtonControls[i]->ShowWindow(SW_HIDE);
        }
        else
        {
            //BUTTON2 ~ 6
            m_DiceButtonControls[i]->ShowWindow(SW_SHOW);
        }
    }

    m_roll++;

    // 정수를 CString으로 변환
    CString strRollNum;
    strRollNum.Format(_T("%d/3"), m_roll);

    CRect rect;
    GetDlgItem(IDC_roll_num)->GetWindowRect(&rect);
    ScreenToClient(&rect);
    InvalidateRect(rect);

    GetDlgItem(IDC_roll_num)->SetWindowTextW(strRollNum);

}

void AdjustButtonToBitmap(CButton& button, HBITMAP hBitmap)
{
    BITMAP bm;
    GetObject(hBitmap, sizeof(BITMAP), &bm);
    button.SetBitmap(hBitmap);
    button.SetWindowPos(nullptr, 0, 0, bm.bmWidth, bm.bmHeight, SWP_NOMOVE | SWP_NOZORDER);
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

    if (m_roll >= 3) {
        OnBnClickedChoosecategory();
    }
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

void CYachtDice1Dlg::ClickedDiceButton(int btnNum)
{
    if (btnNum <= 4) //BUTTON 2 ~ 6
    {
        m_DiceButtonControls[btnNum + 5]->ShowWindow(SW_SHOW);
        // 버튼 2에서 이미지를 추출합니다.
        HBITMAP hBitmap = (HBITMAP)m_DiceButtonControls[btnNum]->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);
        BITMAP bm;
        GetObject(hBitmap, sizeof(BITMAP), &bm);

        // 버튼 7에 이미지를 설정합니다.
        m_DiceButtonControls[btnNum + 5]->SetBitmap(hBitmap);
        m_DiceButtonControls[btnNum + 5]->SetWindowPos(nullptr, 0, 0, bm.bmWidth, bm.bmHeight, SWP_NOMOVE | SWP_NOZORDER);


        // 버튼 2에 있는 이미지를 삭제합니다.
        m_DiceButtonControls[btnNum]->SetBitmap(nullptr);
        pickDice[btnNum] = TRUE;

        m_DiceButtonControls[btnNum]->EnableWindow(FALSE);
        m_DiceButtonControls[btnNum + 5]->EnableWindow(TRUE);

        m_DiceButtonControls[btnNum]->ShowWindow(SW_HIDE);

        m_top_dices[btnNum] = m_ready_dices[btnNum];
    }
    else //BUTTON 7 ~ 11
    {
        m_DiceButtonControls[btnNum - 5]->ShowWindow(SW_SHOW);
        m_DiceButtonControls[btnNum - 5]->EnableWindow(TRUE);

        // 버튼 7에서 이미지를 추출합니다.
        HBITMAP hBitmap = (HBITMAP)m_DiceButtonControls[btnNum]->SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0);

        // 버튼 2에 이미지를 설정합니다.
        m_DiceButtonControls[btnNum - 5]->SetBitmap(hBitmap);

        // 버튼 7에 있는 이미지를 삭제합니다.
        m_DiceButtonControls[btnNum]->SetBitmap(nullptr);
        pickDice[btnNum - 5] = FALSE;

        CString str;
        m_DiceButtonControls[btnNum]->GetWindowText(str);

        m_DiceButtonControls[btnNum]->EnableWindow(FALSE);
        m_DiceButtonControls[btnNum]->ShowWindow(SW_HIDE);

        m_top_dices[btnNum - 5] = 0;
    }
    
}

void CYachtDice1Dlg::OnBnClickedDiceButton2()
{
    ClickedDiceButton(0);
}


void CYachtDice1Dlg::OnBnClickedDiceButton3()
{
    ClickedDiceButton(1);
}


void CYachtDice1Dlg::OnBnClickedDiceButton4()
{
    ClickedDiceButton(2);
}


void CYachtDice1Dlg::OnBnClickedDiceButton5()
{
    ClickedDiceButton(3);
}


void CYachtDice1Dlg::OnBnClickedDiceButton6()
{
    ClickedDiceButton(4);
}


void CYachtDice1Dlg::OnBnClickedDiceButton7()
{
    ClickedDiceButton(5);
}


void CYachtDice1Dlg::OnBnClickedDiceButton8()
{
    ClickedDiceButton(6);
}


void CYachtDice1Dlg::OnBnClickedDiceButton9()
{
    ClickedDiceButton(7);
}


void CYachtDice1Dlg::OnBnClickedDiceButton10()
{
    ClickedDiceButton(8);
}


void CYachtDice1Dlg::OnBnClickedDiceButton11()
{
    ClickedDiceButton(9);
}


void CYachtDice1Dlg::OnBnClickedChoosecategory()
{
    // TODO: Add your control notification handler code here
    GetDlgItem(IDC_Roll)->ShowWindow(SW_HIDE);

    for (int i = 0; i < 5; i++)
    {
        if (!pickDice[i]) // 선택이 안 된 주사위
        {
            switch (i)
            {
            case 0:
                OnBnClickedDiceButton2();
                break;
            case 1:
                OnBnClickedDiceButton3();
                break;
            case 2:
                OnBnClickedDiceButton4();
                break;
            case 3:
                OnBnClickedDiceButton5();
                break;
            case 4:
                OnBnClickedDiceButton6();
                break;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        m_DiceButtonControls[i]->ShowWindow(SW_HIDE); //BUTTON 2 ~ 6
        m_DiceButtonControls[i+5]->EnableWindow(FALSE); //BUTTON 7 ~ 11
    }
}


BOOL CYachtDice1Dlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    m_tip_ctrl.RelayEvent(pMsg);

    return CDialogEx::PreTranslateMessage(pMsg);
}

void CYachtDice1Dlg::PlayYachtCPU()
{
    v_tempCpuScore = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //Aces ~ Yacht

    for (int i = 0; i < v_tempCpuScore.size(); i++)
    {
        v_check[i] = false;
    }

    int num = rand() % 3 + 1;

    //랜덤으로 1~3회 주사위 돌리기
    for (int i = 0; i < num; i++)
    {
        OnBnClickedRoll();
        Sleep(1500);
    }
    OnBnClickedChoosecategory();

    //점수 계산
    //Aces ~ Sixes
    for (int i = 1; i <= 6; i++)
    {
        for (int die : m_top_dices) {
            if (die == i) {
                v_tempCpuScore[i - 1] += i;
            }
        }
    }

    //Choice
    for (int die : m_top_dices) {
        v_tempCpuScore[6] += die;
    }

    int count[7] = { 0 };
    for (int die : m_top_dices) {
        count[die]++;
    }

    bool twoSame = false, threeSame = false;

    for (int i = 1; i <= 6; i++) {
        //4 of a kind
        if (count[i] >= 4) {
            for (int die : m_top_dices)
            {
                v_tempCpuScore[7] += die;
            }
        }

        //풀하우스
        if (count[i] == 2) {
            twoSame = true;
        }
        if (count[i] == 3) {
            threeSame = true;
        }
    }

    //풀하우스
    if (twoSame && threeSame)
    {
        v_tempCpuScore[8] = accumulate(m_top_dices.begin(), m_top_dices.end(), 0);
    }


    vector<int> uniqueDice(m_top_dices.begin(), m_top_dices.end());
    sort(uniqueDice.begin(), uniqueDice.end());

    //S.S
    vector<vector<int>> smallStraightPatterns = {
        {1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}, {1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}
    };

    for (const auto& pattern : smallStraightPatterns) {
        bool found = true;
        for (int i = 0; i < pattern.size(); i++) {
            if (find(uniqueDice.begin(), uniqueDice.end(), pattern[i]) == uniqueDice.end()) {
                found = false;
                break;
            }
        }
        if (found) {
            v_tempCpuScore[9] = 15;
            break;
        }
    }

    //L.S
    if ((uniqueDice == vector<int>{1, 2, 3, 4, 5}) || (uniqueDice == vector<int>{2, 3, 4, 5, 6})) {
        v_tempCpuScore[10] = 30;
    }

    //Yacht
    if (count[m_top_dices[0]] == 5) {
        v_tempCpuScore[11] = 50;
    }


    //CPU는 최대 점수를 획득할 수 있도록 카테고리 선택
    int max = 0, max_i = -1;
    for (int i = 0; i < v_tempCpuScore.size(); i++)
    {
        if (num >= max && !v_check[i])
        {
            max = v_tempCpuScore[i];
            max_i = i;
        }
    }

    v_check[max_i] = true;
    v_CpuScore[max_i] = max;

    CString strScore;
    strScore.Format(_T("%d"), max);


}

void CYachtDice1Dlg::SwitchTurn(int turn)
{
    //턴 표시 0으로 
    m_roll = 0;
    CString strRollNum;
    strRollNum.Format(_T("%d/3"), m_roll);
    CRect rect;
    GetDlgItem(IDC_roll_num)->GetWindowRect(&rect);
    ScreenToClient(&rect);
    InvalidateRect(rect);
    GetDlgItem(IDC_roll_num)->SetWindowTextW(strRollNum);

    // 점수 집계를 위한 벡터 초기화
    m_ready_dices.clear();
    m_top_dices.clear();

     //ROLL 버튼 다시 표시
    GetDlgItem(IDC_Roll)->ShowWindow(SW_SHOW);

    //올라간 주사위 안 보이게
    for (int i = 0; i < 10; i++)    
    {
        if (i <= 4)
        {
            m_DiceButtonControls[i]->EnableWindow(TRUE);
        }
        else
        {
            m_DiceButtonControls[i]->EnableWindow(TRUE);
            m_DiceButtonControls[i]->ShowWindow(SW_HIDE);
        }
    }

    m_top_dices.clear();
    pickDice.clear();
    for (int i = 0; i < 5; i++)
    {
        pickDice.push_back(0);
    }

    if (turn) //CPU 턴일 때
    {
        //라운드 횟수 추가
        m_round++;
        CString strRound;
        strRound.Format(_T("%d"), m_round);
        GetDlgItem(IDC_round_num)->SetWindowTextW(strRound);

        //턴 이미지 바꾸기
        m_turn_user.SetBitmap(m_Pepe2);
        m_turn_cpu.SetBitmap(m_Pepe1);

        //플레이어 점수판 버튼 비활성화
        for (int i = 0; i < m_playerEditControls.size(); i++)
        {
            m_playerEditControls[i]->EnableWindow(FALSE);
        }


        //이하 CPU 플레이 코드 들어갈 예정
        //PlayYachtCPU();
        
        //플레이어로 턴 전환
        SwitchTurn(0);
    }
    else //플레이어 턴일 때
    {
        //턴 이미지 바꾸기
        m_turn_user.SetBitmap(m_Pepe1);
        m_turn_cpu.SetBitmap(m_Pepe2);

        for (int i = 0; i < m_playerEditControls.size(); i++)
        {
            m_playerEditControls[i]->EnableWindow(TRUE);
        }
    }
}

void CYachtDice1Dlg::OnBnClickedp1_1()
{
    // 주사위에서 숫자 1의 개수를 계산
    int countOfOnes = 0;
    for (int die : m_top_dices) {
        if (die == 1) {
            countOfOnes++;
        }
    }

    // p1_1 버튼에 해당 계산식 적용하여 결과 출력
    int score = countOfOnes * 1; // 숫자 1의 개수에 1을 곱한 값
    CString strScore;
    strScore.Format(_T("%d"), score);
    SetDlgItemText(IDC_p1_1, strScore);

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedp1_2()
{
    // 주사위에서 숫자 2의 개수를 계산
    int countOfTwos = 0;
    for (int die : m_top_dices) {
        if (die == 2) {
            countOfTwos++;
        }
    }

    // p1_2 버튼에 해당 계산식 적용하여 결과 출력
    int score = countOfTwos * 2; // 숫자 2의 개수에 2를 곱한 값
    CString strScore;
    strScore.Format(_T("%d"), score);
    SetDlgItemText(IDC_p1_2, strScore);

    UpdateScoreBoard();
}



void CYachtDice1Dlg::OnBnClickedP1_3()
{
    // 주사위에서 숫자 3의 개수를 계산
    int countOfThrees = 0;
    for (int die : m_top_dices) {
        if (die == 3) {
            countOfThrees++;
        }
    }

    // p1_3 버튼에 해당 계산식 적용하여 결과 출력
    int score = countOfThrees * 3; // 숫자 3의 개수에 3을 곱한 값
    CString strScore;
    strScore.Format(_T("%d"), score);
    SetDlgItemText(IDC_p1_3, strScore);

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedP1_4()
{
    // 주사위에서 숫자 4의 개수를 계산
    int countOfFours = 0;
    for (int die : m_top_dices) {
        if (die == 4) {
            countOfFours++;
        }
    }

    // p1_4 버튼에 해당 계산식 적용하여 결과 출력
    int score = countOfFours * 4; // 숫자 4의 개수에 4를 곱한 값
    CString strScore;
    strScore.Format(_T("%d"), score);
    SetDlgItemText(IDC_p1_4, strScore);

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedP1_5()
{
    // 주사위에서 숫자 5의 개수를 계산
    int countOfFives = 0;
    for (int die : m_top_dices) {
        if (die == 5) {
            countOfFives++;
        }
    }

    // p1_5 버튼에 해당 계산식 적용하여 결과 출력
    int score = countOfFives * 5; // 숫자 5의 개수에 5를 곱한 값
    CString strScore;
    strScore.Format(_T("%d"), score);
    SetDlgItemText(IDC_p1_5, strScore);

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedP1_6()
{
    // 주사위에서 숫자 6의 개수를 계산
    int countOfsixes = 0;
    for (int die : m_top_dices) {
        if (die == 6) {
            countOfsixes++;
        }
    }

    // p1_6 버튼에 해당 계산식 적용하여 결과 출력
    int score = countOfsixes * 6; // 숫자 6의 개수에 6을 곱한 값
    CString strScore;
    strScore.Format(_T("%d"), score);
    SetDlgItemText(IDC_p1_6, strScore);

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedP1_7()
{
    // 주사위 숫자들의 합을 계산
    int sum = 0;
    for (int die : m_top_dices) {
        sum += die;
    }

    // p1_7 버튼에 계산된 합계를 출력
    CString strSum;
    strSum.Format(_T("%d"), sum);
    SetDlgItemText(IDC_p1_7, strSum);

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedP1_8()
{
    // 배열에 같은 수 4개 이상이면 해당 합계 출력
    int count[7] = { 0 };
    for (int die : m_top_dices) {
        count[die]++;
    }
    for (int i = 1; i <= 6; i++) {
        if (count[i] >= 4) {
            // p1_8 버튼에 계산된 합계를 출력
            CString strScore;
            strScore.Format(_T("%d"), accumulate(m_top_dices.begin(), m_top_dices.end(), 0));
            SetDlgItemText(IDC_p1_8, strScore);
            return;
        }
    }
    // 조건에 맞는 경우가 없을 때는 0 출력
    SetDlgItemText(IDC_p1_8, _T("0"));

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedP1_9()
{
    // 배열에 Full House가 되면 해당 합계 출력
    int count[7] = { 0 };
    for (int die : m_top_dices) {
        count[die]++;
    }
    bool twoSame = false, threeSame = false;
    for (int i = 1; i <= 6; i++) {
        if (count[i] == 2) {
            twoSame = true;
        }
        if (count[i] == 3) {
            threeSame = true;
        }
    }
    if (twoSame && threeSame) {
        // p1_9 버튼에 계산된 합계를 출력
        CString strScore;
        strScore.Format(_T("%d"), accumulate(m_top_dices.begin(), m_top_dices.end(), 0));
        SetDlgItemText(IDC_p1_9, strScore);
    }
    else {
        // 조건에 맞는 경우가 없을 때는 0 출력
        SetDlgItemText(IDC_p1_9, _T("0"));
    }

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedP1_10()
{

    // 배열에 Small Straight가 되면 해당 합계 출력
    vector<int> uniqueDice(m_top_dices.begin(), m_top_dices.end());
    sort(uniqueDice.begin(), uniqueDice.end());

    vector<vector<int>> smallStraightPatterns = {
        {1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}, {1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}
    };

    for (const auto& pattern : smallStraightPatterns) {
        bool found = true;
        for (int i = 0; i < 4; i++) {
            if (find(uniqueDice.begin(), uniqueDice.end(), pattern[i]) == uniqueDice.end()) {
                found = false;
                break;
            }
        }
        if (found) {
            // p1_10 버튼에 계산된 합계를 출력
            SetDlgItemText(IDC_p1_10, _T("15"));
            return;
        }
    }
    // 조건에 맞는 경우가 없을 때는 0 출력
    SetDlgItemText(IDC_p1_10, _T("0"));

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedP1_11()
{

    // 배열에 Large Straight가 되면 해당 합계 출력
    vector<int> uniqueDice(m_top_dices.begin(), m_top_dices.end());
    sort(uniqueDice.begin(), uniqueDice.end());

    if ((uniqueDice == vector<int>{1, 2, 3, 4, 5}) || (uniqueDice == vector<int>{2, 3, 4, 5, 6})) {
        // p1_11 버튼에 계산된 합계를 출력
        SetDlgItemText(IDC_p1_11, _T("30"));
    }
    else {
        // 조건에 맞는 경우가 없을 때는 0 출력
        SetDlgItemText(IDC_p1_11, _T("0"));
    }

    UpdateScoreBoard();
}


void CYachtDice1Dlg::OnBnClickedP1_12()
{
    // 배열에 Yacht가 되면 해당 합계 출력
    int count[7] = { 0 };
    for (int die : m_top_dices) {
        count[die]++;
    }
    if (count[m_top_dices[0]] == 5) {
        // p1_12 버튼에 계산된 합계를 출력
        SetDlgItemText(IDC_p1_12, _T("50"));
    }
    else {
        // 조건에 맞는 경우가 없을 때는 0 출력
        SetDlgItemText(IDC_p1_12, _T("0"));
    }

    UpdateScoreBoard();
}

void CYachtDice1Dlg::UpdateScoreBoard()
{
    //글자 겹침 해결
    CRect rect1, rect2, rect3;

    GetDlgItem(IDC_p1_sub)->GetWindowRect(&rect1);
    ScreenToClient(&rect1);
    InvalidateRect(rect1);

    GetDlgItem(IDC_p1_bonus)->GetWindowRect(&rect2);
    ScreenToClient(&rect2);
    InvalidateRect(rect2);

    GetDlgItem(IDC_p1_total)->GetWindowRect(&rect3);
    ScreenToClient(&rect3);
    InvalidateRect(rect3);

    // p1_1부터 p1_6까지의 값을 합산
    int sub = 0;
    for (int i = 0; i < 6; i++) {
        CString str;
        m_p1[i].GetWindowText(str);
        int value = _ttoi(str);
        sub += value;
    }

    // p1_sub에 합계 출력
    CString sumStr;
    sumStr.Format(_T("%d"), sub);
    m_p1Sub.SetWindowText(sumStr);

    // p1_sub이 65 이상인 경우 p1_bonus에 35 출력
    int bonus = (sub >= 65) ? 35 : 0;
    CString bonusStr;
    bonusStr.Format(_T("%d"), bonus);
    m_p1Bonus.SetWindowText(bonusStr);

    
    // sub + bonus + p1_7부터 p1_12까지의 값을 합산
    int total = sub + bonus;
    for (int i = 6; i < 12; i++) {
        CString str;
        m_p1[i].GetWindowText(str);
        int value = _ttoi(str);
        total += value;
    }


    // p1_total에 합계 출력
    CString totalStr;
    totalStr.Format(_T("%d"), total);
    m_p1Total.SetWindowText(totalStr);

    //CPU로 턴 전환
    SwitchTurn(1);
}