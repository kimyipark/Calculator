#pragma once


// D_NumericBox 대화 상자

class D_NumericBox : public CDialogEx
{
	DECLARE_DYNAMIC(D_NumericBox)

public:
	CRect m_rect;
	CSize m_size;

public:
	D_NumericBox(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~D_NumericBox();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
