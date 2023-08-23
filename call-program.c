#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){
  execvp("evince",argv);
  return 0;
}
