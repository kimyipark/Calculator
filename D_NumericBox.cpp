// D_NumericBox.cpp: 구현 파일
//

#include "pch.h"
#include "calculator.h"
#include "D_NumericBox.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(D_NumericBox, CDialogEx)

D_NumericBox::D_NumericBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NUMERIC_BTN, pParent)
{

}

D_NumericBox::~D_NumericBox()
{
}

void D_NumericBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(D_NumericBox, CDialogEx)
END_MESSAGE_MAP()

BOOL CcalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	

	return TRUE;
}


