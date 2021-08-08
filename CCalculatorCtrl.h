#pragma once


/*
��� ��
1. �����
2. �Է°��� ��������� ����
3. �����ڿ� �з���ȣ �ο�
4. ������ �켱���� üũ
5. ���������� �������� ������ ��ȯ
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



