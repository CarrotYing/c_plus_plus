#pragma once
#include <string.h>
#include <iostream>
#include <assert.h>
using namespace std;
class String
{
public:
    String(const char* ptr="")
        :_size(strlen(ptr))
    {
        _capacity = _size;
        _ptr = new char[_size+1];
        strcpy(_ptr,ptr);
    }
    ~String()
    {
        if(_ptr)
        {
            delete[] _ptr;
        }
    }
    //传统写法
    /*
    String(const String& s)
    {
        _size = strlen(s._ptr);
        _capacity = _size;
        _ptr = new char[_size+1];
        strcpy(_ptr,s._ptr);
    }
    String& operator=(const String& s)
    {
        if(this != &s)
        {
            _size = strlen(s._ptr);
            _capacity = _size;
            char* tmp = new char[_size+1];
            strcpy(tmp,s._ptr);
            delete _ptr;
            _ptr = tmp;
        }
        return *this;
    }
    */
    //现代写法
    void Swap(String& s)
    {
        swap(_ptr,s._ptr);
        swap(_size,s._size);
        swap(_capacity,s._capacity);
    }
    String(const String& s)
        :_ptr(NULL)
    {
        String tmp(s._ptr);
        Swap(tmp);
    }

    String& operator=(String s)
    {
        Swap(s);
        return *this;
    }
    const char* c_str()
    {
        return _ptr;
    }
    char& operator[](size_t pos)
    {
        return _ptr[pos];
    }
    void Reserve(size_t n)
    {
        Expand(n);
    }
    void PushBack(const char* str)
    {
        Insert(_size,str);
    }
    void PushBack(char ch)
    {
        Insert(_size,ch);
    }
    void PopBack()
    {
        Erase(_size-1);
    }
    size_t Find(char ch)
    {
        size_t i=0;
        for(;i<_size;++i)
        {
            if(_ptr[i] == ch)
            {
                return i;
            }
        }
        return -1;
    }
    size_t Find(const char* str)
    {
        if(str == NULL)
        {
            return -1;
        }
        size_t len=strlen(str);
        size_t i=0;
        //这里理解为i是单词的第一个下标，即0，因此最后一个字母的下标是len-1
        for(;i+len-1<_size;++i)
        {
            if(strncmp(_ptr+i,str,len)==0)
                return i;
        }
        return -1;
    }
    void Insert(size_t pos,const char* str)
    {
        assert(pos<=_size);
        if(str == NULL)
            return;
        size_t len = strlen(str);
        if(_size+len > _capacity)
        {
            Reserve(_size+len);
        }
        size_t end = _size;
        for(;end>=pos;--end)
        {
            _ptr[end+len] = _ptr[end];
        }
        strncpy(_ptr+pos,str,len);
        _size += len;
    }
    void Insert(size_t pos,char ch)
    {
        assert(pos<=_size);
        if(_size == _capacity)
        {
            Reserve(_capacity * 2);
        }
        int i=_size;
        for(;i>=(int)pos;--i)
        {
            _ptr[i+1] = _ptr[i];
        }
        _ptr[pos] = ch;
        _size++;
    }
    void Erase(size_t pos,size_t n=1)
    {
        assert(pos <= _size);
        size_t i=pos;
        for(;i+n<=_size;++i)
        {
            _ptr[i]=_ptr[i+n];
        }
        _size -= n;
    }
    String& operator+=(char ch)
    {
        PushBack(ch);
        return *this;
    }
    String operator+(char ch)
    {
        String tmp(*this);
        tmp+=ch;
        return tmp;
    }
    String& operator+=(const char* str)
    {
        PushBack(str);
        return *this;
    }
    String operator+(const char* str)
    {
        String tmp(*this);
        tmp+=(str);
        return tmp;
    }

    bool operator>(String& s)
    {
        return strcmp(_ptr,s._ptr)>0;
    }
    bool operator==(String& s)
    {
        return strcmp(_ptr,s._ptr)==0;
    }
    bool operator>=(String& s)
    {
        return (*this)>s || (*this)==s;
    }
    bool operator!=(String& s)
    {
        return !((*this)==s);
    }
    bool operator<(String& s)
    {
        return !((*this)>=s);
    }
    bool operator<=(String& s)
    {
        return !((*this)>s);
    }
private:
    char* _ptr;
    size_t _size;
    size_t _capacity;
    void Expand(size_t n)
    {
        if(n > _size)
        {
            char* tmp = new char[n+1];
            strcpy(tmp,_ptr);
            delete[] _ptr;
            _ptr = tmp;
            _capacity = n;
        }
    }
};
