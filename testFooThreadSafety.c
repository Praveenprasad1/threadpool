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
** $Log: testFooThreadSafety.c,v $
** Revision 1.2  2024/07/27 21:38:10  praveen
** Updated the code to test threads call stack and status and instantiation of local variables. Local variables are instantiated locally on pthread specific function call stack itself.
**
** Revision 1.1  2024/07/27 19:16:22  praveen
** Initial revision
**
** Revision 1.2  2023/04/23 20:44:58  praveen
** Added 2-Clause BSD license header, removed unwanted comments, some trivial code changes before github commits.
**
**
*/

#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h> 

const int totalThreads = 2;
// Declaration of thread condition variable
pthread_cond_t condMainTh = PTHREAD_COND_INITIALIZER;

// declaring mutex 
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 

uint32_t generateRandomNumber();

int runPool;

void *scanF() {
      int userIn;
      pthread_cond_signal (&condMainTh);
      do {
        scanf("%d", &userIn);
      } while(userIn);
      runPool = 0;
}

void *initF () {
   uint32_t randomNum;
   int tIndex = -2;
   do {
      pthread_mutex_lock (&lock);

      printf ("initF(): Thread index %d  TID: %ld\n", tIndex, (long)pthread_self());
      pthread_cond_wait (&condMainTh, &lock);
      randomNum = generateRandomNumber();
      printf ("initF(): RandomNum = %d Thread index %d  TID: %ld\n", randomNum, tIndex, (long)pthread_self());
      tIndex = randomNum;
      sleep(2);
      pthread_mutex_unlock (&lock);
      pthread_cond_signal (&condMainTh);
   }while(runPool);
}

// Function to generate a random 32-bit unsigned integer
uint32_t generateRandomNumber() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate a random number
    uint32_t randomNum = rand();

    return randomNum;
}

int main () {
   pthread_t stid, tid[totalThreads];
   runPool = 1; //True
   printf ("\nMain(): Initializing all Job threads.");
   for (int i = 0; i < totalThreads; i++)
	   pthread_create (&tid[i], NULL, initF, NULL); 
   printf ("\nMain(): Initialization Done.\nNow Unblocking task threads to start and relinquishing CPU.\n");
   pthread_create (&stid, NULL, scanF, NULL);
   for (int i = 0; i < totalThreads; i++)
	   pthread_join(tid[i], NULL);
   pthread_join(stid, NULL);
   return 0;
} 
