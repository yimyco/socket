#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
int port=50000;
int main()
{
    struct sockaddr_in sin,pin;
	int sin_size;
	int sfp,temp_sin;    //socket handle
	int address_size;
	char buf[2000];
	sfp = socket(AF_INET,SOCK_STREAM,0);
	if(sfp==-1){
		perror("fail open socket");
		return 1;
	}
	memset(&sin,0,sizeof(struct sockaddr_in));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=INADDR_ANY;
	sin.sin_port=htons(port);
	if(bind(sfp,(struct sockaddr *)&sin,sizeof(struct sockaddr))==-1){
		perror("fail to bind");
		return 1;
	}
	if(listen(sfp,20)==-1){
		perror("fail to listen");
		return 1;
	}
	printf("wait to accept");
    while(1){
		temp_sin=accept(sfp,(struct sockaddr *)&pin,&address_size);
		if(temp_sin==-1){
			perror("fail to accept");
			return 1;
		}else{
			printf("hello");
		}
		if(recv(temp_sin,buf,2000,0)==-1){
			perror("fail to recv");
			return 1;
		}
		printf("%s\n",buf);
		printf("please reply client\n");
  		char a[40];
		scanf("%s",a);
		int len=strlen(a);
		if(send(temp_sin,a,len,0)==-1){
			perror("fail sent");
			return 1;
		}
		close(temp_sin);
	}
	return 0;
}
