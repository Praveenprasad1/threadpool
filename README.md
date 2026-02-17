# Thread Pool – Systems-Oriented Implementation

A lightweight thread pool implementation written in C, focused on
predictable behaviour under load and suitability for high-performance
systems such as protocol processors, network services, and infrastructure
components.

This repository serves as an experimentation space for studying
concurrency design trade-offs using first-principles approaches rather
than framework abstractions.

## Purpose Of Repository

This project is part of ongoing experimentation into:
	- **•	concurrent execution models**
	- **•	low-latency infrastructure components**
	- **•	protocol and IO processing pipelines**
	- **•	systems programming using C/C++**

The emphasis is on understanding behaviour, not hiding complexity.

---

## Design Goals

- **Predictable latency under contention**  
  Ensure task execution latency remains stable even when multiple producers
  compete for worker resources.

- **Minimal lock contention**  
  Reduce synchronization overhead through careful queue access patterns
  and controlled critical sections.

- **Scalable worker lifecycle management**  
  Support efficient creation, reuse, sleep, and shutdown of worker threads
  without excessive context switching.

- **Suitable for protocol-processing pipelines**  
  Designed to integrate naturally with staged or event-driven systems where
  connections mature over time and are processed incrementally.

---

## Architecture Overview

The implementation focuses on:

- Producer → Work Queue → Worker execution model
- Controlled synchronization primitives
- Efficient wakeup and sleep mechanisms
- Separation between task submission and execution domains

The goal is not maximum feature richness, but **clarity of concurrency
behaviour and performance predictability**.

---

## Runtime Behaviour

Example execution output:
====================================================================================
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
