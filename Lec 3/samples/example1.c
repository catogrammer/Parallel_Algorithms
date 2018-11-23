#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid, ppid, uid, gid;

	pid  = getpid();
	ppid = getppid();
	uid  = getuid();
	gid  = getgid();

	printf("pid  = %d\nppid = %d\nuid  = %d\ngid  = %d\n", pid, ppid, uid, gid);
}