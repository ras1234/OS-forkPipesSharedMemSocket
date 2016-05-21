#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
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
        printf("shmget failed\n");
        exit(1);
    }
    
   // key = ftok("./", 'x');
    shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
    if(shmid<0)
    {
        printf("shmget failed");
        return 1;
    }

    len=atoi(argv[2]);
    printf("%d\n", len);
    shmptr = (struct memory*) shmat(shmid, NULL, 0);
    shmptr->some_text[1]=atoi(argv[1]);
    printf("%d\n",shmptr->some_text[1]);
    shmptr->status=1;
    shmptr->i=0;

   // printf("%d %d %d %d\n",shmptr->some_text[0],shmptr->some_text[1], );
    while(shmptr->i <len-2)
    {   
        while(shmptr->status!=0)
            sleep(1);
        while(shmptr->status==0)
        {   
            printf("Recieved %d from producer\n", shmptr->some_text[1]);
            shmptr->some_text[2] = shmptr->some_text[0] + shmptr->some_text[1];
            printf("Sending %d to producer\n", shmptr->some_text[2]);
            shmptr->some_text[0]= shmptr->some_text[1];
            shmptr->some_text[1]= shmptr->some_text[2];
             
             shmptr->i = shmptr->i +1;
             //printf("incrementing i %d",shmptr->i);
             shmptr->status=1;
           
        }
        if(shmptr->i>len)
            break;
        
           
    } 

    shmdt((void*)shmptr);
     if (shmdt == (void *)-1)
    {
        //printf("shmdt failed\n");
        exit(1);
    }
    shmctl(shmid, IPC_RMID, NULL);

  return 1;
}
