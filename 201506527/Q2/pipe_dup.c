#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{	
	char str1[1000];
	strcpy(str1,argv[1]);
	char *pch1[1000],*pch2[1000],*pch3[1000];
	int i=0;
	pch1[i]=strtok(str1,"|");
	while(pch1[i]!=NULL)
	{	
		i++;
		pch1[i]=strtok(NULL,"|");

	} 

	i=0;
	pch2[i]=strtok(pch1[i]," ");
	while(pch2[i]!=NULL)
	{
		i++;
		pch2[i]=strtok(NULL," ");

	}
	i=0;
	pch3[0]=strtok(pch1[1]," ");
	while(pch3[i]!=NULL)
	{
		i++;
		pch3[i]=strtok(NULL," ");

	}

	int status;
	int pfd[2];
	pid_t cpid;
	if(pipe(pfd)<0)
	{
		printf("error:pipe\n");
		exit(1);
	}
	cpid=fork();
	if(cpid==0)
	{
	
		close(pfd[1]);
		dup2(pfd[0],0);
		execvp(*pch3,pch3);
		printf("error in exec\n");
		
		exit(0);
	}
	else if(cpid >0)
	{
	
		close(pfd[0]);
		dup2(pfd[1],1);
		execvp(*pch2,pch2);
		printf("error in exec\n");
		close(pfd[1]);
		close(1);
		wait(&status);
	}
	else
	{
		printf("error\n");
		exit(1);
	}  
	return 0;
}
	 
	