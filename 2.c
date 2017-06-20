#include <stdio.h>     
#include <sys/types.h>     
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


int  main()    
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


    
    while(1)    
    {    
    printf("speed:%d,dir:%d, some_text:%s  \n",shared_stuff->speed,shared_stuff->dir,shared_stuff->some_text);    
    sleep(3);    
    }    
    
    exit(0);    
}  
