#include <iostream>
#include "string.h"
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
    s1.Insert(0,'H');//头部插入
    cout<<"头部插入H:";
    cout<<s1.c_str()<<endl;
    s1.Erase(2);//删除
    cout<<"删除e：";
    cout<<s1.c_str()<<endl;
    int ret = s1.Find("Hello");
    if(ret!=-1)
    {
        cout<<"查找Hello:";
        cout<<ret<<endl;
    }
    s1+=' ';
    s1+='H';//重载+= 单个字符
    cout<<"+=H ：";
    cout<<s1.c_str()<<endl;
    cout<<"+= ello:";//重载+= 字符串
    s1+="ello";
    cout<<s1.c_str()<<endl;
    String s4;
    s4 = s1+" World";//重载+
    cout<<"s1+\" World\" s4:";
    cout<<s4.c_str()<<endl;
    return 0;
}
