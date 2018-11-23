#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {    
    int *SHARED;
    
    int sm;
    sm = shmget( IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT | IPC_EXCL );
    SHARED = (int*)shmat(sm, NULL, 0);
    
    *SHARED = 777;
    
    int pid = fork();
    
    if ( pid == 0 ) {
        printf("Child initial SHARED = %d\n", *SHARED);
        sleep(5);
        printf("Child next SHARED    = %d\n", *SHARED);
    }
    else {
        printf("Parent initial SHARED = %d\n", *SHARED);
        sleep(2);
        *SHARED = 999;
        printf("Parent modify SHARED  = %d\n", *SHARED);        
        wait(NULL);
    }
    
    shmctl(sm, IPC_RMID, NULL);
}