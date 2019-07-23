#pragma once
class CUserData
{
	friend class CMyList;
public:
	CUserData();
	~CUserData();
	
	void SetName(const char *pszName);
	void SetPhone(const char *pszName);
	void SetNext(CUserData *pUserData);
	const char* GetName(void) const { return szName; }
	const char* GetPhone(void) const { return szPhone; }
	CUserData* GetNext(void) const { return pNext; }

protected:
	char szName[32];
	char szPhone[32];

	CUserData *pNext;

	static int nUserDataCounter;
};

