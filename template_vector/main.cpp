#include <string>
#include "vector.hpp"
using namespace std;
void TestSeqList() 
{ 
    SeqList<string> s2; 
    s2.PushBack("aaaaaaaaaaaaaaaaaaa"); 
    s2.PushBack("bbb"); 
    s2.PushBack("ccc"); 
    s2.PushBack("ddd"); 
    cout<<"深拷贝中的深拷贝:"<<endl;
    s2.Print(); 
    SeqList<string> s1=s2;
    cout<<"拷贝构造：s1:"<<endl;
    s1.Print();

    SeqList<string> s3=s2;
    cout<<"赋值运算符重载：s3:"<<endl;
    s3.Print();
} 

int main()
{
    TestSeqList();
    return 0;
}
