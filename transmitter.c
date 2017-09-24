#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int CHAR_NUMBER = 6;
const int BITS_PER_CHAR = 8;


int main () {
	int trans_pid, rec_pid;
//	int msg_bin_letter[BITS_PER_CHAR * CHAR_NUMBER];
	char recieved_msg[CHAR_NUMBER * BITS_PER_CHAR];

	trans_pid = getpid ();
	printf ("my pid is %d, i am a transmitter\n", trans_pid);
	scanf ("%d", &rec_pid);
        printf ("the reciever's pid is %d\n", rec_pid);
	
	getchar();	

    int i, j;
    int msg_dec = 0;
    int pow2 = 1;

    for (i = 0; i < (CHAR_NUMBER * BITS_PER_CHAR); i++) {
	scanf("%c", &recieved_msg[i]);
	}

/*    for (i = 0; i < (CHAR_NUMBER * BITS_PER_CHAR); i++){
	    printf("%c", recieved_msg[i]);
	    }*/
//    printf ("\n");

	for (i = 0; i < CHAR_NUMBER; i++) {
		int current_msg = (int) recieved_msg[i];
		for (j = BITS_PER_CHAR * (i + 1) - 1; j >= BITS_PER_CHAR * (i); j--) {
	//		int current_msg_digit = (int) recieved_msg[j];
			if (recieved_msg[j] == '1'){
				msg_dec = msg_dec + pow2;		
			}
			pow2 = pow2 * 2;
		        }

		printf("%c", msg_dec);
		msg_dec = 0;
		pow2 = 1;
	        }

/*
    for (i = 0; i < CHAR_NUMBER * BITS_PER_CHAR; i++) {
	printf("%d", msg_bin_letter[i]);
        }
*/
        printf("\n");

return 0;


}
