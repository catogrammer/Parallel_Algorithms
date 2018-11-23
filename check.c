#include <stdlib.h>
#include <stdio.h>

void print_arr(int* arr, int size){
    int i = 0;
    for(; i < size; i++) {
       printf("%i", arr[i]);
    }
}

void init_arr(int* arr, int size){
    int i = 0;
    for(; i < size; i++) {
       arr[i] = i;
    }
}

int main(int argc, char const *argv[])
{
    int* a = malloc(6*sizeof(int));
    int* b = malloc(3*sizeof(int));
    int** c = malloc(2*sizeof(int*));
    c[0] = a;
    c[1] = b;
    init_arr(a, 6);
    int* p = a + 3;
    print_arr(c[0], 6);
    printf("\n");
    print_arr(c[1], 3);
    printf("\n");
    print_arr(p, 3);
    printf("\n");
    init_arr(p, 3);
    print_arr(p, 3);
    printf("\n");
    print_arr(c[0], 6);
    printf("\n");
    return 0;
}
