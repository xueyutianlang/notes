/*****************************************************************************
 * File name  : 8-2.c
 * Description: vfork函数演示，用于创建新进程，新进程目的是exec一个新程序。vfork已保证子进程调用exec或exit之前，内核使父进程处于休眠状态
 * Author     : 郭全
 * Date       : 2016/09/07
 * Note       : vfork，已经废弃，可以用fork+exec替代，fork用了一种Copy-On-Write写时复制的技术
 * *****************************************************************************/
#include "apue.h"

int  glob  = 6;//在数据初始化中的外部变量
char buf[] = "a write to stdout\n";

int main(void)
{
    int   var;//栈上的自动变量
    pid_t pid;
    
    var = 88;

    printf("before vfork\n");

    if ((pid = vfork()) < 0)
    {
        err_sys("vfork error");
    }
    else if (pid == 0)//child
    {
        glob++; //vfork子进程在父进程的地址空间运行，会改变父进程的值
        var++;
        //_exit不执行标准I/O缓冲的冲洗操作
        //exit依赖标准I/O库实现，输出不确定
        _exit(0);
    }

    //parent
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);

    /*
     * 结果
     * =============
     * $ ./a.out
     * before vfork
     * pid = 21893, glob = 7, var = 89
     */
}
