#include "pch.h"
#include "CalculatorMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //_DEBUG


CCalculatorMgr::CCalculatorMgr()
{
	m_pStackCalculator = new CStackCalculator();
}

CCalculatorMgr::~CCalculatorMgr()
{

}

