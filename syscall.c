#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
/*this program changes the file permissin of a file whose name is in arg 1 according to the first argument passed to it*/
int main(int argc, char ** argv){
 
  
  if (argc == 3){
    int perm = (int) strtol(argv[2], NULL, 8);
    printf("perm: %o\n", perm);
    int rc;
    rc = syscall(SYS_chmod, argv[1], perm);
    if (rc == -1){
      fprintf(stderr, "chmod failed, errno: %d \n", errno);
      perror("");
    }
    
  }
  else {
    printf("please provide right number of arguments\n");
  }
  return 0;
}
