#pragma once
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <algorithm>
typedef int DataType;
class Vector
{
public:
    Vector()
        :_first(NULL)
         ,_finish(NULL)
         ,_endofstorage(NULL)
    {}

    ~Vector()
    {
        if(_first)
        {
            delete[] _first;
        }
        _first = _finish = _endofstorage = NULL;
    }

    Vector(const Vector& v)
    {
        size_t size = v.Size();
        _first = new DataType[size];
        if(_first)
        {
            memcpy(_first,v._first,sizeof(DataType)*size);
        }
        _finish = _first + size;
        _endofstorage = _first + size;
    }

    Vector& operator=(Vector v)
    {
        swap(_first,v._first);
        swap(_finish,v._finish);
        swap(_endofstorage,v._endofstorage);
        return *this;
    }
    void ReSize(size_t n,DataType value)
    {
        if(n<Size())
        {
            _finish = _first + n;
        }
        else 
        {
            Expand(n);
            size_t i=Size();
            for(;i<n;++i)
            {
                _first[i] = value;
            }
        }
    }
    void Reserve(size_t n)
    {
        Expand(n);
    }
    void PushBack(DataType value)
    {
        Insert(Size(),value);
    }
    void PopBack()
    {
        Erase(Size()-1);
    }

    size_t Find(DataType value)
    {
        size_t i=0;
        for(;i<Size();++i)
        {
            if(_first[i] == value)
            {
                return i;
            }
        }
        return -1;
    }
    void Insert(size_t pos,DataType value)
    {
        if(_finish == _endofstorage)
        {
            size_t newcapa = Capacity()==0 ? 3:Capacity()*2;
            Expand(newcapa);
        }
        DataType* end = _finish-1;
        while(end > _first+pos)
        {
            *(end+1) = *end;
            --end;
        }
        *(_first+pos)=value;
        ++_finish;
    }
    void Erase(size_t pos)
    {
        if(pos >= Size())
        {
            return ;
        }
        DataType* start = _first+pos;
        while(start< _finish-1)
        {
            *start=*(start+1);
            ++start;
        }
        --_finish;
    }
    size_t Size()const
    {
        return _finish-_first;
    }
    size_t Capacity()const
    {
        return _endofstorage-_first;
    }
    void Print()
    {
        size_t i=0;
        for(;i<Size();++i)
        {
            cout<<_first[i]<<" ";
        }
        cout<<endl;
        cout<<"Size="<<Size()<<" "<<"Capacity="<<Capacity()<<endl;
    }
private:
    DataType* _first;
    DataType* _finish;
    DataType* _endofstorage;
    void Expand(size_t n)
    {
        size_t size = Size();
        if(n > size)
        {
            DataType* tmp = new DataType[n];
            if(_first)
            {
                memcpy(tmp,_first,sizeof(DataType)*size);
                delete[] _first;
            }
            _first = tmp;
            _finish = _first + size;
            _endofstorage = _first + n;
        }
    }
};

