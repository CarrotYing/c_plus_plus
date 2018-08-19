#pragma once
//引用计数放在头部
#include <string.h>
#include <stdlib.h>
class String
{
public:
    String(const char* ptr="")
    {
        _ptr = new char[strlen(ptr)+2];
        strcpy(_ptr+1,ptr);
        *_ptr = 1;
    }
    ~String()
    {
        if(--(*_ptr) == 0)
        {
            delete[] _ptr;
        }
    }
    String(const String& s)
    {
        _ptr = s._ptr;
        ++(*_ptr); 
    }
    char& operator[](size_t pos)
    {
        CopyOnWrite();
        return _ptr[pos+1];
    }
    const char* c_str()
    {
        return _ptr+1;
    }
    String& operator=(const String& s)
    {
        if(_ptr != s._ptr)
        {
           if(--(*_ptr) == 0)
           {
               delete[] _ptr;
           }
           _ptr = s._ptr;
           ++(*_ptr);
        }
        return *this;
    }
    void CopyOnWrite()
    {
        if(*_ptr > 1)
        {
            --(*_ptr);
            char* tmp = new char[strlen(_ptr)+1];
            strcpy(tmp,_ptr);
            _ptr = tmp; 
            *_ptr = 1;
        }
    }
private:
    char* _ptr;
};
