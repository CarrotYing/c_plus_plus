#include "stack.hpp"
int main()
{
    Stack<int> st1;
    st1.PushBack(1);
    st1.PushBack(2);
    st1.PushBack(3);
    st1.PushBack(4);
    int top = st1.GetTop();
    cout<<"top="<<top<<endl;
    st1.PopBack();
    top = st1.GetTop();
    cout<<"top="<<top<<endl;

    Stack<string,list<string> >  st2;
    st2.PushBack("abcd");
    st2.PushBack("efhi");
    string top_string = st2.GetTop();
    cout<<"top_string="<<top_string<<endl;

    return 0;
}
