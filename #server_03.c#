/*
 *server file
 */

#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#define SOCK_NAME "/tmp/unix_sock"
#define BACKLOG 5
#define BUF_SIZE 256

int
main(int argc, char ** argv){
  printf("entering main function successful\n");

  struct sockaddr_un addr;
  int sfd, cfd;
  ssize_t numRead;
  char buffer[BUF_SIZE];
  

  sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if(sfd == -1){
    perror("socket");
    exit(1);
  }
  printf("sfd: %d\n", sfd);
  
  printf("creating socket successful\n");
  
  if (remove(SOCK_NAME) == -1 && errno!= ENOENT)
    {
      perror("removing file");
      exit(1);
    }
      printf("removing old socket successful\n");
  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCK_NAME, sizeof(addr.sun_path) - 1);
  printf("printing socket name:%s$\n", addr.sun_path);

  if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un) ) == -1){
    perror("bind");
    close(sfd);
    exit(-1);
  }

  
  if (listen(sfd, BACKLOG) == -1){
    perror("listen");
    exit(-1);
  }
  printf("listen successful\n");

  for(;;){

    cfd = accept(sfd, NULL, 0);
    if (cfd == -1) {
        perror("Accepting failed");
        close(sfd);
        exit(1);
    }
    printf("cfd file descriptor: %d\n", cfd);

    // Read data from the client and print it


    while ((numRead = read(cfd, buffer, BUF_SIZE)) > 0) {
      sleep(3);
      if (write(STDOUT_FILENO, buffer, numRead) != numRead )
	perror("write failed!");
    }

    

  }
  
  close(sfd);
  close(cfd);
  remove(SOCK_NAME);  
  return 0;
}
