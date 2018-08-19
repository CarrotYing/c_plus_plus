#include <iostream>
#include "string1.h"
using namespace std;
int main()
{
    String s1;
    s1 = "Hello World!";
    cout<<"s1:";
    cout<<s1.c_str()<<endl;
    String s2 = s1;//拷贝构造
    cout<<"拷贝构造s2:";
    cout <<s2.c_str()<<endl;
    String s3;
    s3 = s2;//赋值运算符重载
    cout<<"赋值运算符重载s3:";
    cout<<s3.c_str()<<endl;
    return 0;
}
