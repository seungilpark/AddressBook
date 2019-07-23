#pragma once
#include "pch.h"
#include "CUserInterface.h"
#include <iostream>
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

}

void CUserInterface::Search(void)
{

}
void CUserInterface::Remove(void)
{

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
