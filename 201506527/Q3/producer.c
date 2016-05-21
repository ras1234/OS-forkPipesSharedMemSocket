#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

struct memory
{
int status;
int some_text[3];
int i;
};

int main(int argc, char *argv[])
{
    int shmid,len;
    key_t key;
    key=3456;
    struct memory *shmptr;
    if(argc<3)
    {
        printf("Error\n");
        exit(1);
    }
    
    //key = ftok("./", 'x');
    shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
    if(shmid<0)
    {
        printf("shmget failed");
        exit(1);
    
   }
    shmptr = (struct memory*) shmat(shmid, NULL, 0);
    if (shmptr == (struct memory *) -1) 
    {
        printf("shmat failed");
        exit(1);
    }
    shmptr->status=6;
    len=atoi(argv[2]);
    shmptr->some_text[0]=atoi(argv[1]);
    printf("%d %d\n",shmptr->some_text[0],atoi(argv[1]));
    shmptr->i=0;
    	
    
            
    	
    	while(shmptr->i <len-2)
    	{  

    		while(shmptr->status!=1)
    		sleep(1);
    	while(shmptr->status==1)
        {		//printf("%d",shmptr->i);
                printf("Recieved %d from consumer\n", shmptr->some_text[1]);
                shmptr->some_text[2] = shmptr->some_text[0] + shmptr->some_text[1];
                printf("Sending %d to consumer\n", shmptr->some_text[2]);
                shmptr->some_text[0] = shmptr->some_text[1];
                shmptr->some_text[1] = shmptr->some_text[2];
                shmptr->i = shmptr->i + 1;
                printf("incrementing i %d",shmptr->i);
                shmptr->status=0;

        }
        if(shmptr->i>len)
            break;
        
    }
    


    shmdt((void *)shmptr);
    if (shmdt == (void *)-1)
    {
        printf("shmdt failed\n");
        exit(1);
    }
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
       // printf("failed to delete\n");
        exit(1); 

    }

    return 0;
}

