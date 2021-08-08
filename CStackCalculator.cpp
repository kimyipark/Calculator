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
	// 1. ���� ��ȸ�ϸ鼭 �������� ���������� üũ
	   //2. �����̸� �������� ���ÿ� Ǫ��.
	   //2-2. ���ڿ��̸� ')'���� Ȯ��.
	   //2-3. ')'�� �ƴϸ� ������ ���ÿ� Ǫ��.
	   // 2-4. ���ؼ� �켱������ ���� ������ �ִ� �����ں��� ���� �����ڴ� ��� �������� ���ÿ� Ǫ��  
	   //3. ')'�� ������ ������ ���ÿ��� '(' ã��
	   //3-2. ������ ���� ����, ������ ')' �� ����.
	   //4. '('�� ���� ������ �� ����.
	   //4-2. �� ������ �����ڴ� �������� ���ÿ� Ǫ��.
	   //5. ������ ��->���� ��ĵ�ϸ鼭 ���ڴ� ��ȯ���ÿ� �ְ� �����ڴ� ���꿡 �ʿ��� ����(������ NUILL�� �� ������ ��)������ ���� �� �ٽ� ���ÿ� �߰�
	   //6. ��ȯ
	for (int i = 0; i < stringLength; i++)
	{ 
		singleCharacter = inputString.GetAt(i);
		int opStackLen = 0;

		if (singleCharacter >= '0' && singleCharacter <= '9')
		{
			postfixStack += singleCharacter;
			// posfixStack = "1"
		}
		else // ������ �Ǵ� ��ȣ�̸�./.. 
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
		// 20210722 cs yuk ����Ʈ�� ���� ���� ����ߴ�.
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
	{ // ù��° ��Һ��� ������ 
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
	//SetResultString(returnString); //������� ���� ���� ����
	ResetString(); // ������� ������ ���� ����
	return returnString;
}