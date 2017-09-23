#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int CHAR_NUMBER = 2;
const int BITS_PER_CHAR = 8;

int main () {
        int trans_pid = 0;
        int rec_pid = 0;
	int i = 0;
	int j = 0;
	char msg[CHAR_NUMBER];
	char msg_bin_letter[BITS_PER_CHAR];

        rec_pid = getpid ();
        printf ("my pid is %d, i am a reciever\n", rec_pid);
        scanf ("%d", &trans_pid);
        printf ("the transmitter's pid id %d\n", trans_pid);


	for (i = 0; i < CHAR_NUMBER; msg[i] = '\0', i++);

        for (i = 0; i < CHAR_NUMBER; i++){
	        msg[i] = getchar();
	}

		
	for (i = 0; i < CHAR_NUMBER; i++){
		for (j = 0; j < BITS_PER_CHAR; j++){
			msg_bin_letter[j] = msg[i] % 2;
			msg[i] >>= 1;
			printf("%d", msg_bin_letter[j]); 
		}
				
	
	}
	
return 0;

}

