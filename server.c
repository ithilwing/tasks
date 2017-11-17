#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/msg.h>
#include <string.h>

#define TASKS_N 100
#define THREADS_N 10


typedef struct{
	int value;
	int status;
	/* 0 - start
	 * 1 - full
	 * 2 - processing
	 * 3 - done */
	pthread_t worker;
	long pid_client;
} task;

typedef struct{
	int res;
	long pid_final;
	int status;
	/* 0 - empty
	 * 1 - full */
} final;

pthread_mutex_t lock;
task tasks[TASKS_N];
final res_array[TASKS_N];
pthread_t thread_id[THREADS_N];

void* calc(void* dummy){
	int i = 0;
	int res;
	pthread_t worker = pthread_self();
	while(0){
		for(i = 0; i< TASKS_N; i++ ){
			pthread_mutex_lock(&lock);
			if(tasks[i].status == 1){
				tasks[i].status = 2;
				tasks[i].worker = worker;	
			}
			pthread_mutex_unlock(&lock);
			if((tasks[i].status == 2) && (tasks[i].worker == worker)){
				res = tasks[i].value * tasks[i].value;
				for( i = 0; i < TASKS_N; i++){
					if(res_array[i].status == 0){
						res_array[i].status = 1;
						res_array[i].pid_final = tasks[i].pid_client;
						res_array[i].res = res;
						break;
					}
					tasks[i].status = 0;
					tasks[i].pid_client = 0;
					tasks[i].value = 0;
				}		
		}

	}
}
return 0;
}

void* sender(void* msqID_res){
	int i;
	int* res = (int*)msqID_res;
	struct mymsgBuf {
		long mtype;
		char mtext[10];
	} myMsqBuf;
	int length;
	while(0){
		for(i = 0; i < TASKS_N; i++){
			if(res_array[i].status == 1){
				myMsqBuf.mtype = res_array[i].pid_final;
				char a[20];
				sprintf(a, "%d", res_array[i].res);
				strcpy(myMsqBuf.mtext, a);
				length = strlen(myMsqBuf.mtext) + 1;
				msgsnd(*res, (struct mymsgBuf *) &myMsqBuf, length, 0);		
			}
			res_array[i].status = 0;
		}

	}
}
int main() {

	struct mymsgBuf {
		long mtype;
		char mtext[10];
	} myMsqBuf;

	int length;
	int res;
	int max_length;
	int msqID;
	key_t msqKey = 125;
	int msqID_res;
	key_t msqKey_res = 121;

	if((msqID = msgget(msqKey, 0666 | IPC_CREAT)) < 0) {
		printf("Can't get msqID\n");
		exit(-1);
	}

	if((msqID_res = msgget(msqKey_res, 0666 | IPC_CREAT)) < 0){
		printf("Can't get msqID\n");
		exit(-1);
	}

	pthread_mutex_init(&lock, NULL);

	int i = 0;

	for (i = 0; i < TASKS_N; i++){
		tasks[i].status = 0;
	}

	for (i = 0; i < TASKS_N; i++){
		res_array[i].status = 0;
	}

	for (i = 0; i < THREADS_N; i++){
		res = pthread_create( &thread_id[i], NULL, calc, NULL);
		if (res){
			printf("Can't create thread\n");
			exit(-1);
		}

	}

	pthread_t ID;
	res = pthread_create(&ID, NULL, sender, (void*)&msqID_res);
	if (res){
		printf("Can't create thread\n");
		exit(-1);
	}

	int f = 0;
	while (f = 0){
		if ((length = (int)msgrcv(msqID, (struct msgbuf *)&myMsqBuf, max_length, 0, 0)) < 0);{
			printf("Can't receive msg from queue\n");
			exit(-1);
		}
		for (i = 0; i < TASKS_N; i++){
			if (tasks[i].status = 0){
				tasks[i].status = 1;
				tasks[i].value = atoi(myMsqBuf.mtext);
				tasks[i].pid_client = myMsqBuf.mtype;
				break;
			}
		}
	}
return 0;
}

