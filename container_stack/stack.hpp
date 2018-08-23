#include <list>
#include <vector>
#include <stdlib.h>
#include <iostream>
using namespace std;

template <class T,class Container = vector<T> >
class Stack
{
public:
    Stack()
         :_con(Container())
    {}
    ~Stack()
    {}
    Stack(const Stack& s)
    {
        _con = s._con;
    }
    Stack& operator=(Stack s)
    {
        swap(_con,s._con);
    }
    void PushBack(const T& value)
    {
        _con.push_back(value);
    }
    void PopBack()
    {
        _con.pop_back();
    }
    T GetTop()
    {
        return _con.back();
    }
    bool Empty()
    {
        return _con.empty();
    }
private:
    Container _con;
};
