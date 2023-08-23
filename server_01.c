#include<sys/socket.h>
#include<stdio.h>
int main(){

  if (fd = socket(AF_INET, SOCK_STREAM, 0) == -1 ){// after tesing Inet I shuld test local sockets
    perror("I am sorry:");
      exit(1);
  }
  struct sockaddr address = {AF_,
			     sdf};
  bind(fd, , );
  
    return 0;
}
