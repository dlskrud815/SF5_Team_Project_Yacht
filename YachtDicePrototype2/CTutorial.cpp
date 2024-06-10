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
END_MESSAGE_MAP()


// CTutorial message handlers
