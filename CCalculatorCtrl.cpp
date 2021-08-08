#include "pch.h"
#include "CCalculatorCtrl.h"

#ifdef DEBUG
#define new DEBUG_NEW
#endif // DEBUG

enum OperatorCode
{
	NONE = 0,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	REMAINDER,
	LBRACKET,
	RBRACKET
}Operator;

CCalculatorCtrl::CCalculatorCtrl()
{
	m_iStringLength = 0;
	m_strReceived.Empty();
	m_strResult.Empty();
}


CCalculatorCtrl::~CCalculatorCtrl()
{

}


wchar_t CCalculatorCtrl::StringPop(CString &strInput)
{
	wchar_t rtnChar;
	const int Index = strInput.GetLength() - 1;

	rtnChar = strInput.GetAt(Index);
	strInput.SetAt(Index, ' ');
	strInput.TrimRight();

	return rtnChar;
}


void CCalculatorCtrl::StringPush(CString &strBuffer, const wchar_t &cElement)
{
	const int LastIndex = strBuffer.GetLength()-1;

	strBuffer.SetAt(LastIndex, cElement);
}



int CCalculatorCtrl::GiveOperatorValue(const wchar_t &cOperator)
{
	int rtnValue = NONE;

	switch (cOperator)
	{
	case '+':
		rtnValue = PLUS; //1
		break;

	case'-':
		rtnValue = MINUS; // 2
		break;

	case'*':
		rtnValue = MULTIPLY;// 3
		break;

	case'/':
		rtnValue = DIVIDE; //4
		break;

	case'%':
		rtnValue = REMAINDER; //5
		break;

	case'(':
		rtnValue = LBRACKET;
		break;

	case')':
		rtnValue = RBRACKET;
		break;

	default: // 0
		break;
	}

		return rtnValue;
}
BOOL CCalculatorCtrl::IsPrecedance(const CString &strOperator, const wchar_t &cContender)
{
	int topValue = GiveOperatorValue(strOperator.GetAt(strOperator.GetLength() - 1));
	int contenderValue = GiveOperatorValue(cContender);
	
	if (topValue >= MULTIPLY && topValue <LBRACKET && contenderValue<MULTIPLY)  return FALSE; // 연산자 스택에 있는 연산자보다 우선순위가 낮다.
	else return TRUE; // 
}



CString CCalculatorCtrl::MakePostfix(const CString strInfix)
{
	CString strReturn = NULL;
	CString strPostfix = NULL;
	CString strOperator = NULL;
	const int strLength = strInfix.GetLength();
	wchar_t singleChar = NULL;
	BOOL bPrecedance = FALSE;

	for (int i = 0; i < strLength; i++)
	{
		singleChar = strInfix.GetAt(i);

		if (singleChar >= '0' && singleChar <= '9')
		{
			strPostfix += singleChar;
		}
		else
		{ // 연산자라면...
			if (singleChar != '(')	strPostfix += _T(" ");
			bPrecedance = IsPrecedance(strOperator, singleChar);
			
			if (strOperator.IsEmpty() == TRUE)
			{
				if (GiveOperatorValue(singleChar) > 5) AfxMessageBox(_T("Wrong expression"));
			}

			if (!bPrecedance) // 스택에 있는 연산자가 우선순위가 더 높다면 수핸ㅇ
			{
				wchar_t PoppedOperator = StringPop(strOperator);
				
				while (PoppedOperator != '(')
				{
					strPostfix += PoppedOperator;
					PoppedOperator = StringPop(strOperator);
				}
			}
			else strOperator += singleChar;
		}
	}

	return strPostfix;
}



