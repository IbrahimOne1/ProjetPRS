#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
int main(int argc , char* argv[])
{int sig=atoi(argv[1]);
  int pid=atoi(argv[2]);
  kill(pid,sig);
  return 0;}
