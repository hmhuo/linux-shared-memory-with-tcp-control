#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
 
#include <sys/types.h>     
#include <sys/ipc.h>     
#include <sys/shm.h>     
#include <stdio.h>     

#define INET_ADDR_STR_LEN   1024
#define MAX_LINE 100
 
#define BUF_SIZE 1024     
#define MYKEY 25     

int main(int argc,char **argv)
{
    struct sockaddr_in sin;
    struct sockaddr_in cin;
    int l_fd;
    int c_fd;
    socklen_t len;
    char buf[MAX_LINE];
    char addr_p[INET_ADDR_STR_LEN];
    int port = 8000;
    int n;
    bzero(&sin , sizeof(sin));
     



    int shmid;    
    char * shmptr;    
    
    if((shmid = shmget(MYKEY,BUF_SIZE,IPC_CREAT)) ==-1)    
    {    
    printf("shmget error!\n");    
    exit(1);    
    }    
    
    if((shmptr = shmat(shmid,0,0)) == (void *)-1)    
    {    
    printf("shmat error!\n");    
    exit(1);    
    }    








    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);
     
    if((l_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("fail to create socket");
        exit(1);
    }
    if(bind(l_fd,(struct sockaddr *)&sin ,sizeof(sin) ) == -1) 
    {
        perror("fail to bind");
        exit(1);
    }
     
    if(listen(l_fd,10) == -1)
    {
        perror("fail to listen");
        exit(1);
    }
    printf("waiting.....\n");
    while(1)
    {
        if((c_fd = accept(l_fd,(struct sockaddr *)&cin, &len)) == -1)
        {
            perror("fail to accept");
            exit(1);
        }
         
        n = recv(c_fd , buf, MAX_LINE, 0);
        if(n == -1)
        {
            perror("fail to recv");
            exit(1);
        }
        else if(n == 0)
        {
            printf("the connect has been closed\n");
            close(c_fd);
            continue;
        }
        inet_ntop(AF_INET,&cin.sin_addr,addr_p,sizeof(addr_p));
        printf("content is : %s\n",buf);
         

        // printf("input:");  
        //shmptr = buf;
        strcpy(shmptr,buf);
        //scanf("%s",shmptr);    


        n = strlen(buf);
        sprintf(buf,"%d",n);
         
        n = send(c_fd , buf, sizeof(buf) + 1 , 0);
        if( n == -1)
        {
            perror("fail to send");
            exit(1);
        }
        if(close(c_fd) == -1)
        {
            perror("fail to close");
            exit(1);
        }
    }
    if(close(l_fd) == -1)
    {
        perror("fail to close");
        exit(1);
    }
    return 0;
}