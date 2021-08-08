#pragma once
#include "pch.h"



class CAdder
{
private:
	int m_length;
	CString m_stackBuffer;
	CString m_opStack;

	char m_cOperator;
	int m_iFlag;
	int m_iFirstOperand;
	int m_iSecondOperand;
	

	BOOL IsEmpty(); // 스택이 비어있는가
	int CheckBracket(CStatic *result_text, wchar_t c);
	int GetBufferLength();
	void GetResult(CStatic _text, int opCode);
	
	BOOL Pop(CStatic* result_text);
	void SetFlag();
	
public:
	void Push(wchar_t c, int num);
	CString GetStackBuffer() { return m_stackBuffer; }
public:
	CAdder();
	~CAdder();

};

