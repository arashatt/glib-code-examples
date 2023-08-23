#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char ** argv){
  size_t size = 14;
  char * cwd  = (char *) malloc(size);
  if(cwd == NULL)
    return 1;
  
  cwd = getcwd(NULL, size);
  if(cwd == NULL){
    perror("getcwd:"); exit(1);
  }
  
  printf("%s\n", cwd);
  //  printf("directory:%d\n", get_current_dir_name());
  free(cwd);
   chdir("/home/arash");
   char * args[2] = {"ls", '\0'};
   __asm__("syscall");

   
  return 0;
}
