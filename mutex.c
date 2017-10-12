#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define TASK_N 100
#define THREADS_N 10

typedef enum{
	NEW,
	PROCESSING,
	DONE
}statuses;

//typedef struct{
//	int counter;
//	pthread_t name;
//}personal;

typedef struct{
	int duration;
	int id;
	statuses status;
	pthread_t worker;
	int counter;
}task_t;

int flag = 0;
pthread_mutex_t lock;

task_t tasks[TASK_N];
pthread_t thread_id[THREADS_N];
//personal worker_id[THREADS_N];
//long int pthread_self[THREADS_N];

void* func(void* dummy){
//	int* t;
//	t = (int*) j;
  //     	int z = *t;	
	int i;
//	for(i = 0; i < THREADS_N; i++){	
//		pthread_self[i] = pthread_self();
//	}
	
	for(i = 0; i < TASK_N; i++){
	     	pthread_mutex_lock(&lock);
		if( tasks[i].status == 0){
			tasks[i].worker = pthread_self();
			tasks[i].status= 1;
		//	sleep(tasks[i].duration);
		//	tasks[i].status = 2;
		//	tasks[i].counter++;
		}
	pthread_mutex_unlock(&lock);
	if ((tasks[i].status == 1) && (tasks[i].worker == pthread_self() ) ){

		usleep(tasks[i].duration);
		tasks[i].counter++;
		tasks[i].status = 2;
		
		printf("Worker %ld has finished task %d\n", pthread_self(), tasks[i].id );
//		worker_id[z].counter++;
//		printf("counter is %d/n", worker_id[z].counter);
		}
	}
        return NULL;
}       

int main(){
	int i, k, j;
	int thread_res;
	for(i = 0; i < TASK_N; i++){
		tasks[i].status = 0;
		tasks[i].id = i;
		tasks[i].duration = 1;
		tasks[i].counter = 0;
	}
	for(i = 0; i < THREADS_N; i ++){
		thread_res = pthread_create(&thread_id[i], NULL, func, NULL);
//		worker_id[j].name = j;
	}
	if(thread_res){
		printf("Can not create thread\n");
		exit(0);
	}
/*	if( flag == 100)
		printf("All tasks have been complete\n");
	else
		printf("ERROR\n");*/
	for(i = 0; i < THREADS_N; i++){
		pthread_join(thread_id[i], NULL);
	}
        for(i = 0; i < TASK_N; i++){
	        k = tasks[i].counter + k;
	}
	        printf("Task was done %d times\n", k);
	


	return 0;

}

