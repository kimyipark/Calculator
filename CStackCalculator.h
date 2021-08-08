#include "pch.h"
#pragma once

#define MAX_STACK_LENGTH 100

class CStackCalculator
{
private:
	CString m_ResultString;
	CString m_ReceivedString;
	int m_iStringLength;

public:
	CStackCalculator();
	~CStackCalculator();
	void SetInput(CString singleCharacter) { this->m_ReceivedString += singleCharacter;  } // OnBnClicked 발생시 누른 버튼에 따라 
	CString GetResultString()									{ return this->m_ReceivedString; }
	CString ResetString()											{this->m_ReceivedString.Empty(); return this->m_ReceivedString; }
	CString DoCalculation(CString inpuString);
	CString ConvertToPostfix(CString inputString);


private:
	void SetResultString(CString inputString) { this->m_ReceivedString = inputString; } 
	BOOL IsPrecedence(CString operatorStack, wchar_t singleString);
	void PushString(CString stackString, wchar_t singleCharacter) { stackString += singleCharacter; } // push A to B
	CString PopString(CString stackString);
	//CString ConvertToPostfix(CString inputString);
};

