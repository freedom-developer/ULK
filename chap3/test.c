#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


// 信息SIGUSER1的处理函数
void siguser1_handler(int signum)
{
    printf("SIGUSER1 received\n");

}


int main()
{
    signal(SIGUSR1, siguser1_handler);
    
    pause();

    return 0;
}