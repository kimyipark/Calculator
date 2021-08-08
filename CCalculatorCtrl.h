#pragma once


/*
기능 명세
1. 계산기능
2. 입력값을 멤버변수에 세팅
3. 연산자에 분류번호 부여
4. 연산자 우선순위 체크
5. 중위연산을 후위연산 순서로 변환
*/


typedef struct OperandBuffer
{
	char m_Buffer[20] = { 0, };
	int m_Count = 0;
}OpBuffer;



class CCalculatorCtrl
{
public:
	CCalculatorCtrl();
	~CCalculatorCtrl();

private:
	CString m_strReceived;
	CString m_strResult;
	int m_iStringLength;

private:
	wchar_t StringPop(CString &strInput);
	void StringPush(CString &strBuffer,const wchar_t &cElement);
	int GiveOperatorValue(const wchar_t &cOperator);
	BOOL IsPrecedance(const CString &strOperator,const wchar_t &cElement);
	CString MakePostfix(CString strInput);
	CString DoCalculation(const CString &strPostfix);

	CString GetResult() const { return m_strResult; }
	void UpdateString(const CString InputString);
};



