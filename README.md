# threadpool
Refer below console logs on information to build and run (and platform infos) : -
Build: cc threadpool.c -lpthread

=======================================================================================

praveen@latitude-3410-i5:~/trcode/threads/threadPools$ cc threadJobPool2.c -lpthread
praveen@latitude-3410-i5:~/trcode/threads/threadPools$ ll
total 24
-rwxrwxr-x 1 praveen praveen 13280 Apr 24 02:27 a.out*
-rw-r--r-- 1 praveen praveen  3464 Apr 24 02:27 threadJobPool2.c
-rw-r--r-- 1 praveen praveen  3732 Apr 24 02:17 threadJobPool.c
praveen@latitude-3410-i5:~/trcode/threads/threadPools$ ./a.out 

Main(): Initializing all Job threads.Spawning the Initiator thread...

Main(): Initialization Done.
Now Unblocking task threads to start and relinquishing CPU.
Thread 2 : Tid 7fcffb36e700 : Counter Val = 0
Thread 3 : Tid 7fcffab6d700 : Counter Val = 1
Thread 4 : Tid 7fcff9b6b700 : Counter Val = 2
Thread 5 : Tid 7fcffa36c700 : Counter Val = 3
Thread 6 : Tid 7fcff936a700 : Counter Val = 4
Thread 7 : Tid 7fcff8b69700 : Counter Val = 5
Thread 8 : Tid 7fcff8368700 : Counter Val = 6
Thread 9 : Tid 7fcff7b67700 : Counter Val = 7
Thread 10 : Tid 7fcff7366700 : Counter Val = 8
Thread 11 : Tid 7fcff6b65700 : Counter Val = 9
Thread 12 : Tid 7fcff6364700 : Counter Val = 10
Thread 13 : Tid 7fcff5b63700 : Counter Val = 11
Thread 14 : Tid 7fcff5362700 : Counter Val = 12
Thread 15 : Tid 7fcff4b61700 : Counter Val = 13
Thread 16 : Tid 7fcff4360700 : Counter Val = 14
Thread 2 : Tid 7fcff3b5f700 : Counter Val = 15
Thread 3 : Tid 7fcffb36e700 : Counter Val = 16
Thread 4 : Tid 7fcffab6d700 : Counter Val = 17
Thread 5 : Tid 7fcff9b6b700 : Counter Val = 18
Thread 6 : Tid 7fcffa36c700 : Counter Val = 19
Thread 7 : Tid 7fcff936a700 : Counter Val = 20
Thread 8 : Tid 7fcff8b69700 : Counter Val = 21
Thread 9 : Tid 7fcff8368700 : Counter Val = 22
Thread 10 : Tid 7fcff7b67700 : Counter Val = 23
Thread 11 : Tid 7fcff7366700 : Counter Val = 24
^C
praveen@latitude-3410-i5:~/trcode/threads/threadPools$ rm a.out

praveen@latitude-3410-i5:~/trcode/threads/threadPools$ cc threadJobPool.c -lpthread
praveen@latitude-3410-i5:~/trcode/threads/threadPools$ ll
total 24
-rwxrwxr-x 1 praveen praveen 13296 Apr 24 02:29 a.out*
-rw-r--r-- 1 praveen praveen  3464 Apr 24 02:27 threadJobPool2.c
-rw-r--r-- 1 praveen praveen  3732 Apr 24 02:17 threadJobPool.c
praveen@latitude-3410-i5:~/trcode/threads/threadPools$ ./a.out 

Main(): Initializing all Job threads.
initF():Thread index 0

initF():Thread index 1

initF():Thread index 2

initF():Thread index 3

initF():Thread index 4

initF():Thread index 5

initF():Thread index 6

initF():Thread index 7

initF():Thread index 8

initF():Thread index 9

initF():Thread index 10

initF():Thread index 11

initF():Thread index 12

initF():Thread index 13

Main(): Initialization Done.
Now Unblocking task threads to start and relinquishing CPU.

initF():Thread index 14
Thread 1 : Tid 7ffb8c52e700 : Counter Val = 0
Thread 2 : Tid 7ffb8bd2d700 : Counter Val = 1
Thread 3 : Tid 7ffb8b52c700 : Counter Val = 2
Thread 4 : Tid 7ffb8ad2b700 : Counter Val = 3
Thread 5 : Tid 7ffb8a52a700 : Counter Val = 4
Thread 6 : Tid 7ffb89d29700 : Counter Val = 5
Thread 7 : Tid 7ffb89528700 : Counter Val = 6
Thread 8 : Tid 7ffb88d27700 : Counter Val = 7
^C
praveen@latitude-3410-i5:~/trcode/threads/threadPools$ uname -a
Linux latitude-3410-i5 5.4.0-135-generic #152~18.04.2-Ubuntu SMP Tue Nov 29 08:23:49 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
praveen@latitude-3410-i5:~/trcode/threads/threadPools$ lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 18.04.2 LTS (beaver-osp1-maester X48)
Release:	18.04
Codename:	bionic

=================================================================================================
