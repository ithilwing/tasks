/*Иллюстрация работы с разделяемой памятью*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
	int *get_number; /* Указатель на разделяемую память */
	int *final_number;
	int shmid; /* IPC дескриптор для области разделяемой памяти */
	int is_new = 1; /* инициализации элементов массива */
	key_t key = 123; /* IPC ключ, ipcrm удалит по ключу */
	int semid;
	key_t semkey = 124;
	struct sembuf mybuf;

	if ((shmid = shmget(key, 2 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {

		if(errno != EEXIST) {
			printf("Can't create shared memory\n");
			exit(-1);
		} else {
			if((shmid = shmget(key, 2 * sizeof(int), 0)) < 0){
				printf("Can't find shared memory\n");
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

//              scanf("%d", get_number); 	

//	mybuf.sem_op = 1;
//	mybuf.sem_flg = 0;
//	mybuf.sem_num = 1;

//	printf("ok b, i know you were launched too\n");

//	mybuf.sem_op = -1;
//	mybuf.sem_flg = 0;
//	mybuf.sem_num = 0;
	
	scanf("%d", &get_number[0]); 
	mybuf.sem_op = 1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 1;

	if(semop(semid, &mybuf, 1) < 0){
		printf("Can't wait for condition");
		exit(-1);
	}	

	mybuf.sem_op = -1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;

	if(semop(semid, &mybuf, 1) < 0){
		printf("Can't wait for condition");
		exit(-1);
	}
	printf("wait\n");
	printf("%d\n", get_number[1]);


	if (shmdt(get_number) < 0) {
		printf("Can't detach shared memory\n");
		exit(-1);
	}

	return 0;
}
