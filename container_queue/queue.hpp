#include <list>
#include <stdlib.h>
#include <iostream>
using namespace std;

template <class T,class Container = list<T> >
class Queue
{
public:
    Queue()
        :_con(Container())
    {}
    ~Queue()
    {}
    Queue(const Queue& q)
    {
        _con = q._con;
    }
    Queue operator=(Queue q)
    {
        swap(_con,q._con);
    }
    void PushBack(const T& value)
    {
        _con.push_back(value);
    }
    void PopFront()
    {
        _con.pop_front();
    }
    T GetTop()
    {
        return _con.front();
    }
    bool Empty()
    {
        return _con.empty();
    }
private:
    Container _con;
};
