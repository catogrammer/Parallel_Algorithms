#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define _USE_MATH_DEFINES 
#include <math.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "omp.h"

// compile with flag -lm for math.h
// compile with flag -fopenmp for omp.h

long double calc_part_of_PI ( int begin, int end ){
    long double part_PI = 0;
    int i = 0;
    for(i = begin; i < end; i++)
        part_PI += ( pow( -1, (i+1)%2 ) * 4 ) / ( 2*i -1 );

    return part_PI;
}

long double prl_culc_PI(unsigned long long num_of_addend, int num_of_process){
	
    long double PI = 0;
	int *fd =(int *)malloc(2*num_of_process*sizeof(int));
	int range_ = num_of_addend/num_of_process;

    int i = 0;
    for( i; i < num_of_process; i++){
		if (pipe(fd+i*2) < 0) {
			printf("Error coll of function pipe\n");
			return 1;
   		}	
    	pid_t pid = fork();
        if ( pid < 0 )
            printf("Process wasn't created!");
        else if ( !pid ){
			close(fd[2*i]);
			long double tmp;
			if( i+1 == num_of_process ){
				tmp = calc_part_of_PI( i*range_ + 1, num_of_addend + 1);
				write(fd[2*i+1],  &tmp, sizeof(long double));
				}
			else{
				tmp = calc_part_of_PI( i*range_ + 1, (i+1)*range_ + 1);
				write(fd[2*i+1], &tmp, sizeof(long double));
			}

			exit(EXIT_SUCCESS);
		}
    }

	while(wait(NULL)>0){} 

	int k = 0;
	
	for( k; k < num_of_process; k++ ){
		long double interm = 0;
		close(fd[2*k+1]);
		read(fd[2*k], &interm, sizeof(long double));
		// printf("interm = %Lf\n", interm);
		PI += interm;
	}
    
    return PI;
}

int main(int argc, char const *argv[])
{	
    long double PI = 0;
	double start = 0, end = 0, diff_time = 0;
    unsigned long long num_of_addend = 100000000; int num_of_process = 3;
	FILE *fp;

	if(argc > 2){
		num_of_addend = atoi(argv[1]);
		num_of_process = atoi(argv[2]);
		start = omp_get_wtime();
		PI = prl_culc_PI(num_of_addend, num_of_process);
		end = omp_get_wtime();
		printf("diff time = %.16g\n", end - start);    
		printf("define PI = %.20f\n", M_PI);
		printf("\n       PI = %.20Lf\n", PI);
		long double diff = M_PI-PI;
		printf("\ndiff   PI = %.20Lf\n", diff);
	}
	
	if( argc == 2 ){

		start = omp_get_wtime();
		// num_of_process = atoi(argv[1]);
		// printf("num of proc = %d", num_of_process);
		// PI = prl_culc_PI(num_of_addend, num_of_process);
		// end = omp_get_wtime();
		int i;
	
		for( i = 1; i < 21;i++){
			num_of_process = i;
			start = omp_get_wtime();
			PI = prl_culc_PI(num_of_addend, num_of_process);
			end = omp_get_wtime();
			printf("diff time = %.16g\n", end - start);
			long double diff = M_PI-PI;
			printf("diff   PI = %.20Lf\n", diff);
		}
		// printf("diff time = %.16g\n", end - start);    
		// printf("define PI = %.20f\n", M_PI);
		// printf("\n       PI = %.20Lf\n", PI);
		// long double diff = M_PI-PI;
		// printf("diff   PI = %.20Lf\n", diff);

	}else if( !strcmp(argv[1], "tofile") ){
		fp = fopen("data.txt", "w");
		
		if( fp == 0){
			printf("error open file\n");
			return 0;
		}
	
		for( ; num_of_process < 15; num_of_process++){
			start = 0; end = 0;
			start = omp_get_wtime();
			PI = prl_culc_PI(num_of_addend, num_of_process);
			end = omp_get_wtime();
			diff_time = end - start;
			printf("%d ", num_of_process);
			printf("%.16g\n", diff_time);
			fprintf(fp, "%d ", num_of_process);
			fprintf(fp, "%.16g\n", diff_time);
		}

		fclose(fp);
	}

    return 0;
}
