#pragma once
#include <stdlib.h>
#include <string.h>
//引用计数写时拷贝
class String
{
private:
    char* _ptr;//字符串
    int* _pcount;//引用计数指针
public:
    String(const char* ptr = "")
    {
        _ptr = new char[strlen(ptr)+1];
        strcpy(_ptr,ptr);
        _pcount = new int(1);
    }
    ~String()
    {
        if(--(*_pcount) == 0)
        {
            delete[] _ptr;
            delete _pcount;
        }
    }
    String(const String& s)
    {
        _ptr = s._ptr;
        _pcount = s._pcount;
        ++(*_pcount);
    }
    String& operator=(const String& s)
    {
        if(_ptr != s._ptr)
        {
            if(--(*_pcount) == 0)
            {
                delete[] _ptr;
                delete _pcount;
            }
            _ptr = s._ptr;
            _pcount = s._pcount;
            ++(*_pcount);
        }
        return *this;
    }
    const char* c_str()
    {
        return _ptr;
    }
    char& operator[](size_t pos)
    {
        CopyOnWrite();
        return _ptr[pos];
    }
    void CopyOnWrite()
    {
        if(*_pcount > 1)
        {
            char* tmp = new char[strlen(_ptr)+1];
            strcpy(tmp,_ptr);
            _ptr = tmp;
            --(*_pcount);
            _pcount = new int(1);
        }
    }
};
