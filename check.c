#include <stdlib.h>
#include <stdio.h>

#include <omp.h>


int main(int argc, char const *argv[])
{
	int i, s = 0, k = 0;
	#pragma omp parallel shared(s)
	{
		#pragma omp for
		for( i = 0; i < 20; i++){
			#pragma omp atomic
			s += i;
		}
	}
	printf("%d ", s);

	for( i = 0; i < 20; i++){
			k += i;
	}
	printf("%d ", k);
    return 0;
}
