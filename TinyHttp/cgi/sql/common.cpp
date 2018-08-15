#include "common.h"
void test()
{
    cout<<"client version: "<<mysql_get_client_info()<<endl;
}

MYSQL* mysql_connect()
{
    MYSQL* myfd = mysql_init(NULL);
    if(mysql_real_connect(myfd,"127.0.0.1","root","","myHttp",3306,NULL,0)==NULL)
    {
        cout<<"connect error"<<endl;
    }
    else 
    {
        cout<<"connect success"<<endl;
    }
    return myfd;
}

int mysql_insert(MYSQL* myfd,string& name,string& school,string& hobby)
{
    string sql="INSERT INTO students (name,school,hobby) VALUES(\"";
    sql += name;
    sql += "\",\"";
    sql += school;
    sql += "\",\"";
    sql += hobby;
    sql += "\")";
    cout<<"注册成功"<<endl;
    return mysql_query(myfd,sql.c_str());
}
int mysql_select(MYSQL *myfd)
{
    string sql = "SELECT * FROM students";
    mysql_query(myfd,sql.c_str());

    MYSQL_RES *result = mysql_store_result(myfd);
    int lines = mysql_num_rows(result);
    int cols = mysql_num_fields(result);
    cout<<"共"<<lines<<"条记录"<<endl;
    MYSQL_FIELD *fields = mysql_fetch_fields(result);
    int i = 0;
    cout<<"<table border=\"1\">"<<endl;
    for(;i<cols;++i)
    {
        cout<<"<th>"<<fields[i].name<<"</th>"<<"\t";
    }
    cout<<endl;
    MYSQL_ROW my_row;
    for(i=0;i<lines;++i)
    {
        cout<<"<tr>"<<endl;
        my_row = mysql_fetch_row(result);
        int j = 0;
        for(;j<cols;++j)
        {
            cout<<"<td>"<<my_row[j]<<"</td>"<<"\t";
        }
        cout<<endl;
        cout<<"</tr>"<<endl;
    }
    cout<<"<table border=\"1\">"<<endl;
//    free(result);
}
void myclose(MYSQL* myfd)
{
    mysql_close(myfd);
}
