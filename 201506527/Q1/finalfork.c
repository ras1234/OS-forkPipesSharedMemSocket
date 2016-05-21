#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{	
  pid_t pid;
	long int i,j;
  long int row_count,column_count;
	scanf("%ld  %ld",&row_count,&column_count);
	long int array[row_count][column_count];
  long int k,sum;
	
	for(i=0;i<row_count;i++)
	{
		for(j=0;j<column_count;j++)
		{
			scanf("%ld", &array[i][j]);
		}
		
	}

	for ( i = 0; i < row_count; i++)
	{	

    		pid=fork();
    		if (pid < 0) 
			  {
          		printf("Failed to fork process 1\n");
          		exit(1);
        }
      	else if(pid==0)
      	{	
           exit(0);
        }
        else
        {

            pid=getpid();
            sum=0;
            for (k = 0; k <column_count; k++) 
            {
                sum+=array[i][k];
            }
             printf("Child pid:%d ,sum of row:%ld is:%ld\n",getpid(),row_count,sum);
        }

      		
  }
	
	return 0;
}

