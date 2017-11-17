#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/msg.h>
#include <string.h>

int main(){
	int number;
	scanf("%d\n", &number);

	int msq_id;
	key_t key = 125;
	int msq_result;
	key_t msq_key_result = 121;

	struct mymsgbuf
	{
		long mtype;
		char mtext[81];
	} mybuf;

	if ((msq_id = msgget(key, 0666 | IPC_CREAT)) < 0){
		printf("Can't get msqid\n");
		exit(-1);
	}

	if ((msq_result = msgget(msq_key_result, 0666 | IPC_CREAT)) < 0){
		printf("Can't get msqid\n");
		exit(-1);
	}

	mybuf.mtype = getpid();
	strcpy(mybuf.mtext, number);
	int length;
	length = (int)strlen(mybuf.mtext) + 1;

	if (msgsnd(msq_id, (struct msgbuf *) &mybuf, length, 0) < 0){
		printf("Can't send msg to queue\n");
		exit(-1);
	}

	int flag;
	int max_length = 15;

	while (flag == 0){
		if ((length = (int)msgrcv(msq_result, (struct msgbuf *)&mybuf, max_length, getpid(), 0)) < 0){
			printf("Can't receive msg from queue\n");
			exit(-1);
		}
		if (mybuf.mtype == getpid()){
			flag = 1;
			printf("pid %ld, result %c", mybuf.mtype, mybuf.mtext);
		}

	}



return 0;
}
