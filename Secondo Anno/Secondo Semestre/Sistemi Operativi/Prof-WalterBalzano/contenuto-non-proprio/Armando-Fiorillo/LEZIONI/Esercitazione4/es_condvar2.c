/* Due thread si alternano per incrementare i valori di count 
il primo incrementa i numeri tra count < COUNT_HALT1 || count > COUNT_HALT2 il secondo gli altri fino a COUNT_DONE */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

 
void *funCount1(void *);
void *funCount2(void *);
int  count = 0;

#define COUNT_DONE   8
#define COUNT_HALT1  3
#define COUNT_HALT2  5


int main(void)
{
   pthread_t thread1, thread2;
   pthread_create( &thread1, NULL, &funCount1, NULL);
   pthread_create( &thread2, NULL, &funCount2, NULL);

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);
 
   printf("Conto finale: %d\n",count);
   exit(EXIT_SUCCESS);

}
 
// Scrive i numeri 1-3 e 7-8 lasciati a funCount1() da funCount2()
void *funCount1(void * arg)
{
   for(;;)
   {
      // prende il lock del mutex 
      pthread_mutex_lock( &count_mutex );

      // Aspetta che funCount2() sblocchi count
      pthread_cond_wait( &condition_var, &count_mutex );
      count++;
      printf("valore di count - funCount1: %d\n",count);
      pthread_mutex_unlock( &count_mutex );
      if(count >= COUNT_DONE) return(NULL);
    }
}
 
//Scrive i numeri 3-7
 
void *funCount2(void * arg)
{
    for(;;)
    {
       pthread_mutex_lock( &count_mutex );

       if( count < COUNT_HALT1 || count > COUNT_HALT2) 
          // Questi numeri sono delegati a funCount1
          // funCount1() viene ripristinata e puo' modificare "count".
          pthread_cond_signal( &condition_var );
       else
       {
          count++;
          printf("valore di count - funCount2: %d\n",count);
       }
       pthread_mutex_unlock( &count_mutex );
       if(count >= COUNT_DONE) return(NULL);
    }
}

