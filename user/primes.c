#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void siftss(int i, int* p);

/**
 * 通过层层的管道的sift掉非素数
*/
int
main(int argc, char *argv[])
{
   int p[2];
   pipe(p);
    for(int i=2;i<=35;i++){
         write(p[1],&i,4);
    }
    //end flag
    int end=-1;
     write(p[1],&end,4);
  siftss(2,p);
  exit(0);
}

//begin i==2
void 
siftss(int i,int* p){
    if(i>35){
        return;
    }

   int childpipe[2];
   pipe(childpipe);
   int value;
     
    while( value!=-1 && read(p[0],&value,4)!=0 ){
        if(value%i!=0){
                write(childpipe[1],&value,4);
        }
        if(value==i){
            printf("prime %d \n",value);  
        }

    }

     //end flag
     int end=-1;
     write(childpipe[1],&end,4);

    close(p[1]);
    close(p[0]);
    int pid=fork();

    if(pid>0){
     //wait 语意是等待任子进程完成
         wait((int *)0);
         exit(0);
    }else if(pid==0){
     
         siftss(i+1,childpipe);
    }else{
         printf("fork error\n");
    }

}




