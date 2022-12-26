#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int count1=0;
int main()
{
    pid_t cpid ;
    int fd;
    ssize_t r1,r2,w1,w2;
    char buff[50000],buff_1[1];
    int pipe_fd1[2],pipe_fd2[2];
    



    fd = open("/usr/include/stdio.h", O_RDONLY );
    if(-1 == fd )
    {
        perror("Error in opening File\n");
        exit(EXIT_FAILURE);

    }
    pipe(pipe_fd1);
    pipe(pipe_fd2);


    cpid = fork();
    if(cpid == -1){
        perror("Error in creating child\n");
        exit(EXIT_FAILURE);
    }

    if(cpid == 0)
    { 
        int count = 0;  
        close(pipe_fd1[1]);
        close(pipe_fd2[0]);
        while(read(pipe_fd1[0],buff_1,sizeof(buff_1)))
        {
            if(buff_1[0] == 's')
            {
                count++;
            }
        }
       // w2=write(pipe_fd2[1],&count,sizeof(count));
        printf("Number of 's' is %d\n",count);
        close(pipe_fd1[0]);



        //chilld process
    }
    else{
            close(pipe_fd1[0]);
            close(pipe_fd2[1]);
            r1 = read(fd,buff,sizeof(buff));
            if(r1==-1)
            {
                perror("Errpr in reading\n");
                exit(EXIT_FAILURE);

            }

           w1 = write(pipe_fd1[1],buff,r1);
          //r2= read(pipe_fd2[0],&count1,sizeof(count1));
          // printf("The s are %d times\n",count1);
           close(pipe_fd1[1]);
           close(pipe_fd2[0]);


        //parent process
    }
    close(fd);
 return 0;   

}