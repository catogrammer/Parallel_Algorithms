#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * start_thread (void *message)
{
    printf("PID: %d, %s\n", getpid(), (const char *) message);
    //printf("PThreadID: %d\n", pthread_self());
    return message;
}

int main (void)
{
    pthread_t thing1, thing2;
    const char *message1 = "Thing 1";
    const char *message2 = "Thing 2";
    
    /* Создаются два потока, каждый со своим сообщением */
    pthread_create (&thing1, NULL, start_thread, (void *) message1);
    pthread_create (&thing2, NULL, start_thread, (void *) message2);
    
    pthread_join (thing1, NULL);
    pthread_join (thing2, NULL);
    
    return 0;
}