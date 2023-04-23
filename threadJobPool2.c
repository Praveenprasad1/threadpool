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
** $Log: threadJobPool2.c,v $
** Revision 1.1  2023/04/23 20:50:42  praveen
** Initial revision
**
**
*/

#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 

const int totalThread = 15;	
// Declaration of thread condition variable
pthread_cond_t condMainTh = PTHREAD_COND_INITIALIZER;

// declaring mutex 
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t localSLock = PTHREAD_MUTEX_INITIALIZER; 	//Need to ensure atomic increment of tIndex in initF()

void jFoo (); 
void yeildCPU ();

void unBlock () {
   //Thread Id as tIndex grabs CPU time.
   pthread_cond_signal (&condMainTh);
}

void yeildCPU () {
   //Already Grabed lock, now cond_wait at respective index
   pthread_mutex_lock (&lock);
   pthread_cond_wait (&condMainTh, &lock);
   pthread_mutex_unlock (&lock);
   jFoo ();
}

//Thread Job Main Function 
void jFoo () {
   static pthread_mutex_t llock;
   static unsigned counter;
   pthread_mutex_lock(&llock);
   sleep (1);	//Sleeps here to allow human readable slower console outputs.
   printf ("Thread %d : Tid %lx : Counter Val = %d\n", (counter % totalThread+1) + 1 , pthread_self(), counter);
   //No Mutex_lock unlock used to protect counter, as already discussed during interview -by design only one thread is gureenteed to be here.
   ++counter;
   unBlock ();
   pthread_mutex_unlock (&llock);
   yeildCPU ();
} 

void *initF (void *argp) {
   yeildCPU ();
}

void *initorFoo (void *argp) {
	unBlock ();
	yeildCPU ();
}

int main () {
   pthread_t tid[totalThread], initid;
   void **ptRetval;
   printf ("\nMain(): Initializing all Job threads.");
   for (int i = 0; i < totalThread; i++)
	   pthread_create (&tid[i], NULL, initF, NULL); 
   printf ("Spawning the Initiator thread...\n");
   pthread_create (&initid, NULL, initorFoo, NULL);
   printf ("\nMain(): Initialization Done.\nNow Unblocking task threads to start and relinquishing CPU.\n");
   pthread_join (initid, ptRetval);
   for (int i = 0; i < totalThread; i++)
	   pthread_join (tid[i], ptRetval);
   return 0; 
} 
