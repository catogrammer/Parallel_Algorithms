#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {    
    int *SHARED;
    
    key_t key = ftok( "./shm-idle.c", 1 );
    
    int sm;
    sm = shmget( key, sizeof(int), 0666 | IPC_CREAT );
    SHARED = (int*)shmat(sm, NULL, 0);
    
    printf("Current shared value: %d\n", *SHARED);
    *SHARED = getpid();
    printf("Set new value to: %d\n"    , *SHARED);        
    
    shmctl(sm, IPC_RMID, NULL);
    
    return 0;
}