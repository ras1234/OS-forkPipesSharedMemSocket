#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
 #include <netdb.h>
#include <fcntl.h>

int main(int argc ,char *argv[])
{
	int sockfd,portno,bytes_recieved;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[2000];
	if(argc<3)
	{
		printf("Error");
		exit(1);
	}
	portno=atoi(argv[2]);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Error");
	}
	server=gethostbyname(argv[1]);
	if(server==NULL)
	{
		printf("Error");
		exit(1);
	}
	bzero((char*) &serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port=htons(portno);
	if(connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("Error connect");
	}

	while(1)
	{
			printf("Type String to send:");
			bzero(buffer,256); 
			fgets(buffer,2000,STDIN);
			send(sockfd, buffer,strlen(buffer), 0); 
			bytes_recieved=recv(sockfd,buffer,1024,0);
    		buffer[bytes_recieved] = '\0';
    		printf("Sum Recieved: = %s\n " ,buffer);
    }

	

return 0;
}