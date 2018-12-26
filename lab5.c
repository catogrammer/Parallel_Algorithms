#include <stdlib.h>
#include <stdio.h>

// export OMP_NUM_THREADS=4 && time ./a.out

#include <omp.h>

// static long steps = 5000000000;
static long steps = 500000000;
// static long steps = 50000000;
// static long steps = 50000;

double step;

int main() {
	int i, j, k;
    double x, tmp=0.0;
    double pi, sum = 0.0;
    double start = 0, end = 0;

    step = 1.0/(double) steps;

    int choice = 0;
    printf("Enter your choice : ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            for(k = 1; k < 21; k++){
                omp_set_num_threads(k);
                sum = 0.0;
                start = omp_get_wtime();
                #pragma omp parallel for reduction(+:sum) private(x)
                for (i=0; i < steps; i++) {
                    x = (i+0.5)*step;
                    sum += 4.0 / (1.0+x*x); 
                }
                pi = step * sum;
                end = omp_get_wtime();
                printf("threads = %i\n", k);
                printf("PI = %.16g \n", pi);
                printf("time: %f\n", end-start);
            }
            break;
        case 2:
            for(k = 1; k < 21; k++){
                omp_set_num_threads(4);
                x = 0.0; sum = 0.0;
                start = omp_get_wtime();
                #pragma omp parallel shared(sum) private(tmp)
                {
                    tmp = 0.0; 
                    #pragma omp for private(x)
                    for (i=0; i < steps; i++) {
                        x = (i+0.5)*step;
                        tmp += 4.0 / (1.0+x*x); 
                    }
                    #pragma omp atomic
                    sum += tmp;
                }
                pi = step * sum;
                end = omp_get_wtime();
                printf("threads = %i\n", k);
                printf("PI = %.16g \n", pi);
                printf("time: %f\n", end-start);
            }
            break;
        default:
            printf("Error choice!");
    }
    return 0;
}