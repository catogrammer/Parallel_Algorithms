#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void task1 (){
	pid_t pid = fork();
	if(pid < 0){
		printf("Process is wasn't fork");
	}else if(pid > 0 ){
		printf("parent 1: %d\n", getpid());
	}else if(pid == 0){
		printf("daughter 1: %d\n", getpid());

		pid = fork();
		if(pid < 0){
			printf("Process is wasn't fork");
		}else if(pid == 0){
			printf("daughter 2: %d\tparent 2: %d\n", getpid(), getppid());
			pid = fork();
		}else if(pid > 0 ){
			printf("parent 2: %d\n", getpid());

			pid = fork();
			if(pid < 0){
				printf("Process is wasn't fork");
			}else if(pid == 0){
				printf("daughter 2: %d\tparent 2: %d\n ", getpid(), getppid());
			}

		}else{
			wait(NULL);
			wait(NULL);
			}

	}else
		wait(NULL);

}

void task2 (){
	pid_t pid = fork();
	if( pid < 0 ) {
		printf("Process is wasn't fork");
	}else if( pid > 0 ){
		printf("parent 1: %d\n", getpid());
	}else if( pid == 0 ){
		printf("daughter 1: %d\n", getpid());

		pid_t pid = fork();
		if( pid < 0 ) {
			printf("Process is wasn't fork");
		}else if( pid > 0 ){
			printf("parent 2: %d\n", getpid());
		}else if( pid == 0 ){
			printf("daughter 2: %d\n", getpid());
			
			pid_t pid = fork();
			if( pid < 0 ) {
				printf("Process is wasn't fork");
			}else if( pid > 0 ){
				printf("parent 3: %d\n", getpid());
			}else if( pid == 0 ){
				printf("daughter 3: %d\n", getpid());
			}
		}
	}else
		wait(NULL);
}

void task3 (){
	pid_t pid = fork();
	if(pid < 0){
		printf("Process is wasn't fork");
	}else if(pid == 0){
		printf("daughter 1: %d\tparent 2: %d\n", getpid(), getppid());
		pid = fork();
	}else if(pid > 0 ){
		printf("parent 1: %d\n", getpid());

		pid = fork();
		if(pid < 0){
			printf("Process is wasn't fork");
		}else if(pid == 0){
			printf("daughter 2: %d\tparent 2: %d\n", getpid(), getppid());

			pid_t pid = fork();
			if( pid < 0 ) {
				printf("Process is wasn't fork");
			}else if( pid > 0 ){
				printf("parent 3: %d\n", getpid());
			}else if( pid == 0 ){
				printf("daughter 3: %d\n", getpid());
			}
		}
	}else
		wait(NULL);
}

int main (){
	printf("root process: %d\n", getpid());
	// task1();
	// task2();
	task3();
	
	return 0;
}
