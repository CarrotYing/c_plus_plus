#include <iostream>
#include <string>
#include <new>
#include "alloc.h"
#include "list.h"
#include <time.h>
void TestList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);

	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		std::cout << *it << " ";
		++it;
	}

	std::cout << std::endl;
}

int main(int argc, char** argv) {
	TestList();
	return 0;
}
