/* VIEW 지켜야할 사항
	1.  Model이 가지고 있는 정보를 따로 저장해서는 안된다.
	2. Model이나 Control의 구성요소를 몰라야한다.
	3. 변경이 일어나면 변경통지에 대한 처리를 구현해야한다.
*/

#include "pch.h"
#include "framework.h"
#include "calculator.h"
#include "D_NaviBox.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CcalculatorDlg::CcalculatorDlg(CWnd* pParent)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_pCalculatorMgr = new CCalculatorMgr();
	ctrl = new CCalculatorCtrl();
}

void CcalculatorDlg::DoDataExchange(CDataExchange* pDX) // 컨트롤과 그 컨트롤의 매개변수를 ㄴ이어주는 역할
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Text_RESULT, m_DisplayingInputText);
	DDX_Control(pDX, IDC_Text_RESULT2, m_DisplayingResultText);
}

BEGIN_MESSAGE_MAP(CcalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_BTN0, IDC_BTN_REMOVE, CcalculatorDlg::OnBnClicked)
	ON_BN_CLICKED(IDCANCEL, &CcalculatorDlg::OnBnClickedCancel)//IDCANCLE과 캔슬버튼입력이벤트가 연결되어 있다.
	ON_BN_CLICKED(IDC_RADIO_ENABLE, &CcalculatorDlg::OnBnClickedRadioEnable)
	ON_BN_CLICKED(IDC_RADIO_DISABLE, &CcalculatorDlg::OnBnClickedRadioDisable)
END_MESSAGE_MAP()



BOOL CcalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_BTN1)->GetWindowRect(m_btn_rect);
	SetWindowText(L"Calculator");

	//SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	//SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	GetDlgItem(IDC_PIC)->GetWindowRect(m_image_rect);
	ScreenToClient(m_image_rect);

	m_image.Load(L"kmac.bmp");
	InvalidateRect(m_image_rect, FALSE);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


void CcalculatorDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
	}
	else
	{
		if (!m_image.IsNull())
		{
			dc.SetStretchBltMode(COLORONCOLOR);
			m_image.Draw(dc, m_image_rect);
		}
	}
}

void CcalculatorDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CcalculatorDlg::UpdateString(CString inputString)
{
	m_pCalculatorMgr = new CCalculatorMgr();
}
//void CcalculatorDlg::OnBnClickedBtn0()
//{
//	// 1. 버튼을 누르면 구별해 줄 함수 선언 - OnBNClicked
//	// 2. 숫자인지 연산자인지 구분 및 Control할 함수 - 
//	// 3. Control함수에서 연상한 데이터가 쌓이는 Data Class 선언
//	// 4. Data Class 데이터를 저장할 Set, Get 함수 선언
//	// 4. UI에 Display할 때 Data Class에 저장한 멤버변수 Get해서 표시
//	
//	SetSelectedID();
//}

void CcalculatorDlg::OnBnClicked(UINT uiID)
{
	CString str = nullptr;
	switch (uiID)
	{
	case IDC_BTN_EQUAL:
		//str = _T("2*5-7"); //3 통과
		//str = _T("135*22*1+24/12+3*120/6"); //3,032 통과
		//str = _T("130*(12+1+3*2)"); //2,470 통과
		str = _T("123*111-(33/2+1+10*2)*2"); //13,578    테스트케이스 미통
		m_pCalculatorMgr->GetStackCalculator()->SetInput(str);
		str=m_pCalculatorMgr->GetStackCalculator()->ConvertToPostfix(m_pCalculatorMgr->GetStackCalculator()->GetResultString());
		//str = m_pCalculatorMgr->GetStackCalculator()->DoCalculation(m_pCalculatorMgr->GetStackCalculator()->GetResultString());
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN0:
		str = _T("0");
		m_pCalculatorMgr->GetStackCalculator()->SetInput(str);
		str = m_pCalculatorMgr->GetStackCalculator()->GetResultString();
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN1:
		str = _T("1");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN2:
		str = _T("2");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN3:
		str = _T("3");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN4:
		str = _T("4");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN5:
		str = _T("5");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN6:
		str = _T("6");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN7:
		str = _T("7");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN8:
		str = _T("8");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN9:
		str = _T("9");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN_MULTIPLY:
		str = _T("*");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN_ADD:
		str = _T("+");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN_SUB:
		str = _T("-");
		m_DisplayingInputText.SetWindowText(str);//변수 이름 수정 필요. 
		// view에 선언된 변수 값을 get하는 것보다 이벤트가 발생하면
		//컨트롤의 변수에 값을 set해주고 view는 그 값을 get해서 출력해주자.
		break;

	case IDC_BTN_DIVIDE:
		str = _T("/");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN_LBRACKET:
		str = _T("(");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN_RBRACKET:
		str = _T(")");
		m_DisplayingInputText.SetWindowText(str);
		break;

	case IDC_BTN_REMOVE:
		str = m_pCalculatorMgr->GetStackCalculator()->ResetString();
		m_DisplayingInputText.SetWindowText(str);
		break;
	}
}

void CcalculatorDlg::OnBnClickedRadioEnable()
{// 리스트박스 활성화
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CListBox* list = (CListBox*)GetDlgItem(IDC_LIST_HISTORY);
	list->ShowWindow(TRUE);
}

void CcalculatorDlg::OnBnClickedRadioDisable()
{//리스트박스 비활성화
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CListBox* list = (CListBox*)GetDlgItem(IDC_LIST_HISTORY);
	list->ShowWindow(FALSE);
}
