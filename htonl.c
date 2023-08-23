#include<arpa/inet.h>
#include<stdio.h>
int main(){
  long a = 937;
  printf("%ld -> %u\n", a, htonl(a));

  return 0;
}
