#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int CHAR_NUMBER = 1;
const int BITS_PER_CHAR = 8;
int k = 1;
void wait() {
	k = 0;
}

//TRANSMITTER//
int main() {
    int trans_pid, rec_pid;
	char msg[CHAR_NUMBER];
    int msg_bin_letter[BITS_PER_CHAR * CHAR_NUMBER];

	signal(SIGUSR1, wait);

    trans_pid = getpid();
    printf("my pid is %d, i am a transmitter\n", trans_pid);
    scanf("%d", &rec_pid);
    printf("the reciever's pid is %d\n", rec_pid);

    getchar();

    int i, j;

    for (i = 0; i < CHAR_NUMBER; i++) {
	        scanf("%c", &msg[i]);
	}
		
	for (i = 0; i < CHAR_NUMBER; i++) {
        int current_msg = (int) msg[i];
		for (j = BITS_PER_CHAR * (i + 1) - 1; j >= BITS_PER_CHAR * i; j--) {
			msg_bin_letter[j] = current_msg % 2;
			current_msg >>= 1;
        }
	}
	
  /*  for (i = 0; i < CHAR_NUMBER * BITS_PER_CHAR; i++) {
        printf("%d", msg_bin_letter[i]);
    }

    printf("\n");
*/

	for (i = 0; i < CHAR_NUMBER * BITS_PER_CHAR; i++) {
		if (msg_bin_letter[i] == 1){
			kill (rec_pid, SIGUSR1);
		}
		else
			kill (rec_pid, SIGUSR2);
		while (k != 0){
		}	
		k = 1;	
	}

    return 0;
}

