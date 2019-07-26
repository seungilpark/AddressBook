#pragma once
#include "pch.h"
#include "CUserInterface.h"
#include <iostream>
#include "CMyList.h"
#include "CUserData.h"
using namespace std;

CUserInterface::CUserInterface(CMyList &rList)
	:m_List(rList)
{
}


CUserInterface::~CUserInterface()
{
}

void CUserInterface::Add(void)
{
	char szName[32];
	char szPhone[32];
	cout << "Enter Name to add: ";
	cout << endl;
	cin >> szName;
	cout << "Enter Phone Nuber: ";
	cin >> szPhone;
	cout << endl;
	m_List.AddNewNode(szName, szPhone);
	PrintAll();
}

void CUserInterface::Search(void)
{
	char szName[32];
	CUserData *nodeFound;
	cout << "Enter Name to find: ";
	cin >> szName;
	cout << endl;
	if ((nodeFound = m_List.FindNode(szName)))
	{
		cout << nodeFound->GetName() << " : " << nodeFound->GetPhone() << endl;
	}
	else cout << "No item found" << endl;
}
void CUserInterface::Remove(void)
{
	char szName[32];
	cout << "Enter Name to delete from phone book: ";
	cin >> szName;
	cout << endl;
	if (m_List.RemoveNode(szName) == 1)
	{
		cout << "Deleted: " << szName << endl;
	}
	else
	{
		cout << "No item with name in the phonebook" << szName << endl;
	}
}

int CUserInterface::PrintUI(void)
{
	int nMenu = 0;
	cout << "Menu <1> Add <2> Search <3> Print All <4> Remove" << endl;
	do 
	{
		cin >> nMenu;
	} while (nMenu > 4 || nMenu < 0);

	return nMenu;
}

void CUserInterface::PrintAll(void)
{
	std::cout << "------------------Phone Book------------------" << std::endl;
	std::cout << "Total number of items = " << m_List.GetCount() << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
	m_List.PrintAll();
	std::cout << "----------------------------------------------" << std::endl;
}

int CUserInterface::Run(void)
{
	int nMenu = 0;
	while ((nMenu = PrintUI()) != 0)
	{
		switch (nMenu)
		{
		case 1: // add
			Add();
			break;

		case 2: // Search
			Search();
			break;

		case 3: // Print All
			PrintAll();
			break;

		case 4: // REmove
			Remove();
			break;

		}
	}

	return nMenu;
}
