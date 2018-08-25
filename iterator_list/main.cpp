#include <string>
#include "list.hpp"

int main()
{
    List<string> s1;
    s1.PushBack("aaa");
    s1.PushBack("bbb");
    s1.PushBack("ccc");
    s1.PushBack("ddd");
    s1.PushBack("eee");
    s1.PushBack("fff");
    List<string>::Iterator it = s1.begin();
    while(it != s1.end())
    {
        cout<<*it<<endl;
        ++it;
    }
    return 0;
}
