#include "pch.h"
#include "CMyList.h"
#include "CMyNode.h"
#include "CUserData.h"
#include <iostream>


using namespace std;
CMyList::CMyList(CMyNode* pHead)
	:m_pHead(pHead)
{
}


CMyList::~CMyList()
{
}


CMyNode* CMyList::FindNode(const char* pszName)
{

}


int CMyList::AddNewNode(CMyNode *pNewNode)
{
	if (FindNode(pNewNode->GetKey()) != nullptr)
	{
		delete pNewNode;
		return 0;
	}

	pNewNode->pNext = m_pHead->pNext;
	m_pHead->pNext = pNewNode;

	return 1;
}


int CMyList::RemoveNode(const char* pszName)
{

}

void CMyList::ReleaseList(void)
{

}


void CMyList::PrintAll(void)
{
	CMyNode *pTmp = m_pHead->pNext;

	while (pTmp != nullptr)
	{
		pTmp->PrintNode();
		pTmp = pTmp->pNext;
	}

	cout << "CUserData Counter: " <<CUserData::GetUserDataCounter() << endl;
}

