#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>     
#include <sys/shm.h>     

#define BUF_SIZE 1024     
#define MYKEY 25     


#define TEXT_SZ 2048

struct shared_use_st {
    int speed;
    int dir;
    char some_text[TEXT_SZ];
};  





int main(int argc, char **argv)
{





    int shmid;    
    
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;

    if((shmid = shmget(MYKEY,sizeof(shared_stuff),IPC_CREAT)) ==-1)    
    {    
    printf("shmget error!\n");    
    exit(1);    
    }    
    
    if((shared_stuff = shmat(shmid,0,0)) == (void *)-1)    
    {    
    printf("shmat error!\n");    
    exit(1);    
    }    














    printf("Welcome! This is a UDP server, I can only received message from client and reply with same message\n");
    char* port = "8000";
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);


    int sock;
    if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(1);
    }
    char buff[512];
    struct sockaddr_in clientAddr;
    int n;
    int len = sizeof(clientAddr);
    int i4speed;
    int i4dir;


    char *u1conf; 
    char *u1dir;  
    char *u1speed;


    u1conf  =   (char*)malloc(sizeof(char) *4);
    u1dir   =   (char*)malloc(sizeof(char) *6);
    u1speed =   (char*)malloc(sizeof(char) *5);

    while (1)
    {
        n = recvfrom(sock, buff, 511, 0, (struct sockaddr*)&clientAddr, &len);
        if (n>0)
        {
            buff[n] = 0;
            printf("%s %u says: %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buff);


            
            memcpy(u1conf,buff,3);
            u1conf[3] =0;

            memcpy(u1dir,buff+3,5);
            u1dir[5] =0;

            memcpy(u1speed,buff+8,4);
            u1speed[5] =0;


            printf("u1conf:%s\n",u1conf);
            printf("u1dir:%s\n",u1dir);
            printf("u1speed:%s\n",u1speed);
            i4dir   = atoi(u1dir);
            i4speed = atoi(u1speed);

            printf("i4dir:%d,i4speed:%d\n",i4dir,i4speed);



            shared_stuff->speed=i4speed;
            shared_stuff->dir=i4dir;
            memcpy(shared_stuff->some_text,u1conf,4);




        }
        else
        {
            perror("recv");
            break;
        }
    }
    return 0;
}
