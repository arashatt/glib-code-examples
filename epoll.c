#include <sys/epoll.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sysmacros.h>
#include <fcntl.h>
#include <stdlib.h>
#define DEBUG

#define MAX_EVENTS 50
struct epoll_event ev, events[MAX_EVENTS];
void *print_handle(void *);
struct epoll_info
{
  int efd;
  struct files
  {
    int fd;
    struct files *next;
  } *files;
};

int main(int argc, char **argv)
{
  pthread_t pid;
  int nfd;
  struct epoll_info info;
  struct stat dirstat;
  info.files = (struct files *)malloc(sizeof(struct files));
  struct files *index = info.files;

  if (1 > argc)
  {
    perror("bad usage");
  }
  else
  {
    for (int i = 1; i < argc - 1; i++)
    {
      index->next = (struct files *)malloc(sizeof(struct files));
      index = index->next;
    }
    index->next = NULL;
  }
  if (stat(argv[1], &dirstat) != 0)
    perror("couldn't stat:");
  switch (dirstat.st_mode & S_IFMT)
  {
  case S_IFBLK:
    printf("block device\n");
    break;
  case S_IFCHR:
    printf("character device\n");
    break;
  case S_IFDIR:
    printf("directory\n");
    break;
  case S_IFIFO:
    printf("FIFO/pipe\n");
    break;
  case S_IFLNK:
    printf("symlink\n");
    break;
  case S_IFREG:
    printf("regular file\n");
    break;
  case S_IFSOCK:
    printf("socket\n");
    break;
  default:
    printf("unknown?\n");
    break;
  }

  info.efd = epoll_create1(0);
  if (info.efd == -1)
    perror("failed at creating epoll instance:");
  ev.events = EPOLLIN | EPOLLET;
  int i = 1;
  for (struct files *index = info.files; index != NULL; index = index->next)
  {
    index->fd = open(argv[i++], O_RDWR);

#ifdef DEBUG
    printf("File Descriptor %s: %d\n", argv[i - 1], index->fd);
#endif
    if (epoll_ctl(info.efd, EPOLL_CTL_ADD, index->fd, &ev) == -1)
      perror("faild");
  }
  pthread_create(&pid, NULL, print_handle, &info);
  pthread_join(pid, NULL);
  return 0;
}

// data structure for epoll
void *print_handle(void *arg)
{

  printf("thread created\n");
  for (;;)
  {
    struct epoll_info *info = (struct epoll_info *)arg;
    int nfd;
    int efd = info->efd;

    nfd = epoll_wait(efd, events, MAX_EVENTS, -1); // blocks either until time expires or event occures.
    printf("nfd %d\n", nfd);
    for (int i = 0; i < nfd; i++)
    {
      printf("Event Rready:");

      printf("%d is ready\n", events[i].data.fd);
    }
  }
}
