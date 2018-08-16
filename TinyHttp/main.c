#include <stdio.h>
#include "myHttp.h"
int status_code = 200;
int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        printf("use:%s port ip\n",argv[0]);
        exit(1);
    }
    startup(argv[2],argv[1]);
    return 0;
}
