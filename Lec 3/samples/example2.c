#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid;

	pid = fork();
	if ( pid == 0 ) {
		// Child
		printf("Child\n");
		sleep(10);
	}
	else {
		// Parent
		printf("Parent\n");
		sleep(10);
	}

	printf("Finished\n");

	return 0;
}