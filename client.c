#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
unsigned short port=50000;

int main()
{
    int cfp;
    int recbytes;
    int sin_size;
    char buffer[2000]={0};
    struct sockaddr_in s_add,c_add;
    cfp=socket(AF_INET,SOCK_STREAM,0);
    if(cfp==-1){
        printf("gg");
        return -1;
    }
    memset(&s_add,0,sizeof(struct sockaddr_in));
    s_add.sin_family=AF_INET;
    s_add.sin_addr.s_addr=inet_addr("127.0.0.1");
    s_add.sin_port=htons(port);
    while(1){
        if(-1==connect(cfp,(struct sockaddr *)(&s_add),sizeof(struct sockaddr))){
        printf("fail connect to service");
        return 1;
    }
    char sen[20];
    scanf("%s",sen);
    send(cfp,sen,strlen(sen),0);
    recbytes=read(cfp,buffer,2000);
    printf("%s\n",buffer);
    close(cfp);}
    return 0;
}
