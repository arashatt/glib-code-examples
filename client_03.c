/*
 *client file
 */

#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#define SOCK_NAME "/tmp/unix_sock"

int
main(int argc, char ** argv){
  struct sockaddr_un addr;
  int sfd;
  
  
  sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if(sfd == -1){
    perror("socket");
    exit(1);
  }

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCK_NAME, sizeof(addr.sun_path) - 1);
  printf("printing sock name:%s$\n", addr.sun_path) ;
  #define BUF_SIZE 256
  char buffer[BUF_SIZE];
  ssize_t num_bytes_read;

  if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un) ) == -1 )
    exit(1);
  
  //while ((num_bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0) {
  num_bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE) ;
  int i = 0;
  while (1) {

    if (write(sfd, buffer, num_bytes_read) != num_bytes_read){
      close (sfd);
      perror("write to socket");
      exit(1);
    }
    printf("write successful:%d\n",i++);
  }

  if(num_bytes_read == -1){
    perror("finished");
    exit(0);
  }
  
  close(sfd);

  return 0;
}
