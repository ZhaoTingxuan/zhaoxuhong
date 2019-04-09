实验三  同步与通信
===
安全1601班     15282028     赵旭宏      
--
实验题目一
--
1.1内容：
-
通过fork的方式，产生4个进程P1,P2,P3,P4，每个进程打印输出自己的名字，例如P1输出“I am the process P1”。要求P1最先执行，P2、P3互斥执行，P4最后执行。通过多次测试验证实现是否正确。
##
1.2原理
-
前驱关系：P1-->P2、P1-->P3、P2-->P4、P3-->P4
前趋图如下：
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/qianqu.jpeg)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/jincheng.jpeg)
##
四个进程必须是P1最先执行，P2、P3在P1执行完后互斥执行，P4最后执行。

定义三个信号量，其初值均为0。
P1进程执行完打印任务之后对信号量1进行V操作，产生一个资源让等待信号量1的进程P2和P3其中之一可以执行。由于P2和P3都是等待信号量1，但是P1进程只产生一个单位的信号，所以P2和P3的执行是互斥的，这样就满足了题目要求。最后在P2和P3执行完打印任务后对信号量2和信号量3进行V操作从各产生一个单位的信号量，而进程P4会等待信号量2和信号量3，所以知道当P2和P3进程都完成才能进行P4进程。通过控制这三个信号量，这四个进程之间的前驱关系就满足了题目要求。

流程图：
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/liucheng.jpeg)
#
进程树：
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/tree.jpeg)
#
1.3运行结果
--
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/1.png)
#
经过多次测试，四个进程在屏幕上打印的顺序只有两种结果，分别如下：
1:P1-->P2-->P3-->P4
2:P1-->P3--P2-->P4
由于P1是P2和P3的前驱，所以P1一定会在P2和P3之前执行，但是P2和P3是互斥关系，这两个进程谁先获得P1产生的信号量谁就先执行另一个进程等待。最后等P2和P3都执行完了再执行P4.
2.1内容：
-
火车票余票数ticketCount 初始值为1000，有一个售票线程，一个退票线程，各循环执行多次。添加同步机制，使得结果始终正确。要求多次测试添加同步机制前后的实验效果。
2.2 实验过程
--
未添加同步机制:
在main函数中创建两个线程，分别是模拟售票的线程SaleThread和模拟退票的线程RefundThread，两个进程并发执行，不添加任何的同步机制。
模拟票数的变量ticketCount是全局变量
程序运行需要输入两个参数，第一个是售票数量，第二个数退票数
运行结果可以分为两种类型，一种是售票数量比退票数量多，另一种是售票数量比退票数量少。
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/2.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/3.png)
#
售票进程和退票进程同时进行，初始票数均为1000，售票进程完成一次是票数为999，售票进程开始下一次售票，但是在运行temp=ticketCount之前，退票进程处理的数据还没有写入到内存中，导致售票进程读取的还是自己之前计算的ticketCount值，而不是全局的值。退票进程也是同理。
#
添加同步机制:
flag初始值为设置为1，表示每次只允许一个线程操作ticketCount.
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/4.png)
#
运行结果:
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/5.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/6.png)
#
增加了同步机制之后的多线程并发程序有效的解决了脏数据的读取问题.
当给售票进程和退票进程都加上同步机制后，保证了每个线程操作的原子性，每个线程操作的过程中其他的线程不能对共享的ticketCount变量进程修改，这样的话最终的结果就是正确的结果。
##
3.1内容：
--
一个生产者一个消费者线程同步。设置一个线程共享的缓冲区， char buf[10]。一个线程不断从键盘输入字符到buf,一个线程不断的把buf的内容输出到显示器。要求输出的和输入的字符和顺序完全一致。（在输出线程中，每次输出睡眠一秒钟，然后以不同的速度输入测试输出是否正确）。要求多次测试添加同步机制前后的实验效果。
#
3.2 实验过程
--
设置两个信号量empty和ful来控制程序的执行，其中empty信号量用于保证输入线程在写入数据到缓存的时候缓存中还有空余的位置，保证写入线程后写入的数据不会把前面写入但是为输出的数据给覆盖掉，其初始值为10，表示最开始缓存中有10个空余的位置供给写入线程写入数据；full信号量是用于保证输出线程有数据输出，避免在写入线程还没有写入数据的情况下输出线程输出随机数据，其初始值为0，表示初始状态下缓存中没有数据可以输出.
##
输入线程在写入一个数据前要等待empty信号量，进入后便消耗一个信号量；完成写入数据操作之后post一个full信号量，通知输出线程输出数据。
#
输出线程在输出一个数据之前哟啊等待full信号量，进出输出操作后便消耗一个full信号量；完成输出操作后post一个empty信号量，通知写入线程缓存又多一个空余位置以供写入数据。输出线程每输出一个字符等待一秒钟，方便实验结果的查看。
#
3.3 实验结果
--
这个题与我们课上的练习题差不多，老师也解释了很多。
10个以内输入字母和数字:
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/7.png)
#
10个以上
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/8.png)
#
不间断输入:
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/9.png)
#

4.1 实验要求
--
a）通过实验测试，验证共享内存的代码中，receiver能否正确读出sender发送的字符串？如果把其中互斥的代码删除，观察实验结果有何不同？如果在发送和接收进程中打印输出共享内存地址，他们是否相同，为什么？
b)有名管道和无名管道通信系统调用是否已经实现了同步机制？通过实验验证，发送者和接收者如何同步的。比如，在什么情况下，发送者会阻塞，什么情况下，接收者会阻塞？
c）消息通信系统调用是否已经实现了同步机制？通过实验验证，发送者和接收者如何同步的。比如，在什么情况下，发送者会阻塞，什么情况下，接收者会阻塞？

4.2 实验过程:
--
（这部分参考了孙汉武同学的实验过程，主要参考其猜想和验证过程）
4.2.1 a:
--
创建一个共享内存的ID,就是代码中的key

     key_t  key;
     key = ftok(".", 0xFF);
##
通过ftok函数创建一个key_t类型的变量，作为共享内存的key，ftok函数的两个参数分别是文档名(一个存在的路径),上例中的路径是.表示当前路径，另一个参数是子序号
创建并初始化信号量
    int sem_id;
    sem_id = semget(key, 1, IPC_CREAT|0644);
    if(-1 == sem_id)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    if(-1 == (semctl(sem_id, 0, SETVAL, value)))
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }
    ##
通过semget()函数创建一个信号量，初始值为1，再通过semctl()函数初始化该信号量.

主循环中首先判断表示共享内存访问情况的信号量是否为0(为0表示共享内存空闲)，如果为0的话提示用户输入想要输入的消息，并将用户输入的消息写入共享内存中，写完后通过semop函数将信号量加一，通知receiver读取消息。并且定义一个end命令表示退出当前进程。循环退出的时候取消共享内存的挂载.
#
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/10.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/11.png)
#
删除互斥访问后:
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/12.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/13.png)
##
打印Sender和Receiver进程中共享内存的地址:
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/14.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/15.png)
##
可以看到共享内存在不同进程中是不相同的，总结有以下的原因导致共享内存在不同进程中的地址不一样.
进程在挂载内存的时候使用的shmat()函数中的第二个参数使用的是NULL，NULL参数的含义是进程让系统分配给共享内存合适的地址。在shmat()函数中，第二个参数有三种选择，分别是：
|参数值   |	NULL |	addr |	addr|
|含义 	|系统将自动选择一个合适的地址 	|如果shmaddr非0 并且指定了SHM_RND 则此段连接到shmaddr -（shmaddr mod SHMLAB)所表示的地址上。 |	第三个参数如果在flag中指定了SHM_RDONLY位，则以只读方式连接此段，否则以读写的方式连接此段。|
##
现代操作系统中都存在ASLR(地址空间随机化)，ASLR是⼀种针对缓冲区溢出的安全保护机制，具有ASLR机制的操作系统每次加载到内存的程序起始地址会随机变化。系统的这个随机化操作可能导致共享内存的地址不一致。
##
以下进行验证：
指定共享内存的挂载地址:
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/16.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/17.png)
##
关闭系统的ASLR操作:
sudo su
sysctl -w kernel.randomize_va_space=0
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/18.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/19.png)
##
4.2.2 b:
--
无名管道:
通过pipe函数创建管道，函数传递一个整形数组fd，fd的两个整形数表示的是两个文件描述符，其中第一个用于读取数据，第二个用于写数据。两个描述符相当远管道的两端，一段负责写数据，一段负责读数据。

pipe管道某一时刻只能读或者只能写,读写管道就和读写普通文件一样，使用write和read.
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/20.png)
#
无名管道同步机制验证:
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/21.png)
父进程中会持续向管道中写入用户输入的消息，子进程会一直输出管道中的消息，如果管道中没有消息就会阻塞等待。
##
有名管道:
当写进程和读进程都设置成阻塞状态的时候，不论先执行那个进程，先执行的进程都会阻塞等待，待另一个进程执行后两个进程才正常执行。
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/22.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/23.png)
##
设置了阻塞的写进程而言：当写入的数据量小于PIPE_BUF时，Linux保证写入原子性。如果此时管道中的空闲位置不足以容纳要写入的数据，泽写进程阻塞，直到管道中空间足够，一次性写入所有数据,当写入的数据量大于PIPE_BUF时，Linux不再保证写入的原子性。一旦管道中有空闲位置便尝试写入数据，直到所有数据写入完成后返回。
4.2.3 c
--
消息队列:
程序分为服务器端和客户端，客户端向服务器发起通信，服务器端收到数据后将一模一样的数据返回.
|参数 	|msgid 	|ptr |	length |	type |	flag|
|含义 	|消息队列标识符 |	消息缓冲区指针 	|消息数据长度 |	决定从队列中返回那一条下消息 |	阻塞与否|
|备注 	|			|   |    |=0 返回消息队列中第一条消息;>0 返回消息队列中等于mtype 类型的第一条消息。 |  |
##
通过msgsnd函数向消息队列中加入消息，msgsnd的参数列表见下面。
|参数 |	msgid |	ptr |	length |	flag|
|含义 |	消息队列标识符 |	消息缓冲区指针 	|消息数据长度 |	阻塞与否|
##
运行结果:
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/24.png)
消息队列通过msgrcv和msgsnd两个函数的flag参数控制是否阻塞，将其设置为IPC_NOWAIT表示不阻塞；如果客户端和服务器端都设置阻塞话，就可以达到同步的目的.
##
客服端不阻塞:
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/25.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/26.png)
##
客户端阻塞，服务器端不阻塞
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/27.png)
![](https://github.com/ZhaoTingxuan/zhaoxuhong/blob/master/15282028_Lab3/img/28.png)
当服务器端没有设置阻塞的时候，服务器端会一直接受消息队列中的空消息并向客户端转发。
##
5 实验内容
--
阅读Pintos操作系统，找到并阅读进程上下文切换的代码，说明实现的保存和恢复的上下文内容以及进程切换的工作流程。

首先devices/timer.c文件中
timer_ticks函数:
/* Returns the number of timer ticks since the OS booted. */
##
timer_ticks函数中第4行涉及一个名为intr_disable()的函数，该函数的具体定义在devices/interrupt.c文件中。
/* Disables interrupts and returns the previous interrupt status. */

##
返回值intr_level代码在devices/interrupt.h中：
/* Interrupts on or off? */
enum intr_level 
  {
    INTR_OFF,             /* Interrupts disabled. */
    INTR_ON               /* Interrupts enabled. */
  };
  ##
  
通过注释信息和分析汇编代码可以知道，intr_get_level这个函数的作用是返回当前的中断状态。intr_get_level函数弄清楚了之后，返回上一层函数中，到了intr_disable函数中，这样就可以清楚的知道intr_disable函数的作用：
    获取当前中断状态
    将当前中断状态更改为不可中断
    返回先前的中断状态
    ##
timer_ticks函数的作很简单，就是想获取当前系统的ticks值而已，而上面通过这么大篇幅的介绍timer_ticks函数的4、6两行的作用，原因是第4行和第6行通过先关闭中断，待t获取到ticks值之后载恢复之前的中断状态，来保证操作的原子性，简单的说就是在t获取全局变量ticks的值的时候，不能被打断。
##
再看看thread_yield函数的具体定义（在thread/thread.c文件中），thread_yield函数第5行顾名思义，作用就是返回当前正在运行的线程，通过一个thread类型的结构体指针接受该函数返回值。
##
thread_yield函数的第7行通过断言的方式判断中断类型，如果是由于I/O等引起的硬中断则退出，如果是软中断的话正常运行。
再深入schedule函数(thread/thread.c文件)看,schedule函数首先获取当前正在运行的线程指针cur和下一个运行的线程next，之后是三个断言。
    ASSERT (intr_get_level () == INTR_OFF)：保证中断状态是开启的
    ASSERT (cur->status != THREAD_RUNNING)：保证当前运行的线程是RUNNING_THREAD的
    ASSERT (is_thread (next))：保证下一个线程有效
##
shcedule函数最后一行执行的操作，最后一行调用thread_schedule_tail函数，下面详细分析一下这个函数（thread/thread.c文件中）。
首先是获得当前线程的的cur(切换之后的线程)，然后将cur的状态改为THREAD_RUNNING，然后thread_ticks清零开始新的线程切换时间片。然后调用diaoyongprocess_activate函数申请新的地址空间，再分析process_active函数(在useruserprog/process.c文件中定义)
##
关键的就是pagedir_activate()函数和tss_update函数，这两个函数分别位于userprog/pagedir.c和userprog/tss.c文件中
thread_schedule_tail函数，其作用就是分配恢复之前执行的状态和现场， 如果当前线程死了就清空资源。
##
schedule函数的作用就是拿下一个线程切换过来继续运行。thread_yield函数的作用是shi把当前进程放在就绪队列里，调用schedule切换到下一个进程。
最后返回到最顶层的timer_sleep函数，他的作用就是在ticks的时间内nei，如果线程处于running状态就不断的把它放在就绪队列不让它执行。
