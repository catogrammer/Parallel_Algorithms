#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>                                                                                                                                                                                   
#include <sys/stat.h>                                                                                                                                                                                    
#include <fcntl.h> 

long s = 0;

void * start_thread () {

    //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);    
    //pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, NULL );
    pthread_setcanceltype( PTHREAD_CANCEL_DEFERRED, NULL );

    while( 1 ) {        
        s += 1;        
        sleep(1);
        pthread_testcancel();
    }       
}

int main (void)
{
    
    pthread_t thing1;
        
    pthread_create (&thing1, NULL, start_thread, NULL);   
        
    int d;
    printf("Press any key and enter: ");
    scanf("%d", &d);
    
    int r = pthread_cancel( thing1 );
    printf("pthread_cancel result: %d\n", r);
    
    r = pthread_join (thing1, NULL);
    printf("pthread_join result: %d\n", r);
    
    printf("Var result: %lu\n", s);

}
        