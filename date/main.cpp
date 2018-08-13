#include <iostream>
#include "date.h"
using namespace std;
int main(){
    Date d1(1997,2,28);
    Date d2(d1);
    d1.print();
    d2.print();
    d1++;
    d1.print();
    d2--;
    d2.print();
    d1=d2;
    d1.print();
    (d1+=50).print();
    Date d3(d1);
    d3=d1-200;
    d3.print();
    (d1-=50).print();
}
