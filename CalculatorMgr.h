//���� Ŭ������ �������ִ� Ŭ����.
//��� ��������� Ŭ������ �̰��� ����Ǿ� �־� �ʿ��ϸ� ������ ���� �ȴ�.
#pragma once
#include "pch.h"
#include "CStackCalculator.h"

class CStackCalculator;
class CCalculatorMgr
{
private:
	CStackCalculator* m_pStackCalculator;
	//CDataMgr* m_pDataMgr;

public:
	CCalculatorMgr(void);
	~CCalculatorMgr(void);

public:
	CStackCalculator* GetStackCalculator() { return m_pStackCalculator; } // ��Ʈ�� Ŭ���� ��ȯ. Ŭ���� ���� �޼ҵ带 ����� �� �ְ� �ȴ�.
};