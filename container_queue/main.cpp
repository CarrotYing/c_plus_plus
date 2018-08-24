#include "queue.hpp"

int main()
{
    Queue<string> q1;
    q1.PushBack("aaa");
    q1.PushBack("bbb");
    q1.PushBack("ccc");
    q1.PushBack("ddd");
    string top;
    top = q1.GetTop();
    cout<<"top="<<top<<endl;
    q1.PopFront();
    top = q1.GetTop();
    cout<<"top="<<top<<endl;
    return 0;
}
