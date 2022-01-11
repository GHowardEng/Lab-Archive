// toneplayer.c - play a tune using hardware tone generator ELEX 7660 201710 Lab 3
// outline by Ed. Casas 2017-1-22
// modified by: <Grant Howard>

#include "unistd.h"		/* for usleep() */

#define N 72
#define sleep_dur 150000 // Sleep duration of 150 ms or 150 000 us

int freq [N] = { 330, 392, 440, 494, 523, 494, 440, 370, 294,
    330, 370, 392, 330, 330, 311, 330, 370, 311, 247, 330, 392,
    440, 494, 523, 494, 440, 370, 294, 330, 370, 392, 370, 330,
    311, 277, 294, 330, 330, 587, 587, 554, 494, 440, 370, 294,
    330, 370, 392, 330, 330, 311, 330, 370, 311, 247, 587, 587,
    554, 494, 440, 370, 294, 330, 370, 392, 370, 330, 311, 277,
    294, 330, 330} ;

int duration [N] = { 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2,
    4, 2, 4, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2,
    6, 4, 6, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 6, 6,
    3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4} ;

#if 0

#include "system.h"		/* peripheral base addresses */
#define SETFREQ(x) (*(int*)TONEGEN_0_BASE) = (x)

#else

#define SETFREQ(x) (printf("%d Hz",x))
#define usleep(x)  (printf(" for %d ms\n",x/1000))

#endif

int main(void)
{ 

   for (int i = 0, i < N, i++)
   {
	   SETFREQ(freq[N]);				// Set next note frequency
	   usleep(duration[N] * sleep_dur);	// Hold for note duration
   }

   SETFREQ(0) ;

   return 0;
}

