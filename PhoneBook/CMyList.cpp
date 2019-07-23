#include "pch.h"
#include "CMyList.h"
#include <string>
#include <iostream>


CMyList::CMyList(const char* pszFileName)
{
	// call lostList()
}


CMyList::~CMyList()
{
	CMyList::ReleaseList();
}

void CMyList::LoadList(const char* pszFileName)
{
	// check if file exists
	// if yes
	// load a list from file
	// else
	// create a file 

}

void CMyList::SaveList(const char* pszFileName)
{

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
}

int CMyList::AddNewNode(const char* pszName, const char* pszPhone)
{
	CUserData *newNode = new CUserData;
	if (!newNode) return 0;//also throw an allocation error

	newNode->SetName(pszName);
	newNode->SetPhone(pszPhone);
	newNode->SetNext(nullptr);

	if (m_Head.GetNext()) newNode->SetNext(m_Head.GetNext());
	m_Head.SetNext(newNode);
}

void CMyList::PrintAll(void)
{
	const CUserData *cur = m_Head.GetNext();
	std::cout << "------------------Phone Book------------------" << std::endl;
	while (cur)
	{
		std::cout << "Name: " << cur->GetName() << std::endl;
		std::cout << "Phone: " << cur->GetPhone() << std::endl;
		std::cout << "----------------------------------------------" << std::endl;
		cur = cur->GetNext();
	}
	std::cout << "----------------------------------------------" << std::endl;
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

			std::cout << "Removed Item with name: { " << pszName << " }." << std::endl; //maybe move it to UI

			return 1;
		}
	}
	std::cout << "No Item found with name: { " << pszName << " }." << std::endl; //UI function maybe move it to UI
	return -1;
}