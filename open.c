#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char ** argv){

  int fd =open("open-this-file.cccccc", O_RDWR | O_CREAT);
  if (fd < 0 ){
    perror("fd");
    exit(1);
  }
  close(fd);

  
  
  return 0;
}
