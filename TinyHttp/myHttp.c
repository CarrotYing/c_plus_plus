#include "myHttp.h"
extern int status_code;
int startup(char* ip,char* port)
{
    int listen_sock=socket(AF_INET,SOCK_STREAM,0);
    if(listen_sock<0)
    {
        perror("socket");
        exit(2);
    }
    int opt=1;
    //允许套接口和一个已在使用的地址捆绑
    setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    signal(SIGPIPE,SIG_IGN);//忽略管道信号，防止因为客户端关闭服务器挂掉
    struct sockaddr_in server_socket;
    server_socket.sin_family = AF_INET;//AF_INET ipv4类型地址
    server_socket.sin_addr.s_addr=inet_addr(ip);
    server_socket.sin_port=htons(atoi(port));
    if(bind(listen_sock,(struct sockaddr*)&server_socket,\
               sizeof(struct sockaddr))<0)
    {
        perror("Bind");
        close(listen_sock);    
        exit(3);
    }
    if(listen(listen_sock,5)<0)
    {
        perror("listen");
        close(listen_sock);
        exit(4);
    }
    while(1)
    {
        struct sockaddr_in client_socket;
        socklen_t len=sizeof(client_socket);
        int client_sock=accept(listen_sock,\
                (struct sockaddr*)&client_socket,&len);
        if(client_sock<0)
        {
            continue;
        }
        pthread_t tid=0;
        pthread_create(&tid,NULL,handle,(void*)&client_sock);
        pthread_detach(tid);
    }
    close(listen_sock);
}

void* handle(void* fd)
{
    int sock=*(int*)fd;
    char buf[1024];
    getbuf(sock,buf);
    char *method=strtok(buf," ");
    char *uri=strtok(NULL," ");
    char* query_string=NULL;
    int i=0;
    //将报文首行信息拆分成有效数据
    for(;uri[i]!='\0';i++)
    {
        if(uri[i]=='?')
        {
            uri[i]='\0';
            query_string=&uri[i+1];
            break;
        }
    }
    _handle(sock,method,uri,query_string);
    close(sock);
    return NULL;
}
void _handle(int sock,char* method,char* uri,char* query_string)
{
    if(method==NULL)
    {
        return;
    }
    char buf[1024]={0};
    int cgi=0;
    char content_length[128]={0};
    char path[256]={0};
    if(strcasecmp(method,"GET")==0)
    {
    }
    else if(strcasecmp(method,"POST")==0)
    {
        cgi=1;
        do
        {
            getbuf(sock,buf);
            if(strncmp(buf,"Content-Length: ",16)==0)
            {
                strcpy(content_length,buf+16);
            }
        }while(strcmp(buf,"\n")!=0);
    }
    else 
    {
        clear_header(sock);
        status_code = 400;
        goto end;
    }
    if(query_string!=NULL)
    {
        cgi=1;
    }
    if(strcmp(uri,"/")==0||strcmp(uri,"/favicon.ico")==0)
    {
        sprintf(path,"wwwroot");
    }
    else
    {
        sprintf(path,".%s",uri);
    }
#ifdef DEBUG
    printf("method:%s\npath=%s\ncontent_length=%s\nquery_string=%s\n",\
           method,path,content_length,query_string);
    printf("cgi=%d\n",cgi);
#endif
    struct stat st;
    if( stat(path,&st)<0)
    {
        clear_header(sock);
        status_code=404;
        goto end;
    }
    else if(!(st.st_mode & S_IFDIR)&&
            (st.st_mode & S_IXGRP ||
             st.st_mode & S_IXOTH ||
             st.st_mode & S_IXUSR))
    {
        cgi=1;
    }
    if(cgi==1)
    {
       exe_cgi(sock,method,path,content_length,query_string);
    }
    else if(st.st_mode & S_IFREG)
    {
        status_code = echo_www(sock,path,st.st_size);
    }
    else if(st.st_mode & S_IFDIR)
    {
        strcat(path,"wwwroot");
        printf("dir path=%s\n",path);
        if(stat(path,&st)!=0)
        {
            perror("dir stat");
            status_code = 404;
            goto end;
        }
        else
            status_code = echo_www(sock,path,st.st_size);
    }
end:
    if(status_code != 200)
    {
        echo_error(sock,status_code);
    }
}
void getbuf(int fd,char* line)
{
    if(line==NULL)
    {
        return;
    }
    int i=0;
    char c='a';
    while(c!='\n')
    {
        if(read(fd,&c,1)>0)
        {
            if(c=='\r')
            {
                //窥探一下，因为不确定下一个数据是否要接收
                recv(fd,&c,1,MSG_PEEK);
                if(c=='\n')
                {
                    read(fd,&c,1);
                }
                else 
                {
                    c='\n';
                }
            }
            line[i++]=c;
        }
    }
    line[i]='\0';
}
void clear_header(int sock)
{
    char buf[1024]={0};
    do
    {
        getbuf(sock,buf);
    }while(strcmp(buf,"\n")!=0);
}
int echo_www(int sock,char* path,int size)
{
    char buf[1024];
    printf("echo_www,path=%s\n",path);
    clear_header(sock);
    int fd=open(path,O_RDONLY);
    if(fd < 0)
        return 404;
    sprintf(buf,"HTTP/1.0 200 OK\r\n");
    send(sock,buf,strlen(buf),0);
    sprintf(buf,"Content-Type: text/html;image/jpeg;charset=UTF-8\r\n");
    send(sock,buf,strlen(buf),0);
    sprintf(buf,"\r\n");
    send(sock,buf,strlen(buf),0);
    sendfile(sock,fd,NULL,size);
    close(fd);
    return 200;
}
int exe_cgi(int sock,char* method,char* path,char* content_length,char* query_string)
{
    printf("enter cgi mode\n");
    char buf[256]={0};  
    if(strcasecmp(method,"GET")==0)
    {
        clear_header(sock);
    }
    int input[2];
    int output[2];
    pipe(input);//以孩子的视角命名
    pipe(output);
    pid_t pid = fork();
    if(pid <0)
    {
        return 503;
    }
    else if(pid==0)
    {
        close(input[1]);
        close(output[0]);
        char method_env[128]={0};
        char content_length_env[128]={0};
        char query_string_env[1024]={0};
        sprintf(method_env,"METHOD=%s",method);
        putenv(method_env);
        if(strcasecmp(method,"POST")==0)
        {
            sprintf(content_length_env,"CONTENT_LENGTH=%s",content_length);
            putenv(content_length_env);
        }
        else if(strcasecmp(method,"GET")==0)
        {
            sprintf(query_string_env,"QUERY_STRING=%s",query_string);
            putenv(query_string_env);
        }
        dup2(input[0],0);
        dup2(output[1],1);
        if(execl(path,path,NULL)==-1)
        {
            perror("execl");
            exit(8);
        }
    }
    else
    {
        close(input[0]);
        close(output[1]);
        char c;
        if(strcasecmp(method,"POST") == 0)
        {
            int i = 0;
            printf("content_length = %d\n",atoi(content_length));
            //读取post参数，通过管道传送至cgi程序
            for(; i <atoi(content_length) ;i++)
            {
                recv(sock,&c,1,0);
                write(input[1],&c,1);
            }
        }
        sprintf(buf,"HTTP/1.0 200 0K\r\n");
        send(sock,buf,strlen(buf),0);
        sprintf(buf,"Content-Type: text/html;image/jpeg;charset=UTF-8\r\n");
        send(sock,buf,strlen(buf),0);
        sprintf(buf,"\r\n");
        send(sock,buf,strlen(buf),0);
        //读取子进程返回的数据，发送给客户端
        while(read(output[0],&c,1) >0)
        {
            send(sock,&c,1,0);
        }
        waitpid(pid,NULL,0);
    }
    return 200;
}
void show_404(int sock)
{
    char line[1024];
    sprintf(line,"HTTP/1.0 404 Not Found\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"Content-Type: text/html;image/jpeg;charset=UTF-8\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"\r\n");
    send(sock,line,strlen(line),0);
    struct stat st;
    stat(PAGE_404,&st);
    int fd = open(PAGE_404,O_RDONLY);
    sendfile(sock,fd,NULL,st.st_size);
}
void echo_error(int sock,int code)
{
    //待补充
    show_404(sock);
}
