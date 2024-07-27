About the new file testFooThreadSafety.c which is added here on the "Master" branch:
To compile, use gcc or any c compiler as below: 
praveen@praveen-latitude-3410:~/trcode/threads/threadPools$ cc testFooThreadSafety.c

After running, to terminate the execution gracefully, input 0 and "return" to stop all the threads and the main program. Ofcourse one may terminate with Ctrl-C but not all the logs could come as expected.

===Console Run Logs (Observe the logs to decipher the different instantiation of stack local variables yourself)===
praveen@praveen-latitude-3410:~/trcode/threads/threadPools$ cc testFooThreadSafety.c 
praveen@praveen-latitude-3410:~/trcode/threads/threadPools$ ./a.out 

Main(): Initializing all Job threads.
Main(): Initialization Done.
Now Unblocking task threads to start and relinquishing CPU.
initF(): Thread index -2  TID: 140403466565184
initF(): Thread index -2  TID: 140403458172480
initF(): RandomNum = 1911605001 Thread index -2  TID: 140403466565184
initF(): Thread index 1911605001  TID: 140403466565184
initF(): RandomNum = 229002138 Thread index -2  TID: 140403458172480
initF(): Thread index 229002138  TID: 140403458172480
initF(): RandomNum = 704975713 Thread index 1911605001  TID: 140403466565184
initF(): Thread index 704975713  TID: 140403466565184
initF(): RandomNum = 1163658329 Thread index 229002138  TID: 140403458172480
0initF(): Thread index 1163658329  TID: 140403458172480
initF(): RandomNum = 1630268978 Thread index 704975713  TID: 140403466565184
initF(): Thread index 1630268978  TID: 140403466565184
initF(): RandomNum = 1014978222 Thread index 1163658329  TID: 140403458172480
initF(): Thread index 1014978222  TID: 140403458172480
initF(): RandomNum = 409228501 Thread index 1630268978  TID: 140403466565184
initF(): Thread index 409228501  TID: 140403466565184
initF(): RandomNum = 1942567954 Thread index 1014978222  TID: 140403458172480
initF(): Thread index 1942567954  TID: 140403458172480
initF(): RandomNum = 1335721248 Thread index 409228501  TID: 140403466565184

initF(): RandomNum = 1797238902 Thread index 1942567954  TID: 140403458172480

====================================================================================
