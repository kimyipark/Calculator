#include "pch.h"
#include "CAdder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //_DEBUG

//class CCalculatorMgr;

CAdder::CAdder()
{
	m_length = 0;
	m_stackBuffer = _T("");
	m_opStack = _T("");


	m_cOperator = ' ';
	m_iFlag = 0;
	m_iFirstOperand = 0;
	m_iSecondOperand = 0;
	//m_pCalculatorMgr = new CCalculatorMgr();

}


CAdder::~CAdder()
{
}


BOOL CAdder::IsEmpty()
{
	if (this->m_stackBuffer.IsEmpty())
		return TRUE;

	return FALSE;
}


int CAdder::CheckBracket(CStatic* result_text, wchar_t c)
{
	//BOOL bRet = FALSE;
	int index = -1; //return -1 character is not found.

	switch (c)
	{
	case'(':
		//this->Push(result_text, c);
		break;


	case')':
		index = this->m_stackBuffer.Find('(');
		if (index == -1)
		{
			//Do nothing.
		}
		else
		{
			//this->Push(result_text, c,);
		}
		break;


	default:
		//Do nothing
		break;
	}


	return index;
}


int CAdder::GetBufferLength()
{
	return this->m_length;
}


void CAdder::GetResult(CStatic _text, int opCode)
{
	switch (opCode)
	{
	case 0: //+
		break;
	default:
		break;
	}
}

void CAdder::Push(wchar_t c, int num) // 문자 입력.
{
	if (c >= '0' && c <= '9')
	{
		this->m_stackBuffer += c; // 문자 추가.
		this->m_length++; // 문자열 길이++
	}
	else// 연산자 입력를 입력 했을 때
	{
			wchar_t str = this->m_stackBuffer.GetAt(this->m_length - 1); //이전 입력값 확인

			if (str >= '0' && str <= '9')
			{
				this->m_iFirstOperand = num;
				this->m_stackBuffer.Empty();
				this->m_length = 0;						// 문자열 길이++
			}
	}
}

BOOL CAdder::Pop(CStatic* result_text) // 가장 최근 입력된 문자 제거.
{
	BOOL bRet = FALSE;


	if (this->m_stackBuffer.IsEmpty())
	{
		AfxMessageBox(L"Error occured. Stack is empty");
	}
	else
	{
		this->m_stackBuffer.SetAt(m_length - 1, ' '); // 가장 최근에 추가된 문자열을 공백문자로 Set.
		this->m_stackBuffer.TrimRight(); // 오른쪽 공백 제거.
		this->m_length--; // 문자열 길이++.

		result_text->SetWindowTextW(this->m_stackBuffer); // 문자열 출력.
		bRet = TRUE;
	}


	return bRet;
}

void CAdder::SetFlag()
{
	this->m_iFlag = 1;
}

//void CAdder::DoCalculate(int )
//{// 스택 계산기 알고리즘.
//	// 미구현
//}