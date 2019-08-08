#pragma once
class CMyNode
{
	friend class CMyList;
public:
	CMyNode();
	virtual ~CMyNode();

	CMyNode* GetNext(void) { return pNext; }

	// interfrace member functions needed for management
	virtual const char* GetKey(void) = 0;
	virtual void PrintNode(void) = 0;

private:
	CMyNode *pNext;

};

