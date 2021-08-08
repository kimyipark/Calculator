//개별 클래스를 관리해주는 클래스.
//모든 멤버변수와 클래스는 이곳에 선언되어 있어 필요하면 가져다 쓰면 된다.
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
	CStackCalculator* GetStackCalculator() { return m_pStackCalculator; } // 컨트롤 클래스 반환. 클랙스 내부 메소드를 사용할 수 있게 된다.
};