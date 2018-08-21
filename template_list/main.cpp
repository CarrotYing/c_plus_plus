#include <string>
#include "list.hpp"

int main()
{
    List<string> s1;
    cout<<"Insert:aaaaaaaaaaaaaa"<<endl;
    s1.PushBack("aaaaaaaaaaaaaa");
    s1.Print();
    cout<<"Insert:bbbbbbbbbbbb"<<endl;
    s1.PushBack("bbbbbbbbbbbb");
    s1.Print();
    cout<<"Insert:aaaaaaaaaaaaaaccccccccccccccccccccccccccccc"<<endl;
    s1.PushBack("aaaaaaaaaaaaaaccccccccccccccccccccccccccccc");
    s1.Print();
    s1.PopBack();
    cout<<"尾删一个:"<<endl;
    s1.Print();
    cout<<"头插：ddddddd"<<endl;
    s1.PushFront("ddddddd");
    s1.Print();
    cout<<"头插：eeeee"<<endl;
    s1.PushFront("eeee");
    s1.Print();
    cout<<"头删一个："<<endl;
    s1.PopFront();
    s1.Print();
    List<string> s2=s1;
    cout<<"拷贝构造s2："<<endl;
    s2.Print();
    List<string> s3;
    s3 = s1;
    cout<<"赋值运算符重载s3:"<<endl;
    s3.Print();
    return 0;
}
