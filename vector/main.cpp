#include <iostream>
using namespace std;
#include "vector.h"

void TestVector()
{
    Vector v1;
    v1.PushBack(1);
    v1.Print();
    v1.PushBack(2);
    v1.Print();
    v1.PushBack(3);
    v1.Print();
    v1.PushBack(4);
    v1.Print();
    Vector v2(v1);
    v2.Print();
    v2.PushBack(5);
    v2.Print();
    Vector v3;
    v3 = v1;
    v3.Print();
    v3.PushBack(5);

    v3.Print();

}
int main()
{
    TestVector();
    return 0;
}
