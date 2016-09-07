/*****************************************************************************
 * File name  : 8-3.c
 * Description: 打印exit状态说明
 * Author     : 郭全
 * Date       : 2016/09/07
 * *****************************************************************************/
#include "apue.h"
#include <sys/wait.h>

void pr_exit(int status);

int main(void)
{
    pid_t pid;
    int status;
    
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)//child
    {
        exit(7);
    }
    //parent
    if (wait(&status) != pid)//wait for child
    {
        err_sys("wait error");
    }
    pr_exit(status);//打印状态

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        abort();//异常终止，产生SIGABRT信号
    }
    if (wait(&status) != pid)
    {
        err_sys("wait error");
    }
    pr_exit(status);

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        status /= 0;//SIGFPE除0异常
    }
    if (wait(&status) != pid)
    {
        err_sys("wait error");
    }
    pr_exit(status);
    exit(0);
    /*
     * 结果
     * =======
     * $ gcc 8-3.c -Wno-div-by-zero
     * $ ./a.out
     * 正常终止，退出码：7
     * 异常终止，信号：6
     * 异常终止，信号：8
     */

}

void pr_exit(int status)
{
    if (WIFEXITED(status))
    {
        printf("正常终止，退出码：%d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        printf("异常终止，信号：%d%s\n", WTERMSIG(status),
    #ifdef WCOREDUMP
        WCOREDUMP(status) ? " (core file generated)" : "");
    #else
        "");
    #endif
    }
    else if (WIFSTOPPED(status))
    {
        printf("子进程停止，信号：%d\n", WTERMSIG(status));
    }
}
