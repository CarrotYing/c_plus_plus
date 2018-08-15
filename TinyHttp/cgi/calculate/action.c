#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void calculate(int m1,int m2){
    printf("<table border=\"1\" align=\"center\">");
    printf("<tr><td>");
    printf("%d + %d = %d\r\n",m1,m2,m1+m2);
    printf("</td></tr><tr><td>");
    printf("%d - %d = %d\r\n",m1,m2,m1-m2);
    printf("</td></tr><tr><td>");
    printf("%d * %d = %d\r\n",m1,m2,m1*m2);
    printf("</td></tr><tr><td>");
    if(m2==0)
        printf("0不能做除数");
    else
    printf("%d / %d = %d\r\n",m1,m2,m1/m2);
    printf("</td></tr></table>");
}
int main(){
    printf("<h1 align=\"center\">Welcome to my calculate!</h1>");
       // char* method=getenv("METHOD");
//        if(buf!=NULL){
//            printf("METHOD=%s\n",buf);
//        }
//        else printf("METHOD is NULL\n");
       // char* query_string=NULL;
 //       if(buf!=NULL){
 //           printf("QUERY_STRING=%s\n",buf);
 //       }
 //       else printf("QUERY_STRING is NULL\n");
        //char* content_length=NULL;
 //       if(buf!=NULL){
 //           printf("CONTENT_LENGTH=%s\n",buf);
 //       }
 //       else printf("CONTENT_LENGTH is NULL\n");
       // if(strcasecmp(method,"GET")==0){
       //      query_string=getenv("QUERY_STRING");
       // }
       // else if(strcasecmp(method,"POST")==0){
       //     content_length=getenv("CONTENT_LENGTH");
       // }
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
         int m1=0,m2=0;
          sscanf(buf,"number1=%d&number2=%d",&m1,&m2);
          calculate(m1,m2);
    return 0;
}
