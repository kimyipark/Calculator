#pragma once
#include "pch.h"
#include "CStackCalculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif // _DEBUG

typedef struct operandBuffer
{
	int Buffer[20] = { 0, };
	int Count = 0;
}OpBuffer;


CStackCalculator::CStackCalculator() {
	m_ResultString.Empty();
	m_ReceivedString.Empty();
	m_iStringLength = 0;
}


CStackCalculator::~CStackCalculator()
{

}
BOOL CStackCalculator::IsPrecedence(CString operatorStack, wchar_t singleString)
{
 	BOOL b_rtn = FALSE;
	if (!operatorStack.IsEmpty())
	{
		int opLen = operatorStack.GetLength();
		if (operatorStack.GetAt(opLen - 1) == '*' || operatorStack.GetAt(opLen - 1) == '/') b_rtn = TRUE;
	}
	return b_rtn;
}

CString  CStackCalculator::PopString(CString stackString)
{
	CString returnString = NULL;
	int LastIndex = stackString.GetLength() - 1;
	returnString = stackString.GetAt(LastIndex);

	return returnString;
}

CString CStackCalculator::ConvertToPostfix(CString inputString)
{
	CString returnStack = NULL;
	CString postfixStack = NULL;
	CString operatorStack = NULL;

	int stringLength = inputString.GetLength();


	wchar_t singleCharacter = NULL;
	// 1. 스택 순회하면서 숫자인지 연산자인지 체크
	   //2. 숫자이면 후위연산 스택에 푸시.
	   //2-2. 문자열이면 ')'인지 확인.
	   //2-3. ')'가 아니면 연산자 스택에 푸시.
	   // 2-4. 비교해서 우선순위가 현재 가지고 있는 연산자보다 높은 연산자는 즉시 후위연산 스택에 푸시  
	   //3. ')'가 들어오면 연산자 스택에서 '(' 찾기
	   //3-2. 없으면 연산 에러, 있으면 ')' 팝 시작.
	   //4. '('가 나올 때까지 팝 수행.
	   //4-2. 팝 수행한 연산자는 후위연산 스택에 푸시.
	   //5. 스택을 왼->오로 스캔하면서 숫자는 반환스택에 넣고 연산자는 연산에 필요한 숫자(스택이 NUILL이 될 때까지 팝)꺼내서 연산 후 다시 스택에 추가
	   //6. 반환
	for (int i = 0; i < stringLength; i++)
	{ 
		singleCharacter = inputString.GetAt(i);
		int opStackLen = 0;

		if (singleCharacter >= '0' && singleCharacter <= '9')
		{
			postfixStack += singleCharacter;
			// posfixStack = "1"
		}
		else // 연산자 또는 괄호이면./.. 
		{
			if(singleCharacter !='(')	postfixStack += ' ';
			switch (singleCharacter)
			{
			case')':
				//postfixStack += ' ';
				while (operatorStack.GetAt(operatorStack.GetLength() - 1) != '(')
				{
					postfixStack += operatorStack.GetAt(operatorStack.GetLength() - 1);
					operatorStack.SetAt(operatorStack.GetLength() - 1, ' ');
					operatorStack.TrimRight();
				}
				operatorStack.SetAt(operatorStack.GetLength() - 1, ' ');
				operatorStack.TrimRight();
				break;

			case'(':
				operatorStack += singleCharacter;

				break;

			case'+':
				if (operatorStack.IsEmpty())
				{
					operatorStack += singleCharacter;
				}
				else
				{
					while (IsPrecedence(operatorStack, singleCharacter))
					{
						postfixStack += PopString(operatorStack);
						operatorStack.SetAt(operatorStack.GetLength() - 1, ' ');
						operatorStack.TrimRight();
					}
					operatorStack += singleCharacter;
				}
				break;

			case'-':
				if (operatorStack.IsEmpty())
				{
					operatorStack += singleCharacter;
				}
				else
				{
					while (IsPrecedence(operatorStack, singleCharacter))
					{
						postfixStack += PopString(operatorStack);
						operatorStack.SetAt(operatorStack.GetLength()-1, ' ');
						operatorStack.TrimRight();
					}
					operatorStack += singleCharacter;
				}
				break;

			case'*':
				operatorStack += singleCharacter;
				break;

			case '/':
				operatorStack += singleCharacter;
				break;
			}
		}
	}
	int opStackLen = operatorStack.GetLength();
	for (int j = 0; j < opStackLen; j++)
	{
		wchar_t c = postfixStack.GetAt(postfixStack.GetLength() - 1);
		if (j == 0&&c>='0'&&c<='9') postfixStack += _T(" ");
		postfixStack += this->PopString(operatorStack);
		operatorStack.SetAt(operatorStack.GetLength() - 1, ' ');
		operatorStack.TrimRight(); 
		// 20210722 cs yuk 원노트에 에러 이유 기록했다.
	}
	returnStack = postfixStack;

	return returnStack;
}


CString CStackCalculator::DoCalculation(CString inpuString)
{
	CString postfixString = NULL;
	CString returnString=NULL;
	operandBuffer operandBuffer;
	CString characterBuffer=NULL;

	postfixString = this->ConvertToPostfix(inpuString);
	for (int i = 0; i < postfixString.GetLength(); i++) 
	{ // 첫번째 요소부터 꺼내서 
		wchar_t singleCharacter = postfixString.GetAt(i);

		if (singleCharacter>='0' && singleCharacter<='9')
		{
			characterBuffer += singleCharacter;
		}
		else
		{
			int result = 0;
			if (postfixString.GetAt(i) == ' ')
			{
				//i++;
				operandBuffer.Buffer[operandBuffer.Count] = _tstoi(characterBuffer);
				operandBuffer.Count++;
				characterBuffer.Empty();
				continue;
			}
			
			switch (singleCharacter)
			{
			case '+':
				result = operandBuffer.Buffer[operandBuffer.Count - 2] + operandBuffer.Buffer[operandBuffer.Count - 1];
				operandBuffer.Buffer[operandBuffer.Count - 1] = 0;
				operandBuffer.Buffer[operandBuffer.Count - 2] = result;
				operandBuffer.Count--;
				break;

			case '-':
				result = operandBuffer.Buffer[operandBuffer.Count - 2] - operandBuffer.Buffer[operandBuffer.Count - 1];
				operandBuffer.Buffer[operandBuffer.Count - 1] = 0;
				operandBuffer.Buffer[operandBuffer.Count - 2] = result;
				operandBuffer.Count--;
				break;

			case '*':
				result = operandBuffer.Buffer[operandBuffer.Count - 2] * operandBuffer.Buffer[operandBuffer.Count - 1];
				operandBuffer.Buffer[operandBuffer.Count - 1] = 0;
				operandBuffer.Buffer[operandBuffer.Count - 2] = result;
				operandBuffer.Count--;
				break;

			case '/':
				if (operandBuffer.Buffer[operandBuffer.Count - 1] == 0)
				{
					AfxMessageBox(_T("ZeroDivide Ex"));
					this->ResetString();
					break;
				}
				result = operandBuffer.Buffer[operandBuffer.Count - 2] / operandBuffer.Buffer[operandBuffer.Count - 1];
				operandBuffer.Buffer[operandBuffer.Count - 1] = 0;
				operandBuffer.Buffer[operandBuffer.Count - 2] = result;
				operandBuffer.Count--;
				break;

			default:
				break;
			}
		}
	}

	returnString.Format(_T("%d"), operandBuffer.Buffer[0]);
	//SetResultString(returnString); //결과값을 갖고 연산 수행
	ResetString(); // 결과값을 버리고 연산 수행
	return returnString;
}