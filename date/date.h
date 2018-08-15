#pragma once
#include<iostream>
using namespace std;

class Date{
    public:
        Date(size_t year=1990,size_t month=1,size_t day=1)
            :_year(year)
             ,_month(month)
             ,_day(day)
        {
            cout<<"Date()\n";
        }
       ~Date()
       {
            cout<<"~Date()\n";
       }
       Date(const Date& d)
       { 
           cout<<"Date(const &)\n";
           _year=d._year;
           _month=d._month;
           _day=d._day;
       }
       int GetMonthDay()const
       {
           if(_year<1990 || _month <1 || _month >13)
           {
               return -1;
           }
           int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
           int day=days[_month];
           if(_month==2 && 
              ((_year%4==0&&_year%400!=0)||_year%400==0))
                return ++day;
           else return day;
       }
       int GetMonthDay()
       {
           if(_year<1990 || _month <1 || _month >13)
           {
               return -1;
           }
           int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
           int day=days[_month];
           if(_month==2 && 
              ((_year%4==0&&_year%400!=0)||_year%400==0))
                return ++day;
           else return day;
       }
       bool IsValid()const
       {
           if(_year<1900||
              _month<0 || _month>12 || 
              _day<0 ||_day>GetMonthDay())
               return 0;
           return 1;
       }
       bool IsValid()
       {
           if(_year<1900||
              _month<0 || _month>12 || 
              _day<0 ||_day>GetMonthDay())
               return 0;
           return 1;
       }
       Date& operator=(const Date& d);
       Date& operator+=(int day);
       Date operator+(int day);
       Date& operator-=(int day);
       Date operator-(int day);
       int operator -(const Date& d);
       Date& operator ++();
       Date operator ++(int);
       Date& operator --();
       Date operator --(int);
       bool operator >(const Date& d);
       bool operator <(const Date& d);
       bool operator ==(const Date& d);
       bool operator !=(const Date& d);
       bool operator >=(const Date& d);
       bool operator <=(const Date& d);
       void print(){
           cout<<"year="<<_year<<"month="<<_month<<"day="<<_day<<endl;
       }
    private:
        int _year;
        int _month;
        int _day;
};
