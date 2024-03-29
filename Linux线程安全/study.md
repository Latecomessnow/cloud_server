## Linux线程互斥

### 进程线程间的互斥相关背景概念

1. 临界资源： 多线程执行流共享的资源叫做临界资源。

2. 临界区： 每个线程内部，访问临界资源的代码，就叫做临界区。

3. 互斥： 任何时刻，互斥保证有且只有一个执行流进入临界区，访问临界资源，通常对临界资源起保护作用。

4. 原子性： 不会被任何调度机制打断的操作，该操作只有两态，要么完成，要么未完成。


在多线程情况下，如果这多个执行流都自顾自的对临界资源进行操作，那么此时就可能导致数据不一致的问题。解决该问题的方案就叫做互斥，互斥的作用就是，保证在任何时候有且只有一个执行流进入临界区对临界资源进行访问。

// 抢票不加锁存在的问题

一开始临界资源ticket = 1000;

1. thread-1线程先被CPU调度，thread-1线程刚刚被调度就被切走了，那么thread-1被切走时
还要带走它的上下文数据，此时thread-1上下文数据中的ticket就还是1000

2. thread-1线程被切走后，thread-2线程立马就被调度，由于thread-1线程刚刚被调度就被切走了
只是执行了--操作的第一步，并没有把--之后的数据写回到内存中，所以thread-2中看到的ticket
还是1000，thread-2执行了100次--操作后，ticket变为900，但还未写回到内存中，thread-2线程
就被切走了，所以内存中的ticket还是1000

3. thread-2被切走后，thread-1又被调度回来了，此时thread-1上下文数据ticket=1000也会被
加载回CPU内，执行--操作后写回到内存中，所以此时内存中的ticket就是999
但是我们要知道thread-1执行了1次--操作，thread-2执行了100次--操作，而剩余的票数却是999
这就是有问题的！！！

++、-- 操作都不是原子的

////////////////////////////////

要解决上述抢票系统的问题，需要做到三点：

1. 代码必须有互斥行为：当代码进入临界区执行时，不允许其他线程进入该临界区。

2. 如果多个线程同时要求执行临界区的代码，并且此时临界区没有线程在执行，那么只能允许一个线程进入该临界区。

3. 如果线程不在临界区中执行，那么该线程不能阻止其他线程进入临界区。
要做到这三点，本质上就是需要一把锁，Linux上提供的这把锁叫互斥量。


pthreda_mutex_t mtx // 互斥量

// 对互斥量进行加锁操作

```c++
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
```
mutex：需要初始化的互斥量。
attr：初始化互斥量的属性，一般设置为NULL即可。

锁也被多个线程竞争式的共享，锁本身也是一种共享资源，而共享资源是需要被保护的，那么谁来保护
锁这个共享资源呢？其实就是锁自己保护自己，我们只需要确保申请锁的过程是原子的就可以了、

### 当线程释放锁时，需要执行以下步骤：

1. 将内存中的mutex置回1。使得下一个申请锁的线程在执行交换指令后能够得到1，形象地说就是“将锁的钥匙放回去”。

2. 唤醒等待Mutex的线程。唤醒这些因为申请锁失败而被挂起的线程，让它们继续竞争申请锁。

申请锁的过程一条交换指令，而这一条交换指令是一条汇编代码，所以说申请锁的过程是原子的


 CPU内的寄存器不是被所有的线程共享的，每个线程都有自己的一组寄存器，但内存中的数据是各个线程共享的。申请锁实际就是，把内存中的mutex通过交换指令，原子性的交换到自己的al寄存器中。

### 死锁的四个必要条件

1. 互斥条件： 一个资源每次只能被一个执行流使用。

2. 请求与保持条件： 一个执行流因请求资源而阻塞时，对已获得的资源保持不放。

3. 不剥夺条件： 一个执行流已获得的资源，在未使用完之前，不能强行剥夺。

4. 循环等待条件： 若干执行流之间形成一种头尾相接的循环等待资源的关系。

注意： 这是死锁的四个必要条件，也就是说只有同时满足了这四个条件才可能产生死锁。