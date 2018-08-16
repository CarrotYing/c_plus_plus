#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
using namespace std;
MYSQL* mysql_connect();
void myclose(MYSQL* myfd);
int mysql_select(MYSQL *myfd);
int mysql_insert(MYSQL* myfd,string& name,string& school,string& hobby);
