//Kapova, Smirnov and an independent expert 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>


typedef struct{
	long int left;
	long int right;
	long long int sum;
}params;

void* my_func(void *pointer){
	params* x;
	x = (params*)pointer; // x is the pointer for params
	int k = x->left;
	x->sum = 0;
	for (k = x->left; k <= x->right; k++){
//		printf("%d\n", x->left);
		x->sum = x->sum + k;
	}
	return x;

	
}

int main () {
	long int L, R;
	int n;
	int i = 0;
	int thread_result = 0;
	long long int final_result = 0;
	int digits_in_pack = 0;
	int last_left;
	printf("Enter left border: ");
	scanf("%ld", &L);
        printf("Enter right border: ");
	scanf("%ld", &R);
        printf("Enter number of threads: ");
	scanf("%d", &n);

	digits_in_pack = (R - L + 1)/(n);
//	printf("\n%d digits in pack\n",digits_in_pack );
	

	params* structures = (params*) malloc(sizeof(params) * n);
	pthread_t* thread_id = malloc(sizeof(pthread_t) * n);


	for (i = 0; i < n; i++){
		
		structures[i].left = L + (i * digits_in_pack);
		structures[i].right = structures[i].left + digits_in_pack - 1;
	//	printf("%d structures[%d].left and ", structures[i].left, i);
        //        printf("%d structures[%d].right\n", structures[i].right, i);	
		
		thread_result = pthread_create(&thread_id[i],
				NULL,
				my_func,
				(params*)&structures[i]
				);
		if (thread_result) {
			printf("can't create thread, returned value = %d\n", thread_result);
			exit(0);
		}
	//	structures[i].left = structures[i].left + 1;

	}

	for (i = 0; i < n; i++){
		pthread_join(thread_id[i], NULL);
		final_result = final_result + structures[i].sum;
	}
//	int digits_left = R -  (( R - L + 1) % n);
	last_left = L + (digits_in_pack * n);
//	int in_last_pack = R - (last_left) + 1
//	printf("last_left = %d and digits left = %\n", last_left, digits_left);
	for (i = last_left; i <= R; i++){
		final_result = final_result + i;

	}

	printf("Congratulations!\nThe sum from %ld to %ld is %lld\n",L, R, final_result);

	free(structures);
	free(thread_id);

	

	return 0;

}
