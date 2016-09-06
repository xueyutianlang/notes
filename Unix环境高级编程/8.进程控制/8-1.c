/*****************************************************************************
 * File name  : 8-1.c
 * Description: fork函数演示，子进程变量修改不影响父进程
 * Author     : 郭全
 * Date       : 2016/09/06
 * *****************************************************************************/
#include "apue.h"

int  glob  = 6;//在数据初始化中的外部变量
char buf[] = "a write to stdout\n";

int main(void)
{
    int   var;//栈上的自动变量
    pid_t pid;
    
    var = 88;

    //wirte：系统调用,无buffer
    //STDOUT_FILENO：标准输出文件描述符
    //sizeof(buf)-1：获取字符串长度比strlen更优(strlen不包含NULL(\0)的长度,且函数调用),因为计算结果包含NULL,所以-1是为了不输出终止NULL字符(\0)
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) -1)
    {
        err_sys("write error");
    }
    
    //stdout stream是行缓冲, stderr无缓冲
    //printf：默认不会刷新，除非字符串中包含换行符\n
    //1.printf("before fork\n");
    //2.setbuf(stdout, NULL);printf("before fork");//关闭buffer
    //3.printf("before fork");fflush(stdout);//刷新buffer
    //4.fprintf(stderr, "before fork");//stderr无缓冲
    //5.write(STDOUT_FILENO, "before fork", sizeof("before fork") - 1);//系统调用无缓冲
    printf("before fork\n");

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)//child
    {
        glob++; 
        var++;
    }
    else//parent
    {
        sleep(2);//休眠2秒，让子进程先执行
    }
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);

    /*
     * 结果
     * =============
     * $ ./a.out  //终端是行缓冲
     * a write to stdout//write无缓冲，输出1次
     * before fork//标准输出缓冲区由换行符冲洗，输出1次
     * pid = 20246, glob = 7, var = 89
     * pid = 20245, glob = 6, var = 88
     * -------------
     * $ ./a.out > temp.out //文件是全缓冲，fork时buffer会复制到子进程
     * a write to stdout//write无缓冲
     * before fork//fork之前printf1次，但因是全缓冲，该行数据还在缓冲区，数据空间复制时，也复制到了子进程，每个进程终止时，最终会刷新缓冲区
     * pid = 20248, glob = 7, var = 89
     * before fork
     * pid = 20247, glob = 6, var = 88
     */
}
