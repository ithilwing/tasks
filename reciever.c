#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define char_number  20

int main () {
        int trans_pid = 0;
        int rec_pid = 0;
	int i = 0;
	int j = 0;
	char msg[char_number];
	char msg_bin_letter[8];
        rec_pid = getpid ();
        printf ("my pid is %d, i am a reciever", rec_pid);
        scanf ("%d", &trans_pid);
        printf ("the transmitter's pid id %d", trans_pid);

		
	for (i = 0; i < char_number; i++){
		for (j = 0; j < 8; j++){
			msg_bin_letter[j] = msg[i] % 2;
			msg[i] = msg[i] >> 1;
			printf("%d", msg_bin_letter[j]); 
		}
				
	
	}
	
return 0;

}

