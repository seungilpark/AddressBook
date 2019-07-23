// AddressBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

// Phone Book Program
// manages Phone


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <assert.h>

/* the filename to save addresses */
const char *DATA_FILE_NAME = "Address.dat";

/* define Node */

typedef struct node
{
	char name[32];
	char num[32];
	struct node *next;
} node;

typedef struct list
{
	node *head;
	int length;
} list;

list g_list = { {0}, 0 };

/* node managing code */
node* FindNode(char* pszName);//find node by name
int AddNewNode(char *pszName, char *pszNum); // add new node to the list
int RemoveNode(char *pszName);//deletes node by its name
void ReleaseList();//deletes all nodes (deallocates)
int LoadList(const char *pszFileName);// reads nodes from a file and completes the address list
int SaveList(const char *pszFileName); // saves the list to a file


/* Interface Functions */
void Add();//take input from user to add node
void Search(); //take input from user and search node
void PrintAll(); // print all nodes 
void Remove(); // take input to delete a node
int PrintUI(); // display options for main menu and takes a user input(choice from the list of options)



int main()
{
	int userChoice, fileState;
	fileState = LoadList(DATA_FILE_NAME);
	PrintAll();
	
	while ((userChoice = PrintUI()) != 0)
	{
		switch (userChoice)
		{
		case -1:
			puts("invalid input...");
			puts("try again...");
			break;

		case 1:
			Add();
			PrintAll();
			break;

		case 2:
			//search
			Search();
			break;

		case 3:
			Remove();
			break;
			// remove

		default: break;
		}
	};

	puts("saving....");
	SaveList(DATA_FILE_NAME);
	ReleaseList();
	puts("Good Bye...");
	exit(0);

	return 0;
}

/*
	find node by name
*/
node* FindNode(char* pszName)
{
	//iterate through the list
	// check if pszName exist
	// found return node 
	// else return null
	node *cursor = g_list.head;
	while (cursor != NULL)
	{
		if (strcmp(cursor->name, pszName) == 0)
			return cursor;
		else
			cursor = cursor->next;
	}
	return NULL;
}


int AddNewNode(char *pszName, char *pszNum) // add new node to the list
{
	node *newNode = (node*)malloc(sizeof(node));
	if (newNode == NULL) return 0;
	strncpy_s(newNode->name, pszName, 32);
	strncpy_s(newNode->num, pszNum, 32);
	newNode->next = NULL;
	if (g_list.length) newNode->next = g_list.head;
	g_list.head = newNode;
	g_list.length++;
	return 1;

	//save the list?
}

//deletes node by its name
int RemoveNode(char *pszName)
{
	node *cursor = g_list.head;
	node *prev = NULL;
	// case 1 empty list
	if (cursor == NULL)
	{
		printf("ERROR In RemoveNode(): empty list");
		return 0;
	}

	while (cursor != NULL)
	{
		if ((strcmp(pszName, cursor->name) == 0))
		{
			if (g_list.length == 1)
			{
				g_list.head = NULL;
				free(cursor);
				g_list.length--;
				return 1;
			}

			prev->next = cursor->next;
			free(cursor);
			g_list.length--;
			return 1;
		}
		else
		{
			prev = cursor;
			cursor = cursor->next;
		}
	}

	return 0;//not found
}


// reads nodes from a file and completes the address list
int LoadList(const char *pszFileName)
{
	node nodeBuffer;
	FILE *fptr;  
	fopen_s(&fptr, pszFileName, "rb");
	if (fptr == NULL)
	{
		printf("Empty file. Creating a list...\n");
		fopen_s(&fptr, pszFileName, "w");
		fclose(fptr);
		return 0;
	}

	while (fread(&nodeBuffer, sizeof(node), 1, fptr))
	{
		AddNewNode(nodeBuffer.name, nodeBuffer.num);
		g_list.length++;
	}

	fclose(fptr);
	return 1;
}

// saves the list to a file
int SaveList(const char *pszFileName)
{
	node *cur = g_list.head;
	FILE *fptr;
	fopen_s(&fptr, pszFileName, "wb");
	if (fptr == NULL) return 0;
	while (cur)
	{
		fwrite(cur, sizeof(node), 1, fptr);
		cur = cur->next;
	}
	fclose(fptr);
	return 1;
}

//deletes all nodes (deallocates)
void ReleaseList()
{
	node *toDelete, *cur;
	cur = g_list.head;

	while (cur)
	{
		g_list.head = cur->next;
		toDelete = cur;
		cur = g_list.head;
		free(toDelete);
	}
}
//take input from user to add node
void Add()
{
	char name[32];// 0x0135FD54
	char num[32];//0x0135FD2C

	getchar();
	puts("Enter name:");
	gets_s(name, 32);

	puts("Enter number:");
	gets_s(num, 32);
	
	AddNewNode(name,  num);
	printf("New entry added to the list: %s - %s.\n", name, num);

}

//take input from user and search node
void Search()
{
	char searchTerm[32];
	printf("Enter the name you want to searach: ");
	getchar();
	gets_s(searchTerm, 32);
	putchar('\n');

	node *result;
	if ((result = FindNode(searchTerm)) != NULL)
	{
		printf("Number found for %s: %s\n", result->name, result->num);
	}
	else
	{
		puts("Number not found...");
	}
	PrintAll();

}

// print all nodes 
void PrintAll()
{
	node *cur = g_list.head;
	if (cur == NULL)
	{
		puts("Empty list...");
		return;
	}
	puts("\n----Name-----\t----Number----\n");

	while (cur)
	{
		printf("%s\t:\t%s\n", cur->name, cur->num);
		cur = cur->next;
	}

	puts("\n----------------------------------\n");
}


// take input to delete a node
void Remove()
{
	char searchTerm[32];
	getchar();
	printf("Enter the name you want to remove from the list: ");
	gets_s(searchTerm, 32);
	putchar('\n');

	RemoveNode(searchTerm);
	PrintAll();
}


int PrintUI() // display options for main menu and takes a user input(choice from the list of options)
{
	int userChoice;
	do 
	{
		puts("<1> Add\n<2> Search\n<3> Delete\n\n<0> Quit");
		printf(">>> ");
		scanf_s("%d", &userChoice);
		putchar('\n');
	} while (userChoice < 0 || userChoice > 4);
	
	return userChoice;
}


