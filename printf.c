#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char ** argv){

  size_t read;
  read = printf("printf: Hello World!\n");
  printf("read:%z", read);

  return 0;

}
