#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <sys/wait.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#include <semaphore.h>  // compile with flag -pthread
#include "omp.h"

sem_t mutex;

void print_Matrix(int* const matrix, unsigned num_rows, unsigned num_columns){
    int i = 0;
    for(; i < num_rows*num_columns; i++){
		if(i != 0 && i%num_columns == 0)
			printf("\n");
        printf("%i ", matrix[i]);
    }
	printf("\n");
}

void print_Vector(int* const vector, unsigned size){
	int i = 0;
	printf("[ ");
	for(; i < size; i++){
		printf("%i ", vector[i]);
	}
	printf("]\n");
}

int** generate_data(unsigned num_rows, unsigned num_columns){

	// printf("sizeof(unsigned) = %LU", sizeof(unsigned));
	// if( num_rows*num_columns < sizeof(unsigned))
	// 	printf("All's good!\n");

	int** data = malloc(2*sizeof(int*));
    int* g_matrix = malloc(num_rows*num_columns*sizeof(int));
	int* g_vector = malloc(num_columns*sizeof(int));

	srand(time(NULL));

	int i = 0, j = 0;
	for(; i < num_rows*num_columns; i++){
		g_matrix[i] = rand()%50; // min + rand()%(max - min)
	}
	
	for(; j < num_columns; j++){
		g_vector[j] = rand()%50;
	}
	
	data[0] = g_matrix;
	data[1] = g_vector;
	
    return data;
}

//***************************************************************************

int multiple_two_vectors(int* vec1, int* vec2, unsigned size){
	int result = 0;
	int i = 0;
	for(; i < size; i++){
		result += vec1[i]*vec2[i];
	}
	return result;
}

void mult_rows_by_vector(int** SHARED, int num_columns, int range_begin, int range_end){
	int i = range_begin;
	for(; i < range_end; i++){
		SHARED[0][i] = multiple_two_vectors(SHARED[1], SHARED[2] + 	i*num_columns, num_columns);
		// printf("\n");
		// printf("%d ", SHARED[0][i]);
	}
	// printf("\n----------------!\n");
}

void init_shared_mem(int* arr, int* data, int size){
	int i = 0;
	for(; i < size; i++){
		arr[i] = data[i];
	}
}

int* parallel_calc__rows_by_vector_(int** data, unsigned num_rows, unsigned num_columns, unsigned num_processes){
	int* res_vector;
	int scale_ = num_rows/num_processes;
	double start = 0, end = 0, diff_time = 0;
	int *SHARED[3]; //[0] -result_vec, [1]-vector, [2]-matrix
    int sm_0, sm_1, sm_2;
    sm_0 = shmget( IPC_PRIVATE, num_columns*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL ); //result
	sm_1 = shmget( IPC_PRIVATE, num_columns*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL ); //vector
	sm_2 = shmget( IPC_PRIVATE, num_columns*num_rows*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL ); //martix
	SHARED[0] = (int*)shmat(sm_0, NULL, 0);
	SHARED[1] = (int*)shmat(sm_1, NULL, 0); //vector
	SHARED[2] = (int*)shmat(sm_2, NULL, 0); //martix
	init_shared_mem(SHARED[1], data[1], num_columns);
	init_shared_mem(SHARED[2], data[0], num_columns*num_rows);
	
	start = omp_get_wtime();
	for(size_t i = 0; i < num_processes; i++){
		pid_t pid = fork();
		
		if(pid < 0){
			printf("Process wasn't created");
		}else if( !pid ){
			if( i+1 == num_processes ){
				mult_rows_by_vector(SHARED, num_columns, scale_*i, num_rows);
			}else{
				mult_rows_by_vector(SHARED, num_columns, scale_*i, scale_*(i+1));
			}
			exit(EXIT_SUCCESS);
		}
	}
	while(wait(NULL)>0){}
	res_vector = SHARED[0];
	shmctl(sm_0, IPC_RMID, NULL);
	shmctl(sm_1, IPC_RMID, NULL);
	shmctl(sm_2, IPC_RMID, NULL);
	end = omp_get_wtime();
	printf("diff time = %.16g\n", end - start);
	return res_vector;
}

//****************************************************************************

void multiple_1234(int* vec1, int* vec2, int el, int num_columns, unsigned size){
	int i = 0;
	for(; i < size; i++){
		int a = *(vec2 + i*num_columns)*el;
		sem_post(&mutex); //increment
		vec1[i] += a;
		sem_wait(&mutex); //decrement
	}
}

void mult_columns_by_element(int** SHARED, int num_rows, int num_columns, int range_begin, int range_end){
	int i = range_begin;
	
	for(; i < range_end; i++){
		multiple_1234(SHARED[0], SHARED[2] +  i, SHARED[1][i], num_columns, num_rows);
	}
	
}

int* parallel_calc__columns_by_element_(int** data, unsigned num_rows, unsigned num_columns, unsigned num_processes){
	int* res_vector;
	double start = 0, end = 0, diff_time = 0;
	int scale_ = num_columns/num_processes;
	int *SHARED[3]; //[0] -result_vec, [1]-vector, [2]-matrix
    int sm_0, sm_1, sm_2;
    sm_0 = shmget( IPC_PRIVATE, num_columns*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL ); //result
	sm_1 = shmget( IPC_PRIVATE, num_columns*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL ); //vector
	sm_2 = shmget( IPC_PRIVATE, num_columns*num_rows*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL ); //martix
	SHARED[0] = (int*)shmat(sm_0, NULL, 0);
	SHARED[1] = (int*)shmat(sm_1, NULL, 0); //vector
	SHARED[2] = (int*)shmat(sm_2, NULL, 0); //martix
	init_shared_mem(SHARED[1], data[1], num_columns);
	init_shared_mem(SHARED[2], data[0], num_columns*num_rows);

	sem_init(&mutex, sm_0, 1); 
	start = omp_get_wtime();
	for(size_t i = 0; i < num_processes; i++){
		pid_t pid = fork();
		
		if(pid < 0){
			printf("Process wasn't created");
		}else if( !pid ){
			if( i+1 == num_processes ){
				mult_columns_by_element(SHARED, num_rows, num_columns, scale_*i, num_columns);
			}else{
				mult_columns_by_element(SHARED, num_rows, num_columns, scale_*i, scale_*(i+1));
			}
			exit(EXIT_SUCCESS);
		}
	}
	while(wait(NULL)>0){}
	// print_Vector(SHARED[0], num_columns);
	res_vector = SHARED[0];
	shmctl(sm_0, IPC_RMID, NULL);
	shmctl(sm_1, IPC_RMID, NULL);
	shmctl(sm_2, IPC_RMID, NULL);

	end = omp_get_wtime();
	printf("diff time = %.16g\n", end - start);

	return res_vector;
}

void menu(){
	printf("1 - Rows by vector\n2 - Columns by element\n");
}

int main(int argc, char const *argv[]){

	// printf("This is parant: id = %i\n", getpid());
	unsigned num_processes = 3;
	unsigned rows = 15000, columns = 15000;
	if(argc > 1){
		num_processes = atoi(argv[1]);
	}
	printf("num of proc : %i\n", num_processes);
	int** data = generate_data(rows, columns);
	int* matrix = data[0];
	int* vector = data[1];
	// print_Matrix(matrix, rows, columns);
	// print_Vector(vector, columns);
	int* result;
	int choice = 0;
	menu();
	printf("Enter your choice : ");
	scanf("%d", &choice);
	switch(choice){
		case 1:
			result = parallel_calc__rows_by_vector_(data, rows, columns, num_processes);
			// printf("Multiplay rows by vector     : ");
			// print_Vector(result, rows);
			printf("End calc rows by vector!");
			break;
		case 2: 
			result = parallel_calc__columns_by_element_(data, rows, columns, num_processes);
			// printf("Multiplay columns by element : ");
			// print_Vector(result, rows);
			printf("End calc columns by element!");
	}
	
    return 0;
}
