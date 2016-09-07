/*****************************************************************************
 * File name  : 8-4.c
 * Description: 调用fork两次避免僵死进程
 * Author     : 郭全
 * Date       : 2016/09/07
 * *****************************************************************************/
#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)//第一次fork的子进程
    {
        if ((pid = fork()) < 0)
        {
            err_sys("fork error");
        }
        else if (pid > 0)//第二次fork的父进程
        {
            exit(0);
        }
        //第二次fork的子进程逻辑
        //第二次fork中的sleep(2)休眠保证父进程先执行，在父进程调用exit后，第一个子进程终止
        //第二个子进程的父进程会变成init
        sleep(2);
        printf("第二次fork的子进程，父进程pid:%d\n", getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)
    {
        err_sys("waitpid error");
    }
    exit(0);
}
