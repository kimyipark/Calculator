#include "pch.h"
#include "CDataMgr.h"

#ifdef DEBUG
#define new DEBUG_NEW
#endif // DEBUG


CDataMgr::CDataMgr()
{
	CString m_History = NULL;
	double m_ResultValue = 0;
}

CDataMgr::~CDataMgr()
{

}

void CDataMgr::DataUpload(CString str, double result)
{
	m_History = str;
	m_ResultValue = result;
}