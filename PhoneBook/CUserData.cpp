#include "pch.h"
#include "CUserData.h"
#include <string>

CUserData::CUserData()
	: pNext(nullptr)
{
}

CUserData::CUserData(const char* pszName, const char* pszPhone)
	:pNext(nullptr)
{
	this->SetName(pszName);
	this->SetPhone(pszPhone);
}


CUserData::~CUserData()
{
}

void CUserData::SetName(const char *pszName)
{
	strncpy_s(this->szName, pszName, 32);
}

void CUserData::SetPhone(const char *pszPhone)
{
	strncpy_s(this->szPhone, pszPhone, 32);
}

void CUserData::SetNext(CUserData *pUserData)
{
	pNext = pUserData;
}

