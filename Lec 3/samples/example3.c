#include <stdio.h>
#include <unistd.h>

int main() {
	
	char cmd[10];
	pid_t pid;

	while( 1 ) {
		printf("Enter the command: ");
		scanf("%s", cmd);

		pid = fork();
		if ( pid == 0 ) {
			printf("Processing command: %s\n", cmd);

			int r = execlp( cmd, cmd, NULL );

			printf("This text should be never printed\n");

			return 0;
				
		}
		else {
			wait(NULL);
		}		
	}
}