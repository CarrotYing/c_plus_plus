#include <string>
#include "vector.hpp"
using namespace std;
void TestSeqList() 
{ 
    SeqList<string> s2; 
    s2.PushBack("aaa");
    s2.PushBack("bbb");
    s2.PushBack("ccc");
    s2.PushBack("ddd");
    s2.PushBack("eee");
    s2.PushBack("fff");
    SeqList<string>::Iterator it = s2.begin();
    while(it != s2.end())
    {
        cout<<*it<<endl;
        it++;
    }
} 

int main()
{
    TestSeqList();
    return 0;
}
