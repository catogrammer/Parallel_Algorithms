#include <stdio.h>
#include <signal.h>

void handler( int signum ) {
    printf("Catch signal!\n");
}

int main() {       
    //signal( SIGINT, &handler );   
    signal( SIGHUP, &handler );   
    
    printf("Sleeping...\n");
    while( 1 ) 
        sleep(5);    
}