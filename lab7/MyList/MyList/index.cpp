#include "stdafx.h"
#include "MyList.h"
#include <list>

typedef int MyInt;
class CExample
{
public:
	CExample(int a)
		: a(a) {};
public:
	int a;
};


int main()
{
	CMyList<CExample> a;
	a.PushBack(CExample(1));
	auto it = a.begin();
	return 0;
}

