#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h> 
#include <strings.h>



int main(int argc ,char *argv[])
{
	int sockfd,newsockfd,portno,bytes_recieved,i,sum,y;
	socklen_t clilen;
	struct sockaddr_in serv_addr,cli_addr;
	char buffer[256];
	if(argc<2)
	{
		printf("Error");
		exit(1);
	}
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Error");
	}
	bzero((char*) &serv_addr,sizeof(serv_addr));
	portno=atoi(argv[1]);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("Error on bind");
		exit(1);
	}	
	listen(sockfd,3);
	clilen=sizeof(cli_addr);
	newsockfd=accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
	if(newsockfd<0)
	{
		printf("Error on accept");
	}
	while(1)
	{
		bzero(buffer,256);
		bytes_recieved=recv(newsockfd,buffer,1024,0);
    	buffer[bytes_recieved] = '\0';
    	printf("\nString Recieved = %s\n " ,buffer);
    	int string_length=strlen(buffer);
    	sum=0;
    	for(i=0;i<string_length;i++)
    	{	

    		y=(int)buffer[i];
    		sum+=y;
    	}
    	printf("Sum Sent:%d\n",sum);
    	int rem, len = 0, n;
    	n = sum;
		while (n != 0)
    	{
			len++;
        	n /= 10;
    	}

    	for (i = 0; i < len; i++)
   	    {

       		 rem = sum % 10;
			 sum = sum / 10;
        	 buffer[len - (i + 1)] = rem + '0';

    	}
    	buffer[len] = '\0';
		send(newsockfd, buffer,strlen(buffer), 0);
	}	
	
           
	return 0;
}


