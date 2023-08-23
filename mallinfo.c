#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int main(int argc, char ** argv){
  printf("%s\n",  mallinfo());
  
  
  return 0;
}
