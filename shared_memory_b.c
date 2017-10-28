#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int *get_number;
	int *final_number;
	int shmid;
	int is_new = 1;
	key_t key = 123; /* IPC ключ */
	int semid;
	key_t semkey = 124;
	struct sembuf mybuf;


	if ((shmid = shmget(key, 2 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
		if(errno != EEXIST){
			printf("Can't create shared memory\n");
			exit(-1);
		} else {
			if((shmid = shmget(key, 2 * sizeof(int), 0)) < 0) {
				printf("Can't find shared memory\n");
				strerror(errno);
				exit(-1);
			}
			is_new = 0;
		}
	}

	if ((semid = semget(semkey, 2, 0666 | IPC_CREAT)) < 0){
		printf("Can't get semid\n");
		exit(-1);
	}

	if ((get_number = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
		printf("Can't attach shared memory\n");
		exit(-1);
	}

	if((final_number = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
	printf("Can't attach shared memory\n");
	exit(-1);

	}

	
//	mybuf.sem_op = -1;
//	mybuf.sem_flg = 0;
//	mybuf.sem_num = 1;

//	printf("ok a, i know you were launched\n");

	mybuf.sem_op = -1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 1;

	if(semop(semid, &mybuf, 1) < 0){
		printf("Can't wait for condition");
		exit(-1);
	}

	printf("so what's next?\n");
	
	int a = *get_number;
	int b = a * a;
//	*final_number = (*get_number) * (*get_number);
	*final_number = b;
	printf("%d\n", *final_number);
	printf("%d\n", *final_number);
//	printf("%d\n", b);
	
	
	mybuf.sem_op = 1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;

	if(semop(semid, &mybuf, 1) < 0){
		printf("Can't wait for condition");
		exit(-1);
	}

	printf("done\n");


	if(shmdt(get_number) < 0){
		printf("Can't detach shared memory\n");
		exit(-1);
	}

	if(shmdt(final_number) < 0){
		printf("Can't detach shared memory\n");
		exit(-1);
	}

	return 0;
}
