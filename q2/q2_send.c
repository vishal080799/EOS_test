#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <mqueue.h>

struct mq_attr vishal_attr;
int main()
{
     ssize_t r1,r2,w1,w2;
    char buff[50000],buff_1[1];
    int pipe_fd1[2],pipe_fd2[2];
    int fd;

     mqd_t vishal_mq_desd;
    int vishal_send_bytes,v_close;
    vishal_attr.mq_maxmsg  = 5;
    vishal_attr.mq_msgsize = sizeof(buff);

    fd = open("/usr/include/stdio.h", O_RDONLY );
    if(-1 == fd )
    {
        perror("Error in opening File\n");
        exit(EXIT_FAILURE);

    }

    r1 = read(fd,buff,sizeof(buff));
            if(r1==-1)
            {
                perror("Errpr in reading\n");
                exit(EXIT_FAILURE);
            }
    vishal_send_bytes = mq_send(vishal_mq_desd,buff,r1,0);  
     if(vishal_send_bytes == -1)
    {
          perror("Error in sending of msg in msg_queue\n");
        exit(EXIT_FAILURE);
    }
     v_close = mq_close(vishal_mq_desd);
    if(v_close ==-1)
    {
          perror("Error in closing of msg_queue\n");
        exit(EXIT_FAILURE);
    }  


return 0;
}
    
