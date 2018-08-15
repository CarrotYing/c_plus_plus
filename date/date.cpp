#include <iostream>
#include "date.h"
using namespace std;
Date& Date::operator=(const Date& d)
{
    if(!IsValid()){
        cout<<"error date"<<endl;
    }    
    if(this!=&d)
    {
       _year=d._year;
       _month=d._month;
       _day=d._day;
    }
    return *this;
}

Date& Date::operator+=(int day)
{
    if(day<0){
        return *this-=-day;
    }
    _day+=day;
    while(_day>GetMonthDay()){
        _day-=GetMonthDay();
        ++_month;
        if(_month>12){
            _month=1;
            _year++;
        }
    }
    return *this;
}
Date Date::operator+(int day)
{
    Date ret(*this);
    return ret+=day;
}
Date& Date::operator-=(int day)
{
    if(day<0){
        return *this+=-day;
    }
    _day-=day;
    while(_day<=0){
        --_month;
        if(_month<1){
            --_year;
            _month=12;
        }
        _day+=GetMonthDay();
    }
    return *this;
}
Date Date::operator-(int day)
{
    Date ret(*this);
    return ret-=day;
}
int Date::operator-(const Date& d)
{
    Date max=*this;
    Date min=d;
    int flag=1;
    if(min>max){
        swap(max,min);
        flag=-1;
    }
    int n=0;
    while(min<max){
        n++;
        min++;
    }
    return flag*n;
}
Date& Date::operator ++(){
    _day++;
    if(_day>GetMonthDay()){
        _day=1;
        _month++;
        if(_month>12){
            _month=1;
            _year++;
        }
    }
    return *this;
}
Date Date::operator ++(int){
    Date ret=*this;
    ++(*this);
    return ret;
}

Date& Date::operator --(){
    _day--;
    if(_day<=0){
        _month--;
        if(_month<=0){
            _year--;
            _month=12;
        }
        _day=GetMonthDay();
    }
    return *this;
}
Date Date::operator --(int){
    Date ret(*this);
    --(*this);
    return ret;
}
bool Date::operator >(const Date& d){
    if(!d.IsValid())
        return false;
    if(_year>d._year){
        return true;
    }
    else if(_year==d._year){
        if(_month>d._month)
            return true;
        else if(_month==d._month){
            if(_day>d._day)
                return true;
        }
    }
    return false;
}
bool Date::operator ==(const Date& d)
{
    if(!d.IsValid())
        return false;
    if(_year==d._year&&_month==d._month&&_day==d._day){
        return true;
    }
    return false;
}
bool Date::operator <(const Date& d){
    return !(*this>=d);
}
bool Date::operator !=(const Date& d){
    return !(*this==d);
}
bool Date::operator >=(const Date& d){
    return *this>d&&*this==d;
}
bool Date::operator <=(const Date& d){
    return !(*this>d);
}
