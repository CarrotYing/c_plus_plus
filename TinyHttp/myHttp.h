#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#define HOME_PAGE "wwwroot"
#define PAGE_404 "404.html"
//创建监听套接字
int startup(char* ip,char* port);
//线程处理函数
void* handle(void * arg);
//辅助线程处理
void _handle(int sock,char* method,char* uri,char* query_string);
//读取报文一行信息
void getbuf(int fd,char* line);
//清空报文头部
void clear_header(int sock);
//处理普通文件
int echo_www(int sock,char* path,int size);
//cgi模式
int exe_cgi(int sock,char* method,char* path,char* content_length,char* query_string);
//错误处理
void show_404(int sock);
void echo_error(int sock,int code);
