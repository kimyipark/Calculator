
// calculator.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "calculator.h"
#include "D_NaviBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CcalculatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CcalculatorApp 생성

CcalculatorApp::CcalculatorApp()
{
	 //m_pCalculatorMgr = new CCalculatorMgr();
}


// 유일한 CcalculatorApp 개체입니다.

CcalculatorApp theApp;


// CcalculatorApp 초기화

BOOL CcalculatorApp::InitInstance()
{
	CWinApp::InitInstance();
	
	//// 대화 상자에 셸 트리 뷰 또는
	//// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	//CShellManager *pShellManager = new CShellManager;

	//// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 표준 초기화
	//m_pCalculatorMgr = new CCalculatorMgr();
	CcalculatorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	

	return FALSE;
}

