// Передача данных от родительского процесса дочернему через канал

#include <stdio.h>
#include <unistd.h>

int main(void) {
    int n;
    int fd[2];
    pid_t pid;
    char line[255];
    
    if (pipe(fd) < 0) {
        printf("ошибка вызова функции pipe\n");
        return 1;
    }
    
    if ((pid = fork()) < 0) {
        printf("ошибка вызова функции fork\n");
        return 1;
    } else if (pid > 0) { /* родительский процесс */
        close(fd[0]);
        write(fd[1], "Hello\n", 6);
    } else { /* дочерний процесс */        
        close(fd[1]);
        n = read(fd[0], line, 255);
        printf("Message from parent: %s", line);
    }
    
    return 0;
}