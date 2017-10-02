#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>


int j = 0;
int n = 0;
int counter = 0;
long long int current_sum[n + 1];

struct params{
	int left;
	int right;
};

void* my_func(void *pointer){
	int local_l, local_r;
	params* x;
	x = (params*)pointer; // x is the pointer for params
	local_l = x->left;
	local_r = x->right;

	
}

int main () {
	int right, left;
	int i = 0;
	int fail = 0;
	int pack = 0;
	int rest = 0;
	scanf("%d\n", &L);
	scanf("%d\n", &R);
	scanf("%d\n", &n);
	int j = L;
	digits_in_pack = (R - L)/(n);
	for (i = 0; i < n; i++){
		fail = pthread_create(&thread_id,
				(pthread_attr_t *)NULL,
				my_func,
				(void *)&thread_id
				);
		if (fail) {
			printf("can't create thread, returned value = %d\n", fail);
		}
	}

	return 0;

}
