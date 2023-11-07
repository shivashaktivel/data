#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
int main()
{
        int sockdesc;
        struct sockaddr_in servaddr,cliaddr;
        sockdesc=socket(AF_INET,SOCK_STREAM,0);
        if(sockdesc==-1)
        {
                printf("Socket not created");
                return -1;
        }

        servaddr.sin_family=AF_INET;

        servaddr.sin_port=htons(2080);                  // PORT number ranges from 1024 to 49151

        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

        if(bind(sockdesc,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)

        {

                printf("Bind Failed");

                return -1;

        }



        if(listen(sockdesc,5)<0)

        {

                printf("Listen Failed");

                return -1;

        }





        while(1)

        {

                int len=sizeof(cliaddr);

                int connfd=accept(sockdesc,(struct sockaddr*)&cliaddr,&len);

                if (connfd<0)

                {

                        printf("Accept failed");

                        return -1;

                }





                char buffer[50];

                strcpy(buffer," ");

                read(connfd,buffer,50);

                printf("Message received from client: %s", buffer);

                int c=0;

                int i=1;

                int j=1;

                char buffer2[60];

                strcpy(buffer2,"");

                buffer2[0]=buffer[0];

                while(buffer[i]!='\0')

                {

                        if(buffer[i]=='1' && buffer[i-1] == '1')

                                c++;

                        if (buffer[i] == '0')

                                c = 0;

                        buffer2[j]=buffer[i];

                        j++;

                        if(c==4)

                        {

                                buffer2[j]='0';

                                j++;

                                c=0;

                        }

                        i++;



                }

                buffer2[j]='\0';

                write(connfd,buffer2,sizeof(buffer2));



        }



        close(sockdesc);







        return 0;

}