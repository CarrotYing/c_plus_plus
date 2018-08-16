#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    char method[64];
    char buf[1024];
    int content_length = -1;
    if(getenv("METHOD"))
    {
        strcpy(method,getenv("METHOD"));
        if(strcasecmp(method,"GET")== 0)
        {
            strcpy(buf,getenv("QUERY_STRING"));
        }
        else 
        {
            content_length = atoi(getenv("CONTENT_LENGTH"));
            int i=0;
            for(;i<content_length;i++)
            {
                read(0,buf+i,1);
            }
            buf[i] = '\0';
        }
    }
    strtok(buf,"=&");
    string name = strtok(NULL,"=&");
    strtok(NULL,"=&");
    string school = strtok(NULL,"=&");
    strtok(NULL,"=&");
    string hobby = strtok(NULL,"=&");

    MYSQL* myfd = mysql_connect();
    mysql_insert(myfd,name,school,hobby);
    myclose(myfd);
    return 0;
}
