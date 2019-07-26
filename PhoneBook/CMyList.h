#pragma once
#include "CUserData.h"

class CMyList
{
public:
	CMyList(const char* pszFileName);
	~CMyList();

protected:
	void ReleaseList(void);
	CUserData m_Head;
	int ItemCount;

public:
	void LoadList(const char* pszFileName);

	void SaveList(const char* pszFileName);

	CUserData* FindNode(const char* pszName);
	
	int AddNewNode(const char* pszName, const char* pszPhone);

	void PrintAll(void);

	int RemoveNode(const char* pszName);

	int GetCount(void) { return ItemCount; }

};

