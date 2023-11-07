#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
int main()
{
	int sockdesc;
	struct sockaddr_in servaddr;
	sockdesc=socket(AF_INET,SOCK_DGRAM,0);
	if(sockdesc==-1)
	{
		printf("Socket not created");
		return -1;
	}

	servaddr.sin_family=AF_INET;
    	servaddr.sin_port=htons(1025);			
    	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	char buffer[10];
	printf("Enter the string to be sent to server: ");
	fgets(buffer,sizeof(buffer),stdin);
	sendto(sockdesc,buffer,strlen(buffer),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	int len=sizeof(servaddr);
	recvfrom(sockdesc,buffer,sizeof(buffer),0,(struct sockaddr *)&servaddr,&len);
	printf("Message from server: %s", buffer);


	close(sockdesc);
	return 0;

}
