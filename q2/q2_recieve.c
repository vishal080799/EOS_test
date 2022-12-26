#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <mqueue.h>

struct mq_attr vishal_attr;
int count =0;
int main()
{
     ssize_t r1,r2,w1,w2;
    char buff[50000],buff_1[50000];
    int pipe_fd1[2],pipe_fd2[2];
    int fd;

     mqd_t vishal_mq_desd;
    int vishal_recieve_bytes,v_close;
    vishal_attr.mq_maxmsg  = 5;
    vishal_attr.mq_msgsize = sizeof(buff);
     vishal_mq_desd = mq_open("/vishal_msg_q",O_CREAT | O_WRONLY,S_IRUSR | S_IWUSR,&vishal_attr);

    if(vishal_mq_desd == -1)
    {
        perror("Error in opening of msg_queue\n");
        exit(EXIT_FAILURE);
    } vishal_recieve_bytes = mq_receive(vishal_mq_desd, buff_1, sizeof(buff_1), 0);
    if(vishal_recieve_bytes == -1)
    {
        perror("Error in recieving  of msg at msg_queue\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0 ; i <= vishal_recieve_bytes;i++)
    {
        buff_1[i] == 's';
        count++;
    }
    printf("the no of s is %d\n",count);

     v_close = mq_close(vishal_mq_desd);
    if(v_close ==-1)
    {
          perror("Error in closing of msg_queue\n");
        exit(EXIT_FAILURE);
    }


    return 0;
}

    
