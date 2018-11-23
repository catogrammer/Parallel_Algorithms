// Вывод списка всех переменных окружения текущего процесса

#include <stdio.h>

extern char **environ;

int main() {
    int i;
    
    for( i=0; environ[i] != NULL; i++ ) {
        printf("environ[%d]: %s\n", i, environ[i]);
    }    
}