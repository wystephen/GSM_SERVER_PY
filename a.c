/*
 * main.cpp
 * TCP客户端信息转发
 * Author: Yayi
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/wait.h>
 
#define WAITBUF 10
int main(int argc, char *argv[])
{
	int sockfd,clientnub,client2nub;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr,client2_addr;
	socklen_t sin_size;
	char serverlog0[1024] = {0};
	char serverlog1[1024] = {0};
	char serverlog2[1024] = {0};
	time_t timep;
	struct tm *p;
 
	/*服务器端开始建立socket描述符*/
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
        fprintf(stderr,"Socket error:%s\n",strerror(errno));
        exit(1);
	}
 
	/*服务器端填充 sockaddr结构*/
	bzero(&server_addr,sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
 
	/*自动填充主机IP*/
 	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 	server_addr.sin_port=htons(8888);
 
 	/*捆绑sockfd描述符*/
 	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
 	{
        	fprintf(stderr,"Bind error:%s\n",strerror(errno));
        	exit(1);
	}
 
	/*监听sockfd描述符*/
	if(listen(sockfd, WAITBUF)==-1)
	{
    	    fprintf(stderr,"Listen error:%s\n",strerror(errno));
    	    exit(1);
	}
 
	/*等待客户端链接*/
	printf("Wait for link");
        sin_size=sizeof(struct sockaddr_in);
        clientnub=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size);
 
        /*日志格式化*/
    	time(&timep);
    	p = gmtime(&timep);
 
	sprintf(serverlog0,"[%d.%d.%d", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
	sprintf(serverlog1," %d:%d:%d] ", p->tm_hour, p->tm_min, p->tm_sec);
	sprintf(serverlog2,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));
 
	FILE* file = fopen("tcpserver.log","a+");
	fwrite(serverlog0,1,strlen(serverlog0),file);
	fwrite(serverlog1,1,strlen(serverlog1),file);
	fwrite(serverlog2,1,strlen(serverlog2),file);
	fclose(file);
 
	/*发送链接"OK\n"信号*/
	send(clientnub,"OK\n",strlen("OK\n"),0);
	
 
	/*等待客户端2链接*/
	//sin_size=sizeof(struct sockaddr_in);
	//client2nub=accept(sockfd,(struct sockaddr *)(&client2_addr),&sin_size);
        /*日志格式化*/
    	//time(&timep);
    	//p = gmtime(&timep);
 
 
	//sprintf(serverlog0,"[%d.%d.%d", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
	//sprintf(serverlog1," %d:%d:%d] ", p->tm_hour, p->tm_min, p->tm_sec);
	//sprintf(serverlog2,"Server get connection from %s\n",inet_ntoa(client2_addr.sin_addr));
 
	//file = fopen("tcpserver.log","a+");
	//fwrite(serverlog0,1,strlen(serverlog0),file);
	//fwrite(serverlog1,1,strlen(serverlog1),file);
	//fwrite(serverlog2,1,strlen(serverlog2),file);
	//fclose(file);
 
	/*发送链接"OK\n"信号*/
	//send(client2nub,"OK\n",strlen("OK\n"),0);
 
	 while(1)
 	{
		char recv_send_data[1024]={0};
		/*把客户端2接收转发客户端*/
		//if((recv(client2nub,recv_send_data,1024,0))>0)
			//send(clientnub,recv_send_data,strlen(recv_send_data),0);
		/*把客户端接收转发客户端2*/
		if((recv(clientnub,recv_send_data,1024,0))>0)
			printf("%1.1024s\n",recv_send_data);			//send(client2nub,recv_send_data,strlen(recv_send_data),0);
 	}
 	close(sockfd);
 	exit(0);
}
