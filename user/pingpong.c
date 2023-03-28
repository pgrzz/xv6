#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
 
    // fork
    int p1[2]; int p2[2];
    //d records the read and write file descriptors  in the array p
    // 0 read side. 1 write side

     pipe(p1);
     pipe(p2);

  int pid=fork();

    char buf[1];
    buf[0]='p';
    int len=sizeof(buf)/1;

  if(pid > 0){

    //send a byte to the child
    write(p1[1], &buf, len);
     close(p1[1]);
    //通过read 阻塞
   read(p2[0],&buf, sizeof buf);
   close(p2[0]);
     //rint "<pid>: received pong", and exit. 
     int parentPid=  getpid();
     printf("%d received pong\n",parentPid);

} else if(pid == 0){
    //read 
     read(p1[0], &buf, sizeof buf);
    close(p1[0]);
   int childPid=  getpid();
     printf("%d received ping\n",childPid);
   // write the byte on the pipe to the parent exit
    write(p2[1],&buf, len);
    close(p2[1]);
    exit(0);


} else {
printf("fork error\n");
}

  exit(0);
}
