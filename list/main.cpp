#include <iostream>
#include "list.h"
using namespace std;

void TestList()
{
    List l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.Print();
    List l2=l;
    l2.Print();
    List l3;
    l3 = l;
    l3.Print();
}
int main()
{
    TestList();
    return 0;
}
