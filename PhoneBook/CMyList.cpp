#include "pch.h"
#include "CMyList.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>


CMyList::CMyList(const char* pszFileName)
	: ItemCount(0)
{
	// call loadList()
	LoadList(pszFileName);
}


CMyList::~CMyList()
{
	CMyList::ReleaseList();
}

void CMyList::LoadList(const char* pszFileName)
{
	CUserData UDBuffer;
	std::ifstream fptr;
	
	fptr.open(pszFileName, std::ios::in | std::ios::binary);
	if (!fptr.fail())
	while(fptr.read((char*) &UDBuffer, sizeof(CUserData)), !fptr.eof())
	{
		AddNewNode(UDBuffer.GetName(), UDBuffer.GetPhone());
	}
	else fptr.open(pszFileName, std::ios::out | std::ios::binary);
	
	fptr.close();
	//problem would be the order of the objects saved because it always saved to the head
}

void CMyList::SaveList(const char* pszFileName)
{
	CUserData UDBuffer;
	CUserData* cur = m_Head.GetNext();
	std::ofstream fptr;
	fptr.open(pszFileName);

	while (cur) 
	{
		UDBuffer.SetName(cur->GetName());
		UDBuffer.SetPhone(cur->GetPhone());
		fptr.write((char*)&UDBuffer, sizeof(UDBuffer));
		cur = cur->GetNext();
	}

	fptr.close();
}

void CMyList::ReleaseList(void)
{
	int count = 0;
	CUserData *cur = &m_Head;
	CUserData *nodeToBeDeleted = nullptr;
	std::cout << "Releasing the list..."<< std::endl;
	while (cur->GetNext())
	{
		nodeToBeDeleted = cur->GetNext();
		cur->SetNext(cur->GetNext()->GetNext());
		std::cout << "Node to be deleted: " << nodeToBeDeleted->GetName() << std::endl;
		delete nodeToBeDeleted;
		count++;
	}
	std::cout << "Finished Releasing the list..."<< std::endl;
	std::cout << "Total deleted items = "<< count << std::endl;
}

/*
	find a node with a given parameter key
	may be enhanced replacing with reference parameter / return type
*/
CUserData* CMyList::FindNode(const char* pszName)
{
	CUserData* cur = &m_Head;
	while (cur->GetNext())
	{
		if (strncmp(cur->GetNext()->GetName(), pszName, 32) == 0)
		{
			return cur->GetNext();
		}
		cur = cur->GetNext();
	}

	return nullptr;
}

int CMyList::AddNewNode(const char* pszName, const char* pszPhone)
{
/*
	CUserData *newNode = new CUserData;
	if (!newNode) return 0;//maybe throw an allocation error
	newNode->SetName(pszName);
	newNode->SetPhone(pszPhone);
	newNode->SetNext(nullptr);
*/
	CUserData *newNode = new CUserData(pszName, pszPhone);
	if (!newNode) return 0;
	if (m_Head.GetNext()) newNode->SetNext(m_Head.GetNext());
	m_Head.SetNext(newNode);
	ItemCount++;
	return 1;
}

void CMyList::PrintAll(void)
{
	const CUserData *cur = &m_Head;
	while (cur->GetNext())
	{
		std::cout << "Name: " << cur->GetNext()->GetName() << std::endl;
		std::cout << "Phone: " << cur->GetNext()->GetPhone() << std::endl;
		std::cout << "----------------------------------------------" << std::endl;
		cur = cur->GetNext();
	}
}


int CMyList::RemoveNode(const char* pszName)
{
	CUserData *cur = &m_Head;
	CUserData *nodeToDelete;
	while (cur->GetNext())
	{
		if (strncmp(cur->GetNext()->GetName(), pszName, 32) == 0)
		{
			nodeToDelete = cur->GetNext();
			cur->SetNext(cur->GetNext()->GetNext()); // detaching the node to delete
			
			delete nodeToDelete; // deallocating the node to delete
			ItemCount--;


			return 1;
		}
	}
	return -1;
}