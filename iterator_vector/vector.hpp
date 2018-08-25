#include <stdlib.h>
#include <iostream>
using namespace std;
template<class T>
class SeqList
{
public:
    typedef T* Iterator;
    typedef const T* ConstIterator;
    Iterator begin()
    {
        return _a;
    }
    Iterator end()
    {
        return _a+_size;
    }
    ConstIterator begin()const
    {
        return _a;
    }
    ConstIterator end()const
    {
        return _a+_size;
    }
public:
    SeqList()
        :_a(NULL)
         ,_size(0)
         ,_capacity(0)
    {}
    ~SeqList()
    {
        if(_a)
        {
            delete[] _a;
        }
        _a = NULL;
        _size = _capacity = 0;
    }
    SeqList(const SeqList& s)
    {
        _size = s._size;
        _a = new T[_size];
        size_t i = 0;
        for(;i<_size;++i)
        {
            _a[i] = s._a[i];
        }
        _capacity = _size;
    }
    SeqList& operator=(SeqList s)
    {
        swap(this->_a,s._a);
        swap(this->_size,s._size);
        swap(this->_capacity,s._capacity);
        return *this;
    }

    void Insert(size_t pos,const T& value)
    {
        if(_size == _capacity)
        {
            ReServe(_capacity*2 + 1);
        }
        if(pos > _size)
            return;
        size_t i = _size;
        for(;i>pos;++i)
        {
            _a[i] = _a[i-1];
        }
        _a[pos] = value;
        _size++;
    }
    void Erase(size_t pos)
    {
        size_t i=pos+1;
        for(;i<_size;++i)
        {
            _a[i-1] = _a[i];
        }
        _size--;
    }
    void PushBack(const T& value)
    {
        Insert(_size,value);
    }
    void PopBack()
    {
        Erase(_size-1);
    }

    void ReSize(size_t n,const T& value)
    {
        if(n<_size)
        {
            _size = n;
        }
        else if(n>_size)
        {
            Expand(n);
            size_t i=_size;          
            for(;i<n;++i)
            {
                _a[i] = value;
            }
        }
    }
    void ReServe(size_t n)
    {
        Expand(n);
    }
    size_t Find(const T& value)
    {
        size_t i=0;
        for(;i<_size;++i)
        {
            if(_a[i] == value)
                return i;
        }
        return -1;
    }
    char* c_str()
    {
        return _a;
    }
    T& operator[](size_t pos)
    {
        return _a[pos];
    }
    void Print()
    {
        size_t i = 0;
        for(;i<_size;++i)
        {
            cout<<_a[i]<<endl;
        }
    }
private:
    T* _a;
    size_t _size;
    size_t _capacity;
    void Expand(size_t n)
    {
        if(n > _size)
        {
            T* tmp = new T[n];
            size_t i=0;
            for(;i<_size;++i)
            {
                tmp[i] = _a[i];
            }
            delete[] _a;
            _a = tmp;
            _capacity = n;
        }
    }
};
