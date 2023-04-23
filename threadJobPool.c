/* 
** Copyright (c) 2023 Praveen K Prasad
** Email Id: praveen.prasad1@hotmail.com, praveen_213@yahoo.co.in
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
** 
** 2. Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and/or other materials provided with the distribution.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
** INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
** OF SUCH DAMAGE.
**
** RCS:
** $Log: threadJobPool.c,v $
** Revision 1.2  2023/04/23 20:44:58  praveen
** Added 2-Clause BSD license header, removed unwanted comments, some trivial code changes before github commits.
**
**
*/

#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 

const int totalThread = 15;	
// Declaration of thread condition variable
pthread_cond_t condMainTh = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_arr[15] = {PTHREAD_COND_INITIALIZER}; 

// declaring mutex 
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t lockMainTh = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t localSLock = PTHREAD_MUTEX_INITIALIZER; 	//Need to ensure atomic increment of tIndex in initF()

void jFoo (); 
void yeildCPU (int);

void unBlock (int tIndex) {
   //Thread Id as tIndex grabs CPU time.
   pthread_cond_signal (&cond_arr[tIndex]);
}

void yeildCPU (int tIndex) {
   //Already Grabed lock, now cond_wait at respective index
   pthread_mutex_lock (&lock);
   pthread_cond_wait (&cond_arr[tIndex], &lock);
   pthread_mutex_unlock (&lock);
   jFoo ();
}

//Thread Job Main Function 
void jFoo () {
   static unsigned counter;
   sleep (1);	//Sleeps here to allow human readable slower console outputs.
   printf ("Thread %d : Tid %lx : Counter Val = %d\n", (counter % totalThread) + 1 , pthread_self(), counter);
   //No Mutex_lock unlock used to protect counter, as already discussed during interview -by design only one thread is gureenteed to be here.
   ++counter;
   unBlock (counter % totalThread);
   pthread_mutex_unlock (&lock);
   yeildCPU ((counter - 1) % totalThread);
} 

void *initF () {
   static int tIndex;
   pthread_mutex_lock (&localSLock);
   printf ("\ninitF():Thread index %d\n", tIndex);
   tIndex++;
   pthread_mutex_unlock (&localSLock);
   yeildCPU (tIndex -1);
}

//For to block main thread.
void yeild2 () {
   pthread_mutex_lock (&lockMainTh);
   pthread_cond_wait (&condMainTh, &lockMainTh);
   pthread_mutex_unlock (&lockMainTh);
}

int main () {
   pthread_t tid;
   printf ("\nMain(): Initializing all Job threads.");
   for (int i = 0; i < totalThread; i++)
	   pthread_create (&tid, NULL, initF, NULL); 
   printf ("\nMain(): Initialization Done.\nNow Unblocking task threads to start and relinquishing CPU.\n");
   unBlock (0);
   yeild2 ();
   return 0; 
} 
