
/* VIEW 지켜야할 사항
	1.  Model이 가지고 있는 정보를 따로 저장해서는 안된다.
	2. Model이나 Control의 구성요소를 몰라야한다.
	3. 변경이 일어나면 변경통지에 대한 처리를 구현해야한다.
*/
#pragma once
#include "CalculatorMgr.h"
#include "CCalculatorCtrl.h"

class CcalculatorDlg : public CDialogEx
{
public:
	CcalculatorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
		//virtual ~CcalculatorDlg();

private: 
	void UpdateString(CString inputString);

private:
	CRect m_image_rect; // to get picture control rect
	CImage m_image; // to display company logo
	CStatic m_DisplayingInputText;// Display input String and only for display
	CStatic m_DisplayingResultText;// Display calculation result and only for display
    CCalculatorMgr* m_pCalculatorMgr;
	CCalculatorCtrl *ctrl;
	CRect m_btn_rect;


	//CString m_testArray[100] = { 0, };  For future.

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Resource 와 각종 컨트롤


protected:
	virtual BOOL OnInitDialog(); // 화면에 보이는 컨트롤들의 초기화를 담당하는 영역.
	afx_msg void OnPaint(); // 대화상자크기 변경등을 수행하는 영역.
	DECLARE_MESSAGE_MAP()


public: // 버튼이벤트 관련 함수
	afx_msg void OnBnClicked(UINT uiID);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadioEnable();
	afx_msg void OnBnClickedRadioDisable();
};
