#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
   if(argc < 2){
    printf("usage: sleep <ticks>\n");
    exit(1);
  }

  int times;
  times=atoi(argv[1]);

   sleep(times);

  exit(0);
}
